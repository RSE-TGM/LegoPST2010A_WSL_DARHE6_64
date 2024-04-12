C*****************************************************************************
C     Modulo BCN0
C     -----------
C     Creato     il 18.01.01 a partire del modullo CNDN
C     Modificato il 17.07.95 per introduzione CORR 
C     Modificato il 19.10.99 per eliminazione errori (March./Miglia./Spelta)
C     Modificato il 18.01.01 Modulo CNDN trasformato per un modello di 
C                            dissalatore: uso delle tavole di acqua salata per
C                            il fluido dentro il fascio tubiero 
C     Modificato il 22.01.01 Aggiunta equazione momento fascio tubiero
C                            Introduzione della scelta di topologia delle
C                            variabili del fascio tubiero
C     Modificato il 24.01.01 per introduzione di HVCN, entalpia del vapore
C                            per introduzione di Fr.NaCl per il calcolo del
C                                coefficiente di perdita di carico 
C
C*****************************************************************************
      SUBROUTINE BCN0I3 (IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/BCN000/IBLOC
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER*4 NOMAPP
      DATA MOD/'BCN0'/
      CALL BCN0I4(IOB,MOD)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A,'- **** MODULO ',A,' - ',A)
      NSTATI =   2
      NUSCIT =   7
      NINGRE =  17
C
      WRITE(NOMAPP,'(A1)')IBLOC
      WP=0.
      IF(NOMAPP(1:1).EQ.'+')WP=1.
      IF(NOMAPP(1:1).EQ.'-')WP=2.
C
      WRITE(IFO,3000)IOB
      WRITE(IFO,3001)IOB
      WRITE(IFO,3002)IOB
      WRITE(IFO,3003)IOB
      WRITE(IFO,3004)IOB
      WRITE(IFO,3029)IOB
      WRITE(IFO,3019)IOB
      WRITE(IFO,3020)IOB
      IF(WP.EQ.0.)WRITE(IFO,3022)IOB
      IF(WP.EQ.1.)WRITE(IFO,3023)IOB
      IF(WP.EQ.2.)WRITE(IFO,3024)IOB
      WRITE(IFO,3005)IOB
      WRITE(IFO,3006)IOB
      WRITE(IFO,3007)IOB
      WRITE(IFO,3008)IOB
      WRITE(IFO,3009)IOB
      WRITE(IFO,3010)IOB
      WRITE(IFO,3011)IOB
      WRITE(IFO,3012)IOB
      WRITE(IFO,3013)IOB
      WRITE(IFO,3014)IOB
      WRITE(IFO,3015)IOB
      IF(WP.EQ.0.)THEN
         WRITE(IFO,3026)IOB
         WRITE(IFO,3027)IOB
      ELSE IF(WP.EQ.1.)THEN
         WRITE(IFO,3025)IOB
         WRITE(IFO,3027)IOB
      ELSE IF(WP.EQ.2.)THEN
         WRITE(IFO,3025)IOB
         WRITE(IFO,3026)IOB
      ENDIF   
      WRITE(IFO,3017)IOB
      WRITE(IFO,3018)IOB
      WRITE(IFO,3021)IOB
      WRITE(IFO,3028)IOB
C      
 3000 FORMAT('PCND',A4,2X,'--US-- STEAM PRESSURE IN THE CONDENSER')
 3001 FORMAT('LCND',A4,2X,'--US-- LEVEL OF LIQUID IN THE CONDENSER')
 3002 FORMAT('TMFT',A4,2X,
     $  '--UA-- MEAN TEMPERATURE OF METAL AT TUBE BUNDLE OUTLET')
 3003 FORMAT('HUFT',A4,2X,
     $  '--UA-- COOLER ENTHALPY AT THE TUBE BUNDLE OUTLET')
 3004 FORMAT('HLCN',A4,2X,'--UA-- ENTHALPY OF THE CONDENSATE LIQUID')
 3029 FORMAT('HVCN',A4,2X,'--UA-- ENTHALPY OF THE SATURATE STEAM')
 3019 FORMAT('PFCN',A4,2X,'--UA-- PRESSURE IN THE CONDENSER BOTTOM')
 3020 FORMAT('%LCN',A4,2X,'--UA-- MEASURED LIQUID LEVEL')
 3022 FORMAT('WRFT',A4,2X,'--UA-- COOLING BRINE FLOW RATE')
 3023 FORMAT('PMON',A4,2X,'--UA-- COOLING BRINE UPSTREAM PRESSURE')
 3024 FORMAT('PVAL',A4,2X,'--UA-- COOLING BRINE DOWNSTREAM PRESSURE')
 3005 FORMAT('WTUR',A4,2X,
     $  '--IN-- FLOW RATE OF MAIN TURBINE BLOW-OFF STEAM')
 3006 FORMAT('HTUR',A4,2X,
     $  '--IN-- ENTHALPY OF MAIN TURBINE BLOW-OFF STEAM')
 3007 FORMAT('WEXT',A4,2X,
     $  '--IN-- FLOW RATE OF STEAM FROM SECONDARY CONDENSER INLET')
 3008 FORMAT('HEXT',A4,2X,
     $  '--IN-- ENTHALPY OF STEAM AT SECONDARY CONDENSER INLET')
 3009 FORMAT('WLCP',A4,2X,'--IN-- CONDENSATE EXTRACTION FLOW RATE')
 3010 FORMAT('WDRE',A4,2X,
     $  '--IN-- DRAINS FLOW RATE AT THE CONDENSER INLET')
 3011 FORMAT('HDRE',A4,2X,
     $  '--IN-- DRAINS ENTHALPY AT THE CONDENSER INLET')
 3012 FORMAT('WLCX',A4,2X,
     $  '--IN-- LEVEL CONTROL EXTRACTED (SUPPL.) LIQUID FLOW RATE')
 3013 FORMAT('WVCN',A4,2X,
     $  '--IN-- FLOW RATE OF STEAM EXTRACTED FOR CONDENSER VACUUM')
 3014 FORMAT('WRIC',A4,2X,
     $  '--IN-- FLOW RATE OF LIQUID RECIRCULATED BY EXTR. PUMPS')
 3015 FORMAT('HRIC',A4,2X,
     $  '--IN-- ENTHALPY OF LIQUID RECIRCULATED BY EXTR. PUMPS')
 3025 FORMAT('WRFT',A4,2X,'--IN-- COOLING BRINE FLOW RATE')
 3026 FORMAT('PMON',A4,2X,'--IN-- COOLING BRINE UPSTREAM PRESSURE')
 3027 FORMAT('PVAL',A4,2X,'--IN-- COOLING BRINE DOWNSTREAM PRESSURE')
 3017 FORMAT('HIFT',A4,2X,
     $  '--IN-- COOLING BRINE ENTHALPY AT THE TUBE BUNDLE INLET')
 3018 FORMAT('CORR',A4,2X,
     $  '--IN-- THERMAL EXCHANGE CORRECTION COEFFICIENT')
 3021 FORMAT('FNAC',A4,2X,'--IN-- NACL MASS FRACTION IN BRINE')
 3028 FORMAT('AKTB',A4,2X,
     $  '--IN-- CORRECTION COEFF. FOR COOLING BRINE HEAD LOSS')
