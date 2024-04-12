      SUBROUTINE BRTTI3(IFO,IOB,DEBL) 
      PARAMETER (NN=11, NC=NN+1, NS=NC+2, NL=NS+2, NV=NL+2)
C
      CHARACTER*4 MOD, IOB, MOI, DEBL * 80
      CHARACTER NOME(NV)*4, TIPO(NV)*2, DESC(NV)*50
      DATA MOD/'BRTT'/
      DATA (NOME(I),TIPO(I),DESC(I),I=1,NV) /
     $   'WFUM','UA','FLUE GASES FLOW RATE AFTER BYPASS AIX MIXING',
     $   'TFUM','UA','FLUE GASES TEMPERATURE AFTER BYPASS AIX MIXING',
     $   'THOT','UA','FLUE GASES TEMPERATURE IN THE HOT CHAMBER',
     $   'XCOM','UA','FUEL/AIR MASS RATIO (FLUE GAS CHEM. COMP.)',
     $   'XH2O','UA','H2O/AIR MASS RATIO (FLUE GAS CHEM. COMP.)',
     $   'XXCH','UA','H/C MOLAR RATIO (FUEL MEAN CHEM. COMP.)',
     $   'ZMN2','UA','INERT MASS RATIO (FUEL MEAN CHEM. COMP.)',
     $   'WAIR','IN','AIR FLOW RATE AT COMBUSTION CHAMBER INLET',
     $   'TAIR','IN','AIR TEMPERATURE AT COMBUSTION CHAMBER INLET',
     $   'WBYP','IN','AIR FLOW RATE THROUGH THE CHAMBER BYPASS',
     $   'TBYP','IN','AIR TEMPERATURE THROUGH THE CHAMBER BYPASS',
     $   'WCO#','IN','FUEL # FLOW RATE AT COMBUSTION CHAMBER INLET',
     $   'TCO#','IN','FUEL # TEMPERATURE AT COMBUSTION CHAMBER INLET',
     $   'WSTE','IN','DENOX STEAM FLOW RATE AT CHAMBER INLET',
     $   'TSTE','IN','DENOX STEAM TEMPERATURE AT CHAMBER INLET',
     $   'WLIQ','IN','DENOX WATER FLOW RATE AT CHAMBER INLET',
     $   'TLIQ','IN','DENOX WATER TEMPERATURE AT CHAMBER INLET',
     $   'JFLA','IN','COMBUSTION CHAMBER IGNITION FLAG (1.=ON, 0.=OFF)'/
C
      CALL BRTTI4(MOD,MOI,NFUEL,NDENO)
      WRITE(IFO,2999)MOI,IOB,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOME(I),IOB,TIPO(I),DESC(I),I=1,NN)
C
      DO I = 1, NFUEL
        DO J = NC, NC+1
          NOME(J)(4:4) = CHAR(I+48)
          DESC(J)(6:6) = CHAR(I+48)
          WRITE(IFO,3000)NOME(J),IOB,TIPO(J),DESC(J)
        ENDDO
      ENDDO
      J = 0
      IF (NDENO .EQ. 1) J = NS
      IF (NDENO .EQ. 2) J = NL
      IF (J .NE. 0) WRITE(IFO,3000)(NOME(I),IOB,TIPO(I),DESC(I),I=J,J+1)
      WRITE(IFO,3000) NOME(NV),IOB,TIPO(NV),DESC(NV)
C
      RETURN
 2999 FORMAT(2A4,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE BRTTI4(MOD,MOI,NFUEL,NDENO)
      CHARACTER*4 MOD, MOI, ICA * 1
C
    1 WRITE(6,2)
      READ(5,3)ICA
      IF (ICA .EQ. ' ') THEN
        MOI = MOD
        NDENO = 0
      ELSE IF (ICA .EQ. '+') THEN
        MOI = ICA // MOD(1:3)
        NDENO = 1
      ELSE IF (ICA .EQ. '-') THEN
        MOI = ICA // MOD(1:3)
        NDENO = 2
      ELSE
        GOTO 1
      ENDIF
C
    4 WRITE(6,5)
      READ(5,*,ERR=4) NFUEL
      IF (NFUEL .LT. 1 .OR. NFUEL .GT. 9) GOTO 4
C
      RETURN
    2 FORMAT (/5X,'ASSIGN A CHARACTER TO SELECT DENOX INJECTION:',
     $        /5X,'- DRY LOW NOX (NO INJECTION) ======> BLANK',
     $        /5X,'- DENOX STEAM (STEAM INJECTION) ===>   +',
     $        /5X,'- DENOX WATER (WATER INJECTION) ===>   -')
    3 FORMAT (A)
    5 FORMAT (/5X,'NUMBER OF FUEL FLOWS (1-9) ?')
      END
C
C
C
      SUBROUTINE BRTTI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBL1,IBL2,IER,CNXYU,TOL)
