C******************************************************************************
C modulo serva2.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)serva2.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE SERVA2(MODO,VETI,N,I1,I2,VETK,M,K1,K2,IPO,IER)
      DIMENSION IPO(*)
      CHARACTER*8 VETI(N),VETK(M),VAVA
C
C     SE MODO=1  LE PAROLE DI VETI( ) SONO DISTINTE DA QUELLE DI VETK( )
C     SE MODO=2  LE PAROLE DI VETI( ) SONO COMPRESE IN VETK ( ) E IN
C                IPO=VETK SI PONE 1
C
      IER=0
      GO TO (10,100),MODO
   10 MD=3
      DO 20 I=I1,I2
      VAVA=VETI(I)
      CALL SERVA1(MD,VETK,M,K1,K2,VAVA,IP,IERR)
      IF(IERR.EQ.0)GO TO 20
      WRITE(6,1000)VAVA,IERR
 1000 FORMAT(/10X,'ER- LA VARIABILE ',A8,' COMPARE ',I2,' VOLTE'//)
      IER=1
   20 CONTINUE
      GO TO 200
C
  100 MD=2
      DO 50 I=I1,I2
      VAVA=VETI(I)
      CALL SERVA1(MD,VETK,M,K1,K2,VAVA,IPO,IERR)
      IF(IERR.EQ.0)GO TO 50
      WRITE(6,1001)VAVA
 1001 FORMAT(/10X,'ER- LA VARIABILE ',A8,' NON E'' COMPRESA'//)
      IER=1
   50 CONTINUE
  200 RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_serva2
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)serva2.f	2.1\t7/10/95'/
      END
