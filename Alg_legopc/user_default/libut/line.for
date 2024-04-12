C
C********************************************************************
C                                                                    
C     MODULO LINE (LINEA A PI-GRECO)                  
C     Ultime modifiche:  30.03.98
C                                                                    
C********************************************************************
C
      SUBROUTINE LINEI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL IR01, IX01, IR02, IX02, KLIN                                 !SNGL
      REAL IBASE, ZBASE
C      DOUBLE PRECISION IR01, IX01, IR02, IX02, KLIN                     !DBLE
C
C---LINEA A PI-GRECO
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'R_ohm/m '
     $             ,'L_H/m   '
     $             ,'G_S/m   '
     $             ,'C_F/m   '
     $             ,'VNOM_V  '
     $             ,'OMBA_r/s'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) RL
     $            ,XL
     $            ,GTR
     $            ,BTR
     $            ,VNOM
     $            ,OMBA
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C---calcolo corrente e impedenza di base
C
      QBASE=W0*H0
      IBASE=QBASE/(VNOM*SQRT(3.))
      ZBASE=VNOM/IBASE
C
      WRITE(6,*) 'Sono il modulo nuovo'
C
      DATI(ID2   ) = RL/ZBASE
      DATI(ID2+ 1) = XL*OMBA/ZBASE
      DATI(ID2+ 2) = GTR*ZBASE/2.
      DATI(ID2+ 3) = BTR*OMBA*ZBASE/2.
      DATI(ID2+ 4) = QBASE
      DATI(ID2+ 5) = VNOM
      DATI(ID2+ 6) = OMBA
      ID2 = ID2+6
C
C---costanti di normalizzazione
C
 
      CNXYU(IV1   ) = IBASE
      CNXYU(IV1+ 1) = IBASE
      CNXYU(IV1+ 2) = IBASE
      CNXYU(IV1+ 3) = IBASE
      CNXYU(IV1+ 4) = VNOM
      CNXYU(IV1+ 5) = VNOM
      CNXYU(IV1+ 6) = VNOM
      CNXYU(IV1+ 7) = VNOM
      CNXYU(IV1+ 8) = VNOM
      CNXYU(IV1+ 9) = QBASE
      CNXYU(IV1+10) = QBASE
      CNXYU(IV1+11) = QBASE
      CNXYU(IV1+12) = QBASE
      CNXYU(IV1+13) = VNOM
      CNXYU(IV1+14) = VNOM
      CNXYU(IV1+15) = VNOM
      CNXYU(IV1+16) = VNOM
      CNXYU(IV1+17) = 1.
      CNXYU(IV1+18) = 1.
      CNXYU(IV1+19) = 1.
      CNXYU(IV1+20) = OMBA
      CNXYU(IV1+21) = 1.
C
C
      RETURN
      END
C
C
C
      SUBROUTINE LINEC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      COMMON/NEQUAZ/NEQMOD
C
      NEQMOD=8
C
C---LINEA A PI-GRECO
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL LINEJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL LINE (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 CONTINUE
      CALL LINEJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE LINEJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL LINE
C
      REAL IR01, IX01, IR02, IX02, KLIN                                 !SNGL
C      DOUBLE PRECISION IR01, IX01, IR02, IX02, KLIN                     !DBLE
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
      NEQ_TRANS=8
      NVAR=22
      DO I=1,NEQ_TRANS
         DO J=1,NVAR
         IF(J.LT.9.OR.J.GT.13)THEN
         AJAC(I,J)=1.
         ENDIF
         END DO
      ENDDO
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      IF (KREGIM) THEN
         NRIG=13
      ELSE
         NRIG=8
      ENDIF
      NCOL=22
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL LINEJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $              NRIG,NCOL,NSTATI,EPS,EPSLIM,LINE)
      RETURN
      END
C
C
C
      SUBROUTINE LINEJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     $                   NRIG,NCOL,NSTATI,EPS,EPSLIM,RESIDUI)
C
C     routine di calcolo jacobiano numerico
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !
C
      LOGICAL KREGIM
      COMMON/REGIME/KREGIM
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
      EXTERNAL RESIDUI
C
      CALL RESIDUI(3,IXYU,XYU,IPD,DATI,RN)
      DO J=1,NCOL
C*   
      IF(KREGIM.OR.J.LT.9.OR.J.GT.13) THEN
C*     
         VAR=EPS*XYU(IXYU+J-1)
         IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
         DO K=1,NCOL
            CXYU(K)=XYU(IXYU+K-1)
            IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
         ENDDO
         CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
         DO I=1,NRIG
            AJAC(I,J)=(CRN(I)-RN(I))/VAR
            IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
         ENDDO
       ENDIF
      ENDDO
C
      RETURN
      END
