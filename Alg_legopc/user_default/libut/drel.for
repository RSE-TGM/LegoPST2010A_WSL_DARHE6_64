      SUBROUTINE DRELI3 (IFO,IOB,DEBL)
      PARAMETER (NV=15)
C
      COMMON/DREL01/IBLOC
      COMMON/DREL02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'DREL'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'UMD1','UA','Voltage                                           ',
     $ 'FAS1','UA','Voltage                                           ',
     $ 'QAT1','UA','Active                                            ',
     $ 'QRE1','UA','Reactive                                          ',
     $ 'IFI1','UA','Field                                             ',
     $ 'VMD2','UA','Voltage                                           ',
     $ 'FAS2','UA','Voltage                                           ',
     $ 'QAT2','UA','Active                                            ',
     $ 'QRE2','UA','Reactive                                          ',
     $ 'IFI2','UA','Field                                             ',
     $ 'UMOD','IN','Voltage                                           ',
     $ 'FASE','IN','Volktage                                          ',
     $ 'QATT','IN','Active                                            ',
     $ 'QREA','IN','Reactive                                          ',
     $ 'IFIL','IN','Field                                             '/
C
      CALL DRELI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 10
      NINGRE = 5
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE DRELI4 (IOB,MOD)
      COMMON/DREL01/IBLOC
      COMMON/DREL02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE DRELI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL UMD1, FAS1, QAT1, QRE1, IFI1                                 !SNGL
      REAL VMD2, FAS2, QAT2, QRE2, IFI2                                 !SNGL
      REAL UMOD, FASE, QATT, QREA, IFIL                                 !SNGL
      REAL VNOM, VBEC, RF, IFLD0                                        !SNGL
C      DOUBLE PRECISION UMD1, FAS1, QAT1, QRE1, IFI1                     !DBLE
C      DOUBLE PRECISION VMD2, FAS2, QAT2, QRE2, IFI2                     !DBLE
C      DOUBLE PRECISION UMOD, FASE, QATT, QREA, IFIL                     !DBLE
C      DOUBLE PRECISION VNOM, VBEC,RF                                    !DBLE
C
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C---elctrical
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'Vnom    '
     $             ,'Vbec    '
     $             ,'Rf      '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) VNOM
     $            ,VBEC
     $            ,RF
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
      DATI(ID2   ) = VNOM
      DATI(ID2+ 1) = VBEC
      DATI(ID2+ 2) = RF
      ID2 = ID2+2
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
            QBASE=W0*H0
            IFLD0=VBEC/RF
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = VNOM
      CNXYU(IV1+ 1) = 1.
      CNXYU(IV1+ 2) = QBASE
      CNXYU(IV1+ 3) = QBASE
      CNXYU(IV1+ 4) = IFLD0
      CNXYU(IV1+ 5) = VNOM
      CNXYU(IV1+ 6) = 1.
      CNXYU(IV1+ 7) = QBASE
      CNXYU(IV1+ 8) = QBASE
      CNXYU(IV1+ 9) = IFLD0
      CNXYU(IV1+10) = VNOM
      CNXYU(IV1+11) = 1.
      CNXYU(IV1+12) = QBASE
      CNXYU(IV1+13) = QBASE
      CNXYU(IV1+14) = IFLD0
C
      RETURN
      END
C
C
C
      SUBROUTINE DRELC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL DREL
C
      REAL UMD1, FAS1, QAT1, QRE1, IFI1                                 !SNGL
      REAL VMD2, FAS2, QAT2, QRE2, IFI2                                 !SNGL
      REAL UMOD, FASE, QATT, QREA, IFIL                                 !SNGL
      REAL VNOM, VBEC, RF                                                !SNGL
