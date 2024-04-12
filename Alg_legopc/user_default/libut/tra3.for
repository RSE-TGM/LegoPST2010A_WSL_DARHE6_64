***********************************************************************
*                                                                     *
*     THREEPHASE THREE COILS TRANFORMER IN SINUSOIDAL REGIME          *
*                               ( 28.03.97) *
*                                                                     *
***********************************************************************
      SUBROUTINE TRA3I3 (IFO,IOB,DEBL)
      PARAMETER (NV=31)
C
      COMMON/TRA301/IBLOC
      COMMON/TRA302/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'TRA3'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'IR1 ','UA','REAL COMPONENT OF FIRST COIL CURRENT              ',
     $ 'IX1 ','UA','IMAGINARY COMPONENT OF FIRST COIL CURRENT         ',
     $ 'IR2 ','UA','REAL COMPONENT OF SECOND COIL CURRENT             ',
     $ 'IX2 ','UA','IMAGINARY COMPONENT OF SECOND COIL CURRENT        ',
     $ 'IR3 ','UA','REAL COMPONENT OF THIRD COIL CURRENT              ',
     $ 'IX3 ','UA','IMAGINARY COMPONENT OF THIRD COIL CURRENT         ',
     $ 'P1  ','UA','ACTIVE POWER ON FIRST COIL                        ',
     $ 'Q1  ','UA','REACTIVE POWER ON FIRST COIL                      ',
     $ 'P2  ','UA','ACTIVE POWER ON SECOND COIL                       ',
     $ 'Q2  ','UA','REACTIVE POWER ON SECOND COIL                     ',
     $ 'P3  ','UA','ACTIVE POWER ON THIRD COIL                        ',
     $ 'Q3  ','UA','REACTIVE POWER ON THIRD COIL                      ',
     $ 'VMR1','UA','REAL COMPONENT OF TENSION AT FIRST COIL TERMINAL  ',
     $ 'VMX1','UA','IMAGINARY COMPONENT OF TENSION AT FIRST COIL TERM.',
     $ 'VMR2','UA','REAL COMPONENT OF TENSION AT SECOND COIL TERMINAL ',
     $ 'VMX2','UA','IMAGINARY COMPONENT OF TENSION AT SECOND COIL TERM',
     $ 'VMR3','UA','REAL COMPONENT OF TENSION AT THIRD COIL TERMINAL  ',
     $ 'VMX3','UA','IMAGINARY COMPONENT OF TENSION AT THIRD COIL TERM.',
     $ 'OMTU','UA','OUTPUT ELECTRICAL DUTY PULSE FACTOR               ',
     $ 'VFR1','IN','REAL COMPONENT OF TENSION AT FIRST COIL           ',
     $ 'VFX1','IN','IMAGINARY COMPONENT OF TENSION AT FIRST COIL      ',
     $ 'VFR2','IN','REAL COMPONENT OF TENSION AT SECOND COIL          ',
     $ 'VFX2','IN','IMAGINARY COMPONENT OF TENSION AT SECOND COIL     ',
     $ 'VFR3','IN','REAL COMPONENT OF TENSION AT THIRD COIL           ',
     $ 'VFX3','IN','IMAGINARY COMPONENT OF TENSION AT THIRD COIL      ',
     $ 'SW1 ','IN','STATE OF FIRST COIL SWITCH                        ',
     $ 'SW2 ','IN','STATE OF SECOND COIL SWITCH                       ',
     $ 'SW3 ','IN','STATE OF THIRD COIL SWITCH                        ',
     $ 'ETA0','IN','TENSION VARIATION ON 2-3 IN PERC. TO MAX          ',
     $ 'OMT ','IN','INPUT ELECTRICAL DUTY PULSE FACTOR                ',
     $ 'MLF1','IN','MALFUNCTION SWITCH                                '/
C
      CALL TRA3I4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 19
      NINGRE = 12
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE TRA3I4 (IOB,MOD)
      COMMON/TRA301/IBLOC
      COMMON/TRA302/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE TRA3I2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      REAL NL,NM
