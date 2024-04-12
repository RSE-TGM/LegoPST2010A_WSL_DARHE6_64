C*********************************************************************
C       Fortran Source:             traduci_f22.f
C       Subsystem:              1
C       Description:
C       %created_by:    famgr %
C       %date_created:  Mon Apr 29 09:08:15 1996 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_traduci_f22_f
      CHARACTER*80  RepoID
      COMMON /CM_traduci_f22_f / RepoID
      DATA RepoID/'@(#)1,fsrc,traduci_f22.f,2'/
      END
C**********************************************************************
C******************************************************************************
C modulo traduci_f22.f
C tipo 
C release 1.3
C data 7/21/94
C reserver @(#)traduci_f22.f	1.3
C******************************************************************************
C
C     File modificato da Villa Giovanni Walter, Gruppo Informatica
C     presso ENEL D.C.O. Milano.
C     Modifiche effettuate: Eliminata la keyword SHARED da una OPEN. 
C
      CHARACTER*80 TITOLO
      CHARACTER*80 NOMEFILE
      CHARACTER*8  MODEL 
      CHARACTER*8 NOMI_MISURE(1000)
      CHARACTER*80 SIMBOLI(1000)
      REAL MISURE(1000)
      INTEGER NUMVAR, NUMSIMB, LUN_NOME


      COMMON/VARIABILI/NOMI_MISURE, SIMBOLI, MISURE, TEMPO,
     $                 TITOLO, NUMVAR, NUMSIMB, MODEL,NOMEFILE,
     $                 LUN_NOME

      PRINT *,'PROGRAMMA PER LA SCRITTURA DI UN FILE f22'
      PRINT *,'NEL FORMATO SCRITTO DAL LEGO RUNTIME A PARTIRE'
      PRINT *,'DAL FORMATO DEL LEGO BATCH'
      PRINT *,'Inserire il nome del file alla fortran:'
      NOMEFILE=' '
      read (*,9999) NOMEFILE
9999  format(A)
      OPEN (UNIT=1,FILE=NOMEFILE,STATUS='OLD',FORM='UNFORMATTED')
      READ(1) TITOLO
      READ(1) NUMVAR,(NOMI_MISURE(I),I=1,NUMVAR)
      DO 999 I=1,NUMVAR
         SIMBOLI(I)(1:8)=NOMI_MISURE(I)(1:8)
999   CONTINUE
      PRINT *,'TITOLO DEL TRANSITORIO'
      PRINT *,TITOLO
C
      PRINT *,'NUMERO VARIABILI:'
      PRINT *,NUMVAR
C 
      NUMSIMB = NUMVAR
      MODEL = 'F22.DAT'
C
      LUN_NOME=80
      do I=1,80
         if(NOMEFILE(I:I).eq.'.') then
            LUN_NOME=I-1
            goto 97
         endif
      enddo
97    NOMEFILE=NOMEFILE(1:LUN_NOME)
C
      CALL SCRIVI_TESTA_BIN
C
99    READ (1,END=100) TEMPO,(MISURE(I),I=1,NUMVAR)           
         CALL SCRIVI_CORPO_BIN
      GO TO 99
100   CONTINUE 
C
200   STOP
      END
