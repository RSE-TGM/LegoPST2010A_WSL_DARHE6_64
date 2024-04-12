C*********************************************************************
C       Fortran Source:             lg1_gotoca.f
C       Subsystem:              1
C       Description:
C       %created_by:    famgr %
C       %date_created:  Tue Apr 30 10:09:02 1996 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_lg1_gotoca_f
      CHARACTER*80  RepoID
      COMMON /CM_lg1_gotoca_f / RepoID
      DATA RepoID/'@(#)1,fsrc,lg1_gotoca.f,3'/
      END

      SUBROUTINE GOTOCA(NST,MODUL,IVIA,KST,KEN,IOUT)
      DIMENSION MODUL(1),KLAB(300)
C$$$$$     !!!!!!! INIZIO ISTRUZIONI PER SCCS !!!!!!!
       CHARACTER*80 SccsID
       DATA SccsID/'@(#)lg1_gotoca.f	1.2\t 1.2\t 3/30/95'/
C$$$$$     !!!!!!! FINE ISTRUZIONI PER SCCS !!!!!!!
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
