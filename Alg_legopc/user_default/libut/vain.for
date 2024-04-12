      SUBROUTINE VAINI3(IFO,IOB,DEBL)
C
      PARAMETER (NV = 8)
      CHARACTER*4 MOD,IOB,IBLOC*8,DEBL*80
      CHARACTER*4 NOME(NV),DESC(NV)*50
C
      DATA MOD/'VAIN'/
      DATA (NOME(I),DESC(I),I=1,NV) /
     $ 'WVAL','GAS FLOW RATE THROUGH THE VALVE',
     $ 'TVAL','GAS TEMPERATURE AT VALVE OUTLET',
     $ 'TMI ','GAS TEMP. AT VALVE INLET (INV. FLOW)',
     $ 'PMON','GAS PRESSURE AT VALVE INLET',
     $ 'PVAL','GAS PRESSURE AT VALVE OUTLET',
     $ 'TMON','GAS TEMPERATURE AT VALVE INLET',
     $ 'TVI ','GAS TEMP. AT VALVE OUTLET (INV. FLOW)',
     $ 'ALZV','GAS VALVE LIFT'/
C
      CALL VAINI4(IOB,MOD,IBLOC,I,J,K)
      WRITE (IFO,2999) IBLOC,IOB,MOD,DEBL
      WRITE (IFO,3000) NOME(I),IOB,'UA',DESC(I),
     $                 NOME(2),IOB,'UA',DESC(2),
     $                 NOME(3),IOB,'UA',DESC(3),
     $                 NOME(J),IOB,'IN',DESC(J),
     $                 NOME(K),IOB,'IN',DESC(K),
     $                 NOME(6),IOB,'IN',DESC(6),
     $                 NOME(7),IOB,'IN',DESC(7),
     $                 NOME(8),IOB,'IN',DESC(8)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE VAINI4(IOB,MOD,IBLOC,I1,I4,I5)
      CHARACTER*4 MOD,IOB,IBLOC*8,ICA*1
C
    1 WRITE(6,2)
      READ(5,3)ICA
      IF (ICA .EQ. ' ') THEN
        IBLOC = MOD // IOB
        I1 = 1
        I4 = 4
        I5 = 5
      ELSE IF (ICA .EQ. '+') THEN
        IBLOC = ICA // MOD(1:3) // IOB
        I1 = 4
        I4 = 1
        I5 = 5
      ELSE IF (ICA .EQ. '-') THEN
        IBLOC = ICA // MOD(1:3) // IOB
        I1 = 5
        I4 = 1
        I5 = 4
      ELSE
        GOTO 1
      ENDIF
      RETURN
    2 FORMAT (/5X,'ASSIGN A CHARACTER TO SELECT VALVE OUTPUT:',
     $        /5X,'- OUTPUT IN GAS FLOW RATE =====> BLANK',
     $        /5X,'- OUTPUT IN INLET PRESSURE ====>   +',
     $        /5X,'- OUTPUT IN OUTLET PRESSURE ===>   -')
    3 FORMAT (A)
      END
C
C
C
      SUBROUTINE VAINI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBL1,IBL2,IER,CNXYU,TOL)
C
      INTEGER VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
      CHARACTER ICA,IBLOC*8
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
C---VALV.GAS CON INV.PORTATA O CLAPET
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500)'CV      ','PMONOM  ','PVANOM  ','ALZNOM  ',
     $             'XWNOM   ','XKTEMP  ','CLAPET  ',
     $             'ALFA    ','TMONOM  ','IGAS    '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) CCV,PMONOM,PVANOM,ALZNOM,XWNOM,XKTEMP,
     $             CLAP,ALFA,TMONOM,GAS
      IF (ALFA .LE. 0.) ALFA = 1.
C
C--per default si assume il fluido come aria 
C
      IGAS = NINT(GAS)
      IF (IGAS .LE. 0) IGAS = 1
      CLAP = ANINT(CLAP)
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      CALL TAVOGP(101325.,273.15,R10,H10,S10,IGAS)
      RAPP = R10 / 3600.
      CALL R1CPGP(R1,CP,CV,IGAS)
      XK1 = CP / CV
      RC = (2. / (XK1 + 1.)) ** (XK1 / (XK1 - 1.))
