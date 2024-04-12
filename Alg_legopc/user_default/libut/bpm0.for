C**********************************************************************
C modulo bpm0.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)bpm0.f	5.2
C**********************************************************************
C--A. Rossi: modulo pompa centrifuga  (primaria,turbopompa,motopompa)
C            derivato da cpom.f ed adattato ad una soluzione di H2O e NaCl
C            (09/jan/2001)
C
      SUBROUTINE BPM0I3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C------POMPA CENTRIFUGA (PRIMARIA,TURBOPOMPA,MOTOPOMPA)
C
      PARAMETER (NV=10)
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOME(NV), TIPO(NV)*2, DESC(NV)*50
      COMMON /BPM001/ IBLOC
      COMMON /BPM002/ IVEL,IOUT
C
      DATA MOD/'BPM0'/
      DATA (NOME(I),TIPO(I),DESC(I),I=1,NV) /
     $'ECIN','US','KINETIC ENERGY OF THE ROTATING MASSES',
     $'OMPM','UA','ROTATIONAL SPEED OF THE PUMP',
     $'HUPM','UA','FLUID ENTHALPY AT THE PUMP OUTLET',
     $'WPOM','UA','FLUID FLOW RATE THROUGH THE PUMP',
     $'PUPM','IN','PRESSURE AT THE PUMP OUTLET',
     $'PIPM','IN','PRESSURE AT THE PUMP INLET',
     $'HIPM','IN','FLUID ENTHALPY AT THE PUMP INLET',
     $'QIPM','IN','POWER ABSORBED BY THE PUMP',
     $'FNAC','IN','NACL MASS FRACTION',
     $'NPOM','IN','NUMBER OF PUMPS IN PARALLEL'/
C
      CALL BPM0I4(IOB,MOD)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      IF (IVEL .EQ. 2) THEN
        WRITE(IFO,3000)NOME(1),IOB,TIPO(1),DESC(1)
        WRITE(IFO,3000)NOME(2),IOB,TIPO(2),DESC(2)
      ENDIF
      WRITE(IFO,3000)NOME(3),IOB,TIPO(3),DESC(3)
      IF (IOUT .EQ. 2) THEN
        WRITE(IFO,3000)NOME(6),IOB,'UA',DESC(6)
        WRITE(IFO,3000)NOME(5),IOB,'IN',DESC(5)
        WRITE(IFO,3000)NOME(4),IOB,'IN',DESC(4)
      ELSE IF (IOUT .EQ. 3) THEN
        WRITE(IFO,3000)NOME(5),IOB,'UA',DESC(5)
        WRITE(IFO,3000)NOME(6),IOB,'IN',DESC(6)
        WRITE(IFO,3000)NOME(4),IOB,'IN',DESC(4)
      ELSE
        WRITE(IFO,3000)NOME(4),IOB,'UA',DESC(4)
        WRITE(IFO,3000)NOME(5),IOB,'IN',DESC(5)
        WRITE(IFO,3000)NOME(6),IOB,'IN',DESC(6)
      ENDIF
      WRITE(IFO,3000)NOME(7),IOB,TIPO(7),DESC(7)
      IF (IVEL .EQ. 2) THEN
        WRITE(IFO,3000)NOME(8),IOB,TIPO(8),DESC(8)
      ELSE
        WRITE(IFO,3000)NOME(2),IOB,TIPO(8),DESC(2)
      ENDIF
      WRITE(IFO,3000)NOME(9),IOB,TIPO(9),DESC(9)
      WRITE(IFO,3000)NOME(10),IOB,TIPO(10),DESC(10)
      RETURN
 2999 FORMAT(A8,'  BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE BPM0I4(IOB,MOD)
      CHARACTER*4 IOB, MOD, IBLOC*8
      COMMON /BPM001/ IBLOC
      COMMON /BPM002/ IVEL,IOUT
      CHARACTER*4 MODU, RISP*1
C
    1 WRITE(6,3001)
 3001 FORMAT(/10X,'CENTRIFUGAL PUMP WITH IMPOSED SPEED [YES/NO] ?')
      READ(5,3000)RISP
      IF (RISP .EQ. 'Y' .OR. RISP .EQ. 'y') THEN
        IVEL = 1
      ELSE IF (RISP .EQ. 'N' .OR. RISP .EQ. 'n') THEN
        IVEL = 2
      ELSE
        GOTO 1
      ENDIF
C
    2 WRITE(6,3002)
 3002 FORMAT(/5X,'GIVE A CHARACTER'
     $ /5X,'- FLOW RATE AS OUTPUT =========> BLANK',
     $ /5X,'- INLET PRESSURE AS OUTPUT ====>   +',
     $ /5X,'- OUTLET PRESSURE AS OUTPUT ===>   -')
      READ(5,3000)RISP
      IF (RISP .EQ. ' ') THEN
        IOUT = 1
        MODU = MOD
      ELSE IF (RISP .EQ. '+') THEN
        IOUT = 2
        MODU = RISP // MOD(1:3)
      ELSE IF (RISP .EQ. '-') THEN
        IOUT = 3
        MODU = RISP // MOD(1:3)
      ELSE
        GOTO 2
      ENDIF
C
      IBLOC = MODU // IOB
      RETURN
 3000 FORMAT(A)
      END
C
C
C
      SUBROUTINE BPM0I2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $ IBLOC1,IBLOC2,IER,CNXYU,TOL)
C
C------POMPA CENTRIFUGA
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
      CHARACTER*1 CWP
      CHARACTER*4 MI,QN1,QN2,OM1,DP1,PT,ET,SPA,RO1,RO2
      CHARACTER*4 GIR1,GIR2,IVAL1,IVAL2,ITP
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      DATA ITP/'TYP'/,MI/'INER'/
      DATA QN1/'QVNO'/,QN2/'M   '/,OM1/'OMNO'/
      DATA DP1/'DPNO'/,PT/'POTN'/,ET/'ETAN'/
      DATA SPA/'    '/,RO1/'DENS'/,RO2/'.   '/
      DATA GIR1/'N.GI'/,GIR2/'RAN.'/
      DATA IVAL1/'VALV'/,IVAL2/' INT'/
      DATA PI/3.141592/,G/9.81/
C
      GO TO(1,10),IFUN
C
C------SCRITTURA SIMBOLI DATI
C
    1 WRITE(14,1000)ITP,SPA,MI,SPA,QN1,QN2
      WRITE(14,1000)OM1,QN2,DP1,QN2,PT,SPA
      WRITE(14,1000)RO1,RO2,GIR1,GIR2,IVAL1,IVAL2
 1000 FORMAT(3(4X,A4,A4,' =',10X,'*'),5X)
      RETURN
C
C------LETTURA DATI E MEMORIZZAZIONE
C
   10 READ(14,1002)
      READ(14,1002)TYP,HIN,QNOM,OMNOM,DPNOM,PNOM,RO,GIRAN,VALV
 1002 FORMAT(3(14X,F10.0,1X),5X)
C
C------DECODIFICA TIPO DI POMPA
C
      IF (NSTATI .GT. 0) THEN
        IHI=2
      ELSE
        IHI=1
      ENDIF
C
      WRITE(CWP,3000)IBLOC1
 3000 FORMAT (A1)
      IF (CWP.EQ.'+') THEN
        IWP=0
      ELSE IF (CWP.EQ.'-') THEN
        IWP=1
      ELSE
        IWP=2
      ENDIF
C
      IF(IHI.EQ.1)WRITE(6,502)'*** IMPOSED SPEED PUMP ***'
      IF(IHI.EQ.2)WRITE(6,502)'*** IMPOSED POWER PUMP ***'
      IF(IWP.EQ.0)WRITE(6,502)'*** INLET PRESSURE AS OUTPUT ***'
      IF(IWP.EQ.1)WRITE(6,502)'*** OUTLET PRESSURE AS OUTPUT ***'
      IF(IWP.EQ.2)WRITE(6,502)'*** FLOW RATE AS OUTPUT ***'
  502 FORMAT(/14X,A)
C
C------CALCOLO DATI DI LAVORO
C
      IF(GIRAN.LE.0.)GIRAN=1.
C___  VALV = 1 DICE CHE LA POMPA COMPRENDE LA VALVOLA CHE SI TROVA
C              A MONTE DELLA POMPA .
      IF(VALV.NE.0.)VALV=1.
      ETANOM=0.85
      IF(PNOM.GT.0.)ETANOM=QNOM*DPNOM/PNOM
      IF(RO.EQ.0.) RO=1000.
C
      DH=DPNOM/RO/G/GIRAN
C
      ECINOM=HIN*OMNOM**2.*.5
      GIRI=OMNOM/2./PI*60.
      GCAR=3.65*GIRI*QNOM**.5/(DH**(3./4.))
      AMPMP=2000.*QNOM
      WRITE(6,1021) GCAR
 1021 FORMAT(/14X,'*** CHARACTERISTIC NUMBER OF ROUND: ',
     $       F8.2,' ***'/)
      CNOM=PNOM/OMNOM
      IF(PNOM.NE.0.)GO TO 167
      CNOM=QNOM*DPNOM/(OMNOM*ETANOM)
 167  CONTINUE
C
C------MEMORIZZAZIONE DEI DATI
C
      DATI(ID2)=IHI
      DATI(ID2+1)=IWP
      DATI(ID2+2)=TYP
      DATI(ID2+3)=HIN
      DATI(ID2+4)=QNOM
      DATI(ID2+5)=OMNOM
      DATI(ID2+6)=DPNOM
      DATI(ID2+7)=PNOM
      DATI(ID2+8)=ETANOM
      DATI(ID2+9)=ECINOM
      DATI(ID2+10)=GCAR
      DATI(ID2+11)=AMPMP
      DATI(ID2+12)=CNOM
      DATI(ID2+16)=.004*CNOM
      DATI(ID2+17)=VALV
      ID2=ID2+17
C
C------NORMALIZZAZIONE
C
      OM0=PI*2.*50.
      GO TO (50,60), IHI
C
   50 CNXYU(IV1)=H0
      CNXYU(IV1+1)=P0
      IF(IWP.EQ.2)CNXYU(IV1+1)=W0
      CNXYU(IV1+2)=P0
      CNXYU(IV1+3)=W0
      IF(IWP.EQ.2)CNXYU(IV1+3)=P0
      CNXYU(IV1+4)=H0
      CNXYU(IV1+5)=OM0
      CNXYU(IV1+6)=1.
      CNXYU(IV1+7)=1.
      GO TO 70
C
   60 CNXYU(IV1)=1.
      CNXYU(IV1+1)=OM0
      CNXYU(IV1+2)=H0
      CNXYU(IV1+3)=P0
      IF(IWP.EQ.2) CNXYU(IV1+3)=W0
      CNXYU(IV1+4)=P0
      CNXYU(IV1+5)=W0
      IF(IWP.EQ.2) CNXYU(IV1+5)=P0
      CNXYU(IV1+6)=H0
      CNXYU(IV1+7)=H0*W0
      CNXYU(IV1+8)=1.
      CNXYU(IV1+9)=1.
C
C------TOLLERANZE STANDARD(1.E-4)
C
   70 RETURN
      END
C
      SUBROUTINE BPM0C1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                  IBLOC1,IBLOC2)
C
C------POMPA CENTRIFUGA
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/IFAN/IFAN
      REAL NPO                                                          !SNGL
C      DOUBLE PRECISION NPO                                              !DBLE
      IFAN=IFUN
      GO TO (1,10,20),IFUN
    1 IHI=DATI(IPD)
      GO TO (2,3), IHI
C
C------TOPOLOGIA JACOBIANO
C
2     CONTINUE      ! IMPOSED SPEED
      AJAC(1,1)=1.
      DO 5 I=1,8
       AJAC(2,I)=1.
    5 CONTINUE
      RETURN
