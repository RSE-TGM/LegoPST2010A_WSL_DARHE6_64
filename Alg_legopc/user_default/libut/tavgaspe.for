C***********************************************************************
C*                                                                     *
C*                   VERSIONE MODIFICATA PER ARIA/METANO               *
C*                          IL 22/08/2000                              *
C*                                                                     *
C***********************************************************************
C
      REAL FUNCTION CASPEG (igas)                                           !SNGL
C      DOUBLE PRECISION FUNCTION CASPEG ()                               !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      go to (1,2) ,igas
C     aria
 1    CASPEG=  1100.
      RETURN
C     metano  
 2    CASPEG = 3223.22
      RETURN
      END


      REAL FUNCTION ERREGP (igas)                                           !SNGL
C      DOUBLE PRECISION FUNCTION ERREGP ()                               !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      go to (1,2) ,igas
C     aria
 1    ERREGP=  287.
      RETURN
C     metano  
 2    ERREGP = 396.85*0.9438
      RETURN
      END


      SUBROUTINE THINGP (T,H,INDEX,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CP = CASPEG(igas)
      IF (INDEX .EQ. 1) THEN
        CALL CHCKGP (2, T,igas)
        H = (T - 273.15) * CP
      ELSE IF (INDEX .EQ. 2) THEN
        CALL CHCKGP (4, H,igas)
        T = H / CP + 273.15
      ELSE
        PRINT '(A,I3)',' Opzione non riconosciuta:',INDEX
        STOP 'Errore in THGP'
      ENDIF
      RETURN
      END


      SUBROUTINE RTPIGP (RO,T,P,INDEX,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      R1 = ERREGP(igas)
      IF (INDEX .EQ. 1) THEN
        CALL CHCKGP (2, T,igas)
        CALL CHCKGP (3, RO,igas)
        P = RO * T * R1
      ELSE IF (INDEX .EQ. 2) THEN
        CALL CHCKGP (1, P,igas)
        CALL CHCKGP (3, RO,igas)
        T = P / (RO * R1)
      ELSE
        PRINT '(A,I3)',' Opzione non riconosciuta:',INDEX
        STOP 'Errore in TPGP'
      ENDIF
      RETURN
      END


      SUBROUTINE STPIGP (S,T,P,INDEX,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CP = CASPEG(igas)
      R1 = ERREGP(igas)
      IF (INDEX .EQ. 1) THEN
        CALL CHCKGP (2, T,igas)
        P = 101325. * EXP ((CP * LOG (T / 273.15) - S) / R1)
      ELSE IF (INDEX .EQ. 2) THEN
        CALL CHCKGP (1, P,igas)
        T = 273.15 * EXP ((S + R1 * LOG (P / 101325.)) / CP)
      ELSE
        PRINT '(A,I3)',' Opzione non riconosciuta:',INDEX
        STOP 'Errore in TSGP'
      ENDIF
      RETURN
      END


      SUBROUTINE TAVOGP (P,T,RO,H,S,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      R1 = ERREGP(igas)
      CP = CASPEG(igas)
      CALL CHCKGP (1, P,igas)
      CALL CHCKGP (2, T,igas)
      RO = P / (R1 * T)
      H  = CP * (T - 273.15)
      S  = CP * LOG (T / 273.15) - R1 * LOG (P / 101325.)
      RETURN
      END


      SUBROUTINE R1CPGP (R1,CP,CV,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      R1 = ERREGP(igas)
      CP = CASPEG(igas)
      CV = CP - R1
      RETURN 
      END


      SUBROUTINE DRPSGP (P,T,DRDP,DRDS,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CP = CASPEG(igas)
      R1 = ERREGP(igas)
      CALL CHCKGP (1, P,igas)
      CALL CHCKGP (2, T,igas)
      DEN = CP * R1 * T
      DRDP = (CP - R1)/ DEN
      DRDS = - P / DEN
      RETURN
      END


      SUBROUTINE DRPTGP (P,T,DRDP,DRDT,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CP = CASPEG(igas)
      R1 = ERREGP(igas)
      CALL CHCKGP (1, P,igas)
      CALL CHCKGP (2, T,igas)
      DRDP = 1. / (R1 * T)
      DRDT = - P * DRDP / T
      RETURN
      END


      SUBROUTINE CHCKGP (INDEX,ARG,igas)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      LOGICAL VAMALE
      VAMALE = .FALSE.
      IF (INDEX .EQ. 1) THEN
        IF (ARG .LE. 0.) THEN
          PRINT '(A,G12.5)', ' Pressione non positiva [in Pa] = ', ARG
          VAMALE = .TRUE.
        ENDIF
      ELSE IF (INDEX .EQ. 2) THEN
        IF (ARG .LE. 0.) THEN
          PRINT '(A,G12.5)', ' Temperatura non positiva [in K] = ', ARG
          VAMALE = .TRUE.
        ENDIF
      ELSE IF (INDEX .EQ. 3) THEN
        IF (ARG .LE. 0.) THEN
          PRINT '(A,G12.5)', ' Densità non positiva [in kg/m³] = ', ARG
          VAMALE = .TRUE.
        ENDIF
      ELSE IF (INDEX .EQ. 4) THEN
        HMIN = - CASPEG (igas) * 273.15
        IF (ARG .LE. HMIN) THEN
          PRINT '(A,G12.5)',
     $          ' Entalpia specifica non ammissibile [in J/kg] = ', ARG
          VAMALE = .TRUE.
        ENDIF
      ELSE
        PRINT '(A,I3)', ' Opzione errata in CHKGP = ', INDEX
        VAMALE = .TRUE.
      ENDIF
      IF (VAMALE) STOP 'Errore in validazione parametri'
      RETURN
      END
