C******************************************************************************
C modulo lg1fil.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)lg1fil.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LG1FIL
C
C______ FILES DI LAVORO DI LG1
C
      CHARACTER*32 LMODUL,F01DAT,F02DAT,LTMFOR,CLTMDA,LG1ERR,LSCHEM
C
      COMMON/LG1FLS/LMODUL,F01DAT,F02DAT,LTMFOR,CLTMDA,LG1ERR,LSCHEM
C
C_________ DEFINIZIONE DEI FILES
C
      LMODUL = '..\..\libut\l_moduli.dat'
      F01DAT = 'f01.dat'
      F02DAT = 'proc\f02.dat'
      LTMFOR = 'proc\ltm.f'
      CLTMDA = 'proc\crealtm.dat'
      LG1ERR = 'proc\lg1.err'
C
       RETURN
       END
C
C Procedura contenete la variabile per l'identificazione della versione
C
      SUBROUTINE SCCS_lg1fil
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)lg1fil.f	2.1\t7/10/95'/
      END
