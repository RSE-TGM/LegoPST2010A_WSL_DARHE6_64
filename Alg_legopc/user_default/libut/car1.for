C***********************************************************************
C
C     Modello carico statico
C     Ultima modifica:  30.03.98
C
C***********************************************************************
C
      SUBROUTINE CAR1I2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2), IBASE
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      REAL IR00, IX00, IM00                                             !SNGL
C      DOUBLE PRECISION IR00, IX00, IM00                                 !DBLE
C
C---CARICO SEZIONABILE AD AMMETTENZA VARIABILE
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'Pnom_W  '
     $             ,'Qnom_VAR'
     $             ,'Vnom_V  '
     $             ,'PU?_1=SI'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) PNOM
     $            ,QNOM
     $            ,VNOM
     $            ,PU
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      QBASE=W0*H0
      YBASE=VNOM**2/QBASE
      GNOM=YBASE*PNOM/VNOM**2
      BNOM=-YBASE*QNOM/VNOM**2
C
      DATI(ID2   ) = GNOM
      DATI(ID2+ 1) = BNOM
      DATI(ID2+ 2) = VNOM
      DATI(ID2+ 3) = PU
      ID2 = ID2+3
C
C---costanti di normalizzazione
C
      IF (PU.EQ.1.) THEN
        DO J=1,12
          CNXYU(IV1+J-1)=1.
        END DO
      ELSE
        IBASE=QBASE/(SQRT(3.)*VNOM)
C
        CNXYU(IV1   ) = IBASE
        CNXYU(IV1+ 1) = IBASE
        CNXYU(IV1+ 2) = QBASE               !NON EQUAZIONI
        CNXYU(IV1+ 3) = QBASE
        CNXYU(IV1+ 4) = IBASE
        CNXYU(IV1+ 5) = VNOM
        CNXYU(IV1+ 6) = 1.
        CNXYU(IV1+ 7) = VNOM
        CNXYU(IV1+ 8) = VNOM
        CNXYU(IV1+ 9) = 1.
        CNXYU(IV1+10) = 1.
        CNXYU(IV1+11) = 1.
      END IF
C
      RETURN
      END
C
C
C
      SUBROUTINE CAR1C1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/NEQUAZ/NEQMOD
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL CAR1
C
      REAL IR00, IX00, IM00, III                                             !SNGL
C      DOUBLE PRECISION IR00, IX00, IM00                                 !DBLE
C
C---CARICO SEZIONABILE AD AMMETTENZA VARIABILE 
C
      GNOM   = DATI(IPD   )
      BNOM   = DATI(IPD+ 1)
      VNOM   = DATI(IPD+ 2)
      PU     = DATI(IPD+ 3)
C
      NEQMOD = 2
C
      GO TO(100,200,300),IFUN
C
  100 CONTINUE
C
C---topologia jacobiano 
C
C
      CALL CAR1JC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL CAR1 (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 CONTINUE
      CALL CAR1JC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE CAR1JC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL CAR1
C
      REAL IR00, IX00, IM00                                             !SNGL
C      DOUBLE PRECISION IR00, IX00, IM00                                 !DBLE
C
      NEQ    = 2
      IF(KREGIM) NEQ = 7
C
      NVAR = 12
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
      DO J=1,2
        DO I=1,NVAR
        IF(I.LT.3.OR.I.GT.7) THEN
         AJAC(J,I)=1.
        ENDIF
        END DO 
      END DO
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      EPS    = 1.E-3
      EPSLIM = 1.E-4
C
      CALL CAR1JAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $             NEQ,NVAR,NSTATI,EPS,EPSLIM,CAR1)
C
      RETURN
      END
C
C
C
      SUBROUTINE CAR1JAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     $               NRIG,NCOL,NSTATI,EPS,EPSLIM,RESIDUI)
C
C     routine di calcolo jacobiano numerico
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      EXTERNAL RESIDUI
C
      CALL RESIDUI(3,IXYU,XYU,IPD,DATI,RN)
C
      DO 30 J=1,NCOL
C*
      IF(KREGIM.OR.J.LT.3.OR.J.GT.7) THEN
C*
      VAR=EPS*XYU(IXYU+J-1)
      IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C
      DO 10 K=1,NCOL
      CXYU(K)=XYU(IXYU+K-1)
      IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
   10      CONTINUE
C
C
      CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
C
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(CRN(I)-RN(I))/VAR
      IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
   20      CONTINUE
C
      ENDIF
   30      CONTINUE
C
      RETURN
      END
