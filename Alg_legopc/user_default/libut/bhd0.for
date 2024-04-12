C**********************************************************************
C modulo bhd0.f
C tipo 
C release 5.4
C data 10/4/96
C reserver @(#)bhd0.f	5.4
C**********************************************************************
C--A. Rossi: modulo collettore
C            derivato da colt.f versione UFFICIALE ed adattato ad una  
C            soluzione di H2O e NaCl (09/jan/2001)
C---------------------------------------------------------------------- 
C
      SUBROUTINE BHD0I3(IFO,IOB,DEBL)
      COMMON/BHD000/IBLOC,NE,NU
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'BHD0'/
C
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C---CON TEMPERATURA METALLO ,TEMPERATURA ESTERNA E COEFFICIENTE DI
C---SCAMBIO ESTERNO IN EVIDENZA
C
C   ( VERSIONE CON POSSIBILITA' DI INTRODURRE UNA COMPRIMIBILITA' FITTIZIA
C     DEL FLUIDO (se GAMES < 0) AL FINE DI UTILIZZO DEL MODULO COME
C     SMORZATORE DI OSCILLAZIONI NUMERICHE - POLLACHINI 23/12/1993 )
C
C     A. Rossi : GAMES e' il nome attribuito a GEST nella routine bhd0
C
      CALL BHD0I4(IOB,MOD)
C
C
      NSTATI=0
      NUSCIT=4                
      NINGRE=3*(NE+NU)+2      
      NVAR=NUSCIT+NINGRE
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('HCOL',A4,2X,'--UA-- FLUID ENTHALPY IN THE MANIFOLD')
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('PCOL',A4,2X,'--UA-- FLUID PRESSURE IN THE MANIFOLD')
C
      WRITE(IFO,3405)IOB
 3405 FORMAT('TCOL',A4,2X,'--UA-- MANIFOLD METAL TEMPERATURE')
C
      WRITE(IFO,3406)IOB
 3406 FORMAT('FNAC',A4,2X,'--UA-- NaCl mass fr. in the manifold')
C
      DO 30 J=1,NE
	WRITE(IFO,3010)J,IOB,J
 3010   FORMAT('WE',I2,A4,2X,
     $    '--IN-- FLOW RATE IN THE ENTERING BRANCH N.',I2)
	WRITE(IFO,3015)J,IOB,J
 3015   FORMAT('HE',I2,A4,2X,
     $    '--IN-- ENTHALPY IN THE ENTERING BRANCH N.',I2)
	WRITE(IFO,3016)J,IOB,J
 3016   FORMAT('FE',I2,A4,2X,
     $    '--IN-- NaCl mass fr. IN THE ENTERING BRANCH N.',I2)
   30 CONTINUE
C
      DO 40 J=1,NU
	WRITE(IFO,3020)J,IOB,J
 3020   FORMAT('WU',I2,A4,2X,
     $    '--IN-- FLOW RATE IN THE COMING OUT BRANCH N.',I2)
	WRITE(IFO,3025)J,IOB,J
 3025   FORMAT('HU',I2,A4,2X,
     $    '--IN-- ENTHALPY IN THE COMING OUT BRANCH N.',I2,' (W<0)')
	WRITE(IFO,3026)J,IOB,J
 3026   FORMAT('FU',I2,A4,2X,
     $    '--IN-- NaCl mass fr. IN THE COMING OUT BRANCH N.',
     $    I2,' (W<0)')
   40 CONTINUE
      WRITE(IFO,3415)IOB
 3415 FORMAT('TEST',A4,2X,
     $  '--IN-- FLUID TEMPERATURE OUTSIDE THE MANIFOLD')
      WRITE(IFO,3425)IOB
 3425 FORMAT('GEST',A4,2X,
     $  '--IN-- THERMAL EXCHANGE COEFF. OUTSIDE THE MANIFOLD')
C
      RETURN
      END
C---------------------------------------------------------------------- 
      SUBROUTINE BHD0I4(IOB,MOD)
      COMMON/BHD000/IBLOC,NE,NU
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      MAX=40
C
   10 WRITE(6,101) MAX
  101 FORMAT(10X,'BRANCH POINT OF FLOW RATES'/
     $       10X,'NUMBER OF ENTERING BRANCHES (01 -',I3,') ?')
      READ(5,*) NE
      IF(NE.LE.0.OR.NE.GT.MAX) THEN
      WRITE(6,102) NE
  102 FORMAT(10X,'ERROR - N.ENT.=',I3,/)
      GOTO 10
      ENDIF
C
   15 WRITE(6,105) MAX
  105 FORMAT(10X,'NUMBER OF COMING OUT BRANCHES (01 -',I3,') ?')
      READ(5,*) NU
      IF(NU.LE.0.OR.NU.GT.MAX) THEN
      WRITE(6,106) NU
  106 FORMAT(10X,'ERROR - N.USC.=',I3,/)
      GOTO 15
      ENDIF
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
C---------------------------------------------------------------------- 
	SUBROUTINE BHD0I2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
	DIMENSION VAR(MX1,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
	PARAMETER (MAX=40)
        PARAMETER (GAM0=1000.)
	DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
	COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C
	GO TO(100,200),IFUN
C
  100   WRITE(14,500)'NU.TU.EN','NU.TU.US','VOLUME  ',
     1               'MASSA ME','CP MET. ','COND MET',
     1               'SPESSORE','SUP.  ES'
	RETURN
C
C---lettura e memorizzazione dati
C
  200   READ(14,502)
	READ(14,502) FNE,FNU,VOLUME,CM,CPM,COND,SPESS,SUPES
C
  500   FORMAT(3(4X,A8,' =',10X,'*'))
  502   FORMAT(3(14X,F10.2,1X))
C
C______________________________________________
C
       NE=FNE
       NU=FNU
	  HRIF=XYU(IV1  )
	  PRIF=XYU(IV1+1)
	  FRIF=XYU(IV1+3)
	  TEST=XYU(IV1+3+3*NE+3*NU+1)
C
	  ISOLATO=0
	CTMET=CM*CPM
	GAMET=2.*COND/SPESS
	DEQ=(VOLUME+SQRT(VOLUME**2+VOLUME*2.*SPESS*SUPES))*2./SUPES
	DATI(ID2  ) = NE
	DATI(ID2+1) = NU
	DATI(ID2+2) = VOLUME
	DATI(ID2+3) = CTMET
C       DATI(ID2+4) = Sk
C       DATI(ID2+5) = PK
C       DATI(ID2+6) = S
C       DATI(ID2+7) = P
	DATI(ID2+8) = PRIF
C	DATI(ID2+9) = TM  ! temporanea
	DATI(ID2+10)= GAMET
	DATI(ID2+11)= SUPES
C       DATI(ID2+12)= TM
	DATI(ID2+13)= HRIF
	DATI(ID2+14)= ISOLATO
	DATI(ID2+15)= DEQ
	DATI(ID2+16)= 1000.
	DATI(ID2+17)= FRIF
C	DATI(ID2+18)= ROK
C	DATI(ID2+19)= YK
C
	ID2 = ID2+19
C
C---costanti di normalizzazione
C
	CNXYU(IV1  ) = H0  ! FLUID ENTHALPY IN THE MANIFOLD
	CNXYU(IV1+1) = P0  ! FLUID PRESSURE IN THE MANIFOLD
	CNXYU(IV1+2) = T0  ! MANIFOLD METAL TEMPERATURE
	CNXYU(IV1+3) = 1.  ! NaCl mass fr. in the manifold
C
	NT=NE+NU
	I0=IV1+3
	DO J = 1,NT
	  JW=3*J-2
	  JH=JW+1
	  JF=JH+1
	  CNXYU(I0+JW) = W0  ! FLOW RATE IN THE BRANCH N.
	  CNXYU(I0+JH) = H0  ! ENTHALPY IN THE BRANCH N.
	  CNXYU(I0+JF) = 1.  ! NaCl mass fr. IN THE BRANCH N.
	ENDDO
	CNXYU(I0+3*NT+1) = T0    ! FLUID TEMPERATURE OUTSIDE THE MANIFOLD
	CNXYU(I0+3*NT+2) = GAM0  ! THERMAL EXCHANGE COEFF. OUTSIDE THE MANIFOLD 
C
	RETURN
	END
C---------------------------------------------------------------------- 
	SUBROUTINE BHD0C1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
	DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C   CALCOLO RESIDUI
C
	PARAMETER (MAX=40)
	DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
	COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
	COMMON/PARPAR/NUL(7),ITERT
	COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
	EXTERNAL BHD0
	LOGICAL KREGIM
	COMMON/REGIME/KREGIM
C
	NE=DATI(IPD)       ! Number of ENTERING BRANCH
	NU=DATI(IPD+1)     ! Number of COMING OUT BRANCH
	NVAR=3*(NE+NU)+6   ! Number of variables
C
        NSTATI =0
        NUSCIT =4
        NINGRE =3*(NE+NU) +2
C-------
	GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100   DO I=1,NUSCIT
	  DO J =1,NVAR
	    AJAC(I,J) = 1.
	  END DO
	END DO
	RETURN
C
C---calcolo residui
C
  200   CONTINUE
C        WRITE(6,*) IBL1,IBL2
	CALL BHD0(IFUN,IXYU,XYU,IPD,DATI,RNI)
	RETURN
C
C---calcolo jacobiano NUMERICO
C
  300   CONTINUE
      EPS   =1.E-3
      EPSLIM=1.E-4
      CALL BHDJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,BHD0)
C
      RETURN
      END
C---------------------------------------------------------------------- 
C**************************************************************************
      SUBROUTINE BHDJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1              NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,RESIDUI)
