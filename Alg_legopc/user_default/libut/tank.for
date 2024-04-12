C**********************************************************************
C modulo tank.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)tank.f	5.2
C**********************************************************************
C
      SUBROUTINE TANKI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/TANK01/IBLOC
      COMMON/TANK02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'TANK'/
C
      CALL TANKI4(IOB,MOD)
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      NSTATI =  4
      NUSCIT =  2
      NINGRE =  6
      WRITE(IFO,3001)IOB
 3001 FORMAT('PCAV',A4,2X,
     $'--US-- STEAM PRESSURE IN THE CAVITY')
      WRITE(IFO,3002)IOB
 3002 FORMAT('HVCA',A4,2X,
     $'--US-- STEAM ENTHALPY IN THE CAVITY')
      WRITE(IFO,3003)IOB
 3003 FORMAT('HLCA',A4,2X,
     $'--US-- WATER ENTHALPY IN THE CAVITY')
      WRITE(IFO,3004)IOB
 3004 FORMAT('MLCA',A4,2X,
     $'--US-- WATER MASS IN THE CAVITY')
      WRITE(IFO,3005)IOB
 3005 FORMAT('LIV%',A4,2X,
     $'--UA-- WATER LEVEL IN THE CAVITY')
      WRITE(IFO,3006)IOB
 3006 FORMAT('PFCA',A4,2X,
     $'--UA-- PRESSURE ON THE BOTTOM OF THE CAVITY')
