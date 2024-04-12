C******************************************************************************
C modulo passot.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)passot.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE PASSOT(NP,TSTEP,TEMPO,IGRAD,KOUT)
C
C     DEFINISCE  KOUT = 0   NO-OUTPUT
C                     = 1   OUTPUT
      KOUT=0
      IF(TEMPO.EQ.0.)GO TO 10
      IF(IGRAD.EQ.1)GO TO 10
C
      N=TEMPO /TSTEP
      TT= N*TSTEP
      TT1=(N+1)*TSTEP
C
      DT=ABS(TEMPO-TT)
      DT1=ABS(TEMPO-TT1)
      IF(DT1.LT.DT)N=N+1
      IF(MOD(N,NP).NE.0)GO TO 20
      IF(N.EQ.0)GO TO 20
   10 KOUT=1
   20 RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_passot
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)passot.f	2.1\t7/10/95'/
      END