C
C
C
      SUBROUTINE CAR1 (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/NEQUAZ/NEQMOD
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL IR00, IX00, IM00                                             !SNGL
      DOUBLE PRECISION QAPP                                             !DBLE
C
C---CARICO SEZIONABILE AD AMMETTENZA VARIABILE 
C   calcolo residui
C
C---decodifica variabili e dati
C
C
      GNOM   = DATI(IPD   )
      BNOM   = DATI(IPD+ 1)
      VNOM   = DATI(IPD+ 2)
      PU     = DATI(IPD+ 3)
C
      IR00   = XYU(IXYU   )
      IX00   = XYU(IXYU+ 1)
      QATT   = XYU(IXYU+ 2)
      QREA   = XYU(IXYU+ 3)
      IM00   = XYU(IXYU+ 4)
      VM00   = XYU(IXYU+ 5)
      FDIP   = XYU(IXYU+ 6)
      VR00   = XYU(IXYU+ 7)
      VX00   = XYU(IXYU+ 8)
      FG00   = XYU(IXYU+ 9)
      FB00   = XYU(IXYU+ 10)
      SISC   = JFLOLOG(XYU(IXYU+11))
C
C---calcolo residui
C
      IF (SISC) THEN
C
C--------------Interruttore chiuso (SISC=1)
C
      RNI(1) = IR00+VR00*FG00*GNOM-VX00*FB00*BNOM
C
      RNI(2) = IX00+VX00*FG00*GNOM+VR00*FB00*BNOM
C
C             A REGIME
C
         IF(KREGIM)THEN
c
            RNI(3) = -QATT+VR00*IR00+VX00*IX00
C
            RNI(4) = -QREA+VX00*IR00-VR00*IX00
C
            RNI(5) = -IM00+SQRT(IR00*IR00+IX00*IX00)
C
            RNI(6) = -VM00+SQRT(VR00*VR00+VX00*VX00)
C
            QAPP =SQRT(QATT*QATT+QREA*QREA) 
            IF (QAPP.GT.0.00000001) THEN
            FDP0 = abs(QATT)/QAPP
            ELSE
            FDP0 = 0.
            END IF
C
            RNI(7) = -FDIP+FDP0
C
         ELSE 
C
C           DURANTE I TRANSITORI
C
            RNI(3) = VR00*IR00+VX00*IX00
C
            RNI(4) = VX00*IR00-VR00*IX00
C
            RNI(5) = SQRT(IR00*IR00+IX00*IX00)
C
            RNI(6) = SQRT(VR00*VR00+VX00*VX00)
C
            QAPP =SQRT(QATT*QATT+QREA*QREA) 
            IF (QAPP.GT.0.00000001) THEN
            FDP0 = abs(QATT)/QAPP
            ELSE
            FDP0 = 0.
            END IF
C
            RNI(7) = FDP0
C
	 END IF
C
      ELSE
C
C--------------Interruttore aperto (SISC=0)
C
        RNI(1) =IR00
        RNI(2) =IX00
        IF(KREGIM) THEN
            RNI(3) =QATT
            RNI(4) =QREA
            RNI(5) =IM00
            RNI(6) =-VM00+SQRT(VR00*VR00+VX00*VX00)
            RNI(7) =FDIP
         ELSE
            RNI(3) =0.
            RNI(4) =0.
            RNI(5) =0.
            RNI(6) =SQRT(VR00*VR00+VX00*VX00)
            RNI(7) =0.        
         ENDIF
C

      END IF
C
      RETURN
      END
C
C
C
      SUBROUTINE CAR1I3 (IFO,IOB,DEBL)
C
      COMMON/CAR101/IBLOC
      COMMON/CAR102/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'CAR1'/
C
      CALL CAR1I4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 7
      NINGRE = 5
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('IR00',A4,2X,
     $  57H--UA-- CORRENTE REALE DI CARICO [A]                      )
      WRITE(IFO,3002)IOB
 3002 FORMAT('IX00',A4,2X,
     $  57H--UA-- CORRENTE IMMAG. DI CARICO [A]                     )
      WRITE(IFO,3003)IOB
 3003 FORMAT('QATT',A4,2X,
     $  57H--UA-- POTENZA ATTIVA DI CARICO [W]                      )
      WRITE(IFO,3004)IOB
 3004 FORMAT('QREA',A4,2X,
     $  57H--UA-- POTENZA REATTIVA DI CARICO [W]                    )
      WRITE(IFO,3005)IOB
 3005 FORMAT('IM00',A4,2X,
     $  57H--UA-- MODULO CORRENTE DI CARICO [A]                     )
      WRITE(IFO,3006)IOB
 3006 FORMAT('VM00',A4,2X,
     $  57H--UA-- MODULO TENSIONE DI CARICO [V]                     )
      WRITE(IFO,3007)IOB
 3007 FORMAT('FDIP',A4,2X,
     $  57H--UA-- FATTORE DI POTENZA DEL CARICO                     )
      WRITE(IFO,3008)IOB
 3008 FORMAT('VR00',A4,2X,
     $  57H--IN-- TENSIONE REALE DEL CARICO [V]                     )
      WRITE(IFO,3009)IOB
 3009 FORMAT('VX00',A4,2X,
     $  57H--IN-- TENSIONE IMMAG. DEL CARICO [V]                    )
      WRITE(IFO,3010)IOB
 3010 FORMAT('FG00',A4,2X,
     $  57H--IN-- MOLTIPLICATORE DI CONDUTTANZA                     )
      WRITE(IFO,3011)IOB
 3011 FORMAT('FB00',A4,2X,
     $  57H--IN-- MOLTIPLICATORE DI SUSCETTANZA                     )
      WRITE(IFO,3012)IOB
 3012 FORMAT('SISC',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE CARICO (1=on)                  )
      RETURN
      END
C
C
C
      SUBROUTINE CAR1I4 (IOB,MOD)
      COMMON/CAR101/IBLOC
      COMMON/CAR102/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE CAR1D1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---CARICO SEZIONABILE AD AMMETTENZA VARIABILE 
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
