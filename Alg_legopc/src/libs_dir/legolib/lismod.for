C******************************************************************************
C modulo lismod.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)lismod.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LISMOD(LIMODU,NOSL,NST,
     $                  MAXMOD,LG1ERR,FIL01,IER)
      DIMENSION NOSL(*)
      CHARACTER*(*) LIMODU(*)
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
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_lismod
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)lismod.f	2.1\t7/10/95'/
      END
