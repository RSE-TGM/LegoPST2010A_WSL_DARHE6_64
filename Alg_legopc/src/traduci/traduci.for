      PROGRAM TRADUCI
C
C     Translates a f22.dat produced by lego into a f22 C-Tidea format for grafics
C
      CHARACTER*80 TITOLO
      CHARACTER*80 NOMEFILE
      CHARACTER*8  MODEL, NMMODU
      CHARACTER*9  SIMBOLI(1000)
      CHARACTER*71 LABELS(1000)
      CHARACTER*80 GIASEL(1000)
      REAL MISURE(1000)
      INTEGER NUMVAR, NUMSIMB, LUN_NOME, NSEL


      COMMON/VARIABILI/SIMBOLI, MISURE, TEMPO,
     $                 TITOLO, NUMVAR, NUMSIMB, MODEL,NOMEFILE,
     $                 LUN_NOME, LABELS

      PRINT *,'PROGRAMMA PER LA SCRITTURA DI UN FILE f22'
      PRINT *,'NEL FORMATO SCRITTO DAL LEGO RUNTIME A PARTIRE'
      PRINT *,'DAL FORMATO DEL LEGO BATCH'
      PRINT *,'Inserire il nome del file alla fortran:'
      NOMEFILE=' '
      read (*,10) NOMEFILE
10    format(A)
      OPEN (UNIT=1,FILE=NOMEFILE,STATUS='OLD',FORM='UNFORMATTED')
      READ(1) TITOLO
      READ(1) NUMVAR,(SIMBOLI(I)(1:8),I=1,NUMVAR),NMMODU,NSEL,
     $        (GIASEL(J),J=1,NSEL)
      DO I=1,NUMVAR
         DO J=1,NSEL
            IF (GIASEL(J)(1:8).EQ.SIMBOLI(I)(1:8)) THEN
               LABELS(I)=GIASEL(J)(11:80)
               GOTO 20
            ENDIF
         ENDDO   
20       CONTINUE
      ENDDO
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
      CALL scrivi_testa_bin_
C
99    READ (1,END=100) TEMPO,(MISURE(I),I=1,NUMVAR)           
         CALL scrivi_corpo_bin_
      GO TO 99
100   CONTINUE 
C
200   STOP
      END
