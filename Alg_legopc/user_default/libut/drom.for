      SUBROUTINE DROMI3 (IFO,IOB,DEBL)
      PARAMETER (NV=6)
C
      COMMON/DROM01/IBLOC
      COMMON/DROM02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'DROM'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'OME1','UA','rotor pulsation reference (1)                     ',
     $ 'DEL1','UA','rotor angle reference (1)                         ',
     $ 'OME2','UA','rotor pulsation reference (2)                     ',
     $ 'DEL2','UA','rotor angle reference (2)                         ',
     $ 'OMEG','IN','rotor reference pulsation                         ',
     $ 'DELT','IN','rotor reference angle                             '/
C
      CALL DROMI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 4
      NINGRE = 2
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE DROMI4 (IOB,MOD)
      COMMON/DROM01/IBLOC
      COMMON/DROM02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE DROMI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
C
      REAL OME1, DEL1, OME2, DEL2, OMEG                                 !SNGL
      REAL DELT, OME0, DEL0                                             !SNGL
C      DOUBLE PRECISION OME1, DEL1, OME2, DEL2, OMEG                     !DBLE
C      DOUBLE PRECISION DELT, OME0, DEL0                                 !DBLE
C
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C---Speedy and angle branch
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'OMEGNorm'
     $             ,'DELTNorm'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) OME0
     $            ,DEL0
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
      IF(OME0.eq.0.) OME0 = 314.16
      IF(DEL0.eq.0.) DEL0 = 1.
      DATI(ID2   ) = OME0
      DATI(ID2+ 1) = DEL0
      ID2 = ID2+1
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = OME0
      CNXYU(IV1+ 1) = DEL0
      CNXYU(IV1+ 2) = OME0
      CNXYU(IV1+ 3) = DEL0
      CNXYU(IV1+ 4) = OME0
      CNXYU(IV1+ 5) = DEL0
C
      RETURN
      END
C
C
C
      SUBROUTINE DROMC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL DROM
C
      REAL OME1, DEL1, OME2, DEL2, OMEG                                 !SNGL
      REAL DELT, OME0, DEL0                                             !SNGL
