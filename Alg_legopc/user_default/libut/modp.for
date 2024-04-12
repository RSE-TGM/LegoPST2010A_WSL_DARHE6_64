      SUBROUTINE MODPI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL M1, M2                                                       !SNGL
C      DOUBLE PRECISION M1, M2                                           !DBLE
C
C---modulo di prova
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'TAU1    '
     $             ,'TAU2    '
     $             ,'GUAD1   '
     $             ,'GUAD2   '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) T1
     $            ,T2
     $            ,M1
     $            ,M2
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = T1
      DATI(ID2+ 1) = T2
      DATI(ID2+ 2) = M1
      DATI(ID2+ 3) = M2
      ID2 = ID2+3
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = 1.
      CNXYU(IV1+ 1) = 1.
      CNXYU(IV1+ 2) = 1.
      CNXYU(IV1+ 3) = 1.
      CNXYU(IV1+ 4) = 1.
C
      RETURN
      END
C
C
C
      SUBROUTINE MODPC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL MODP
C
      REAL M1, M2                                                       !SNGL
C      DOUBLE PRECISION M1, M2                                           !DBLE
C
C---modulo di prova
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL MODPJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL MODP (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL MODPJC (2,...
C
C      jacobiano numerico  CALL MODPJC (3,...
C
C$*$
  300 CONTINUE
      CALL MODPJC (2,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE MODPJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL MODP
C
      REAL M1, M2                                                       !SNGL
C      DOUBLE PRECISION M1, M2                                           !DBLE
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (di stato):
C   ---dipendenza da X1XX
      AJAC(1,1)=1.
C   ---dipendenza da U1XX
      AJAC(1,4)=1.
C
C---equazione n.2 (di stato):
C   ---dipendenza da X2XX
      AJAC(2,2)=1.
C   ---dipendenza da U2XX
      AJAC(2,5)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da X1XX
      AJAC(3,1)=1.
C   ---dipendenza da X2XX
      AJAC(3,2)=1.
C   ---dipendenza da YXXX
      AJAC(3,3)=1.
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
      X1XX   = XYU(IXYU   )
      X2XX   = XYU(IXYU+ 1)
      YXXX   = XYU(IXYU+ 2)
      U1XX   = XYU(IXYU+ 3)
      U2XX   = XYU(IXYU+ 4)
C
      T1     = DATI(IPD   )
      T2     = DATI(IPD+ 1)
      M1     = DATI(IPD+ 2)
      M2     = DATI(IPD+ 3)
C
C$*$
C
C--derivata del residuo n.  1 (equazione di stato)   *******
C     --- rispetto alla variabile X1XX
       AJAC(1,1) = -(1/T1)
C     --- rispetto alla variabile U1XX
       AJAC(1,4) = M1/T1
C
C--derivata del residuo n.  2 (equazione di stato)   *******
C     --- rispetto alla variabile X2XX
       AJAC(2,2) = -(1/T2)
C     --- rispetto alla variabile U2XX
       AJAC(2,5) = M2/T2
C
C--derivata del residuo n.  3 (equazione algebrica)   *******
C     --- rispetto alla variabile X1XX
       AJAC(3,1) = 1.
C     --- rispetto alla variabile X2XX
       AJAC(3,2) = 1.
C     --- rispetto alla variabile YXXX
       AJAC(3,3) = -1.
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 2
      NUSCIT = 1
      NINGRE = 2
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,MODP)
      RETURN
      END
C
C
C
      SUBROUTINE MODP (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
      REAL M1, M2                                                       !SNGL
C      DOUBLE PRECISION M1, M2                                           !DBLE
C
C---modulo di prova
C   calcolo residui
C
C---decodifica variabili e dati
C
      X1XX   = XYU(IXYU   )
      X2XX   = XYU(IXYU+ 1)
      YXXX   = XYU(IXYU+ 2)
      U1XX   = XYU(IXYU+ 3)
      U2XX   = XYU(IXYU+ 4)
C
      T1     = DATI(IPD   )
      T2     = DATI(IPD+ 1)
      M1     = DATI(IPD+ 2)
      M2     = DATI(IPD+ 3)
C$*$
C
C---calcolo residui
C
C--residuo n.  1 (equazione di stato)   *******
      RNI(1) = (-1/T1)*X1XX+M1*U1XX/T1
C
C--residuo n.  2 (equazione di stato)   *******
      RNI(2) = (-1/T2)*X2XX+M2*U2XX/T2
C
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3) = YXXX-X1XX-X2XX
C
      RETURN
      END
C
C
C
      SUBROUTINE MODPI3 (IFO,IOB,DEBL)
C
      COMMON/MODP01/IBLOC
      COMMON/MODP02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'MODP'/
C
      CALL MODPI4(IOB,MOD)
      NSTATI = 2
      NUSCIT = 1
      NINGRE = 2
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('X1XX',A4,2X,
     $  57H--US-- Variabile di stato  n.1                           )
      WRITE(IFO,3002)IOB
 3002 FORMAT('X2XX',A4,2X,
     $  57H--US-- Variabile di stato  n.2                           )
      WRITE(IFO,3003)IOB
 3003 FORMAT('YXXX',A4,2X,
     $  57H--UA-- Variabile di uscita                               )
      WRITE(IFO,3004)IOB
 3004 FORMAT('U1XX',A4,2X,
     $  57H--IN-- Variabile di ingresso n.1                         )
      WRITE(IFO,3005)IOB
 3005 FORMAT('U2XX',A4,2X,
     $  57H--IN-- Variabile di ingresso n.2                         )
      RETURN
      END
C
C
C
      SUBROUTINE MODPI4 (IOB,MOD)
      COMMON/MODP01/IBLOC
      COMMON/MODP02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE MODPD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---modulo di prova
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C$*$
C
C DATI RELATIVI ALL'EQUAZIONE DI STATO RESIDUO X1XX
C
C---descrizione equazione X1XX in stazionario (max. 50 car)
       SIGNEQ ( 1) = 'prima equazione di stato'
C
C---unita` di misura residuo X1XX (max. 10 car)
       UNITEQ ( 1) = '-'
C
C---costante di normalizzazione residuo X1XX in stazionario
       COSNOR ( 1) = 1.
C
C---topologia jacobiano in stazionario per il residuo X1XX
C------dipendenza dalla variabile X1XX
      ITOPVA ( 1, 1) = 1
C------dipendenza dalla variabile U1XX
      ITOPVA ( 1, 4) = 1
C
C DATI RELATIVI ALL'EQUAZIONE DI STATO RESIDUO X2XX
C
C---descrizione equazione X2XX in stazionario (max. 50 car)
       SIGNEQ ( 2) = 'seconda equazione di stato'
C
C---unita` di misura residuo X2XX (max. 10 car)
       UNITEQ ( 2) = '-'
C
C---costante di normalizzazione residuo X2XX in stazionario
       COSNOR ( 2) = 1.
C
C---topologia jacobiano in stazionario per il residuo X2XX
C------dipendenza dalla variabile X2XX
      ITOPVA ( 2, 2) = 1
C------dipendenza dalla variabile U2XX
      ITOPVA ( 2, 5) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO YXXX
C
C---descrizione equazione YXXX in stazionario (max. 50 car)
       SIGNEQ ( 3) = 'equazione di uscita'
C
C---unita` di misura residuo YXXX (max. 10 car)
       UNITEQ ( 3) = '-' 
C
C---costante di normalizzazione residuo YXXX in stazionario
       COSNOR ( 3) = 1.
C
C---topologia jacobiano in stazionario per il residuo YXXX
C------dipendenza dalla variabile X1XX
      ITOPVA ( 3, 1) = 1
C------dipendenza dalla variabile X2XX
      ITOPVA ( 3, 2) = 1
C------dipendenza dalla variabile YXXX
      ITOPVA ( 3, 3) = 1
      RETURN
      END