C
C
C
      SUBROUTINE LINE (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM
      LOGICAL STL1, STL2, JFLOLOG ,SLIN
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL IR01, IX01, IR02, IX02, KLIN                                 !SNGL
      REAL IRAU, IXAU, IR11, IR22, IX11, IX22
C      DOUBLE PRECISION IR01, IX01, IR02, IX02, KLIN                     !DBLE
C
C---LINEA A PI-GRECO
C   calcolo residui
C
C---decodifica variabili e dati
C
      IR01   = XYU(IXYU   )
      IX01   = XYU(IXYU+ 1)
      IR02   = XYU(IXYU+ 2)
      IX02   = XYU(IXYU+ 3)
      VRL1   = XYU(IXYU+ 4)
      VXL1   = XYU(IXYU+ 5)
      VRL2   = XYU(IXYU+ 6)
      VXL2   = XYU(IXYU+ 7)
      VVLM   = XYU(IXYU+ 8)
      QP01   = XYU(IXYU+ 9)
      QQ01   = XYU(IXYU+10)
      QP02   = XYU(IXYU+11)
      QQ02   = XYU(IXYU+12)
      VR01   = XYU(IXYU+13)
      VX01   = XYU(IXYU+14)
      VR02   = XYU(IXYU+15)
      VX02   = XYU(IXYU+16)
      STL1   = JFLOLOG(XYU(IXYU+17))
      STL2   = JFLOLOG(XYU(IXYU+18))
      KLIN   = XYU(IXYU+19)
      OMLI   = XYU(IXYU+20)
      SLIN   = JFLOLOG(XYU(IXYU+21))
C
      RL     = DATI(IPD   )
      XL     = DATI(IPD+ 1)
      GTR    = DATI(IPD+ 2)
      BTR    = DATI(IPD+ 3)
      QBASE  = DATI(IPD+ 4)
      VNOM   = DATI(IPD+ 5)
      OMBA   = DATI(IPD+ 6)
C
C
C---calcolo residui
C
      IF(KLIN.LE.0.1) KLIN=0.1
C
        YR     = RL/((RL**2.+(XL*OMLI)**2.)*KLIN)
        YX     = -XL*OMLI/((RL**2.+(XL*OMLI)**2.)*KLIN)
        GL     = GTR*KLIN
        BCL    = BTR*OMLI*KLIN
        IRAU   = (VR02-VR01)*YR+(VX01-VX02)*YX
        IXAU   = (VX02-VX01)*YR+(VR02-VR01)*YX
        IR11   = VR01*GL-VX01*BCL
        IX11   = VR01*BCL+VX01*GL
        IR22   = VR02*GL-VX02*BCL
        IX22   = VR02*BCL+VX02*GL
C
      IF ((STL1.AND.STL2).AND.SLIN) THEN
        RNI(1) = IR01-IRAU + IR11
        RNI(2) = IX01-IXAU + IX11
        RNI(3) = IR02+IRAU + IR22
        RNI(4) = IX02+IXAU + IX22
        RNI(5) = VRL1 - VR01 
        RNI(6) = VXL1 - VX01 
        RNI(7) = VRL2 - VR02 
        RNI(8) = VXL2 - VX02 
        IF (KREGIM) THEN
           RNI(9) = VVLM-SQRT((VRL1-VRL2)**2.+(VXL1-VXL2)**2.)
        ELSE
           RNI(9) = SQRT((VRL1-VRL2)**2.+(VXL1-VXL2)**2.)
        ENDIF
      ELSE IF((STL1.AND..NOT.STL2).AND.SLIN) THEN
        RNI(1) = IR01+2*IR11
        RNI(2) = IX01+2*IX11
        RNI(3) = IR02
        RNI(4) = IX02
        RNI(5) = VRL1 - VR01 
        RNI(6) = VXL1 - VX01 
        RNI(7) = VRL2 - VR01 
        RNI(8) = VXL2 - VX01 
        IF (KREGIM) THEN
           RNI(9) = VVLM
        ELSE
           RNI(9) = 0.
        ENDIF
      ELSE IF((.NOT.STL1.AND.STL2).AND.SLIN) THEN
        RNI(1) = IR01
        RNI(2) = IX01 
        RNI(3) = IR02+2*IR22
        RNI(4) = IX02+2*IX22
        RNI(5) = VRL1 - VR02 
        RNI(6) = VXL1 - VX02 
        RNI(7) = VRL2 - VR02 
        RNI(8) = VXL2 - VX02 
        IF (KREGIM) THEN
           RNI(9) = VVLM
        ELSE
           RNI(9) = 0.
        ENDIF
      ELSE
        RNI(1) = IR01 
        RNI(2) = IX01
        RNI(3) = IR02
        RNI(4) = IX02
        RNI(5) = VRL1
        RNI(6) = VXL1
        RNI(7) = VRL2  
        RNI(8) = VXL2
        IF (KREGIM) THEN
           RNI(9) = VVLM
        ELSE
           RNI(9) = 0.
        ENDIF
      ENDIF
C
      IF (KREGIM) THEN
         RNI(10) = QP01-(VRL1*IR01+VXL1*IX01)
         RNI(11) = QQ01-(VXL1*IR01-VRL1*IX01)
         RNI(12) = QP02-(VRL2*IR02+VXL2*IX02)
         RNI(13) = QQ02-(VXL2*IR02-VRL2*IX02)
      ELSE
         RNI(10) = VRL1*IR01+VXL1*IX01
         RNI(11) = VXL1*IR01-VRL1*IX01
         RNI(12) = VRL2*IR02+VXL2*IX02
         RNI(13) = VXL2*IR02-VRL2*IX02
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE LINEI3 (IFO,IOB,DEBL)
C
      COMMON/LINE01/IBLOC
      COMMON/LINE02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'LINE'/
C
      CALL LINEI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 13
      NINGRE = 9
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('IR01',A4,2X,
     $  57H--UA-- CORRENTE REALE LATO 1 [A]                         )
      WRITE(IFO,3002)IOB
 3002 FORMAT('IX01',A4,2X,
     $  57H--UA-- CORRENTE IMMAGINARIA LATO 1 [A]                   )
      WRITE(IFO,3003)IOB
 3003 FORMAT('IR02',A4,2X,
     $  57H--UA-- CORRENTE REALE LATO 2 [A]                         )
      WRITE(IFO,3004)IOB
 3004 FORMAT('IX02',A4,2X,
     $  57H--UA-- CORRENTE IMMAGINARIA LATO 2  [A]                  )
      WRITE(IFO,3005)IOB
 3005 FORMAT('URL1',A4,2X,
     $  57H--UA-- TENSIONE REALE AI MORSETTI LATO 1 [V]             )
      WRITE(IFO,3006)IOB
 3006 FORMAT('UXL1',A4,2X,
     $  57H--UA-- TENSIONE IMMAGINARIA AI MORSETTI LATO 1 [V]       )
      WRITE(IFO,3007)IOB
 3007 FORMAT('URL2',A4,2X,
     $  57H--UA-- TENSIONE REALE AI MORSETTI LATO 2 [V]             )
      WRITE(IFO,3008)IOB
 3008 FORMAT('UXL2',A4,2X,
     $  57H--UA-- TENSIONE IMMAGINARIA AI MORSETTI LATO 2 [V]       )
      WRITE(IFO,3010)IOB
 3010 FORMAT('UULM',A4,2X,
     $  57H--UA-- MODULO DELLA CADUTA DI TENSIONE IN LINEA [V]      )
      WRITE(IFO,3011)IOB
 3011 FORMAT('QP01',A4,2X,
     $  57H--UA-- POTENZA ATTIVA LATO 1 [w]                         )
      WRITE(IFO,3012)IOB
 3012 FORMAT('QQ01',A4,2X,
     $  57H--UA-- POTENZA REATTIVA LATO 1 [w]                       )
      WRITE(IFO,3013)IOB
 3013 FORMAT('QP02',A4,2X,
     $  57H--UA-- POTENZA ATTIVA LATO 2 [w]                         )
      WRITE(IFO,3014)IOB
 3014 FORMAT('QQ02',A4,2X,
     $  57H--UA-- POTENZA REATTIVA LATO 2 [w]                       )
      WRITE(IFO,3015)IOB
 3015 FORMAT('UR01',A4,2X,
     $  57H--IN-- TENSIONE REALE LATO 1 [V]                         )
      WRITE(IFO,3016)IOB
 3016 FORMAT('UX01',A4,2X,
     $  57H--IN-- TENSIONE IMMAGINARIA LATO 1 [V]                   )
      WRITE(IFO,3017)IOB
 3017 FORMAT('UR02',A4,2X,
     $  57H--IN-- TENSIONE REALE LATO 2 [V]                         )
      WRITE(IFO,3018)IOB
 3018 FORMAT('UX02',A4,2X,
     $  57H--IN-- TENSIONE IMMAGINARIA LATO 2 [V]                   )
      WRITE(IFO,3019)IOB
 3019 FORMAT('STL1',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE LATO 1 (STL1=1-->INT CHIUSO)   )
      WRITE(IFO,3020)IOB
 3020 FORMAT('STL2',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE LATO 2 (STL2=1-->INT CHIUSO)   )
      WRITE(IFO,3021)IOB
 3021 FORMAT('KLIN',A4,2X,
     $  57H--IN-- LUNGHEZZA DELLA LINEA [m]                         )
      WRITE(IFO,3022)IOB
 3022 FORMAT('OMLI',A4,2X,
     $  57H--IN-- PULSAZIONE INGRESSO LINEA [rad/sec]               )
      WRITE(IFO,3023)IOB
 3023 FORMAT('SLIN',A4,2X,
     $  57H--IN-- CONDIZIONE DEL BLOCCO LINEA                       )
      RETURN
      END
C
C
C
      SUBROUTINE LINEI4 (IOB,MOD)
      COMMON/LINE01/IBLOC
      COMMON/LINE02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE LINED1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---LINEA A PI-GRECO
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
