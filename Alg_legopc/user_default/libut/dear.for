      SUBROUTINE DEARI3 (IFO,IOB,DEBL)
      PARAMETER (NV=14)
C
      COMMON/DEAR01/IBLOC
      COMMON/DEAR02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'DEAR'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'POUT','UA','OUTLET PRESSURE                                   ',
     $ 'TOUT','UA','OUTLET TEMPERATURE                                ',
     $ 'WOUT','UA','OUTLET MASS FLOW RATE                             ',
     $ 'HOUT','UA','OUTLET ENTHALPY                                   ',
     $ 'WVAP','UA','STEAM MASS FLOW RATE                              ',
     $ 'AKVP','IN','STEAM CHARGE LOSSES COEFFICIENT                   ',
     $ 'HVAP','IN','STEAM ENTHALPY                                    ',
     $ 'PVAP','IN','STEAM PRESSURE                                    ',
     $ 'WDR1','IN',' DRAIN FLOW 1                                     ',
     $ 'HDR1','IN',' DRAIN ENTHALPY 1                                 ',
     $ 'WDR2','IN','DRAIN FLOW 2                                      ',
     $ 'HDR2','IN','DRAIN ENTHALPY 2                                  ',
     $ 'WCON','IN','CONDENSATE MASS FLOW                              ',
     $ 'HCON','IN','CONDENSATE ENTHALPY                               '/
C
      CALL DEARI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 5
      NINGRE = 9
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE DEARI4 (IOB,MOD)
      COMMON/DEAR01/IBLOC
      COMMON/DEAR02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE DEARI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL POUT, TOUT, WOUT, HOUT, AKVP                                 !SNGL
      REAL WVAP, HVAP, PVAP, WDR1, HDR1                                 !SNGL
      REAL WDR2, HDR2, WCON, HCON                                       !SNGL
C      DOUBLE PRECISION POUT, TOUT, WOUT, HOUT, AKVP                     !DBLE
C      DOUBLE PRECISION WVAP, HVAP, PVAP, WDR1, HDR1                     !DBLE
C      DOUBLE PRECISION WDR2, HDR2, WCON, HCON                           !DBLE
C
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C---deareator for static BOP calculation
C
      GO TO(100,200), IFUN
C
  100 CONTINUE
      WRITE(14,500) 'DPVP_NOM'
     $             ,'WVP_NOM '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) DPVPNOM
     $            ,WVPNOM
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
      DATI(ID2   ) = DPVPNOM/P0
      DATI(ID2+ 1) = WVPNOM/W0
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
      CNXYU(IV1   ) = P0
      CNXYU(IV1+ 1) = T0
      CNXYU(IV1+ 2) = W0
      CNXYU(IV1+ 3) = H0
      CNXYU(IV1+ 4) = W0
      CNXYU(IV1+ 5) = 1.
      CNXYU(IV1+ 6) = H0
      CNXYU(IV1+ 7) = P0
      CNXYU(IV1+ 8) = W0
      CNXYU(IV1+ 9) = H0
      CNXYU(IV1+10) = W0
      CNXYU(IV1+11) = H0
      CNXYU(IV1+12) = W0
      CNXYU(IV1+13) = H0
C
      RETURN
      END
C
C
C
      SUBROUTINE DEARC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL DEAR
C
      REAL POUT, TOUT, WOUT, HOUT, AKVP                                 !SNGL
      REAL WVAP, HVAP, PVAP, WDR1, HDR1                                 !SNGL
      REAL WDR2, HDR2, WCON, HCON                                       !SNGL
C      DOUBLE PRECISION POUT, TOUT, WOUT, HOUT, AKVP                     !DBLE
C      DOUBLE PRECISION WVAP, HVAP, PVAP, WDR1, HDR1                     !DBLE
C      DOUBLE PRECISION WDR2, HDR2, WCON, HCON                           !DBLE
C
C---deareator for static BOP calculation
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL DEARJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL DEAR (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL DEARJC (2,...
C
C      jacobiano numerico  CALL DEARJC (3,...
C
C$*$
  300 CONTINUE
      CALL DEARJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE DEARJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL DEAR
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL POUT, TOUT, WOUT, HOUT, AKVP                                 !SNGL
      REAL WVAP, HVAP, PVAP, WDR1, HDR1                                 !SNGL
      REAL WDR2, HDR2, WCON, HCON                                       !SNGL
C      DOUBLE PRECISION POUT, TOUT, WOUT, HOUT, AKVP                     !DBLE
C      DOUBLE PRECISION WVAP, HVAP, PVAP, WDR1, HDR1                     !DBLE
C      DOUBLE PRECISION WDR2, HDR2, WCON, HCON                           !DBLE
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
      DO I=1,5
      DO J=1,14
      AJAC(I,J)=1.   
      ENDDO
      ENDDO
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
      NSTATI = 0
      NUSCIT = 5
      NINGRE = 9
      EPS    = 1.E-3
      EPSLIM = 1.E-6
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,DEAR)
      RETURN
      END
C
C
C
      SUBROUTINE DEAR (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
      REAL POUT, TOUT, WOUT, HOUT, AKVP                                 !SNGL
      REAL WVAP, HVAP, PVAP, WDR1, HDR1                                 !SNGL
      REAL WDR2, HDR2, WCON, HCON                                       !SNGL
C      DOUBLE PRECISION POUT, TOUT, WOUT, HOUT, AKVP                     !DBLE
C      DOUBLE PRECISION WVAP, HVAP, PVAP, WDR1, HDR1                     !DBLE
C      DOUBLE PRECISION WDR2, HDR2, WCON, HCON                           !DBLE
C
C---deareator for static BOP calculation
C   calcolo residui
C
C---decodifica variabili e dati
C
      POUT   = XYU(IXYU   )
      TOUT   = XYU(IXYU+ 1)
      WOUT   = XYU(IXYU+ 2)
      HOUT   = XYU(IXYU+ 3)
      WVAP   = XYU(IXYU+ 4)
      AKVP   = XYU(IXYU+ 5)
      HVAP   = XYU(IXYU+ 6)
      PVAP   = XYU(IXYU+ 7)
      WDR1   = XYU(IXYU+ 8)
      HDR1   = XYU(IXYU+ 9)
      WDR2   = XYU(IXYU+10)
      HDR2   = XYU(IXYU+11)
      WCON   = XYU(IXYU+12)
      HCON   = XYU(IXYU+13)
C
      DPVPNOM  = DATI(IPD  )
      WVPNOM   = DATI(IPD+1)     
C
      PREAL=P0*POUT
      HREAL=H0*HOUT 
      S=SHEV(PREAL,HREAL,1)
      TCOUT= TEV(PREAL,S,1)
      CALL SATUR(PREAL,7,TSAT,ZOT,1)
      CALL SATUR(PREAL,2,HLSAT,HVSAT,1)
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C$*$

      DPVP=AKVP*WVAP*ABS(WVAP)/(WVPNOM*WVPNOM)*DPVPNOM
C
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
      RNI(1) = PVAP-POUT-DPVP
C
C--residuo n.  2 (equazione algebrica)   *******
      RNI(2) = TOUT-TCOUT/T0
C
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3) = WOUT-WDR1-WDR2-WCON-WVAP
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4) = (HREAL-HLSAT)/H0
C
C--residuo n.  5 (equazione algebrica)   *******
      RNI(5) = WOUT*HOUT-WDR1*HDR1-WDR2*HDR2-WCON*HCON-WVAP*HVAP
      RETURN
      END
C
C
C
      SUBROUTINE DEARD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---deareator for static BOP calculation
C

      RETURN
      END
