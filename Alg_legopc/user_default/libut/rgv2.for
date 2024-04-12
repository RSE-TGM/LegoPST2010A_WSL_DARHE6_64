C-------------------------------------------------------------------------
C-----                                                               -----
C-----                            MODULO RGV2                        -----
C-----                                                               -----
C-----                   REGOLATORE DI TENSIONE PRIMARIO             -----
C-----                                                               -----
C-----               CON LIMITI IN SOVRA E SOTTOECCITAZIONE          -----
C-----                                                               -----
C-----                       (CURVE DI CAPABILITY)                   -----
C-----                                                               -----
C-----               Ultima correzione:  04.06.98      -----
C-------------------------------------------------------------------------
C
      SUBROUTINE RGV2I2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
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
      REAL VOEX, VUEX, VF11, VOE1, VUE1, VRIF, VF00, VR00, VX00        !SNGL
      REAL QATT, QREA, IFLD, VRF0, VPS0, VMMA, IFL, VFAC , IFLD0       !SNGL
C
       QBASE=H0*W0           !POTENZA DI BASE
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'T1_s    '
     $             ,'T2_s    '
     $             ,'GAIN    '
     $             ,'Tover_s '
     $             ,'Tunder_s'
     $             ,'Iflim_A '
     $             ,'Qrif0_VA'
     $             ,'beta    '
     $             ,'VNOM_V  '
      WRITE(14,500) 'VBECC_V '
     $             ,'VC1_pum '
     $             ,'VC2_pum '
     $             ,'RF_Ohm  '
     $             ,'PU?_1=SI'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) T1
     $            ,T2
     $            ,GAIN
     $            ,TO
     $            ,TU
     $            ,IFL
     $            ,QV0
     $            ,BETA
     $            ,VNOM
      READ(14,501) VBEC
     $            ,VC1
     $            ,VC2
     $            ,RF
     $            ,PU
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = T1
      DATI(ID2+ 1) = T2
      DATI(ID2+ 2) = GAIN
      DATI(ID2+ 3) = TO
      DATI(ID2+ 4) = TU
      DATI(ID2+ 5) = IFL
      DATI(ID2+ 6) = QV0
      DATI(ID2+ 7) = BETA
      DATI(ID2+ 8) = VNOM
      DATI(ID2+ 9) = VBEC
      DATI(ID2+10) = VC1
      DATI(ID2+11) = VC2
      DATI(ID2+12) = RF
      DATI(ID2+13) = PU
      ID2 = ID2+13
C
C---costanti di normalizzazione
C 
C---CORRENTE DI BASE PER LA CORRENTE DI ECCITAZIONE---
C
      IFLD0=VBEC/RF
C
C
      IF (PU.EQ.1.) THEN
       DO I=1,15
        CNXYU(IV1+I-1)=1.
       END DO
      ELSE
       CNXYU(IV1   ) = VNOM
       CNXYU(IV1+ 1) = VNOM
       CNXYU(IV1+ 2) = VBEC
       CNXYU(IV1+ 3) = VNOM
       CNXYU(IV1+ 4) = VNOM
       CNXYU(IV1+ 5) = VNOM
       CNXYU(IV1+ 6) = VBEC
       CNXYU(IV1+ 7) = VBEC
       CNXYU(IV1+ 8) = VNOM
       CNXYU(IV1+ 9) = 1.
       CNXYU(IV1+10) = QBASE
       CNXYU(IV1+11) = QBASE
       CNXYU(IV1+12) = IFLD0
       CNXYU(IV1+13) = VNOM
       CNXYU(IV1+14) = VNOM
      END IF
C
      RETURN
      END
C
C
C
      SUBROUTINE RGV2C1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL RGV2
C
      REAL VOEX, VUEX, VF11, VOE1, VUE1, VRIF, VF00, VR00, VX00        !SNGL
      REAL QATT, QREA, IFLD, VRF0, VPS0, VMMA, IFL, VFAC                 !SNGL
