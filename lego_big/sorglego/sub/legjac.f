C*********************************************************************
C       Fortran Source:             legjac.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:26:45 2001 %
C
C**********************************************************************
C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_legjac_f
      CHARACTER*80  RepoID
      COMMON /CM_legjac_f / RepoID
      DATA RepoID/'@(#)1,fsrc,legjac.f,2'/
      END
C**********************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGJAC(NBL,ISLB,IPDATI,IP,XYU,DATI,IPVRS,NUSCI,NUSTA,
     $                   IPCJ,ICBJ,FJ,CDT,NEQSIS,ICJ,RIGA,AJAC,MMX5,
     $                  NOBLC,MX3,RNI,
C***************************** TAVOLE ******************************
     $                  NOSUB)
C***************************** TAVOLE ******************************
      DIMENSION ISLB(*),IPDATI(*),IP(*),XYU(*),DATI(*),IPVRS(*),
     $          NUSCI(*),NUSTA(*),IPCJ(*),ICBJ(*),
     $          FJ(*),ICJ(*),RIGA(*),
     $          NOBLC(MX3,2),RNI(*),AJAC(MMX5,*)
      COMMON/NORM/P0,H0,T0,Q0,RO0,AL0,V0,DP0
      COMMON/DIMAJA/NRXJC,NCXJC
C********************** TAVOLE ******************************
      DIMENSION NOSUB(*)
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP .
C
C
C
      COMMON/LGTV01/LGTEMP,ILEGO,ICOUNT,ICNTMX
      COMMON/LGTV02/LGMODU,LGBLOC
      CHARACTER*8 LGMODU,LGBLOC
      REAL LGTEMP
C********************** TAVOLE ******************************
C
C
C    COSTRUZIONE DELLO JACOBIANO DEL SISTEMA ALG-DIFF A PARTIRE DALLE
C    MATRICI JACOBIANE DEI SINGOLI BLOCCHI UTILIZZANDO LE INFORMAZIONI
C    TOPOLOGICHE DEFINITE DA TOPSIS - LO JACOBIANO EST MEMORIZZ. IN FJ
C
C
C
C
      IFUN=3
      MX5=MMX5
      DO 500 I=1,NBL
      K=ISLB(I)
      IPD=IPDATI(I)
      IXYU=IP(I)
      DO 1 J=1,NRXJC
      DO 1 JL=1,NCXJC
      AJAC(J,JL)=0.
    1 CONTINUE
      IBLOC1=NOBLC(I,1)
      IBLOC2=NOBLC(I,2)
C********************** TAVOLE ******************************
      WRITE(LGMODU,'(A4)')NOSUB(I)
      WRITE(LGBLOC,'(2A4)')IBLOC1,IBLOC2
C********************** TAVOLE ******************************
C
C
      CALL MODC1(K,IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBLOC1,IBLOC2)
C
C
      I1=IP (I)
      I2=IP (I+1)-1
      NXYU=I2-I1+1
C
C     TRASFERIMENTO DEI TERMINI DELLO JACOBINANO DI UN BLOCCO NELLO JAC.
C     DEL SISTEMA - I TERMINI RELATIVI ALLE EQUAZ. DIFF. VENGONO
C     MODIFICATI PER TENER CONTO CHE L'EQUAZ. ALG. RELATIVA E'
C                XN-CDT.F(XN)-T(N-1)=0
C
      NY=NUSCI(I)
      NS=NUSTA(I)
      IF(NS.EQ.0)GO TO 201
      DO 200 J=1,NS
      DO 199 JL=1,NXYU
      AJAC(J,JL)=-CDT*AJAC(J,JL)
  199 CONTINUE
      AJAC(J,J)=1.+AJAC(J,J)
  200 CONTINUE
  201 NSY=NS+NY
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$
      IF(NSY.EQ.0)GO TO 500
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$
      I0=I1-1
      DO 220 J=1,NSY
      K1=IPVRS(I0+J)
      J1=IPCJ(K1)
      J2=IPCJ(K1+1)-1
      DO 210 JK= J1,J2
      ICB=ICBJ(JK)
      FJ(JK)=AJAC(J,ICB)
  210 CONTINUE
  220 CONTINUE
  500 CONTINUE
C
C     STAMPA OPZIONALE
C
      CALL SSWTCH(2,LL)
      IF(LL.NE.1) RETURN
      WRITE(6,1000)
 1000 FORMAT(///10X,'STAMPA OPZIONALE SSWTCH-2 '//10X,'MATRICE JACOBIANA
     $ DEL SISTEMA ALG-DIFF '//)
      DO 300 I=1,NEQSIS
      WRITE(6,1001)I
 1001 FORMAT(//10X,'RIGA ',I4)
      K1=IPCJ(I)
      K2=IPCJ(I+1)-1
      WRITE(6,1002)(ICJ(K),FJ(K),K=K1,K2)
 1002 FORMAT(5X,5(I5,1X,E12.5))
  300 CONTINUE
      RETURN
      END
C            
