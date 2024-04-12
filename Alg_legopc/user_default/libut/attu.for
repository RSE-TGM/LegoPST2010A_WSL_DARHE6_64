C**********************************************************************
C modulo attu.f
C tipo 
C release 5.3
C data 10/3/96
C reserver @(#)attu.f	5.3
C**********************************************************************
C
      SUBROUTINE ATTUI3(IFO,IOB,DEBL)
      COMMON/ATTU00/IBLOC,NCEL,NPAR
      CHARACTER*4 MOD, IOB, IBLOC*8, DEBL*80, INIZ*1, IVAR*2
      DATA MOD/'ATTU'/
C
      CALL ATTUI4(IOB,MOD,IBLOC,NCEL,INIZ)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
C
      IF (INIZ .EQ. ' ') THEN
        IVAR = 'VV'
      ELSE
        IVAR = INIZ // 'V'
      ENDIF
      DO K=1,NCEL
        WRITE(IFO,3000)IVAR,K,IOB,'US','VALUE',K
      ENDDO
C
      IF (INIZ .EQ. ' ') THEN
        IVAR = 'ST'
      ELSE
        IVAR = INIZ // 'S'
      ENDIF
      DO K=1,NCEL
        WRITE(IFO,3000)IVAR,K,IOB,'IN','SET POINT',K
      ENDDO
C
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(A2,I2,A4,'  --',A2,
     $  '-- ACTUATOR: ',A,' OF ACTUATED VARIABLE N.',I2)
      END
C
C
C
      SUBROUTINE ATTUI4(IOB,MOD,IBLOC,NCEL,INIZ)
      PARAMETER (MAXX = 7)
      CHARACTER*4 MOD, IOB, IBLOC*8, INIZ*1
C
      IBLOC = MOD // IOB
C
    1 WRITE(6,11) MAXX
   11 FORMAT(10X,'NUMBER OF ACTUATED VARIABLES (MAX. =',I2,') ?')
      READ (5,*,ERR=1) NCEL
      IF (NCEL .GT. MAXX) GOTO 1
C
    2 WRITE(6,12)
   12 FORMAT(10X,'I/O VARIABLES FIRST CHARACTER [RETURN=DEFAULT] ?')
      READ(5,13,ERR=2) INIZ
   13 FORMAT(A)
      ICA = ICHAR(INIZ)
      IF (ICA .GE. 97 .AND. ICA .LE. 122) THEN
        INIZ = CHAR(ICA-32)
      ELSE IF (ICA .LT. 32 .OR. ICA .GE. 127) THEN
        INIZ = ' '
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE ATTUI2(IFUN,SYMB,MX,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBL1,IBL2,IER,CNXYU,TOL)
C
C     Modulo attuatori
C     preparazione file dati e lettura dati
C
      DIMENSION SYMB(MX,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
      CHARACTER*4 NNORM(11)
      CHARACTER*3 ANORMU,ANORMX
      DIMENSION CNORM(8)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      EQUIVALENCE (CNORM(1),P0)
      DATA NNORM/'P0 ','H0 ','T0 ','W0 ','RO0','AL0','V0 ','DP0','  ',
     1    'Q0 ','OM0'/
      DATA OM0/314.1592/
C
      GOTO (1,10),IFUN
C
C     Scrittura simboli dei dati su file 14
C
  1   DO 2 I=1,(IV2+1-IV1)/2
  2        WRITE(14,1000) 'TAU ',I,'GAIN',I,'VMAX',I,'NORU',I,'NORX',I
 1000 FORMAT(3(4X,A4,I2,2X,' =',10X,'*'))
C
      RETURN
C
C     LETTURA DATI DA FILE 14
C
   10 READ(14,2000)
 2000 FORMAT(10X)
C
      IER = 0
      K1 = ID1
      K2 = ID1+1
      NDATI = (IV2+1-IV1)/2
      DATI(K1) = NDATI
C
      LX = 0
      LU = 0
      DO 11 J=IV1,IV1+NDATI-1
      READ(14,2001) (DATI(I),I=K2,K2+2),ANORMU,ANORMX
 2001 FORMAT(3(14X,F10.0,1X)/2(14X,A3,8X))
C
      DO 12 K=1,11
       IF(ANORMX.EQ.NNORM(K)) LX = K
       IF(ANORMU.EQ.NNORM(K)) LU = K
  12  CONTINUE
C
      IF(LU.LE.0 .OR. LX.LE.0) THEN
      PRINT *,'ANU',ANORMU,'ANX',ANORMX,'LX',LX,'LU',LU
      IER = 1
      WRITE(6,*) 'NORMALIZZAZIONE ERRATA'
      ELSE
      IF(LX.LT.9) CNXYU(J) = CNORM(LX)
      IF(LX.EQ.9) CNXYU(J) = 1.
      IF(LX.EQ.10) CNXYU(J) = W0*H0
      IF(LX.EQ.11) CNXYU(J) = OM0
      IF(LU.LT.9) CNXYU(NDATI+J) = CNORM(LU)
      IF(LU.EQ.9) CNXYU(NDATI+J) = 1.
      IF(LU.EQ.10) CNXYU(NDATI+J) = W0*H0
      IF(LU.EQ.11) CNXYU(NDATI+J) = OM0
      DATI(K2+1) = DATI(K2+1)/CNXYU(J)*CNXYU(J+NDATI)  !!! Norm. gain
      DATI(K2+2) = DATI(K2+2)/CNXYU(J)     !!! Norm. vmax
      LU = 0       !!! DATI(IPD+3*(I-1)+1) = Tau
      LX = 0       !!! DATI(IPD+3*(I-1)+2) = Gain
      K2 = K2+3    !!! DATI(IPD+3*(I-1)+3) = Vmax
      ENDIF
  11  CONTINUE
C
      ID2 = K2-1
C
      RETURN
      END
C
      SUBROUTINE ATTUC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RN,IBL1,IBL2)
C
      PARAMETER (MAXX = 7)
      DIMENSION AJAC(MX5,1),XYU(1),RN(1),DATI(1)
      DIMENSION X(MAXX),U(MAXX),TAU(MAXX),GAIN(MAXX)
C
      NVARX = DATI(IPD)
      GO TO (10,20,20),IFUN
C
C      TOPOLOGIA JACOBIANO
C
  10  DO 1 I=1,NVARX
      AJAC(I,I)=1.
   1  AJAC(I,I+NVARX)=1.
      RETURN
C
C      DECODIFICA DATI E VARIABILI
C
  20  K1 = IPD+1
      K2 = K1
      DO 2 I=1,NVARX
         TAU(I) = DATI(K2)
         GAIN(I) = DATI(K2+1)
         X(I) = XYU(IXYU+I-1)
         U(I) = XYU(IXYU+NVARX-1+I)
  2      K2 = K2+3
C
C      DERIVATE
C
      DO 3 I=1,NVARX
      RN(I) = -X(I)/TAU(I)+U(I)/TAU(I)*GAIN(I)
  3   IF(ABS(RN(I)).GT.DATI(IPD+3*I)) RN(I) = SIGN(DATI(IPD+3*I),RN(I))
      IF(IFUN.EQ.2) RETURN
C
C      JACOBIANO
C
      DO 4 I=1,NVARX
      AJAC(I,I)=-1./TAU(I)
      AJAC(I,I+NVARX)=1./TAU(I)*GAIN(I)
      IF(RN(I).GT.DATI(IPD+3*I)) THEN
      AJAC(I,I) = 0.
      AJAC(I,I+NVARX)=0.
      ELSE
      ENDIF
  4   CONTINUE
C
      RETURN
      END
C
      SUBROUTINE ATTUD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                  IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
