C**********************************************************************
C modulo aint.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)aint.f	5.2
C**********************************************************************
C
       SUBROUTINE AINTI3(IFO,IOB,DEBL)
C************************************************************************
C
C
C         AINT - INTEGRATORE
C
C
C************************************************************************
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       COMMON/AINT01/IBLOC
       COMMON/AINT02/NCEL,NPAR
       CHARACTER*80 DEBL
       CHARACTER*8 IBLOC
       CHARACTER*4 IOB
       CHARACTER*4 MOD
       DATA MOD/'AINT'/
C
       CALL AINTI4(IOB,MOD)
       NSTATI = 0
       NUSCIT = 1
       NINGRE = 2
C
       WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999  FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
       WRITE(IFO,3001)IOB
 3001  FORMAT('UINT',A4,2X,
     & '--UA-- INTEGRATOR OUTPUT VARIABLE')
C
       WRITE(IFO,3002)IOB
 3002  FORMAT('IINT',A4,2X,
     & '--IN-- INTEGRATOR INPUT VARIABLE')
C
       WRITE(IFO,3004)IOB
 3004  FORMAT('KTIN',A4,2X,
     & '--IN-- INTEGRAL TIME OF THE INTEGRATOR')
C
       RETURN
       END
       SUBROUTINE AINTI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       COMMON/AINT01/IBLOC
       COMMON/AINT02/NCEL,NPAR
       CHARACTER*8 IBLOC
       CHARACTER*4 IOB
       CHARACTER*4 MOD
C
       WRITE(IBLOC,1000)MOD,IOB
 1000  FORMAT(2A4)
       RETURN
       END
      SUBROUTINE AINTI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     &  IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
C*******************************************
C
C____ AINT - INTEGRATORE CON LIMITAZIONE ALTA E BASSA
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      GO TO(100,200), IFUN
 100  CONTINUE
C
C____ CHIAMATA AL MODULO AINT PER SCRIVERE I DATI
C
      IDP=ID1
      CALL AINTSI(IFUN,DATI,IDP)
C
      RETURN
C
C____ LETTURA DA FILE14 DEL NOME DEL REGOLATORE
C
  200 READ(14,1000)
 1000 FORMAT(A)
C
C____ CHIAMATA AL MODULO AINT PER LEGGERE I DATI
C
      IDP=ID1
      CALL AINTSI(IFUN,DATI,IDP)
C
      ID2=IDP
C
C
C_____ COSTANTI DI NORMALIZZAZIONE
C
      CNXYU(IV1  )=1.
      CNXYU(IV1+1)=1.
      CNXYU(IV1+2)=1.
C
C____ TOLLERANZE 1 PER MILLE
C
      TOL(1)=1.E-3
C
      RETURN
      END
      SUBROUTINE AINTSI(IFUN,DATI,ID)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
C
      GO TO (100,200),IFUN
C
C____ SCRITTURA SUL FILE 14 DEI DATI DI AINT
C
  100 CONTINUE
      WRITE(14,501)
  501 FORMAT(
     & '    SAT_MX   =          *    SAT_MN   =          *')
      RETURN
C
C____ LETTURA DA FILE 14 DEI DATI DI AINT
C
  200 CONTINUE
      READ(14,503)SATMAX,SATMIN
  503 FORMAT(2(14X,F10.0,1X))
      DATI(ID  )=SATMAX
      DATI(ID+1)=SATMIN
C
C_____ RISERVO UN POSTO PER LO STATO DELL' INTEGRATORE
C
      DATI(ID+2)=0.
      ID=ID+2
C
      RETURN
      END
      SUBROUTINE AINTC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT
C*******************************************
C
C____ REGOLATORE AINT - INTEGRATORE CON LIMITAZIONE ALTA E BASSA
C
C*********** INIZIO ISTRUZIONI DICHIARATIVE
C
C______ USCITE REGOLATORE
C
C      REAL UA01
C
C______ INGRESSI REGOLATORE
C
      REAL IN01                                                         !SNGL
      REAL KT01                                                         !SNGL
C      DOUBLE PRECISION IN01                                             !DBLE
C      DOUBLE PRECISION KT01                                             !DBLE
      LOGICAL SAT
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      GO TO (1,100,2),IFUN
 1    CONTINUE
C
C____ TOPOLOGIA JACOBIANO
C
      AJAC(1,1)=1.
      AJAC(1,2)=1.
      AJAC(1,3)=1.
      RETURN
C
 2    CONTINUE
C
C____ JACOBIANO
C
      UA01 = XYU(IXYU +  0)
      IN01 = XYU(IXYU +  1)
      KT01 = XYU(IXYU +  2)
C
      IDD=IPD
      CALL AINTSR(UA01,IN01,KT01,IDD,DATI,SAT,IBL1,IBL2,IFUN)
      IF(.NOT.KREGIM) THEN
