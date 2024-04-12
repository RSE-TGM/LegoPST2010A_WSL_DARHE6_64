C**********************************************************************
C modulo mart.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)mart.f	5.2
C**********************************************************************
C********************************************************************
C*                                                                  *
C*                          modulo  MART                            *
C*                                                                  *
C*  Cinetica delle masse rotanti per N Gruppi Turbo-Alternatori     *
C*  solidali.                                                       *
C*                                                                  *
C********************************************************************
C
      SUBROUTINE MARTI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/MART01/IBLOC
      COMMON/MART02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'MART'/
C
      CALL MARTI4(IOB,MOD)
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      NSTATI=0
      NUSCIT=NCEL
      NINGRE=3*NCEL+3
C
      DO 20 K=1,NCEL
      WRITE(IFO,3000)K,IOB,K
 3000 FORMAT('RPM',I1,A4,2X,'--UA-- VELOCITY OF TURBINE N.',I1)
   20 CONTINUE
C
      DO 30 K=1,NCEL
      WRITE(IFO,3001)K,IOB,K
 3001 FORMAT('QTU',I1,A4,2X,'--IN-- POWER OF TURBINE N.',I1)
   30 CONTINUE
      DO 40 K=1,NCEL
      WRITE(IFO,3002)K,IOB,K
 3002 FORMAT('ASC',I1,A4,2X,'--IN-- TRIP OF TURBINE N.',I1)
   40 CONTINUE
      DO 50 K=1,NCEL
      WRITE(IFO,3003)K,IOB,K
 3003 FORMAT('AAV',I1,A4,2X,'--IN-- STARTING OF TURBINE N.',I1)
   50 CONTINUE
      WRITE(IFO,3004)IOB
 3004 FORMAT('ARIF',A4,2X,'--IN-- LOAD REJECTION')
      WRITE(IFO,3005)IOB
 3005 FORMAT('QAUS',A4,2X,'--IN-- AUXILIARIES POWER')
      WRITE(IFO,3006)IOB
 3006 FORMAT('RPMI',A4,2X,
     $  '--IN-- NETWORK FREQ (ISOLATED OR UNBOUNDED POWER)')
C
      RETURN
      END
C********************************************************************
C
      SUBROUTINE MARTI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/MART01/IBLOC
      COMMON/MART02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      PARAMETER (MAX=9)
C
   10 WRITE(6,101) MAX
  101 FORMAT(10X,'NUMBER OF TURBINES OF THE '/
     $       10X,'PLANT (1 - ',I1,') ?')
      READ(5,*) NCEL
C
      IF(NCEL.GE.1.AND.NCEL.LE.MAX) GOTO 15
      WRITE(6,103) NCEL
  103 FORMAT(/10X,'ERROR - N.TURBINES=',I2,/)
      GOTO 10
C
   15 CONTINUE
C
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
C********************************************************************
C
      SUBROUTINE MARTI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBLOC1,IBLOC2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (MAX=9)
      REAL INER                                                         !SNGL
C      DOUBLE PRECISION INER                                             !DBLE
      DIMENSION TAVV(MAX),PNOM(MAX),OMNOM(MAX),INER(MAX)
      DIMENSION QVEN(MAX),QLAM(MAX),QATT(MAX)
      CHARACTER*6 TAVVIA,POTNOM,OMNOMI,QVENTI,QLAMIN,QATTRI
      CHARACTER*8 DTLOAD
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      DATA TAVVIA/'TAVVIA'/, POTNOM/'POTNOM'/, OMNOMI/'OMNOMI'/,
     $     QVENTI/'QVENTI'/, QLAMIN/'QLAMIN'/, QATTRI/'QATTRI'/,
     $     DTLOAD/'DTLOAD'/
C
      NVAR  = IV2-IV1+1
      NTURB = (NVAR-3)/4
C
      GOTO(10,20), IFUN