C
C---three coils transformer
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'V1_NOM  '
     $             ,'V2_NOM  '
     $             ,'V3_NOM  '
     $             ,'P1_NOM  '
     $             ,'P2_NOM  '
     $             ,'P3_NOM  '
     $             ,'A_NOM   '
     $             ,'OM_NOM  '
     $             ,'PCC12   '
     $             ,'PCC23   '
     $             ,'PCC31   '
     $             ,'VCC12   '
     $             ,'VCC23   '
     $             ,'VCC31   '
     $             ,'PVIDE   '
     $             ,'IVIDE   '
     $             ,'N_MIN   '
     $             ,'N_MAX   '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) V1N
     $            ,V2N
     $            ,V3N
     $            ,P1N
     $            ,P2N
     $            ,P3N
     $            ,AN 
     $            ,OMN
     $            ,PCC12
     $            ,PCC23
     $            ,PCC31
     $            ,VCC12
     $            ,VCC23
     $            ,VCC31
     $            ,PVIDE
     $            ,IVIDE
     $            ,NL
     $            ,NM
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
C---determinazione zccij=rccij+j*xccij*OMT
C
      PCC12=PCC12*(P1N/AN)
      PCC23=PCC23*(P2N/AN)
      PCC31=PCC31*(P3N/AN)
C
      RCC12=PCC12/100.
      RCC23=PCC23/100.
      RCC31=PCC31/100.
C
      XCC12=SQRT((VCC12/100.)**2-RCC12**2)
      XCC23=SQRT((VCC23/100.)**2-RCC23**2)
      XCC31=SQRT((VCC31/100.)**2-RCC31**2)
C
C---determinazione impedenza a vuoto z0=r0+x0*OMT
C
      PVIDE=PVIDE*(P1N/AN)
C
      R0=100./PVIDE
      X0=1./SQRT((IVIDE/100.)**2-(PVIDE/100.)**2)
C
C---determinazione resistenze ed induttanze d'avvolgimento
C
      R1 = 0.5*(RCC12-RCC23+RCC31)
      R2 = 0.5*(RCC12+RCC23-RCC31)
      R3 = 0.5*(-RCC12+RCC23+RCC31)
      X1 = 0.5*(XCC12-XCC23+XCC31)
      X2 = 0.5*(XCC12+XCC23-XCC31)
      X3 = 0.5*(-XCC12+XCC23+XCC31)
C
C---determinazione di alpha=DN1max/(N1nom+DN1max)
C
      DN1MAX=NM-NL
      ALPHA=DN1MAX/(NL+DN1MAX)
C
      DATI(ID2   ) = R1
      DATI(ID2+ 1) = R2
      DATI(ID2+ 2) = R3
      DATI(ID2+ 3) = X1
      DATI(ID2+ 4) = X2
      DATI(ID2+ 5) = X3
      DATI(ID2+ 6) = R0
      DATI(ID2+ 7) = X0
      DATI(ID2+ 8) = ALPHA
      ID2 = ID2+8
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = AN/V1N
      CNXYU(IV1+ 1) = AN/V1N
      CNXYU(IV1+ 2) = AN/V2N
      CNXYU(IV1+ 3) = AN/V2N
      CNXYU(IV1+ 4) = AN/V3N
      CNXYU(IV1+ 5) = AN/V3N
      CNXYU(IV1+ 6) = AN
      CNXYU(IV1+ 7) = AN
      CNXYU(IV1+ 8) = AN
      CNXYU(IV1+ 9) = AN
      CNXYU(IV1+10) = AN
      CNXYU(IV1+11) = AN
      CNXYU(IV1+12) = V1N
      CNXYU(IV1+13) = V1N
      CNXYU(IV1+14) = V2N
      CNXYU(IV1+15) = V2N
      CNXYU(IV1+16) = V3N
      CNXYU(IV1+17) = V3N
      CNXYU(IV1+18) = OMN
      CNXYU(IV1+19) = V1N
      CNXYU(IV1+20) = V1N
      CNXYU(IV1+21) = V2N
      CNXYU(IV1+22) = V2N
      CNXYU(IV1+23) = V3N
      CNXYU(IV1+24) = V3N
      CNXYU(IV1+25) = 1.
      CNXYU(IV1+26) = 1.  
      CNXYU(IV1+27) = 1.
      CNXYU(IV1+28) = 1.
      CNXYU(IV1+29) = OMN
      CNXYU(IV1+30) = 1.
