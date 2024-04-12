C******************************************************************************
C modulo gotoca.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)gotoca.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE GOTOCA(NST,MODUL,IVIA,KST,KEN,IOUT)
      DIMENSION MODUL(*),KLAB(300)
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
 1001 FORMAT(5X,'$',6X,9(I3,','),I3,29X)
      IF(NSTT.LE.10) GOTO 9
      KK1=NSTT/10-1
      JJ=10
      DO 8 K=1,KK1
      NN=JJ
      II=NN+1
      JJ=NN+10
      WRITE(IOUT,2001) (KLAB(I),I=II,JJ)
    8 CONTINUE
 2001 FORMAT(5X,'$',5X,',',9(I3,','),I3,29X)
    9 WRITE(IOUT,1002)
 1002 FORMAT(5X,'$      ),KI')
C
      GO TO (10,20,30,40,46),IVIA
C
   10 DO 15 I=1,NST
      WRITE(IOUT,1003)KLAB(I),MODUL(I)
 1003 FORMAT(2X,I3,1X,'CALL ',A4,'I1(IFUN,K,IBLOC1,IBLOC2,NSTATI,',
     $   'NUSCIT,NINGRE)')
      WRITE(IOUT,1004)KEN
 1004 FORMAT(6X,'GO TO ',I3)
   15 CONTINUE
      GO TO 50
C
   20 DO 25 I=1,NST
      WRITE(IOUT,1005)KLAB(I),MODUL(I)
 1005 FORMAT(2X,I3,1X,'CALL ',A4,'I2(IFUN,VAR,MX1,I1,I2,XYU,DATI,',
     $   'K1,K2,IBLOC1,IBLOC2,'/5X,'$',12X,'IER,CNXYU,TOL)')
      WRITE(IOUT,1004)KEN
   25 CONTINUE
      GO TO 50
C
   30 DO 35 I=1,NST
      WRITE(IOUT,1006)KLAB(I),MODUL(I)
 1006 FORMAT(2X,I3,1X,'CALL ',A4,'C1(IFUN,AJAC,MXX,IXYU,XYU,IPD,',
     $   'DATI,RNI,NOBL1,NOBL2)')
      WRITE(IOUT,1004)KEN
   35 CONTINUE
      GO TO 50
C
   40 DO 45 I=1,NST
      WRITE(IOUT,1007)KLAB(I),MODUL(I)
 1007 FORMAT(2X,I3,1X,'CALL ',A4,'I3(IFO,IOB,DEBL)')
      WRITE(IOUT,1004)KEN
   45 CONTINUE
C
   46 DO 47 I=1,NST
      WRITE(IOUT,1008)KLAB(I),MODUL(I)
 1008 FORMAT(2X,I3,1X,'CALL ',A4,'D1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE
     $,SYMVAR,XYU,IXYU,')
      WRITE(IOUT,1009)
 1009 FORMAT('     $       DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)')
      WRITE(IOUT,1004)KEN
   47 CONTINUE
   50 RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_gotoca
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)gotoca.f	2.1\t7/10/95'/
      END