C
C routine generale di calcolo jacobiano numerico con DERIVATE +/-
C con incrementi +/- EPS in p.u. ( valori minimi assoluti EPSLIM )
C i residui devono essere calcolati dalla routine ( da dich.EXTERNAL )
C SUBROUTINE RESIDUI(IFUN,IXYU,XYU,IPD,DATI,RN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(5),CXYU(100),CCRN(5),CCXYU(100)
	COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      EXTERNAL RESIDUI
C
      NRIG=NSTATI+NUSCIT
      NCOL=NRIG+NINGRE
      EPSPLIM=50./P0
C
      DO 30 J=1,NCOL
      VAR=EPS*XYU(IXYU+J-1)
      IF(J.EQ.2)THEN
        IF(ABS(VAR).LT.EPSLIM) VAR=EPSPLIM
      ELSE
        IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
      ENDIF 
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
C**************************************************************************
C---------------------------------------------------------------------- 
	SUBROUTINE BHD0(IFUN,IXYU,XYU,IPD,DATI,RNI)
	DIMENSION XYU(*),DATI(*),RNI(*)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C   CALCOLO RESIDUI
C
	PARAMETER (MAX=40)
        PARAMETER (GAM0=1000.)
	DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX),FE(MAX),FU(MAX)
C
	COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
	COMMON/PARPAR/NUL(7),ITERT
	COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
	LOGICAL KREGIM
	COMMON/REGIME/KREGIM
        COMMON/TOLEG00/TOLIN(100)
