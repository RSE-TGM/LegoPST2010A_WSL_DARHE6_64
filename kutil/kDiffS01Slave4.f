CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C
C  Stampa i valori di stazionario delle variabili di interconnessione
C  delle task dello skedulatore
C
C  INPUT : S01
C  OUTPUT: diffs01.out
C
C  MAX_MODEL  = N. MAX MODELLI
C  MAX_COLL   = N. MAX DI INGRESSI CONNESSI PER CIASCUN MODELLO
C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      PROGRAM DIFFS01

      PARAMETER (MAX_MODEL=60)         
      PARAMETER (MAX_COLL=1500)

      CHARACTER*80 RIGA
      CHARACTER*80 PA
      CHARACTER*50 FILE
      CHARACTER*1 ENDCHAR
      character*10 PIPPO
      
      REAL*4 DT(MAX_MODEL)

C      STRUCTURE/MODEL_ST/
C         CHARACTER*8 NAME
C         INTEGER*4 LUN_NAME
C         CHARACTER*50 PATH
C         INTEGER*4 LUN_PATH
C      END STRUCTURE
C      RECORD/MODEL_ST/MODEL(MAX_MODEL)
	
      
      CHARACTER*8  MODEL_NAME(MAX_MODEL)
      INTEGER*4    MODEL_LUN_NAME(MAX_MODEL)
      CHARACTER*50 MODEL_PATH(MAX_MODEL)
      INTEGER*4    MODEL_LUN_PATH(MAX_MODEL)

C      STRUCTURE/STRIN_ST/
C        CHARACTER*80 STRINGA
C        INTEGER*4 LUN_STRINGA
C      END STRUCTURE
C      RECORD/STRIN_ST/STRIN(10)


      CHARACTER*80 STRIN_STRINGA(10)
      INTEGER*4    STRIN_LUN_STRINGA(10)

C      WRITE(6,1000)
C      READ(6,'(I1)') IRISP
C      IF (IRISP.EQ.9) GO TO 9999
C       
       IRISP=2

      OPEN(UNIT=1,FILE='S01',STATUS='OLD',ERR=901)
C
C lettura nome simulatore
C
      ENDCHAR=' '
      PIPPO='pluto'
      CALL LEGGE_RIGA(RIGA,LUN,ENDCHAR)   !Star
      CALL LEGGE_RIGA(RIGA,LUN,ENDCHAR)   !Nome simulatore
      CALL LEGGE_RIGA(RIGA,LUN,ENDCHAR)   !Star
C
C lettura dei NOMI dei modelli
C
      DO NMOD=1,MAX_MODEL
         CALL LEGGE_RIGA(RIGA,LUN,' ')
         IF(RIGA(1:4).EQ.'****') GO TO 10
         CALL SEPARA_STR(RIGA,LUN,NSTR,STRIN_STRINGA,
     &                   STRIN_LUN_STRINGA)       
         MODEL_NAME(NMOD)=STRIN_STRINGA(1)(1:8)
         MODEL_LUN_NAME(NMOD)=STRIN_LUN_STRINGA(1)
      ENDDO
10    NMOD=NMOD-1
      IF (NMOD.EQ.0) STOP 'ATTENZIONE  Numero modelli = 0 '
C
C lettura delle DIRECTORY dei modelli
C
      DO I=1,NMOD
         CALL LEGGE_RIGA(RIGA,LUN,'/')
         CALL SEPARA_STR(RIGA,LUN,NSTR,STRIN_STRINGA,
     &                   STRIN_LUN_STRINGA)            
         LUN=STRIN_LUN_STRINGA(1)
         MODEL_PATH(I)=STRIN_STRINGA(1)(1:LUN)
         MODEL_LUN_PATH(I)=LUN
      END DO
      CALL LEGGE_RIGA(RIGA,LUN,' ') !Star
C
C lettura delle righe con OS host ...
C
      DO I=1,NMOD
         CALL LEGGE_RIGA(RIGA,LUN,'/')
      END DO
      CALL LEGGE_RIGA(RIGA,LUN,' ') !Star
C
C lettura dei passi di tempo dei singoli modelli
C
      ENDCHAR=' '
      DO I=1,NMOD
         CALL LEGGE_RIGA(RIGA,LUN,' ')
      END DO
      CALL LEGGE_RIGA(RIGA,LUN,' ')  !Star
C
C  apro i files kDiffS01.DB
C
      DO I=1,NMOD
	LP=MODEL_LUN_PATH(I)
	PA=MODEL_PATH(I)(1:LP)//'kDiffS01.DB'
	IUN=I+30
