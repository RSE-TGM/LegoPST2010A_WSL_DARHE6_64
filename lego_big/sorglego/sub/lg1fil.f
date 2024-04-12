C*********************************************************************
C       Fortran Source:             lg1fil.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:27:13 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_lg1fil_f
      CHARACTER*80  RepoID
      COMMON /CM_lg1fil_f / RepoID
      DATA RepoID/'@(#)1,fsrc,lg1fil.f,2'/
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
      LMODUL = '../libut/lista_moduli.dat'
      LSCHEM = '../libut_reg/lista_schemi.dat'
      F01DAT = 'f01.dat'
      F02DAT = 'proc/f02.dat'
      LTMFOR = 'proc/ltm.f'
      CLTMDA = 'proc/crealtm.dat'
      LG1ERR = 'proc/lg1.err'
C
       RETURN
       END
C
