C**********************************************************************
C modulo asom.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)asom.f	5.2
C**********************************************************************
C
      SUBROUTINE ASOMI3(IFO,IOB,DEBL)
C*****************************************************************************
C
C
C        BLOCCO SOMMATORE
C
C
C*****************************************************************************
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/ASOM01/IBLOC
      COMMON/ASOM02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'ASOM'/
C
      CALL ASOMI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 1
      NINGRE = NCEL
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3001)IOB
 3001 FORMAT('USOM',A4,2X,
     & '--UA-- ANALOG OUTPUT SIGNAL FROM THE ADDER')
      DO I=1,NCEL
C
      WRITE(IFO,3003)I,IOB,I
 3003 FORMAT('I',I1,'SO',A4,2X,
     & '--IN-- INPUT SIGNAL ',I1,' TO THE ADDER')
C
      ENDDO
C
      RETURN
      END
      SUBROUTINE ASOMI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/ASOM01/IBLOC
      COMMON/ASOM02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
    1 WRITE(6,*)'  HOW MANY INPUT SIGNALS ? (MAX 9)'
      READ(5,*)NCEL
       IF(NCEL.LT.0.OR.NCEL.GT.9) GO TO 1
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
      RETURN
      END
      SUBROUTINE ASOMI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     &  IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
C*******************************************
C
C____ ASOM - BLOCCO SOMMATORE CON USCITA LIMITATA
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      NIN=IV2-IV1
C
      GO TO(100,200), IFUN
 100  CONTINUE
C
C____ CHIAMATE AL MODULO ASOM PER SCRIVERE I DATI
C
      IDP=ID1
      CALL ASOMSI(IFUN,DATI,IDP,NIN)
C
      RETURN
C
C____ LETTURA DA FILE14 DEL NOME DEL BLOCCO
C
  200 READ(14,1000)
 1000 FORMAT(A)
C
C____ CHIAMATE AL MODULO ASOM PER LEGGERE I DATI
C
      IDP=ID1
      CALL ASOMSI(IFUN,DATI,IDP,NIN)
C
C___ riservo una posizione per depositare lo stato " saturazione"
      ID2=IDP+1
C
C____ COSTANTI DI NORMALIZZAZIONE
C
      DO I=1,NIN+1
      CNXYU(IV1+I-1 )=1.
      ENDDO
C
C____ TOLLERANZE 1 PER MILLE
C
      TOL(1)=1.E-3
C
      RETURN
      END
      SUBROUTINE ASOMSI(IFUN,DATI,ID,NIN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*),GUAD(9)
C
      GO TO (100,200),IFUN
C
C____ SCRITTURA SUL FILE 14 DEI DATI DI ASOM
C
  100 CONTINUE
      WRITE(14,499)(I,I=1,NIN)
  499 FORMAT(3(4X,'GUAD',I4,' =',10X,'*',:))
      WRITE(14,500)
  500 FORMAT('    U MAX    =          *    U MIN    =          *')
      RETURN
C
C____ LETTURA DA FILE 14 DEI DATI DI PROP
C
  200 CONTINUE
      READ(14,502)(GUAD(I),I=1,NIN)
      READ(14,502)UMAX,UMIN
  502 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID   )=NIN
      DATI(ID+1 )=UMAX
      DATI(ID+2 )=UMIN
C
      DO I=1,NIN
      DATI(ID+2+I)=GUAD(I)
      ENDDO
C
      ID=ID+2+NIN
      RETURN
      END
      SUBROUTINE ASOMC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT
C*******************************************
C
C____ ASOM - BLOCCO SOMMATORE CON USCITA LIMITATA
C
C*********** INIZIO ISTRUZIONI DICHIARATIVE
      REAL II (9) ,GUAD(9)                                              !SNGL
C      DOUBLE PRECISION II (9) ,GUAD(9)                                  !DBLE
      LOGICAL SAT
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      NIN  =DATI(IPD   )
      UMAX =DATI(IPD+1 )
      UMIN =DATI(IPD+2 )
C
      DO I=1,NIN
	GUAD(I)=DATI(IPD+2+I)
      ENDDO
C___ DECODIFICO lo stato " saturazione"
      FSAT=DATI(IPD+2+NIN+1)
C
      GO TO (1,100,2),IFUN
C
C____ TOPOLOGIA JACOBIANO
C
 1    DO I=1,NIN+1
      AJAC(1,I)=1.
      ENDDO
      RETURN
C
C____ COEFFICIENTI JACOBIANO
C
 2    CONTINUE
      IF(FSAT.EQ.0.) THEN
C___ NON SONO IN SATURAZIONE
	 AJAC(1,1)=-1.
	 DO I=1,NIN
	   AJAC(1,I+1)=GUAD(I)
	 ENDDO
      ELSE
C___  SONO IN SATURAZIONE
	 AJAC(1,1)=-1.
      ENDIF
      RETURN
C
 100  CONTINUE
C
C____ DECODIFICA DELLE VARIABILI
C
      UU   = XYU(IXYU)
      DO I=1,NIN
	II(I)= XYU(IXYU +I)
      ENDDO
      FSAT=DATI(IPD+2+NIN+1)
C
      CALL ASOMSR(UUC,II,FSAT,NIN,UMAX,UMIN,GUAD,ITERT)
C
C____ RESIDUI
C
      RNI(  1) = UU-UUC
      DATI(IPD+2+NIN+1)=FSAT
      RETURN
      END
      SUBROUTINE ASOMSR(UU,II,FSAT,NIN,UMAX,UMIN,GUAD,ITERT)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      LOGICAL KREGIM
      REAL      II(*),GUAD(*)                                          !SNGL
C       DOUBLE PRECISION      II(*),GUAD(*)                              !DBLE
      COMMON/REGIME/KREGIM
C
      UU = 0.
      DO I=1,NIN
      UU = UU + GUAD(I)*II(I)
      ENDDO
C
C____ DEFINISCO LA SATURAZIONE FACENDO IL TEST SOLO
C     QUANDO SONO ALL'INIZIO DI UN PASSO DI TEMPO
C
       IF(ITERT.EQ.0.OR.KREGIM) THEN
	 FSAT=0.
	 IF(UU.LT.UMIN) THEN
	    UU=UMIN
	    FSAT=-1.
	 ENDIF
	 IF(UU.GT.UMAX) THEN
	    UU=UMAX
	    FSAT=1.
	 ENDIF
       ELSE
	 IF(FSAT) 10,20,30
 10        UU=UMIN
 20        RETURN
 30        UU=UMAX
       ENDIF
C
      RETURN
      END
CC
      SUBROUTINE ASOMD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $      IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