C      DOUBLE PRECISION OME1, DEL1, OME2, DEL2, OMEG                     !DBLE
C      DOUBLE PRECISION DELT, OME0, DEL0                                 !DBLE
C
C---Speedy and angle branch
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL DROMJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL DROM (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL DROMJC (2,...
C
C      jacobiano numerico  CALL DROMJC (3,...
C
C$*$
  300 CONTINUE
      CALL DROMJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE DROMJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL DROM
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL OME1, DEL1, OME2, DEL2, OMEG                                 !SNGL
      REAL DELT, OME0, DEL0                                             !SNGL
C      DOUBLE PRECISION OME1, DEL1, OME2, DEL2, OMEG                     !DBLE
C      DOUBLE PRECISION DELT, OME0, DEL0                                 !DBLE
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da OME1
      AJAC(1,1)=1.
C   ---dipendenza da DEL1
      AJAC(1,2)=1.
C   ---dipendenza da OME2
      AJAC(1,3)=1.
C   ---dipendenza da DEL2
      AJAC(1,4)=1.
C   ---dipendenza da OMEG
      AJAC(1,5)=1.
C   ---dipendenza da DELT
      AJAC(1,6)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da OME1
      AJAC(2,1)=1.
C   ---dipendenza da DEL1
      AJAC(2,2)=1.
C   ---dipendenza da OME2
      AJAC(2,3)=1.
C   ---dipendenza da DEL2
      AJAC(2,4)=1.
C   ---dipendenza da OMEG
      AJAC(2,5)=1.
C   ---dipendenza da DELT
      AJAC(2,6)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da OME1
      AJAC(3,1)=1.
C   ---dipendenza da DEL1
      AJAC(3,2)=1.
C   ---dipendenza da OME2
      AJAC(3,3)=1.
C   ---dipendenza da DEL2
      AJAC(3,4)=1.
C   ---dipendenza da OMEG
      AJAC(3,5)=1.
C   ---dipendenza da DELT
      AJAC(3,6)=1.
C
C---equazione n.4 (algebrica):
C   ---dipendenza da OME1
      AJAC(4,1)=1.
C   ---dipendenza da DEL1
      AJAC(4,2)=1.
C   ---dipendenza da OME2
      AJAC(4,3)=1.
C   ---dipendenza da DEL2
      AJAC(4,4)=1.
C   ---dipendenza da OMEG
      AJAC(4,5)=1.
C   ---dipendenza da DELT
      AJAC(4,6)=1.
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
      OME1   = XYU(IXYU   )
      DEL1   = XYU(IXYU+ 1)
      OME2   = XYU(IXYU+ 2)
      DEL2   = XYU(IXYU+ 3)
      OMEG   = XYU(IXYU+ 4)
      DELT   = XYU(IXYU+ 5)
C
      OME0   = DATI(IPD   )
      DEL0   = DATI(IPD+ 1)
C
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C$*$
C
C--derivata del residuo n.  1 (equazione algebrica)   *******
C     --- rispetto alla variabile OME1
C     --- rispetto alla variabile DEL1
C     --- rispetto alla variabile OME2
C     --- rispetto alla variabile DEL2
C     --- rispetto alla variabile OMEG
C     --- rispetto alla variabile DELT
C
C--derivata del residuo n.  2 (equazione algebrica)   *******
C     --- rispetto alla variabile OME1
C     --- rispetto alla variabile DEL1
C     --- rispetto alla variabile OME2
C     --- rispetto alla variabile DEL2
C     --- rispetto alla variabile OMEG
C     --- rispetto alla variabile DELT
C
C--derivata del residuo n.  3 (equazione algebrica)   *******
C     --- rispetto alla variabile OME1
C     --- rispetto alla variabile DEL1
C     --- rispetto alla variabile OME2
C     --- rispetto alla variabile DEL2
C     --- rispetto alla variabile OMEG
C     --- rispetto alla variabile DELT
C
C--derivata del residuo n.  4 (equazione algebrica)   *******
C     --- rispetto alla variabile OME1
C     --- rispetto alla variabile DEL1
C     --- rispetto alla variabile OME2
C     --- rispetto alla variabile DEL2
C     --- rispetto alla variabile OMEG
C     --- rispetto alla variabile DELT
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 4
      NINGRE = 2
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,DROM)
      RETURN
      END
C
C
C
      SUBROUTINE DROM (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL OME1, DEL1, OME2, DEL2, OMEG                                 !SNGL
      REAL DELT, OME0, DEL0                                             !SNGL
C      DOUBLE PRECISION OME1, DEL1, OME2, DEL2, OMEG                     !DBLE
C      DOUBLE PRECISION DELT, OME0, DEL0                                 !DBLE
C
C---Speedy and angle branch
C   calcolo residui
C
C---decodifica variabili e dati
C
      OME1   = XYU(IXYU   )
      DEL1   = XYU(IXYU+ 1)
      OME2   = XYU(IXYU+ 2)
      DEL2   = XYU(IXYU+ 3)
      OMEG   = XYU(IXYU+ 4)
      DELT   = XYU(IXYU+ 5)
C
      OME0   = DATI(IPD   )
      DEL0   = DATI(IPD+ 1)
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C$*$
C
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
C
      RNI(1) = OMEG-OME1
C--residuo n.  2 (equazione algebrica)   *******
C
      RNI(2) = DELT-DEL1
C--residuo n.  3 (equazione algebrica)   *******
C
      RNI(3) = OMEG-OME2
C--residuo n.  4 (equazione algebrica)   *******
C
      RNI(4) = DELT-DEL2
      RETURN
      END
C
C
C
      SUBROUTINE DROMD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
