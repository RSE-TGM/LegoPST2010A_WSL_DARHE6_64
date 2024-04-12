C*********************************************************************
C       Fortran Source:             initsm.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Wed Jun  7 12:32:15 2006 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_initsm_f
      CHARACTER*80  RepoID
      COMMON /CM_initsm_f / RepoID
      DATA RepoID/'@(#)1,fsrc,initsm.f,2'/
      END
C**********************************************************************
        SUBROUTINE INITSM
C
C   VERSIONE MODIFICATA PER COLLEGAMENTO A
C   SHARED MEMORY
C
      COMMON/CONT/PD,SD
      PD=0.
      SD=-0.2
C
        CALL ISM01(IRET)
C
        CALL CONLIS
C
        RETURN
        END