C
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      CHARACTER ICA, MOI * 4
      DIMENSION HLV(9), ETA(9), CPC(9), XCH(9), XN2(9)
C
C---CAMERA DI COMBUSTIONE
C
      WRITE (MOI, 4) IBL1
      ICA = MOI(1:1)
    4 FORMAT (A4)
      IF (ICA .EQ. '+') THEN
        NDENO = 1
      ELSE IF (ICA .EQ. '-') THEN
        NDENO = 2
      ELSE
        NDENO = 0
      ENDIF
C
      NFUEL = (NINGRE - 5) / 2
      IF (NDENO .NE. 0) NFUEL = NFUEL - 1
C
      GO TO(100,200), IFUN
C
  100 DO I = 1, NFUEL
        WRITE(14,502) 'LHVcom',I,'ETAcom',I,'CPcomb',I,
     $                'XmolHC',I,'%inert',I
      ENDDO
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      DO I = 1, NFUEL
        READ(14,501) HLV(I), ETA(I), CPC(I), XCH(I), XN2(I)
      ENDDO
C
  502 FORMAT(3(4X,A6,I2,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      IF (ECOMB .LE. 0.) ECOMB = 1.
C
      DATI(ID2  ) = NDENO
      DATI(ID2+1) = NFUEL
      DATI(ID2+2) = 0.
      IDJ = ID2+3
      DO I = 1, NFUEL
        IF (ETA(I) .LE. 0.) ETA(I) = 1.
        DATI(IDJ  ) = HLV(I)
        DATI(IDJ+1) = ETA(I)
        DATI(IDJ+2) = CPC(I)
        DATI(IDJ+3) = XCH(I)
        DATI(IDJ+4) = XN2(I) / 100.
        IDJ = IDJ+5
      ENDDO
C
      ID2=IDJ
C
C---costanti di normalizzazione
C
      CNXYU(IV1  ) = W0
      CNXYU(IV1+1) = T0
      CNXYU(IV1+2) = T0
      CNXYU(IV1+3) = 1.
      CNXYU(IV1+4) = 1.
      CNXYU(IV1+5) = 1.
      CNXYU(IV1+6) = 1.
      DO I = IV1+7, IV2-2, 2
        CNXYU(I  ) = W0
        CNXYU(I+1) = T0
      ENDDO
      CNXYU(IV2) = 1.
C
      RETURN
      END
C
C
C
      SUBROUTINE BRTTC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,MX5),XYU(*),DATI(*),RNI(*)
C
      EXTERNAL BRTT
C
C---calcolo numero di uscite e di ingressi
C
      NDENO = NINT(DATI(IPD  ))
      NFUEL = NINT(DATI(IPD+1))
      NSTATI = 0
      NUSCIT = 7
      NINGRE = 5 + 2 * NFUEL
      IF (NDENO .NE. 0) NINGRE = NINGRE + 2
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano (escluso JFLA)
C
  100 DO I = 1, NSTATI + NUSCIT
        DO J = 1, NSTATI + NUSCIT + NINGRE - 1
          AJAC(I,J) = 1.
        ENDDO
      ENDDO
      RETURN
C
C---calcolo residui
C
  200 CALL BRTT(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 CALL BRTTNJ(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE)
      RETURN
      END
C
C
C
      SUBROUTINE BRTTNJ(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     $                  NSTATI,NUSCIT,NINGRE)
C
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
C
      EPS    = 1.E-3
      EPSLIM = 1.E-5
C
      NRIG=NSTATI+NUSCIT
      NCOL=NRIG+NINGRE
C
      CALL BRTT(3,IXYU,XYU,IPD,DATI,RN)
C
      EPSTEMP = 10./T0
      EPSPORT = 5./W0
C
      DO J = 1, NCOL
        IF (J.EQ.2 .OR. J.EQ.3 .OR. J.EQ.9 .OR. J.EQ.11) THEN
           VAR = EPSTEMP
        ELSE IF (J.EQ.1 .OR. J.EQ.8 .OR. J.EQ.10) THEN
           VAR = EPSPORT
        ELSE
          VAR = EPS * XYU(IXYU+J-1)
          IF (ABS(VAR) .LT. EPSLIM) VAR = EPSLIM
        ENDIF
C
        DO K = 1, NCOL
          CXYU(K) = XYU(IXYU+K-1)
          IF (K.EQ.J) CXYU(K) = CXYU(K) + VAR
        ENDDO
C
        CALL BRTT(3,1,CXYU,IPD,DATI,CRN)
C
        DO I = 1, NRIG
          AJAC(I,J) = (CRN(I)-RN(I))/VAR
          IF (I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
        ENDDO
C
      ENDDO
C
      RETURN
      END
C
C
C
      SUBROUTINE BRTT(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      PARAMETER (WMIN = 5., TRIF = 273.15)
      DIMENSION XYU(*),DATI(*),RNI(*),XCFU(2),RFUM(2),ROUT(2),
     $          WCO(9),TCO(9),COE(9)
      LOGICAL KREGIM,JFIR,JFLOLOG
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C---decodifica variabili e dati
C
      NDENO = NINT(DATI(IPD  ))
      NFUEL = NINT(DATI(IPD+1))
C
      WFUM = XYU(IXYU   ) * W0
      TFUM = XYU(IXYU+ 1) * T0
      THOT = XYU(IXYU+ 2) * T0
      XCOM = XYU(IXYU+ 3)
      XH2O = XYU(IXYU+ 4)
      XXHC = XYU(IXYU+ 5)
      ZMN2 = XYU(IXYU+ 6)
      WAIR = XYU(IXYU+ 7) * W0
      TAIR = XYU(IXYU+ 8) * T0
      WBYP = XYU(IXYU+ 9) * W0
      TBYP = XYU(IXYU+10) * T0
C
      IXYJ = IXYU+11
      DO I = 1, NFUEL
        WCO(I) = XYU(IXYJ  ) * W0
        TCO(I) = XYU(IXYJ+1) * T0
        IXYJ = IXYJ+2
      ENDDO
C
      IF (NDENO .EQ. 0) THEN
        WH2O = 0.
        TH2O = TRIF
      ELSE
        WH2O = XYU(IXYJ  ) * W0
        TH2O = XYU(IXYJ+1) * T0
        IXYJ = IXYJ+2
      ENDIF
C
      JFIR = JFLOLOG(XYU(IXYJ))
C
C---memoria portata aria per scelta forma residuo
C
      IF (IFUN .EQ. 2 .AND. ITERT .LE. 0) DATI(IPD+2) = WAIR
      WPRE = DATI(IPD+2)
C
C---calcolo composizione chimica media del combustibile
C
      WCLI = 0.
      DO I = 1, NFUEL
        COE(I) = AMAX1 (WCO(I), 0.)
        IF (COE(I) .LT. 0.001) COE(I) = 0.
        WCLI = WCLI + COE(I)
      ENDDO
C
      IF (WCLI .EQ. 0.) THEN
        COE(1) = 1.
        DO I = 2, NFUEL
          COE(I) = 0.
        ENDDO
      ELSE
        DO I = 1, NFUEL
          COE(I) = COE(I) / WCLI
        ENDDO
      ENDIF
C
      HLV = 0.
      ETA = 0.
      CPC = 0.
      XCH = 0.
      XN2 = 0.
C
      IDJ = IPD+3
      DO I = 1, NFUEL
        HLV = HLV + COE(I) * DATI(IDJ  )
        ETA = ETA + COE(I) * DATI(IDJ+1)
        CPC = CPC + COE(I) * DATI(IDJ+2)
        XCH = XCH + COE(I) * DATI(IDJ+3)
        XN2 = XN2 + COE(I) * DATI(IDJ+4)
        IDJ = IDJ+5
      ENDDO
C
C---calcolo portata di combustibile
C
      WCOM = 0.
      TCOM = 0.
      DO I = 1, NFUEL
        WCOM = WCOM + WCO(I)
        TCOM = TCOM + TCO(I) * COE(I)
      ENDDO
C
C---test accensione fuochi e composizione fumi
C
      WBRU = AMAX1 (WCOM, 0.)
      IF (.NOT. JFIR) WBRU = 0.
C
      XCFU(1) = XCH
      XCFU(2) = XN2
C
      WALI = AMAX1 (WAIR, WMIN)
      WHLI = AMAX1 (WH2O, 0.)
      WBLI = AMAX1 (WBYP, 0.)
      RFUM(1) = WBRU / WALI
      RFUM(2) = WHLI / WALI
      ROUT(1) = WBRU / (WALI + WBLI)
      ROUT(2) = WHLI / (WALI + WBLI)
C
C---residuo 1 (portata di fumi)
C
      RNI(1) = (WFUM - WAIR - WBYP - WCOM - WH2O) / W0
C
C---residui 2 e 3 (temperatura dei fumi)
C
      CALL INITAF (3, 0., 0.)
      CALL THINAF (TAIR, HAIR, 1, 3)
      CALL THINAF (TBYP, HBYP, 1, 3)
      QCOM = WCOM * CPC * (TCOM - TRIF)
      QBRU = WBRU * HLV * ETA
      QH2O = WH2O * BRTTHS (TH2O, NDENO)
      QAIR = WAIR * HAIR
      QBYP = WBYP * HBYP
C
C---differenziati a seconda della portata d'aria
C
      IF (WPRE .LE. WMIN) THEN
        QMIN = WMIN * HAIR
        HHC = (QMIN + QCOM + QBRU + QH2O) / (WMIN + WCOM + WH2O)
        HFC = (QMIN + QCOM + QBRU + QH2O + QBYP) /
     $        (WMIN + WCOM + WH2O + WBYP)
        CALL INITAF (4, XCFU, RFUM)
        CALL THINAF (THC, HHC, 2, 4)
        CALL INITAF (4, XCFU, ROUT)
        CALL THINAF (TFC, HFC, 2, 4)
        RNI(2) = (TFUM - TFC) / T0
        RNI(3) = (THOT - THC) / T0
      ELSE
        CALL INITAF (4, XCFU, RFUM)
        CALL THINAF (THOT, HHOT, 1, 4)
        CALL INITAF (4, XCFU, ROUT)
        CALL THINAF (TFUM, HFUM, 1, 4)
        QHOT = (WFUM - WBYP) * HHOT
        QFUM = WFUM * HFUM
        RNI(2) = (QFUM - QAIR - QBRU - QCOM - QH2O - QBYP) / (H0*W0)
        RNI(3) = (QHOT - QAIR - QBRU - QCOM - QH2O) / (H0*W0)
      ENDIF
C
C---residui 4, 5, 6 e 7 (comp. chimica dei fumi)
C
      RNI(4) = (XCOM - ROUT(1)) * 10.
      RNI(5) = (XH2O - ROUT(2)) * 10.
      RNI(6) = (XXHC - XCFU(1)) / 10.
      RNI(7) = ZMN2 - XCFU(2) * 100.
C
      RETURN
      END
C
C
C
      FUNCTION BRTTHS (T, I)
      PARAMETER (TRIF = 273.15)
      DATA A, B, C / 1613.4, -46.6E-3, 111.7E-6 /
      DATA TC, HZ, ESP / 374.15, 2.502e6, 0.333333333 /
C
      TD = T - TRIF
      HS = A * TD + B * TD ** 2 / 2. + C * TD ** 3 / 6.
      HR = 0.
      IF (TD .LT. TC) HR = HZ * (1. - TD / TC) ** ESP
C
      IF (I .EQ. 1) THEN
        BRTTHS = HS
      ELSE IF (I .EQ. 2) THEN
        BRTTHS = HS - HR
      ELSE
        BRTTHS = 0.
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE BRTTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $    XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
