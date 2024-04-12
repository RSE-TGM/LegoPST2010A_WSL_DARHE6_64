C*********************************************************************
C       Fortran Source:             blleg1.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:23:21 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_blleg1_f
      CHARACTER*80  RepoID
      COMMON /CM_blleg1_f / RepoID
      DATA RepoID/'@(#)1,fsrc,blleg1.f,2'/
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

      SUBROUTINE BLLEG1(IPVRS,NVART,XYU,XY,UU)
      DIMENSION IPVRS(*),XY(*),UU(*),XYU(*)
C
C     TRASFERISCE IL CONTENUTO DEL VETTORE XYU (VARIABILI DI OGNI
C     BLOCCO) NEI VETTORI XY(VARIABILI DEL SISTEMA -STATI,USCITE)
C     E UU (VARIABILI DI INGRESSO)
C
      DO 10 I=1,NVART
      J=IPVRS(I)
      IF(J)1,1,2
    1 J=-J
      UU(J)=XYU(I)
      GO TO 10
    2 XY(J)=XYU(I)
   10 CONTINUE
      RETURN
      END
C            
