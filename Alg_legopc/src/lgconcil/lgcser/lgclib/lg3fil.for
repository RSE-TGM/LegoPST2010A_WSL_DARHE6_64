C******************************************************************************
C modulo lg3fil.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)lg3fil.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LG3FIL
C
C______ FILES DI LAVORO DI LG3
C
      CHARACTER*32 F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR
C
      COMMON/LG3FLS/F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR
C
C_________ DEFINIZIONE DEI FILES
C
      F14DAT = 'f14.dat'
      F03DAT = 'proc/f03.dat'
      F04DAT = 'proc/f04.dat'
      F24DAT = 'proc/f24.dat'
      LG3ERR = 'proc/lg3.err'
C
      RETURN
      END
