C******************************************************************************
C modulo ordin.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)ordin.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE ORDIN(IV1,IV2,IVV1,IVV2,K)
      DIMENSION IV1(*),IV2(*),IVV1(*),IVV2(*)
      DO 20 J=1,K
      MIN=9999
      DO 10 I=1,K
      IF(IV1(I).LT.0)GO TO 10
      IF(IV1(I).GE.MIN)GO TO 10
      IMIN=I
      MIN=IV1(I)
   10 CONTINUE
      IVV1(J)=MIN
      IV1(IMIN)=-1
      IVV2(J)=IV2(IMIN)
   20 CONTINUE
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_ordin
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)ordin.f	2.1\t7/10/95'/
      END