C	 WRITE(6,*)' Opening kDiffS01.DB ', PA
	OPEN(IUN,FILE=PA,STATUS='OLD',ERR=902)
      END DO
C
C  apro il file diffs01.out
C
      OPEN(UNIT=26,FILE='diffs01.out',STATUS='UNKNOWN',
     1   ERR=903)
      WRITE(26,1001)

C
C  apro il file diffs01.err
C
      OPEN(UNIT=27,FILE='diffs01.err',STATUS='UNKNOWN',
     1   ERR=904)
      WRITE(27,1001)
C
C  leggo i valori
C
      DO I=1,NMOD
         WRITE(6,*)' Reading kDiffS01.DB ', MODEL_NAME(I)
         CALL LEGGE_RIGA(RIGA,LUN,' ')  !Nome task
         DO WHILE (.TRUE.)
            CALL LEGGE_RIGA(RIGA,LUN,' ')  
      	    IF(RIGA(1:4).EQ.'****') GOTO 200
C
	    CALL SEPARA_STR(RIGA,LUN,NSTR,STRIN_STRINGA,
     &                      STRIN_LUN_STRINGA)
            CALL CERCA_F(IRISP,MODEL_NAME,MODEL_LUN_NAME,
     &		         MODEL_PATH,MODEL_LUN_PATH,
     &			 I,NSTR,STRIN_STRINGA,
     &                   STRIN_LUN_STRINGA)
     
         ENDDO
200      CONTINUE
         WRITE(26,1001)
      ENDDO

      STOP ' '

901   WRITE(6,*)' ERRORE OPEN FILE S01'
      STOP
902   WRITE(6,*)' ERRORE OPEN FILE ',PA
      STOP
903   WRITE(6,*)' ERRORE OPEN FILE diffs01.out'
      STOP
904   WRITE(6,*)' ERRORE OPEN FILE diffs01.err'
      STOP
     