C____ JACOBIANO IN TRANSITORIO
	IF(.NOT.SAT) THEN
	  AJAC(1,1)=-1.
	  AJAC(1,2)=DTINT/KT01
	  AJAC(1,3)=-DTINT*IN01/KT01/KT01
	ELSE
	  AJAC(1,1)=-1.
	ENDIF
      ELSE
C____ JACOBIANO A REGIME
	IF(.NOT.SAT) THEN
	  AJAC(1,2)=-1.
	ELSE
	  AJAC(1,1)=-1.
	ENDIF
      ENDIF
      RETURN
C
 100  CONTINUE
C
C____ DECODIFICA DELLE VARIABILI
C
      UA01 = XYU(IXYU +  0)
C
      IN01 = XYU(IXYU +  1)
      KT01 = XYU(IXYU +  2)
C
      IDD=IPD
      IF(KREGIM) THEN
C___ A REGIME
      UA01C=UA01
      CALL AINTSR(UA01C,IN01,KT01,IDD,DATI,SAT,IBL1,IBL2,IFUN)
       IF(.NOT.SAT) THEN
C
C____ RESIDUO QUANDO L'USCITA NON E` SATURATA
C
	 RNI(  1) = IN01
       ELSE
C
C____ RESIDUO QUANDO L'USCITA E` SATURATA
C
	 RNI(  1) = UA01-UA01C
       ENDIF
C
      ELSE
C___ IN TRANSITORIO
	 UA01C=UA01
	 CALL AINTSR(UA01C,IN01,KT01,IDD,DATI,SAT,IBL1,IBL2,IFUN)
C
C____ RESIDUI
C
	 RNI(  1) = UA01-UA01C
C
      ENDIF
      RETURN
      END
      SUBROUTINE AINTSR(UI,II,GT,ID,DATI,SAT,IBL1,IBL2,IFUN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
      COMMON/INTEGR/TLEGO1,TLEGO2,DTRE,NLEGO,TLEGO3                    !SNGL
C       COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      REAL II                                                          !SNGL
C       DOUBLE PRECISION II                                              !DBLE
      LOGICAL SAT
C
C
C        Integratore
C
C        Variabili Analogiche :
C
C        II    segnale in ingresso -
C        UI    uscita integratore -
C        UIP   stato uscita precedente
C        GT    tempo integrale in secondi
C        SATMIN  valore minimo uscita
C        SATMAX  valore massimo uscita
C
C
C______ DECODIFICA VARIABILI DEL PASSO PRECEDENTE
C
	 SATMAX = DATI(ID  )
	 SATMIN = DATI(ID+1)
	 SAT=.FALSE.
C
C        integrazione del segnale d' ingresso se non si e` a regime
C
	 IF (.NOT. KREGIM) THEN
C
	   IF(ITERT.EQ.0) THEN
	     UIP= UI
C_____ MEMORIZZAZIONE DELLO STATO
	     DATI(ID+2)=UIP
	   ELSE
	     UIP=DATI(ID+2)
	   ENDIF
C
	     UI = UIP + DTRE/GT * II
C=======================================================================
C        saturazione dell'uscita del regolatore e memorizzazione
C=======================================================================
	   IF (UI.LT.SATMIN) THEN
	       UI=SATMIN
	       SAT=.TRUE.
	   ENDIF
	   IF (UI.GT.SATMAX) THEN
	       UI=SATMAX
	       SAT=.TRUE.
	   ENDIF
C
C - - - A REGIME ...
C
	 ELSE
C=======================================================================
C_____  TEST SULLA SATURAZIONE
C=======================================================================
	   IF (UI.LE.SATMIN) THEN
	      IF(IFUN.EQ.2)WRITE(6,1000)IBL1,IBL2
 1000 FORMAT(//10X,'WARNING  ***** !'/
     $ ,10X,'OUTPUT < LOW LIMIT INTEGRATOR'/
C           'INTEGRATORE CON USCITA < DEL LIMITE BASSO'/
     $ ,10X,'BLOCCO ',2A4)
	       SAT=.TRUE.
	       UI=SATMIN
	   ENDIF
	   IF (UI.GE.SATMAX) THEN
	      IF(IFUN.EQ.2)WRITE(6,1001)IBL1,IBL2
 1001 FORMAT(//10X,'ATTENZIONE  ***** !'/
     $ ,10X,'OUTPUT > LOW LIMIT INTEGRATOR'/
C           'INTEGRATORE CON USCITA > DEL LIMITE ALTO'/
     $ ,10X,'BLOCK ',2A4)
	       SAT=.TRUE.
	       UI=SATMAX
	   ENDIF
C
C
C_____ MEMORIZZAZIONE DELLO STATO
C
	 DATI(ID+2) = UI
C
	 END IF
      RETURN
      END
CC
      SUBROUTINE AINTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                  IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
