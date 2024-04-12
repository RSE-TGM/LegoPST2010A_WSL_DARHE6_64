C*********************************************************************
C       Fortran Source:             leci.f
C       Subsystem:              1
C       Description:
C       %created_by:    lopez %
C       %date_created:  Mon Oct 28 10:54:13 2002 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_leci_f
      CHARACTER*80  RepoID
      COMMON /CM_leci_f / RepoID
      DATA RepoID/'@(#)1,fsrc,leci.f,2'/
      END
C**********************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LECI(ICV,NEQSIS,ICI,NU,SIVAR,MX1,VARI,MX3,VARNO,VARSI,
     $                XY,UU,XN,XIN,KN,KIN,IER)
      DIMENSION ICV(*),ICI(*),VARNO(MX3,2)
      DIMENSION XY(*),UU(*),XN(*),XIN(*),VARSI(MX1,2)
      CHARACTER*8 SIVAR(MX1),VARI(MX3)
C***  DATA NO/'NOTO'/,BLK/' '/,ISI/'SI'/
      KN=0
      KIN=0
      NX1=MX1
      NX3=MX3
      CALL SEPAR(NEQSIS,ICV,SIVAR,NX1,VARNO,VARSI,NX3,KN,KIN,XY,XN,XIN,
     $           NX1)
      CALL SEPAR(NU,ICI,VARI,NX3,VARNO,VARSI,NX3,KN,KIN,UU,XN,XIN,NX1)
      K=KN
      IER=0
      WRITE(6,1000)
 1000 FORMAT(///10X,'CONTROLLO CHE IL NUMERO DELLE VARIABILI NOTE ',
     $   'SIA PARI AL NUMERO DEGLI INGRESSI'/10X,
     $   'PER POTER CALCOLARE IL REGIME INIZIALE '/)
      IF(NU-K)30,35,40
   30 WRITE(6,1001)K,NU
 1001 FORMAT(//10X,'LE VARIABILI NOTE SONO ',I6,
     $   /10X,'GLI INGRESSI SONO',I7)
      M=K-NU
      WRITE(6,1002)M
 1002 FORMAT(//10X,I6,' VARIABILI DEFINITE NOTE DEVONO DIVENTARE ',
     $   'INCOGNITE DEL PROBLEMA '/)
      GO TO 45
   40 M=NU-K
      WRITE(6,1001)K,NU
      WRITE(6,1003)M
 1003 FORMAT(//10X,I6,' VARIABILI DEVONO ESSERE AGGIUNTE A QUELLE ',
     $   'RITENUTE NOTE '/)
      IER=1
   45 CONTINUE
      WRITE(6,1013)
 1013 FORMAT(//10X,'I DATI NECESSARI AL CALCOLO DEL REGIME INIZIALE '/
     $   10X,'SONO INSUFFICIENTI - ESECUZIONE INTERROTTA ')
      IER=1
      RETURN
   35 WRITE(6,1004)
 1004 FORMAT(//10X,'IL PROBLEMA PUO ESSERE RISOLTO '//)
      RETURN
      END
C            