1000  FORMAT(' -------- VARIABILI CONNESSE IN S01 --------',//,
     +       ' 1 - STAMPA COMPLETA DI TUTTI I VALORI',/,
     +       ' 2 - STAMPA DIFFERENZE > 1%',/,
     +       ' 9 - FINE',//,' SCELTA: ')
1001  FORMAT(1X,79(1H*))

9999  END

C-----------------------------------------------------------------

      SUBROUTINE SEPARA_STR(RIGA,LUN,NSTR,STRIN_STRINGA,
     &                      STRIN_LUN_STRINGA)

      CHARACTER*80 RIGA

C      STRUCTURE/STRIN_ST/
C         CHARACTER*80 STRINGA
C         INTEGER*4 LUN_STRINGA
C      END STRUCTURE
C      RECORD/STRIN_ST/STRIN(10)

      CHARACTER*80 STRIN_STRINGA(10)
      INTEGER*4    STRIN_LUN_STRINGA(10)

      NSTR=0
      INIZIO_STRINGA=1
      I=1
30    IF(I.LE.LUN) THEN
         IF(RIGA(I:I).EQ.' ') THEN
            NSTR=NSTR+1
            STRIN_STRINGA(NSTR)=RIGA(INIZIO_STRINGA:I-1)        
            STRIN_LUN_STRINGA(NSTR)=I-INIZIO_STRINGA
            IF(NSTR.EQ.10) GO TO 20
10          I=I+1
            IF(I.GT.LUN) GO TO 20
            IF(RIGA(I:I).EQ.' ') GO TO 10
            INIZIO_STRINGA=I
            IF(NSTR.EQ.3)RETURN
         ENDIF
         I=I+1
         GO TO 30
      ELSE
         NSTR=NSTR+1
         STRIN_STRINGA(NSTR)=RIGA(INIZIO_STRINGA:I-1)        
         STRIN_LUN_STRINGA(NSTR)=I-INIZIO_STRINGA
      ENDIF
20    RETURN
      END

C-----------------------------------------------------------------

      SUBROUTINE LEGGE_RIGA(RIGA,LUN,ENDCHAR)

      CHARACTER*80 RIGA
      CHARACTER*1 ENDCHAR

      READ(1,'(A)',END=100) RIGA
      DO I=80,1,-1
         IF(ENDCHAR.EQ.' '.AND.RIGA(I:I).NE.' ') GO TO 50
         IF(ENDCHAR.NE.' '.AND.RIGA(I:I).EQ.ENDCHAR) GO TO 50
      ENDDO
50    LUN=I
      RETURN
100   STOP 'ATTENZIONE end_of_file inatteso del file S01 '
      END

C-----------------------------------------------------------------

      SUBROUTINE CERCA_F(IRISP,
     &                   MODEL_NAME,MODEL_LUN_NAME,
     &		         MODEL_PATH,MODEL_LUN_PATH,
     &                   II,NSTR,STRIN_STRINGA,
     &                   STRIN_LUN_STRINGA)

C   IRISP=1  Modalita di stampa completa
C   IRISP=2  Modalita di stampa solo se le variabili sono diverse

      PARAMETER (MAX_MODEL=60)         
      PARAMETER (MAX_COLL=1500)

C      STRUCTURE/STRIN_ST/
C         CHARACTER*80 STRINGA
C         INTEGER*4 LUN_STRINGA
C      END STRUCTURE
C      RECORD/STRIN_ST/STRIN(10)


      CHARACTER*80 STRIN_STRINGA(10)
      INTEGER*4    STRIN_LUN_STRINGA(10)



C      STRUCTURE/MODEL_ST/
C         CHARACTER*8 NAME
C         INTEGER*4 LUN_NAME
C         CHARACTER*50 PATH
C         INTEGER*4 LUN_PATH
C      END STRUCTURE
C      RECORD/MODEL_ST/MODEL(MAX_MODEL)


      CHARACTER*8  MODEL_NAME(MAX_MODEL)
      INTEGER*4    MODEL_LUN_NAME(MAX_MODEL)
      CHARACTER*50 MODEL_PATH(MAX_MODEL)
      INTEGER*4    MODEL_LUN_PATH(MAX_MODEL)



      CHARACTER*80 S1,S2,S3
      CHARACTER*132 RIGA1,RIGA2

      LP=MODEL_LUN_PATH(II)
      LNM=MODEL_LUN_NAME(II)
      S1=STRIN_STRINGA(1)
      LS1=STRIN_LUN_STRINGA(1)
      S2=STRIN_STRINGA(2)
      LS2=STRIN_LUN_STRINGA(2)
      S3=STRIN_STRINGA(3)
      LS3=STRIN_LUN_STRINGA(3)
      DO I=1,MAX_MODEL
         IF(S2(1:LS2).EQ.MODEL_NAME(I)(1:MODEL_LUN_NAME(I)))GO TO 95
      ENDDO
95    LP=MODEL_LUN_PATH(I)
      IL=MODEL_LUN_NAME(I)
      LUNU1=II+30
      LUNU2=I+30
      
      REWIND(LUNU1)
100   READ(LUNU1,FMT='(A)',END=500) RIGA1
      IF(RIGA1(1:8).NE.S1) GOTO 100
      REWIND(LUNU2)
200   READ(LUNU2,FMT='(A)',END=600) RIGA2
      IF(RIGA2(1:8).NE.S3) GOTO 200

      IF(IRISP.EQ.2) THEN
         READ(RIGA1(17:26),'(F10.0)') VAL1
         READ(RIGA2(17:26),'(F10.0)') VAL2
         IF (ABS(VAL1).LE.1.E-5) VAL1=0.
          IF (ABS(VAL2).LE.1.E-5) VAL2=0.
          IF ((ABS(VAL1).LE.1.E-2).AND.(ABS(VAL2).LE.1.E-2)) RETURN
          IF (ABS(VAL1-VAL2).LE.(ABS(VAL1)*0.02)) RETURN
       write(*,*)'val1=',val1,' val2=',val2
      ENDIF
      WRITE(26,3001) MODEL_NAME(II)(1:LNM), RIGA1(1:9), VAL1,
     + RIGA1(27:100)
      WRITE(26,3001) S2(1:LS2), RIGA2(1:9), VAL2,
     + RIGA2(27:100)
      WRITE(26,4000)
3000  FORMAT(1X,A8,5X,A)
3001  FORMAT(1X,A8,2X,A,1X,E11.5,1X,A)
4000  FORMAT(1X,'---------------------------------------------------')
      RETURN
500   WRITE(6,777) S1(1:8),MODEL_NAME(II)(1:MODEL_LUN_NAME(II))
      WRITE(27,777) S1(1:8),MODEL_NAME(II)(1:MODEL_LUN_NAME(II))
777   FORMAT(' THE VARIABILE ',A,' DOES NOT EXIST ...... ',A)
      RETURN
600   WRITE(6,778) S3(1:8),S2(1:8)
      WRITE(27,778) S3(1:8),S2(1:8)
778   FORMAT(' THE VARIABILE ',A,' DOES NOT EXIST IN MODEL ',A)
      RETURN
      END