C      DOUBLE PRECISION UMD1, FAS1, QAT1, QRE1, IFI1                     !DBLE
C      DOUBLE PRECISION VMD2, FAS2, QAT2, QRE2, IFI2                     !DBLE
C      DOUBLE PRECISION UMOD, FASE, QATT, QREA, IFIL                     !DBLE
C      DOUBLE PRECISION VNOM, VBEC,RF                                    !DBLE                                 !SNGL
C
C---elctrical
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL DRELJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL DREL (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL DRELJC (2,...
C
C      jacobiano numerico  CALL DRELJC (3,...
C
C$*$
  300 CONTINUE
      CALL DRELJC (2,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE DRELJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL DREL
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL UMD1, FAS1, QAT1, QRE1, IFI1                                 !SNGL
      REAL VMD2, FAS2, QAT2, QRE2, IFI2                                 !SNGL
      REAL UMOD, FASE, QATT, QREA, IFIL                                 !SNGL
      REAL VNOM, VBEC, RF                                               !SNGL
C      DOUBLE PRECISION UMD1, FAS1, QAT1, QRE1, IFI1                     !DBLE
C      DOUBLE PRECISION VMD2, FAS2, QAT2, QRE2, IFI2                     !DBLE
C      DOUBLE PRECISION UMOD, FASE, QATT, QREA, IFIL                     !DBLE
C      DOUBLE PRECISION VNOM, VBEC,RF                                    !DBLE
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da UMD1
      AJAC(1,1)=1.
C   ---dipendenza da UMOD
      AJAC(1,11)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da FAS1
      AJAC(2,2)=1.
C   ---dipendenza da FASE
      AJAC(2,12)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da QAT1
      AJAC(3,3)=1.
C   ---dipendenza da QATT
      AJAC(3,13)=1.
C
C---equazione n.4 (algebrica):
C   ---dipendenza da QRE1
      AJAC(4,4)=1.
C   ---dipendenza da QREA
      AJAC(4,14)=1.
C
C---equazione n.5 (algebrica):
C   ---dipendenza da IFI2
      AJAC(5,5)=1.
C   ---dipendenza da IFIL
      AJAC(5,15)=1.
C
C---equazione n.6 (algebrica):
C   ---dipendenza da VMD2
      AJAC(6,6)=1.
C   ---dipendenza da UMOD
      AJAC(6,11)=1.
C
C---equazione n.7 (algebrica):
C   ---dipendenza da FAS2
      AJAC(7,7)=1.
C   ---dipendenza da FASE
      AJAC(7,12)=1.
C
C---equazione n.8 (algebrica):
C   ---dipendenza da QAT2
      AJAC(8,8)=1.
C   ---dipendenza da QATT
      AJAC(8,13)=1.
C
C---equazione n.9 (algebrica):
C   ---dipendenza da QRE2
      AJAC(9,9)=1.
C   ---dipendenza da QREA
      AJAC(9,14)=1.
C
C---equazione n.10 (algebrica):
C   ---dipendenza da UMD1
C   ---dipendenza da IFI2
      AJAC(10,10)=1.
C   ---dipendenza da IFIL
      AJAC(10,15)=1.
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da UMD1
      AJAC(1,1)=-1.
C   ---dipendenza da UMOD
      AJAC(1,11)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da FAS1
      AJAC(2,2)=-1.
C   ---dipendenza da FASE
      AJAC(2,12)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da QAT1
      AJAC(3,3)=-1.
C   ---dipendenza da QATT
      AJAC(3,13)=1.
C
C---equazione n.4 (algebrica):
C   ---dipendenza da QRE1
      AJAC(4,4)=-1.
C   ---dipendenza da QREA
      AJAC(4,14)=1.
C
C---equazione n.5 (algebrica):
C   ---dipendenza da IFI1
      AJAC(5,5)=-1.
C   ---dipendenza da IFIL
      AJAC(5,15)=1.
C
C---equazione n.6 (algebrica):
C   ---dipendenza da VMD2
      AJAC(6,6)=-1.
C   ---dipendenza da UMOD
      AJAC(6,11)=1.
C
C---equazione n.7 (algebrica):
C   ---dipendenza da FAS2
      AJAC(7,7)=-1.
C   ---dipendenza da FASE
      AJAC(7,12)=1.
C
C---equazione n.8 (algebrica):
C   ---dipendenza da QAT2
      AJAC(8,8)=-1.
C   ---dipendenza da QATT
      AJAC(8,13)=1.
C
C---equazione n.9 (algebrica):
C   ---dipendenza da QRE2
      AJAC(9,9)=-1.
C   ---dipendenza da QREA
      AJAC(9,14)=1.
C
C---equazione n.10 (algebrica):
C   ---dipendenza da IFI2
      AJAC(10,10)=-1.
C   ---dipendenza da IFIL
      AJAC(10,15)=1.
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 10
      NINGRE = 5
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,DREL)
      RETURN
      END
C
C
C
      SUBROUTINE DREL (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
      REAL UMD1, FAS1, QAT1, QRE1, IFI1                                 !SNGL
      REAL VMD2, FAS2, QAT2, QRE2, IFI2                                 !SNGL
      REAL UMOD, FASE, QATT, QREA, IFIL                                 !SNGL
      REAL VNOM, VBEC, RF                                               !SNGL
C      DOUBLE PRECISION UMD1, FAS1, QAT1, QRE1, IFI1                     !DBLE
C      DOUBLE PRECISION VMD2, FAS2, QAT2, QRE2, IFI2                     !DBLE
C      DOUBLE PRECISION UMOD, FASE, QATT, QREA, IFIL                     !DBLE
C      DOUBLE PRECISION VNOM, VBEC,RF                                    !DBLE
C
C---elctrical
C   calcolo residui
C
C---decodifica variabili e dati
C
      UMD1   = XYU(IXYU   )
      FAS1   = XYU(IXYU+ 1)
      QAT1   = XYU(IXYU+ 2)
      QRE1   = XYU(IXYU+ 3)
      IFI1   = XYU(IXYU+ 4)
      VMD2   = XYU(IXYU+ 5)
      FAS2   = XYU(IXYU+ 6)
      QAT2   = XYU(IXYU+ 7)
      QRE2   = XYU(IXYU+ 8)
      IFI2   = XYU(IXYU+ 9)
      UMOD   = XYU(IXYU+10)
      FASE   = XYU(IXYU+11)
      QATT   = XYU(IXYU+12)
      QREA   = XYU(IXYU+13)
      IFIL   = XYU(IXYU+14)
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
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
            RNI(1) = UMD1-UMOD
C
C--residuo n.  2 (equazione algebrica)   *******
            RNI(2) = FAS1-FASE
C
C--residuo n.  3 (equazione algebrica)   *******
            RNI(3) = QAT1-QATT
C
C--residuo n.  4 (equazione algebrica)   *******
            RNI(4) = QRE1-QREA
C
C--residuo n.  5 (equazione algebrica)   *******
            RNI(5) = IFI1-IFIL
C
C--residuo n.  6 (equazione algebrica)   *******
            RNI(6) = VMD2-UMOD
C
C--residuo n.  7 (equazione algebrica)   *******
            RNI(7) = FAS2-FASE
C
C--residuo n.  8 (equazione algebrica)   *******
            RNI(8) = QAT2-QATT
C
C--residuo n.  9 (equazione algebrica)   *******
            RNI(9) = QRE2-QREA
C
C--residuo n. 10 (equazione algebrica)   *******
            RNI(10) = IFI2-IFIL
C
      RETURN
      END
C
C
C
      SUBROUTINE DRELD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
