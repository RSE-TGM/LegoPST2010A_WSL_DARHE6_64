C**********************************************************************
C modulo nodo.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)nodo.f	5.2
C**********************************************************************
C
      SUBROUTINE NODOI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NODO01/IBLOC
      COMMON/NODO02/NCEL
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'NODO'/
C
      CALL NODOI4(IOB,MOD)
C
      NSTATI=0
      NUSCIT=1
      NINGRE=NCEL-1
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('USOM',A4,2X,
     $  '--UA-- LINEAR RELATION : OUTPUT VARIABLE')
C
      DO 30 K=1,NCEL-1
      WRITE(IFO,3001)K,IOB,K
 3001 FORMAT('IN',I2,A4,2X,
     $  '--IN-- LINEAR RELATION : INPUT N. ',I2)
   30 CONTINUE
C
      RETURN
      END
      SUBROUTINE NODOI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NODO01/IBLOC
      COMMON/NODO02/NCEL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      MAX=20
C
   10 WRITE(6,101) MAX
  101 FORMAT(10X,'NUMBER OF VARIABLES APPEARING'/
     $       10X,'IN THE LINEAR EQUATION (02 -',I3,') ?')
      READ(5,*) NCEL
  102 FORMAT(I2)
      IF(NCEL.GE.2.AND.NCEL.LE.MAX) GOTO 15
      WRITE(6,103) NCEL
  103 FORMAT(/10X,'ERROR - N.VAR.=',I3,/)
      GOTO 10
C
   15 CONTINUE
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
      SUBROUTINE NODOI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBLOC1,IBLOC2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (MAX=20)
      INTEGER VAR
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      DIMENSION COEF(MAX),CNORM(8)
      CHARACTER*4 SNO(MAX),NOR,ALIZ
      CHARACTER*10 NORMA(MAX)
      CHARACTER*4 NORSIM(11)
      EQUIVALENCE (CNORM(1),P0)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/NO/NORMA
      DATA NOR/'NORM'/,ALIZ/'ALIZ'/
      DATA NORSIM/'P0  ','H0  ','T0  ','W0  ','RO0 ',
     $            'AL0 ','V0  ','DP0 ','Q0  ','OM0 ','    '/
C
      NVAR=IV2-IV1+1
C
      GOTO(10,20), IFUN
C
   10 CONTINUE
      SNO(1)='U_01'
      DO I=2,NVAR
      J=I-1
      WRITE(SNO(I),301)J
 301  FORMAT('I_',I2)
      END DO
      WRITE(14,101) NOR,ALIZ,(NOR,SNO(I),I=2,NVAR)
  101 FORMAT(3(4X,2A4,' =',10X,'*'),5X)
C
      WRITE(14,101) (VAR(I,1),VAR(I,2),I=IV1,IV2)
C
      RETURN
C
   20 READ(14,201)
      READ(14,201) (NORMA(I),I=1,NVAR)
  201 FORMAT(3(14X,A10,1X),5X)
C
      READ(14,202) (COEF(I),I=1,NVAR)
  202 FORMAT(3(14X,F10.0,1X),5X)
C
C-------------------- CISE  18-06-1990 -----------------------------
C
C     Assegnazione automatica della costante di normalizzazione
C     e del coefficiente da utilizzare nella combinazione lineare
C
C
      DO 1 II=2,NVAR
	IF(NORMA(II).EQ.'          ') NORMA(II)=NORMA(II-1)
    1 CONTINUE
C
C--------------------------------------------------------------------
C
      DATI(ID1)=NVAR
      DO 30 I=1,NVAR
C
      DO 25 J=1,11
      IF(NORMA(I)(1:4).EQ.NORSIM(J)) GOTO 26
   25 CONTINUE
      READ(NORMA(I),24,ERR=27) COENORM
   24 FORMAT(G10.5)
      IF(COENORM.LT..1) GOTO 27
      GOTO 28
   27 WRITE(6,203) NORMA(I)
  203 FORMAT(5X,'THE SYMBOL ',A10,'IS NOT CONTEMPLATED OR IS < .1')
      IER=1
      GOTO 40
   26 COENORM=1.
      IF(J.LE.8) COENORM=CNORM(J)
      IF(J.EQ.9) COENORM=W0*H0
      IF(J.EQ.10) COENORM=314.1592
C
   28 ID2=ID1+I
      IF(I.EQ.1) COEUSC=COENORM
      DATI(ID2)=COEF(I)*COENORM/COEUSC
C
      CNXYU(IV1+I-1)=COENORM
   30 CONTINUE
C
   40 CONTINUE
      RETURN
      END
      SUBROUTINE NODOC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                  IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (MAX=20)
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      DIMENSION COEF(MAX),VAR(MAX)
C
      NVAR=DATI(IPD)
C
      GOTO (10,30,30), IFUN
C
C  TOPOLOGIA JACOBIANO
C
   10 DO 20 I=1,NVAR
      AJAC(1,I)=1.
   20 CONTINUE
C
C  DECODIFICA COEFFIC. E VARIABILI
C
   30 DO 40 I=1,NVAR
      COEF(I)=DATI(IPD+I)
      VAR(I)=XYU(IXYU+I-1)
   40 CONTINUE
C
      IF(IFUN.EQ.2) GOTO 60
C
C  CALCOLO JACOBIANO
C
      DO 50 I=1,NVAR
      AJAC(1,I)=-COEF(I)
   50 CONTINUE
      RETURN
C
C  CALCOLO RESIDUO
C
   60 SOMVAR=0.
      DO 70 I=1,NVAR
      SOMVAR=SOMVAR+COEF(I)*VAR(I)
   70 CONTINUE
C
      RNI(1)=SOMVAR
C
      RETURN
      END
CC
      SUBROUTINE NODOD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $  XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