C
3     CONTINUE       ! calculated speed
      AJAC(3,3)=1.
      DO 6 I=2,9
       AJAC(1,I)=1.
       AJAC(4,I)=1.
    6 CONTINUE
      AJAC(1,1)=1.
      AJAC(1,8)=1.
      AJAC(2,1)=1.
      AJAC(2,2)=1.
      DO 7 I=1,4
       AJAC(I,10)=1.
    7 CONTINUE
      RETURN
C
C------CALCOLO RESIDUI  E DERIVATE
C
  10  CALL PMPDEC_B0(XYU,IXYU,ECIN,OM,HV,PM,PV,Q,HM,WM,FNAC,
     $            DATI,IPD,IHI,IWP,TYP,HIN,NPO,IBLOC1,IBLOC2,
     $            QNOM,OMNOM,DPNOM,CNOM,GCAR,ECINOM,ETANOM,PERD,VALV)
      CALL PMPDR_B0(PM,PV,HM,HV,Q,OM,ECIN,ETANOM,FNAC,
     $           TYP,WM,HIN,RNI,NPO,PERD,VALV,
     $           GCAR,QNOM,OMNOM,DPNOM,CNOM,IHI,ECINOM,DATI,IPD)
      RETURN
C
C------CALCOLO DELLLO JACOBIANO
C
   20 CALL PMPJC_B0(AJAC,MX5,IXYU,XYU,DATI,IPD,RNI,IFUN,
     $           IBLOC1,IBLOC2)
      RETURN
      END
C
      SUBROUTINE PMPDEC_B0(XYU,IXYU,ECIN,OM,HV,PM,PV,Q,HM,WM,FNAC,
     $                  DATI,IPD,IHI,IWP,TYP,HIN,NPO,IBL1,IBL2,
     $                  QNOM,OMNOM,DPNOM,CNOM,GCAR,ECINOM,ETANOM,PERD,
     $                  VALV)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION XYU(*),DATI(*)
      REAL NPO                                                          !SNGL
C      DOUBLE PRECISION NPO                                              !DBLE
C
      IHI   =DATI(IPD)
      IWP   =DATI(IPD+1)
      TYP   =DATI(IPD+2)
      HIN   =DATI(IPD+3)
      QNOM  =DATI(IPD+4)
      OMNOM =DATI(IPD+5)
      DPNOM =DATI(IPD+6)
      PNOM  =DATI(IPD+7)
      ETANOM=DATI(IPD+8)
      ECINOM=DATI(IPD+9)
      GCAR  =DATI(IPD+10)
      CNOM  =DATI(IPD+12)
      PERD  =DATI(IPD+16)
      VALV  =DATI(IPD+17)
C
    1 GO TO (10,11), IHI
