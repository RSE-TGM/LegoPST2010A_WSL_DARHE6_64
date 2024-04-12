      SUBROUTINE SPLIT(NEQSIS,NU,ICV,ICI,VARNO,VARSI,XY,UU,XN,XIN,
     $                 SIVAR,VARI,PESI,NOTO,NNOTO)
C
      CHARACTER*4 ICV(*),ICI(*)
      CHARACTER*8 VARNO(*),VARSI(*),SIVAR(*),VARI(*)
      DIMENSION XY(*),UU(*),XN(*),XIN(*),PESI(*)
C
      NOTO=0
      NNOTO=0
      DO I=1,NEQSIS
      IF (ICV(I).EQ.'NOTO') THEN
         NOTO=NOTO+1
         VARNO(NOTO)=SIVAR(I)
         XN(NOTO)=XY(I)
      ELSE
         NNOTO=NNOTO+1
         VARSI(NNOTO)=SIVAR(I)
         XIN(NNOTO)=XY(I)
         READ(ICV(I),'(F4.0)') PESI(NNOTO)
      ENDIF
      ENDDO
      DO I=1,NU
      IF (ICI(I).EQ.'NOTO') THEN
         NOTO=NOTO+1
         VARNO(NOTO)=VARI(I)
         XN(NOTO)=UU(I)
      ELSE
         NNOTO=NNOTO+1
         VARSI(NNOTO)=VARI(I)
         XIN(NNOTO)=UU(I)
         READ(ICI(I),'(F4.0)') PESI(NNOTO)
      ENDIF
      ENDDO
C
      RETURN
      END