C
C____________ COEFFICIENTI PER DEFINIRE LO SCAMBIO FLUIDO PARETE
C             COPIATI DA GAMTERT
C
	DATA CCW/4.0125/,CCV/7.495/,AAW/0.0375/,AAV/0.0167E-5/
C
C---calcolo residui
C
C
C---decodifica dati
C
	NE    = DATI(IPD   )
	NU    = DATI(IPD+1 )
	VOL   = DATI(IPD+2 )
	CTMET = DATI(IPD+3 )
	PRIF  = DATI(IPD+8 )
	GAMET = DATI(IPD+10)
	SUPES = DATI(IPD+11)
C
	HRIF    = DATI(IPD+13)
	ISOLATO = DATI(IPD+14)
	DEQ     = DATI(IPD+15)
C
C---decodifica variabili
C
	HNODO = XYU(IXYU  )
	PNODO = XYU(IXYU+1)
	TMMET = XYU(IXYU+2)
	FNaCl = XYU(IXYU+3)
C
	I0=IXYU+3
	DO J = 1,NE
	  JW=3*J-2
	  JH=JW+1
	  JF=JH+1
	  WE(J) = XYU(I0+JW)
	  HE(J) = XYU(I0+JH)
	  FE(J) = XYU(I0+JF)
	END DO
	I0=I0+3*NE
	DO J = 1,NU
	  JW=3*J-2
	  JH=JW+1
	  JF=JH+1
	  WU(J) = XYU(I0+JW)
	  HU(J) = XYU(I0+JH)
	  FU(J) = XYU(I0+JH)
	END DO