C      
      IF(CCV.GT.0.) THEN
         CVMAX=CCV*2.4E-5
         WEPS=1.E-3
      ELSE
         WNOM = XWNOM * RAPP
         WEPS = WNOM * 1.E-3 
         CALL TAVOGP(PMONOM,TMONOM,RMONOM,HMONOM,SMONOM,IGAS)
         DPNOM = PMONOM - AMAX1 (PVANOM, RC*PMONOM)
         CVMAX = SQRT (WNOM * (WNOM + WEPS) / (RMONOM * DPNOM)) /
     $           ALZNOM**ALFA
         CCV=CVMAX*1.E5/2.4
      ENDIF
      WRITE (6,10) CCV
   10 FORMAT (/10X,'GAS VALVE  CV  = ',G12.5)
C
C---selezione uscita e costanti di normalizzazione
C
      CNXYU(IV1+1) = T0
      CNXYU(IV1+2) = T0
      CNXYU(IV1+5) = T0
      CNXYU(IV1+6) = T0
      CNXYU(IV1+7) = 1.
C
      WRITE (IBLOC,11) IBL1,IBL2
   11 FORMAT (2A4)
      ICA = IBLOC(1:1)
      IF (ICA .EQ. '+') THEN
        IWP = 1
        CNXYU(IV1  ) = P0
        CNXYU(IV1+3) = W0
        CNXYU(IV1+4) = P0
      ELSE IF (ICA .EQ. '-') THEN
        IWP = 2
        CNXYU(IV1  ) = P0
        CNXYU(IV1+3) = W0
        CNXYU(IV1+4) = P0
      ELSE
        IWP = 0
        CNXYU(IV1  ) = W0
        CNXYU(IV1+3) = P0
        CNXYU(IV1+4) = P0
      ENDIF
C
      DATI(ID2  ) = CVMAX
      DATI(ID2+1) = ALFA
      DATI(ID2+2) = CLAP
      DATI(ID2+3) = XKTEMP
      DATI(ID2+4) = 1.
      DATI(ID2+5) = IGAS
      DATI(ID2+6) = IWP
      DATI(ID2+7) = RC
      DATI(ID2+8) = WEPS
      ID2 = ID2+8
C
      RETURN
      END
C
C
C
      SUBROUTINE VAINC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      COMMON/VAIN10/IBLOC1,IBLOC2
      EXTERNAL VAIN
C
      IBLOC1 = IBL1
      IBLOC2 = IBL2
C
C---VALV.GAS CON INV.PORTATA O CLAPET
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 DO I = 1, 3
        DO J = 1, 8
          AJAC(I,J) = 1.
        ENDDO
      ENDDO
      RETURN
C
C---calcolo residui
C
  200 CALL VAIN(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 NSTATI = 0
      NUSCIT = 3
      NINGRE = 5
      EPS    = 1.E-3
      EPSLIM = 1.E-5
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,VAIN)
      RETURN
C
      END
