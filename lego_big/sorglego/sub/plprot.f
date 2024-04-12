C*********************************************************************
C       Fortran Source:             plprot.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:37 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_plprot_f
      CHARACTER*80  RepoID
      COMMON /CM_plprot_f / RepoID
      DATA RepoID/'@(#)1,fsrc,plprot.f,2'/
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

      SUBROUTINE PLPROT(N,IPOUT,SIVAR,MX1,VARI,MX3,NEQSIS,NU,
     $                  XY,UU,CNXY,CNUU,NN,XYOUT,SYOUT,MX2)
      DIMENSION IPOUT(*),XY(*),UU(*),
     $          CNXY(*),CNUU(*),XYOUT(*)
      CHARACTER*8 SIVAR(MX1),VARI(MX3),SYOUT(MX2)
      CHARACTER*8 WAWA
C
C     CARICA NEL VETTORI: SYOUT  I SIMBOLI
C                         XYOUT  I VALORI
C     DELLE VARIABILI
C        IN OUTPUT
C
      IF(N.EQ.0)RETURN
      IF(N.EQ.99999)GO TO 30
C
      NN=N
      DO 20 I=1,NN
      K= IPOUT(I)
      IF(K.LT.0)GO TO 5
      WAWA=SIVAR(K)
      Z=XY(K) * CNXY(K)
      GO TO 10
C
    5 K=-K
      WAWA=VARI(K)
      Z=UU(K)*CNUU(K)
C
   10 SYOUT(I)=WAWA
      XYOUT(I)=Z
   20 CONTINUE
      RETURN
C
   30 DO 40 I=1,NEQSIS
      SYOUT(I)=SIVAR(I)
      XYOUT(I)=XY(I)*CNXY(I)
   40 CONTINUE
      DO 50 I=1,NU
      K=NEQSIS+I
      SYOUT(K)=VARI(I)
      XYOUT(K)=UU(I)*CNUU(I)
   50 CONTINUE
      NN=NEQSIS+NU
      RETURN
      END
C            