C
   10 HV   =XYU(IXYU)
      PM   =XYU(IXYU+1)
      PV   =XYU(IXYU+2)
      Q    =XYU(IXYU+3)
      HM   =XYU(IXYU+4)
      OM   =XYU(IXYU+5)
      FNAC =XYU(IXYU+6)
      NPO  =XYU(IXYU+7)
      IF(NPO.LT..99)WRITE(6,3000)IBL1,IBL2
 3000 FORMAT(//' ********WARNING********'/
     $ ' THE PUMP ',2A4,' HAS  1.>NPO>0. '//)
      IF(NPO.GT.1.E-3)GO TO 13
      WRITE(6,3001)IBL1,IBL2
 3001 FORMAT(//' ********ERROR********'/
     $ ' LA POMPA ',2A4, ' HA NPO< 1.E-3'/
     $ ' *********STOP  ESECUTION*******'/)
      STOP
  13  IF(IWP.EQ.0)GO TO 20
      IF(IWP.EQ.2)GO TO 15
      PV   =XYU(IXYU+1)
      PM   =XYU(IXYU+2)
      GO TO 20
   15 Q    =XYU(IXYU+1)
      PM   =XYU(IXYU+3)
      GO TO 20
C
   11 ECIN =XYU(IXYU)
      OM   =XYU(IXYU+1)
      HV   =XYU(IXYU+2)
      PM   =XYU(IXYU+3)
      PV   =XYU(IXYU+4)
      Q    =XYU(IXYU+5)
      HM   =XYU(IXYU+6)
      WM   =XYU(IXYU+7)
      FNAC =XYU(IXYU+8)
      NPO  =XYU(IXYU+9)
      IF(NPO.LT..99)WRITE(6,3000)IBL1,IBL2
      IF(NPO.GT.1.E-3)GO TO 17
      WRITE(6,3001)IBL1,IBL2
      STOP
  17  IF(IWP.EQ.0)GO TO 20
      IF(IWP.EQ.2)GO TO 16
      PV   =XYU(IXYU+3)
      PM   =XYU(IXYU+4)
      GO TO 20
   16 Q    =XYU(IXYU+3)
      PM   =XYU(IXYU+5)
   20 CONTINUE
      RETURN
      END
C
      SUBROUTINE PMPDR_B0(PMN,PVN,HMN,HVN,QN,OMN,ECINN,ETANOM,FNAC,
     $                 TYP,WMN,HIN,RNI,NPO,PERD,VALV,
     $                 GCAR,QNOM,OMNOM,DPNOM,CNOM,IHI,ECINOM,DATI,IPD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      REAL NPO                                                          !SNGL
C      DOUBLE PRECISION NPO                                              !DBLE
      DIMENSION RNI(*),DATI(*)
      DATA NFL/1/,OM0/314.1592/
      PM  =PMN*P0
      PV  =PVN*P0
      Q   =QN*W0
      HM  =HMN*H0
      HV  =HVN*H0
      OM  =OMN*OM0
      Q1P =Q/NPO
      IF(KREGIM) GO TO 526
      IF(ITERT.GT.0)GO TO 527
Car---09/jan/2001
Car526   SM  =SHEV(PM,HM,NFL)
Car      RO  =ROEV(PM,SM,NFL)
Car      DATI(IPD+15)=RO
Car---09/jan/2001-------------fine
526   CONTINUE   ! calcolo ro
      CALL T_FOR(PM,HM,FNAC,TM)     ! SM  =SHEV(PM,HM,NFL)
      CALL ROC_FOR(FNAC,TM,PM,RO)   ! RO  =ROEV(PM,SM,NFL)
      DATI(IPD+15)=RO
527   CONTINUE
      RO=DATI(IPD+15)
      Q1PV=Q1P/RO
C
C------CALCOLO RESIDUI
C
      IF(TYP.LE.0.) CALL PMPDPC_B0(GCAR,QNOM,OMNOM,DPNOM,CNOM,
     $                          Q1PV,OM,DP,CRES)
      IF(TYP.GT.0.) CALL DPU_B0(TYP,QNOM,OMNOM,DPNOM,CNOM,ETANOM,
     $                       Q1PV,RO,OM,DP,CRES)
      WR=CRES*OM*NPO
      GO TO (16,17),IHI
C
 16   IF(KREGIM)GO TO 1000
      CALL CPOTERB0(DATI,IPD,Q,HM,HV,WR,PM,PV,HVT,FNAC)
      RNI(1)=(HV-HVT)/H0
      GO TO 1010
C
C     CALCOLO REGIME PERMANENTE
C
1000  IF(Q.GT.1.E-3)GO TO 1001
C
C______  se a regime la portata e' nulla l'entalpia a valle
C______  e' uguale a quella a monte
C
      RNI(1)=(HV-HM)/H0
      GO TO 1020
C
1001  RNI(1)=(WR-Q*(HV-HM))/W0/H0
Car
Car1020  DATI(IPD+13)=SHEV(PV,HV,1)
Car   
1020  CALL T_FOR(PV,HV,FNAC,TV)
      CALL S_FOR(TV,FNAC,SV)
      DATI(IPD+13)=SV              ! SHEV(PV,HV,1)
1010  CONTINUE
C
C____ SE LA POMPA E` FERMA ( OM=0 ) E VALV =1. L'EQUAZIONE E`  W=0.
C____ ALTRIMENTI  L'EQUAZIONE E`  PV-PM=DP
C
      IF(OM.LT.1.E-3.AND.VALV.EQ.1.) THEN
        RNI(2)=-Q/W0
      ELSE
        RNI(2)=(PV-PM-DP)/P0
      ENDIF
      RETURN
C
   17 WM=WMN*W0*H0
      ECIN=ECINN*ECINOM
      RNI(1)=(WM-WR-PERD*OM)/ECINOM/NPO
      RNI(2)=(HIN*OM*ABS(OM)/2.-ECIN)/W0/H0
      IF(KREGIM)GO TO 2000
      CALL CPOTERB0(DATI,IPD,Q,HM,HV,WR,PM,PV,HVT,FNAC)
      RNI(3)=(HV-HVT)/H0
      GO TO 2010
C
C     CALCOLO REGIME PERMANENTE
C
 2000 IF(Q.GT.1.E-3)GO TO 2001
C
C______  se a regime la portata e' nulla l'entalpia a valle
C______  e' uguale a quella a monte
C
      RNI(3)=(HV-HM)/H0
      GO TO 2020
2001  RNI(3)=(WR-Q*(HV-HM))/W0/H0
Car   
Car2020  DATI(IPD+13)=SHEV(PV,HV,1)
Car   
2020  CALL T_FOR(PV,HV,FNAC,TV)
      CALL S_FOR(TV,FNAC,SV)
      DATI(IPD+13)=SV              ! SHEV(PV,HV,1)
2010  CONTINUE
C
C____ SE LA POMPA E` FERMA ( OM=0 ) E VALV =1. L'EQUAZIONE E`  W=0.
C____ ALTRIMENTI  L'EQUAZIONE E`  PV-PM=DP
C
      IF(OM.LE.1.E-3.AND.VALV.EQ.1.) THEN
        RNI(4)=-Q/W0
      ELSE
        RNI(4)=(PV-PM-DP)/P0
      ENDIF
      RETURN
      END
C
      SUBROUTINE PMPJC_B0(AJAC,MX5,IXYU,XYU,DATI,IPD,RNI,IFUN,
     $                 IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      DIMENSION G1(4),RNI(*),AJAC(MX5,*),DATI(*),VAR(9),XYU(*)
      REAL NPO                                                          !SNGL
C      DOUBLE PRECISION NPO                                              !DBLE
C
C------CALCOLO JACOBIANO NUMERICO
C
      CALL PMPDEC_B0(XYU,IXYU,ECIN,OM,HV,PM,PV,Q,HM,WM,FNAC,
     $            DATI,IPD,IHI,IWP,TYP,HIN,NPO,IBL1,IBL2,
     $            QNOM,OMNOM,DPNOM,CNOM,GCAR,ECINOM,ETANOM,PERD,
     $            VALV)
      CALL PMPDR_B0(PM,PV,HM,HV,Q,OM,ECIN,ETANOM,FNAC,
     $           TYP,WM,HIN,RNI,NPO,PERD,VALV,
     $           GCAR,QNOM,OMNOM,DPNOM,CNOM,IHI,ECINOM,DATI,IPD)
C
      GO TO (1,2), IHI
C
    1 DO 10 I=1,2
      G1(I)=RNI(I)
   10 CONTINUE
      DO 30 I=1,8
      EPS=XYU(IXYU+I-1)*.001
      IF(ABS(EPS).LT.1.E-4)EPS=1.E-4
      DO 15 J=1,8
      VAR(J)=XYU(IXYU+J-1)
      IF(J.EQ.I)VAR(J)=VAR(J)+EPS
   15 CONTINUE
      CALL PMPDEC_B0(VAR,1,ECIN,OM,HV,PM,PV,Q,HM,WM,FNAC,
     $            DATI,IPD,IHI,IWP,TYP,HIN,NPO,IBL1,IBL2,
     $            QNOM,OMNOM,DPNOM,CNOM,GCAR,ECINOM,ETANOM,PERD,
     $            VALV)
      CALL PMPDR_B0(PM,PV,HM,HV,Q,OM,ECIN,ETANOM,FNAC,
     $           TYP,WM,HIN,RNI,NPO,PERD,VALV,
     $           GCAR,QNOM,OMNOM,DPNOM,CNOM,IHI,ECINOM,DATI,IPD)
C
      DO 25 J=1,2
      AJAC(J,I)=-(RNI(J)-G1(J))/EPS
   25 CONTINUE
   30 CONTINUE
      IF(.NOT.KREGIM) AJAC(1,1)=-1.
      RETURN
C
    2 DO 11 I=1,4
      G1(I)=RNI(I)
   11 CONTINUE
      DO 31 I=1,10
      EPS=XYU(IXYU+I-1)*.001
      IF(ABS(EPS).LT.1.E-4)EPS=1.E-4
      DO 16 J=1,10
      VAR(J)=XYU(IXYU+J-1)
      IF(J.EQ.I)VAR(J)=VAR(J)+EPS
   16 CONTINUE
      CALL PMPDEC_B0(VAR,1,ECIN,OM,HV,PM,PV,Q,HM,WM,FNAC,
     $            DATI,IPD,IHI,IWP,TYP,HIN,NPO,IBL1,IBL2,
     $            QNOM,OMNOM,DPNOM,CNOM,GCAR,ECINOM,ETANOM,PERD,
     $            VALV)
      CALL PMPDR_B0(PM,PV,HM,HV,Q,OM,ECIN,ETANOM,FNAC,
     $           TYP,WM,HIN,RNI,NPO,PERD,VALV,
     $           GCAR,QNOM,OMNOM,DPNOM,CNOM,IHI,ECINOM,DATI,IPD)
C
      AJAC(1,I)=(RNI(1)-G1(1))/EPS
      DO 26 J=2,4
      AJAC(J,I)=-(RNI(J)-G1(J))/EPS
   26 CONTINUE
   31 CONTINUE
      IF(.NOT.KREGIM) AJAC(3,3)=-1.
      RETURN
      END
C
      SUBROUTINE PMPDPC_B0(GCAR,QNOM,OMNOM,DPNOM,CNOM,Q,OM,DP,CRES)
C
C ----------------- PARAMETRI FISICI --------------------
C     ITYP = 1 : N. GIRI CAR. = 96
C            2 : N. GIRI CAR. = 142
C            3 : N. GIRI CAR. = 353
C            4 : N. GIRI CAR. = 380
C            5 : N. GIRI CAR. = 447
C     QNOM = PORTATA NOMINALE
C     OMNOM = NUMERO DI GIRI NOMINALE
C     DPNOM = PREVALENZA NOMINALE
C     CNOM = COPPIA RESISTENTE NOMINALE
C ----------------- DATI DI INGRESSO ----------------------
C     Q     = PORTATA ATTUALE
C     OM    = NUMERO DI GIRI ATTUALE
C ----------------- DATI DI USCITA ------------------------
C     DP    = PREVALENZA CALCOLATA
C     CRES  = COPPIA RESISTENTE CALCOLATA
C
      DOUBLE PRECISION RQ,ROM,ALFAR,ALFAG,ALF,RDP,RCRES,RMOLT,H,T       !SNGL
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION ACURV(5),H(181,5),T(181,5)
      DATA ACURV/96.,142.,353.,380.,447./
C ------ CURVA DI PREV. -  N. GIRI CARATT. (UNITA' SI) = 96
      DATA (H(K,1),K=1,45) /
     .     -.758000D+00  ,  -.736647D+00  ,  -.715295D+00  ,
     .     -.692664D+00  ,  -.662472D+00  ,  -.632280D+00  ,
     .     -.599747D+00  ,  -.562765D+00  ,  -.525783D+00  ,
     .     -.431407D+00  ,  -.306144D+00  ,  -.185579D+00  ,
     .     -.107793D+00  ,  -.300076D-01  ,  0.487863D-01  ,
     .     0.127978D+00  ,  0.191600D+00  ,  0.240715D+00  ,
     .     0.289413D+00  ,  0.337701D+00  ,  0.380312D+00  ,
     .     0.420197D+00  ,  0.473376D+00  ,  0.517413D+00  ,
     .     0.552285D+00  ,  0.586710D+00  ,  0.620818D+00  ,
     .     0.654289D+00  ,  0.688044D+00  ,  0.722085D+00  ,
     .     0.758193D+00  ,  0.796519D+00  ,  0.832210D+00  ,
     .     0.861223D+00  ,  0.890236D+00  ,  0.927622D+00  ,
     .     0.965927D+00  ,  0.997262D+00  ,  0.101565D+01  ,
     .     0.103404D+01  ,  0.105850D+01  ,  0.108616D+01  ,
     .     0.111382D+01  ,  0.112207D+01  ,  0.112703D+01  /
      DATA (H(K,1),K=46,90) /
     .     0.113200D+01  ,  0.114507D+01  ,  0.115813D+01  ,
     .     0.117085D+01  ,  0.118146D+01  ,  0.119208D+01  ,
     .     0.119893D+01  ,  0.119860D+01  ,  0.119827D+01  ,
     .     0.118896D+01  ,  0.117482D+01  ,  0.115903D+01  ,
     .     0.112827D+01  ,  0.109750D+01  ,  0.107543D+01  ,
     .     0.105678D+01  ,  0.102533D+01  ,  0.981949D+00  ,
     .     0.940810D+00  ,  0.901887D+00  ,  0.878546D+00  ,
     .     0.862872D+00  ,  0.842967D+00  ,  0.828650D+00  ,
     .     0.819939D+00  ,  0.789419D+00  ,  0.764105D+00  ,
     .     0.749589D+00  ,  0.728594D+00  ,  0.701032D+00  ,
     .     0.679316D+00  ,  0.663873D+00  ,  0.644581D+00  ,
     .     0.615536D+00  ,  0.586492D+00  ,  0.561537D+00  ,
     .     0.537031D+00  ,  0.515239D+00  ,  0.498488D+00  ,
     .     0.481737D+00  ,  0.464904D+00  ,  0.448028D+00  ,
     .     0.431153D+00  ,  0.417415D+00  ,  0.404207D+00  /
      DATA (H(K,1),K=91,135) /
     .     0.391000D+00  ,  0.384443D+00  ,  0.377886D+00  ,
     .     0.370928D+00  ,  0.361598D+00  ,  0.352268D+00  ,
     .     0.343770D+00  ,  0.336856D+00  ,  0.329943D+00  ,
     .     0.324903D+00  ,  0.320873D+00  ,  0.316193D+00  ,
     .     0.305596D+00  ,  0.294999D+00  ,  0.289095D+00  ,
     .     0.285042D+00  ,  0.282950D+00  ,  0.282683D+00  ,
     .     0.280143D+00  ,  0.275361D+00  ,  0.273216D+00  ,
     .     0.272412D+00  ,  0.278801D+00  ,  0.281007D+00  ,
     .     0.279017D+00  ,  0.281349D+00  ,  0.286245D+00  ,
     .     0.296287D+00  ,  0.305725D+00  ,  0.314550D+00  ,
     .     0.324400D+00  ,  0.335349D+00  ,  0.346876D+00  ,
     .     0.359865D+00  ,  0.372854D+00  ,  0.383273D+00  ,
     .     0.393411D+00  ,  0.402872D+00  ,  0.411079D+00  ,
     .     0.419286D+00  ,  0.426903D+00  ,  0.434211D+00  ,
     .     0.441519D+00  ,  0.443002D+00  ,  0.443501D+00  /
      DATA (H(K,1),K=136,181) /
     .     0.444000D+00  ,  0.420615D+00  ,  0.397231D+00  ,
     .     0.367876D+00  ,  0.303203D+00  ,  0.238530D+00  ,
     .     0.171058D+00  ,  0.982656D-01  ,  0.254731D-01  ,
     .     -.305332D-01  ,  -.775030D-01  ,  -.122725D+00  ,
     .     -.152018D+00  ,  -.181311D+00  ,  -.210011D+00  ,
     .     -.238476D+00  ,  -.265352D+00  ,  -.290745D+00  ,
     .     -.317164D+00  ,  -.344595D+00  ,  -.369194D+00  ,
     .     -.392407D+00  ,  -.417457D+00  ,  -.441675D+00  ,
     .     -.465056D+00  ,  -.491822D+00  ,  -.516464D+00  ,
     .     -.536763D+00  ,  -.556427D+00  ,  -.575448D+00  ,
     .     -.593081D+00  ,  -.609225D+00  ,  -.621914D+00  ,
     .     -.625848D+00  ,  -.629783D+00  ,  -.639283D+00  ,
     .     -.649392D+00  ,  -.655314D+00  ,  -.653458D+00  ,
     .     -.651602D+00  ,  -.660817D+00  ,  -.675857D+00  ,
     .     -.690896D+00  ,  -.712522D+00  ,  -.735261D+00  ,
     .     -.758000D+00  /
C---- CURVA DI COPPIA -  N. GIRI CARATT. (UNITA' SI) = 96
      DATA (T(K,1),K=1,44) /
     .                      -.250000D+00  ,  -.227982D+00  ,
     .     -.205963D+00  ,  -.177960D+00  ,  -.114557D+00  ,
     .     -.511536D-01  ,  -.838486D-02  ,  -.481664D-02  ,
     .     -.124842D-02  ,  0.364676D-01  ,  0.925607D-01  ,
     .     0.147395D+00  ,  0.190762D+00  ,  0.234130D+00  ,
     .     0.292163D+00  ,  0.355982D+00  ,  0.417764D+00  ,
     .     0.477649D+00  ,  0.516070D+00  ,  0.533323D+00  ,
     .     0.531769D+00  ,  0.520914D+00  ,  0.506978D+00  ,
     .     0.506965D+00  ,  0.520914D+00  ,  0.541972D+00  ,
     .     0.562437D+00  ,  0.581618D+00  ,  0.599226D+00  ,
     .     0.615240D+00  ,  0.634336D+00  ,  0.656738D+00  ,
     .     0.678695D+00  ,  0.699525D+00  ,  0.720355D+00  ,
     .     0.741718D+00  ,  0.763140D+00  ,  0.783540D+00  ,
     .     0.802042D+00  ,  0.820545D+00  ,  0.831976D+00  ,
     .     0.839688D+00  ,  0.847400D+00  ,  0.851057D+00  /
      DATA (T(K,1),K=45,89) /
     .     0.854028D+00  ,  0.857000D+00  ,  0.854028D+00  ,
     .     0.851057D+00  ,  0.848989D+00  ,  0.852267D+00  ,
     .     0.855544D+00  ,  0.852893D+00  ,  0.838974D+00  ,
     .     0.825055D+00  ,  0.815480D+00  ,  0.808244D+00  ,
     .     0.799361D+00  ,  0.775462D+00  ,  0.751563D+00  ,
     .     0.741701D+00  ,  0.737379D+00  ,  0.727603D+00  ,
     .     0.712747D+00  ,  0.705402D+00  ,  0.705467D+00  ,
     .     0.698833D+00  ,  0.688918D+00  ,  0.683309D+00  ,
     .     0.687153D+00  ,  0.700477D+00  ,  0.718078D+00  ,
     .     0.732113D+00  ,  0.738877D+00  ,  0.746904D+00  ,
     .     0.756211D+00  ,  0.769576D+00  ,  0.787295D+00  ,
     .     0.803892D+00  ,  0.817646D+00  ,  0.831399D+00  ,
     .     0.850353D+00  ,  0.869878D+00  ,  0.883584D+00  ,
     .     0.886485D+00  ,  0.889385D+00  ,  0.884757D+00  ,
     .     0.876168D+00  ,  0.867579D+00  ,  0.837177D+00  /
      DATA (T(K,1),K=90,134) /
     .     0.803088D+00  ,  0.769000D+00  ,  0.761826D+00  ,
     .     0.754652D+00  ,  0.746754D+00  ,  0.734578D+00  ,
     .     0.722402D+00  ,  0.708352D+00  ,  0.690744D+00  ,
     .     0.673135D+00  ,  0.643977D+00  ,  0.608601D+00  ,
     .     0.573439D+00  ,  0.540220D+00  ,  0.507000D+00  ,
     .     0.472493D+00  ,  0.437477D+00  ,  0.411847D+00  ,
     .     0.394962D+00  ,  0.361473D+00  ,  0.311601D+00  ,
     .     0.274186D+00  ,  0.242876D+00  ,  0.204310D+00  ,
     .     0.170180D+00  ,  0.140499D+00  ,  0.118051D+00  ,
     .     0.954848D-01  ,  0.725951D-01  ,  0.478280D-01  ,
     .     0.211582D-01  ,  0.398572D-02  ,  -.299491D-02  ,
     .     -.121709D-01  ,  -.269087D-01  ,  -.416466D-01  ,
     .     -.651455D-01  ,  -.896055D-01  ,  -.113282D+00  ,
     .     -.135503D+00  ,  -.157725D+00  ,  -.184609D+00  ,
     .     -.213947D+00  ,  -.243284D+00  ,  -.277027D+00  /
      DATA (T(K,1),K=135,181) /
     .     -.311514D+00  ,  -.346001D+00  ,  -.374968D+00  ,
     .     -.403935D+00  ,  -.432941D+00  ,  -.462180D+00  ,
     .     -.491419D+00  ,  -.518144D+00  ,  -.540094D+00  ,
     .     -.562044D+00  ,  -.582492D+00  ,  -.602131D+00  ,
     .     -.621994D+00  ,  -.643898D+00  ,  -.665802D+00  ,
     .     -.684485D+00  ,  -.701896D+00  ,  -.712306D+00  ,
     .     -.716191D+00  ,  -.728378D+00  ,  -.748755D+00  ,
     .     -.758727D+00  ,  -.763602D+00  ,  -.775195D+00  ,
     .     -.779605D+00  ,  -.776812D+00  ,  -.772079D+00  ,
     .     -.773780D+00  ,  -.788543D+00  ,  -.781011D+00  ,
     .     -.750887D+00  ,  -.721412D+00  ,  -.692634D+00  ,
     .     -.664674D+00  ,  -.638789D+00  ,  -.612904D+00  ,
     .     -.589840D+00  ,  -.567085D+00  ,  -.541506D+00  ,
     .     -.510681D+00  ,  -.479857D+00  ,  -.441442D+00  ,
     .     -.399033D+00  ,  -.356625D+00  ,  -.320388D+00  ,
     .     -.285194D+00  ,  -.250000D+00  /
C ------ CURVA DI PREV. -  N. GIRI CARATT. (UNITA' SI) = 142
      DATA (H(K,2),K=1,45) /
     .     -.562500D+00  ,  -.525355D+00  ,  -.488209D+00  ,
     .     -.451981D+00  ,  -.421177D+00  ,  -.390373D+00  ,
     .     -.357687D+00  ,  -.321425D+00  ,  -.285164D+00  ,
     .     -.247527D+00  ,  -.209149D+00  ,  -.170075D+00  ,
     .     -.124662D+00  ,  -.792486D-01  ,  -.447517D-01  ,
     .     -.145619D-01  ,  0.600252D-01  ,  0.175982D+00  ,
     .     0.263599D+00  ,  0.323269D+00  ,  0.376158D+00  ,
     .     0.425700D+00  ,  0.475212D+00  ,  0.521079D+00  ,
     .     0.563292D+00  ,  0.605732D+00  ,  0.646860D+00  ,
     .     0.685330D+00  ,  0.724929D+00  ,  0.765674D+00  ,
     .     0.805458D+00  ,  0.844213D+00  ,  0.881062D+00  ,
     .     0.913086D+00  ,  0.945110D+00  ,  0.976267D+00  ,
     .     0.100733D+01  ,  0.103768D+01  ,  0.106672D+01  ,
     .     0.109576D+01  ,  0.112273D+01  ,  0.114860D+01  ,
     .     0.117448D+01  ,  0.119373D+01  ,  0.121187D+01  /
      DATA (H(K,2),K=46,90) /
     .     0.123000D+01  ,  0.123961D+01  ,  0.124921D+01  ,
     .     0.125754D+01  ,  0.125832D+01  ,  0.125910D+01  ,
     .     0.125691D+01  ,  0.124909D+01  ,  0.124127D+01  ,
     .     0.123926D+01  ,  0.124037D+01  ,  0.123933D+01  ,
     .     0.121860D+01  ,  0.119787D+01  ,  0.118694D+01  ,
     .     0.117988D+01  ,  0.116044D+01  ,  0.112947D+01  ,
     .     0.110788D+01  ,  0.109554D+01  ,  0.108134D+01  ,
     .     0.106622D+01  ,  0.105208D+01  ,  0.102274D+01  ,
     .     0.978152D+00  ,  0.995847D+00  ,  0.100045D+01  ,
     .     0.977830D+00  ,  0.956587D+00  ,  0.936743D+00  ,
     .     0.919788D+00  ,  0.905934D+00  ,  0.886438D+00  ,
     .     0.852647D+00  ,  0.818857D+00  ,  0.803555D+00  ,
     .     0.790281D+00  ,  0.776292D+00  ,  0.760978D+00  ,
     .     0.745664D+00  ,  0.729311D+00  ,  0.712412D+00  ,
     .     0.695513D+00  ,  0.677171D+00  ,  0.658585D+00  /
      DATA (H(K,2),K=91,135) /
     .     0.640000D+00  ,  0.637781D+00  ,  0.635562D+00  ,
     .     0.631230D+00  ,  0.614399D+00  ,  0.597567D+00  ,
     .     0.583096D+00  ,  0.573111D+00  ,  0.563127D+00  ,
     .     0.557618D+00  ,  0.554518D+00  ,  0.550075D+00  ,
     .     0.533397D+00  ,  0.516719D+00  ,  0.498499D+00  ,
     .     0.479670D+00  ,  0.482459D+00  ,  0.505391D+00  ,
     .     0.510500D+00  ,  0.498025D+00  ,  0.494578D+00  ,
     .     0.495597D+00  ,  0.498531D+00  ,  0.507332D+00  ,
     .     0.522017D+00  ,  0.519825D+00  ,  0.517778D+00  ,
     .     0.516220D+00  ,  0.520876D+00  ,  0.531830D+00  ,
     .     0.541908D+00  ,  0.551047D+00  ,  0.558950D+00  ,
     .     0.563722D+00  ,  0.568494D+00  ,  0.578632D+00  ,
     .     0.589359D+00  ,  0.598306D+00  ,  0.603949D+00  ,
     .     0.609593D+00  ,  0.621814D+00  ,  0.637497D+00  ,
     .     0.653179D+00  ,  0.637337D+00  ,  0.616168D+00  /
      DATA (H(K,2),K=136,181) /
     .     0.595000D+00  ,  0.580107D+00  ,  0.565215D+00  ,
     .     0.550511D+00  ,  0.536920D+00  ,  0.523328D+00  ,
     .     0.496497D+00  ,  0.444502D+00  ,  0.392507D+00  ,
     .     0.336925D+00  ,  0.279412D+00  ,  0.222056D+00  ,
     .     0.166139D+00  ,  0.110222D+00  ,  0.636237D-01  ,
     .     0.207023D-01  ,  -.351865D-01  ,  -.103157D+00  ,
     .     -.203105D+00  ,  -.334600D+00  ,  -.400889D+00  ,
     .     -.435052D+00  ,  -.478331D+00  ,  -.507514D+00  ,
     .     -.522563D+00  ,  -.537172D+00  ,  -.556874D+00  ,
     .     -.586900D+00  ,  -.608044D+00  ,  -.620186D+00  ,
     .     -.631193D+00  ,  -.640982D+00  ,  -.649877D+00  ,
     .     -.656507D+00  ,  -.663138D+00  ,  -.667185D+00  ,
     .     -.670948D+00  ,  -.673354D+00  ,  -.673236D+00  ,
     .     -.673118D+00  ,  -.663853D+00  ,  -.649776D+00  ,
     .     -.635699D+00  ,  -.612344D+00  ,  -.587422D+00  ,
     .     -.562500D+00  /
C ----CURVA DI COPPIA -  N. GIRI CARATT. (UNITA' SI) = 142
      DATA (T(K,2),K=1,44) /
     .                      -.488600D+00  ,  -.433125D+00  ,
     .     -.377650D+00  ,  -.322261D+00  ,  -.267378D+00  ,
     .     -.212494D+00  ,  -.158853D+00  ,  -.107572D+00  ,
     .     -.562906D-01  ,  -.946343D-02  ,  0.349666D-01  ,
     .     0.792958D-01  ,  0.122707D+00  ,  0.166118D+00  ,
     .     0.211692D+00  ,  0.258121D+00  ,  0.298873D+00  ,
     .     0.334337D+00  ,  0.364536D+00  ,  0.389541D+00  ,
     .     0.423056D+00  ,  0.460704D+00  ,  0.486890D+00  ,
     .     0.513069D+00  ,  0.539241D+00  ,  0.564497D+00  ,
     .     0.584222D+00  ,  0.592752D+00  ,  0.604029D+00  ,
     .     0.618089D+00  ,  0.625015D+00  ,  0.624284D+00  ,
     .     0.618817D+00  ,  0.601349D+00  ,  0.583882D+00  ,
     .     0.582917D+00  ,  0.583762D+00  ,  0.580830D+00  ,
     .     0.570880D+00  ,  0.560930D+00  ,  0.548724D+00  ,
     .     0.535330D+00  ,  0.521936D+00  ,  0.514008D+00  /
      DATA (T(K,2),K=45,89) /
     .     0.507004D+00  ,  0.500000D+00  ,  0.472364D+00  ,
     .     0.444729D+00  ,  0.419121D+00  ,  0.405510D+00  ,
     .     0.391900D+00  ,  0.378785D+00  ,  0.366614D+00  ,
     .     0.354443D+00  ,  0.350335D+00  ,  0.350567D+00  ,
     .     0.350657D+00  ,  0.349458D+00  ,  0.348259D+00  ,
     .     0.354351D+00  ,  0.363321D+00  ,  0.373357D+00  ,
     .     0.384388D+00  ,  0.407527D+00  ,  0.442613D+00  ,
     .     0.484150D+00  ,  0.528512D+00  ,  0.509513D+00  ,
     .     0.517414D+00  ,  0.552290D+00  ,  0.586711D+00  ,
     .     0.615255D+00  ,  0.631894D+00  ,  0.655359D+00  ,
     .     0.685743D+00  ,  0.707500D+00  ,  0.719998D+00  ,
     .     0.735680D+00  ,  0.759425D+00  ,  0.783170D+00  ,
     .     0.790341D+00  ,  0.795695D+00  ,  0.804165D+00  ,
     .     0.818423D+00  ,  0.832681D+00  ,  0.834729D+00  ,
     .     0.830354D+00  ,  0.825979D+00  ,  0.827819D+00  /
      DATA (T(K,2),K=90,134) /
     .     0.830710D+00  ,  0.833600D+00  ,  0.830710D+00  ,
     .     0.827819D+00  ,  0.820741D+00  ,  0.788884D+00  ,
     .     0.757028D+00  ,  0.728207D+00  ,  0.705155D+00  ,
     .     0.682104D+00  ,  0.657281D+00  ,  0.631504D+00  ,
     .     0.604691D+00  ,  0.568435D+00  ,  0.532179D+00  ,
     .     0.496771D+00  ,  0.461697D+00  ,  0.427494D+00  ,
     .     0.394101D+00  ,  0.361662D+00  ,  0.330164D+00  ,
     .     0.300023D+00  ,  0.270584D+00  ,  0.246872D+00  ,
     .     0.214772D+00  ,  0.174261D+00  ,  0.142908D+00  ,
     .     0.114790D+00  ,  0.931216D-01  ,  0.619434D-01  ,
     .     0.211276D-01  ,  -.145980D-01  ,  -.448613D-01  ,
     .     -.782255D-01  ,  -.119446D+00  ,  -.160666D+00  ,
     .     -.170909D+00  ,  -.177753D+00  ,  -.202971D+00  ,
     .     -.262314D+00  ,  -.321658D+00  ,  -.384211D+00  ,
     .     -.448453D+00  ,  -.512694D+00  ,  -.556409D+00  /
      DATA (T(K,2),K=135,181) /
     .     -.596655D+00  ,  -.636901D+00  ,  -.696066D+00  ,
     .     -.755232D+00  ,  -.813883D+00  ,  -.869492D+00  ,
     .     -.925101D+00  ,  -.978513D+00  ,  -.102775D+01  ,
     .     -.107699D+01  ,  -.112423D+01  ,  -.117039D+01  ,
     .     -.121752D+01  ,  -.127359D+01  ,  -.132966D+01  ,
     .     -.136558D+01  ,  -.139356D+01  ,  -.145294D+01  ,
     .     -.154156D+01  ,  -.157676D+01  ,  -.155926D+01  ,
     .     -.155395D+01  ,  -.155461D+01  ,  -.154821D+01  ,
     .     -.156075D+01  ,  -.159230D+01  ,  -.159184D+01  ,
     .     -.157674D+01  ,  -.153239D+01  ,  -.149308D+01  ,
     .     -.145888D+01  ,  -.140930D+01  ,  -.134322D+01  ,
     .     -.128937D+01  ,  -.126650D+01  ,  -.124364D+01  ,
     .     -.119876D+01  ,  -.115147D+01  ,  -.108396D+01  ,
     .     -.978886D+00  ,  -.873816D+00  ,  -.799924D+00  ,
     .     -.742434D+00  ,  -.684945D+00  ,  -.620302D+00  ,
     .     -.554451D+00  ,  -.488600D+00  /
C ------ CURVA DI PREV. -  N. GIRI CARATT. (UNITA' SI) = 352
      DATA (H(K,3),K=1,45) /
     .     -.118000D+01  ,  -.109269D+01  ,  -.100538D+01  ,
     .     -.918380D+00  ,  -.833235D+00  ,  -.748090D+00  ,
     .     -.671807D+00  ,  -.612358D+00  ,  -.552909D+00  ,
     .     -.486581D+00  ,  -.416549D+00  ,  -.347405D+00  ,
     .     -.286341D+00  ,  -.225277D+00  ,  -.149775D+00  ,
     .     -.685773D-01  ,  0.919461D-02  ,  0.837743D-01  ,
     .     0.154599D+00  ,  0.221721D+00  ,  0.305830D+00  ,
     .     0.398182D+00  ,  0.466031D+00  ,  0.537576D+00  ,
     .     0.612825D+00  ,  0.669467D+00  ,  0.728614D+00  ,
     .     0.793058D+00  ,  0.844955D+00  ,  0.884132D+00  ,
     .     0.921867D+00  ,  0.958054D+00  ,  0.100229D+01  ,
     .     0.106691D+01  ,  0.113154D+01  ,  0.120587D+01  ,
     .     0.128127D+01  ,  0.135732D+01  ,  0.143457D+01  ,
     .     0.151183D+01  ,  0.155842D+01  ,  0.158889D+01  ,
     .     0.161936D+01  ,  0.164360D+01  ,  0.166680D+01  /
      DATA (H(K,3),K=46,90) /
     .     0.169000D+01  ,  0.169801D+01  ,  0.170602D+01  ,
     .     0.171777D+01  ,  0.175163D+01  ,  0.178550D+01  ,
     .     0.181586D+01  ,  0.183956D+01  ,  0.186327D+01  ,
     .     0.188452D+01  ,  0.190445D+01  ,  0.192630D+01  ,
     .     0.196559D+01  ,  0.200488D+01  ,  0.198202D+01  ,
     .     0.193463D+01  ,  0.193272D+01  ,  0.197319D+01  ,
     .     0.198007D+01  ,  0.195380D+01  ,  0.195386D+01  ,
     .     0.196641D+01  ,  0.188884D+01  ,  0.186494D+01  ,
     .     0.189486D+01  ,  0.181929D+01  ,  0.176409D+01  ,
     .     0.175137D+01  ,  0.174440D+01  ,  0.174325D+01  ,
     .     0.172891D+01  ,  0.170042D+01  ,  0.167295D+01  ,
     .     0.164805D+01  ,  0.162315D+01  ,  0.159588D+01  ,
     .     0.156835D+01  ,  0.154890D+01  ,  0.154445D+01  ,
     .     0.154000D+01  ,  0.153062D+01  ,  0.151865D+01  ,
     .     0.150668D+01  ,  0.150047D+01  ,  0.149524D+01  /
      DATA (H(K,3),K=91,135) /
     .     0.149000D+01  ,  0.144669D+01  ,  0.140339D+01  ,
     .     0.136132D+01  ,  0.132664D+01  ,  0.129196D+01  ,
     .     0.125122D+01  ,  0.119897D+01  ,  0.114672D+01  ,
     .     0.109571D+01  ,  0.104537D+01  ,  0.994686D+00  ,
     .     0.940946D+00  ,  0.887207D+00  ,  0.822637D+00  ,
     .     0.753794D+00  ,  0.697532D+00  ,  0.652992D+00  ,
     .     0.610013D+00  ,  0.568571D+00  ,  0.525014D+00  ,
     .     0.480473D+00  ,  0.446840D+00  ,  0.408315D+00  ,
     .     0.364885D+00  ,  0.325282D+00  ,  0.284850D+00  ,
     .     0.242695D+00  ,  0.204940D+00  ,  0.171646D+00  ,
     .     0.141601D+00  ,  0.115042D+00  ,  0.866422D-01  ,
     .     0.535762D-01  ,  0.205101D-01  ,  -.147738D-01  ,
     .     -.503010D-01  ,  -.850921D-01  ,  -.118516D+00  ,
     .     -.151940D+00  ,  -.187771D+00  ,  -.224867D+00  ,
     .     -.261964D+00  ,  -.277115D+00  ,  -.288558D+00  /
      DATA (H(K,3),K=136,181) /
     .     -.300001D+00  ,  -.361375D+00  ,  -.422749D+00  ,
     .     -.483479D+00  ,  -.540399D+00  ,  -.597319D+00  ,
     .     -.655540D+00  ,  -.716233D+00  ,  -.776927D+00  ,
     .     -.834219D+00  ,  -.889679D+00  ,  -.943489D+00  ,
     .     -.982259D+00  ,  -.102103D+01  ,  -.108869D+01  ,
     .     -.116775D+01  ,  -.128061D+01  ,  -.142495D+01  ,
     .     -.158293D+01  ,  -.175434D+01  ,  -.187370D+01  ,
     .     -.196761D+01  ,  -.210248D+01  ,  -.218325D+01  ,
     .     -.220978D+01  ,  -.223752D+01  ,  -.228010D+01  ,
     .     -.235271D+01  ,  -.237849D+01  ,  -.235681D+01  ,
     .     -.231892D+01  ,  -.226364D+01  ,  -.220251D+01  ,
     .     -.212656D+01  ,  -.205061D+01  ,  -.198251D+01  ,
     .     -.191527D+01  ,  -.183954D+01  ,  -.174804D+01  ,
     .     -.165654D+01  ,  -.158068D+01  ,  -.151305D+01  ,
     .     -.144542D+01  ,  -.135905D+01  ,  -.126953D+01  ,
     .     -.118000D+01  /
C ----CURVA DI COPPIA -  N. GIRI CARATT. (UNITA' SI) = 352
      DATA (T(K,3),K=1,44) /
     .                      -.156000D+01  ,  -.139855D+01  ,
     .     -.123711D+01  ,  -.107850D+01  ,  -.936670D+00  ,
     .     -.794841D+00  ,  -.671973D+00  ,  -.585124D+00  ,
     .     -.498276D+00  ,  -.407970D+00  ,  -.315804D+00  ,
     .     -.223754D+00  ,  -.132750D+00  ,  -.417472D-01  ,
     .     0.179837D-01  ,  0.653758D-01  ,  0.120754D+00  ,
     .     0.183574D+00  ,  0.251222D+00  ,  0.323631D+00  ,
     .     0.381114D+00  ,  0.431204D+00  ,  0.477048D+00  ,
     .     0.517413D+00  ,  0.552285D+00  ,  0.586710D+00  ,
     .     0.620818D+00  ,  0.654289D+00  ,  0.686956D+00  ,
     .     0.718807D+00  ,  0.749485D+00  ,  0.778905D+00  ,
     .     0.807374D+00  ,  0.833434D+00  ,  0.859493D+00  ,
     .     0.894587D+00  ,  0.930672D+00  ,  0.968828D+00  ,
     .     0.101083D+01  ,  0.105283D+01  ,  0.109095D+01  ,
     .     0.112703D+01  ,  0.116310D+01  ,  0.117182D+01  /
      DATA (T(K,3),K=45,89) /
     .     0.117591D+01  ,  0.118000D+01  ,  0.122445D+01  ,
     .     0.126890D+01  ,  0.131144D+01  ,  0.134262D+01  ,
     .     0.137380D+01  ,  0.140835D+01  ,  0.144930D+01  ,
     .     0.149026D+01  ,  0.152319D+01  ,  0.155180D+01  ,
     .     0.157985D+01  ,  0.160269D+01  ,  0.162554D+01  ,
     .     0.166807D+01  ,  0.171838D+01  ,  0.174325D+01  ,
     .     0.174440D+01  ,  0.176309D+01  ,  0.179909D+01  ,
     .     0.181812D+01  ,  0.182881D+01  ,  0.184293D+01  ,
     .     0.186494D+01  ,  0.189486D+01  ,  0.188488D+01  ,
     .     0.189882D+01  ,  0.196166D+01  ,  0.197319D+01  ,
     .     0.193272D+01  ,  0.192059D+01  ,  0.193888D+01  ,
     .     0.194848D+01  ,  0.193606D+01  ,  0.192364D+01  ,
     .     0.190445D+01  ,  0.188452D+01  ,  0.186951D+01  ,
     .     0.186365D+01  ,  0.185779D+01  ,  0.183391D+01  ,
     .     0.180056D+01  ,  0.176720D+01  ,  0.174070D+01  /
      DATA (T(K,3),K=90,134) /
     .     0.171535D+01  ,  0.169000D+01  ,  0.166680D+01  ,
     .     0.164360D+01  ,  0.162134D+01  ,  0.160461D+01  ,
     .     0.158788D+01  ,  0.155828D+01  ,  0.150420D+01  ,
     .     0.145012D+01  ,  0.136965D+01  ,  0.127497D+01  ,
     .     0.118112D+01  ,  0.109478D+01  ,  0.100843D+01  ,
     .     0.929287D+00  ,  0.852981D+00  ,  0.778903D+00  ,
     .     0.706900D+00  ,  0.639227D+00  ,  0.575827D+00  ,
     .     0.500558D+00  ,  0.419478D+00  ,  0.346527D+00  ,
     .     0.278637D+00  ,  0.215823D+00  ,  0.163226D+00  ,
     .     0.109812D+00  ,  0.546239D-01  ,  -.515548D-02  ,
     .     -.695883D-01  ,  -.136510D+00  ,  -.206102D+00  ,
     .     -.296258D+00  ,  -.438512D+00  ,  -.580766D+00  ,
     .     -.598599D+00  ,  -.602785D+00  ,  -.634262D+00  ,
     .     -.716430D+00  ,  -.798598D+00  ,  -.890603D+00  ,
     .     -.987782D+00  ,  -.108496D+01  ,  -.119517D+01  /
      DATA (T(K,3),K=135,181) /
     .     -.130759D+01  ,  -.142000D+01  ,  -.146362D+01  ,
     .     -.150725D+01  ,  -.155318D+01  ,  -.161282D+01  ,
     .     -.167246D+01  ,  -.171910D+01  ,  -.174103D+01  ,
     .     -.176297D+01  ,  -.179394D+01  ,  -.182978D+01  ,
     .     -.186846D+01  ,  -.193309D+01  ,  -.199771D+01  ,
     .     -.207071D+01  ,  -.214702D+01  ,  -.223662D+01  ,
     .     -.233861D+01  ,  -.245983D+01  ,  -.260002D+01  ,
     .     -.273085D+01  ,  -.285627D+01  ,  -.284210D+01  ,
     .     -.288607D+01  ,  -.298835D+01  ,  -.308664D+01  ,
     .     -.311288D+01  ,  -.299315D+01  ,  -.299658D+01  ,
     .     -.312481D+01  ,  -.314048D+01  ,  -.303536D+01  ,
     .     -.294734D+01  ,  -.290261D+01  ,  -.285787D+01  ,
     .     -.274642D+01  ,  -.262766D+01  ,  -.249770D+01  ,
     .     -.234695D+01  ,  -.219620D+01  ,  -.207803D+01  ,
     .     -.197701D+01  ,  -.187599D+01  ,  -.177110D+01  ,
     .     -.166555D+01  ,  -.156000D+01  /
C------- CURVA DI PREV. -  N. GIRI CARATT. (UNITA' SI) = 380
      DATA (H(K,4),K=1,45) /
     .     -.118000D+01  ,  -.109269D+01  ,  -.100538D+01  ,
     .     -.918380D+00  ,  -.833235D+00  ,  -.748090D+00  ,
     .     -.671807D+00  ,  -.612358D+00  ,  -.552909D+00  ,
     .     -.486581D+00  ,  -.416549D+00  ,  -.347405D+00  ,
     .     -.286341D+00  ,  -.225277D+00  ,  -.149775D+00  ,
     .     -.685773D-01  ,  0.919461D-02  ,  0.837743D-01  ,
     .     0.154599D+00  ,  0.221721D+00  ,  0.305830D+00  ,
     .     0.398182D+00  ,  0.466031D+00  ,  0.537576D+00  ,
     .     0.612825D+00  ,  0.669467D+00  ,  0.728614D+00  ,
     .     0.793058D+00  ,  0.844955D+00  ,  0.884132D+00  ,
     .     0.921867D+00  ,  0.958054D+00  ,  0.100229D+01  ,
     .     0.106691D+01  ,  0.113154D+01  ,  0.120587D+01  ,
     .     0.128127D+01  ,  0.135732D+01  ,  0.143457D+01  ,
     .     0.151183D+01  ,  0.155842D+01  ,  0.158889D+01  ,
     .     0.161936D+01  ,  0.164360D+01  ,  0.166680D+01  /
      DATA (H(K,4),K=46,90) /
     .     0.169000D+01  ,  0.169801D+01  ,  0.170602D+01  ,
     .     0.171777D+01  ,  0.175163D+01  ,  0.178550D+01  ,
     .     0.181586D+01  ,  0.183956D+01  ,  0.186327D+01  ,
     .     0.188452D+01  ,  0.190445D+01  ,  0.192630D+01  ,
     .     0.196559D+01  ,  0.200488D+01  ,  0.198202D+01  ,
     .     0.193463D+01  ,  0.193272D+01  ,  0.197319D+01  ,
     .     0.198007D+01  ,  0.195380D+01  ,  0.195386D+01  ,
     .     0.196641D+01  ,  0.188884D+01  ,  0.186494D+01  ,
     .     0.189486D+01  ,  0.181929D+01  ,  0.176409D+01  ,
     .     0.175137D+01  ,  0.174440D+01  ,  0.174325D+01  ,
     .     0.172891D+01  ,  0.170042D+01  ,  0.167295D+01  ,
     .     0.164805D+01  ,  0.162315D+01  ,  0.159588D+01  ,
     .     0.156835D+01  ,  0.154890D+01  ,  0.154445D+01  ,
     .     0.154000D+01  ,  0.153062D+01  ,  0.151865D+01  ,
     .     0.150668D+01  ,  0.150047D+01  ,  0.149524D+01  /
      DATA (H(K,4),K=91,135) /
     .     0.149000D+01  ,  0.144669D+01  ,  0.140339D+01  ,
     .     0.136132D+01  ,  0.132664D+01  ,  0.129196D+01  ,
     .     0.125122D+01  ,  0.119897D+01  ,  0.114672D+01  ,
     .     0.109571D+01  ,  0.104537D+01  ,  0.994686D+00  ,
     .     0.940946D+00  ,  0.887207D+00  ,  0.822637D+00  ,
     .     0.753794D+00  ,  0.697532D+00  ,  0.652992D+00  ,
     .     0.610013D+00  ,  0.568571D+00  ,  0.525014D+00  ,
     .     0.480473D+00  ,  0.446840D+00  ,  0.408315D+00  ,
     .     0.364885D+00  ,  0.325282D+00  ,  0.284850D+00  ,
     .     0.242695D+00  ,  0.204940D+00  ,  0.171646D+00  ,
     .     0.141601D+00  ,  0.115042D+00  ,  0.866422D-01  ,
     .     0.535762D-01  ,  0.205101D-01  ,  -.147738D-01  ,
     .     -.503010D-01  ,  -.850921D-01  ,  -.118516D+00  ,
     .     -.151940D+00  ,  -.187771D+00  ,  -.224867D+00  ,
     .     -.261964D+00  ,  -.277115D+00  ,  -.288558D+00  /
      DATA (H(K,4),K=136,181) /
     .     -.300001D+00  ,  -.361375D+00  ,  -.422749D+00  ,
     .     -.483479D+00  ,  -.540399D+00  ,  -.597319D+00  ,
     .     -.655540D+00  ,  -.716233D+00  ,  -.776927D+00  ,
     .     -.834219D+00  ,  -.889679D+00  ,  -.943489D+00  ,
     .     -.982259D+00  ,  -.102103D+01  ,  -.108869D+01  ,
     .     -.116775D+01  ,  -.128061D+01  ,  -.142495D+01  ,
     .     -.158293D+01  ,  -.175434D+01  ,  -.187370D+01  ,
     .     -.196761D+01  ,  -.210248D+01  ,  -.218325D+01  ,
     .     -.220978D+01  ,  -.223752D+01  ,  -.228010D+01  ,
     .     -.235271D+01  ,  -.237849D+01  ,  -.235681D+01  ,
     .     -.231892D+01  ,  -.226364D+01  ,  -.220251D+01  ,
     .     -.212656D+01  ,  -.205061D+01  ,  -.198251D+01  ,
     .     -.191527D+01  ,  -.183954D+01  ,  -.174804D+01  ,
     .     -.165654D+01  ,  -.158068D+01  ,  -.151305D+01  ,
     .     -.144542D+01  ,  -.135905D+01  ,  -.126953D+01  ,
     .     -.118000D+01  /
C ----CURVA DI COPPIA -  N. GIRI CARATT. (UNITA' SI) = 380
      DATA (T(K,4),K=1,44) /
     .                      -.156000D+01  ,  -.139855D+01  ,
     .     -.123711D+01  ,  -.107850D+01  ,  -.936670D+00  ,
     .     -.794841D+00  ,  -.671973D+00  ,  -.585124D+00  ,
     .     -.498276D+00  ,  -.407970D+00  ,  -.315804D+00  ,
     .     -.223754D+00  ,  -.132750D+00  ,  -.417472D-01  ,
     .     0.179837D-01  ,  0.653758D-01  ,  0.120754D+00  ,
     .     0.183574D+00  ,  0.251222D+00  ,  0.323631D+00  ,
     .     0.381114D+00  ,  0.431204D+00  ,  0.477048D+00  ,
     .     0.517413D+00  ,  0.552285D+00  ,  0.586710D+00  ,
     .     0.620818D+00  ,  0.654289D+00  ,  0.686956D+00  ,
     .     0.718807D+00  ,  0.749485D+00  ,  0.778905D+00  ,
     .     0.807374D+00  ,  0.833434D+00  ,  0.859493D+00  ,
     .     0.894587D+00  ,  0.930672D+00  ,  0.968828D+00  ,
     .     0.101083D+01  ,  0.105283D+01  ,  0.109095D+01  ,
     .     0.112703D+01  ,  0.116310D+01  ,  0.117182D+01  /
      DATA (T(K,4),K=45,89) /
     .     0.117591D+01  ,  0.118000D+01  ,  0.122445D+01  ,
     .     0.126890D+01  ,  0.131144D+01  ,  0.134262D+01  ,
     .     0.137380D+01  ,  0.140835D+01  ,  0.144930D+01  ,
     .     0.149026D+01  ,  0.152319D+01  ,  0.155180D+01  ,
     .     0.157985D+01  ,  0.160269D+01  ,  0.162554D+01  ,
     .     0.166807D+01  ,  0.171838D+01  ,  0.174325D+01  ,
     .     0.174440D+01  ,  0.176309D+01  ,  0.179909D+01  ,
     .     0.181812D+01  ,  0.182881D+01  ,  0.184293D+01  ,
     .     0.186494D+01  ,  0.189486D+01  ,  0.188488D+01  ,
     .     0.189882D+01  ,  0.196166D+01  ,  0.197319D+01  ,
     .     0.193272D+01  ,  0.192059D+01  ,  0.193888D+01  ,
     .     0.194848D+01  ,  0.193606D+01  ,  0.192364D+01  ,
     .     0.190445D+01  ,  0.188452D+01  ,  0.186951D+01  ,
     .     0.186365D+01  ,  0.185779D+01  ,  0.183391D+01  ,
     .     0.180056D+01  ,  0.176720D+01  ,  0.174070D+01  /
      DATA (T(K,4),K=90,134) /
     .     0.171535D+01  ,  0.169000D+01  ,  0.166680D+01  ,
     .     0.164360D+01  ,  0.162134D+01  ,  0.160461D+01  ,
     .     0.158788D+01  ,  0.155828D+01  ,  0.150420D+01  ,
     .     0.145012D+01  ,  0.136965D+01  ,  0.127497D+01  ,
     .     0.118112D+01  ,  0.109478D+01  ,  0.100843D+01  ,
     .     0.929287D+00  ,  0.852981D+00  ,  0.778903D+00  ,
     .     0.706900D+00  ,  0.639227D+00  ,  0.575827D+00  ,
     .     0.500558D+00  ,  0.419478D+00  ,  0.346527D+00  ,
     .     0.278637D+00  ,  0.215823D+00  ,  0.163226D+00  ,
     .     0.109812D+00  ,  0.546239D-01  ,  -.515548D-02  ,
     .     -.695883D-01  ,  -.136510D+00  ,  -.206102D+00  ,
     .     -.296258D+00  ,  -.438512D+00  ,  -.580766D+00  ,
     .     -.598599D+00  ,  -.602785D+00  ,  -.634262D+00  ,
     .     -.716430D+00  ,  -.798598D+00  ,  -.890603D+00  ,
     .     -.987782D+00  ,  -.108496D+01  ,  -.119517D+01  /
      DATA (T(K,4),K=135,181) /
     .     -.130759D+01  ,  -.142000D+01  ,  -.146362D+01  ,
     .     -.150725D+01  ,  -.155318D+01  ,  -.161282D+01  ,
     .     -.167246D+01  ,  -.171910D+01  ,  -.174103D+01  ,
     .     -.176297D+01  ,  -.179394D+01  ,  -.182978D+01  ,
     .     -.186846D+01  ,  -.193309D+01  ,  -.199771D+01  ,
     .     -.207071D+01  ,  -.214702D+01  ,  -.223662D+01  ,
     .     -.233861D+01  ,  -.245983D+01  ,  -.260002D+01  ,
     .     -.273085D+01  ,  -.285627D+01  ,  -.284210D+01  ,
     .     -.288607D+01  ,  -.298835D+01  ,  -.308664D+01  ,
     .     -.311288D+01  ,  -.299315D+01  ,  -.299658D+01  ,
     .     -.312481D+01  ,  -.314048D+01  ,  -.303536D+01  ,
     .     -.294734D+01  ,  -.290261D+01  ,  -.285787D+01  ,
     .     -.274642D+01  ,  -.262766D+01  ,  -.249770D+01  ,
     .     -.234695D+01  ,  -.219620D+01  ,  -.207803D+01  ,
     .     -.197701D+01  ,  -.187599D+01  ,  -.177110D+01  ,
     .     -.166555D+01  ,  -.156000D+01  /
C ------ CURVA DI PREV. -  N. GIRI CARATT. (UNITA' SI) = 447
      DATA (H(K,5),K=1,45) /
     .     -.184300D+01  ,  -.178460D+01  ,  -.172620D+01  ,
     .     -.166435D+01  ,  -.158217D+01  ,  -.149999D+01  ,
     .     -.141395D+01  ,  -.132056D+01  ,  -.122717D+01  ,
     .     -.112406D+01  ,  -.101572D+01  ,  -.908094D+00  ,
     .     -.806955D+00  ,  -.705815D+00  ,  -.597637D+00  ,
     .     -.486681D+00  ,  -.367029D+00  ,  -.239273D+00  ,
     .     -.982714D-01  ,  0.557929D-01  ,  0.201678D+00  ,
     .     0.343311D+00  ,  0.447725D+00  ,  0.538492D+00  ,
     .     0.615577D+00  ,  0.696449D+00  ,  0.770758D+00  ,
     .     0.831722D+00  ,  0.892708D+00  ,  0.953714D+00  ,
     .     0.101431D+01  ,  0.107447D+01  ,  0.113179D+01  ,
     .     0.118195D+01  ,  0.123211D+01  ,  0.128555D+01  ,
     .     0.133934D+01  ,  0.139425D+01  ,  0.145124D+01  ,
     .     0.150823D+01  ,  0.156700D+01  ,  0.162671D+01  ,
     .     0.168642D+01  ,  0.174656D+01  ,  0.180678D+01  /
      DATA (H(K,5),K=46,90) /
     .     0.186700D+01  ,  0.194236D+01  ,  0.201772D+01  ,
     .     0.208429D+01  ,  0.209890D+01  ,  0.211351D+01  ,
     .     0.213832D+01  ,  0.218252D+01  ,  0.222673D+01  ,
     .     0.226528D+01  ,  0.230077D+01  ,  0.233505D+01  ,
     .     0.235825D+01  ,  0.238144D+01  ,  0.240294D+01  ,
     .     0.242377D+01  ,  0.246721D+01  ,  0.253172D+01  ,
     .     0.252985D+01  ,  0.246250D+01  ,  0.243828D+01  ,
     .     0.243555D+01  ,  0.246917D+01  ,  0.250311D+01  ,
     .     0.253738D+01  ,  0.252095D+01  ,  0.250365D+01  ,
     .     0.248515D+01  ,  0.244771D+01  ,  0.239108D+01  ,
     .     0.234804D+01  ,  0.231959D+01  ,  0.228752D+01  ,
     .     0.224623D+01  ,  0.220494D+01  ,  0.215811D+01  ,
     .     0.211066D+01  ,  0.206109D+01  ,  0.200756D+01  ,
     .     0.195403D+01  ,  0.189713D+01  ,  0.183845D+01  ,
     .     0.177977D+01  ,  0.171159D+01  ,  0.164179D+01  /
      DATA (H(K,5),K=91,135) /
     .     0.157200D+01  ,  0.150899D+01  ,  0.144598D+01  ,
     .     0.138226D+01  ,  0.131434D+01  ,  0.124642D+01  ,
     .     0.117867D+01  ,  0.111123D+01  ,  0.104378D+01  ,
     .     0.975236D+00  ,  0.906096D+00  ,  0.837166D+00  ,
     .     0.770145D+00  ,  0.703125D+00  ,  0.640877D+00  ,
     .     0.580513D+00  ,  0.521751D+00  ,  0.464481D+00  ,
     .     0.410682D+00  ,  0.360305D+00  ,  0.314685D+00  ,
     .     0.271429D+00  ,  0.230929D+00  ,  0.193607D+00  ,
     .     0.159474D+00  ,  0.129757D+00  ,  0.101565D+00  ,
     .     0.764076D-01  ,  0.553068D-01  ,  0.383167D-01  ,
     .     0.230473D-01  ,  0.962427D-02  ,  -.410119D-02  ,
     .     -.185929D-01  ,  -.330846D-01  ,  -.648743D-01  ,
     .     -.985616D-01  ,  -.133350D+00  ,  -.170182D+00  ,
     .     -.207015D+00  ,  -.255395D+00  ,  -.309851D+00  ,
     .     -.364306D+00  ,  -.418350D+00  ,  -.472326D+00  /
      DATA (H(K,5),K=136,181) /
     .     -.526301D+00  ,  -.585399D+00  ,  -.644497D+00  ,
     .     -.701727D+00  ,  -.747900D+00  ,  -.794073D+00  ,
     .     -.842342D+00  ,  -.894597D+00  ,  -.946852D+00  ,
     .     -.992913D+00  ,  -.103564D+01  ,  -.107897D+01  ,
     .     -.112778D+01  ,  -.117659D+01  ,  -.122949D+01  ,
     .     -.128400D+01  ,  -.134369D+01  ,  -.140822D+01  ,
     .     -.146855D+01  ,  -.152473D+01  ,  -.156722D+01  ,
     .     -.160332D+01  ,  -.170206D+01  ,  -.175623D+01  ,
     .     -.176569D+01  ,  -.182484D+01  ,  -.187874D+01  ,
     .     -.192145D+01  ,  -.195448D+01  ,  -.197769D+01  ,
     .     -.200530D+01  ,  -.203762D+01  ,  -.206730D+01  ,
     .     -.209028D+01  ,  -.211325D+01  ,  -.212203D+01  ,
     .     -.212925D+01  ,  -.212917D+01  ,  -.211549D+01  ,
     .     -.210182D+01  ,  -.207253D+01  ,  -.203502D+01  ,
     .     -.199750D+01  ,  -.194742D+01  ,  -.189521D+01  ,
     .     -.184300D+01  /
C-----CURVA DI COPPIA -  N. GIRI CARATT. (UNITA' SI) = 447
      DATA (T(K,5),K=1,44) /
     .                      -.126800D+01  ,  -.120258D+01  ,
     .     -.113715D+01  ,  -.107055D+01  ,  -.996972D+00  ,
     .     -.923396D+00  ,  -.843732D+00  ,  -.752504D+00  ,
     .     -.661276D+00  ,  -.551555D+00  ,  -.431882D+00  ,
     .     -.313280D+00  ,  -.204431D+00  ,  -.955806D-01  ,
     .     -.600142D-02  ,  0.759743D-01  ,  0.154218D+00  ,
     .     0.228984D+00  ,  0.291867D+00  ,  0.343031D+00  ,
     .     0.390112D+00  ,  0.435167D+00  ,  0.478370D+00  ,
     .     0.520163D+00  ,  0.560541D+00  ,  0.600612D+00  ,
     .     0.638821D+00  ,  0.673263D+00  ,  0.703796D+00  ,
     .     0.730365D+00  ,  0.755023D+00  ,  0.777630D+00  ,
     .     0.800052D+00  ,  0.822001D+00  ,  0.843951D+00  ,
     .     0.861847D+00  ,  0.879299D+00  ,  0.900225D+00  ,
     .     0.927605D+00  ,  0.954984D+00  ,  0.991056D+00  ,
     .     0.103170D+01  ,  0.107234D+01  ,  0.112729D+01  /
      DATA (T(K,5),K=45,89) /
     .     0.118464D+01  ,  0.124200D+01  ,  0.129803D+01  ,
     .     0.135405D+01  ,  0.141012D+01  ,  0.146642D+01  ,
     .     0.152273D+01  ,  0.157641D+01  ,  0.162510D+01  ,
     .     0.167379D+01  ,  0.171645D+01  ,  0.175586D+01  ,
     .     0.179443D+01  ,  0.182525D+01  ,  0.185608D+01  ,
     .     0.187987D+01  ,  0.190089D+01  ,  0.192027D+01  ,
     .     0.193812D+01  ,  0.195283D+01  ,  0.196445D+01  ,
     .     0.198794D+01  ,  0.201716D+01  ,  0.202172D+01  ,
     .     0.203602D+01  ,  0.206008D+01  ,  0.202897D+01  ,
     .     0.201061D+01  ,  0.201873D+01  ,  0.202155D+01  ,
     .     0.201898D+01  ,  0.199834D+01  ,  0.195830D+01  ,
     .     0.192465D+01  ,  0.190715D+01  ,  0.188966D+01  ,
     .     0.184845D+01  ,  0.180463D+01  ,  0.176314D+01  ,
     .     0.172596D+01  ,  0.168878D+01  ,  0.165054D+01  ,
     .     0.161174D+01  ,  0.157294D+01  ,  0.152469D+01  /
      DATA (T(K,5),K=90,134) /
     .     0.147484D+01  ,  0.142500D+01  ,  0.137013D+01  ,
     .     0.131526D+01  ,  0.125968D+01  ,  0.119990D+01  ,
     .     0.114013D+01  ,  0.107722D+01  ,  0.100837D+01  ,
     .     0.939509D+00  ,  0.874407D+00  ,  0.811326D+00  ,
     .     0.748246D+00  ,  0.685167D+00  ,  0.622089D+00  ,
     .     0.562657D+00  ,  0.504663D+00  ,  0.445977D+00  ,
     .     0.386646D+00  ,  0.323459D+00  ,  0.256466D+00  ,
     .     0.179763D+00  ,  0.982467D-01  ,  0.128288D-01  ,
     .     -.556591D-01  ,  -.107170D+00  ,  -.161378D+00  ,
     .     -.212711D+00  ,  -.258185D+00  ,  -.303018D+00  ,
     .     -.347203D+00  ,  -.392709D+00  ,  -.439635D+00  ,
     .     -.486042D+00  ,  -.531137D+00  ,  -.576232D+00  ,
     .     -.623936D+00  ,  -.671926D+00  ,  -.717513D+00  ,
     .     -.758639D+00  ,  -.799765D+00  ,  -.842981D+00  ,
     .     -.887297D+00  ,  -.931614D+00  ,  -.968871D+00  /
      DATA (T(K,5),K=135,181) /
     .     -.100494D+01  ,  -.104100D+01  ,  -.108178D+01  ,
     .     -.112255D+01  ,  -.116191D+01  ,  -.119291D+01  ,
     .     -.122392D+01  ,  -.125453D+01  ,  -.128442D+01  ,
     .     -.131431D+01  ,  -.134240D+01  ,  -.136952D+01  ,
     .     -.139753D+01  ,  -.143366D+01  ,  -.146978D+01  ,
     .     -.149970D+01  ,  -.152719D+01  ,  -.155351D+01  ,
     .     -.157875D+01  ,  -.161594D+01  ,  -.166492D+01  ,
     .     -.169448D+01  ,  -.171441D+01  ,  -.172347D+01  ,
     .     -.173759D+01  ,  -.175680D+01  ,  -.175424D+01  ,
     .     -.174952D+01  ,  -.174069D+01  ,  -.173256D+01  ,
     .     -.172515D+01  ,  -.172033D+01  ,  -.171827D+01  ,
     .     -.171112D+01  ,  -.169104D+01  ,  -.167095D+01  ,
     .     -.165498D+01  ,  -.163945D+01  ,  -.161893D+01  ,
     .     -.158912D+01  ,  -.155931D+01  ,  -.152111D+01  ,
     .     -.147849D+01  ,  -.143586D+01  ,  -.138126D+01  ,
     .     -.132463D+01  ,  -.126800D+01  /
      DO 10 I=1,5
      ITYP=I
      DIF=ACURV(I)-GCAR
      IF(DIF.GE.0.) GO TO 11
   10 CONTINUE
   11 IF(ITYP.EQ.1.OR.DIF.LT.0.) GO TO 15
      DIF1=GCAR-ACURV(ITYP-1)
      IF(DIF.GE.DIF1) ITYP=ITYP-1
   15 RQ=Q/QNOM
      ROM=OM/OMNOM
      IF(RQ.EQ.0..AND.ROM.EQ.0.) THEN
        DP=0.
        CRES=0.
      ELSE
        ALFAR=ATAN2(ROM,RQ)
        ALFAG=57.29578*ALFAR
        IF(ALFAG.LT.0.) ALFAG=360.+ALFAG
        I=ALFAG/2.
        ALF=2.*DFLOAT(I)
        K=I+1
        RDP=H(K,ITYP)+(H(K+1,ITYP)-H(K,ITYP))/2.*(ALFAG-ALF)
        RCRES=T(K,ITYP)+(T(K+1,ITYP)-T(K,ITYP))/2.*(ALFAG-ALF)
C-------RMOLT=ROM**2.+RQ**2.---------A.ROSSI, 20/2/89
        RMOLT=ROM*ABS(ROM)+RQ*ABS(RQ)
        DP=RDP*RMOLT*DPNOM
        CRES=RCRES*RMOLT*CNOM
      ENDIF
      RETURN
      END
C
      SUBROUTINE CPOTERB0(DATI,IPD,Q,HM,HV,POT,PM,PV,HVT,FNAC)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/IFAN/IFAN
      DIMENSION DATI(*)
C
C     CALCOLO TRANSITORIO
C
C     INIZIALIZZAZIONE VARIABILI DI STATO INTERNE
C     QUESTI CALCOLI NON  SONO RIPETUTI DURANTE LE ITERAZIONI
C
      IF(ITERT.LE.0.AND.IFAN.EQ.2)THEN
C
C     CARICAMENTO DELLO STATO DI ENTROPIA S
C     DEL PASSO DI TEMPO PRECEDENTE
C
      S=DATI(IPD+13)
      AMPOMP=DATI(IPD+11)
C
C     BILANCIO DI ENTROPIA
C
Car---09/jan/2001
Car      T=TEV(PM,S,1)
Car---09/jan/2001
      CALL TS_FOR(S,FNAC,T)
      DS=DTINT/AMPOMP/T*(ABS(Q)*(HM-HV)+POT)
      S=S+DS
      CALL TS_FOR(S,FNAC,T)
      CALL ROC_FOR(FNAC,T,PV,RO)
      CALL H_FOR(T,PV,RO,FNAC,HVT)
Car---09/jan/2001
Car      HVT=HEV(PV,S,1)
Car---09/jan/2001
      DATI(IPD+13)=S
      DATI(IPD+14)=HVT
      ENDIF
      HVT=DATI(IPD+14)
      RETURN
      END
C
C
C
      SUBROUTINE BPM0D1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $   XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 IBLOC, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
      Q0 = H0*W0
      OM0 = 314.1592
C
      IHI = DATI(IPD)
      IWP = DATI(IPD+1)
      IF (IHI .NE. 1) GO TO 2
C
C---IHI=1
C
      IF (IWP .EQ. 0) THEN
        IM = 2
        IV = 3
        IQ = 4
      ELSE IF (IWP .EQ. 1) THEN
        IV = 2
        IM = 3
        IQ = 4
      ELSE
        IQ = 2
        IV = 3
        IM = 4
      ENDIF
      VALV = DATI(IPD+17)
      OM = XYU(IXYU+5)*OM0
      Q  = XYU(IXYU+IQ-1)*W0
C
C-----Equazione n. 1 (Algebrica):
C
      SIGNEQ(1) = 'COMPUTATION OF OUTLET ENTHALPY (ENERGY CONS. EQ.)'
      IF (Q .GT. 1.E-3) THEN
C---pompa flussata
        UNITEQ(1) = 'W'
        COSNOR(1) = H0*W0
        ITOPVA(1,1) = 1
        ITOPVA(1,5) = 1
        ITOPVA(1,6) = 1
        ITOPVA(1,7) = 1
        ITOPVA(1,IQ) = 1
        ITOPVA(1,IM) = 1
      ELSE
C---portata nulla
        UNITEQ(1) = 'J/kg'
        COSNOR(1) = H0
        ITOPVA(1,1) = 1
        ITOPVA(1,5) = 1
      ENDIF
C
C-----Equazione n.2 (Algebrica)
C
      SIGNEQ(2) = 'COMPUTATION OF PUMP INLET PRESSURE'
      IF (OM .LE. 1.E-3 .AND. VALV .EQ. 1.) THEN
C---pompa ferma con valvola
        UNITEQ(2) = 'kg/s'
        COSNOR(2) = W0
        ITOPVA(2,IQ) = 1
      ELSE
        UNITEQ(2) = 'Pa'
        COSNOR(2) = P0
        ITOPVA(2,5) = 1
        ITOPVA(2,6) = 1
        ITOPVA(2,7) = 1
        ITOPVA(2,IQ) = 1
        ITOPVA(2,IM) = 1
        ITOPVA(2,IV) = 1
      ENDIF
C
      GO TO 1
C
    2 CONTINUE
C
C---IHI=2
      IF (IWP .EQ. 0) THEN
        IM = 4
        IV = 5
        IQ = 6
      ELSE IF (IWP .EQ. 1) THEN
        IV = 4
        IM = 5
        IQ = 6
      ELSE
        IQ = 4
        IV = 5
        IM = 6
      ENDIF
      VALV = DATI(IPD+17)
      OM = XYU(IXYU+1)*OM0
      Q  = XYU(IXYU+IQ-1)*W0
C
C-----Equazione n. 1 (differenziale):
C
      SIGNEQ(1) = 'COMPUTATION OF PUMP KINETIC ENERGY'
      UNITEQ(1) = 'p.u.'
      COSNOR(1) = 1.
      ITOPVA(1,2) = 1
      ITOPVA(1,7) = 1
      ITOPVA(1,8) = 1
      ITOPVA(1,9) = 1
      ITOPVA(1,IQ) = 1
      ITOPVA(1,IM) = 1
C
C-----Equazione n. 2 (Algebrica):
C
      SIGNEQ(2) = 'COMPUTATION OF PUMP ROTATIONAL SPEED'
      UNITEQ(2) = 'J'
      COSNOR(2) = Q0
C
      ITOPVA(2,1) = 1
      ITOPVA(2,2) = 1
C
C-----Equazione n. 3 (Algebrica):
C
      SIGNEQ(3) = 'COMPUTATION OF OUTLET ENTHALPY (ENERGY CONS. EQ.)'
      IF (Q .GT. 1.E-3) THEN
C---pompa flussata
        UNITEQ(3) = 'W'
        COSNOR(3) = H0*W0
        ITOPVA(3,2) = 1
        ITOPVA(3,3) = 1
        ITOPVA(3,7) = 1
        ITOPVA(3,9) = 1
        ITOPVA(3,IQ) = 1
        ITOPVA(3,IM) = 1
      ELSE
C---portata nulla
        UNITEQ(3) = 'J/kg'
        COSNOR(3) = H0
        ITOPVA(3,3) = 1
        ITOPVA(3,7) = 1
      ENDIF
C
C-----Equazione n.4 (Algebrica)
C
      SIGNEQ(4) = 'COMPUTATION OF PUMP INLET PRESSURE'
      IF (OM .LE. 1.E-3 .AND. VALV .EQ. 1.) THEN
C---pompa ferma con valvola
        UNITEQ(4) = 'kg/s'
        COSNOR(4) = W0
        ITOPVA(4,IQ) = 1
      ELSE
        UNITEQ(4) = 'Pa'
        COSNOR(4) = P0
        ITOPVA(4,2) = 1
        ITOPVA(4,7) = 1
        ITOPVA(4,9) = 1
        ITOPVA(4,IQ) = 1
        ITOPVA(4,IM) = 1
        ITOPVA(4,IV) = 1
      ENDIF
C
    1 RETURN
      END
C
C~FORAUS_BPM0~C
C
C FORTRAN AUSILIARIO DEL MODULO POMPA CENTRIFUGA
C PER LA SUA SCRITTURA VEDERE MANUALE D'USO O
C UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD.
C
C*********** BREVE SPIEGAZIONE DEI PARAMETRI DELLA SUBROUTINE ******************
C
C      SUBROUTINE DPU_B0(TYP,QVNOM,OMNOM,DPNOM,CNOM,ETANOM,Q,RO,OM,DP,CRES)
C
C  Parametri in ingresso: TYP,QVNOM,OMNOM,DPNOM,CNOM,ETANOM,Q,RO,OM
C  Parametri in uscita  : DP,CRES
C
C      SUBROUTINE UTENTE: DEVE FORNIRE IL VALORE DI DP E CRES IN
C      FUNZIONE DELLE ALTRE VARIABILI.
C      SIGNIFICATO DELLE VARIABILI DI INGRESSO-USCITA:
C
C       TYP = DATO A DISPOSIZIONE DELL'UTENTE PER DISTINGUERE
C             DIVERSE CARATTERISTICHE CONTENUTE IN QUESTA SUBROUTINE
C       QVNOM = PORTATA NOMINALE (M**3/S)
C       OMNOM = NUMERO DI GIRI NOMINALE (RAD/S)
C       DPNOM = PREVALENZA NOMINALE (PA)
C       CNOM = COPPIA NOMINALE (N*M)
C       ETANOM=RENDIMENTO NOMINALE
C       Q = PORTATA EFFETTIVA (M**3/S)
C       RO = DENSITA' EFFETTIVA (KG/M**3)
C       OM = VELOCITA' EFFETTIVA (RAD/S)
C       DP = PREVALENZA EFFETTIVA (PA)
C       CRES = COPPIA RESISTENTE EFFETTIVA (KG*M)
C
C       ESEMPIO DI SUBROUTINE:
C
C****************CARATTERISTICA POMPA*********************
CC        A=1.22
CC        OMS=OM/OMNOM
CC        QS=Q/QVNOM
CC        DP=DPNOM*(A*OMS**2-(A-1.)*QS*ABS(QS))
C
C       QUANDO LA POMPA FUNZIONA A BOCCA CHIUSA (Q=0) E A VELOCITA'
C       NOMINALE (OM=OMNOM), DP=DPNOM*A.
C       A DUNQUE DEFINISCE LA PREVALENZA A BOCCA CHIUSA
C
C****************FORMULA DEL RENDIMENTO*******************
CC        IF(OMS.LT.1.E-4)GO TO 125
CC        RID=QS/OMS
CC        ETA=ETANOM*(-RID**2+2.*RID)
C
C****************COPPIA RESISTENTE***********************
CC        IF(ETA.LT.1.E-4)GO TO 125
CC        OME=OM
CC        IF(OME.LE.1.E-3)OME=1.E-3
CC        CRES=Q*DP/OME/ETA
CC        GO TO 130
CC125     CRES=0.5*DP/DPNOM*CNOM
CC130     CONTINUE
CC        END
C
C       FINE ESEMPIO .
C
C
C************ INIZIO DEL TESTO FORTRAN DA SCRIVERE *****************************
C
C      SUBROUTINE DPU_B0(TYP,QVNOM,OMNOM,DPNOM,CNOM,ETANOM,Q,RO,OM,DP,CRES)
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      RETURN
C      END
C
C~FORAUS_BPM0~C
