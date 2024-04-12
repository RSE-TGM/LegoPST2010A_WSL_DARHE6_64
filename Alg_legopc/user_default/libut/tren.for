C**********************************************************************
C modulo tren.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)tren.f	5.2
C**********************************************************************
C*                                                                   *
C*                           modulo TREN                             *
C*                                                                   *
C*                   Stadio di turbina a reazione                    *
C*                                                                   *
C*********************************************************************
      SUBROUTINE TRENI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/TREN01/IBLOC
      COMMON/TREN02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'TREN'/
C
      CALL TRENI4(IOB,MOD)
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      NSTATI    =  0
      NUSCIT    =  6
      NINGRE    =  7
C
      WRITE(IFO,3001)IOB
 3001 FORMAT('HUTZ',A4,2X,
     $'--UA-- FLUID ENTHALPY AT THE REACTION STAGE OUTLET')
      WRITE(IFO,3002)IOB
 3002 FORMAT('WUTZ',A4,2X,
     $'--UA-- STEAM FLOW RATE AT THE REACTION STAGE OUTLET')
      WRITE(IFO,3003)IOB
 3003 FORMAT('PITZ',A4,2X,
     $'--UA-- STEAM PRESSURE AT THE REACTION STAGE INLET')
      WRITE(IFO,3005)IOB
 3005 FORMAT('QMEC',A4,2X,
     $'--UA-- MECHANICAL POWER OF THE REACTION TURBINE STAGE')
      WRITE(IFO,3006)IOB
 3006 FORMAT('PSPZ',A4,2X,
     $'--UA-- STEAM PRESSURE AT BLEEDING OUTLET')
      WRITE(IFO,3007)IOB
 3007 FORMAT('HSPZ',A4,2X,
     $'--UA-- STEAM ENTHALPY AT BLEEDING OUTLET')
      WRITE(IFO,3008)IOB
 3008 FORMAT('WITZ',A4,2X,
     $'--IN-- STEAM FLOW RATE AT THE REACTION STAGE INLET')
      WRITE(IFO,3009)IOB
 3009 FORMAT('WSPZ',A4,2X,
     $'--IN-- FLOW RATE OF STEAM BLED FROM THE REACTION TURB. STAGE')
      WRITE(IFO,3010)IOB
 3010 FORMAT('HITZ',A4,2X,
     $'--IN-- STEAM ENTHALPY AT THE REACTION STAGE INLET')
      WRITE(IFO,3011)IOB
 3011 FORMAT('PUTZ',A4,2X,
     $'--IN-- STEAM PRESSURE AT THE REACTION STAGE OUTLET')
      WRITE(IFO,3012)IOB
 3012 FORMAT('SERC',A4,2X,
     $'--IN-- LOAD REJECTION OR TRIP SIGNAL')
      WRITE(IFO,3013)IOB
 3013 FORMAT('SEAV',A4,2X,
     $'--IN-- STARTING BUTTON OF THE REACTION TURBINE')
      WRITE(IFO,3014)IOB
 3014 FORMAT('RPMV',A4,2X,
     $'--IN-- ROTATIONAL SPEED OF THE REACTION TURBINE')
      RETURN
      END
C
C*********************************************************************
      SUBROUTINE TRENI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/TREN01/IBLOC
      COMMON/TREN02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      WRITE(IBLOC,5000)MOD,IOB
 5000 FORMAT(2A4)
C
      RETURN
      END
C
C*********************************************************************
      SUBROUTINE TRENI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBLOC1,IBLOC2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
C      REAL PIN0,HIN0,WIN0,PUS0,HUS0,VEL0,SIN0,HUIS0,ROI0
C      REAL ETAD0,CK0
      CHARACTER*8 PXIN0,HXIN0,WXIN0,PXUS0,HXSP0,VELX0,ETAX0,WXSP0
      DATA PXIN0/'PRES__IN'/, HXIN0/'ENTA__IN'/, WXIN0/'PORT__IN'/,
     $     PXUS0/'PRES_OUT'/, HXSP0/'ENTA_SPL'/, VELX0/'RPMV_NOM'/,
     $     ETAX0/'REND_NOM'/, WXSP0/'PORT_SPL'/