C
	TEST  = XYU(IXYU+3*(NE+NU)+4)
	GAMES = XYU(IXYU+3*(NE+NU)+5)*GAM0
C
C----- GAMES E' UTILIZZATO COME MOLTIPLICATORE DI DRO/DP (SPELTA !5/06/94)
C----- UTILIZZO DI UNA DRO/DP = 1.E+04 (==> C=100 m/s) PER
C----- INTRODURRE UNA COMPRIMIBILITA' FITTIZIA DEL FLUIDO
C
        IDREN=0
	DRODPMIN = 0.03E-5
	IF(GAMES.LT.0.) THEN
         GAMES  = - GAMES
C        DRODPMIN = 1.E-04 * GAMES
         IDREN=1
	ENDIF
C
C----------------------------calcolo residui
C
C
C----------------------------flussi di massa ed energia e di NaCl
C                             
	SUME  = 0.
	SUMHE = 0.
	SUMU  = 0.
	SUMFE = 0.
C                             
	DO J= 1,NE
	  IF(WE(J).GT.0.)            THEN
	    SUME=SUME+WE(J)
	    SUMHE=SUMHE+WE(J)*HE(J)
	    SUMFE=SUMFE+WE(J)*FE(J)
				     ELSE
	    SUMU=SUMU+WE(J)
	  ENDIF
	END DO
	DO J= 1,NU
	  IF(WU(J).LT.0.)            THEN
	    SUME=SUME-WU(J)
	    SUMHE=SUMHE-WU(J)*HU(J)
	    SUMFE=SUMFE-WU(J)*FU(J)
				     ELSE
	    SUMU=SUMU-WU(J)
	  ENDIF
	END DO
C
      WW=ABS((SUME-SUMU)*W0/2.)
      IF(WW.GT.1000.)WW=1000.
      IF(WW.LT.0.1)WW=0.1
      DELTAT=DTINT
      IF(DELTAT.LE.0.)DELTAT=1.
      WWTOL=WW*.01*DELTAT/W0
      IF(WWTOL.LT.1.E-04)WWTOL=1.E-04
C
      TOLIN(2)=WWTOL
C
	P = PNODO*P0
	H = HNODO*H0
	C = W0*DTINT
	X = FNaCl
C
C------  CASAM    5 Gennaio 1994 -----------
C
C______ PROTEZIONE PER PRESSIONI ED ENTALPIE SBALLATE
C           reintrodotte da vecchio COLN
C
	IF(P.GT.400.E5) THEN
	  P=400.E5
	ELSE IF(P.LT.610.) THEN
	  P=610.
	ENDIF
	IF(H.GT.4200.E3) THEN
	  H=4200.E3
	ELSE IF(H.LT.0.) THEN
	  H=0.
	ENDIF
C----------------------------normalizzazione frazione massica
        IF(X.LT.0.0) X = 0.
        IF(X.GT.0.999) X = 0.999
C----------------------------stazionario o transitorio ?
	IF(KREGIM) GO TO 1000
C----------------------------calcolo transitorio
          CALL T_FOR(P,H,X,T)
          CALL S_FOR(T,X,S)       !  S  = SHEV(P,H,1)
C
	  DELTAP = 1.E-4*P
	  IF(DELTAP.LT.10.)DELTAP=10.
          DELTAS = 1.E-3*S
C
C------  CASAM    5 Gennaio 1994 -----------
C
	  IF(P.GE.400.E+05)THEN
	    P1 = P - DELTAP
	    P2=P1
	  ELSE
	    IF(P.LE.600.)THEN
	      P2 = P + DELTAP
	      P1 = P2
	    ELSE
	      P1 = P - DELTAP
	      P2 = P + DELTAP
	    ENDIF
	  ENDIF
          S1 = S + DELTAS
          S2 = S - DELTAS
          CALL TS_FOR(S1,X,TS1)
          CALL TS_FOR(S2,X,TS2)
          CALL ROC_FOR(X,TS1,P,ROS1)
          CALL ROC_FOR(X,TS2,P,ROS2)
