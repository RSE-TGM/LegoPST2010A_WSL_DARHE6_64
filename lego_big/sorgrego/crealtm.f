C******************************************************************************
C  modulo crealtm.f
C  tipo 
C  release 1.3
C  data 11/13/95
C  reserved @(#)crealtm.f	1.3
C******************************************************************************

      PROGRAM   CREALTM
C
      PARAMETER (NBL01=2000)
C
      DIMENSION NOSLN(NBL01)
      CHARACTER*(80) LISLTM(NBL01)
      CHARACTER*32 FILE_F01
      CHARACTER*32 FILE_LTMFOR
      CHARACTER*32 FILE_LTMDAT
      CHARACTER*80  LINE
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
C       CREAZIONE DELLE SUBROUTINES  MODI2,MODC1 E MODC2 IN LTM.FOR
C       PER TRATTARE GLI SCHEMI DI REGOLAZIONE
C       CREAZIONE ELENCO SCHEMI UTILIZZATI NEL MODELLO
C       (CREALTM.DAT)
C
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
      FILE_F01   ='f01.dat'
      FILE_LTMFOR='ltm.f'
      FILE_LTMDAT='crealtm.dat'
C
      IOUT1=35  ! file LTM.FOR
      IOUT2=34  ! file CREALTM.DAT
C
      OPEN(UNIT=01,FILE=FILE_F01,STATUS='OLD')
      OPEN(UNIT=35,FILE=FILE_LTMFOR,FORM='FORMATTED')
      OPEN(UNIT=34,FILE=FILE_LTMDAT,FORM='FORMATTED')
C
C________________SELEZIONE DELL'ELENCO
C                DEI MODULI USATI NEL MODELLO LEGGENDO IL FILE F01
C
C
      REWIND 01
      READ(01,1000)
 1000 FORMAT(A)
C
      K=0
  1   READ(01,1000)LINE
      IF(LINE(1:1).EQ.'*') GO TO 10
      K=K+1
      LISLTM(K)=LINE
      READ(LINE,'(A4)')NOSLN(K)
      GO TO 1
 10   CONTINUE
      NSTN=K
C
C__________SCRITTURA DEL FILE CREALTM.DAT
C
      REWIND IOUT2
      DO I =1,NSTN
      WRITE(IOUT2,'(A)')LISLTM(I)
      ENDDO
C
C___________SCRITTURA DEL FILE LTM.FOR
C
C
C     CREAZIONE SUBROUTINE MODC1
C
C
      REWIND IOUT1
C
      WRITE(IOUT1,'(A)')'      SUBROUTINE MODI2('
      WRITE(IOUT1,'(A)')
     &'     &        KI,IFUN,IBLOC1,IBLOC2,VAR,NX5,I1,I2,XYU,DATI,'
      WRITE(IOUT1,'(A)')
     &'     &        K1,K2,IER,CNXYU,TOL)'
      WRITE(IOUT1,'(A)')
     &'      DIMENSION  VAR(NX5,2),XYU(1),DATI(1),CNXYU(1),TOL(1)'
      WRITE(IOUT1,'(A)')'      MX1=NX5'
      WRITE(IOUT1,'(A)')'C****'
      KST=0
      IVIA= 2
C      KEN=500
      KEN=999
      CALL GOTOCA(NSTN,NOSLN,IVIA,KST,KEN,IOUT1)
      WRITE(IOUT1,'(A)')'C****'
      WRITE(IOUT1,'(A)')'  999 RETURN'
      WRITE(IOUT1,'(A)')'       END'
C
C
C     CREAZIONE SUBROUTINE MODC1
C
C
      WRITE(IOUT1,'(A)')'      SUBROUTINE MODC1('
      WRITE(IOUT1,'(A)')
     &'     &        KI,IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,'
      WRITE(IOUT1,'(A)')
     &'     &        NOBL1,NOBL2)'
      WRITE(IOUT1,'(A)')
     &'      DIMENSION  AJAC(MX5,MX5),XYU(1),DATI(1),RNI(1)'
      WRITE(IOUT1,'(A)')'      MXX=MX5'
      WRITE(IOUT1,'(A)')'C****'
      KST=0
      IVIA= 3
C      KEN=500
      KEN=999
      CALL GOTOCA(NSTN,NOSLN,IVIA,KST,KEN,IOUT1)
      WRITE(IOUT1,'(A)')'C****'
      WRITE(IOUT1,'(A)')'  999 RETURN'
      WRITE(IOUT1,'(A)')'       END'
C
C____________FINE
C
C     STOP ' FINE ESECUZIONE'
      END
      SUBROUTINE GOTOCA(NST,MODUL,IVIA,KST,KEN,IOUT)
C
      PARAMETER (NBL01=2000)
C
      DIMENSION MODUL(1),KLAB(NBL01)
      KK=KST
      DO 1 I=1,NST
      KK=KK+1
      KLAB(I)= KK
    1 CONTINUE
      NSTT=NST/10
      NSTT=(NSTT+1)*10
      DO 2 J=NST+1,NSTT
      KLAB(J)= KEN
    2 CONTINUE
 1000 FORMAT(6X,'GO TO(')
      WRITE(IOUT,1000)
      WRITE(IOUT,1001)(KLAB(I),I=1,10)
 1001 FORMAT(5X,'&',6X,9(I3,','),I3,29X)
      IF(NSTT.LE.10) GOTO 9
      KK1=NSTT/10-1
      JJ=10
      DO 8 K=1,KK1
      II=JJ+1
      JJ=JJ+10
      WRITE(IOUT,2001) (KLAB(I),I=II,JJ)
    8 CONTINUE
 2001 FORMAT(5X,'&',5X,',',9(I3,','),I3,29X)
    9 WRITE(IOUT,1002)
 1002 FORMAT(5X,'&      ),KI')
C
      GO TO (10,20,30,40),IVIA
C
   10 DO 15 I=1,NST
      WRITE(IOUT,1003)KLAB(I),MODUL(I)
 1003 FORMAT(2X,I3,1X,'CALL ',A4,'I1(IFUN,K,IBLOC1,IBLOC2,NSTATI,NUSCIT,
     &NINGRE)')
      WRITE(IOUT,1004)KEN
 1004 FORMAT(6X,'GO TO ',I3)
   15 CONTINUE
      GO TO 50
C
   20 DO 25 I=1,NST
      WRITE(IOUT,1005)KLAB(I),MODUL(I)
 1005 FORMAT(2X,I3,1X,'CALL ',A4,'I2(IFUN,VAR,MX1,I1,I2,XYU,DATI,K1,K2,I
     &BLOC1,IBLOC2,'/5X,'&',12X,'IER,CNXYU,TOL)')
      WRITE(IOUT,1004)KEN
   25 CONTINUE
      GO TO 50
C
   30 DO 35 I=1,NST
      WRITE(IOUT,1006)KLAB(I),MODUL(I)
 1006 FORMAT(2X,I3,1X,'CALL ',A4,'C1(IFUN,AJAC,MXX,IXYU,XYU,IPD,DATI,RNI
     &,NOBL1,NOBL2)')
      WRITE(IOUT,1004)KEN
   35 CONTINUE
      GO TO 50
C
   40 DO 45 I=1,NST
      WRITE(IOUT,1007)KLAB(I),MODUL(I)
 1007 FORMAT(2X,I3,1X,'CALL ',A4,'I3(IFO,IOB,DEBL)')
      WRITE(IOUT,1004)KEN
   45 CONTINUE
   50 RETURN
      END

C
C Procedura contenete la variabile per l'identificazione della versione
C
      SUBROUTINE SCCS_crealtm
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)crealtm.f	1.3\t11/13/95'/
      END

