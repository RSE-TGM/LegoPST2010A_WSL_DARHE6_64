C******************************************************************************
C modulo prepo.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)prepo.f	2.1
C******************************************************************************
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
      WRITE(6,*)FILE22
      IF(IREGIM.EQ.2)GO TO 101
C
      OPEN(UNIT=22,FILE=FILE22,STATUS='UNKNOWN',FORM='UNFORMATTED')
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
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_prepo
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)prepo.f	2.1\t7/10/95'/
      END