C
C-- SCRITTURA SIMBOLO DEI DATI
C
   10 DO 5 I=1,NTURB
      WRITE(14,101) TAVVIA,I,POTNOM,I,OMNOMI,I
    5 CONTINUE
      DO 6 I=1,NTURB
      WRITE(14,101) QVENTI,I,QLAMIN,I,QATTRI,I
    6 CONTINUE
      WRITE(14,102) DTLOAD
  101 FORMAT(3(4X,A6,I2,' =',10X,'*'),5X)
  102 FORMAT(4X,A8,' =',10X,'*')
C
      RETURN
C
C-- LETTURA DEI DATI
C
   20 READ(14,201)
      DO 7 I=1,NTURB
      READ(14,201) TAVV(I),PNOM(I),OMNOM(I)
    7 CONTINUE
      DO 8 I=1,NTURB
      READ(14,201) QVEN(I),QLAM(I),QATT(I)
    8 CONTINUE
      READ(14,202) TLOAD
  201 FORMAT(3(14X,F10.0,1X),5X)
  202 FORMAT(14X,F10.0,1X)
C
C-- CALCOLO INERZIE
C
      DO 25 I=1,NTURB
      INER(I)=PNOM(I)*TAVV(I)*900./(OMNOM(I)*OMNOM(I)*3.1415*3.1415)
   25 CONTINUE
C
C-- MEMORIZZAZIONE DATI
C
      DATI(ID1)=NTURB
      DO 30 I=1,NTURB
      DATI(ID1+I) = INER(I)
   30 CONTINUE
      DO 40 I=1,NTURB
      DATI(ID1+NTURB+I) = OMNOM(I)
   40 CONTINUE
      DO 50 I=1,NTURB
C ! MW
      DATI(ID1+2*NTURB+I) = QVEN(I)*PNOM(I)/1.E6
   50 CONTINUE
      DO 60 I=1,NTURB
C ! MW
      DATI(ID1+3*NTURB+I) = QLAM(I)*PNOM(I)/1.E6
   60 CONTINUE
      DO 70 I=1,NTURB
C ! MW
      DATI(ID1+4*NTURB+I) = QATT(I)*PNOM(I)/1.E6
   70 CONTINUE
      DO 80 I=1,NTURB
C ! MW
      DATI(ID1+5*NTURB+I) = PNOM(I)/1.E6
   80 CONTINUE
      DATI(ID1+6*NTURB+1) = TLOAD
C
      DO 90 I=1,6*NTURB
      DATI(ID1+6*NTURB+1+I)=0.
   90 CONTINUE
C
      ID2=ID2+12*NTURB+1
C
C-- COSTANTI DI NORMALIZZAZIONE
C
      DO 95 I=1,NTURB
C ! velocita` turbine
      CNXYU(IV1+I-1        ) = 300.
C ! potenze turbine
      CNXYU(IV1+NTURB+I-1  ) = (H0*W0)
C ! segnali di scatto turbine
      CNXYU(IV1+2*NTURB+I-1) = 1.
C ! segnali di avviamento turbine
      CNXYU(IV1+3*NTURB+I-1) = 1.
   95 CONTINUE
C ! rifiuto di carico
      CNXYU(IV1+4*NTURB    ) = 1.
C ! potenza ausiliari
      CNXYU(IV1+4*NTURB+1  ) = (H0*W0)
C ! velocita` rete (isolata o inf.)
      CNXYU(IV1+4*NTURB+2  ) = 300.
C
      RETURN
      END
C********************************************************************
C
      SUBROUTINE MARTC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                  IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      EXTERNAL MART
C
      NTURB=DATI(IPD)
C
      GOTO (10,20,30), IFUN
