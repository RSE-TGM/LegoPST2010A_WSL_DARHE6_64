C******************************************************************************
C modulo for_base.f
C tipo 
C release 4.2
C data 2/9/95
C reserver @(#)for_base.f	4.2
C******************************************************************************
C*                                                                     *
C*                   VERSIONE MODIFICATA DA S.D.I.                     *
C*                          IL 29/5/1992                               *
C*                                                                     *
C***********************************************************************
C
C**************************************************************************
C
C        FORTRAN DI BASE DI OGNI LIBRERIA DEI MODULI LEGO
C        SUBROUTINES : 
C
C         BNAJAC,FDDP,FPPI,NAJAC,LINTAB,LININT,REG
C
C**************************************************************************
      SUBROUTINE BNAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1              NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,RESIDUI)
C
C routine generale di calcolo jacobiano numerico con DERIVATE +/-
C con incrementi +/- EPS in p.u. ( valori minimi assoluti EPSLIM )
C i residui devono essere calcolati dalla routine ( da dich.EXTERNAL )
C SUBROUTINE RESIDUI(IFUN,IXYU,XYU,IPD,DATI,RN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100),CCRN(50),CCXYU(100)
      EXTERNAL RESIDUI
C
      NRIG=NSTATI+NUSCIT
      NCOL=NRIG+NINGRE
C
      DO 30 J=1,NCOL
      VAR=EPS*XYU(IXYU+J-1)
      IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C
      DO 10 K=1,NCOL
      CXYU(K)=XYU(IXYU+K-1)
      CCXYU(K)=XYU(IXYU+K-1)
      IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
      IF(K.EQ.J) CCXYU(K)=CCXYU(K)-VAR
   10      CONTINUE
C
C     residui(ifun,ixyu,xyu,ipd,dati,rn)
C
      CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
      CALL RESIDUI(3,1,CCXYU,IPD,DATI,CCRN)
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(CRN(I)-CCRN(I))/(2.*VAR)
      IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
   20      CONTINUE
C
   30      CONTINUE
C
      RETURN
      END
C**************************************************************************
      SUBROUTINE FDDP(IGO,CN,CD,EN1,XN,XN1,SN1,DT)
C
C     CALCOLA LA RISPOSTA DI
C     1)  UN FILTRO
C     2)  UN DERIVATORE
C     3)  UN POLO UNO ZERO (PROP.+DERIV)
C
C         CN=COSTANTE AL NUMERATORE
C         CD=COSTANTE AL DENOMINATORE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CDTM=1.-DT/(2*CD)
      CDTP=1.+DT/(2*CD)
C
      GO TO (10,20,30),IGO
C*******FILTRO
   10 XN1=(XN*CDTM+DT*CN*EN1/CD)/CDTP
      SN1=XN1
      GO TO 40
C*******DERIVATORE
   20 XN1=(XN*CDTM+DT*CN*EN1/CD/CD)/CDTP
      SN1=EN1*CN/CD-XN1
      GO TO 40
C*******UN POLO UNO ZERO
   30 DN=CN-CD
      XN1=(XN*CDTM+DT*DN*EN1/CD/CD)/CDTP
      SN1=EN1*DN/CD-XN1+EN1
   40 RETURN
      END
C**************************************************************************
      SUBROUTINE FPPI(GI,GP,SMIN,SMAX,E,XN,XN1,S,DT)
C
C                  P I  A DESATURAZIONE
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      ISAT=0
      A=ABS(SMIN)+ABS(SMAX)
      IF(A.GT.1.E-7)ISAT=1
      SP=GP*E
      XN1=XN+GI*E*DT
      S=SP+XN1
      IF(ISAT.EQ.0)GO TO 10
      IF(S.LT.SMAX)GO TO 5
      S=SMAX
      XN1=S-SP
      GO TO 10
   5  IF(S.GT.SMIN)GO TO 10
      S=SMIN
      XN1=S-SP
   10 RETURN
      END
C**************************************************************************
      SUBROUTINE NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1               NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,RESIDUI)
C
C routine generale di calcolo jacobiano numerico
C con incremento EPS in p.u. ( valore minimo assoluto EPSLIM )
C i residui devono essere calcolati dalla routine ( da dich.EXTERNAL )
C SUBROUTINE RESIDUI(IFUN,IXYU,XYU,IPD,DATI,RN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
      EXTERNAL RESIDUI
C
      NRIG=NSTATI+NUSCIT
      NCOL=NRIG+NINGRE
C
C     residui(ifun,ixyu,xyu,ipd,dati,rn)
C
      CALL RESIDUI(3,IXYU,XYU,IPD,DATI,RN)
C
      DO 30 J=1,NCOL
      VAR=EPS*XYU(IXYU+J-1)
      IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C
      DO 10 K=1,NCOL
      CXYU(K)=XYU(IXYU+K-1)
      IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
   10      CONTINUE
C
      CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(CRN(I)-RN(I))/VAR
      IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
   20      CONTINUE
C
   30      CONTINUE
C
      RETURN
      END
C**************************************************************************
      SUBROUTINE LINTAB(TABP,LP,TABX,LX,TABY,X,P,Y,DYX,DYP)
C  INTERP. LINEARE SU TABELLE PARAMETRICHE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION TABP(*),TABX(*),TABY(*)
      LP1=LP-1
      DO 10 I=2,LP1
      IF(P-TABP(I)) 20,20,10
  10  CONTINUE
      I=LP
  20  IP=LX*(I-2)+1
      CALL LININT(TABX,LX,TABY(IP),X,Y1,DYX1)
      IP=IP+LX
      CALL LININT(TABX,LX,TABY(IP),X,Y2,DYX2)
      DYP=(Y2-Y1)/(TABP(I)-TABP(I-1))
      Y=Y1+(P-TABP(I-1))*DYP
      DYX=DYX1+(P-TABP(I-1))*(DYX2-DYX1)/(TABP(I)-TABP(I-1))
      RETURN
      END
C
      SUBROUTINE LININT(TABX,LX,TABY,X,Y,DYX)
C  INTERP. LINEARE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION TABX(*),TABY(*)
      LX1=LX-1
      DO 10 I=2,LX1
      IF(X-TABX(I)) 20,20,10
  10  CONTINUE
      I=LX
  20  DYX=(TABY(I)-TABY(I-1))/(TABX(I)-TABX(I-1))
      Y=TABY(I-1)+(X-TABX(I-1))*DYX
      RETURN
      END
C**************************************************************************
      SUBROUTINE REG001
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG002
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG003
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG004
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG005
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG006
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG007
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG008
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG009
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG010
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG011
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG012
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG013
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG014
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG015
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG016
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG017
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG018
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG019
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
      SUBROUTINE REG020
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