C
C------STADIO TURBINA A REAZIONE
C
      GO TO (1,10),IFUN
C
C------SCRITTURA FILE 14
C
    1 WRITE (14,100) PXIN0, HXIN0, WXIN0
      WRITE (14,100) PXUS0, HXSP0, VELX0
      WRITE (14,100) ETAX0, WXSP0
  100 FORMAT(3(4X,A8,' =',10X,'*'),5X)
      RETURN
C
C------LETTURA FILE 14
C
   10 READ(14,102)
      READ(14,102) PIN0, HIN0, WIN0
      READ(14,102) PUS0, HSP0, VEL0
      READ(14,102) ETA0, WSP0
  102 FORMAT(3(14X,F10.0,1X),5X)
C
C---- CALCOLO NEL PUNTO DI LAVORO NOMINALE DI:
C----       AMMETTENZA DI TRAFILAMENTO CKA0
C----       COEFFICIENTE D'EFFLUSSO    CK0
C----       SALTO ENTALPICO (NORM.)    DH0
C
      SIN0=SHEV(PIN0,HIN0,1)
      HUIS0=HEV(PUS0,SIN0,1)
      ROI0=ROEV(PIN0,SIN0,1)
      HUS0=HIN0-ETA0*(HIN0-HUIS0)
      WTR0=WSP0*(HSP0-HUS0)/(HIN0-HUS0)
      CKA0=WTR0/SQRT(PIN0/ROI0)
       IF(CKA0.LT.0) CKA0=0.
      CK0=(W0*W0/P0)*(PIN0*PIN0-PUS0*PUS0)*ROI0
     $    /(PIN0*WIN0*WIN0)
      DH0=(HIN0-HUS0)/H0
C
C---- STAMPA
C
      WRITE (6,3000) ETA0
 3000 FORMAT('   RENDIMENTO AL NOMINALE = ',F7.4)
      WRITE(6,3011) WTR0,CKA0
 3011 FORMAT('   PORTATA DI TRAFILAMENTO    = ',E12.5 ,'(KG/S)'/
     $       '   AMMETTENZA DI TRAFILAMENTO = ',E12.5)
C
C------MEMORIZZAZIONE DATI
C
      DATI(ID2  )=ETA0
      DATI(ID2+1)=CK0
      DATI(ID2+2)=DH0
      DATI(ID2+3)=VEL0
C
C---- RISERVO 3 POSTI PER GLI STATI
C
      DATI(ID2+4)=0.
      DATI(ID2+5)=0.
      DATI(ID2+6)=0.
C___ PORTATA NOMINALE
      DATI(ID2+7)=WIN0
      DATI(ID2+8)=CKA0*SQRT(P0)/W0
      ID2=ID2+8
CCC
CCC------TOLLERANZE
CCC
C !  3) pressione ingresso stadio
CC      PI=XYU(IV1+2)
CC      PPI=PI/100.
CC      IF(PPI.LT.1000.)PPI=1000.
CCC
CC      TOL(3)=PPI*PPI/(P0*P0)
C
C------VETTORE NORMALIZZAZIONI
C
      CNXYU(IV1)=H0
      CNXYU(IV1+1)=W0
      CNXYU(IV1+2)=P0
      CNXYU(IV1+3)=W0*H0
      CNXYU(IV1+4)=P0
      CNXYU(IV1+5)=H0
      CNXYU(IV1+6)=W0
      CNXYU(IV1+7)=W0
      CNXYU(IV1+8)=H0
      CNXYU(IV1+9)=P0
      CNXYU(IV1+10)=1.
      CNXYU(IV1+11)=1.
      CNXYU(IV1+12)=300.
C
      RETURN
      END
C
C*********************************************************************
      SUBROUTINE TRENC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                  IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/SOLV00/JACSI
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      LOGICAL KREGIM,IZ,IAV
      EXTERNAL TREN
C
C------STADIO TURBINA A REAZIONE
C
      GO TO (1,10,20),IFUN
C
C------TOPOLOGIA JACOBIANO
C
    1 CONTINUE
      DO 5 I=1,6
      DO 5 J=1,13
      AJAC(I,J) = 1.
    5 CONTINUE
      RETURN