C
      RETURN
      END
C
C
C
      SUBROUTINE TRA3C1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      DIMENSION CRN(50),CXYU(100)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C---three coils transformer
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      DO I=1,19
         DO J=1,31
            AJAC(I,J)=1.
         ENDDO
      ENDDO
C
      RETURN
C
C---calcolo residui
C
  200 CONTINUE
C
      CALL TRA3RES(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      RETURN
C
C---calcolo jacobiano numerico
C
  300 CONTINUE
C
      NSTATI = 0
      NUSCIT = 19
      NINGRE = 12
      EPS    = 1.E-3
      EPSLIM = 1.E-4
C
      NRIG=NSTATI+NUSCIT
      NCOL=NRIG+NINGRE
C
      CALL TRA3RES(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      DO J=1,NCOL
         VAR=EPS*XYU(IXYU+J-1)
         IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C
         DO K=1,NCOL
            CXYU(K)=XYU(IXYU+K-1)
            IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
         ENDDO   
C
         CALL TRA3RES(IFUN,1,CXYU,IPD,DATI,CRN)
C   
         DO I=1,NRIG
            AJAC(I,J)=(CRN(I)-RNI(I))/VAR
            IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
         ENDDO  
C 
      ENDDO
C
      RETURN
      END
C
C
C
      SUBROUTINE TRA3RES(IFUN,IXYU,XYU,IPD,DATI,RN)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION XYU(*),DATI(*),RN(*)      
      REAL IR1,IX1,IR2,IX2,IR3,IX3,MLF1,M
C
C   decodifica variabili e dati: il segno meno alle correnti (e,
C   di conseguenza, alle potenze) serve per adattarsi alle convenzioni 
C   di segno del modulo SBAR al quale TRA3 si collega: SBAR usa la 
C   convenzione degli utilizzatori e anche TRA3 usa internamente tale
C   convenzione. Il segno meno mostra esternamente la convenzione dei
C   generatori permettendo la connessione a SBAR.
C
      IR1    = -XYU(IXYU   )
      IX1    = -XYU(IXYU+ 1)
      IR2    = -XYU(IXYU+ 2)
      IX2    = -XYU(IXYU+ 3)
      IR3    = -XYU(IXYU+ 4)
      IX3    = -XYU(IXYU+ 5)
      P1     = -XYU(IXYU+ 6)
      Q1     = -XYU(IXYU+ 7)
      P2     = -XYU(IXYU+ 8)
      Q2     = -XYU(IXYU+ 9)
      P3     = -XYU(IXYU+10)
      Q3     = -XYU(IXYU+11)
      VMR1   = XYU(IXYU+12)
      VMX1   = XYU(IXYU+13)
      VMR2   = XYU(IXYU+14)
      VMX2   = XYU(IXYU+15)
      VMR3   = XYU(IXYU+16)
      VMX3   = XYU(IXYU+17)
      OMTU   = XYU(IXYU+18)
      VFR1   = XYU(IXYU+19)
      VFX1   = XYU(IXYU+20)
      VFR2   = XYU(IXYU+21)
      VFX2   = XYU(IXYU+22)
      VFR3   = XYU(IXYU+23)
      VFX3   = XYU(IXYU+24)
      SW1    = XYU(IXYU+25)
      SW2    = XYU(IXYU+26)
      SW3    = XYU(IXYU+27)
      ETA0   = XYU(IXYU+28)
      OMT    = XYU(IXYU+29)
      MLF1   = XYU(IXYU+30)
C
      IF (SW1.NE.0.) SW1=1.
      IF (SW2.NE.0.) SW2=1.
      IF (SW3.NE.0.) SW3=1.
C
      R1     = DATI(IPD   )
      R2     = DATI(IPD+ 1)
      R3     = DATI(IPD+ 2)
      X1     = DATI(IPD+ 3)
      X2     = DATI(IPD+ 4)
      X3     = DATI(IPD+ 5)
      R0     = DATI(IPD+ 6)
      X0     = DATI(IPD+ 7)
      ALPHA  = DATI(IPD+ 8)
C
      X1 = X1*OMT
      X2 = X2*OMT
      X3 = X3*OMT
      X0 = X0*OMT
C
      M = 1-ETA0*ALPHA
C
      IF (MLF1.EQ.1.) THEN
         SW1=0.
      ELSE IF (MLF1.EQ.2.) THEN
         M=0.6
      ELSE IF (MLF1.NE.0.AND.IFUN.NE.3) THEN
         WRITE(6,*) 'Undefined malfunction type!!!'
         STOP
      ENDIF
C
C
C--residuo n.  1 (equazione algebrica)   *******
      RN(1) = -VMR1+R1*IR1-X1*IX1+R0*(IR1+M*IR2+M*IR3)-
     $               X0*(IX1+M*IX2+M*IX3)
C
C--residuo n.  2 (equazione algebrica)   *******
      RN(2) = -VMX1+R1*IX1+X1*IR1+R0*(IX1+M*IX2+M*IX3)+
     $               X0*(IR1+M*IR2+M*IR3)
C
C--residuo n.  3 (equazione algebrica)   *******
      RN(3) = -VMR2+R2*IR2-X2*IX2+M*R0*(IR1+M*IR2+M*IR3)-
     $               M*X0*(IX1+M*IX2+M*IX3)
C
C--residuo n.  4 (equazione algebrica)   *******
      RN(4) = -VMX2+R2*IX2+X2*IR2+M*R0*(IX1+M*IX2+M*IX3)+
     $               M*X0*(IR1+M*IR2+M*IR3)
C
C--residuo n.  5 (equazione algebrica)   *******
      RN(5) = -VMR3+R3*IR3-X3*IX3+M*R0*(IR1+M*IR2+M*IR3)-
     $               M*X0*(IX1+M*IX2+M*IX3)
C
C--residuo n.  6 (equazione algebrica)   *******
      RN(6) = -VMX3+R3*IX3+X3*IR3+M*R0*(IX1+M*IX2+M*IX3)+
     $               M*X0*(IR1+M*IR2+M*IR3)
C
C--residuo n.  7 (equazione algebrica)   *******
      RN(7) = -P1+3*(VMR1*IR1+VMX1*IX1)
C
C--residuo n.  8 (equazione algebrica)   *******
      RN(8) = -Q1+3*(VMX1*IR1-VMR1*IX1)
C
C--residuo n.  9 (equazione algebrica)   *******
      RN(9) = -P2+3*(VMR2*IR2+VMX2*IX2)
C
C--residuo n. 10 (equazione algebrica)   *******
      RN(10) = -Q2+3*(VMX2*IR2-VMR2*IX2)
C
C--residuo n. 11 (equazione algebrica)   *******
      RN(11) = -P3+3*(VMR3*IR3+VMX3*IX3)
C
C--residuo n. 12 (equazione algebrica)   *******
      RN(12) = -Q3+3*(VMX3*IR3-VMR3*IX3)
C
C--residuo n. 13 (equazione algebrica)   *******
      IF (SW1.EQ.1) THEN
         RN(13) = -VMR1+VFR1
      ELSE
         RN(13) = IR1
      ENDIF
C
C--residuo n. 14 (equazione algebrica)   *******
      IF (SW1.EQ.1) THEN
         RN(14) = -VMX1+VFX1
      ELSE
         RN(14) = IX1
      ENDIF
C
C--residuo n. 15 (equazione algebrica)   *******
      IF (SW2.EQ.1) THEN
         RN(15) = -VMR2+VFR2
      ELSE
         RN(15) = IR2
      ENDIF
C
C--residuo n. 16 (equazione algebrica)   *******
      IF (SW2.EQ.1) THEN
         RN(16) = -VMX2+VFX2
      ELSE
         RN(16) = IX2
      ENDIF
C
C--residuo n. 17 (equazione algebrica)   *******
      IF (SW3.EQ.1) THEN
         RN(17) = -VMR3+VFR3
      ELSE
         RN(17) = IR3
      ENDIF
C
C--residuo n. 18 (equazione algebrica)   *******
      IF (SW3.EQ.1) THEN
         RN(18) = -VMX3+VFX3
      ELSE
         RN(18) = IX3
      ENDIF
C
C--residuo n. 19 (equazione algebrica)   *******
      RN(19) = -OMTU+OMT
C
      RETURN
      END      
C
C
C
      SUBROUTINE TRA3D1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---three coils transformer
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
