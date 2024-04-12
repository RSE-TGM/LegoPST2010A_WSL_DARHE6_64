C******************************************************************************
C modulo legbl1.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)legbl1.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGBL1(NV,IPN,IPM,XLG,XBL)
      DIMENSION IPN(*),IPM(*),XLG(*),XBL(*)
C
C     TRASFERISCE IL CONTENUTO DEL VETTORE XLG (VARIAB.DEL SISTEMA)
C     NEL VETTORE XBL (VARIABILI DI OGNI BLOCCO)
C     USANDO LA MATRICE DI COLLEGAM. INVERSA IPN,IPM
C
      DO 10 I=1,NV
      I1=IPN(I)
      I2=IPN(I+1)-1
      IF(I2.LT.I1)GO TO 10
      DO 5 J=I1,I2
      K=IPM(J)
      XBL(K)=XLG(I)
    5 CONTINUE
   10 CONTINUE
      RETURN
      END
