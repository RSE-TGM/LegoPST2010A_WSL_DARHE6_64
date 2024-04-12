C**********************************************************************
C modulo bvl0.f
C tipo 
C release 5.8
C data 11/19/97
C reserver @(#)bvl0.f	5.8
C**********************************************************************
C-- A. Rossi     : -nella C1, e probabilmente anche in altre routine 
C  (17/jan/2001)    o function, si calcola la pressione critica: aggiustare 
C                   RAP per la salamoia !!!!!
C                  -la function AVAL10 diventa B0AV10
C                  -la function AVNS10 diventa B0NS10
C                  -i common MOVA e MONTE diventano BVL0MV e BVL0MO
C                  -la function ROEV diventa BVL0RO
C                  -la function SHEV diventa BVL0SE ma questa funzione serve solo per
C                   calcolare RO e quindi non sara chiamata
C
      SUBROUTINE BVL0I3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/BVL000/IBLOC
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'BVL0'/
C
      CALL BVL0I4(IOB,MOD)
C
      NSTATI=0
      NUSCIT=1
      NINGRE=4 + 3
C
      IWP=0                           ! Uscita in portata
      IF(IBLOC(1:1).EQ.'+')IWP=1      ! Uscita in pressione a monte
      IF(IBLOC(1:1).EQ.'-')IWP=2      ! Uscita in pressione a valle
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
Car--18/jan/2001----------------------------------------------------
      IF(IWP.EQ.0) THEN               ! Uscita in portata  (IWP=0)
        WRITE(IFO,3007) IOB           ! WVAL - U
        WRITE(IFO,3013) IOB           ! PIVA - I
        WRITE(IFO,3012) IOB           ! PUVA - I
      ELSE
        IF(IWP.EQ.1) THEN             ! Uscita in pressione a monte (IWP=1)
          WRITE(IFO,3002) IOB         ! PIVA - U
          WRITE(IFO,3011) IOB         ! WVAL - I
          WRITE(IFO,3012) IOB         ! PUVA - I
        ELSE                          ! Uscita in pressione a valle (IWP=2)
          WRITE(IFO,3001) IOB         ! PUVA - U
          WRITE(IFO,3013) IOB         ! PIVA - I
          WRITE(IFO,3011) IOB         ! WVAL - I
        ENDIF
      ENDIF
      WRITE(IFO,3005)IOB              ! H  - I
      WRITE(IFO,3006)IOB              ! F  - I
      WRITE(IFO,3010)IOB              ! Z  - I
      WRITE(IFO,3015)IOB              ! Hi - I
      WRITE(IFO,3016)IOB              ! Fi - I
C-------------------------------Format------------------------------
 3001 FORMAT('PUVA',A4,2X,
     $  '--UA-- FLUID PRESSURE AT THE VALVE OUTLET')
 3002 FORMAT('PIVA',A4,2X,
     $  '--UA-- FLUID PRESSURE AT THE VALVE INLET')
 3005 FORMAT('HVAL',A4,2X,
     $  '--IN-- VALVE INLET FLUID ENTHALPY')
 3006 FORMAT('FNAC',A4,2X,
     $  '--IN-- VALVE INLET NaCl mass fraction')
 3007 FORMAT('WVAL',A4,2X,
     $  '--UA-- FLUID FLOW RATE IN THE VALVE')
 3010 FORMAT('ALZA',A4,2X,'--IN-- VALVE LIFT')
 3011 FORMAT('WVAL',A4,2X,'--IN-- FLUID FLOW RATE IN THE VALVE')
 3012 FORMAT('PUVA',A4,2X,'--IN-- FLUID PRESSURE AT THE VALVE OUTLET')
 3013 FORMAT('PIVA',A4,2X,'--IN-- FLUID PRESSURE AT THE VALVE INLET')
 3015 FORMAT('HINV',A4,2X,
     $  '--IN-- VALVE outlet FLUID ENTHALPY ( W<0 )')
 3016 FORMAT('FINV',A4,2X,
     $  '--IN-- VALVE outlet NaCl mass fraction ( W<0 )')

Car--18/jan/2001-----------------------------------------------------fine

C------------------------------------------------------------------------
C
      RETURN
      END
C
C------------------------------------------------------------------------
C
      SUBROUTINE BVL0I4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/BVL000/IBLOC
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
    2 CONTINUE
      WRITE(6,2999)
 2999 FORMAT(/5X,'GIVE A CHARACTER'
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
C------------------------------------------------------------------------
C
      SUBROUTINE BVL0I2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,NOM1,NOM2,
     $ IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      COMMON / NORM / P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON / BVL0MV / DUMMY1,DUMMY2,DUMMY3,IAREA,IMOVAL
      CHARACTER*4 NOMCAR,AZ,CF,WL1,P1L1,P1L2,P2L1,P2L2,HL1,HL2
     $,ZL1,DPAPE1,DPAPE2,DPCLO1,AR,WL2,ICV1,ZL2
      CHARACTER*1 ICV2
      DATA AZ/'ALFA'/,CF/'CFA '/,WL1/'PORT'/,WL2/'ATA'/
      DATA P1L1/'P1 M'/,P1L2/'ONTE'/,P2L1/'P2 V'/,P2L2/'ALLE'/
      DATA HL1/'ENTA'/,HL2/'LPIA'/,ZL1/'CORS'/,ZL2/'A '/
      DATA ICV1/'CVA'/,ICV2/' '/
      DATA FR1/'Frma'/,FR2/'NaCl'/
      DATA DPAPE1/'DP. '/,DPAPE2/'APER'/,DPCLO1/'CHIU'/
      DATA AR/'COD.'/
C
C     MODELLI PREVISTI :
C
C----ELIMINATO--->         CADIPO  (0,1)
C
C         VALVOLA SEMPLIFICATA NON SONICA (2,3)
C
C         VALVOLA SEMPLIFICATA SONICA (4,5)
C
C----ELIMINATO--->         MODELLO MOODY-MORRIS (6)
C
C
      GO TO (1,10),IFUN
C
C      SCRITTURA SUL FILE 14 DEI SIMBOLI DEI DATI DELLA VALVOLA
C
    1 WRITE(14,1010)
 1010 FORMAT('*   VALVE DATA (COD. = IDENTIFIER FOR MATHEMATICAL '
     $,'MODEL CHOICE)')
      WRITE(14,1020) AZ,CF,AR
 1020 FORMAT(3(4X,A4,4X,' =',10X,'*'),5X)
      WRITE(14,1030)
 1030 FORMAT('*   DATA RELATED TO THE DISCHARGING CHARACTERISTIC')
      WRITE(14,1040)ICV1,ICV2, WL1,WL2,P1L1,P1L2,P2L1,P2L2,HL1,HL2,
     $             ZL1,ZL2,FR1,FR2
      WRITE(14,1031)
 1031 FORMAT('*   DATA RELATED TO THE CHECK VALVE (IF PRESENT - '
     $,'DEPENDING ON COD.)')
      WRITE(14,1040)DPAPE1,DPAPE2,DPAPE1,DPCLO1
 1040 FORMAT(3(4X,2A4,' =',10X,'*'),5X)
      RETURN
C
C      LETTURA DAL FILE 14 DEI DATI DELLA VALVOLA
C
   10 READ(14,1060)
 1060 FORMAT(1X)
      READ(14,1060)
      READ(14,1080) ALFA,CFA,PODEL
      READ(14,1060)
      READ(14,1080)CVA, WL,P1L,P2L,HL,ZL,FL
      READ(14,1060)
      READ(14,1080)DPAP,DPCH
 1080 FORMAT(3(14X,F10.0,1X),5X)
      AREA=0.
C
C
C     CONTROLLI SUL MODELLO DI VALVOLA
C
C
      MODEL=PODEL+1
      IF(MODEL.LE.2.OR.MODEL.GT.6) THEN 
        WRITE(6,4020)NOM1,NOM2,PODEL
        MODEL=3
      ENDIF
 4020 FORMAT(//1X,'********DATA ERROR IN THE BLOCK ',2A4,
     $/10X,'THE MARKER OF THE MODEL ',F6.3,' IS NOT CONTEMPLETED '/
     $10X,'THE CODEX (0,1,)2,3,4,5 ARE PERMITTED'
     $//10X,'I TAKE CODE 2 (NO MODEL CADIPO)')
Car--17/jan/2001      GO TO 30
C
   20 CONTINUE
      DO 22 J=3,6
        IF(MODEL.EQ.J)GO TO 30
   22 CONTINUE
      WRITE(6,4020)NOM1,NOM2,PODEL
      MODEL=3
   30 CONTINUE
C
C     CONTROLLO SUI DATI
C
      III=MOD(MODEL,2)          ! se III = 0  clapet
      IF(III.GT.0) THEN         ! LA VALVOLA NON HA IL CLAPET
	DPCH=0.
	DPAP=0.
      ENDIF
      IF(III.EQ.0) THEN         ! LA VALVOLA HA IL CLAPET
	 IF(DPCH.LT.0.)DPCH=0.
	 IF(DPAP.LT.DPCH) DPAP=DPCH
      ENDIF
C
C________ ALLA PRESSIONE A VALLE DEL PUNTO DI LAVORO
C         SI AGGIUNGE IL PESO DEL CLAPET
C
      P2LL=P2L+DPCH
C
      IF(CFA.LE.0.)  CFA=.9
      IF(ALFA.LE.0.) ALFA=1.
C
      CAA=CVA*2.4E-5
C
      IF(CAA.GT.0.)GO TO 12
C
C   CALCOLO DI CA TRAMITE I DATI DEL PUNTO DI DIMENSIONAMENTO
C
      GO TO (52,52,54,54),MODEL-2
C
C     MODELLO DI VALVOLA SEMPLIFICATA NON SONICA
C
  52  CONTINUE
C
      A=B0AV10(ZL,ALFA)
      RAP=.25+(HL/1.E6 - .4)*.11666
      IF(P1L.GT.P2LL)THEN
Car---23/01/2001         S=SHEV(P1L,HL,1)
Car---23/01/2001         R=ROEV(P1L,S,1)
         CALL BVL0RO(P1L,HL,FL,T,R)
         PCR=P1L*RAP
         IF(P2LL.LT.PCR)P2LL=PCR
      ELSE
Car---23/01/2001         S=SHEV(P2LL,HL,1)
Car---23/01/2001         R=ROEV(P2LL,S,1)
         CALL BVL0RO(P2LL,HL,FL,T,R)
         PCR=P2LL*RAP
         IF(P1L.LT.PCR)P1L=PCR
      ENDIF
C
      DP=ABS(P1L-P2LL)
      CAA= SQRT((WL*WL+ABS(WL)/10.)/(R*DP))/A
      GO TO 12
C
C     MODELLO DI VALVOLA SEMPLIFICATA SONICA
C
  54  CONTINUE
C
      A=B0AV10(ZL,ALFA)


      RAP=.25+(HL/1.E6 - .4)*.11666
      IF(P1L.GT.P2LL)THEN
Car---23/01/2001         S=SHEV(P1L,HL,1)
Car---23/01/2001         RM=ROEV(P1L,S,1)
         CALL BVL0RO(P1L,HL,FL,T,RM)
         PCR=P1L*RAP
         IF(P2LL.LT.PCR)P2LL=PCR
      ELSE
Car---23/01/2001         S=SHEV(P2LL,HL,1)
Car---23/01/2001         RM=ROEV(P2LL,S,1)
         CALL BVL0RO(P2LL,HL,FL,T,RM)
         PCR=P2LL*RAP
         IF(P1L.LT.PCR)P1L=PCR
      ENDIF
      DP=ABS(P1L-P2LL)
      CAA=WL/(A*SQRT(RM*DP))
C
C
C   CALCOLO DELL'AREA DI EFFLUSSO
C
  12  CONTINUE
C
      IMOVAL = 1
C
C
C
C*******DECODIFICA DEL NOME DEL BLOCCO PER SAPERE QUALE E'
C       LA VARIABILE DI USCITA
C
      WRITE(NOMCAR,'(A4)')NOM1
      IWP=0                             !  portata
      IF(NOMCAR(1:1).EQ.'+') IWP=1      !  pressione monte
      IF(NOMCAR(1:1).EQ.'-') IWP=2      !  pressione valle
C
C       MEMORIZZAZIONE DATI
C
      COEQ         = 0.0       ! solo per definizione  ar--17/jan/2001
      IAREA        = 0.0       ! solo per definizione  ar--17/jan/2001
C
      DATI(ID1   ) = ALFA
      DATI(ID1+ 1) = CFA
      DATI(ID1+ 2) = CAA
      DATI(ID1+ 3) = IWP
      DATI(ID1+ 4) = COEQ      ! NON SERVE  ar--17/jan/2001
      DATI(ID1+ 5) = IMOVAL    ! NON SERVE  ar--17/jan/2001
      DATI(ID1+ 6) = MODEL
      DATI(ID1+ 8) = DPAP
      DATI(ID1+ 9) = DPCH
      ID2 = ID2+ 9
C
C   COSTANTI DI NORMALIZZAZIONE
C
Car--18/jan/2001------------------------------------
      IF(IWP.EQ.0) THEN           ! Uscita in portata (IWP=0)
         CNXYU(IV1   ) = Q0       ! portata
         CNXYU(IV1+ 1) = P0       ! pressione monte
         CNXYU(IV1+ 2) = P0       ! pressione valle
      ELSE IF(IWP.EQ.1) THEN      ! Uscita in pressione monte (IWP=1)      
         CNXYU(IV1   ) = P0       ! pressione monte
         CNXYU(IV1+ 1) = Q0       ! portata
         CNXYU(IV1+ 2) = P0       ! pressione valle
      ELSE                        ! Uscita in pressione valle (IWP=2)
         CNXYU(IV1   ) = P0       ! pressione valle
         CNXYU(IV1+ 1) = P0       ! pressione monte
         CNXYU(IV1+ 2) = Q0       ! portata
      END IF
C      
      CNXYU(IV1+ 3) = H0          ! entalpia monte
      CNXYU(IV1+ 4) = 1.          ! fraz. mass. monte
      CNXYU(IV1+ 5) = 1.          ! alzata
      CNXYU(IV1+ 6) = H0          ! entalpia valle
      CNXYU(IV1+ 7) = 1.          ! fraz. mass. valle
Car--17/jan/2001------------------------------------ma che vuol fare qui sotto ?
C
C   TOLLERANZA PER LA SOLUZIONE DELL'EQUAZIONE
C   PER I MODELLI 1,2  4,5,6 LA TOLLERANZA E` .0001*Q0
C
Car--17/jan/2001C   PER I MODELLI 2,3 LA TOLLERANZA E` 1000. PASCAL
C   PER I MODELLI 2,3 su file F14.DAT LA TOLLERANZA E` 1000. PASCAL
C
Car--17/jan/2001      IF(MODEL.EQ.2.OR.MODEL.EQ.3) TOL(1)=1000./P0
      IF(MODEL.EQ.3.OR.MODEL.EQ.4) TOL(1)=1000./P0
C
C   STAMPE DEI PARAMETRI
C
Car--17/jan/2001   25 CAA=CAA/2.4E-5
      CAA=CAA/2.4E-5
C
      IF(IWP.EQ.0)WRITE(6,502)'*** FLOW RATE AS OUTPUT ***'
      IF(IWP.EQ.1)WRITE(6,502)'*** INLET PRESSURE AS OUTPUT ***'
      IF(IWP.EQ.2)WRITE(6,502)'*** OUTLET PRESSURE AS OUTPUT ***'
C
      WRITE(6,3300)
 3300 FORMAT(//10X,'CHOICED MODEL OF VALVE')
      GO TO (201,202,203,204,205,206,207),MODEL
C
  201 WRITE(6,3301)
      GO TO 210
  202 WRITE(6,3302)
      GO TO 210
  203 WRITE(6,3303)
      GO TO 210
  204 WRITE(6,3304)
      GO TO 210
  205 WRITE(6,3305)
      GO TO 210
  206 WRITE(6,3306)
      GO TO 210
  207 WRITE(6,3307)
 3301 FORMAT(10X,'CADIPO WITHOUT CLAPET')
 3302 FORMAT(10X,'CADIPO WITH CLAPET')
 3303 FORMAT(10X,'SIMPLYFIED NOT SONIC WITHOUT CLAPET')
 3304 FORMAT(10X,'SIMPLYFIED NOT SONIC WITH CLAPET')
 3305 FORMAT(10X,'SIMPLYFIED  SONIC')
 3306 FORMAT(10X,'SIMPLYFIED  SONIC WITH PROTECTION CLAPET')
 3307 FORMAT(10X,'MOODY-MORRIS')
C
 210  CONTINUE
  502 FORMAT(14X,A)
      WRITE(6,1120) CAA
 1120 FORMAT(/10X,'EXHAUST COEFFICIENT WHEN THE VALVE'
     $,/10X,'IS COMPLETELY OPENED CV =',F10.2/)
      RETURN
      END
C
C------------------------------------------------------------------------
C
      SUBROUTINE BVL0C1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RN,NOM1,NOM2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
Car--18/jan/2001      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*),CXY(4),CXYU(4)
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*),CXY(5),CXYU(5)
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT  ! angelo
      COMMON/BVL0MV/COEQ,A1,CF1,IAREA,IMOVAL
      COMMON/TOLEG00/TOLIN(100)
      LOGICAL KREGIM
C$$$$$
C$$$$$-------- 29/10/90  LA VALVOLA SONICA O SUBSONICA SEMPLIFICATA NON
C$$$$$                   CAMBIA IL SUO MODELLO NEL CORSO DEL TRANSITORIO
C$$$$$
C
      GO TO (1,10,10),IFUN
C
C   DEFINIZIONE DELLA TOPOLOGIA
C
    1 CONTINUE
      DO 5 I=1,8
        AJAC(1,I)=1.
    5 CONTINUE
      RETURN
C
C   DECODIFICA DEI DATI
C
   10 CONTINUE
      ALFA  = DATI(IPD  )
      CFA   = DATI(IPD+1)
      CAA   = DATI(IPD+2)
      IWP   = DATI(IPD+3)
      COEQ  = DATI(IPD+4)          ! NON SERVE  ar--17/jan/2001
      IMOVAL= DATI(IPD+5)          ! NON SERVE  ar--17/jan/2001
      MODEL = DATI(IPD+6)
      DPAP  = DATI(IPD+8)
      DPCH  = DATI(IPD+9)
C
C
C     DECODIFICA DELLE VARIABILI TENENDO CONTO
C     DELLA VARIABILE DI USCITA DEL BLOCCO
C
C
      IF(IWP.EQ.0) THEN            ! Uscita in portata (IWP=0)
        W     = XYU(IXYU  )*Q0     ! portata
        P1    = XYU(IXYU+1)*P0     ! pressione monte
        P2    = XYU(IXYU+2)*P0     ! pressione valle
      ELSE IF(IWP.EQ.1) THEN       ! Uscita in pressione monte (IWP=1)      
        P1    = XYU(IXYU  )*P0     ! pressione monte
        W     = XYU(IXYU+1)*Q0     ! portata
        P2    = XYU(IXYU+2)*P0     ! pressione valle
      ELSE                         ! Uscita in pressione valle (IWP=2)
        P2    = XYU(IXYU  )*P0     ! pressione valle
        P1    = XYU(IXYU+1)*P0     ! pressione monte
        W     = XYU(IXYU+2)*Q0     ! portata    
      END IF
      H1    = XYU(IXYU+3)*H0       ! entalpia monte
      FNAC  = XYU(IXYU+4)          ! fraz. mass. monte
      Z     = XYU(IXYU+5)          ! alzata
      HINV  = XYU(IXYU+6)*H0       ! entalpia valle
      FINV  = XYU(IXYU+7)          ! fraz. mass. valle
C
C_____ CONTROLLO SE LA VALVOLA HA IL CLAPET E DEFINIZIONE
C_____ DELLA POSIZIONE (ZX) DELLO STELO DELLA VALVOLA TENENDO 
C_____ CONTO DELL'EVENTUALE CLAPET 
C
      ZX=Z                       !  posizione stelo con eventuale clapet
      III=MOD(MODEL,2)
      IF(III.GT.0) GO TO 115     !  valvola senza clapet
C
C________ LA VALVOLA HA IL CLAPET
C________ IL TEST SUL CLAPET SI FA SOLO ALLA PRIMA ITERAZIONE
C________ E SI CALCOLA LA POSIZIONE DEL CLAPET (APERTO=1 ,CHIUSO=0)
C
      IF(KREGIM) ITERT=0.
      IF(ITERT.NE.0) THEN
	CLAP=DATI(IPD+7)
	ZX=Z*CLAP                !  posizione stelo con eventuale clapet
      ELSE
	PCLOS=P2+DPCH
	POPEN=P2+DPAP
	IF(P1.GE.POPEN) THEN
	  CLAP=1.
	ELSE IF(P1.LE.PCLOS) THEN
	  CLAP=0.
	ELSE
	  CLAP= (P1-PCLOS)/(POPEN-PCLOS)
	ENDIF
	DATI(IPD+7)=CLAP
	ZX=CLAP*Z                !  posizione stelo con eventuale clapet
      ENDIF
C
C_____ CONTROLLO SE LA VALVOLA E' CHIUSA
C
  115 CONTINUE
      IF(ZX.GT.1.E-6) GO TO 116
      ZX=0.                      !  posizione stelo con eventuale clapet
C
C____ VALVOLA CHIUSA
C
      RN(1)=-W/Q0
      IF(IFUN.EQ.3) THEN
	 AJAC(1,IWP+1)=1.
      ENDIF
      RETURN
C
C____ VALVOLA APERTA
C
 116  IF(ZX.LE.1.)GO TO 131
C
C_____ STELO >1.
C
      IF(.NOT.KREGIM)ZX=1.
      IF(KREGIM)
     $             WRITE(6,8787)NOM1,NOM2
 8787 FORMAT(//1X,'*************** WARNING ****************',
     $/10X,'     VALVE LIFT > 1. ',
     $/10X,'IN THE BLOCK ',2A4,' (MODULE BVL0)'
     $/1X,'*************** MUST BE = o < 1.  ***********')
C
  131 CONTINUE
C
C--------------------------------------------------------------
C    CALCOLO DEI RESIDUI SECONDO IL MODELLO DI VALVOLA SCELTA
C--------------------------------------------------------------
C
      GO TO (52,52,54,54),MODEL-2
C
C----------- MODELLO DI VALVOLA SEMPLIFICATA NON SONICA
C
  52  CONTINUE
      III=MOD(MODEL,2)
      IF(III.EQ.0) THEN    ! LA VALVOLA HA UN CLAPET
	P2=P2+DPCH
      ENDIF
      A=B0AV10(ZX,ALFA)
C
Car---17/jan/2001      RAP=.25+(H1/1.E6 - .4)*.11666
      IF(P1.GE.P2)THEN
         RAP=.25+(H1/1.E6 - .4)*.11666
Car---17/jan/2001         S=SHEV(P1,H1,1)
Car---17/jan/2001         R=ROEV(P1,S,1)
         CALL BVL0RO(P1,H1,FNAC,TU,R)
         PCR=P1*RAP
         IF(P2.LT.PCR)P2=PCR
      ELSE
         RAP=.25+(HINV/1.E6 - .4)*.11666
Car---17/jan/2001         S=SHEV(P2,HINV,1)
Car---17/jan/2001         R=ROEV(P2,S,1)
         CALL BVL0RO(P2,HINV,FINV,TU,R)
         PCR=P2*RAP
         IF(P1.LT.PCR)P1=PCR
      ENDIF
      DDDP=(P1-P2)
      EPST=1.E-04*A*A*P0
      IF(EPST.LT.5.)EPST=5. 
Can      TOLIN(1)=EPST/P0
      COFF=CAA*CAA
      RN(1)=(A*A*DDDP-W*ABS(W)/COFF/R-W/(CAA*CAA*R)/10.)/P0
      GO TO 12
C
C----------- MODELLO DI VALVOLA SEMPLIFICATA SONICA
C
  54  CONTINUE
      III=MOD(MODEL,2)
      IF(III.EQ.0) THEN    ! LA VALVOLA HA UN CLAPET
        P2=P2+DPCH
      ENDIF
      A=B0AV10(ZX,ALFA)
Car---17/jan/2001      RAP=.25+(H1/1.E6 - .4)*.11666
      IF(P1.GE.P2)THEN
        RAP=.25+(H1/1.E6 - .4)*.11666
Car---17/jan/2001        S=SHEV(P1,H1,1)
Car---17/jan/2001        R=ROEV(P1,S,1)
        CALL BVL0RO(P1,H1,FNAC,TU,R)
        PCR=RAP*P1
        IF(PCR.LT.P2) PCR = P2
        DDDP=P1-PCR
        SEGNO=1.
      ELSE
        RAP=.25+(HINV/1.E6 - .4)*.11666
Car---17/jan/2001        S=SHEV(P2,HINV,1)
Car---17/jan/2001        R=ROEV(P2,S,1)
        CALL BVL0RO(P2,HINV,FINV,TU,R)
        PCR=RAP*P2
        IF(PCR.LT.P1) PCR = P1
        DDDP=P2-PCR
        SEGNO=-1.
      ENDIF
      RN(1)=(SEGNO*CAA*A*SQRT(ABS(DDDP)*R)-W)/Q0
C--------------------------------------------------------------
C
   12 IF(IFUN.EQ.2) RETURN
C
C--------------------------------------------------------------
C                CALCOLO DELLO JACOBIANO
C--------------------------------------------------------------
C      write(6,*) ' model=',MODEL
C
      GO TO (152,152,154,154),MODEL-2
C
C------ MODELLO DI VALVOLA SEMPLIFICATA NON SONICA
C
 152  CONTINUE
C      write(6,*) ' 152 continue'
      III=MOD(MODEL,2)
      IF(III.EQ.0) THEN    ! LA VALVOLA HA UN CLAPET
	P2=P2+DPCH
      ENDIF
      A=B0AV10(ZX,ALFA)
C
Car---17/jan/2001      RAP=.25+(H1/1.E6 - .4)*.11666
      IF(P1.GE.P2) THEN
        RAP=.25+(H1/1.E6 - .4)*.11666
Car---17/jan/2001        S=SHEV(P1,H1,1)
Car---17/jan/2001        R=ROEV(P1,S,1)
        CALL BVL0RO(P1,H1,FNAC,TU,R)
        PCR=P1*RAP
        ICRIT=0
        IF(P2.LT.PCR) THEN
          ICRIT=1
          P2=PCR
        ENDIF
      ELSE
        RAP=.25+(HINV/1.E6 - .4)*.11666
Car---17/jan/2001        S=SHEV(P2,HINV,1)
Car---17/jan/2001        R=ROEV(P2,S,1)
        CALL BVL0RO(P2,HINV,FINV,TU,R)
        PCR=P2*RAP
        ICRIT=0
        IF(P1.LT.PCR) THEN
          ICRIT=-1
          P1=PCR
        ENDIF
      ENDIF
      DDDP=(P1-P2)
      COFF=CAA*CAA
C
      AJAC(1,1)=2.*ABS(W)*Q0/COFF/R/P0 + Q0/(CAA*CAA*R)/10./P0
      AJAC(1,2)=-1.*A*A
      AJAC(1,3)=1.*A*A
      IF(ICRIT.EQ.1)THEN
        AJAC(1,2)=-A*A*(1.-RAP)
        AJAC(1,3)=0.
      ENDIF
      IF(ICRIT.EQ.-1)THEN
        AJAC(1,2)=0.
        AJAC(1,3)=A*A*(1.-RAP)
      ENDIF
      DZ=.01
      F0=(-DDDP*A*A+W*ABS(W)/COFF/R+W/(CAA*CAA*R)/10.)/P0
      ZZX=ZX+DZ
      AA=B0AV10(ZZX,ALFA)
      CCOFF=CAA*CAA
      FX=(-DDDP*AA*AA+W*ABS(W)/CCOFF/R+W/(CAA*CAA*R)/10.)/P0
C
Car---18/jan/2001      AJAC(1,5)=(FX-F0)/DZ
      DO J=4,8
       AJAC(1,J)=0.0
      END DO
      AJAC(1,6)=(FX-F0)/DZ
C
C      write(6,*) ' go to 31 da 152'
      GO TO 31
C
C------ MODELLO DI VALVOLA SEMPLIFICATA SONICA
C
 154  CONTINUE
      F0=-RN(1)
      AJAC(1,1)=1.
C
      CXY(1)=P1
      CXY(2)=P2
      CXY(3)=H1
      CXY(4)=HINV
      CXY(5)=ZX
      DX=0.01
      EPSP=ABS(P1-P2)*DX
      IF(EPSP.LT.10.) EPSP=10.
      DO  I=1,5
       EPS=CXY(I)*DX
       IF(EPS.LT.1.E-4) EPS=DX
       IF(I.LE.2) EPS=EPSP
       DO J=1,5
	CXYU(J)=CXY(J)
	IF(J.EQ.I) CXYU(J)=CXYU(J)+EPS
       ENDDO
C
       IF(I.LE.2) THEN   
         EPS=EPS/P0
       ELSE IF(I.EQ.3.OR.I.EQ.4) THEN          
        EPS=EPS/H0
       END IF
       P1 = CXYU(1)
       P2 = CXYU(2)
       H1 = CXYU(3)
       HI = CXYU(4)
       ZX = CXYU(5)
C
       A=B0AV10(ZX,ALFA)
C
Car---18/jan/2001       RAP=.25+(H1/1.E6 - .4)*.11666
C
       IF(P1.GE.P2)THEN
        RAP=.25+(H1/1.E6 - .4)*.11666
Car---18/jan/2001        S=SHEV(P1,H1,1)
Car---18/jan/2001        R=ROEV(P1,S,1)
        CALL BVL0RO(P1,H1,FNAC,TU,R)
        PCR=RAP*P1
        IF(PCR.LT.P2) PCR = P2
        DDDP=P1-PCR
        SEGNO=1.
       ELSE
        RAP=.25+(HI/1.E6 - .4)*.11666
Car---18/jan/2001        S=SHEV(P2,HI,1)
Car---18/jan/2001        R=ROEV(P2,S,1)
        CALL BVL0RO(P2,HINV,FINV,TU,R)
        PCR=RAP*P2
        IF(PCR.LT.P1) PCR = P1
        DDDP=P2-PCR
        SEGNO=-1.
       ENDIF
C
       FX=(W-SEGNO*CAA*A*SQRT(ABS(DDDP)*R))/Q0
       KH = 0
       IF(I.EQ.4) KH=2
       AJAC(1,I+1+KH)=(FX-F0)/EPS
      ENDDO
C
C-------------------------------------------------------------
C____ SISTEMAZIONE COEFFICIENTI JACOBIANO PER
C     TENER CONTO DELL'ORDINAMENTO DELLE VARIABILI DEL MODULO
C-------------------------------------------------------------
C
   31 CONTINUE
C      write(6,*) ' sono a 31 !!!!  IWP=',IWP
      IF(IWP.EQ.0) go to 333  !!    RETURN
      IF(IWP.EQ.1) THEN
	 AX=AJAC(1,1)
	 AJAC(1,1)=AJAC(1,2)
	 AJAC(1,2)=AX
      ELSE
	 AX=AJAC(1,1)
	 AJAC(1,1)=AJAC(1,3)
	 AJAC(1,3)=AX
      ENDIF
C-------------------------------------------------------------
  333 CONTINUE
C-------------------------------------------------------------
C      WRITE(6,*) 'JACO-BVL0 AL TEMPO',TEMPO,' ED ITER=',ITERT
C      WRITE(6,4321) (AJAC(1,K),K=1,8) 
C 4321 FORMAT(8(2X,F12.7))     
C-------------------------------------------------------------
      RETURN
      END
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
      REAL FUNCTION B0AV10(Z,ALFA)                                      !SNGL
C      DOUBLE PRECISION FUNCTION B0AV10(Z,ALFA)                          !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      IF(ALFA.GT.10.)GO TO 1
      B0AV10=Z**ALFA
      RETURN
C
C      CALCOLO DI B0AV10 CON UNA FUNCTION
C      CREATA DALL'UTENTE
C
    1 B0AV10=B0NS10(Z,ALFA)
      RETURN
      END
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C-------------------------------------------------------------------------
C
      SUBROUTINE BVL0D1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $ XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C-----SIGNIFICATO DELLE VARIABILI DI USCITA
C     SIGNEQ = Descrizione dell'equazione  (in stazionario) - 50 car.
C     UNITEQ = Unita' di misura del residuo - 10 car.
C     COSNOR = Costante di normalizzazione del residuo in stazionario
C     ITOPVA = Topologia dello jacobiano di regime - matrice di INTEGER
C
C
C-----VALVOLA
C
      CHARACTER*8 BLOCCO, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
C
      IWP   = DATI(IPD+3)
      MODEL = DATI(IPD+6)
      CLAP  = DATI(IPD+7)
      DPAP  = DATI(IPD+8)
      DPCH  = DATI(IPD+9)
      Z     = XYU(IXYU+4)
C
      IF (IWP.EQ.0) THEN
	P1 = XYU(IXYU+1)*P0
	P2 = XYU(IXYU+2)*P0
      ELSE IF (IWP.EQ.1) THEN
	P1 = XYU(IXYU  )*P0
	P2 = XYU(IXYU+2)*P0
      ELSE
	P1 = XYU(IXYU+1)*P0
	P2 = XYU(IXYU  )*P0
      ENDIF
C
      III=MOD(MODEL,2)
      IF(III.GT.0) GO TO 2
C
C--- LA VALVOLA HA IL CLAPET
C    SI CALCOLA LA POSIZIONE DEL CLAPET (APERTO=1 ,CHIUSO=0)
C
      PCLOS=P2+DPCH
      POPEN=P2+DPAP
C
      IF(P1.GE.POPEN) THEN
	CLAP=1.
      ELSE IF(P1.LE.PCLOS) THEN
	CLAP=0.
      ELSE
	CLAP= (P1-PCLOS)/(POPEN-PCLOS)
      ENDIF
C
C--- DEFINIZIONE DELLA POSIZIONE VALVOLA + CLAPET
C
      ZX = Z*CLAP
      IF(ZX .GT. 1.E-06) GO TO 2
      SIGNEQ(1) = 'CHECK VALVE FLOW INTERCEPTION EQUATION'
      UNITEQ(1) = 'kg/s'
      COSNOR(1) = W0
C
      IF(IWP.EQ.0) ITOPVA(1,1) = 1
      IF(IWP.EQ.1) ITOPVA(1,2) = 1
      IF(IWP.EQ.2) ITOPVA(1,3) = 1
      GO TO 100
C
    2 CONTINUE
C
      SIGNEQ(1) = 'VALVE FLUID FLOW RATE COMPUTATION EQUATION'
      IF (MODEL.EQ.2 .OR. MODEL.EQ.3) THEN
C
C---MODELLO DI VALVOLA SEMPLIFICATA NON SONICA
C
	UNITEQ(1) = 'Pa'
	COSNOR(1) = P0
      ELSE
C
C---VALVOLA MODELLO CADIPO O MOODY-MORRIS O SEMPLIFICATA SONICA
C
	UNITEQ(1) = 'kg/s'
	COSNOR(1) = W0
      ENDIF
C
      DO I = 1,5
	ITOPVA(1,I) = 1
      ENDDO
C
  100 RETURN
      END
C
C-------------------------------------------------------------------------
C
C~FORAUS_BVL0~C
C
C FORTRAN AUSILIARIO DEL MODULO VALVOLA
C PER LA SUA SCRITTURA VEDERE MANUALE D'USO O
C UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD.
C
C
C                       FUNCTION B0NS10(ALZA, ALFA)
C
C  Function per l'assegnazione della caratteristica della valvola
C
C  Parametri d'ingresso: ALZA,ALFA
C  Parametri d'uscita  : B0NS10
C
C************* BREVE SPIEGAZIONE DEI PARAMETRI DELLA FUNCTION ************
C
C [p.u.]  ALZA   -  grado di apetura della valvola.
C
C [ ]     ALFA   -  (>10) parametro,  proveniente  dai  dati  in input, che puo`
C                   essere utilizzato come indice  di  scelta nel caso in cui si
C                   vogliano introdurre diverse caratteristiche standard tramite
C                   un'unica FUNCTION B0NS10(ALZA,ALFA).
C
C [p.u.]  B0NS10 -  valore dell'area  di  passaggio  calcolata. Tale valore deve
C                   essere normalizzato rispetto all'area di passaggio a valvola
C                   completamente aperta.
C
C
C  Esempio di caratteristica assegnata per punti:
C
C
CC      REAL FUNCTION B0NS10(Z,ALFA)                                      !SNGL
CC      DOUBLE PRECISION FUNCTION B0NS10(Z,ALFA)                          !DBLE
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      DIMENSION X1(12),Y1(12)
C      DATA X1/0.,.1,.2,.3,.4,.5,.6,.7,.8,.9,1.,1.2/
C      DATA Y1/.055,.085,.125,.17,.22,.28,.35,.43,.55,.7,1.,1./
CC
CC     CARATTERISTICHE CV=FUNZIONE DI ALZATA VALVOLA
CC
C      IALF=ALFA-10.
C      GO TO (1,100),IALF
CC
CC     CARATTERISTICA DELLA FCV DEL RICIRCOLO
CC
C    1 CALL B0_AVNS(Z,X1,Y1,12,A)
C      B0NS10=A
C      GO TO 500
CC
C 100  CONTINUE
C 500  RETURN
C      END
C
C*************************************************************************
C
C      SUBROUTINE B0_AVNS(Z,X,Y,NP,A)
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      DIMENSION X(*),Y(*)
CC
CC     INTERPOLAZIONE
CC
C      DO 10 I=1,NP-1
C      J=I
C      IF(Z.GE.X(J).AND.Z.LE.X(J+1))GO TO 15
C   10 CONTINUE
C      A=0.
C      GO TO 20
C   15 A=Y(J)+(Z-X(J))*(Y(J+1)-Y(J))/(X(J+1)-X(J))
C   20 RETURN
C      END
C
C************** INIZIO DEL TESTO FORTRAN DA SCRIVERE ********************
C
      REAL FUNCTION B0NS10(Z,ALFA)                                      !SNGL
C      DOUBLE PRECISION  FUNCTION B0NS10(Z,ALFA)                         !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      A = 0.1
      B0NS10=A
      RETURN
      END
C
C************** FINE FUNCTION B0NS10 ********************
C
C
C
C                FUNCTION CFNS10(ALZA,A,CFA)
C
C     Function per l'assegnazione della legge di variazione
C     del coefficiente di recupero della valvola
C
C  Parametri d'ingresso: ALZA, A, CFA
C  Parametri d'uscita  : CFNS10
C
C
C************* BREVE SPIEGAZIONE DEI PARAMETRI DELLA FUNCTION ************
C
C [p.u.]  ALZA   -  grado di apetura della valvola.
C
C [p.u.]  A      -  area di passaggio normalizzata.
C
C [ ]     CFA    -  (>10) parametro,  proveniente dai  dati  in input, che  puo`
C                   essere  utilizzato come indice di scelta qualora si vogliano
C                   assegnare  diverse  leggi  di variazione del coefficiente di
C                   recuperdetramite un'unica FUNCTION CFNS10(ALZA,A,CFA).
C
C [ ]     CFNS10 -  valore del coefficiente di recupero calcolato.
C
C
C
C   Esempio di coefficiente di recupero assegnato tramite function:
C
CC      REAL FUNCTION CFNS10(Z,A,CFA)                                     !SNGL
CC      DOUBLE PRECISION FUNCTION CFNS10(Z,A,CFA)                         !DBLE
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      CFNS=0.95
C      RETURN
C      END
C
C
C************** INIZIO DEL TESTO FORTRAN DA SCRIVERE ********************
C
CC      REAL FUNCTION CFNS10(Z,A,CFA)                                     !SNGL
CC      DOUBLE PRECISION FUNCTION CFNS10(Z,A,CFA)                         !DBLE
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      RETURN
C      END
C
C~FORAUS_BVL0~C
C-----------------------------------------------------------------------
      SUBROUTINE BVL0SE(PI,HI,FI,TU,SU)
C
C-----CALCOLO ENTROPIA SALAMOIA
C
      CALL T_FOR(PI,HI,FI,TU)
      CALL S_FOR(TU,FI,SU)
C
      RETURN
      END
C-----------------------------------------------------------------------
C-----------------------------------------------------------------------
      SUBROUTINE BVL0RO(PI,HI,FI,TU,RU)
C
C-----CALCOLO DENSITA SALAMOIA
C
      CALL T_FOR(PI,HI,FI,TU)
      CALL ROC_FOR(FI,TU,PI,RU)
C
      RETURN
      END
C-----------------------------------------------------------------------
      SUBROUTINE PSDAH_MARE(P,H,F,PSAT)
C
C--- SATURATION PRESSURE OF THE NaCl SOLUTION 
C--- as function of pressure (P), enthalpy (H) and mass fraction (F)
C--- of NaCl
C
      REAL MNACL,MH2O
      DATA MNACL/58.4/,MH2O/18./
C
      CALL T_FOR(P,H,F,TSOL)
C
      NFL   = 1
      PSH2O = PSATEV(TSOL,NFL) 
      XX    = ((1.-F)/MH2O)/(2*F/MNACL + (1.-F)/MH2O)
      PSAT  = PSH2O * XX
C
      RETURN
      END
C-----------------------------------------------------------------------