C
C---REAGOLATORE DI TENSIONE
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL RGV2JC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL RGV2 (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL RGV2JC (2,...
C
C      jacobiano numerico  CALL RGV2JC (3,...
C
C$*$
  300 CONTINUE
      CALL RGV2JC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE RGV2JC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL RGV2
C
      REAL VOEX, VUEX, VF11, VOE1, VUE1, VRIF, VF00, VR00, VX00        !SNGL
      REAL QATT, QREA, IFLD, VRF0, VPS0, VMMA, IFL, VFAC                 !SNGL
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
      DO I=1,8
       DO J=1,15
        AJAC(I,J)=1.
       END DO
      END DO
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 3
      NUSCIT = 5
      NINGRE = 7
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,RGV2)
      RETURN
      END
C
C
C
      SUBROUTINE RGV2 (IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL VOEX, VUEX, VF11, VOE1, VUE1, VRIF, VF00, VR00, VX00        !SNGL
      REAL QATT, QREA, IFLD, VRF0, VPS0, VMMA, IFL, VFAC                 !SNGL
C
C---REGOLATORE DI TENSIONE
C   calcolo residui
C
C---decodifica variabili e dati
C
      VOEX   = XYU(IXYU   )
      VUEX   = XYU(IXYU+ 1)
      VF11   = XYU(IXYU+ 2)
      VOE1   = XYU(IXYU+ 3)
      VUE1   = XYU(IXYU+ 4)
      VRIF   = XYU(IXYU+ 5)
      VFAC   = XYU(IXYU+ 6)
      VF00   = XYU(IXYU+ 7)
      VMMA   = XYU(IXYU+ 8)
      FAMA   = XYU(IXYU+ 9)
      QATT   = XYU(IXYU+10)
      QREA   = XYU(IXYU+11)
      IFLD   = XYU(IXYU+12)
      VRF0   = XYU(IXYU+13)
      VPS0   = XYU(IXYU+14)
C
      T1     = DATI(IPD   )
      T2     = DATI(IPD+ 1)
      GAIN   = DATI(IPD+ 2)
      TO     = DATI(IPD+ 3)
      TU     = DATI(IPD+ 4)
      IFL    = DATI(IPD+ 5)
      QV0    = DATI(IPD+ 6)
      BETA   = DATI(IPD+ 7)
      VNOM   = DATI(IPD+ 8)
      VBEC   = DATI(IPD+ 9)
      VC1    = DATI(IPD+10)
      VC2    = DATI(IPD+11)
      RF     = DATI(IPD+12)
      PU     = DATI(IPD+13)
C$*$
C
      QBASE=H0*W0                         !POTENZA DI BASE
C
C---CORRENTE DI BASE PER LA CORRENTE DI ECCITAZIONE---
C
      IFLD0=VBEC/RF
C
C---calcolo residui
C
      IF (KREGIM) THEN
         RNI(1) = VOEX
         RNI(4) = VOE1
      ELSE IF (IFLD.LT.(IFL/IFLD0)) THEN
         RNI(1) = 0.
         RNI(4) = VOE1 !reset del segnale del limitatore in sovraeccitazione
      ELSE
         RNI(1) = (1/TO)*(IFLD-(IFL/IFLD0))
         RNI(4)=VOE1-VOEX
      ENDIF
C    
      IF (KREGIM) THEN
         RNI(2) = VUEX
         RNI(5) = VUE1
      ELSE IF ((QREA-((QV0/QBASE)+QATT*BETA)).GT.0.) THEN
         RNI(2) = 0.
         RNI(5) = VUE1 !reset del segnale in sottoeccitazione
      ELSE 
         RNI(2) = (1/TU)*(QREA-((QV0/QBASE)+QATT*BETA))
         RNI(5) = VUE1-VUEX
      ENDIF
C
      IF (KREGIM) THEN
C         RNI(3) = VF11-GAIN*(1-T2/T1)*(VRIF+VPS0-VMMA)
         RNI(3) = VF11-(1-T2/T1)*VFAC
      ELSE
         RNI(3) = -VF11/T1+GAIN*(1-T2/T1)*(VRIF+VPS0-VMMA)/T1
      ENDIF
C
      RNI(6) = VRF0-VOE1-VUE1-VRIF 
C
      IF (KREGIM) THEN
         RNI(7) = (VFAC-GAIN*(VRIF+VPS0-VMMA))/GAIN
      ELSE
         RNI(7) = (VFAC-VF11-GAIN*T2/T1*(VRIF+VPS0-VMMA))/GAIN
      ENDIF
C
      IF (VFAC.GE.VC1) THEN
         RNI(8) = VF00-VC1*VMMA
      ELSE IF (VFAC.LE.VC2) THEN
         RNI(8) = VF00-VC2*VMMA
      ELSE
         RNI(8) = VF00-VFAC*VMMA
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE RGV2I3 (IFO,IOB,DEBL)
C
      COMMON/RGV201/IBLOC
      COMMON/RGV202/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'RGV2'/
C
      CALL RGV2I4(IOB,MOD)
      NSTATI = 3
      NUSCIT = 5
      NINGRE = 7
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('VOEX',A4,2X,
     $  57H--US-- STATO DEL LIMITATORE SOVRAECCITAZIONE             )
      WRITE(IFO,3002)IOB
 3002 FORMAT('VUEX',A4,2X,
     $  57H--US-- STATO DEL REGOLATORE SOTTOECCITAZIONE             )
      WRITE(IFO,3003)IOB
 3003 FORMAT('VF11',A4,2X,
     $  57H--US-- STATO DEL REGOLATORE AUTOMATICO DI TENSIONE       )
      WRITE(IFO,3004)IOB
 3004 FORMAT('VOE1',A4,2X,
     $  57H--UA-- SEGNALE POST CEILING LIMITATORE SOVRAECCITAZIONE  )
      WRITE(IFO,3005)IOB
 3005 FORMAT('VUE1',A4,2X,
     $  57H--UA-- SEGNALE POST CEILING LIMITATORE SOTTOECCITAZIONE  )
      WRITE(IFO,3006)IOB
 3006 FORMAT('VRIF',A4,2X,
     $  57H--UA-- SEGNALE DI RIFERIMENTO POST LIMITATORI            )
      WRITE(IFO,3015)IOB
 3015 FORMAT('VFAC',A4,2X,
     $  57H--UA-- TENSIONE DI ECCITAZIONE ANTE CEILING              )
      WRITE(IFO,3007)IOB
 3007 FORMAT('VF00',A4,2X,
     $  57H--UA-- TENSIONE DI ECCITAZIONE                           )
      WRITE(IFO,3008)IOB
 3008 FORMAT('VMMA',A4,2X,
     $  57H--IN-- MODULO TENSIONE GENERATORE                        )
      WRITE(IFO,3009)IOB
 3009 FORMAT('FAMA',A4,2X,
     $  57H--IN-- FASE TENSIONE GENERATORE                          )
      WRITE(IFO,3010)IOB
 3010 FORMAT('QATT',A4,2X,
     $  57H--IN-- POTENZA ATTIVA EROGATA DAL GENERATORE             )
      WRITE(IFO,3011)IOB
 3011 FORMAT('QREA',A4,2X,
     $  57H--IN-- POTENZA REATTIVA EROGATA DAL GENERATORE           )
      WRITE(IFO,3012)IOB
 3012 FORMAT('IFLD',A4,2X,
     $  57H--IN-- CORRENTE DI ECCITAZIONE                           )
      WRITE(IFO,3013)IOB
 3013 FORMAT('VRF0',A4,2X,
     $  57H--IN-- TENSIONE DI RIFERIMENTO                           )
      WRITE(IFO,3014)IOB
 3014 FORMAT('VPS0',A4,2X,
     $  57H--IN-- SEGNALE STABILIZZANTE                             )
      RETURN
      END
C
C
C
      SUBROUTINE RGV2I4 (IOB,MOD)
      COMMON/RGV201/IBLOC
      COMMON/RGV202/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE RGV2D1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C---REGOLATORE DI TENSIONE
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
