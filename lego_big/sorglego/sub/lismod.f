C*********************************************************************
C       Fortran Source:             lismod.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:27:29 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_lismod_f
      CHARACTER*80  RepoID
      COMMON /CM_lismod_f / RepoID
      DATA RepoID/'@(#)1,fsrc,lismod.f,2'/
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

      SUBROUTINE LISMOD(LIMODU,NOSL,NST,LISCHE,NOSCHE,NSCHE,
     $                  MAXMOD,LG1ERR,FIL01,IER)
      DIMENSION NOSL(*),NOSCHE(*)
      CHARACTER*(*) LIMODU(*)
      CHARACTER*(*) LISCHE(*)
      CHARACTER*(*) FIL01(*)
C
      CHARACTER*32 LG1ERR
      CHARACTER*4 DMOD,MODBLO
      CHARACTER*80 LINE
      CHARACTER*8 NOIN,NOBLO
C
C    legge la lista dei moduli lego
C___ e memorizza i nomi nei vettore NOSL e LIMODU
C
C    NST = numero di moduli contenuti nella lista.
C
      IER=0
      NST=0
   1  NST=NST+1
      READ(4,1002,END=20)LIMODU(NST)
 1002 FORMAT(A)
      READ(LIMODU(NST),'(A4)')MODU
      IF(NST.EQ.1)GO TO 7
C
C---CONTROLLO UNICITA' DEI MODULI NELLA LISTA
C
      NS1=NST-1
      DO 5 J=1,NS1
      IF(MODU.EQ.NOSL(J))GO TO 10
    5 CONTINUE
    6 IF(NST.GE.MAXMOD) THEN
C
      IER=1
      ICOD=12
C
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXMOD,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
      RETURN
      ENDIF
C
    7 NOSL(NST)=MODU
      GO TO 1
C
   10 CONTINUE
      NST=NST-1
      GO TO 1
C
   20 NST=NST-1
C
C    legge la lista degli schemi di regolazione
C___ e memorizza i nomi nei vettore NOSCHE e LISCHE
C
C    NSCHE= numero di SCHEMI contenuti nella lista.
C
      IER=0
      NSCHE=0
  51  NSCHE=NSCHE+1
      READ(8,1002,END=70)LISCHE(NSCHE)
C
      READ(LISCHE(NSCHE),'(A4)')MODU
      IF(NSCHE.EQ.1)GO TO 57
C
C---CONTROLLO UNICITA' DEI MODULI NELLA LISTA
C
      NS1=NSCHE-1
      DO 55 J=1,NS1
      IF(MODU.EQ.NOSCHE(J))GO TO 60
   55 CONTINUE
   56 IF(NSCHE.GE.MAXMOD) THEN
C
      IER=1
      ICOD=12
C
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXMOD,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
      RETURN
      ENDIF
C
   57 NOSCHE(NSCHE)=MODU
      GO TO 51
C
   60 CONTINUE
      NSCHE=NSCHE-1
      GO TO 51
C
   70 NSCHE=NSCHE-1
C
      RETURN
      END
C            
