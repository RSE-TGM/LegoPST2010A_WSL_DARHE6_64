C*********************************************************************
C       Fortran Source:             main_lg5sk.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Mar  8 18:23:20 2005 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_main_lg5sk_f
      CHARACTER*80  RepoID
      COMMON /CM_main_lg5sk_f / RepoID
      DATA RepoID/'@(#)1,fsrc,main_lg5sk.f,2'/
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

      PROGRAM LG5SK
      CHARACTER*20 FILE06
      COMMON/LGTV01/LGTEMPO,ILEGO,ICOUNT,ICOUNTMX
      FILE06='lg5.out'
      ICOUNTMX=1.E+06
      OPEN (6,FILE=FILE06,STATUS='UNKNOWN')
      WRITE (6,*) 'FILE06= ', FILE06
      CLOSE(6)
      OPEN (6,FILE=FILE06,STATUS='UNKNOWN')
C
C --- nota: la  UNIT 6  possedeva l'attributo  SHARED
C
      WRITE (6,*) 'FILE06= ', FILE06
      CALL FLUSH(6)
      CALL LG5SIM
      WRITE (6,*) 'LG5SK - FINE REGOLARE DEL PROGRAMMA'
      CLOSE (6)
      CALL LGSTOP
      STOP
      END
C
C
C
      BLOCK DATA MA2801
      LOGICAL ABORT1,ABORT2,ABORT3
      COMMON /MA30E/ LP,ABORT1,ABORT2,ABORT3
      COMMON /MA30G/ EPS,RMIN
      DATA EPS/1.0E-4/
      DATA LP/6/
      DATA ABORT1/.FALSE./,ABORT2/.FALSE./,ABORT3/.FALSE./
      END
C
C
C
      BLOCK DATA MA2802
      COMMON/MC19B /LP,IFAIL
      DATA LP/6/
      END
C
C
C
      BLOCK DATA MA2803
      LOGICAL LBLOCK,GROW,ABORT1,ABORT2
      COMMON /MA28E/ LP,MP,LBLOCK,GROW
      COMMON /MA28F/ EPS,RMIN,RESID,IRNCP,ICNCP,MINIRN,MINICN,
     $               IRANK,ABORT1,ABORT2
      DATA EPS/1.0E-4/
      DATA LP/6/,MP/6/
      DATA LBLOCK/.TRUE./,GROW/.TRUE./
      DATA ABORT1/.FALSE./,ABORT2/.FALSE./
      END
C
C
C
      BLOCK DATA MA2804
      LOGICAL ABORT
      COMMON /MC23B/ LP,NUMNZ,NUM,LARGE,ABORT
      DATA LP/6/,ABORT/.FALSE./
      END
C            
