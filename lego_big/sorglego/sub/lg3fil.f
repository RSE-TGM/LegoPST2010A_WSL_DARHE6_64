C*********************************************************************
C       Fortran Source:             lg3fil.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Thu Mar 24 17:57:39 2005 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_lg3fil_f
      CHARACTER*80  RepoID
      COMMON /CM_lg3fil_f / RepoID
      DATA RepoID/'@(#)1,fsrc,lg3fil.f,2'/
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

      SUBROUTINE LG3FIL
C
C______ FILES DI LAVORO DI LG3
C
      CHARACTER*32 F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR,N04DAT
C
      COMMON/LG3FLS/F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR,N04DAT
C
C_________ DEFINIZIONE DEI FILES
C
      F14DAT = 'f14.dat'
      F03DAT = 'proc/f03.dat'
      F04DAT = 'proc/f04.dat'
      N04DAT = 'proc/n04.dat'
      F24DAT = 'proc/f24.dat'
      LG3ERR = 'proc/lg3.err'
C
      RETURN
      END
C
