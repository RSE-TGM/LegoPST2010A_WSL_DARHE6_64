C**********************************************************************
C modulo fumn.f
C tipo 
C release 5.5
C data 4/14/95
C reserver @(#)fumn.f	5.5
C**********************************************************************
C
C         ===========================================
C
C            *****  CONDOTTO FUMI  *****
C            VERSIONE MODIFICATA DA SPELTA (NOV 91)
C            VERSIONE MODIFICATA  (APR 95)
C
C         ===========================================
C
      SUBROUTINE FUMNI3(IFO,IOB,DEBL)
C--------------------------------------------------------------------
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NCMAX=9)
      PARAMETER (NSMAX=6)
      COMMON/FUMN99/NUCEL,NUME(NCMAX),NSUT
      COMMON/FUMN01/IBLOC
      COMMON/FUMN02/NUCXX,NPAR
C--------------------------------------------------------------------
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'FUMN'/
C
C
C           FUMI
C   MIN 1 MAX 9 CELLE
C   MIN 1 MAX 6 PARETI SCAMBIANTI PER OGNI CELLA
C
C
      CALL FUMNI4(IOB,MOD)
C
      NSTATI= 0
      NUSCIT= 2*NUCEL+1
      NINGRE= NSUT+6
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000) IOB
 3000 FORMAT('TUF ',A4,2X,'--UA-- OUTLET FLUE GAS TEMPERATURE')
C
      do  K=1,NUCEL
      WRITE(IFO,3001)K,IOB,K
 3001 FORMAT('TF',I2,A4,2X,
     $  '--UA-- FLUE GAS MEAN TEMP. INSIDE CELL',I2)
      end do
C
      do  K=1,NUCEL
      WRITE(IFO,3002)K,IOB,K
 3002 FORMAT('GF',I2,A4,2X,
     $  '--UA-- THERMAL EXCHANGE COEFFICIENT IN CELL',I2)
      end do
C
      WRITE(IFO,3003)IOB
      WRITE(IFO,3004)IOB
      WRITE(IFO,3005)IOB
      WRITE(IFO,3006)IOB
      WRITE(IFO,3007)IOB
      WRITE(IFO,3008)IOB
 3003 FORMAT('WIF ',A4,2X,'--IN-- INLET FLOW RATE OF FLUE GAS')
 3004 FORMAT('TIF ',A4,2X,'--IN-- INLET FLUE GAS TEMPERATURE')
 3005 FORMAT('FAS ',A4,2X,'--IN-- GRITNESS FACTOR OF THE TUBES')
 3006 FORMAT('%CO2',A4,2X,
     $  '--IN-- PARTIAL PRESSURE OF CO2 IN FLUE GAS (IN PERCENT)')
 3007 FORMAT('%PH2',A4,2X,
     $  '--IN-- PARTIAL PRESSURE OF H2O IN FLUE GAS (IN PERCENT)')
 3008 FORMAT('%H2O',A4,2X,
     $  '--IN-- MASSIC FRACTION OF H2O IN FLUE GAS (IN PERCENT)')
C
      DO K=1,NUCEL
	DO NM=1,NUME(K)
	  WRITE(IFO,3009) NM,K,IOB,NM,K
	ENDDO
      ENDDO
 3009 FORMAT('TM',I1,I1,A4,2X,
     $  '--IN-- TEMP. OF METAL SURF. ',I1,' FLUE GAS SIDE CELL ',I1)
C
      RETURN
      END
C=====================================================================
      SUBROUTINE FUMNI4(IOB,MOD)
C--------------------------------------------------------------------
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NCMAX=9)
      PARAMETER (NSMAX=6)
      COMMON/FUMN99/NUCEL,NUME(NCMAX),NSUT
      COMMON/FUMN01/IBLOC
      COMMON/FUMN02/NUCXX,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C--------------------------------------------------------------------
C
    1 WRITE(6,2000) NCMAX
 2000 FORMAT(//10X,'FLUE GAS PIPE '//
     $ 10X,'NUMBER OF CELLS (MIN. 1 - MAX. ',I1,') ?')
      READ(5,*) NUCEL
      IF(NUCEL.LT.1.OR.NUCEL.GT.NCMAX) THEN
	WRITE(6,2001) NUCEL
 2001   FORMAT(/10X,'ERROR  - N.CELLS=',I3,/)
	GO TO 1
      ENDIF
C
      NSUT=0
      DO J=1,NUCEL
    2   WRITE(6,2032) J,NSMAX
	READ(5,*) NS
	IF(NS.LT.1.OR.NS.GT.NSMAX) THEN
	  WRITE(6,2033)
	  GOTO 2
	ENDIF
	NSUT=NSUT+NS
	NUME(J) = NS
      ENDDO
 2032 FORMAT(2X,' NUMBER OF WALLS EXCHANGING WITH THE CELL ',I1,
     $          ' (1-',I1,')')
 2033 FORMAT(2X,' WRONG NUMBER. RETRY !!')
