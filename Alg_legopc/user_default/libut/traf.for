C**********************************************************************
C modulo traf.f
C tipo 
C release 1.1
C data 3/2/98
C Puertollano project libut reserver @(#)traf.f	1.1
C**********************************************************************
C
      SUBROUTINE TRAFI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2)
      REAL IBASE1, IBASE2, I0
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      
      REAL IRT1, IXT1, IRT2, IXT2                                       !SNGL
C      DOUBLE PRECISION IRT1, IXT1, IRT2, IXT2                           !DBLE
C
C---TRASFORMATORE RAPP. VARIABILE
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'VBASE1_V'
     $             ,'VN1MX_% '
     $             ,'VBASE2_V'
     $             ,'VCC_%   '
     $             ,'QBASE_w '
     $             ,'QNTRA_w '
     $             ,'QPFER_% '
     $             ,'QPCC_%  '
     $             ,'I0_%    '
      WRITE(14,500) 'OMBA_r/s'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) VBASE1
     $            ,VN1MX
     $            ,VBASE2
     $            ,VCC
     $            ,QBASE
     $            ,QNTRA
     $            ,QPFER
     $            ,QPCC
     $            ,I0
      READ(14,501) OMBA
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = VBASE1
      DATI(ID2+ 1) = VN1MX/100.
      DATI(ID2+ 2) = VBASE2
      DATI(ID2+ 3) = VCC/100.
      DATI(ID2+ 4) = QBASE
      DATI(ID2+ 5) = QNTRA
      DATI(ID2+ 6) = QPFER/100.
      DATI(ID2+ 7) = QPCC/100.
      DATI(ID2+ 8) = I0/100.
      DATI(ID2+ 9) = OMBA
      ID2 = ID2+9
C
C---Calcolo correnti nominali lato at(1) e lato bt(2)
C
      IBASE1  = QBASE/(sqrt(3.)*VBASE1)
      IBASE2  = QBASE/(sqrt(3.)*VBASE2)
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = IBASE1
      CNXYU(IV1+ 1) = IBASE1
      CNXYU(IV1+ 2) = IBASE2
      CNXYU(IV1+ 3) = IBASE2
      CNXYU(IV1+ 4) = QBASE
      CNXYU(IV1+ 5) = QBASE
      CNXYU(IV1+ 6) = 100.
      CNXYU(IV1+ 7) = 100.
      CNXYU(IV1+ 8) = QNTRA
      CNXYU(IV1+ 9) = QNTRA
      CNXYU(IV1+10) = VBASE1
      CNXYU(IV1+11) = VBASE1
      CNXYU(IV1+12) = VBASE2
      CNXYU(IV1+13) = VBASE2
      CNXYU(IV1+14) = VBASE1
      CNXYU(IV1+15) = VBASE1
      CNXYU(IV1+16) = VBASE2
      CNXYU(IV1+17) = VBASE2
      CNXYU(IV1+18) = 1.
      CNXYU(IV1+19) = 1.
      CNXYU(IV1+20) = 1.
      CNXYU(IV1+21) = OMBA
      CNXYU(IV1+22) = 1.
      CNXYU(IV1+23) = 1.
      RETURN
      END
C
C
C
      SUBROUTINE TRAFC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL TRAF
C
      REAL IRT1, IXT1, IRT2, IXT2, I0                                   !SNGL
      REAL IMT1, IMT2