C
          CALL ROC_FOR(X,T,P1,RO1)             ! RO1   =ROEV(P1,S,1)
          CALL DRDP_FOR(RO1,DRODP1)            ! DRODP1=1./A2EV(P1,S,1)
          CALL DRDS_FOR(ROS1,TS1,X,DRODS1)     ! DRODS1=BEV(P1,S,1)
C
          CALL ROC_FOR(X,T,P2,RO2)             ! RO2   =ROEV(P2,S,1)
          CALL DRDP_FOR(RO2,DRODP2)            ! DRODP2=1./A2EV(P2,S,1)
          CALL DRDS_FOR(ROS2,TS2,X,DRODS2)     ! DRODS2=BEV(P2,S,1)
C-----------
	  RO   =(RO1+RO2)/2.
	  DRODP=(DRODP1+DRODP2)/2.
	  DRODS=(DRODS1+DRODS2)/2.
C----------
	IF(ITERT.LE.0.AND.IFUN.EQ.2) THEN         ! S =SHEV(P,H,1)
	  DATI(IPD+4)=S              ! memorizza entropia
	  DATI(IPD+5)=P              ! memorizza pressione
	  DATI(IPD+12)=DATI(IPD+9)   ! memorizza temp. metallo
          DATI(IPD+17)=X             ! memorizza la fraz. massica
          DATI(IPD+18)=RO            ! memorizza la densita della salamoia
	ENDIF
	SK  =DATI(IPD+4)
	PK  =DATI(IPD+5)
	TMK =DATI(IPD+12)
        XK  =DATI(IPD+17)
        ROK =DATI(IPD+18)
C-------------------------------------Titolo
C        CALL TISA_phf(P,H,X,HSS,TSATU,ROSATU,Y,HVS)
        Y = 0.0      !  (28/jan/01)
C-------------------------------------Memo titolo
	IF(ITERT.LE.0.AND.IFUN.EQ.2) THEN
          DATI(IPD+19) = y            ! memorizza il titolo della salamoia
	ENDIF
        YK = DATI(IPD+19)
C-------------------------------------Fine titolo
	  DELTAP = 1.E-4*P
	  IF(DELTAP.LT.10.)DELTAP=10.
          DELTAS = 1.E-3*S
C
C
C---- IPOTESI DI COMPRIMIBILITA' DEL FLUIDO [C=SQRT(1./DRODP)=100 m/s]
C
C	  IF(DRODP.LT.DROSDP) DRODP=DROSDP
	  IF(DRODP.LT.DRODPMIN) DRODP=DRODPMIN
C
C______ AGGIORNAMENTO COEFF. DI SCAMBIO
C
	IF(ITERT.LE.0.AND.IFUN.EQ.2) THEN
	  CC1=(SUME*W0)**0.8/DEQ
	  IF(Y.LE.0) THEN         ! ACQUA SOTTORAFFREDDATA
	    GAMI=CC1*(CCW+AAW*T)+10.
	  ELSE IF(Y.LT.1.) THEN   ! MISCELA 
	    GAMI=CC1*100.+10.
	  ELSE IF(Y.GE.1.) THEN   ! VAPORE SURRISCALDATO 
	    GAMI=CC1*(CCV+AAV*P)+10.
	  ENDIF
	  DATI(IPD+16)=GAMI
	ELSE
	  GAMI= DATI(IPD+16)
	ENDIF
C
	  GAMINT =SUPES* GAMET*GAMI/(GAMET+GAMI)
	  GAMEST =SUPES* GAMET*GAMES/(GAMET+GAMES)
C
C______ Integrazione equaz. energia nel metallo
C
	  DEN=(1.+DTINT*(GAMINT+GAMEST)/CTMET)
	  TM = (TMK+DTINT*(GAMINT*T/T0 + GAMEST*TEST)/CTMET)/DEN
	  DATI(IPD+9)=TM