C
C
C
      SUBROUTINE VAIN(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
      COMMON/VAIN10/IBLOC1,IBLOC2
C
C---valv. gas con inv. portata o clapet
C
C---decodifica dati e variabili
C
      CVMAX  = DATI(IPD  )
      ALFA   = DATI(IPD+1)
      CLAP   = DATI(IPD+2)
      XKTEMP = DATI(IPD+3)
      XCLAP  = DATI(IPD+4)
      IGAS   = DATI(IPD+5)
      IWP    = DATI(IPD+6)
      RC     = DATI(IPD+7)
      WEPS   = DATI(IPD+8)
C
      TVAL = XYU(IXYU+1) * T0
      TMOI = XYU(IXYU+2) * T0
      TMON = XYU(IXYU+5) * T0
      TVAI = XYU(IXYU+6) * T0
      ALZV = XYU(IXYU+7) * 1.
      IF (IWP .EQ. 1) THEN
        PMON = XYU(IXYU  ) * P0
        WVAL = XYU(IXYU+3) * W0
        PVAL = XYU(IXYU+4) * P0
      ELSE IF (IWP .EQ. 2) THEN
        PVAL = XYU(IXYU  ) * P0
        WVAL = XYU(IXYU+3) * W0
        PMON = XYU(IXYU+4) * P0
      ELSE
        WVAL = XYU(IXYU  ) * W0
        PMON = XYU(IXYU+3) * P0
        PVAL = XYU(IXYU+4) * P0
      ENDIF
      IF (PVAL .LT. 500.) PVAL = 500.
      IF (PMON .LT. 500.) PMON = 500.
C
C---test sull'alzata valvola
C
      IF (ALZV .GT. 1. .OR. ALZV .LT. 0.) THEN
        IF (KREGIM .AND. IFUN .EQ. 2) THEN
          WRITE (6,1) IBLOC1, IBLOC2, ALZV
    1     FORMAT(' WARNING: THE LIFT OF THE VALVE ',2A4,' IS ',G12.5)
        ELSE
          IF (ALZV .GT. 1.) ALZV = 1.
          IF (ALZV .LT. 0.) ALZV = 0.
        ENDIF
      ENDIF
C
C---significato di XCLAP: 2. = flusso normale (alzata < 0.15)
C                         1. = flusso normale (alzata >= 0.15)
C                         0. = flusso intercettato (clapet o alz. nulla)
C                        -1. = flusso invertito (no clapet, alz. >= 0.15)
C                        -2. = flusso invertito (no clapet, alz. < 0.15)
C
      IF (IFUN .EQ. 2 .AND. ITERT .LE. 0) THEN
        IF (CLAP .EQ. 1. .AND. PMON .LT. PVAL .OR. ALZV .LT. 1.E-4) THEN
          XCLAP = 0.
        ELSE IF (PMON .LT. PVAL) THEN
          XCLAP = -1.
        ELSE
          XCLAP = 1.
        ENDIF
        IF (ALZV .LT. 0.15) XCLAP = 2. * XCLAP
        DATI(IPD+4) = XCLAP
      ENDIF
C
      IF (XCLAP .EQ. 0.) THEN
        TVAX = TMON
        TMIX = TVAI
      ELSE IF (XCLAP .LT. 0.) THEN
        TVAX = TMON
        TMIX = TVAI - XKTEMP * (PVAL - PMON) / TVAI ** 2
        PMON = AMAX1 (PMON, PVAL*RC)
        CALL TAVOGP(PVAL,TVAI,RING,HDUM,SDUM,IGAS)
      ELSE
        TVAX = TMON - XKTEMP * (PMON - PVAL) / TMON ** 2
        TMIX = TVAI
        PVAL = AMAX1 (PVAL, PMON*RC)
        CALL TAVOGP(PMON,TMON,RING,HDUM,SDUM,IGAS)
      ENDIF
      IF (XCLAP .NE. 0.) ROCC = RING * (CVMAX * ALZV ** ALFA) ** 2
C
      IF (XCLAP .EQ. 0.) THEN
        RNI(1) = WVAL / W0
      ELSE IF (ABS(XCLAP) .EQ. 1.) THEN
        RNI(1) = (PMON - PVAL - WVAL * (ABS(WVAL) + WEPS) / ROCC) / P0
      ELSE
        RNI(1) = (WVAL - (PMON - PVAL) * ROCC / (ABS(WVAL) + WEPS)) / W0
      ENDIF
C
      RNI(2) = (TVAL - TVAX) / T0
      RNI(3) = (TMOI - TMIX) / T0
C
      RETURN
      END
C
C
C
      SUBROUTINE VAIND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $   XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C
C     IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 IBLOC, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
      Q0 = H0*W0
C
      XCLAP = DATI(IPD+4)
 
C-----Equazione n. 1 (Algebrica):
C
       SIGNEQ(1) = 'eq. of fluid flow trough the valve'
        IF(ABS(XCLAP).EQ.1)THEN
         UNITEQ(1) = '[Pa]'
         COSNOR(1) = P0
        ELSE
         UNITEQ(1) = '[kg/s]'
         COSNOR(1) = W0
        ENDIF
        ITOPVA(1,1) = 1
        DO I=4,8
         ITOPVA(1,I) = 1
        ENDDO
C
C-----Equazione n.2 (Algebrica)
C
      SIGNEQ(2) = 'computation of outlet gas temperature in normal flow'
      UNITEQ(2) = '[K]'
      COSNOR(2) = T0
      ITOPVA(2,2) = 1
      ITOPVA(2,6) = 1

C-----Equazione n.3 (Algebrica)
C
      SIGNEQ(3) = 'comput. of outlet gas temperature in inverted flow'
      UNITEQ(3) = '[K]'
      COSNOR(3) = T0
      ITOPVA(3,3) = 1
      ITOPVA(3,7) = 1
C
      RETURN
      END
