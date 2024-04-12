C******************************************************************************
C modulo lgabrt.pf
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)lgabrt.pf	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LGABRT

C
C______ SCRIVE UN FLAG DI ERRORE
C       SUL FILE "PROC/LGERR.OUT"
C       (IL FLAG PUO` ESSERE INTERCETTATO DALLA PROCEDURA
C        CHE HA LANCIATO IL PROGRAMMA LEGO)
C
      CHARACTER*20 FILE13
      FILE13='proc/lgerr.out'
C
      OPEN(UNIT=13,FILE=FILE13,STATUS='UNKNOWN',FORM='FORMATTED')
C
      IERR=1
      WRITE(13,*)IERR
      CLOSE (13)
      STOP
      END