Car-23/jan/2001-------------------------------agg.libuff by MIGL 23/jan/00
       HHLS=0.
       HHVS=0.
       QCOND=0.
Car-26/jan/2001----------Ritogliere  by MIGL 26/jan/00      
Car-26/jan/2001       IF(IDREN.EQ.1) THEN
Car-26/jan/2001         IF(P.LT.221.1E+05)THEN
Car-26/jan/2001Car-23/jan/2001           CALL SATUR(P,2,HHLS,HHVS,1)
Car-26/jan/2001           CALL TISA_phf(P,H,X,HHLS,TSATU,ROSATU,YU,HHVS)
Car-26/jan/2001         ELSE
Car-26/jan/2001Car-23/jan/2001           CALL SATUR(221.1E+05,2,HHLS,HHVS,1)
Car-26/jan/2001           CALL TISA_phf(221.1E+05,H,X,HHLS,TSATU,ROSATU,YU,HHVS)
Car-26/jan/2001         ENDIF
Car-26/jan/2001         TITPREC=YK     !YEV(PK,SK,1)
Car-26/jan/2001         ROPREC=ROK     !ROEV(PK,SK,1)
Car-26/jan/2001         TAUCOND=5.
Car-26/jan/2001         QCOND=ROPREC*VOL*(1.-TITPREC)/TAUCOND/W0
Car-26/jan/2001         HHLS=HHLS/H0
Car-26/jan/2001         HHVS=HHVS/H0
Car-26/jan/2001       ENDIF
Car-23/jan/2001-------------------------------agg.libuff--fine
C
C----------------------------residui
C______ Integrazione equaz. energia nel fluido
C
C	RNI(1)=VOL*RO*T*(S-SK)/W0/H0-DTINT*((SUMHE-SUME*HNODO)-
C     $                            GAMINT*(T-TM*T0)/W0/H0)
	RNI(1)=VOL*RO*T*(S-SK)/W0/H0-DTINT*((SUMHE-SUME*HNODO-
     $         QCOND*HHLS)-GAMINT*(T-TM*T0)/W0/H0)
C
C
C______ Integrazione equaz. massa  nel fluido
C
C	RNI(2)=VOL*(DRODP*(P-PK)+ DRODS*(S-SK))/W0-DTINT*(SUME+SUMU)
	RNI(2)=VOL*(DRODP*(P-PK)+ DRODS*(S-SK))/W0-
     $                            DTINT*(SUME+SUMU-QCOND)
C
C
C______ Temperatura metallo
C
	RNI(3)= TMMET-TM
C
C
C______ Integrazione equaz. massa NaCl nel fluido : FNAC=X
C
        RNI(4) = X - XK * ROK * VOL / (RO*VOL-SUMU*DTINT*W0) -
     $               SUMFE * DTINT*W0 / (RO*VOL-SUMU*DTINT*W0) 
C
	RETURN
C
C---calcolo dello stazionario
C
 1000   CONTINUE
          CALL T_FOR(P,H,X,T)                ! T  =TEV(P,S,1)
          CALL S_FOR(T,X,S)                  ! S=SHEV(P,H,1)
          CALL ROC_FOR(X,T,P,RO)             ! RO=ROEV(P,S,1)
C-------------------------------------Titolo ------  Y  =YEV(P,S,1)
Car-26/jan/2001        CALL TISA_phf(P,H,X,HSS,TSATU,ROSATU,Y,HVS)
          Y = 0.0     ! by MIGL 26/jan/01
C-------------------------------------Fine titolo
C
C          DEQ = 4.*VOL/SUPES           ! vecchia definizione di DEQ
	  CC1=(SUME*W0)**0.8/DEQ
C
	  IF(Y.LE.0) THEN               ! ACQUA SOTTORAFFREDDATA
	    GAMI=CC1*(CCW+AAW*T)+10.
	  ELSE IF(Y.LT.1.) THEN         ! MISCELA
	    GAMI=CC1*100.+10.
	  ELSE IF(Y.GE.1.) THEN         ! VAPORE SURRISCALDATO 
	    GAMI=CC1*(CCV+AAV*P)+10.
	  ENDIF
