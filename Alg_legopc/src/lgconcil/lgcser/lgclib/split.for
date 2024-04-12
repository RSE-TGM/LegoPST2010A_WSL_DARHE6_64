      SUBROUTINE SPLIT (NEQSIS,NU,ICV,ICI,XY,UU,XN,XIN,
     $           	SIVAR,VARI,VARNO,VARSI,NMSIVA,NMVARI,NMSI,
     $           	NMNO,PESI,NOTO,NNOTO,CNXY,CNUU,CNIN,CNN,
     $           	SENSXY,SENSUU,SENSINDX,NGDL,IWZERO)
C
      CHARACTER*4 ICV(*),ICI(*)
      CHARACTER*8 VARNO(*),VARSI(*),SIVAR(*),VARI(*)
      CHARACTER*100 NMSIVA(*),NMVARI(*),NMSI(*),NMNO(*)
      DIMENSION XY(*),UU(*),XN(*),XIN(*),PESI(*)
      DIMENSION CNXY(*),CNUU(*),CNN(*),CNIN(*)
      LOGICAL SENSXY(*),SENSUU(*)
      INTEGER SENSINDX(*)
C
      NOTO=0
      NNOTO=0
      ISEN=0
      NGDL=0
      IWZERO=0
      DO I=1,NEQSIS
      IF (ICV(I).EQ.'NOTO') THEN
         NOTO=NOTO+1
         VARNO(NOTO)=SIVAR(I)
         NMNO(NOTO)=NMSIVA(I)
         XN(NOTO)=XY(I)
         CNN(NOTO)=CNXY(I)
         IF (SENSXY(I).EQ..TRUE.) THEN
             ISEN = ISEN + 1
             SENSINDX(ISEN) = -NOTO
         ENDIF
      ELSE
         NNOTO=NNOTO+1
         VARSI(NNOTO)=SIVAR(I)
         NMSI(NNOTO)=NMSIVA(I)
         XIN(NNOTO)=XY(I)
         CNIN(NNOTO)=CNXY(I)
         READ(ICV(I),'(F4.0)') PESI(NNOTO)
         IF (SENSXY(I).EQ..TRUE.) THEN
             ISEN = ISEN + 1
             NGDL = NGDL + 1
             SENSINDX(ISEN) = NNOTO
             IF (PESI(NNOTO).EQ.0) IWZERO=IWZERO+1
         ENDIF
      ENDIF
      ENDDO
      DO I=1,NU
      IF (ICI(I).EQ.'NOTO') THEN
         NOTO=NOTO+1
         VARNO(NOTO)=VARI(I)
         NMNO(NOTO)=NMVARI(I)
         XN(NOTO)=UU(I)
         CNN(NOTO)=CNUU(I)
         IF (SENSUU(I).EQ..TRUE.) THEN
             ISEN = ISEN + 1
             SENSINDX(ISEN) = -NOTO
         ENDIF
      ELSE
         NNOTO=NNOTO+1
         VARSI(NNOTO)=VARI(I)
         NMSI(NNOTO)=NMVARI(I)
         XIN(NNOTO)=UU(I)
         CNIN(NNOTO)=CNUU(I)
         READ(ICI(I),'(F4.0)') PESI(NNOTO)
         IF (SENSUU(I).EQ..TRUE.) THEN
             ISEN = ISEN + 1
             NGDL = NGDL + 1
             SENSINDX(ISEN) = NNOTO
             IF (PESI(NNOTO).EQ.0) IWZERO=IWZERO+1
         ENDIF
      ENDIF
      ENDDO
C
      RETURN
      END
