C*********************************************************************
C       Fortran Source:             serva1.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:54 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_serva1_f
      CHARACTER*80  RepoID
      COMMON /CM_serva1_f / RepoID
      DATA RepoID/'@(#)1,fsrc,serva1.f,2'/
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

      SUBROUTINE SERVA1(MODO,VET,N,I1,I2,VAVA,IP,IER)
      DIMENSION IP(*)
      CHARACTER*8 VET(N),WAWA,VAVA
C
C     SE MODO=1  IN VET( ) DEVONO TROVARSI NOMI DISTINTI
C     SE MODO=2  IN VET( ) SI DEVE TROVARE VAVA E IN IP( )=VET SI PONE 1
C     SE MODO=3  IN VET( ) NON SI DEVE TROVARE VAVA
      IER=0
      GO TO (10,50,100),MODO
C
   10 DO 20 K=I1,I2-1
        WAWA=VET(K)
        DO 15 J=K+1,I2
          IF (WAWA.EQ.VET(J)) THEN
            IER=IER+1
            GO TO 20
          ENDIF
   15   CONTINUE
   20 CONTINUE
      RETURN
C
   50 KO=0
      DO 60 I=I1,I2
        IF (VAVA.EQ.VET(I)) THEN
          IP(I)=1
          KO=1
        ENDIF
   60 CONTINUE
      IF(KO.EQ.0)IER=1
      RETURN
C
  100 DO 80 I=I1,I2
        IF (VAVA.EQ.VET(I)) IER=IER+1
   80 CONTINUE
      RETURN
      END
C            