C      DOUBLE PRECISION IRT1, IXT1, IRT2, IXT2                           !DBLE
C
C---TRASFORMATORE RAPP. VARIABILE
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL TRAFJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL TRAF (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL TRAFJC (2,...
C
C      jacobiano numerico  CALL TRAFJC (3,...
C
C$*$
  300 CONTINUE
      CALL TRAFJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE TRAFJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL TRAF
C
      REAL IRT1, IXT1, IRT2, IXT2, IMT1, IMT2, I0                         !SNGL
      LOGICAL SIN1, SIN2, STRA, JFLOLOG
C      DOUBLE PRECISION IRT1, IXT1, IRT2, IXT2                           !DBLE
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da IRT1
      AJAC(1,1)=1.
C   ---dipendenza da VR1T
      AJAC(1,15)=1.
C   ---dipendenza da VX1T
      AJAC(1,16)=1.
C   ---dipendenza da VR2T
      AJAC(1,17)=1.
C   ---dipendenza da VX2T
      AJAC(1,18)=1.
C   ---dipendenza da ETA0
      AJAC(1,19)=1.
C   ---dipendenza da OMTI
      AJAC(1,22)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da IXT1
      AJAC(2,2)=1.
C   ---dipendenza da VR1T
      AJAC(2,15)=1.
C   ---dipendenza da VX1T
      AJAC(2,16)=1.
C   ---dipendenza da VR2T
      AJAC(2,17)=1.
C   ---dipendenza da VX2T
      AJAC(2,18)=1.
C   ---dipendenza da ETA0
      AJAC(2,19)=1.
C   ---dipendenza da OMTI
      AJAC(2,22)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da IRT2
      AJAC(3,3)=1.
C   ---dipendenza da VR1T
      AJAC(3,15)=1.
C   ---dipendenza da VX1T
      AJAC(3,16)=1.
C   ---dipendenza da VR2T
      AJAC(3,17)=1.
C   ---dipendenza da VX2T
      AJAC(3,18)=1.
C   ---dipendenza da ETA0
      AJAC(3,19)=1.
C   ---dipendenza da OMTI
      AJAC(3,22)=1.
C
C---equazione n.4 (algebrica):
C   ---dipendenza da IXT2
      AJAC(4,4)=1.
C   ---dipendenza da VR1T
      AJAC(4,15)=1.
C   ---dipendenza da VX1T
      AJAC(4,16)=1.
C   ---dipendenza da VR2T
      AJAC(4,17)=1.
C   ---dipendenza da VX2T
      AJAC(4,18)=1.
C   ---dipendenza da ETA0
      AJAC(4,19)=1.
C   ---dipendenza da OMTI
      AJAC(4,22)=1.
C
C---equazione n.5 (algebrica):
C   ---dipendenza da IRT2
      AJAC(5,3)=1.
C   ---dipendenza da IXT2
      AJAC(5,4)=1.
C   ---dipendenza da QPTR
      AJAC(5,5)=1.
C   ---dipendenza da VR2T
      AJAC(5,17)=1.
C   ---dipendenza da VX2T
      AJAC(5,18)=1.
C
C---equazione n.6 (algebrica):
C   ---dipendenza da IRT2
      AJAC(6,3)=1.
C   ---dipendenza da IXT2
      AJAC(6,4)=1.
C   ---dipendenza da QQTR
      AJAC(6,6)=1.
C   ---dipendenza da VR2T
      AJAC(6,17)=1.
C   ---dipendenza da VX2T
      AJAC(6,18)=1.
C
C---equazione n.7 (algebrica):
C   ---dipendenza da IRT1
      AJAC(7,1)=1.
C   ---dipendenza da IXT1
      AJAC(7,2)=1.
C   ---dipendenza da IMT1
      AJAC(7,7)=1.
C
C---equazione n.8 (algebrica):
C   ---dipendenza da IRT2
      AJAC(8,3)=1.
C   ---dipendenza da IXT2
      AJAC(8,4)=1.
C   ---dipendenza da IMT2
      AJAC(8,8)=1.
C
C---equazione n.9 (algebrica):
C   ---dipendenza da IMT1
      AJAC(9,7)=1.
C   ---dipendenza da QPCU
      AJAC(9,9)=1.
C
C---equazione n.10 (algebrica):
C   ---dipendenza da QPFE
      AJAC(10,10)=1.
C   ---dipendenza da VR1T
      AJAC(10,15)=1.
C   ---dipendenza da VX1T
      AJAC(10,16)=1.
C
C---equazione n.11 (algebrica):
C   ---dipendenza da VR11
      AJAC(11,11)=1.
C   ---dipendenza da VR1T
      AJAC(11,15)=1.
C
C---equazione n.12 (algebrica):
C   ---dipendenza da VX11
      AJAC(12,12)=1.
C   ---dipendenza da VX1T
      AJAC(12,16)=1.
C
C---equazione n.13 (algebrica):
C   ---dipendenza da VR22
      AJAC(13,13)=1.
C   ---dipendenza da VR2T
      AJAC(13,17)=1.
C
C---equazione n.14 (algebrica):

      AJAC(14,14)=1.
C   ---dipendenza da VX2T
      AJAC(14,18)=1.
CC   ---dipendenza da XMAL

      DO J=1,14
       AJAC(J,24) = 1.
      END DO

      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
      IRT1   = XYU(IXYU   )
      IXT1   = XYU(IXYU+ 1)
      IRT2   = XYU(IXYU+ 2)
      IXT2   = XYU(IXYU+ 3)
      QPTR   = XYU(IXYU+ 4)
      QQTR   = XYU(IXYU+ 5)
      IMT1   = XYU(IXYU+ 6)
      IMT2   = XYU(IXYU+ 7)
      QPCU   = XYU(IXYU+ 8)
      QPFE   = XYU(IXYU+ 9)
      VR11   = XYU(IXYU+10)
      VX11   = XYU(IXYU+11)
      VR22   = XYU(IXYU+12)
      VX22   = XYU(IXYU+13)
      VR1T   = XYU(IXYU+14)
      VX1T   = XYU(IXYU+15)
      VR2T   = XYU(IXYU+16)
      VX2T   = XYU(IXYU+17)
      ETA0   = XYU(IXYU+18)
      SIN1   = XYU(IXYU+19)
      SIN2   = XYU(IXYU+20)
      OMTI   = XYU(IXYU+21)
      STRA   = XYU(IXYU+22)
      XMAL   = XYU(IXYU+23)
C
      VBASE1 = DATI(IPD   )
      VN1MX  = DATI(IPD+ 1)
      VBASE2 = DATI(IPD+ 2)
      VCC    = DATI(IPD+ 3)
      QBASE  = DATI(IPD+ 4)
      QNTRA  = DATI(IPD+ 5)
      QPFER  = DATI(IPD+ 6)
      QPCC   = DATI(IPD+ 7)
      I0     = DATI(IPD+ 8)
      OMBA   = DATI(IPD+ 9)
C
C---LO JACOBIANO ANALITICO NON E' CORRETTO
C
C$*$
C
C--derivata del residuo n.  1 (equazione algebrica)   *******
C     --- rispetto alla variabile IRT1
C      AJAC(1,1) = 
C     --- rispetto alla variabile VR1T
C      AJAC(1,15) = 
C     --- rispetto alla variabile VX1T
C      AJAC(1,16) = 
C     --- rispetto alla variabile VR2T
C      AJAC(1,17) = 
C     --- rispetto alla variabile VX2T
C      AJAC(1,18) = 
C     --- rispetto alla variabile ETA0
C      AJAC(1,19) = 
C     --- rispetto alla variabile OMTI
C      AJAC(1,22) = 
C
C--derivata del residuo n.  2 (equazione algebrica)   *******
C     --- rispetto alla variabile IXT1
C      AJAC(2,2) = 
C     --- rispetto alla variabile VR1T
C      AJAC(2,15) = 
C     --- rispetto alla variabile VX1T
C      AJAC(2,16) = 
C     --- rispetto alla variabile VR2T
C      AJAC(2,17) = 
C     --- rispetto alla variabile VX2T
C      AJAC(2,18) = 
C     --- rispetto alla variabile ETA0
C      AJAC(2,19) = 
C     --- rispetto alla variabile OMTI
C      AJAC(2,22) = 
C
C--derivata del residuo n.  3 (equazione algebrica)   *******
C     --- rispetto alla variabile IRT2
C      AJAC(3,3) = 
C     --- rispetto alla variabile VR1T
C      AJAC(3,15) = 
C     --- rispetto alla variabile VX1T
C      AJAC(3,16) = 
C     --- rispetto alla variabile VR2T
C      AJAC(3,17) = 
C     --- rispetto alla variabile VX2T
C      AJAC(3,18) = 
C     --- rispetto alla variabile ETA0
C      AJAC(3,19) = 
C     --- rispetto alla variabile OMTI
C      AJAC(3,22) = 
C
C--derivata del residuo n.  4 (equazione algebrica)   *******
C     --- rispetto alla variabile IXT2
C      AJAC(4,4) = 
C     --- rispetto alla variabile VR1T
C      AJAC(4,15) = 
C     --- rispetto alla variabile VX1T
C      AJAC(4,16) = 
C     --- rispetto alla variabile VR2T
C      AJAC(4,17) = 
C     --- rispetto alla variabile VX2T
C      AJAC(4,18) = 
C     --- rispetto alla variabile ETA0
C      AJAC(4,19) = 
C     --- rispetto alla variabile OMTI
C      AJAC(4,22) = 
C
C--derivata del residuo n.  5 (equazione algebrica)   *******
C     --- rispetto alla variabile IRT2
C      AJAC(5,3) = 
C     --- rispetto alla variabile IXT2
C      AJAC(5,4) = 
C     --- rispetto alla variabile QPTR
C      AJAC(5,5) = 
C     --- rispetto alla variabile VR2T
C      AJAC(5,17) = 
C     --- rispetto alla variabile VX2T
C      AJAC(5,18) = 
C
C--derivata del residuo n.  6 (equazione algebrica)   *******
C     --- rispetto alla variabile IRT2
C      AJAC(6,3) = 
C     --- rispetto alla variabile IXT2
C      AJAC(6,4) = 
C     --- rispetto alla variabile QQTR
C      AJAC(6,6) = 
C     --- rispetto alla variabile VR2T
C      AJAC(6,17) = 
C     --- rispetto alla variabile VX2T
C      AJAC(6,18) = 
C
C--derivata del residuo n.  7 (equazione algebrica)   *******
C     --- rispetto alla variabile IRT1
C      AJAC(7,1) = 
C     --- rispetto alla variabile IXT1
C      AJAC(7,2) = 
C     --- rispetto alla variabile IMT1
C      AJAC(7,7) = 
C
C--derivata del residuo n.  8 (equazione algebrica)   *******
C     --- rispetto alla variabile IRT2
C      AJAC(8,3) = 
C     --- rispetto alla variabile IXT2
C      AJAC(8,4) = 
C     --- rispetto alla variabile IMT2
C      AJAC(8,8) = 
C
C--derivata del residuo n.  9 (equazione algebrica)   *******
C     --- rispetto alla variabile IMT1
C      AJAC(9,7) = 
C     --- rispetto alla variabile QPCU
C      AJAC(9,9) = 
C
C--derivata del residuo n.  10 (equazione algebrica)   *******
C     --- rispetto alla variabile QPFE
C      AJAC(10,10) = 
C     --- rispetto alla variabile VRT1
C      AJAC(10,15) = 
C     --- rispetto alla variabile VXT1
C      AJAC(10,16) = 
C
C--derivata del residuo n.  11 (equazione algebrica)   *******
C     --- rispetto alla variabile VR11
C      AJAC(11,11) = 
C     --- rispetto alla variabile VR1T
C      AJAC(11,15) = 
C
C--derivata del residuo n.  12 (equazione algebrica)   *******
C     --- rispetto alla variabile VX11
C      AJAC(12,12) = 
C     --- rispetto alla variabile VX1T
C      AJAC(12,16) = 
C
C--derivata del residuo n.  13 (equazione algebrica)   *******
C     --- rispetto alla variabile VR22
C      AJAC(13,13) = 
C     --- rispetto alla variabile VR2T
C      AJAC(11,17) = 
C
C--derivata del residuo n.  14 (equazione algebrica)   *******
C     --- rispetto alla variabile VX22
C      AJAC(14,14) = 
C     --- rispetto alla variabile VX2T
C      AJAC(14,18) = 
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 14
      NINGRE = 10
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,TRAF)
      RETURN
      END
C
C
C
      SUBROUTINE TRAF (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL IRT1, IXT1, IRT2, IXT2, I0                                     !SNGL
      REAL IMT1, IMT2, IAR, IAX, I0R1, I0X1, I0R2, I0X2
      LOGICAL SIN1,SIN2,STRA,JFLOLOG
C      DOUBLE PRECISION IRT1, IXT1, IRT2, IXT2                           !DBLE
C
C---TRASFORMATORE RAPP. VARIABILE
C   calcolo residui
C
C---decodifica variabili e dati
C
      IRT1   = XYU(IXYU   )
      IXT1   = XYU(IXYU+ 1)
      IRT2   = XYU(IXYU+ 2)
      IXT2   = XYU(IXYU+ 3)
      QPTR   = XYU(IXYU+ 4)
      QQTR   = XYU(IXYU+ 5)
      IMT1   = XYU(IXYU+ 6)
      IMT2   = XYU(IXYU+ 7)
      QPCU   = XYU(IXYU+ 8)
      QPFE   = XYU(IXYU+ 9)
      VR11   = XYU(IXYU+10)
      VX11   = XYU(IXYU+11)
      VR22   = XYU(IXYU+12)
      VX22   = XYU(IXYU+13)
      VR1T   = XYU(IXYU+14)
      VX1T   = XYU(IXYU+15)
      VR2T   = XYU(IXYU+16)
      VX2T   = XYU(IXYU+17)
      ETA0   = XYU(IXYU+18)
      SIN1   = JFLOLOG(XYU(IXYU+19))
      SIN2   = JFLOLOG(XYU(IXYU+20))
      OMTI   = XYU(IXYU+21)
      STRA   = JFLOLOG(XYU(IXYU+22))
      MALF   = NINT(XYU(IXYU+23))
C
      VBASE1 = DATI(IPD   )
      VN1MX  = DATI(IPD+ 1)
      VBASE2 = DATI(IPD+ 2)
      VCC    = DATI(IPD+ 3)
      QBASE  = DATI(IPD+ 4)
      QNTRA  = DATI(IPD+ 5)
      QPFER  = DATI(IPD+ 6)
      QPCC   = DATI(IPD+ 7)
      I0     = DATI(IPD+ 8)
      OMBA   = DATI(IPD+ 9)
C$*$
C
C---Definizione variabili utili per il calcolo dei residui
C
C--- VV2MX=massima variazione tensione lato BT(2), calcolata dalla massima  
C    variazione del numero di spire primario VNIMX
C  
C      VV2MX  = ABS((1./(1.+VN1MX))-1.)
C   
      CT     = QNTRA/QBASE
C
C---SIN1,SIN2=var logiche stato interruttori (SIN1=vero-->inter chiuso)
C
C---Rapporto di trasformazione in [pu]
C
      AM     = (1.+(2*ETA0-1.)*VN1MX/2.)      
      XCC    = VCC
      RCC    = QPCC
      XC     = XCC*OMTI/2.*(1.+AM**2.)
      RC     = RCC/2.*(1.+AM**2.)
      GC     = RC/(RC**2.+XC**2.)
      BC     = XC/(RC**2.+XC**2.)
C       
       IF(MALF.EQ.1) THEN
        SIN1 = .FALSE.
       ELSE IF(MALF.EQ.2) THEN
        AM=1.666667
       ENDIF
C
C---calcolo residui
C
C
      IF(OMTI.GT..01)THEN
C
C---calcolo corrente a vuoto primaria (1)
C
       I0R1   = VR1T*QPFER+VX1T*(SQRT(I0**2.-QPFER**2.))/OMTI
       I0X1   = VX1T*QPFER-VR1T*(SQRT(I0**2.-QPFER**2.))/OMTI      
C
C---calcolo corrente a vuoto secondaria (2)
C
       I0R2   = VR2T*QPFER+VX2T*(SQRT(I0**2.-QPFER**2.))/OMTI
       I0X2   = VX2T*QPFER-VR2T*(SQRT(I0**2.-QPFER**2.))/OMTI      
C
      ELSE
C
C---calcolo corrente a vuoto primaria (1)
C
       I0R1   = VR1T*QPFER
       I0X1   = VX1T*QPFER
C
C
C---calcolo corrente a vuoto secondaria (2)
C
       I0R2   = VR2T*QPFER
       I0X2   = VX2T*QPFER
C
      ENDIF
C
C---calcolo corrente ausiliaria 
C
       IAR    = (VR1T-AM*VR2T)*GC+(VX1T-AM*VX2T)*BC
       IAX    = -(VR1T-AM*VR2T)*BC+(VX1T-AM*VX2T)*GC
C
C
C
       IF((SIN1.AND.SIN2).AND.STRA) THEN
C       
C--residuo n.  1 (equazione algebrica)   *******
         RNI(1) = IRT1+(I0R1+IAR)*CT
C
C--residuo n.  2 (equazione algebrica)   *******
         RNI(2) = IXT1+(I0X1+IAX)*CT
C
C--residuo n.  3 (equazione algebrica)   *******
         RNI(3) = IRT2-AM*IAR*CT
C
C--residuo n.  4 (equazione algebrica)   *******
         RNI(4) = IXT2-AM*IAX*CT
C
C--residuo n.  5 (equazione algebrica)   *******
         RNI(5) = QPTR-VR2T*IRT2-VX2T*IXT2
C
C--residuo n.  6 (equazione algebrica)   *******
         RNI(6) = QQTR-VX2T*IRT2+VR2T*IXT2
C
C--residuo n.  7 (equazione algebrica)   *******
         RNI(7) = IMT1-SQRT(3.*((IRT1/CT)**2.+(IXT1/CT)**2.))
C
C--residuo n.  8 (equazione algebrica)   *******
         RNI(8) = IMT2-SQRT(3.*((IRT2/CT)**2.+(IXT2/CT)**2.))
C
C--residuo n.  9 (equazione algebrica)   *******
         RNI(9) = QPCU-RC*(IMT1**2.)/3.
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(10) = QPFE-(VR1T**2.+VX1T**2.)*QPFER
C
C--residuo n.  11 (equazione algebrica)   *******
         RNI(11) = VR11-VR1T
C
C--residuo n.  12 (equazione algebrica)   *******
         RNI(12) = VX11-VX1T
C
C--residuo n.  13 (equazione algebrica)   *******
         RNI(13) = VR22-VR2T
C
C--residuo n.  14 (equazione algebrica)   *******
         RNI(14) = VX22-VX2T
C
        ELSE IF ((SIN1.AND..NOT.SIN2).AND.STRA) THEN
C
C
C--residuo n.  1 (equazione algebrica)   *******
         RNI(1) = IRT1+I0R1*CT
C
C--residuo n.  2 (equazione algebrica)   *******
         RNI(2) = IXT1+I0X1*CT
C
C--residuo n.  3 (equazione algebrica)   *******
         RNI(3) = IRT2
C
C--residuo n.  4 (equazione algebrica)   *******
         RNI(4) = IXT2
C
C--residuo n.  5 (equazione algebrica)   *******
         RNI(5) = QPTR
C
C--residuo n.  6 (equazione algebrica)   *******
         RNI(6) = QQTR
C
C--residuo n.  7 (equazione algebrica)   *******
         RNI(7) = IMT1-SQRT(3.*((IRT1/CT)**2.+(IXT1/CT)**2.))
C
C--residuo n.  8 (equazione algebrica)   *******
         RNI(8) = IMT2
C
C--residuo n.  9 (equazione algebrica)   *******
         RNI(9) = QPCU
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(10) = QPFE-(VR1T**2.+VX1T**2.)*QPFER
C
C--residuo n.  11 (equazione algebrica)   *******
         RNI(11) = VR11-VR1T
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(12) = VX11-VX1T
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(13) = VR22-VR1T/AM
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(14) = VX22-VX1T/AM

C
C
        ELSE IF((.NOT.SIN1.AND.SIN2).AND.STRA) THEN
C
C 
C--residuo n.  1 (equazione algebrica)   *******
         RNI(1) = IRT1
C
C--residuo n.  2 (equazione algebrica)   *******
         RNI(2) = IXT1
C
C--residuo n.  3 (equazione algebrica)   *******
         RNI(3) = IRT2+I0R2*CT
C
C--residuo n.  4 (equazione algebrica)   *******
         RNI(4) = IXT2+I0X2*CT
C
C--residuo n.  5 (equazione algebrica)   *******
         RNI(5) = QPTR
C
C--residuo n.  6 (equazione algebrica)   *******
         RNI(6) = QQTR
C
C--residuo n.  7 (equazione algebrica)   *******
         RNI(7) = IMT1
C
C--residuo n.  8 (equazione algebrica)   *******
         RNI(8) = IMT2-SQRT(3.*((IRT2/CT)**2.+(IXT2/CT)**2.))
C
C--residuo n.  9 (equazione algebrica)   *******
         RNI(9) = QPCU
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(10) = QPFE-(VR2T**2.+VX2T**2.)*QPFER
C
C--residuo n.  11 (equazione algebrica)   *******
         RNI(11) = VR11-AM*VR2T
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(12) = VX11-AM*VX2T
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(13) = VR22-VR2T
C
C--residuo n.  10 (equazione algebrica)   *******
         RNI(14) = VX22-VX2T
C
C
        ELSE
C
C
C--residuo n.  1 (equazione algebrica)   *******
        RNI(1) = IRT1
C
C--residuo n.  2 (equazione algebrica)   *******
        RNI(2) = IXT1
C
C--residuo n.  3 (equazione algebrica)   *******
        RNI(3) = IRT2
C
C--residuo n.  4 (equazione algebrica)   *******
        RNI(4) = IXT2
C
C--residuo n.  5 (equazione algebrica)   *******
        RNI(5) = QPTR
C
C--residuo n.  6 (equazione algebrica)   *******
        RNI(6) = QQTR
C
C--residuo n.  7 (equazione algebrica)   *******
        RNI(7) = IMT1
C
C--residuo n.  8 (equazione algebrica)   *******
        RNI(8) = IMT2
C
C--residuo n.  9 (equazione algebrica)   *******
        RNI(9) = QPCU
C
C--residuo n.  10 (equazione algebrica)   *******
        RNI(10) = QPFE
C
C--residuo n.  11 (equazione algebrica)   *******
        RNI(11) = VR11
C
C--residuo n.  10 (equazione algebrica)   *******
        RNI(12) = VX11
C
C--residuo n.  10 (equazione algebrica)   *******
        RNI(13) = VR22
C
C--residuo n.  10 (equazione algebrica)   *******
        RNI(14) = VX22

C
       ENDIF
C
C
C
C
      RETURN
      END
C
C
C
      SUBROUTINE TRAFI3 (IFO,IOB,DEBL)
C
      COMMON/TRAF01/IBLOC
      COMMON/TRAF02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'TRAF'/
C
      CALL TRAFI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 14
      NINGRE = 10
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('IRT1',A4,2X,
     $  57H--UA-- CORRENTE REALE USCENTE LATO 1  [A]                )
      WRITE(IFO,3002)IOB
 3002 FORMAT('IXT1',A4,2X,
     $  57H--UA-- CORRENTE IMMAG USCENTE LATO 1  [A]                )
      WRITE(IFO,3003)IOB
 3003 FORMAT('IRT2',A4,2X,
     $  57H--UA-- CORRENTE REALE USCENTE LATO 2  [A]                )
      WRITE(IFO,3004)IOB
 3004 FORMAT('IXT2',A4,2X,
     $  57H--UA-- CORRENTE IMMAG USCENTE LATO 2  [A]                )
      WRITE(IFO,3005)IOB
 3005 FORMAT('QPTR',A4,2X,
     $  57H--UA-- POTENZA ATTIVA USCENTE LATO 2  [W]                )
      WRITE(IFO,3006)IOB
 3006 FORMAT('QQTR',A4,2X,
     $  57H--UA-- POTENZA REATTIVA USCENTE LATO 2 [W]               )
      WRITE(IFO,3007)IOB
 3007 FORMAT('IMT1',A4,2X,
     $  57H--UA-- CORRENTE USCENTE (1)/CORRENTE NOMINALE (1) [%]    )
      WRITE(IFO,3008)IOB
 3008 FORMAT('IMT2',A4,2X,
     $  57H--UA-- CORRENTE USCENTE (2)/CORRENTE NOMINALE (2) [%]    )
      WRITE(IFO,3009)IOB
 3009 FORMAT('QPCU',A4,2X,
     $  57H--UA-- PERDITE NEL RAME [w]                              )
      WRITE(IFO,3010)IOB
 3010 FORMAT('QPFE',A4,2X,
     $  57H--UA-- PERDITE NEL FERRO [w]                             )
      WRITE(IFO,3011)IOB
 3011 FORMAT('UR11',A4,2X,
     $  57H--UA-- TENSIONE REALE AI MORSETTI LATO 1  [V]            )
      WRITE(IFO,3012)IOB
 3012 FORMAT('UX11',A4,2X,
     $  57H--UA-- TENSIONE IMMAG AI MORSETTI LATO 1  [V]            )
      WRITE(IFO,3013)IOB
 3013 FORMAT('UR22',A4,2X,
     $  57H--UA-- TENSIONE REALE AI MORSETTI LATO 2  [V]            )
      WRITE(IFO,3014)IOB
 3014 FORMAT('UX22',A4,2X,
     $  57H--UA-- TENSIONE IMMAG AI MORSETTI LATO 2  [V]            )
      WRITE(IFO,3016)IOB
 3016 FORMAT('UR1T',A4,2X,
     $  57H--IN-- TENSIONE REALE LATO 1  [V]                        )
      WRITE(IFO,3017)IOB
 3017 FORMAT('UX1T',A4,2X,
     $  57H--IN-- TENSIONE IMMAG LATO 1  [V]                        )
      WRITE(IFO,3018)IOB
 3018 FORMAT('UR2T',A4,2X,
     $  57H--IN-- TENSIONE REALE LATO 2  [V]                        )
      WRITE(IFO,3019)IOB
 3019 FORMAT('UX2T',A4,2X,
     $  57H--IN-- TENSIONE IMMAG LATO 2  [V]                        )
      WRITE(IFO,3020)IOB
 3020 FORMAT('ETA0',A4,2X,
     $  57H--IN-- PERCENTUALE VARIAZIONE DI TENSIONE BT VOLUTA [%]  )
      WRITE(IFO,3021)IOB
 3021 FORMAT('SIN1',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE LATO 1 (1=CHIUSO)              )
      WRITE(IFO,3022)IOB
 3022 FORMAT('SIN2',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE LATO 2 (1=CHIUSO)              )
      WRITE(IFO,3023)IOB
 3023 FORMAT('OMTI',A4,2X,
     $  57H--IN-- PULSAZIONE INGRESSO TRASFORMATORE [rad/sec]       )
      WRITE(IFO,3024)IOB
 3024 FORMAT('STRA',A4,2X,
     $  57H--IN-- STATO DEL TRASFORMATORE (0-->isolato)             )
      WRITE(IFO,3025)IOB
 3025 FORMAT('XMAL',A4,2X,
     $  57H--IN-- Transformer malfunctions                          )
C
      RETURN
      END
C
C
C
      SUBROUTINE TRAFI4 (IOB,MOD)
      COMMON/TRAF01/IBLOC
      COMMON/TRAF02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE TRAFD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---TRASFORMATORE RAPP. VARIABILE
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C$*$
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO IRT1
C
C---descrizione equazione IRT1 in stazionario (max. 50 car)
C      SIGNEQ ( 1) = 
C
C---unita` di misura residuo IRT1 (max. 10 car)
C      UNITEQ ( 1) = 
C
C---costante di normalizzazione residuo IRT1 in stazionario
C      COSNOR ( 1) = 
C
C---topologia jacobiano in stazionario per il residuo IRT1
C------dipendenza dalla variabile IRT1
      ITOPVA ( 1, 1) = 1
C------dipendenza dalla variabile VR1T
      ITOPVA ( 1,15) = 1
C------dipendenza dalla variabile VX1T
      ITOPVA ( 1,16) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA ( 1,17) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA ( 1,18) = 1
C------dipendenza dalla variabile ETA0
      ITOPVA ( 1,18) = 1
C------dipendenza dalla variabile OMTI
      ITOPVA ( 1,22) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO IXT1
C
C---descrizione equazione IXT1 in stazionario (max. 50 car)
C      SIGNEQ ( 2) = 
C
C---unita` di misura residuo IXT1 (max. 10 car)
C      UNITEQ ( 2) = 
C
C---costante di normalizzazione residuo IXT1 in stazionario
C      COSNOR ( 2) = 
C
C---topologia jacobiano in stazionario per il residuo IXT1
C------dipendenza dalla variabile IXT1
      ITOPVA ( 2, 2) = 1
C------dipendenza dalla variabile VR1T
      ITOPVA ( 2,15) = 1
C------dipendenza dalla variabile VX1T
      ITOPVA ( 2,16) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA ( 2,17) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA ( 2,18) = 1
C------dipendenza dalla variabile ETA0
      ITOPVA ( 2,18) = 1
C------dipendenza dalla variabile OMTI
      ITOPVA ( 2,22) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO IRT2
C
C---descrizione equazione IRT2 in stazionario (max. 50 car)
C      SIGNEQ ( 3) = 
C
C---unita` di misura residuo IRT2 (max. 10 car)
C      UNITEQ ( 3) = 
C
C---costante di normalizzazione residuo IRT2 in stazionario
C      COSNOR ( 3) = 
C
C---topologia jacobiano in stazionario per il residuo IRT2
C------dipendenza dalla variabile IRT2
      ITOPVA ( 3, 3) = 1
C------dipendenza dalla variabile VR1T
      ITOPVA ( 3,15) = 1
C------dipendenza dalla variabile VX1T
      ITOPVA ( 3,16) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA ( 3,17) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA ( 3,18) = 1
C------dipendenza dalla variabile ETA0
      ITOPVA ( 3,18) = 1
C------dipendenza dalla variabile OMTI
      ITOPVA ( 3,22) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO IXT2
C
C---descrizione equazione IXT2 in stazionario (max. 50 car)
C      SIGNEQ ( 4) = 
C
C---unita` di misura residuo IXT2 (max. 10 car)
C      UNITEQ ( 4) = 
C
C---costante di normalizzazione residuo IXT2 in stazionario
C      COSNOR ( 2) = 
C
C---topologia jacobiano in stazionario per il residuo IRT1
C------dipendenza dalla variabile IRT1
      ITOPVA ( 4, 4) = 1
C------dipendenza dalla variabile VR1T
      ITOPVA ( 4,15) = 1
C------dipendenza dalla variabile VX1T
      ITOPVA ( 4,16) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA ( 4,17) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA ( 4,18) = 1
C------dipendenza dalla variabile ETA0
      ITOPVA ( 4,18) = 1
C------dipendenza dalla variabile OMTI
      ITOPVA ( 4,22) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO QPTR
C
C---descrizione equazione QPTR in stazionario (max. 50 car)
C      SIGNEQ ( 5) = 
C
C---unita` di misura residuo QPTR (max. 10 car)
C      UNITEQ ( 5) = 
C
C---costante di normalizzazione residuo QPTR in stazionario
C      COSNOR ( 5) = 
C
C---topologia jacobiano in stazionario per il residuo QPTR
C------dipendenza dalla variabile IRT2
      ITOPVA ( 5, 3) = 1
C------dipendenza dalla variabile IXT2
      ITOPVA ( 5, 4) = 1
C------dipendenza dalla variabile QPTR
      ITOPVA ( 5, 5) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA ( 5,17) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA ( 5,18) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO QQTR
C
C---descrizione equazione QQTR in stazionario (max. 50 car)
C      SIGNEQ ( 6) = 
C
C---unita` di misura residuo QQTR (max. 10 car)
C      UNITEQ ( 6) = 
C
C---costante di normalizzazione residuo QQTR in stazionario
C      COSNOR ( 6) = 
C
C---topologia jacobiano in stazionario per il residuo QQTR
C------dipendenza dalla variabile IRT2
      ITOPVA ( 6, 3) = 1
C------dipendenza dalla variabile IXT2
      ITOPVA ( 6, 4) = 1
C------dipendenza dalla variabile QQTR
      ITOPVA ( 6, 6) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA ( 6,17) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA ( 6,18) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO IMT1
C
C---descrizione equazione IMT1 in stazionario (max. 50 car)
C      SIGNEQ ( 7) = 
C
C---unita` di misura residuo IMT1 (max. 10 car)
C      UNITEQ ( 7) = 
C
C---costante di normalizzazione residuo IMT1 in stazionario
C      COSNOR ( 7) = 
C
C---topologia jacobiano in stazionario per il residuo IMT1
C------dipendenza dalla variabile IRT1
      ITOPVA ( 7, 1) = 1
C------dipendenza dalla variabile IXT1
      ITOPVA ( 7, 1) = 1
C------dipendenza dalla variabile IMT1
      ITOPVA ( 7, 7) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO IMT2
C
C---descrizione equazione IMT2 in stazionario (max. 50 car)
C      SIGNEQ ( 8) = 
C
C---unita` di misura residuo IMT2 (max. 10 car)
C      UNITEQ ( 8) = 
C
C---costante di normalizzazione residuo IMT2 in stazionario
C      COSNOR ( 8) = 
C
C---topologia jacobiano in stazionario per il residuo IMT2
C------dipendenza dalla variabile IRT2
      ITOPVA ( 8, 3) = 1
C------dipendenza dalla variabile IXT2
      ITOPVA ( 8, 4) = 1
C------dipendenza dalla variabile IMT2
      ITOPVA ( 8, 8) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO QPCU
C
C---descrizione equazione QPCU in stazionario (max. 50 car)
C      SIGNEQ ( 9) = 
C
C---unita` di misura residuo QPCU (max. 10 car)
C      UNITEQ ( 9) = 
C
C---costante di normalizzazione residuo QPCU in stazionario
C      COSNOR ( 9) = 
C
C---topologia jacobiano in stazionario per il residuo QPCU
C------dipendenza dalla variabile IMT1
      ITOPVA ( 9, 7) = 1
C------dipendenza dalla variabile QPCU
      ITOPVA ( 9, 9) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO QPFE
C
C---descrizione equazione QPFE in stazionario (max. 50 car)
C      SIGNEQ ( 10) = 
C
C---unita` di misura residuo QPFE (max. 10 car)
C      UNITEQ ( 10) = 
C
C---costante di normalizzazione residuo QPFE in stazionario
C      COSNOR ( 10) = 
C
C---topologia jacobiano in stazionario per il residuo QPFE
C------dipendenza dalla variabile QPFE
      ITOPVA (10,10) = 1
C------dipendenza dalla variabile VR1T
      ITOPVA (10,15) = 1
C------dipendenza dalla variabile VX1T
      ITOPVA (10,16) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO VR11
C
C---descrizione equazione VR11 in stazionario (max. 50 car)
C      SIGNEQ (11) = 
C
C---unita` di misura residuo VR11 (max. 10 car)
C      UNITEQ (11) = 
C
C---costante di normalizzazione residuo VR11 in stazionario
C      COSNOR (11) = 
C
C---topologia jacobiano in stazionario per il residuo VR11
C------dipendenza dalla variabile VR11
      ITOPVA (11,11) = 1
C------dipendenza dalla variabile VR1T
      ITOPVA (11,15) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO VX11
C
C---descrizione equazione VX11 in stazionario (max. 50 car)
C      SIGNEQ (12) = 
C
C---unita` di misura residuo VX11 (max. 10 car)
C      UNITEQ (12) = 
C
C---costante di normalizzazione residuo VX11 in stazionario
C      COSNOR (12) = 
C
C---topologia jacobiano in stazionario per il residuo VX11
C------dipendenza dalla variabile VX11
      ITOPVA (12,12) = 1
C------dipendenza dalla variabile VX1T
      ITOPVA (12,16) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO VR22
C
C---descrizione equazione VR22 in stazionario (max. 50 car)
C      SIGNEQ (13) = 
C
C---unita` di misura residuo VR22 (max. 10 car)
C      UNITEQ (13) = 
C
C---costante di normalizzazione residuo VR22 in stazionario
C      COSNOR (13) = 
C
C---topologia jacobiano in stazionario per il residuo VR22
C------dipendenza dalla variabile VR22
      ITOPVA (13,13) = 1
C------dipendenza dalla variabile VR2T
      ITOPVA (13,17) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO VX22
C
C---descrizione equazione VX22 in stazionario (max. 50 car)
C      SIGNEQ (14) = 
C
C---unita` di misura residuo VX22 (max. 10 car)
C      UNITEQ (14) = 
C
C---costante di normalizzazione residuo VX22 in stazionario
C      COSNOR (14) = 
C
C---topologia jacobiano in stazionario per il residuo VX22
C------dipendenza dalla variabile VX22
      ITOPVA (14,14) = 1
C------dipendenza dalla variabile VX2T
      ITOPVA (14,18) = 1
      RETURN
      END
