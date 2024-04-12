C*********************************************************************
C       Fortran Source:             stajac.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:30:02 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_stajac_f
      CHARACTER*80  RepoID
      COMMON /CM_stajac_f / RepoID
      DATA RepoID/'@(#)1,fsrc,stajac.f,2'/
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

      SUBROUTINE STAJAC(NBL,NUSTA,NUSCI,IPVRS,IPCJ,ICBJ,FJ,ICJ,NEQSYS,
     $                  RIGA,IP)
      DIMENSION  NUSTA(*),NUSCI(*),IPVRS(*),IPCJ(*),ICBJ(*),FJ(*),
     $           ICJ(*),RIGA(*),IP(*)
C
C     STAMPA DI CONTROLLO DELLA TOPOLOGIA DEL SYSTEMA ALGEBRICO-DIFF.
C
      DO 50 I=1,NBL
      NS=NUSTA(I)
      NY=NUSCI(I)
      I1=IP (I)
      I2=IP (I+1)-1
      NSY=NS+NY
      I0=I1-1
      DO 30 K=1,NSY
      K1=IPVRS(I0+K)
      J1=IPCJ(K1)
      J2=IPCJ(K1+1)-1
      DO 20 J=J1,J2
      ICB=ICBJ(J)
C
C     FJ(J)=JAC(K,ICB)
      FJ(J)=10000*I+100*K +  ICB
   20 CONTINUE
   30 CONTINUE
   50 CONTINUE
C
C     STAMPA DELLA MATRICE TOPOLOGICA DEL SISTEMA
C
      WRITE(6,1000)
 1000 FORMAT(///10X,'STAMPA OPZIONALE SSWTCH-4 '//10X,
     $   'MATRICE TOPOLOGICA DEL SISTEMA ALGEBRICO-DIFFERENZIALE '///)
      DO 100 I=1,NEQSYS
      WRITE(6,1001)I
 1001 FORMAT(//10X,'RIGA ',I4)
      K1=IPCJ(I)
      K2=IPCJ(I+1)-1
      DO 70 K=1,NEQSYS
      RIGA(K)=0.
   70 CONTINUE
      DO 80 K=K1,K2
      IC=ICJ(K)
      RIGA(IC)=FJ(K)
   80 CONTINUE
      WRITE(6,1002)(RIGA(J),J=1,NEQSYS)
 1002 FORMAT(10(1X,F10.0))
  100 CONTINUE
      RETURN
      END
C            