C
C--- TOPOLOGIA JACOBIANO
C
   10 DO 15 I=1,NTURB
	DO 16 J=1,NTURB
	  AJAC(I,J)=1.
   16   CONTINUE
   15 CONTINUE
      DO 17 I=1,NTURB
	    AJAC(I,I+NTURB)=1.
   17 CONTINUE
      DO 18 I=1,NTURB
	DO 19 J=4*NTURB+2,4*NTURB+3
	  AJAC(I,J)=1.
   19   CONTINUE
   18 CONTINUE
      RETURN
C
C--- CALCOLO RESIDUI
C
   20 CALL MART(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C--- CALCOLO JACOBIANO NUMERICO
C
   30 NSTATI = 0
      NUSCIT = NTURB
      NINGRE = 3*NTURB+3
      EPS    = 1.E-4
      EPSLIM = 1.E-5
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,MART)
C
      RETURN
      END
C********************************************************************
C
      SUBROUTINE MART(IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (MAX=9)
C ! VALORE IN ACCORDO CON LE POTENZE (MW)
      PARAMETER (COP=10.)
      DIMENSION XYU(*),DATI(*),RNI(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      LOGICAL ISCA,IAVV,JFLOLOG
      REAL INER(MAX),NSCA,NAVV,NFUNZ,KVEN(MAX),                          !SNGL
     $ KLAM(MAX),KATT(MAX),KTOT(MAX)                                     !SNGL
C      DOUBLE PRECISION INER(MAX),NSCA,NAVV,NFUNZ,KVEN(MAX),              !DBLE
C     $ KLAM(MAX),KATT(MAX),KTOT(MAX)                                     !DBLE
      DIMENSION QTU(MAX),QAC(MAX),QAUS(MAX),QREG(MAX),PNOM(MAX)
      DIMENSION SCA(MAX),AVV(MAX)
      DIMENSION OMEG(MAX),OMNOM(MAX),OMEGC(MAX),ON(MAX)
      DIMENSION OM2(MAX),OMRET(MAX)
      DIMENSION ECIN(MAX),ECINK(MAX),DELTECIN(MAX)
      DIMENSION PESI(MAX)
      DIMENSION QVEN(MAX),QLAM(MAX),QATT(MAX)
C ! NUMERO TURBINE COSTITUENTI L'IMPIANTO
      INTEGER NTURB
C ! DISCRIMINA FRA INSEGUIM. E INTEGRAZ. EQUAZ.
      INTEGER CALCOL(MAX)
C
C-- DECODIFICA VARIABILI E DATI
C
      NTURB    = DATI(IPD)
C
      DO 5 I=1,NTURB
      OMEG(I)  = XYU(IXYU+I-1)*300.
C ! MW
      QTU(I)   = XYU(IXYU+NTURB+I-1)*(H0*W0)/1.E6
      ISCA     = JFLOLOG(XYU(IXYU+2*NTURB+I-1))
      SCA(I)   = 0.
      IF (ISCA)  SCA(I)   = 1.
      IAVV = JFLOLOG(XYU(IXYU+3*NTURB+I-1))
      AVV(I)   = 0.
      IF (IAVV)  AVV(I)   = 1.
    5 CONTINUE
C
      RIFCA    = XYU(IXYU+4*NTURB)
C ! MW
      QISO     = XYU(IXYU+4*NTURB+1)*(H0*W0)/1.E6
      FREQ     = XYU(IXYU+4*NTURB+2)*300.
C
      DO 6 I=1,NTURB
      INER(I)  = DATI(IPD+I)
      OMNOM(I) = DATI(IPD+NTURB+I)
      QVEN(I)  = DATI(IPD+2*NTURB+I)
      QLAM(I)  = DATI(IPD+3*NTURB+I)
      QATT(I)  = DATI(IPD+4*NTURB+I)
      PNOM(I)  = DATI(IPD+5*NTURB+I)
    6 CONTINUE
      TLOAD    = DATI(IPD+6*NTURB+1)
C
C--- INTRODUZIONE DI VALORI STANDARD PER LE PERDITE NEL CASO
C--- IN CUI L' UTENTE NON ABBIA INSERITO ALCUN VALORE
C
      DO 7 I=1,NTURB
      IF (QVEN(I) .LE. .000001) QVEN(I)=.0125000*PNOM(I)
      IF (QLAM(I) .LE. .000001) QLAM(I)=.0015625*PNOM(I)
      IF (QATT(I) .LE. .000001) QATT(I)=.0006375*PNOM(I)
    7 CONTINUE
C
C*******************************************************************
C*                                                                 *
C*             MASSE ROTANTI DI PIU` TURBINE SOLIDALI              *
C*                                                                 *
C*                        CALCOLO RESIDUI                          *
C*                                                                 *
C*******************************************************************
C
C
C-- CALCOLO NUMERO DI TURBINE SCATTATE, "NSCA"
C
      NSCA=0
      DO 60 I=1,NTURB
	 NSCA=NSCA+SCA(I)
  60  CONTINUE
C
C-- CALCOLO NUMERO DI TURBINE IN FASE DI AVVIAMENTO, "NAVV"
C
      NAVV=0
      DO 70 I=1,NTURB
	 NAVV=NAVV+AVV(I)
  70  CONTINUE
C
C--- DISCRIMINAZIONE FRA FUNZIONAMENTO NORMALE (INSEGUIMENTO)
C--- E FUNZIONAMENTO IN RIFIUTO DI CARICO, SCATTO O AVVIAMENTO
C--- (INTEGRAZIONE DELL' EQUAZIONE DELLE MASSE ROTANTI)
C
      DO 61 I=1,NTURB
	CALCOL(I)=0
  61  CONTINUE
C ! RIFIUTO DI CARICO
      IF (RIFCA .GT. 0.1) THEN
	DO 62 I=1,NTURB
	  CALCOL(I)=1
  62    CONTINUE
      ELSE
	DO 63 I=1,NTURB
C ! SCATTO     TURBINA I-ESIMA
	  IF (SCA(I) .GT. 0.9) CALCOL(I)=1
C ! AVVIAMENTO TURBINA I-ESIMA
	  IF (AVV(I) .GT. 0.9) CALCOL(I)=1
  63    CONTINUE
      ENDIF
C
C--------------------------------------------------
C--         FUNZIONAMENTO IN INSEGUIMENTO        --
C--------------------------------------------------
C
      DO 10 I=1,NTURB
	 IF (CALCOL(I) .EQ. 0) THEN
	    OMEGC(I)=FREQ
	    RNI(I) = (OMEG(I)-OMEGC(I))/3000.
C
C----- INIZIALIZZAZIONE DELLA POTENZA MOTRICE E DELL'ENERGIA
C----- CINETICA DA UTILIZZARE COME C.I. PER INTEGRAZIONE
C
	    QREG(I)=QTU(I)
	    DATI(IPD+11*NTURB+1+I)=QREG(I)
	    OM2(I)=(OMEG(I)*2*3.1415/60.)**2
C ! ENERGIA CINETICA IN MJ
	    ECIN(I)=.5*INER(I)*OM2(I)/1.E6
	    DATI(IPD+8*NTURB+1+I)=ECIN(I)
	    DATI(IPD+9*NTURB+1+I)=ECIN(I)
C
C----- AZZERAMENTO DELLA TEMPORIZZAZIONE
C
	    DATI(IPD+6*NTURB+1+I)=0.
C
C----- INIZIALIZZAZIONE DEL CONTATORE DT0
C
	    DATI(IPD+7*NTURB+1+I)=TLOAD
	 ELSE
C
C--------------------------------------------------
C INTEGRAZIONE DELL'EQUAZIONE DELLE MASSE ROTANTI
C--------------------------------------------------
C
	    TEMPOR= DATI(IPD+6*NTURB+1+I)
	    ECINK(I) = DATI(IPD+8*NTURB+1+I)
C
	    IF(TEMPOR.LT.TLOAD*4.) THEN
C
C***************************************************************
C*                                                             *
C*         ----  SIGNIFICATO DEL TEST SU TEMPOR  ----          *
C*                                                             *
C*  DELTECIN(I) VIENE CALCOLATO SENZA CONSIDERARE L'ANDAMENTO  *
C*  DELLA POTENZA PRODOTTA DALLA TURBINA, QTU(I). QUESTO MODO  *
C*  DI PROCEDERE E' SEGUITO FINCHE' IL CONTATORE (TEMPOR) E'   *
C*  MINORE DI UN VALORE DA SCEGLIERSI OPPORTUNAMENTE (PER      *
C*  ORA TALE VALORE E' STATO SCELTO PARI A 4 * TLOAD). PIU'    *
C*  PRECISAMENTE, IL VALORE DI RIFERIMENTO DEVE ESSERE:        *
C*                                                             *
C*   1) MAGGIORE DEL MASSIMO FRA IL TEMPO DI CHIUSURA DELLE    *
C*      VALVOLE (TLOAD) E IL PASSO DI INTEGRAZIONE (DTINT)     *
C*                                                             *
C*   2) MINORE DEL TEMPO DURANTE IL QUALE LE VALVOLE SI        *
C*      MANTENGONO CHIUSE (QUANDO LA TURBINA(I) RICOMINCIA     *
C*      A FORNIRE POTENZA DELTECIN(I) DEVE TENERE CONTO DI     *
C*      QTU(I))                                                *
C*                                                             *
C***************************************************************
C
	       DELTECIN(I)=DATI(IPD+10*NTURB+1+I)
C
	       IF(ITERT.LE.0.AND.IFUN.EQ.2.) THEN
C
		  DTX=DTINT
C
C----- INCREMENTO DEL CONTATORE
C
		  DATI(IPD+6*NTURB+1+I)=DATI(IPD+6*NTURB+1+I)+DTX
C
		  DATI(IPD+8*NTURB+1+I)=DATI(IPD+9*NTURB+1+I)
		  ECINK(I)=DATI(IPD+8*NTURB+1+I)
		  QREG(I)= DATI(IPD+11*NTURB+1+I)
		  DT0 = DATI(IPD+7*NTURB+1+I)
		  IF (DT0 .LE. DTX) THEN
		     DELTECIN(I)=QREG(I)*DT0/2.
		     QREG(I)=0.
		     DATI(IPD+11*NTURB+1+I)=QREG(I)
		     DT0=0.
		     DATI(IPD+7*NTURB+1+I)=DT0
		  ELSE
		     DELTECIN(I)=QREG(I)*DTX*(1.-DTX/(2.*DT0))
		     QREG(I)=QREG(I)*(1.-DTX/DT0)
		     DATI(IPD+11*NTURB+1+I)=QREG(I)
		     DT0=DT0-DTX
		     DATI(IPD+7*NTURB+1+I)=DT0
		  ENDIF
		  DATI(IPD+10*NTURB+1+I)=DELTECIN(I)
	       ENDIF
C
C---- VIA SEGUITA QUANDO LA VALVOLA SI E` CHIUSA E IL TEMPO TRASCORSO
C---- DALLA CHIUSURA E` > 4 * TLOAD (IL CALCOLO DI DELTECIN(I) TORNA A
C---- CONSIDERARE LA POTENZA PRODOTTA DALLA TURBINA, QTU(I))
C
	    ELSE
	       IF(ITERT.LE.0.AND.IFUN.EQ.2.) THEN
		  DATI(IPD+8*NTURB+1+I)=DATI(IPD+9*NTURB+1+I)
		  ECINK(I)=DATI(IPD+8*NTURB+1+I)
	       ENDIF
	       DELTECIN(I)=QTU(I)*DTINT
	    ENDIF
C
C
C----- CALCOLO DELLE POTENZE FRENANTI FUNZIONI DELLA VELOCITA'
C
C
	    ON(I)=OMEG(I)/OMNOM(I)
C
C--     CALCOLO PERDITE PER VENTILAZIONE
C
	    KVEN(I)=QVEN(I)*ON(I)*ON(I)*ON(I)
C
C--     CALCOLO PERDITE LAMINARI
C
	    KLAM(I)=QLAM(I)*ON(I)*ON(I)
C
C--   CALCOLO PERDITE PER ATTRITO
C
	    KATT(I)=QATT(I)*ON(I)
C
C--     PERDITE GLOBALI
C
	    KTOT(I)=KLAM(I)+KVEN(I)+KATT(I)
C
C
C-- CALCOLO NUMERO DI TURBINE IN FUNZIONE (NON
C-- SCATTATE E NON IN FASE DI AVVIAMENTO), "NFUNZ"
C
	    NFUNZ=REAL(NTURB)-NSCA-NAVV                                 !SNGL
C            NFUNZ=DBLE(NTURB)-NSCA-NAVV                                 !DBLE
C
C--- CALCOLO POTENZE AUSILIARI
C
	    IF (SCA(I).GT.0.9 .OR. AVV(I).GT.0.9) THEN
C
C--- AZZERAMENTO POTENZA AUSILIARI PER LE
C--- TURBINE SCATTATE O IN FASE DI AVVIAMENTO
C
	       QAUS(I)=0.
	    ELSE
C
C--- RIPARTIZIONE POTENZA AUSILIARI SULLE "NFUNZ" TURBINE IN FUNZIONE
C
	       QAUS(I)=QISO/NFUNZ
	    ENDIF
C
C-- CALCOLO POTENZE DI ACCOPPIAMENTO
C
C ! una o nessuna turbina connessa
	    IF (NFUNZ .LT. 1.1) THEN
	       QAC(I)=0.
C
C ! piu` turbine connesse
	    ELSE
	       DO 90 J=1,NTURB
		  IF (SCA(J).GT.0.9 .OR. AVV(J).GT.0.9) THEN
		     PESI(J)=0.
		  ELSE
		     PESI(J)=1.
		  ENDIF
  90           CONTINUE
	       SOMMAPESI=0.
	       SOMMAPESATA=0.
	       DO 91 J=1,NTURB
		  SOMMAPESI=SOMMAPESI+PESI(J)
		  SOMMAPESATA=SOMMAPESATA+PESI(J)*OMEG(J)
  91           CONTINUE
	       IF (SCA(I).LT.0.1 .AND. AVV(I).LT.0.1)  THEN
		  OMRET(I)=(SOMMAPESATA-PESI(I)*OMEG(I))/
     $                     (SOMMAPESI-PESI(I))
		  QAC(I)=COP*(OMEG(I)-OMRET(I))
	       ELSE
		  QAC(I)=0.
	       ENDIF
	    ENDIF
C
C
C___ CALCOLO PER INTEGRAZIONE DELL'ENERGIA CINETICA (IN MJ)
C
C
	    ECIN(I)=(-QAUS(I)-KTOT(I)-QAC(I))*DTINT+
     $              ECINK(I)+DELTECIN(I)
C
C
C
	    IF(ECIN(I).LT.0.) ECIN(I)=0.
	    DATI(IPD+9*NTURB+1+I)=ECIN(I)
C
C ! TEST INGIUSTIFICATO
	    IF(INER(I).LT.1.) INER(I)=10000.
C
C_______ CALCOLO DELLA VELOCITA` DI ROTAZIONE
C
	    OMEGC(I)=SQRT(2.*ECIN(I)/INER(I))*6.E4/(2.*3.1415)
	    RNI(I)=(OMEG(I)-OMEGC(I))/3000.
C
	 ENDIF
  10  CONTINUE
      RETURN
      END
CC
      SUBROUTINE MARTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $   XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