C
      RETURN
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0I4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
      COMMON/BCN000/IBLOC
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MODU
      CHARACTER*1 ICA,IMEN,IPIU
      CHARACTER*1 IBL
      CHARACTER*4 MOD
      DATA IBL/' '/
      DATA IPIU/'+'/
      DATA IMEN/'-'/
C
    2 WRITE(6,2999)
 2999 FORMAT(//10X,'GIVE A CHARACTER FOR COOLING BRINE TOPOLOGY'
     $ /5X,' - FLOW RATE AS OUTPUT =========> BLANK'
     $ /5X,' - INLET PRESSURE AS OUTPUT ====>   +'
     $ /5X,' - OUTLET PRESSURE AS OUTPUT ===>   -')
      READ(5,3001)ICA
      IF(ICA.EQ.IPIU)GO TO 1
      IF(ICA.EQ.IMEN)GO TO 1
      IF(ICA.EQ.IBL)GO TO 1
      GO TO 2
 3001 FORMAT(A)
    1 CONTINUE
C
      WRITE(MODU,'(A1,A3)')ICA,MOD
      IF(ICA.EQ.IBL)MODU=MOD
      WRITE(IBLOC,'(2A4)')MODU,IOB
C
      RETURN
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0I2 (IFUN, VAR, MX1, IV1, IV2, XYU, DATI, ID1, ID2,
     $             IBL1, IBL2, IER, CNXYU, TOL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER IFUN, MX1, VAR
      DIMENSION VAR(MX1, *), XYU(*), DATI(*), CNXYU(*), TOL(*)
      DIMENSION H(5),TMI(5)
      CHARACTER*4 NOMAPP
C
      COMMON /NORM/ P0, H0, T0,  W0,RO0, AL0, V0, DP0
C
      INTEGER ID2, IV1
C
      DATA PIGR,G/3.1415926,9.80665/
C
C     ----- CONDENSATORE   MODELLO CON CAVITA' IN EQUILIBRIO
C
      GO TO (100, 200), IFUN
C
  100 WRITE (14, 500)'NTUB    ','DIAE    ','DIAI    ','LUNG    ',
     $'TYPE_CAV','VOL.CAV.','ZERO_Y  ','VOL_Y   ','GAMMA_Y ','SEZ_Y   ',
     $'ROM     ','CP MET. ','COND.MET','NCEL    '
      WRITE (14,2010)
      WRITE (14, 500)'PORTATA ','P1 MONTE','P2 VALLE',
     $               'ENTALPIA','Fr.NaCl ','COEFF.  '
      WRITE (14,2011)
      WRITE (14, 500)'DISLIV. '
C     
      RETURN
C
C     -----  LETTURA E MEMORIZZAZIONE DATI
C
 200  READ (14, 501)
      READ (14, 501)ANTUB  , DIAE     , DIAI     , ALUNG    ,
     $ TYP      , VCAV     , ZERY     , VY       , GY       , SEZY     ,
     $ ROM      , CPMET    , COND     , ANCEL    
      READ(14,501)
      READ(14,501) WL,PM,PV,HFT,FDAT,CS
      READ(14,501)
      READ(14,501) DZ
C
 500  FORMAT (3(4X, A8, ' =',10X, '*'))
 501  FORMAT (3(14X, F10.0, 1X))
 2010 FORMAT('*   DATA TO BE ASSIGNED TO DEFINE THE HEAD LOSS')
 2011 FORMAT('*   SEAL ADDED TO THE HEAD LOSS')
C
C     -----   inizio modifica istruzione di DECODE   -----
C
      WRITE(NOMAPP,'(A1)')IBL1
      IWP=0
      IF(NOMAPP(1:1).EQ.'+')IWP=1
      IF(NOMAPP(1:1).EQ.'-')IWP=2
C
C     -----    fine modifica istruzione di DECODE    -----
C
CC&   MARCH  INIZIO MODIFICA MARCH 22/9/92
C
C
Car--- A. Rossi 09/02/01 -- inizio modifica ANCEL = numero di celle -----
C
      IF(ANCEL.LT.1.) ANCEL = 1.
      IF(ANCEL.GT.5.) ANCEL = 5.
C
Car--- A. Rossi 09/02/01 -- fine modifica ANCEL = numero di celle -----
C
      P        = XYU(IV1)
      Y        = XYU(IV1 +  1)
      TM       = XYU(IV1 +  2)
      HU       = XYU(IV1 +  3)
      HLS      = XYU(IV1 +  4)
      HVS      = XYU(IV1 +  5)
      PF       = XYU(IV1 +  6)
      YP       = XYU(IV1 +  7)
      IF(IWP.EQ.0)WCF = XYU(IV1 +  8)
      IF(IWP.EQ.1)PMON= XYU(IV1 +  8)
      IF(IWP.EQ.2)PVAL= XYU(IV1 +  8)
      WV       = XYU(IV1 +  9)
      HVI      = XYU(IV1 + 10)
      WVV      = XYU(IV1 + 11)
      HVVI     = XYU(IV1 + 12)
      WEC      = XYU(IV1 + 13)
      WDR      = XYU(IV1 + 14)
      HDR      = XYU(IV1 + 15)
      WLS      = XYU(IV1 + 16)
      WVS      = XYU(IV1 + 17)
      WRC      = XYU(IV1 + 18)
      HRC      = XYU(IV1 + 19)
      IF(IWP.EQ.0)THEN 
         PMON  = XYU(IV1 + 20)
         PVAL  = XYU(IV1 + 21)
      ELSE IF(IWP.EQ.1)THEN
         WCF   = XYU(IV1 + 20)
         PVAL  = XYU(IV1 + 21)
      ELSE IF(IWP.EQ.2)THEN
         WCF   = XYU(IV1 + 20)
         PMON  = XYU(IV1 + 21)
      ENDIF
      HI       = XYU(IV1 + 22)
      CORR     = XYU(IV1 + 23)
      FNAC     = XYU(IV1 + 24)
      FC       = XYU(IV1 + 25)
C
C     CALCOLO DEL COEFFICIENTE DI PERDITA DI CARICO
C
      RK0=0.
      PMD=0.5*PM+0.5*PV
C
      IF(WL.GT.0.) THEN
	 IFL=1
CC	 S=SHEV(PMD,H,IFL)
CC	 RO=ROEV(PMD,S,IFL)
         CALL T_FOR(PMD,HFT,FDAT,TFT)
         CALL ROC_FOR(FDAT,TFT,PMD,RO)
	 RK0=2.*(PM-PV)*RO/(WL*WL+.1*WL)*W0*W0/P0
	 GO TO 15
      ENDIF
C
      RK0= CS/P0*W0*W0
C      
 15   CONTINUE
C
C     CALCOLO DATI GEOMETRICI
C
      NCEL  =ANCEL+.1
      PINT  =PIGR*ANTUB
      TSEZ  =.25*PINT*DIAI**2
      VI    =TSEZ*ALUNG/ANCEL
      DIAM  =.5*(DIAE+DIAI)
      CTM   =.25*PINT*(DIAE**2-DIAI**2)*ROM*CPMET*ALUNG/ANCEL
      ALNEI =.5*ALOG(DIAE/DIAI)
      ALNEM =.5*ALOG(DIAE/DIAM)
      ALNMI =.5*ALOG(DIAM/DIAI)
C
C     COEFFICIENTE DI SCAMBIO LATO MANTELLO COSTANTE
C
      CTES  =25000.
C
C     PRESSIONE LATO TUBI COSTANTE
C
      PCI   =300000.
C
      CALL SATUR(P,2,HL,HV,1)
      CALL SATUR(P,7,TSAT,AUS,1)
C
C     INIZIALIZZAZIONE LIVELLO MISURATO
C
      IF (YP.LE.0.) XYU(IV1+7)=0.01
C
C     INIZIALIZZAZIONE CON PORTATA DI REFRIGERANTE NULLA
C
      IF (WCF.LE.0.) THEN
         HU=HL
         DO 11 I=1,NCEL
	    H(I)=HU
   11    CONTINUE
         GO TO 102
      ENDIF
C
C     INIZIALIZZAZIONE STANDARD
C
C     STIMA DI HU SE NON VIENE ASSEGNATO UN VALORE DI TENTATIVO
C
      IF (HU.LE.0.) THEN
       Q=WV*HVI+WVV*HVVI+WDR*HDR-(WEC+WLS)*HL-WVS*HV+WRC*HRC
       HU=HI+Q/WCF
      ELSE
       Q=WCF*(HU-HI)
      ENDIF
CC
CC    Modifica del 18/01/01
CC    Uso delle tavole di acqua salata per il 
CC        fluido dentro il fascio tubiero
CC
CC    SR=SHEV(PCI,HU,1)
CC    TF=TEV(PCI,SR,1)
CC    CPLR=CPEV(PCI,SR,0.,1.,1)
      CALL T_FOR(PCI,HU,FNAC,TF)
      CALL CS_FOR(FNAC,CPLR)
CC
CC    Fine modifica del 18/01/01
CC
      IF(WCF.LE.1.E-3) THEN
         GAMMA=100.
      ELSE
         WCFS=MAX(WCF,10.)
         CALL GAM03(GAMMA,DGAM,WCFS,TSEZ,DIAI,PCI,TF)
      ENDIF
C
      CSX=PINT/(1./(DIAE*CTES)+ALNEI/COND+1./(DIAI*GAMMA))
C
      WCP=WCF*CPLR
      WCH=WCP/CSX
C
      EL=EXP(ALUNG/WCH)
      ALUNG=ALUNG/ANCEL
C
C     STIMA DELLA DISTRIBUZIONE DI POTENZA E DI ENTALPIA LUNGO I TUBI
C
      DO 110 I=1,NCEL
         EX=EXP(I*ALUNG/WCH)
         QC=Q*EL*(EX-1.)/(EX*(EL-1.))
         H(I)=HI+QC/WCF
C
  110 CONTINUE
C
  102 CONTINUE
C
C     TERMINE INIZIALIZZAZIONE
C
C     BETA : FATTORE PESO PER IL CALCOLO DELLA TEMPERATURA DI SCAMBIO
C
      BETA=0.3
C
      XYU( IV1+  3) = HU
C
      DATI(ID2)     = ANTUB
      DATI(ID2+  1) = DIAE
      DATI(ID2+  2) = DIAI
      DATI(ID2+  3) = ALUNG
      DATI(ID2+  4) = TYP
      DATI(ID2+  5) = VCAV
      DATI(ID2+  6) = ZERY
      DATI(ID2+  7) = VY
      DATI(ID2+  8) = GY
      DATI(ID2+  9) = SEZY
      DATI(ID2+ 10) = ROM
      DATI(ID2+ 11) = CPMET
      DATI(ID2+ 12) = COND
      DATI(ID2+ 13) = VI
      DATI(ID2+ 14) = CTM
      DATI(ID2+ 15) = ANCEL
      DATI(ID2+ 16) = ALNEI
      DATI(ID2+ 17) = ALNEM
      DATI(ID2+ 18) = ALNMI
      DATI(ID2+ 19) = TSEZ
      DATI(ID2+ 20) = PCI
      DATI(ID2+ 21) = CTES
      DATI(ID2+ 22) = BETA
      DATI(ID2+ 23) = RK0
      DATI(ID2+ 24) = IWP
      DATI(ID2+ 25) = DZ*G/P0
C
      ID2 = ID2+ 25
C
      DO 103 I=1,NCEL
         DATI(ID2+     I)=H(I)
         DATI(ID2+NCEL+I)=0.
  103 CONTINUE
C
      ID2 = ID2+ 2*NCEL
C
CC&   MARC FINE MODIFICA MARCH 22/9/1992
C
C     -----  COSTANTI DI NORMALIZZAZIONE
C
      CNXYU(IV1)     =  P0
      CNXYU(IV1+  1) =  1.
      CNXYU(IV1+  2) =  T0
      CNXYU(IV1+  3) =  H0
      CNXYU(IV1+  4) =  H0
      CNXYU(IV1+  5) =  H0
      CNXYU(IV1+  6) =  P0
      CNXYU(IV1+  7) =  1.
      IF(IWP.EQ.0)CNXYU(IV1 +  8)=W0
      IF(IWP.EQ.1)CNXYU(IV1 +  8)=P0
      IF(IWP.EQ.2)CNXYU(IV1 +  8)=P0
      CNXYU(IV1+  9) =  W0
      CNXYU(IV1+ 10) =  H0
      CNXYU(IV1+ 11) =  W0
      CNXYU(IV1+ 12) =  H0
      CNXYU(IV1+ 13) =  W0
      CNXYU(IV1+ 14) =  W0
      CNXYU(IV1+ 15) =  H0
      CNXYU(IV1+ 16) =  W0
      CNXYU(IV1+ 17) =  W0
      CNXYU(IV1+ 18) =  W0
      CNXYU(IV1+ 19) =  H0
      IF(IWP.EQ.0)THEN 
         CNXYU(IV1 + 20)=P0
         CNXYU(IV1 + 21)=P0
      ELSE IF(IWP.EQ.1)THEN
         CNXYU(IV1 + 20)=W0
         CNXYU(IV1 + 21)=P0
      ELSE IF(IWP.EQ.2)THEN
         CNXYU(IV1 + 20)=W0
         CNXYU(IV1 + 21)=P0
      ENDIF
      CNXYU(IV1+ 22) =  H0
      CNXYU(IV1+ 23) =  1.
      CNXYU(IV1+ 24) =  1.
      CNXYU(IV1+ 25) =  1.
C
      RETURN
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0C1 (IFUN, AJAC, MX5, IXYU, XYU, IPD,
     $   DATI, RNI, IBLI, IBL2)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER IFUN, MX5, IPD
      DIMENSION AJAC(MX5, *), XYU(*), DATI(*), RNI(*)
C
      EXTERNAL BCN0
C
      INTEGER I, J, NSTATI, NUSCIT, NINGRE, IXYU
C
C     ----- CONDENSATORE   MODELLO CON CAVITA' IN EQUILIBRIO
C
      GOTO (100, 200, 300), IFUN
C      
C     -----  TOPOLOGIA JACOBIANO
C
 100  DO 11 I= 1,   9
         DO 21 J= 1,  26
            AJAC(I,J) = 1.
 21      CONTINUE
 11   CONTINUE
C
      RETURN
C
C     -----  CALCOLO RESIDUI
C
 200  CALL BCN0 (IFUN, IXYU, XYU, IPD, DATI, RNI)
      RETURN
C
C     -----  CALCOLO JACOBIANO NUMERICO
C
 300  NSTATI =   2
      NUSCIT =   7
      NINGRE =  17
      EPS    = 1.E-3
      EPSLIM = 1.E-7
      CALL NAJAC (AJAC, (MX5), IXYU, XYU, IPD, DATI, RNI,
     $      NSTATI, NUSCIT, NINGRE, EPS, EPSLIM, BCN0)
      RETURN
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0 (IFUN, IXYU, XYU, IPD, DATI, RNI)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER IFUN, IXYU, IPD
      DIMENSION XYU(*), DATI(*), RNI(*)
C
      COMMON /NORM/ P0, H0, T0, W0, RO0, AL0, V0, DP0
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      DIMENSION H(5),TMI(5),TFI(5),TFU(5)
C
      LOGICAL KREGIM
C
      DATA PIGR,G/3.1415926,9.80665/
      DATA NDPT/20/
C
C     ----- CONDENSATORE   MODELLO CON CAVITA' IN EQUILIBRIO
C
C     ----- DECODIFICA VARIABILI E DATI
C
CC&   MARCH INIZIO MODIFICA MARCH 22/9/92
C
      ANTUB    = DATI(IPD)
      DIAE     = DATI(IPD +  1)
      DIAI     = DATI(IPD +  2)
      ALUNG    = DATI(IPD +  3)
      TYP      = DATI(IPD +  4)
      VCAV     = DATI(IPD +  5)
      ZERY     = DATI(IPD +  6)
      VY       = DATI(IPD +  7)
      GY       = DATI(IPD +  8)
      SEZY     = DATI(IPD +  9)
      ROM      = DATI(IPD + 10)
      CPMET    = DATI(IPD + 11)
      COND     = DATI(IPD + 12)
      VI       = DATI(IPD + 13)
      CTM      = DATI(IPD + 14)
      ANCEL    = DATI(IPD + 15)
      ALNEI    = DATI(IPD + 16)
      ALNEM    = DATI(IPD + 17)
      ALNMI    = DATI(IPD + 18)
      TSEZ     = DATI(IPD + 19)
      PCI      = DATI(IPD + 20)
      CTES     = DATI(IPD + 21)
      BETA     = DATI(IPD + 22)
      RK0      = DATI(IPD + 23)
      IWP      = DATI(IPD + 24)
      RGZ      = DATI(IPD + 25)
C
      P        = XYU(IXYU)
      Y        = XYU(IXYU +  1)
      TM       = XYU(IXYU +  2)
      HU       = XYU(IXYU +  3)
      HLS      = XYU(IXYU +  4)
      HVS      = XYU(IXYU +  5)
      PF       = XYU(IXYU +  6)
      YP       = XYU(IXYU +  7)
      IF(IWP.EQ.0)WCF = XYU(IXYU +  8)
      IF(IWP.EQ.1)PMON= XYU(IXYU +  8)
      IF(IWP.EQ.2)PVAL= XYU(IXYU +  8)
      WV       = XYU(IXYU +  9)
      HVI      = XYU(IXYU + 10)
      WVV      = XYU(IXYU + 11)
      HVVI     = XYU(IXYU + 12)
      WEC      = XYU(IXYU + 13)
      WDR      = XYU(IXYU + 14)
      HDR      = XYU(IXYU + 15)
      WLS      = XYU(IXYU + 16)
      WVS      = XYU(IXYU + 17)
      WRC      = XYU(IXYU + 18)
      HRC      = XYU(IXYU + 19)
      IF(IWP.EQ.0)THEN 
         PMON  = XYU(IXYU + 20)
         PVAL  = XYU(IXYU + 21)
      ELSE IF(IWP.EQ.1)THEN
         WCF   = XYU(IXYU + 20)
         PVAL  = XYU(IXYU + 21)
      ELSE IF(IWP.EQ.2)THEN
         WCF   = XYU(IXYU + 20)
         PMON  = XYU(IXYU + 21)
      ENDIF
      HI       = XYU(IXYU + 22)
      CORR     = XYU(IXYU + 23)
      FNAC     = XYU(IXYU + 24)
      FC       = XYU(IXYU + 25)
C
      CTES=CTES*CORR !tiene conto della variabilita dello scambio lato mantello
C
      NCEL=ANCEL+.1
C
      DO 103 I=1,NCEL
         H(I)     = DATI(IPD + 25 + I)
         TMI(I)   = DATI(IPD + 25 + I + NCEL)
  103 CONTINUE
C
C
      DP  = PMON-PVAL
      PMED=(PMON+PVAL)*P0/2.
      HMED=(HI+HU)*H0/2.
CC      S=SHEV(PMED,H*H0,IFL)
CC      RO=ROEV(PMED,S,IFL)
      CALL T_FOR(PMED,HMED,FNAC,TFT)
      CALL ROC_FOR(FNAC,TFT,PMED,RO)
C
      UMBETA=1.-BETA
C
      PINT=PIGR*ANTUB
C
      CALL BCN0ST(P*P0,HL,HV,ROL,ROV,TSAT,DRLDP,DRVDP,DHLDP,DHVDP)
C
C     CALCOLO TEMPERATURA DI USCITA TUBI
C
CC
CC    Modifica del 18/01/01
CC    Uso delle tavole di acqua salata per il 
CC        fluido dentro il fascio tubiero
CC
CC    SR   =SHEV(PCI,HU*H0,1)
CC    TFEX =TEV(PCI,SR,1)
      CALL T_FOR(PCI,HU*H0,FNAC,TFEX)
CC
CC Fine modifica del 18/01/01
CC
C
C     CALCOLO COEFF. DI SCAMBIO LIMINARE LATO TUBI
C
      WCFF =WCF*W0
      IF(WCFF.LE.1.E-3) THEN
         GAMMA=100.
      ELSE
         WCFS =MAX(WCFF,10.)
         CALL GAM03(GAMMA,DGAM,WCFS,TSEZ,DIAI,PCI,TFEX)
      ENDIF
C
C     CALCOLO PRODOTTO COEFF. DI SCAMBIO * SUPERFICIE
C     CSTOT  FRA FLUIDO LATO MANTELLO E LATO TUBI
C     CSE    FRA FLUIDO LATO MANTELLO E CENTRO PARETE TUBI
C     CSI    FRA CENTRO PARETE TUBI E FLUIDO NEI TUBI
C
      CSTOT=PINT*ALUNG/(1./(DIAE*CTES)+ALNEI/COND+1./(DIAI*GAMMA))
      CSE  =PINT*ALUNG/(1./(DIAE*CTES)+ALNEM/COND)
      CSI  =PINT*ALUNG/(ALNMI/COND+1./(DIAI*GAMMA))
C
C      IF(IFUN.EQ.2) THEN
C       WRITE(6,*) 'COND---------'
C       WRITE(6,*) ' CSI  =',CSI,' CSE  =',CSE,' CSTOT=',CSTOT
C       WRITE(6,*) ' GAMMA=',GAMMA
C      ENDIF
C
C
C     CALCOLO DEL REGIME STAZIONARIO
C
C
      IF (KREGIM) THEN
C
C     QQ    POTENZA TOTALE
C     QC    POTENZA DI CELLA
C     TFIN  TEMPERATURA DEL REFRIGERANTE ENTRANTE NELLA CELLA
C     TFU   TEMPERATURA DEL REFRIGERANTE USCENTE DALLA CELLA
C     HIN   ENTALPIA DEL REFRIGERANTE ENTRANTE NELLA CELLA
C     HUC   ENTALPIA DEL REFRIGERANTE USCENTE DALLA CELLA
C     HUS   ENTALPIA DEL REFRIGERANTE USCENTE DALLA CELLA ALLA
C           ITERAZIONE PRECEDENTE
C     TMM   TEMPERATURA DEL CENTRO DELLA PARETE DEL TUBO NELLA CELLA
C
      QQ=0.
      DO 10 I=1,NCEL
C
CC
CC    Modifica del 18/01/01
CC    Uso delle tavole di acqua salata per il 
CC        fluido dentro il fascio tubiero
CC
         IF (I.EQ.1) THEN
	    HIN=HI*H0
CC	    SR  =SHEV(PCI,HIN,1)
CC	    TFIN=TEV(PCI,SR,1)
            CALL T_FOR(PCI,HIN,FNAC,TFIN)
	 ELSE
	    HIN=H(I-1)
	    TFIN=TFU(I-1)
	 ENDIF
C
         HUS=H(I)
CC       SR    =SHEV(PCI,HUS,1)
CC       TFU(I)=TEV(PCI,SR,1)
CC       CPLR  =CPEV(PCI,SR,0.,1.,1)
         CALL T_FOR(PCI,HUS,FNAC,TFU(I))
         CALL CS_FOR(FNAC,CPLR)
C
      HUC=(WCF*W0*HIN+CSTOT*(TSAT-BETA*TFIN-UMBETA*(TFU(I)-HUS/CPLR)))/
     $    (WCF*W0+CSTOT*UMBETA/CPLR)
C
CC       SR    =SHEV(PCI,HUC,1)
CC       TFU(I)=TEV(PCI,SR,1)
         CALL T_FOR(PCI,HUC,FNAC,TFU(I))
CC
CC    Fine modifica del 18/01/01
CC
         QC  = CSTOT*(TSAT-BETA*TFIN-UMBETA*TFU(I))
C
         TMM =(CSE*TSAT+CSI*(BETA*TFIN+UMBETA*TFU(I)))/(CSE+CSI)
C
         QQ  = QQ+QC
C
         H(I)=HUC
	 IF (IFUN.EQ.2) THEN
	    DATI(IPD+25+I)     =HUC
	    DATI(IPD+25+I+NCEL)=TMM
	 ENDIF
C
  10  CONTINUE
C
C     ----  CALCOLO DEI RESIDUI
C
      I=0
      RNI(I+1) =WV*HVI+WVV*HVVI+WDR*HDR+WRC*HRC-(WEC+WLS)*HLS
     $          -WVS*HV/H0+WCF*(HI-HU)
      RNI(I+2) =WV+WVV+WDR-WEC-WLS-WVS+WRC
      RNI(I+3) =  TMM/T0-TM
C
       IF (WCF*W0.GT.10.) THEN
      RNI(I+4) = QQ/(WCF*W0*H0)+HI-HU
       ELSE
      RNI(I+4) = QQ/(W0*H0)
       ENDIF
C
      RNI(I+5) =  HL/H0-HLS
      RNI(I+6) =  HV/H0-HVS
      RNI(I+7) =  PF-P-(G*ROL*Y)/P0
       CALL BCN0TY(TYP,SEZY,Y,ZERY,GY,VY,VL,DVLDY,YPER)
      RNI(I+8) =  YP-YPER
      RNI(I+9) =  DP-FC*RK0/RO/2.*(WCF*ABS(WCF)+.1/W0*WCF) - RGZ*RO
C
      ELSE
C
C
C     CALCOLO DEL TRANSITORIO
C
C
      IF (IFUN.EQ.3.OR.ITERT.GT.0.) GO TO 104
C
C
C     HIN    ENTALPIA INGRESSO CELLA ALL' ISTANTE T+DT
C     HIP    ENTALPIA INGRESSO CELLA ALL' ISTANTE T
C     TFIN   TEMPERATURA INGRESSO CELLA ALL' ISTANTE T+DT
C     TFIP   TEMPERATURA INGRESSO CELLA ALL' ISTANTE T
C     TFI(I) TEMPERATURA USCITA CELLA ALL' ISTANTE T
C     H(I)   ENTALPIA USCITA CELLA ALL' ISTANTE T
C     TMI(I) TEMPERATURA PARETE CELLA ALL' ISTANTE T
C
      IF (WCF.LT.0.) WCF=0.
C
      CDTD=CDT/NDPT
C
      DO 200 JJ=1,NDPT            
         DO 100 I=1,NCEL
            IF (I.EQ.1) THEN
	       HIN =HI*H0
	       HIP =HIN
	       HAUS=HIN
CC
CC    Modifica del 18/01/01
CC    Uso delle tavole di acqua salata per il 
CC        fluido dentro il fascio tubiero
CC
CC             SR  =SHEV(PCI,HIN,1)
CC             TFIN=TEV(PCI,SR,1)
               CALL T_FOR(PCI,HIN,FNAC,TFIN)
	       TFIP=TFIN
            ELSE
	       HIP=HAUS
	       HIN=H(I-1)
               TFIP=TFI(I-1)
            ENDIF
            HAUS=H(I)
C
CC          SR=SHEV(PCI,H(I),1)
CC          TF=TEV(PCI,SR,1)
            CALL T_FOR(PCI,H(I),FNAC,TF)
            TFI(I)=TF
CC          RF  =ROEV(PCI,SR,1)
CC          CPLR=CPEV(PCI,SR,0.,1.,1)
Car---09/02/01---qui c'e' il casino
            CALL ROC_FOR(FNAC,TF,PCIN,RF)
            CALL CS_FOR(FNAC,CPLR)
C
            TAUH=VI*RF
C
      TT1=CDTD*(WCF*W0*(HIP-H(I))+CSI*(TMI(I)-BETA*TFIP-UMBETA*TFI(I)))
      TT2=CDTD*(CSE*(TSAT-TMI(I))-CSI*(TMI(I)-BETA*TFIP-UMBETA*TFI(I)))
C
            CA1=CDTD*WCF*W0
            C11=TAUH+CDTD*(WCF*W0+CSI*UMBETA/CPLR)
            C12=-CDTD*CSI
            C21=C12*UMBETA/CPLR
            C22=CTM+CDTD*(CSE+CSI)
            CB1=CSI*(BETA*TFIN+UMBETA*(TFI(I)-H(I)/CPLR))
            TTN1=TT1-CDTD*CB1+TAUH*H(I)+CA1*HIN
            TTN2=TT2+CDTD*(CSE*TSAT+CB1)+CTM*TMI(I)
            H(I)=(C22*TTN1-C12*TTN2)/(C11*C22-C12*C21)
            TMI(I)=(TTN2-C21*H(I))/C22
C
CC          SR=SHEV(PCI,H(I),1)
CC          TFIN=TEV(PCI,SR,1)
            CALL T_FOR(PCI,H(I),FNAC,TFIN)
CC
CC    Fine modifica del 18/01/01
CC
C
C
            DATI(IPD+25+I)     =H(I)
            DATI(IPD+25+I+NCEL)=TMI(I)
C            
  100    CONTINUE
C
  200 CONTINUE 
C
  104 CONTINUE
C
      CALL BCN0TY(TYP,SEZY,Y,ZERY,GY,VY,VL,DVLDY,YPER)
      CM11=DVLDY*(ROL-ROV)
      CM12=VL*DRLDP+(VCAV-VL)*DRVDP
      CM21=DVLDY*(ROL*HLS*H0-ROV*HV)
      CM22=VL*(ROL*DHLDP+HLS*H0*DRLDP)+(VCAV-VL)*(ROV*DHVDP+HV*DRVDP)-
     $VCAV
      DET=CM11*CM22-CM12*CM21
      TN1=(WV+WVV+WDR-WEC-WLS-WVS+WRC)*W0
C
      QQ=0.
C      
      DO 105 I=1,NCEL
  105    QQ=QQ+CSE*(TSAT-TMI(I))
C
      TN2= (WV*HVI+WVV*HVVI+WDR*HDR+WRC*HRC-(WEC+WLS)*HLS)*H0*W0
     $     -WVS*HV*W0-QQ
C
      I=0
C      
      RNI(I+1) =  (CM11*TN2-CM21*TN1)/(DET*P0)
      RNI(I+2) =  (CM22*TN1-CM12*TN2)/DET
      RNI(I+3) =  TM-TMI(NCEL)/T0
      RNI(I+4) =  HU-H(NCEL)/H0
      RNI(I+5) =  HL/H0-HLS
      RNI(I+6) =  HV/H0-HVS
      RNI(I+7) =  PF-P-(G*ROL*Y)/P0
       CALL BCN0TY(TYP,SEZY,Y,ZERY,GY,VY,VL,DVLDY,YPER)
      RNI(I+8) =  YP-YPER
      RNI(I+9) =  DP-FC*RK0/RO/2.*(WCF*ABS(WCF)+.1/W0*WCF) - RGZ*RO
C
      ENDIF
C
CC&   MARC FINE MODIFICA MARCH 22/9/92
C
C     ATTENZIONE AI CAMBIAMENTI DEI NOMI DEI SOTTOPROGRAMMI
C
C     VSATR     E' DIVENTATO     BCN0ST
C     CNDTYP    E' DIVENTATO     BCN0TY
C
C
      RETURN
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0ST(P,HL,HV,ROL,ROV,TS,DRLDP,DRVDP,DHLDP,DHVDP)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CALL SATUR(P,2,HL,HV,1)
      CALL SATUR(P,3,ROL,ROV,1)
      CALL SATUR(P,7,TS,AUS,1)
      PP=0.99*P
      CALL SATUR(PP,2,HLP,HVP,1)
      CALL SATUR(PP,3,RLP,RVP,1)
      DRLDP=100.*(ROL-RLP)/P
      DRVDP=100.*(ROV-RVP)/P
      DHLDP=100.*(HL-HLP)/P
      DHVDP=100.*(HV-HVP)/P
      RETURN
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0TY(TYP,SEZY,Y,ZERY,GY,VY,VL,DVLDY,YPER)
C
C     **********CAVITA  CONDENSATORE DI VAPORE**********
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      IF(SEZY.LE.0.) THEN
         CALL  BCNLIV(TYP,Y,VL,DVLDY,YPER)
      ELSE
         YPER = (Y-ZERY)/GY*100.
         IF(Y.GE.ZERY.OR.ZERY.EQ.0.)GO TO 10
         AMY = VY/ZERY
         VL = AMY*Y
         DVLDY = AMY
         GO TO 20
   10    VL = VY+SEZY*(Y-ZERY)
         DVLDY = SEZY
   20 ENDIF
C   
      RETURN
C
      END
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCNLIO(Y,RCAV,HLCAV,VL,DVLDY)
C
C Questa routine puo` essere chiamata in BCNLIV per
C calcolare il volume occupato in un cilindro orizzontale
C e DVLDY
C
C NOTI:
C     Y livello
C     RCAV  raggio del cilindro
C     HLCAV lunghezza del cilindro
C
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      ALFA  = ACOS((RCAV-Y)/RCAV)
      VL  = RCAV**2.*(ALFA-COS(ALFA)*SIN(ALFA))*HLCAV
C
      DVLDY  = 2.*RCAV*SIN(ALFA)*HLCAV
      IF(DVLDY.LT..1E-5)DVLDY = 0.
C
      RETURN
      END
C
C
C*****************************************************************************
C
C
C~FORAUS_BCN0~C
C
C FORTRAN AUSILIARIO DEL MODULO CONDENSATORE DI VAPORE
C PER LA SUA SCRITTURA VEDERE MANUALE D'USO O
C UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD.
C
C*********** BREVE SPIEGAZIONE DEI PARAMETRI DELLA SUBROUTINE ******************
C
C  SUBROUTINE BCNLIV(TYP,Y,VL,DVLDY,YPER)
C
C  La subroutine BCNLIV, in funzione dei valori TYP e Y
C  deve fornire  VL, DVLDY e YPER.
C
C  Parametri in ingresso:  TYP, Y
C  Parametri in uscita:    VL, DVLDY, YPER
C
C  Significato dei parametri di chiamata:
C
C  TYP       = corrisponde al dato TYPE_CAV nel file F14 (vedi scheda D1)  viene
C              utilizzato per distinguere le  diverse  geometrie  delle  cavita`
C              trattate dal modulo BCN0 presenti contemporaneamente in un model-
C              lo matematico. Viene di solito usato all'interno della subroutine
C              come puntatore;
C
C  Y         = rappresenta la misura del livello totale nella cavita`in metri;
C
C  VL        = volume occupato dalla zona liquida in m**3;
C
C  DVLDY     = derivata del volume del liquido rispetto al livello;
C
C  YPER      = livello di liquido nel range di misura in %.
C
C
C************ INIZIO DEL TESTO FORTRAN DA SCRIVERE *****************************
C
C      SUBROUTINE  BCNLIV(TYP,Y,VL,DVLDY,YPER)
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      RETURN
C      END
C
C~FORAUS_BCN0~C
CC
C
C
C*****************************************************************************
C
C
      SUBROUTINE BCN0D1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,IX
     $YU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
