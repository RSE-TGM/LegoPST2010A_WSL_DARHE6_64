C*********************************************************************
C       Fortran Source:             creamodi.f
C       Subsystem:              1
C       Description:
C       %created_by:    famgr %
C       %date_created:  Tue Apr 30 10:08:03 1996 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_creamodi_f
      CHARACTER*80  RepoID
      COMMON /CM_creamodi_f / RepoID
      DATA RepoID/'@(#)1,fsrc,creamodi.f,3'/
      END

        PROGRAM CREAMODI
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
C       CREAZIONE DELLA SUBROUTINE  MODI3 IN MODI.FOR
C       PER IL COLLEGAMENTO  LG1-MODULI
C     
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
C
C      FILE '05'  - ELENCO DEI MODULI PRESENTI NELLA LIBRERIA LEGO
C      FILE '02'  - SOTTOPROGRAMMA GENERATO
C
C      MASSIMO ATTUALE 300 MODULI
C
      PARAMETER (MAXMOD=300)
      DIMENSION MODUL(300)
C Guag2024      DATA IBLK/' '/
C
C$$$$$     !!!!!!! INIZIO ISTRUZIONI PER SCCS !!!!!!!
       CHARACTER*80 SccsID
       DATA SccsID/'@(#)creamodi.f	1.6\t 1.6\t 3/30/95'/
C$$$$$     !!!!!!! FINE ISTRUZIONI PER SCCS !!!!!!!
C
C______ DEFINIZIONE DEI FILES DI LAVORO DI CREAMODI
C
      CHARACTER*32 LISTA_MODULI
      CHARACTER*32 MODI_FOR
      CHARACTER*32 MODI_ERR
C
       LISTA_MODULI = 'lista_moduli.dat'
       MODI_FOR     = 'modi.for'
       MODI_ERR     = 'modi.err'
C
      OPEN(UNIT=05,FILE=LISTA_MODULI,STATUS='OLD')
      OPEN(UNIT=2,FILE=MODI_FOR,STATUS='NEW')
C     1     RECORDTYPE='STREAM_LF')
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
C     CREAZIONE SUBROUTINE MODI3
C
C
      REWIND IOUT
      WRITE(IOUT,'(A)')'      SUBROUTINE MODI3(KI,IFO,IOB,DEBL)'
      WRITE(IOUT,'(A)')'      CHARACTER*80 DEBL'
      WRITE(IOUT,'(A)')'      CHARACTER*4 IOB'
      WRITE(IOUT,'(A)')'C****'
      KST=0
      IVIA= 4
      KEN=500
      CALL GOTOCA(NST,MODUL,IVIA,KST,KEN,IOUT)
      WRITE(IOUT,'(A)')'C****'
      WRITE(IOUT,'(A)')'  500 CLOSE(IFO)'
      WRITE(IOUT,'(A)')'      RETURN'
      WRITE(IOUT,'(A)')'      END'
C
C
C____________FINE
C
C      WRITE(6,1010)
C 1010 FORMAT(//10X,'CREATA LA SUBROUTINE MODI3 IN MODI.FOR')
      STOP ' '
   99 OPEN(UNIT=6,FILE=MODI_ERR,STATUS='NEW')
C     &      RECORDTYPE='VARIABLE',CARRIAGECONTROL='LIST')
      WRITE(6,1000)
 1000 FORMAT(///10X,'PROCEDURA PER LA CREAZIONE ',
     &/10X,'DELLA SUBROUTINE MODI3 ',
     &/10X,'NECESSARIE ALLA CREAZIONE DELL'' ESEGUIBILE LG1',
     &//10X,'********ERRORE********',
     &/10X,'IL NUMERO DEI MODULI CHE COMPARE NEL FILE :',
     &/10X,'[USER.LEGOCAD.LIBUT]LISTA_MODULI.DAT',
     &/10X,'NON DEVE ESSERE SUPERIORE A 300',
     &//10X,'RIVEDI IL CONTENUTO DI TALE FILE')
      STOP ' '
      END
     