C
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
      RETURN
      END
C=====================================================================
      SUBROUTINE FUMNI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBLOC1,IBLOC2,IER,CNXYU,TOL)
C--------------------------------------------------------------------
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NCMAX=9)
      PARAMETER (NSMAX=6)
C--------------------------------------------------------------------
      INTEGER DUENSMAX
      INTEGER VAR
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      DIMENSION SUPES(NSMAX)
      CHARACTER*4 NT,ND,NL,ISPA,NLP,NLL,NAC,NFA,SUPER,GA
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      DATA PIGR/3.1415926/
      DATA NT,ND,NL,ISPA/'NTUB','DIAE','LUNG','    '/
      DATA NLP,NLL,NAC,NFA/'PASP','PASL','SCAN','FA  '/
      DATA SUPER/'SUP.'/,GA/'GAMM'/
C
C - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
C
      NUCEL=(NUSCIT-1)/2
      GOTO (1,10),IFUN
C
C  SCRITTURA SIMBOLI DATI ------------- ( LG2 )
C
    1 CONTINUE
C
      DO 999 J=1,NUCEL
	WRITE(14,1031) J,NSMAX
	WRITE(14,1001) NT,J,ND,J,NL,J
	WRITE(14,1001) NLP,J,NLL,J,NAC,J
	WRITE(14,1001) NFA,J,GA,J
	WRITE(14,1002) (SUPER,I,J,I=1,NSMAX)
  999 CONTINUE
C
 1001 FORMAT(3(4X,A4,'  C',I1,' =',10X,'*'))
 1002 FORMAT(3(4X,A4,I1,' C',I1,' =',10X,'*'))
 1029 FORMAT('*   ** NUMBER OF CELLS:',I2)
 1031 FORMAT('*   ----------------- CELL',I2,' -- MAX N. OF SURF. ',I1)
C
      RETURN
C
C--------------------------------LETTURA DATI ---- ( LG3 )
C
   10 CONTINUE
      READ(14,1004)
      DATI(ID1)  = NUCEL
      IDX=ID1+1
C
      DUENSMAX=2*NSMAX
      NST = 0
C===========================LOOP
      DO 9999 J=1,NUCEL
      READ(14,1004)
      READ(14,1004) TUB,DIAE,HLU
      READ(14,1004) PASP,PASL,SCAN
      READ(14,1004) FA,GAMMA
 1004 FORMAT(3(14X,F10.0,1X))
      NTUB=TUB
      READ(14,1004) (SUPES(IK),IK=1,NSMAX)
