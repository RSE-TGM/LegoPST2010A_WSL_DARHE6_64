C*********************************************************************
C       Fortran Source:             main_svinri2.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:17:29 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_main_svinri2_f
      CHARACTER*80  RepoID
      COMMON /CM_main_svinri2_f / RepoID
      DATA RepoID/'@(#)1,fsrc,main_svinri2.f,2'/
      END
C**********************************************************************
       PROGRAM MODDATI
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
       include 'lg_parameter.fh'
C
       PARAMETER (MAXMOD=N001)
C
C      FILE '05'  - ELENCO DEI MODULI PRESENTI NELLA LIBRERIA LEGO
C      FILE '02'  - SOTTOPROGRAMMA GENERATO
C
       CHARACTER*4 MODU
       CHARACTER*4 MODUL(MAXMOD)
C
C
C______ DEFINIZIONE DEI FILES DI LAVORO DI CREAMODI
C
       CHARACTER*32 LISTA_MODULI
       CHARACTER*32 MDAT_FOR
       CHARACTER*32 MDAT_ERR
C
       LISTA_MODULI = 'lista_schemi.dat'
       MDAT_FOR     = 'modidat.f'
       MDAT_ERR     = 'modidat.err'
C
       OPEN(UNIT=05,FILE=LISTA_MODULI,STATUS='OLD')
       OPEN(UNIT=2,FILE=MDAT_FOR,STATUS='UNKNOWN')
CC     1     RECORDTYPE='STREAM_LF')
C     1     CARRIAGECONTROL='LIST')
C
       IOUT=2
C
C
C
C
c      READ(5,1002)
c      READ(5,1002)
C
C
      NST=0
    1 READ(5,1002,END=20)MODU
 1002 FORMAT(A4)
      NST=NST+1
      IF(NST.EQ.1)GO TO 6
      NS1=NST-1
      DO 5 J=1,NS1
      IF(MODU.EQ.MODUL(J))GO TO 10
    5 CONTINUE
    6 MODUL(NST)=MODU
      IF(NST.EQ.MAXMOD) GO TO 99
      GO TO 1
C   10 WRITE(6,1020)MODU
C 1020 FORMAT(//10X,'IL MODULO ',A4,' COMPARE GIA'' NELLA LISTA '/)
  10  NST=NST-1
      GO TO1
C
   20 CONTINUE
C
C
C     CREAZIONE SUBROUTINE MODDATI
C
C
      REWIND IOUT
C      WRITE(IOUT,'(A)')'      SUBROUTINE MODDATI(KI,IFO,IOB,DEBL)'
      WRITE(IOUT,666)
C 666  FORMAT(6X,'SUBROUTINE MODIDAT(KI,IFUN,IBLOC1,IBLOC2,VAR,NX5,
C     &I1,I2,XYU,'/5X,'&',19X,'DATI,K1,K2,IER,CNXYU,TOL)')
 666  FORMAT(6X,'SUBROUTINE MODIDAT(KI,IFUN,IBLOC1,IBLOC2,VAR,NX5,')
      WRITE(IOUT,667)
 667  FORMAT(5X,'&',19X,'I1,I2,XYU,DATI,K1,K2,IER,CNXYU,TOL)')
      WRITE(IOUT,'(A)')'      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)'
      WRITE(IOUT,'(A)')'      INTEGER VAR (NX5,2)'
      WRITE(IOUT,'(A)')'      MX1=NX5'
      WRITE(IOUT,'(A)')'C****'
      KST=0
      IVIA=2 
      KEN=500
      CALL I2GOTO(NST,MODUL,IVIA,KST,KEN,IOUT)
      WRITE(IOUT,'(A)')'C****'
      WRITE(IOUT,'(A)')'  500 RETURN'
      WRITE(IOUT,'(A)')'      END'
C
C
C____________FINE
C
C      WRITE(6,1010)
C 1010 FORMAT(//10X,'CREATA LA SUBROUTINE MODDATI IN MAIN_SVINRI2.FOR')
      STOP ' '
   99 OPEN(UNIT=6,FILE=MDAT_ERR,STATUS='NEW')
C     &      RECORDTYPE='VARIABLE',CARRIAGECONTROL='LIST')
      WRITE(6,1000) MAXMOD
 1000 FORMAT(///10X,'PROCEDURA PER LA CREAZIONE ',
     &/10X,'DELLA SUBROUTINE MODI3 ',
     &/10X,'NECESSARIE ALLA CREAZIONE DELL'' ESEGUIBILE LG1',
     &//10X,'********ERRORE********',
     &/10X,'IL NUMERO DEI MODULI CHE COMPARE NEL FILE :',
     &/10X,'[USER.LEGOCAD.LIBUT]LISTA_MODULI.DAT',
     &/10X,'NON DEVE ESSERE SUPERIORE A ', I4,
     &//10X,'RIVEDI IL CONTENUTO DI TALE FILE')
      STOP ' '
      END
C
