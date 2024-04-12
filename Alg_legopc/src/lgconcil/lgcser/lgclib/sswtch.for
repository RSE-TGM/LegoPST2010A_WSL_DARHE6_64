C******************************************************************************
C modulo sswtch.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)sswtch.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE SSWTCH(K,I)
      DIMENSION KSW(6)
C
      CHARACTER*6 STAMPE
      INTEGER SMORZ
      REAL TOLLER, PESO0, TOLGS  
C
      COMMON /SSTCH/ KSW
      COMMON/SETTINGS/TOLLER,SMORZ,PESO0,TOLGS,STAMPE
      I=0
      IF(K.EQ.10)GO TO 7
      IF(K.NE.9)GO TO 10
      DO 5 J=1,6
      KSW(J)=0
    5 CONTINUE
      K=10
      RETURN
    7 CONTINUE
      READ(STAMPE,1001)(KSW(J),J=1,6)
 1001 FORMAT(6I1)
      WRITE(90,1003) (KSW(J),J=1,6)
 1003 FORMAT(/10X,'STAMPE INTERMEDIE DI CONTROLLO SCELTE = ',6I1)
      RETURN
C
   10 IF(K.GT.6.OR.K.LT.1)GO TO 15
      DO 12 J=1,6
      IF(K.EQ.KSW(J))GO TO 13
   12 CONTINUE
      GO TO 20
   13 I=1
      GO TO 20
   15 WRITE(90,1002)
 1002 FORMAT(///10X,'NUMERO S.SWTCH NON COMPRESO FRA 1 E 6 '/10X,
     $   'LO CONSIDERO ON  (ERRORE LEGO)'//)
      I=1
   20 RETURN
      END