C
C___ LE SUPERFICI POSSONO AVERE VALORE NEGATIVO.
C    QUESTO SIGNIFICA CHE PER QUESTE SUPERFICI LO SCAMBIO
C    TERMICO CON I FUMI E` DI TIPO LONG_FLOW E VIENE QUINDI USATA
C    LA SUBROUTINE UCL12 PER IL CALCOLO DEL COEFFICIENTE DI SCAMBIO
C
      NSUP=0.
      SUTO=0.
      DO IK=1,NSMAX
      IF(ABS(SUPES(IK)).GT.0.) THEN
	 IF(SUPES(IK).GT.0.) THEN
C___ TYPSC=1. ==> SCAMBIO IN CROSS FLOW
	    TYPSC=1.
	 ELSE
C___ TYPSC=2. ==> SCAMBIO IN LONG FLOW
	    TYPSC=2.
	    SUPES(IK)=-SUPES(IK)
	 ENDIF
	 DATI(IDX+1+IK)      =SUPES(IK)
	 DATI(IDX+1+NSMAX+IK)=TYPSC
	 SUTO=SUTO+SUPES(IK)
	 NSUP=NSUP+1
      ELSE
	 DATI(IDX+1+IK)      =0.
	 DATI(IDX+1+NSMAX+IK)=1.
      ENDIF
      ENDDO
      NST = NST+NSUP
C
C---------------------------------ELAB.+MEMO DATI
C
      SGAS=SCAN*(1.-DIAE/PASP)
      PASPD=PASP/DIAE
      PASLD=PASL/DIAE
      OPTL=RADL12(PASPD,PASLD,DIAE)
C
      DATI(IDX+1)      =NSUP
      DATI(IDX+DUENSMAX+2)=OPTL
      DATI(IDX+DUENSMAX+3)=FA
      DATI(IDX+DUENSMAX+4)=DIAE
      DATI(IDX+DUENSMAX+5)=SUTO
      DATI(IDX+DUENSMAX+6)=SGAS
      DATI(IDX+DUENSMAX+7)=HLU
      DATI(IDX+DUENSMAX+8)=GAMMA
C
      IDX=IDX+DUENSMAX+8
C=======================================================
 9999 CONTINUE
      DATI(ID1+1)=NST
      ID2=ID1+1+(8+DUENSMAX)*NUCEL+NUCEL
C
C--------------------------------COSTANTI DI NORMALIZZ.
C
      GAM0=1000.
      CNXYU(IV1)  =T0
      DO 1000 J=1,NUCEL
	CNXYU(IV1+J)=T0
	CNXYU(IV1+NUCEL+J)=GAM0
 1000 CONTINUE
      IXX=IV1+2*NUCEL
      CNXYU(IXX+1)=W0
      CNXYU(IXX+2)=T0
      CNXYU(IXX+3)=1.
      CNXYU(IXX+4)=1.
      CNXYU(IXX+5)=1.
      CNXYU(IXX+6)=1.
      IXX=IXX+6
      DO J=1,NST
	CNXYU(IXX+J)=T0
      ENDDO
C
C                  TOLLERANZE    (STANDARD)
C
      RETURN
      END
C=====================================================================
      SUBROUTINE FUMNC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                    IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*), XYU(*), DATI(*), RNI(*)
      PARAMETER (NCMAX=9)
      PARAMETER (NSMAX=6)
	COMMON/REGIME/KREGIM
	COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
	EXTERNAL FUMN
C
	GAM0=1000.
C
C-----------------------------  FUMN
C
      GOTO(10,20,30),IFUN
C
C=============================  TOPOLOGIA JACOBIANO
C
   10 CONTINUE
      NUCEL = DATI(IPD)
      NST   = DATI(IPD+1)
      NEQ   = NUCEL*2+1
      NVAR  = 6+NST+NEQ
C
      DO 15 I=1,NEQ
      DO 14 J=1,NVAR
      AJAC(I,J)=1.
   14 CONTINUE
   15 CONTINUE
C
      RETURN
C
C=============================  RESIDUI
C
   20 CONTINUE
      CALL FUMN(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C=============================  JACOBIANO
C
   30 CONTINUE
C
      NUCEL = DATI(IPD)
      NST   = DATI(IPD+1)
      NEQ   = NUCEL*2+1
      NVAR  = 6+NST+NEQ
C
      NSTATI=0
      NUSCIT = NEQ
      NINGRE = NVAR-NEQ
      EPS   =1.E-3
      EPSLIM=1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $             NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,FUMN)
      RETURN
      END
C=====================================================================
      SUBROUTINE FUMN(IFUN,IXYU,XYU,IPD,DATI,RN)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NCMAX=9)
      PARAMETER (NSMAX=6)
      INTEGER DUENSMAX
      DIMENSION XYU(*),DATI(*),RN(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      DATA BETA/0.3/
C
C-----------------------------DATI GENERALI
C
      GAM0=1000.
      Q0=W0*H0
C
      NUCEL= DATI(IPD)
      NST  = DATI(IPD+1)
      DUENSMAX=2*NSMAX
      ITU  = IPD+1+(8+DUENSMAX)*NUCEL
C
C----------------------------- GRANDEZZE GENERALI
C
	   IWF  =2*NUCEL+1
	   ITFI =2*NUCEL+2
	   IFF  =2*NUCEL+3
	   ICO  =2*NUCEL+4
	   IH2  =2*NUCEL+5
	   IBW  =2*NUCEL+6
      TFI0 =XYU(IXYU+ITFI)*T0
      WF   =XYU(IXYU+IWF)*W0
      WFABS=ABS(WF)
      FF   =XYU(IXYU+IFF)
      PCO2 =XYU(IXYU+ICO)/100.
      PH2O =XYU(IXYU+IH2)/100.
      H2OBW0=XYU(IXYU+IBW)
      H2OBW =XYU(IXYU+IBW)/100.
C
C-----------------------------LOOP SULLE CELLE
C
      ITM =6+2*NUCEL
      IPC=IPD+1
C-----------------------------DATI E VARIABILI DI UNA CELLA
      DO 2000 ICE=1,NUCEL
C
	TFM=XYU(IXYU+ICE)*T0
	GAM=XYU(IXYU+NUCEL+ICE)*GAM0
C
	NS  =DATI(IPC+1)
	OPTL=DATI(IPC+DUENSMAX+2)
	FA  =DATI(IPC+DUENSMAX+3)
	DIAE=DATI(IPC+DUENSMAX+4)
	SUTO=DATI(IPC+DUENSMAX+5)
	SGAS=DATI(IPC+DUENSMAX+6)
	HLU =DATI(IPC+DUENSMAX+7)
        GAMA=DATI(IPC+DUENSMAX+8)
C-------------------------------------------
       IF(ICE.GT.1) THEN
	  HFI=HFU
	  TFI=TCU
	ELSE
	  TFI=TFI0
	  HFI=HTFU(TFI,H2OBW,1)
	ENDIF
C-------------------------------------------
	TEME=0.
	DO JK=1,NS
	  TMET=XYU(IXYU+ITM+JK)*T0
	  SUP   =DATI(IPC+1+JK)
	  TYPSC =DATI(IPC+1+JK+NSMAX)
	  TEME=TEME+TMET*SUP
	ENDDO
	TEME=TEME/SUTO
	  DELTF=TFM-TEME
C
	IF(KREGIM) GO TO 9
	IF(ITERT.GT.0.OR.IFUN.NE.2) GO TO 10
 9      CONTINUE
C-----CALCOLO IL COEFF. DI SCAMBIO
C
      IF(WFABS.GT.1.E-3) THEN
C
C____ CALCOLO IL COEFF. DI SCAMBIO CONVETTIVO MEDIATO SU OGNI PARETE
        IF(GAMA.EQ.0.) THEN
	     UC=0.
	     UR=0.
	   DO JK=1,NS
	     TMET  =XYU(IXYU+ITM+JK)*T0
	     SUP   =DATI(IPC+1+JK)
	     TYPSC =DATI(IPC+1+JK+NSMAX)
	     TFILM=0.5*(TFM+TMET)
C
   	     IF(TYPSC.EQ.1.) THEN
C_____ SCAMBIO TERMICO IN CROSS-FLOW
	       CALL UC12(TFILM,WFABS,H2OBW0,SGAS,DIAE,FA,
     $                   2,UCC,DUCDTF,DUCDTM)
	     ELSE
C_____ SCAMBIO TERMICO IN LONG-FLOW
	       PERB=SUP/HLU
	       DEQ =4.*SGAS/PERB
	       CALL UCL12(TFILM,TFM,WFABS,H2OBW0,SGAS,DEQ,UCC)
C

	     ENDIF
C___ IL COEFF. CONVETTIVO VIENE PESATO SULLE PARETI
	     UC= UC + UCC*SUP/SUTO
	   ENDDO
C____ CALCOLO DEL COEFFICIENTE RADIATIVO
          CALL UR12(DELTF,TEME,PH2O,PCO2,OPTL,IFUN,UR,
     $              DURDTF,DURDTM,DURDPGAS)
        ENDIF
C
C****** Correzione del coeff. di scambio radiativo (da verificare poi con
C                                                   calma...)
C****** Correzione al momento sospesa in attesa di una decisione definitiva
C
C       if(deltf.lt.10.) ur=0.
C******
C____  COEFFICIENTE COMPLESSIVO
       IF (GAMA.EQ.0.) THEN
          UT=(UC+UR)
       ELSE
          UT=GAMA
       ENDIF
       DATI(ITU+ICE)=UT/GAM0
      ENDIF
C
  10    CONTINUE
C
C___  CALCOLO RESIDUI
C
	UTOT=DATI(ITU+ICE)*GAM0*FF
C
C______ TEST SULLA PORTATA DEI FUMI
C
	IF(WFABS.LT.1.E-3) THEN
C_____ PORTATA FUMI = 0.
	   TFC = TEME
	   RN(1+ICE) = (TFM-TFC)/T0
C
	   IF(ICE.EQ.NUCEL) THEN
	     TFU   =XYU(IXYU)
	     RN(1) =TFU-TFC/T0
	   ENDIF
C
	  RN(1+NUCEL+ICE)=(GAM-UTOT)/GAM0
C
	ELSE
C_____ PORTATA FUMI > 0.
          QBANK=GAM*(TFM-TEME)    !GAM non UTOT per evitare un loop algebrico
	  TCU  = TFM/(1.-BETA) -TFI*BETA/(1.-BETA)
	  HFU=HTFU(TCU,H2OBW,1)
C
	  RN(1+ICE) = (WF*(HFI-HFU)-QBANK*SUTO)/Q0
C
	  IF(ICE.EQ.NUCEL) THEN
	    TFU   =XYU(IXYU)
	    RN(1) =TFU-TCU/T0
	  ENDIF
C
	  RN(1+NUCEL+ICE)=(GAM-UTOT)/GAM0
	ENDIF
C
	ITM =ITM+NS
	IPC=IPC+8+DUENSMAX
C
 2000 CONTINUE
C
      RETURN
      END
CC
      SUBROUTINE FUMND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $  XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
