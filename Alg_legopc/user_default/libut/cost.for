      SUBROUTINE COSTI3 (IFO,IOB,DEBL)
      PARAMETER (NV=17)
C
      COMMON/COST01/IBLOC
      COMMON/COST02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'COST'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'PCAV','UA','INTERNAL PRESSURE                                 ',
     $ 'TCAV','UA','INTERNAL TEMPER.                                  ',
     $ 'WCON','UA','CONDENS. MASS FLOW RATE                           ',
     $ 'HCON','UA','CONDENS. WATER ENTHALPY                           ',
     $ 'PCON','UA','CONDENS. PRESSURE                                 ',
     $ 'WOUT','UA','TUBES OUTPUT MASS FLOW RATE                       ',
     $ 'HOUT','UA','TUBES OUTPUT ENTHALPY                             ',
     $ 'POUT','UA','TUBES OUTPUT PRESSURE                             ',
     $ 'AKVP','IN','STEAM CHARGE LOSS COEFFICIENT                     ',
     $ 'WVAP','IN','BLEEDING MASS FLOW RATE                           ',
     $ 'HVAP','IN','BLEEDING ENTHALPY                                 ',
     $ 'WDRA','IN','DRAINAGE MASS FLOW RATE                           ',
     $ 'HDRA','IN','DRAINAGE ENTHALPY                                 ',
     $ 'WTUB','IN','TUBES INPUT MASS FLOW RATE                        ',
     $ 'HINP','IN','TUBES INPUT ENTHALPY                              ',
     $ 'PINP','IN','TUBES INPUT PRESSURE                              ',
     $ 'DTSU','IN','SATUR.-TUBES OUTPUT  DT                           '/
C
      CALL COSTI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 8
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
      SUBROUTINE COSTI4 (IOB,MOD)
      COMMON/COST01/IBLOC
      COMMON/COST02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE COSTI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL PCAV, TCAV, WCON, HCON, PCON                                 
      REAL WOUT, HOUT, POUT, AKVP, WVAP, LIV_C                          
      REAL HVAP, WDRA, HDRA, WTUB, HINP                                 
      REAL PINP, DTSU, DPALNOM, WALNOM                           
C
C---condenser static model
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'DPAL_NOM'
     $             ,'WAL_NOM '
      WRITE(14,500) 'LIV.COND'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) DPALNOM
     $            ,WALNOM
      READ(14,501) LIV_C
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
      DATI(ID2   ) = DPALNOM
      DATI(ID2+ 1) = WALNOM
      DATI(ID2+ 2) = LIV_C
      ID2 = ID2+2
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = P0
      CNXYU(IV1+ 1) = T0
      CNXYU(IV1+ 2) = W0
      CNXYU(IV1+ 3) = H0
      CNXYU(IV1+ 4) = P0
      CNXYU(IV1+ 5) = W0
      CNXYU(IV1+ 6) = H0
      CNXYU(IV1+ 7) = P0
      CNXYU(IV1+ 8) = 1. 
      CNXYU(IV1+ 9) = W0
      CNXYU(IV1+10) = H0
      CNXYU(IV1+11) = W0
      CNXYU(IV1+12) = H0
      CNXYU(IV1+13) = W0
      CNXYU(IV1+14) = H0
      CNXYU(IV1+15) = P0
      CNXYU(IV1+16) = T0
C
      RETURN
      END
C
C
C
      SUBROUTINE COSTC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL COST
C
      REAL PCAV, TCAV, WCON, HCON, PCON
      REAL WOUT, HOUT, POUT, AKVP, WVAP, LIV_C
      REAL HVAP, WDRA, HDRA, WTUB, HINP
      REAL PINP, DTSU, DPALNOM, WALNOM
C
C---condenser static model
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL COSTJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL COST (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL COSTJC (2,...
C
C      jacobiano numerico  CALL COSTJC (3,...
C
C$*$
  300 CONTINUE
      CALL COSTJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE COSTJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL COST
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL PCAV, TCAV, WCON, HCON, PCON
      REAL WOUT, HOUT, POUT, AKVP, WVAP, LIV_C
      REAL HVAP, WDRA, HDRA, WTUB, HINP
      REAL PINP, DTSU, DPALNOM, WALNOM
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
      DO I=1,8
         DO J=1,17
            AJAC(I,J)=1.
         ENDDO
      ENDDO
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 8
      NINGRE = 9
      EPS    = 1.E-3
      EPSLIM = 1.E-6
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,COST)
      RETURN
      END
C
C
C
      SUBROUTINE COST (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      PARAMETER (G=9.81)
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
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL PCAV, TCAV, WCON, HCON, PCON
      REAL WOUT, HOUT, POUT, AKVP, WVAP, LIV_C
      REAL HVAP, WDRA, HDRA, WTUB, HINP
      REAL PINP, DTSU, DPALNOM, WALNOM
C
C---condenser static model
C   calcolo residui
C
C---decodifica variabili e dati
C
      PCAV   = XYU(IXYU   )*P0
      TCAV   = XYU(IXYU+ 1)*T0
      WCON   = XYU(IXYU+ 2)*W0
      HCON   = XYU(IXYU+ 3)*H0
      PCON   = XYU(IXYU+ 4)*P0
      WOUT   = XYU(IXYU+ 5)*W0
      HOUT   = XYU(IXYU+ 6)*H0
      POUT   = XYU(IXYU+ 7)*P0
      AKVP   = XYU(IXYU+ 8)*1.
      WVAP   = XYU(IXYU+ 9)*W0
      HVAP   = XYU(IXYU+10)*H0
      WDRA   = XYU(IXYU+11)*W0
      HDRA   = XYU(IXYU+12)*H0
      WTUB   = XYU(IXYU+13)*W0
      HINP   = XYU(IXYU+14)*H0
      PINP   = XYU(IXYU+15)*P0
      DTSU   = XYU(IXYU+16)*T0
C
      DPALNOM  = DATI(IPD   )
      WALNOM   = DATI(IPD+ 1)
      LIV_C    = DATI(IPD+ 2)
C
      CALL SATUR(PCAV,2,HLS,HVS,1)
      CALL SATUR(PCAV,3,ROLS,ROVS,1)
      CALL SATUR(PCAV,7,TSAT,ZOT,1)
C
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
      RNI(1) = (DTSU-TSAT+TEV(POUT,SHEV(POUT,HOUT,1),1))/T0
C
C--residuo n.  2 (equazione algebrica)   *******
      RNI(2) = (TCAV-TSAT)/T0
C
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3) = (WVAP+WDRA-WCON)/W0 
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4) = (HCON-HLS)/H0
C
C--residuo n.  5 (equazione algebrica)   *******
      RNI(5) = (PCON-PCAV-G*ROLS*LIV_C)/P0
C
C--residuo n.  6 (identita' per Legophi) *******
      RNI(6) = (WOUT-WTUB)/W0
C
C--residuo n.  6 (equazione algebrica)   *******
      RNI(7) = (WVAP*HVAP+WDRA*HDRA-WCON*HCON-WTUB*(HOUT-HINP))
     $         /(W0*H0)
C
C--residuo n.  7 (equazione algebrica)   *******
      RNI(8) = (PINP-POUT)/DPALNOM - WTUB*ABS(WTUB)/(WALNOM*WALNOM)
C
      RETURN
      END
C
C
C
      SUBROUTINE COSTD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---condenser static model
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