C
C
C------CALCOLO RESIDUI
C
   10 CALL TREN(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano numerico
C
   20 CONTINUE
C
      NSTATI = 0
      NUSCIT = 6
      NINGRE = 7
      EPS    = 1.E-3
      EPSLIM = 1.E-6
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,TREN)
      RETURN
      END
C*********************************************************************
      SUBROUTINE TREN(IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/SOLV00/JACSI
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL

      DIMENSION XYU(*),DATI(*),RNI(*)
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      LOGICAL KREGIM,IZ,IAV,TREFLOLOG
C
C------STADIO TURBINA A REAZIONE
C
C
C------DECODIFICA DATI
C
   10 ETAD0  = DATI(IPD  )
      CK0    = DATI(IPD+1)
      DH0    = DATI(IPD+2)
      VEL0   = DATI(IPD+3)
C
      ROI    = DATI(IPD+4)
      ROISUPI= DATI(IPD+5)
      ETAAD  = DATI(IPD+6)
C____ PORTATA NOMINALE
      WIN0   = DATI(IPD+7)
      CKA0   = DATI(IPD+8)
C
C------DECODIFICA VARIABILI
C
C !  1) entalpia  uscita   stadio
      HS=XYU(IXYU)
C !  2) portata      "       "
      QU=XYU(IXYU+1)
C !  3) pressione ingresso stadio
      PI=XYU(IXYU+2)
C !  4) potenza meccanica fornita dallo stadio
      POTM=XYU(IXYU+3)
      PSPZ=XYU(IXYU+4)
      HSPZ=XYU(IXYU+5)
      QI=XYU(IXYU+6)
      QSP=XYU(IXYU+7)
      HI=XYU(IXYU+8)
      PU=XYU(IXYU+9)
      IZ=TREFLOLOG(XYU(IXYU+10))
      IAV=TREFLOLOG(XYU(IXYU+11))
      VEL=XYU(IXYU+12)
C
 102  NFL=1
      PID=PI*P0
      HID=HI*H0
      IF(PID.LT.1000.)PID=1000.
      IF(PID.GT.400.E5)PID=400.E5
      IF(HID.GT.4180.E3) HID=4180.E3
      SIN=SHEV(PID,HID,NFL)
      ROI=ROEV(PID,SIN,NFL)
      DATI(IPD+4)=ROI
      ROISUPI=ROI/PI
      DATI(IPD+5)=ROISUPI
C
 101  CONTINUE
C
C
C------CALCOLO RESIDUI IN CONDIZIONI NORMALI DI FUNZIONAMENTO
C
   22 CONTINUE
      NFL=1
      PUD=PU*P0
      PID=PI*P0
      HID=HI*H0
C
C******* PROTEZIONE PER PRESSIONI NEGATIVE
C
      IF(PID.LT.1000.)PID=1000.
      IF(PUD.LT.1000.)PUD=1000.
C
      SIN=SHEV(PID,HID,NFL)
C
      HUIS=HEV(PUD,SIN,NFL)/H0
      RNI(1)=-HS+HI-ETAD0*(HI-HUIS)
      RNI(2)=QU+QSP-QI
      RNI(3)=PI*PI-PU*PU-CK0*QI*ABS(QI)/ROISUPI
      RNI(4)=POTM-QI*(HI-HS)
      RNI(5)=PSPZ-PU
      IF(QSP.LT.1.E-5) THEN
        RNI(6)= HSPZ-HS
      ELSE
        RNI(6)=QSP*(HSPZ-HS)-CKA0*SQRT(PI/ROI)*(HI-HS)
      ENDIF
C
      RETURN
      END
C
C*********************************************************************
      SUBROUTINE TREND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $   XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
C
C*********************************************************************
      LOGICAL FUNCTION TREFLOLOG(A)
      REAL A
      IF (A.GT.0.9.AND.A.LT.1.1) THEN
        TREFLOLOG=.TRUE.
      ELSE IF (A.GT.-0.1.AND.A.LT.0.1) THEN
        TREFLOLOG=.FALSE.
      ELSE
        WRITE(6,*) 'TREFLOLOG:Wrong argument value to logical variable'
        STOP
      ENDIF
      RETURN
      END