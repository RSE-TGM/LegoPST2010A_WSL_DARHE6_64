C*********************************************************************
C       Fortran Source:             prepo.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:39 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_prepo_f
      CHARACTER*80  RepoID
      COMMON /CM_prepo_f / RepoID
      DATA RepoID/'@(#)1,fsrc,prepo.f,2'/
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

      SUBROUTINE PREPO (NRE,NGR)
C
C apre il file 22 per registrazioni grandezze
C definisce shared il file 22
C
C NRE = numero di registrazioni ( passi di tempo )
C NGR = numero di grandezze
C
      CHARACTER*8 NOMI
      COMMON/RSTRT1/TREST,IREGIM
      COMMON/FILOTP/FILE21,FILE22
      CHARACTER*50 FILE21,FILE22
      REAL VET,TIM,TOM
      DATA NOMI/'=>RIEN<='/
      TIM = -1.
C
C
      IF(IREGIM.EQ.2)GO TO 101
C
      OPEN(UNIT=22,FILE=FILE22,STATUS='NEW',FORM='UNFORMATTED')
      WRITE(22)(VET,J=1,20)
      WRITE (22) NGR,(NOMI,J=1,NGR)
   90 CONTINUE
      WRITE (22) TIM,(VET,L=1,NGR)
      CLOSE (UNIT=22)
C
      OPEN (UNIT=22,FILE=FILE22,STATUS='OLD',FORM='UNFORMATTED')
C
C   Nota: nella precedente OPEN era presente l'attributo "SHARED"
C
      READ (22) (VET,J=1,20)
      RETURN
C
  101 CONTINUE
      OPEN (UNIT=22,FILE=FILE22,STATUS='OLD',FORM='UNFORMATTED')
      IER=0
      CALL FILPOS(22,TREST,NGR,IER)
      IF (IER.NE.0) CALL LGABRT
      TOM=999999.
      WRITE (22) TOM,(VET,L=1,NGR)
      GO TO 90
      END
C            