C
	  GAMINT =SUPES* GAMET*GAMI/(GAMET+GAMI)
	  GAMEST =SUPES* GAMET*GAMES/(GAMET+GAMES)
C	  WRITE(6,*) ' GAMI=',GAMI,' GAMET=',GAMET,' SUPES=',SUPES
C	  WRITE(6,*) ' GAMES=',GAMES
C	  WRITE(6,*) ' GAMEST=',GAMEST,' GAMINT=',GAMINT
C
	  TM= (GAMINT*T/T0+GAMEST*TEST)/(GAMINT+GAMEST)
C
	  RNI(1) = SUMHE-SUME*HNODO-GAMINT*(T-TM*T0)/W0/H0
	  RNI(2) = SUME+SUMU
	  RNI(3) = TMMET-TM
	  RNI(4) = X*SUME-SUMFE
C
	DATI(IPD+4)=S
	DATI(IPD+5)=P
	DATI(IPD+6)=S
	DATI(IPD+7)=P
	DATI(IPD+9) =TM
	DATI(IPD+12)=TM
	DATI(IPD+17)=X
	DATI(IPD+18)=RO
	DATI(IPD+19)=Y
C
	RETURN
	END
C
C---------------------------------------------------------------------- 
      SUBROUTINE BHD0D1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $  XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 BLOCCO, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
C
      DO I = 1, NUSCIT
	DO J = 1, NUSCIT+NINGRE
	  ITOPVA (I,J) = 1
	ENDDO
      ENDDO

C
C-----Equazione n. 1 (algebrica):
C
      SIGNEQ(1) = 'FLUID ENERGY CONSERV. INSIDE THE MANIFOLD'
      UNITEQ(1) = 'W'
      COSNOR(1) = W0*H0
C
C-----Equazione n. 2 (algebrica):
C
      SIGNEQ(2) = 'FLUID MASS CONSERV. INSIDE THE MANIFOLD'
      UNITEQ(2) = 'kg'
      COSNOR(2) = W0
C
C-----Equazione n. 3 (algebrica):
C
      SIGNEQ(3) = 'TEMPERATURE OF MANIFOLD METAL WALL COMPUT.'
      UNITEQ(3) = 'K'
      COSNOR(3) = T0
C
      RETURN
      END
C-----------------------------------------------------------------------
      SUBROUTINE TISA_phf(PI,HI,FI,HSATU,TSATU,ROSATU,YU,HVU)
C
C---  TITLE OF THE NaCl SOLUTION & saturation properties
C---  as function of pressure (PI), enthalpy (HI) and mass fraction (FI)
C---  of NaCl
C     Inlet parameters  : PI     = pressure (Pascal)
C                         HI     = enthalpy (j/Kg)
C                         FI     = NaCl mass fraction (per unit)
C     Outlet parameters : HSATU  = solution saturation enthalpy (j/Kg)
C                         TSATU  = solution saturation temperature (K)
C                         ROSATU = solution saturation density (Kg/m**3)
C                         YU     = solution title (p.u.)
C                         HVU    = water vapour enthalpy (j/Kg)
C                                  if title = 0 ==> HVU = 0.
C
C-------------------------------------Saturation properties
          X  =  FI
          CALL TSAT_FOR(PI,X,TSAT)
          CALL ROC_FOR(X,TSAT,PI,ROSAT)
          CALL H_FOR(TSAT,PI,ROSAT,X,HSAT)
C-------------------------------------Titolo
          Y  =  0.
          HV =  0.
C
          IF(HI.GT.HSAT) THEN
            NFL  =  1
            YV   =  1.
            SV   =  STEV(PI,TSAT,YV,NFL)
            HV   =  HEV(PI,SV,NFL)
            Y    = ( HI - HSAT ) / ( HV - HSAT )
          ENDIF
C
          IF(Y.LT.0.0) Y = 0.0
          IF(Y.GT.1.0) Y = 1.0
C-------------------------------------Fine titolo
          HSATU  = HSAT
          TSATU  = TSAT
          ROSATU = ROSAT
          YU     = Y
          HVU    = HV
C
      RETURN
      END
C-----------------------------------------------------------------------
