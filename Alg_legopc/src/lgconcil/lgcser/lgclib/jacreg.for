C******************************************************************************
C modulo jacreg.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)jacreg.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE JACREG(NBL,ISLB,IPDATI,IP,XYU,DATI,IPVRS,NUSCI,NUSTA,
     $                  NZMAX,NZTER,IRJ,ICJ,FJ,NEQSIS,RIGA,AJAC,MMX5,
     $                  NOBLC,MX3,RNI,
C********************* TAVOLE ******************************************
     $                  NOSUB,NNOTO,IA)
C********************* TAVOLE ******************************************
      DIMENSION ISLB(*),IPDATI(*),IP(*),XYU(*),DATI(*),NUSCI(*),
     $          NUSTA(*),FJ(*),RIGA(*),IRJ(*),ICJ(*),IA(*),
     $          NOBLC(MX3,2),RNI(*),AJAC(MMX5,MMX5),IPVRS(*)
      COMMON/NORM/P0,H0,T0,Q0,RO0,AL0,V0,DP0
      COMMON/DIMAJA/NRXJC,NCXJC
C********************** TAVOLE ******************************
      DIMENSION NOSUB(*)
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP.
C
      COMMON/LGTV01/LGTEMP,ILEGO,ICOUNT,ICNTMX
      COMMON/LGTV02/LGMODU,LGBLOC
      CHARACTER*8 LGMODU,LGBLOC
      REAL LGTEMP
C********************** TAVOLE ******************************
      COMMON/JACZER/JACTUT
      COMMON/NEQUAZ/NEQMOD
C
C      COSTRUZIONE MATRICE JACOBIANA   FJ,IRJ,ICJ
C      PER IL CALCOLO DEL REGIME INIZIALE
C
      N1=0
      K1=0
      NZTER=0
C
      IFUN=3
      MX5=MMX5
      DO 210 I=1,NBL
      K=ISLB(I)
      IPD=IPDATI(I)
      IXYU=IP(I)
      NOBL1=NOBLC(I,1)
      NOBL2=NOBLC(I,2)
C********************** TAVOLE ******************************
      WRITE(LGMODU,'(A4)')NOSUB(I)
      WRITE(LGBLOC,'(2A4)')NOBL1,NOBL2
C********************** TAVOLE ******************************
C
      JACTUT=0
      NEQMOD=-1
      I1=IP (I)
      I2=IP (I+1)-1
      NY=NUSCI(I)
      NS=NUSTA(I)
      NSY=NS+NY
      DO 1 J=1,NSY
      DO 1 JL=1,I2-I1+1
      AJAC(J,JL)=0.
    1 CONTINUE
C
      CALL MODC1(K,IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,NOBL1,NOBL2)
C
      DO 205 IJ=1,NSY
      IR=K1+IJ
C
C     SE IL MODULO NON HA EQUAZIONI LA SUA MATRICE JACOBIANA E`
C     LA MATRICE UNITA`
C
      IF(NEQMOD.EQ.0) THEN
      	NZTER=NZTER+1
	IC=IR
      	IF(NZTER.GT.NZMAX)GO TO 500
      	IRJ(NZTER)=IR
      	ICJ(NZTER)=IC
      	FJ(NZTER)=1.
      ELSE
C
C      CALCOLO DEL VALORE PIU' PICCOLO # 0 PER OGNI EQUAZIONE
C
      	SN=1.E-10
      IF(JACTUT.GT.0)GO TO 2204
      SN=0.
C
      ICB=0
      DO 203 J=I1,I2
      ICB=ICB+1
      SN=SN+AJAC(IJ,ICB)*AJAC(IJ,ICB)
  203 CONTINUE
      SN=SQRT(SN)/ICB *1.E-6
C
 2204 CONTINUE
C
      ICB=0
      DO 204 J=I1,I2
      ICB=ICB+1
      IF(IPVRS(J).LT.0)GO TO 204
      AA=ABS(AJAC(IJ,ICB))
      IF(SN.GT.AA)GO TO 204
C
C      MEMORIZZAZIONE DI UN TERMINE #0 DELLA RIGA IJ
C
      IC=IPVRS(J)
      NZTER=NZTER+1
      IF(NZTER.GT.NZMAX)GO TO 500
      IRJ(NZTER)=IR
      ICJ(NZTER)=IC
      FJ(NZTER)=AJAC(IJ,ICB)
  204 CONTINUE
      ENDIF
  205 CONTINUE
      K1=K1+NSY
  210 CONTINUE
      CALL JACTO(IRJ,ICJ,NZTER,NEQSIS,NNOTO,IA)
C
C     STAMPA OPZIONALE
C
      CALL SSWTCH(3,LL)
      IF(LL.NE.1) RETURN
      WRITE(90,1000)
 1000 FORMAT(///10X,'STAMPA OPZIONALE SSWTCH-3 '//10X,
     $   'MATRICE JACOBIANA DEL SISTEMA A REGIME'///)
      KO=1
      DO 300 I=1,NEQSIS
      WRITE(90,1001)I
 1001 FORMAT(//10X,'RIGA ',I4)
      K=KO
      L1=K
      DO 250 J=K,NZTER
      IR=IRJ(J)
      IF(IR.NE.I)GO TO 260
      KO=KO+1
  250 CONTINUE
      J=NZTER+1
  260 L2=J-1
  270 WRITE(90,1002)(ICJ(J),FJ(J),J=L1,L2)
 1002 FORMAT(5X,5(I5,1X,E12.5))
  300 CONTINUE
      GO TO 600
  500 WRITE(90,1004)
 1004 FORMAT(//10X,'MEMORIA INSUFFICIENTE PER LO JACOBIANO')
      CALL LGABRT
  600 CONTINUE
      RETURN
      END