C$MISC      WRITE(IFO,4006)IOB
C$MISC 4006 FORMAT('HFCA',A4,2X,
C$MISC     $57H--UA--     ENTALPIA LIQUIDO SUL FONDO CAVITA'            )
      WRITE(IFO,3007)IOB
 3007 FORMAT('WMIC',A4,2X,
     $'--IN-- FLOW RATE OF WATER-STEAM ON THE BOTTOM OF THE CAVITY')
      WRITE(IFO,3008)IOB
 3008 FORMAT('HMIC',A4,2X,
     $'--IN-- ENTHALPY OF WATER-STEAM AT THE INLET OF THE CAVITY')
      WRITE(IFO,3009)IOB
 3009 FORMAT('WAIC',A4,2X,
     $'--IN-- WATER FLOW RATE AT THE INLET OF THE CAVITY')
      WRITE(IFO,3010)IOB
 3010 FORMAT('HAIC',A4,2X,
     $'--IN-- WATER ENTHALPY AT THE INLET OF THE CAVITY')
      WRITE(IFO,3011)IOB
 3011 FORMAT('WVCA',A4,2X,
     $'--IN-- STEAM FLOW RATE AT THE OUTLET OF THE CAVITY')
      WRITE(IFO,3012)IOB
 3012 FORMAT('WAUC',A4,2X,
     $'--IN-- WATER FLOW RATE AT THE OUTLET OF THE CAVITY')
C$MISC      WRITE(IFO,4012)IOB
C$MISC 4012 FORMAT('ALFW',A4,2X,
C$MISC     $'--IN--     FRAZIONE DI PORTATA INGRESSO CAVITA` CHE SI MESCOLA
C$MISC     $UNIFORMEMENTE' )
      RETURN
      END
      SUBROUTINE TANKI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/TANK01/IBLOC
      COMMON/TANK02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      WRITE(IBLOC,5000)MOD,IOB
 5000 FORMAT(2A4)
C
      RETURN
      END
      SUBROUTINE TANKI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBLOC1,IBLOC2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION XYU(*), VAR(MX1,*), DATI(*), CNXYU(*), TOL(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C--- CAVITA'
C
      GOTO(1,10),IFUN
C
    1 WRITE(14,101) 'TYPE_CAV','VOL.CAV.','MISURA_Y',
     1             'X_OVER  ','X_UNDER ','ZERO_Y  ',
     2       'VOL_Y   ','GAMMA_Y ','SEZ_Y   '
  101 FORMAT(3(4X,A8,' =',10X,'*'))
      RETURN
C
   10 READ(14,102)
C
      READ(14,102) TYP,VCAV,FY,
     1      XOV,XUN ,ZERY,
     2      VY  ,GY ,SEZY
  102 FORMAT(3(14X,F10.0,1X))
C
C--------RIEMPIMENTO VETTORE DATI
C
      AML0=VCAV*200.
C
      DATI(ID2)  =AML0
      DATI(ID2+1)=TYP
      DATI(ID2+2)=VCAV
      DATI(ID2+3)=FY
      DATI(ID2+4)=XOV/100.
      DATI(ID2+5)=XUN/100.
      DATI(ID2+6)=ZERY
      DATI(ID2+7)=VY
      DATI(ID2+8)=GY
      DATI(ID2+9)=SEZY
C ! VUOTO = .FALSE.
      DATI(ID2+10)=1.
C ! PIENO = .FALSE.
      DATI(ID2+11)=1.
      ID2=ID2+11
C
C--------NORMALIZZAZIONI
C
      CNXYU(IV1   )=P0
      CNXYU(IV1+1 )=H0
      CNXYU(IV1+2 )=H0
      CNXYU(IV1+3 )=AML0
      CNXYU(IV1+4 )=100.
      CNXYU(IV1+5 )=P0
C$MISC      CNXYU(IV1+6 )=H0
      CNXYU(IV1+6 )=W0
      CNXYU(IV1+7 )=H0
      CNXYU(IV1+8 )=W0
      CNXYU(IV1+9 )=H0
      CNXYU(IV1+10)=W0
      CNXYU(IV1+11)=W0
C$MISC      CNXYU(IV1+13)=1.
C maggiore toller. su Y se misura di volume
C$SPELTA
C      IF(FY.GT.0.) TOL(5)=1.E-3
C$SPELTA
C
      RETURN
      END
      SUBROUTINE TANKC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                    IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*), XYU(*), DATI(*), RNI(*)
      EXTERNAL TANK
C
C--- CAVITA'
C
      GOTO(10,20,30),IFUN
C
   10 DO I=1,6
      DO J=1,12
      AJAC(I,J)=1.
      END DO
      END DO
      RETURN
C
   20 CALL TANK(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
   30 NSTATI=4
      NUSCIT=2
      NINGRE=6
      EPS   =1.E-3
      EPSLIM=1.E-4
C
      CALL TNAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     1           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,TANK)
      RETURN
      END
      SUBROUTINE TNAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1              NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,RESIDUI)
C
C routine PARTICOLARE di calcolo jacobiano numerico con DERIVATE +/-
C con incrementi +/- EPS in p.u. ( valori minimi assoluti EPSLIM )
C i residui devono essere calcolati dalla routine ( da dich.EXTERNAL )
C SUBROUTINE RESIDUI(IFUN,IXYU,XYU,IPD,DATI,RN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100),CCRN(50),CCXYU(100)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      EXTERNAL RESIDUI
C
      NRIG=NSTATI+NUSCIT
      NCOL=NRIG+NINGRE
C
      DO 30 J=1,NCOL
      VAR=EPS*XYU(IXYU+J-1)
      IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C$SPELTA
C_____________ INCREMENTO SULLA PRESSIONE
      IF(J.EQ.1.OR.J.EQ.6)VAR=.01*XYU(IXYU+J-1)
C$SPELTA
C
      DO 10 K=1,NCOL
      CXYU(K)=XYU(IXYU+K-1)
      CCXYU(K)=XYU(IXYU+K-1)
      IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
      IF(K.EQ.J) CCXYU(K)=CCXYU(K)-VAR
   10      CONTINUE
C
C     residui(ifun,ixyu,xyu,ipd,dati,rn)
C
      CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
      CALL RESIDUI(3,1,CCXYU,IPD,DATI,CCRN)
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(CRN(I)-CCRN(I))/(2.*VAR)
      IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
   20      CONTINUE
C
   30      CONTINUE
C
      RETURN
      END
      SUBROUTINE TANK(IFUN,IXYU,XYU,IPD,DATI,RN)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION XYU(*),DATI(*),RN(*)
      LOGICAL KREGIM,VUOTO,PIENO
      COMMON/REGIME/KREGIM
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
	COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
      PARAMETER ( ZERO = 0. )
C
      P0SW0  =P0/W0
      H0SW0  =H0/W0
      W0H0   =W0*H0
      P0SW0H0=P0/W0H0
      AML0   =DATI(IPD)
C
C--- DECODIFICA VARIABILI
C
      P  =XYU(IXYU)
      HG =XYU(IXYU+1)
      HL =XYU(IXYU+2)
      AML=XYU(IXYU+3)
C
      PSI  =P*P0
C
C____ PROTEZIONI PER PRESSIONI TROPPPO BASSE O TROPPO ALTE
C
      IF(PSI.LT.610.) PSI=610.
      IF(PSI.GT.220.E5)PSI=220.E5
C
      HGSI =HG*H0
      HLSI =HL*H0
      AMLSI=AML*AML0
C
      YLG=XYU(IXYU+4)
      PD =XYU(IXYU+5)
C$MISC      HD =XYU(IXYU+6)
C
      WR =XYU(IXYU+6)
      HR =XYU(IXYU+7)
      WA =XYU(IXYU+8)
      HA =XYU(IXYU+9)
      WV =XYU(IXYU+10)
      WD =XYU(IXYU+11)
C$MISC      CW =XYU(IXYU+13)
C
C--- DECODIFICA DATI
C
      TYP  =DATI(IPD+1)
      VCAV =DATI(IPD+2)
      FY   =DATI(IPD+3)
      RXOV =DATI(IPD+4)
      RXUN =DATI(IPD+5)
      ZERY =DATI(IPD+6)
      VY   =DATI(IPD+7)
      GY   =DATI(IPD+8)
      SEZY =DATI(IPD+9)
      STAT =DATI(IPD+10)
      STOT =DATI(IPD+11)
C
      CALL TANKPAR(TYP,PSI,TAUG,TAUL,BETA,ALFA,AKQ,AKW)
C
C svuotamento zona liquido
C
      IF(KREGIM) THEN
	  VUOTO=.FALSE.
	  IF(AMLSI.LE.AML0*1.E-4) VUOTO=.TRUE.
	  DATI(IPD+10)=1.
	  IF(VUOTO) DATI(IPD+10)=0.
      ELSE
	IF( (IFUN.NE.2).OR.(ITERT.NE.0)) THEN
	  VUOTO=STAT.LT.0.5
	ELSE
	   VUOTO=.FALSE.
	   IF(AMLSI.LE.AML0*1.E-4) VUOTO=.TRUE.
	   DATI(IPD+10)=1.
	   IF(VUOTO) DATI(IPD+10)=0.
	ENDIF
      ENDIF
C        IF(VUOTO)WRITE(6,*)'  VUOTO E` VERO'
C
      IF(VUOTO) AMLSI=0.0
C
C--- tavole vapore
C
      CALL SATUR(PSI,3,ROWSAT,ROVSAT,NFL)
	NFL=1
      SL=SHEV(PSI,HLSI,NFL)
      XL=YEV(PSI,SL,NFL)
      TL=TEV(PSI,SL,NFL)
      ROL=ROEV(PSI,SL,NFL)
      DRHL=BEV(PSI,SL,NFL)/TL
      DRPL=1./A2EV(PSI,SL,NFL)-DRHL/ROL
C
      SG=SHEV(PSI,HGSI,NFL)
      XG=YEV(PSI,SG,NFL)
      TG=TEV(PSI,SG,NFL)
      ROG=ROEV(PSI,SG,NFL)
C$SPELTA
       IF(PSI.LT.5.E5) THEN
       ROG=ROVSAT
       ENDIF
C$SPELTA
      DRHG=BEV(PSI,SG,NFL)/TG
      DRPG=1./A2EV(PSI,SG,NFL)-DRHG/ROG
C
      CALL SATUR(PSI,2,HWSAT,HVSAT,NFL)
      HVSAT=HVSAT/H0
      HWSAT=HWSAT/H0
C
C$SPELTA
C______ E` STATA DISABILITATA LA MISURA DI LIVELLO COMPRENDENTE LE BOLLE
C
CCC      IF(FY.LE.0.) THEN
C livello (misura di peso)
      ROY=MAX(ROL,ROWSAT)
      VLIV = AMLSI*(1-XL)/ROY
      VGAS = VCAV-VLIV
CCC      ELSE
C livello (misura di pelo libero)
CCC      ROY=ROL
CCC      VLIV = AMLSI/ROY
CCC      ENDIF
C$SPELTA
C
      IF(SEZY.LE.0.) THEN
      CALL TANKLIV(TYP,VLIV,Y,YTOT,AREA)
      ELSE
      Y    = (VLIV-VY)/(SEZY*GY)
      YTOT = Y*GY+ZERY
      AREA = SEZY
      ENDIF
C
C volumi
C
      VL=AMLSI/ROL
      VG=VCAV-VL
C
C riempimento totale di liquido
C
      IF(KREGIM)THEN
	PIENO=.FALSE.
	IF(VGAS.LE.VCAV*1.E-2) PIENO=.TRUE.
	DATI(IPD+11)=1.
	IF(PIENO) DATI(IPD+11)=0.
	GOTO 21
      ENDIF
C
      IF( (IFUN.NE.2).OR.(ITERT.NE.0)) THEN
	PIENO=STOT.LT.0.5
      ELSE
   20   PIENO=.FALSE.
	IF(VGAS.LE.VCAV*1.E-2) PIENO=.TRUE.
	DATI(IPD+11)=1.
	IF(PIENO) DATI(IPD+11)=0.
      ENDIF
C      IF(PIENO)WRITE(6,*)'  PIENO E` VERO'
C
C
C uscita separatori
C
   21 CONTINUE
      XR    =(HR-HWSAT)/(HVSAT-HWSAT)
      CALL TANKSEP(TYP,RXOV,RXUN,XR,WR*W0,PSI,XOV,XUN)
C
C
      XOVSEP=MAX(XR,XOV)
      XUNSEP=MIN(XR,XUN)
C
C$SPELTA  (INVERSIONE DI PORTATA NELLA MISCELA ENTRANTE)
C
      IF(WR.LT.0.)THEN
	WRG=0.
	HRG=HG
	WRL=WR
	HRL=HL
C
      ELSE
	HRG=HWSAT+XOVSEP*(HVSAT-HWSAT)
	HRL=HWSAT+XUNSEP*(HVSAT-HWSAT)
	WRG=WR*(HR-HRL)/(HRG-HRL)
	WRL=WR-WRG
C$SPELTA
      ENDIF
C$$$$$$$$$$$$$$$$
C condensazione
C
C$SPELTA
      IF(PSI.GE.5.E5) THEN
	 WC =MAX(ZERO,VG*ROG*(XOV-XG)/(TAUG*W0))
      ENDIF
C$SPELTA
C evaporazione
C
      WEV=MAX(ZERO,AMLSI*(XL-XUN)/(TAUL*W0))
C
      IF(VUOTO.OR.PIENO) THEN
	WCSUP=0.
	QSUP=0.
      ELSE
C condensazione superficiale
	CALL SATUR(PSI,7,TSAT,ZOT,NFL)
	WCSUP=AKW*AREA*BETA*(TSAT-TL)/(HVSAT-HWSAT)/W0H0
C potenza di scambio superficiale
	QSUP =AKQ*AREA*(TG-TSAT)*(1+ALFA*BETA*(TSAT-TL))/W0H0
      ENDIF
	IF(VUOTO)WEV=0.
	IF(PIENO)WC=0.
C
C--- RESIDUI
C
      RN(5)=YLG-Y
      RN(6)=PD-P-ROY*9.81*YTOT/P0
C
C$MISC      IF(WD.LE.0.)THEN
C$MISC         DELTH=0.
C$MISC      ELSE
C$MISC         DELTH=(1-CW)*WA*(HL-HA)/WD
C$MISC      ENDIF
C$MISC      RN(7)=HD-HL+DELTH
C
C$MISC      WLU=WD-(1.-CW)*WA
C$MISC      SOMWL =CW*WA+WRL-WLU+WCSUP+WC-WEV
C$MISC      SOMHWL=CW*WA*(HA-HL)+WRL*(HRL-HL)+WCSUP*(HVSAT-HL)+
C$MISC     $         WC*(HWSAT-HL)-WEV*(HVSAT-HL)+QSUP
C
      SOMWL =WA+WRL-WD+WCSUP+WC-WEV
      SOMHWL=WA*(HA-HL)+WRL*(HRL-HL)+WCSUP*(HVSAT-HL)+
     $         WC*(HWSAT-HL)-WEV*(HVSAT-HL)+QSUP
      SOMWG =WRG-WV+WEV-WCSUP-WC
C$SPELTA
      SOMHWG=WRG*(HRG-HG)+WEV*(HVSAT-HG)-
     $         WC*(HWSAT-HG)-QSUP
      IF(PSI.LT.5.E5) THEN
	 WC=(WRG*(HRG-HG)+WEV*(HVSAT-HG)-QSUP)/
     $   (HWSAT-HG)
	 IF(WC.LT.0.)WC=0.
      ENDIF
C$SPELTA
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
	WVD=0.
	IF(VUOTO)WVD=WD-WRL-WA
	XGG=(HL-HWSAT)/(HVSAT-HWSAT)
	IF(XGG.LT.0.)XGG=0.
	IF(XGG.GT.1.)XGG=1.
	WLDD=WD*(1.-XGG)
	WVDD=WD-WLDD
      IF(VUOTO)SOMWL =WA+WRL-WLDD+WC
      IF(VUOTO)SOMWG =WRG-WV-WVDD-WC
	XGG=(HG-HWSAT)/(HVSAT-HWSAT)
	IF(XGG.LT.0.)XGG=0.
	IF(XGG.GT.1.)XGG=1.
	WLGU=WV*(1.-XGG)
	WVGU=WV-WLGU
      IF(PIENO)SOMWL =WA+WRL-WLGU-WD-WEV
      IF(PIENO)SOMWG =WRG-WVGU+WEV
C
      IF(KREGIM) THEN
C
	IF(VUOTO)THEN
	      IF(WD.GT.0) THEN
	       HVV=(WA*HA+WRL*HRL+WVD*HG)/WD
	      ELSE
	       HVV=HVSAT
	      ENDIF
	  SOMHWL=HVV-HL
	ENDIF
C
	IF(VUOTO)SOMHWG=HG-HVSAT
	IF(VUOTO)SOMWL =WA+WRL-WLDD
	IF(VUOTO)SOMWG =WRG-WV-WVDD
	IF(PIENO)SOMHWG=(HG-HL)*WV
	IF(PIENO)SOMHWL=WA*HA+WR*HR-(WV+WD)*HL
	IF(PIENO)SOMWL =WA+WR-WD-WV
	IF(PIENO)SOMWG =WRG-WVGU
       RN(1)=SOMWG
C$SPELTA
       RN(2)=SOMHWG
       IF(PSI.LT.5.E5) THEN
	 RN(2)=WC
       ENDIF
C$SPELTA
       RN(3)=SOMHWL
       RN(4)=SOMWL
      ELSE
C
      AL= ROL/W0
      BL= VL*DRPL*P0SW0
      CL= VL*DRHL*H0SW0
      EL=-VL*P0SW0H0
      FL= AMLSI/W0
C
      AG=-ROG/W0
	IF(PIENO)AG=-ROVSAT/W0
      BG= VG*DRPG*P0SW0
      CG= VG*DRHG*H0SW0
      EG=-VG*P0SW0H0
      FG= VG*ROG/W0
C$SPELTA
       IF(PSI.LT.5.E5) THEN
	 PPSI=PSI+500.
	 CALL SATUR(PPSI,3,RROWSAT,RROVSAT,NFL)
	 DRPG=(RROVSAT-ROVSAT)/500.
	 BG= VG*DRPG*P0SW0
	 CG=0.
	 EG=0.
	 FG=1.
       ENDIF
C$SPELTA
C
      AA=SOMWL*FL-SOMHWL*CL
      BB=SOMWG*FG-SOMHWG*CG
      CC=BL*FL-EL*CL
      DD=BG*FG-EG*CG
C
       IF(VUOTO) THEN
	 PP =(-FG*AG*MAX(ZERO,SOMWL)+AL*BB)/(AL*DD)
	 HVV=(WA*HA+WRL*HRL+WVD*HG)/WD
	 HLP=(HVV-HL)/TAUL
	 HGP=(SOMHWG-EG*PP)/FG
C         WRITE(6,*)'   VUOTO AL TEMPO ',TEMPO
       ELSE
	 IF(PIENO)THEN
	   PP=(-FL*AL*MAX(ZERO,SOMWG)+AG*AA)/(AG*CC)
	   HLP=(SOMHWL-EL*PP)/FL
	   HGP=(HL-HG)/TAUG
C         WRITE(6,*)'   PIENO AL TEMPO ',TEMPO
	 ELSE
	   PP=(-FG*AG*AA+FL*AL*BB)/(-FG*AG*CC+FL*AL*DD)
	   HLP=(SOMHWL-EL*PP)/FL
C$SPELTA
	   HGP=(SOMHWG-EG*PP)/FG
	   IF(PSI.LT.5.E5) THEN
	     HGP=(HVSAT-HG)/1.
	   ENDIF
C$SPELTA
C
	 ENDIF
       ENDIF
      AMLP=SOMWL*W0/AML0
C
      RN(1)=PP
      RN(2)=HGP
      RN(3)=HLP
      RN(4)=AMLP
C
      ENDIF
      RETURN
      END
      SUBROUTINE TANKLIO(VCAV,RCAV,HLCAV,Y,YTOT,SEZ)
C
C CALCOLA IL LIVELLO  IN UN CILINDRO ORIZZONTALE
C
C          Y  livello diviso 100
C          YTOT livello in metri
C          SEZ  superficie del pelo libero
C NOTI:
C     VCAV  volume occupato
C     RCAV  raggio del cilindro
C     HLCAV lunghezza del cilindro
C
C ESECUZIONE
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      Y0=Y
      VMAX=RCAV*RCAV*3.141592*HLCAV
      IF(VCAV.LT.VMAX)GO TO 99
      YTOT=2*RCAV
      Y=YTOT/100.
      SEZ=0.
      RETURN
   99 IF(VCAV.GT.1.E-3)GO TO 98
      YTOT=0.
      Y=0.
      SEZ=0.
      RETURN
C
C     CALCOLO IETERATIVO SECONDO NEWTON-RAPHSON
C
   98 IT=0
      Y=RCAV
    1 IT=IT+1
C
C ALFA: ANGOLO AL CENTRO DEL SEGMENTO CIRCOLARE
C
      ALFA=ACOS((RCAV-Y)/RCAV)
      AST=RCAV**2.*ALFA-RCAV*(RCAV-Y)*SIN(ALFA)
C
C   RESIDUO
C
      RES=VCAV-HLCAV*AST
C
      IF(ABS(RES).LT.1.E-4)GO TO 10
      IF(IT.GT.100)GO TO 20
C
C     JACOBIANO
C
      DALFA=1./(RCAV*SQRT(1.-((RCAV-Y)/RCAV)**2.))
      DASOT=RCAV**2.*DALFA+RCAV*SIN(ALFA)+COS(ALFA)*RCAV*
     $ DALFA*(Y-RCAV)
      DVDY=DASOT*HLCAV
C
C   ITERAZIONE
C
      DY=RES/DVDY
      Y=Y+DY
      GO TO 1
C
C   SOLUZIONE
C
   10 CONTINUE
      YTOT=Y
      SEZ=HLCAV*2*SQRT(2*RCAV*Y-Y*Y)
      Y=Y/100.
      RETURN
   20 WRITE(6,1000)RES
 1000 FORMAT(//10X,'SUBROUTINE TANKLIO'/
     $10X,'SUPERATO ITERAZ. MAX - RESIDUO = ',E12.5//)
      GO TO 10
      END
      SUBROUTINE TANKPAR(TYP,P,TG,TL,BETA,ALFA,AKQ,AKW)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C ! coeff. scambio condensazione superficiale
      AKW=100.E3
C ! coeff. scambio convezione superficiale
      AKQ=100.
C ! peso sottoraf. nella convezione sup.
      ALFA=3.3
C ! sottoraf. sup./sottoraf. bulk
      BETA=0.1
C ! tempo condensazione
      TG=1.
C ! tempo evaporazione
      TL=1.
      RETURN
      END
      SUBROUTINE TANKSEP(TYP,RXOV,RXUN,XR,WR,P,XOV,XUN)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      XOV=RXOV
      XUN=RXUN
      RETURN
      END
C
C
C~FORAUS_TANK~C
C
C FORTRAN AUSILIARIO DEL MODULO CAVITA` LIQUIDO-VAPORE
C PER LA SUA SCRITTURA VEDERE MANUALE D'USO O
C UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD.
C
C*********** BREVE SPIEGAZIONE DEI PARAMETRI DELLA SUBROUTINE ******************
C
C  SUBROUTINE TANKLIV(TYP,VLIV,Y,YTOT,AREA)
C
C  La subroutine CNDLIV, in funzione dei valori TYP e VLIV
C  deve fornire  Y,YTOT,AREA
C
C  Parametri in ingresso:  TYP, VLIV
C  Parametri in uscita:    Y, YTOT, AREA
C
C  Significato dei parametri di chiamata:
C
C  TYP       = corrisponde al dato  TYPE_CAV richiesto in input (vedi scheda C1)
C              viene  utilizzato  per  distinguere  le  diverse  geometrie delle
C              cavita` trattate dal modulo  TANK  presenti contemporaneamente in
C              un modello matematico.  Viene  di  solito usato all'interno della
C              subroutine come puntatore;
C
C  VLIV      = volume occupato dal liquido in m**3;
C
C  Y         = rappresenta la misura del livello in percentuale rispetto alla
C              escursione massima misurabile dagli strumenti
C
C  YTOT      = rappresenta la misura del livello totale nella cavita`in metri;
C
C  AREA      = area della superficie di separazione fra la fase liquido e la
C              fase vapore
C
C************ INIZIO DEL TESTO FORTRAN DA SCRIVERE *****************************
C
C     SUBROUTINE  TANKLIV(TYP,VLIV,Y,YTOT,AREA)
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C     RETURN
C     END
C
C~FORAUS_TANK~C
CC
      SUBROUTINE TANKD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $ XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
