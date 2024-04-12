C*********************************************************************
C       Fortran Source:             main_svinforms.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:17:11 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_main_svinforms_f
      CHARACTER*80  RepoID
      COMMON /CM_main_svinforms_f / RepoID
      DATA RepoID/'@(#)1,fsrc,main_svinforms.f,2'/
      END
C**********************************************************************
       PROGRAM MODFORMS
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
       include 'lg_parameter.fh'
C
       PARAMETER (MAXMOD=N001)
C
C      FILE '05'  - ELENCO DEI MODULI PRESENTI NELLA LIBRERIA LEGO
C      FILE '02'  - SOTTOPROGRAMMA GENERATO

       CHARACTER*4 MODU
       CHARACTER*4 MODUL(MAXMOD)


C______ DEFINIZIONE DEI FILES DI LAVORO DI MODFORMS
C
       CHARACTER*32 LISTA_MODULI
       CHARACTER*32 MVAR_FORM
       CHARACTER*32 MDAT_FORM
       CHARACTER*32 MDAT_ERR

       LISTA_MODULI = 'lista_moduli_reg.dat'
       MVAR_FORM     = 'modrvar.f'
       MDAT_FORM     = 'modrdat.f'
       MDAT_ERR      = 'svinforms.err'

       OPEN(UNIT=05,FILE=LISTA_MODULI,STATUS='OLD')
       OPEN(UNIT=2,FILE=MVAR_FORM,STATUS='UNKNOWN')
       OPEN(UNIT=3,FILE=MDAT_FORM,STATUS='UNKNOWN')

       IOUT=2




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
   10 WRITE(6,1020)MODU
 1020 FORMAT(//10X,'IL MODULO ',A4,' COMPARE GIA'' NELLA LISTA '/)
  101  NST=NST-1
      GO TO1

   20 CONTINUE




C     CREAZIONE SUBROUTINE MODRVAR
C
C
      REWIND IOUT
      WRITE(IOUT,666)
 666  FORMAT(6X,'SUBROUTINE MODRVAR(KI,IOB,DEBL)')
      WRITE(IOUT,'(A)')'      CHARACTER*80 DEBL'
      WRITE(IOUT,'(A)')'      CHARACTER*4 IOB'
      WRITE(IOUT,667)
 667  FORMAT(6X,'OPEN(UNIT=55,FILE=''APPOVAR'',STATUS=''UNKNOWN'')')
      WRITE(IOUT,'(A)')'      IFO=55'
      WRITE(IOUT,'(A)')'C****'
      KST=0
      IVIA=4 
      KEN=500
      CALL I2GOTO(NST,MODUL,IVIA,KST,KEN,IOUT)
      WRITE(IOUT,'(A)')'C****'
      WRITE(IOUT,668)
 668  FORMAT('  500 CLOSE(IFO)',/6X,'RETURN')
      WRITE(IOUT,'(A)')'      END'




C     CREAZIONE SUBROUTINE MODRDAT
C
C
      IOUT=3
      REWIND IOUT
      WRITE(IOUT,766)
 766  FORMAT(6X,'SUBROUTINE MODRDAT(KI,IFUN,IBLOC1,IBLOC2,'
     &,/5X,'&',19X,'DATI,ID,IER)')
      WRITE(IOUT,'(A)')'      DIMENSION DATI(1)'
      WRITE(IOUT,'(A)')'      CHARACTER*6 IBLOC1'
      WRITE(IOUT,767)
 767  FORMAT(6X,'OPEN(UNIT=14,FILE=''APPODATI'',STATUS=''UNKNOWN'')')
      WRITE(IOUT,'(A)')'C****'
      KST=0
      IVIA=5 
      KEN=500
      CALL I2GOTO(NST,MODUL,IVIA,KST,KEN,IOUT)
      WRITE(IOUT,'(A)')'C****'
      WRITE(IOUT,768)
 768  FORMAT('  500 CLOSE(14)',/6X,'RETURN')
      WRITE(IOUT,'(A)')'      END'

C____________FINE




      WRITE(6,1010)
 1010 FORMAT(/,'CREATE LE SUBROUTINE MODRVAR MODRDAT',
     &' (main_svinforms.f) ')
      STOP ' '
   99 OPEN(UNIT=6,FILE=MDAT_ERR,STATUS='NEW')
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
C
