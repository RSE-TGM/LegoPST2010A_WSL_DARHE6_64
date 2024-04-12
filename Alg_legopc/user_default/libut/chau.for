      SUBROUTINE CHAUI3 (IFO,IOB,DEBL)
      PARAMETER (NV=19)
C
      COMMON/CHAU01/IBLOC
      COMMON/CHAU02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'CHAU'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'PCAV','UA','HEATER INTERNAL PRESSURE                          ',
     $ 'TCAV','UA','HEATER INTERNAL TEMPER.                           ',
     $ 'WVAP','UA','BLEEDING MASS FLOW RATE                           ',
     $ 'WCON','UA','CONDENS. MASS FLOW RATE                           ',
     $ 'HCON','UA','CONDENS. WATER ENTHALPY                           ',
     $ 'TCON','UA','CONDENS. TEMPERATURE                              ',
     $ 'HOUT','UA','TUBES OUTPUT ENTHALPY                             ',
     $ 'POUT','UA','TUBES OUTPUT PRESSURE                             ',
     $ 'WTOU','UA','TUBES OUTPUT MASS FLOW RATE                       ',
     $ 'PVAP','IN','TURBINE BLEEDING TAKEOUT PRESS.                   ',
     $ 'AKVP','IN','STEAM CHARGE LOSS COEFFICIENT                     ',
     $ 'HVAP','IN','BLEEDING ENTHALPY                                 ',
     $ 'WDRA','IN','DRAINAGE MASS FLOW RATE                           ',
     $ 'HDRA','IN','DRAINAGE ENTHALPY                                 ',
     $ 'WTUB','IN','TUBES INPUT MASS FLOW RATE                        ',
     $ 'HINP','IN','TUBES INPUT ENTHALPY                              ',
     $ 'PINP','IN','TUBES INPUT PRESSURE                              ',
     $ 'DTSO','IN','CONDENS.-TUBES INPUT DT                           ',
     $ 'DTSU','IN','SATUR.-TUBES OUTPUT  DT                           '/
C
      CALL CHAUI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 9
      NINGRE = 10
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE CHAUI4 (IOB,MOD)
      COMMON/CHAU01/IBLOC
      COMMON/CHAU02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE CHAUI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL PCAV, TCAV, DPBL, WCON, HCON                                 
      REAL TCON, HOUT, POUT, WTOU, PVAP, WVAP                                 
      REAL HVAP, WDRA, HDRA, WTUB, HINP                                 
      REAL PINP, DTSO, DTSU, DPALNOM, WALNOM                           
C
C---heaters static model
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'DPAL_NOM'
     $             ,'WAL_NOM '
      WRITE(14,500) 'DPVP_NOM'
     $             ,'WVP_NOM '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) DPALNOM
     $            ,WALNOM
      READ(14,501) DPVPNOM
     $            ,WVPNOM
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
      DATI(ID2   ) = DPALNOM
      DATI(ID2+ 1) = WALNOM
      DATI(ID2+ 2) = DPVPNOM
      DATI(ID2+ 3) = WVPNOM
      ID2 = ID2+3
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = P0
      CNXYU(IV1+ 1) = T0
      CNXYU(IV1+ 2) = W0
      CNXYU(IV1+ 3) = W0
      CNXYU(IV1+ 4) = H0
      CNXYU(IV1+ 5) = T0
      CNXYU(IV1+ 6) = H0
      CNXYU(IV1+ 7) = P0
      CNXYU(IV1+ 8) = W0
      CNXYU(IV1+ 9) = P0
      CNXYU(IV1+10) = 1.
      CNXYU(IV1+11) = H0
      CNXYU(IV1+12) = W0
      CNXYU(IV1+13) = H0
      CNXYU(IV1+14) = W0
      CNXYU(IV1+15) = H0
      CNXYU(IV1+16) = P0
      CNXYU(IV1+17) = T0
      CNXYU(IV1+18) = T0
C
      RETURN
      END
C
C
C
      SUBROUTINE CHAUC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL CHAU
C
      REAL PCAV, TCAV, DPBL, WCON, HCON   
      REAL TCON, HOUT, POUT, WTOU, PVAP, WVAP  
      REAL HVAP, WDRA, HDRA, WTUB, HINP 
      REAL PINP, DTSO, DTSU, DPALNOM, WALNOM       
C
C---heaters static model
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL CHAUJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL CHAU (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL CHAUJC (2,...
C
C      jacobiano numerico  CALL CHAUJC (3,...
C
C$*$
  300 CONTINUE
      CALL CHAUJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE CHAUJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL CHAU
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL PCAV, TCAV, DPBL, WCON, HCON      
      REAL TCON, HOUT, POUT, WTOU, PVAP, WVAP     
      REAL HVAP, WDRA, HDRA, WTUB, HINP    
      REAL PINP, DTSO, DTSU, DPALNOM, WALNOM    
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da PCAV
      AJAC(1,1)=1.
C   ---dipendenza da TCAV
      AJAC(1,2)=1.
C   ---dipendenza da HOUT
      AJAC(1,7)=1.
C   ---dipendenza da POUT
      AJAC(1,8)=1.
C   ---dipendenza da DTSU
      AJAC(1,18)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da PCAV
      AJAC(2,1)=1.
C   ---dipendenza da TCAV
      AJAC(2,2)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da PCAV
      AJAC(3,1)=1.
C   ---dipendenza da WVAP
      AJAC(3,3)=1.
C   ---dipendenza da PVAP
      AJAC(3,9)=1.
C   ---dipendenza da AKVP
      AJAC(3,10)=1.
C
C---equazione n.4 (algebrica):
C   ---dipendenza da WCON
      AJAC(4,4)=1.
C   ---dipendenza da WVAP
      AJAC(4,10)=1.
C   ---dipendenza da WDRA
      AJAC(4,12)=1.
C
C---equazione n.5 (algebrica):
C   ---dipendenza da PCAV
      AJAC(5,1)=1.
C   ---dipendenza da HCON
      AJAC(5,5)=1.
C   ---dipendenza da TCON
      AJAC(5,6)=1.
C
C---equazione n.6 (algebrica):
C   ---dipendenza da TCON
      AJAC(6,6)=1.
C   ---dipendenza da HINP
      AJAC(6,15)=1.
C   ---dipendenza da PINP
      AJAC(6,16)=1.
C   ---dipendenza da DTSO
      AJAC(6,17)=1.
C
C---equazione n.7 (algebrica):
C   ---dipendenza da WCON
      AJAC(7,4)=1.
C   ---dipendenza da HCON
      AJAC(7,5)=1.
C   ---dipendenza da HOUT
      AJAC(7,7)=1.
C   ---dipendenza da WVAP
      AJAC(7,10)=1.
C   ---dipendenza da HVAP
      AJAC(7,11)=1.
C   ---dipendenza da WDRA
      AJAC(7,12)=1.
C   ---dipendenza da HDRA
      AJAC(7,13)=1.
C   ---dipendenza da WTUB
      AJAC(7,14)=1.
C   ---dipendenza da HINP
      AJAC(7,15)=1.
C
C---equazione n.8 (algebrica):
C   ---dipendenza da POUT
      AJAC(8,8)=1.
C   ---dipendenza da WTUB
      AJAC(8,14)=1.
C   ---dipendenza da PINP
      AJAC(8,16)=1.
C
C--equazione n.9 (identita' per LEGOPHI):
C   ---dipendenza da WTUB
      AJAC(9,14)=1.
C   ---dipendenza da WTOU
      AJAC(9,9)=1.
C
      do i=1,8
      do j=1,19
      ajac(i,j)=1.
      enddo
      enddo
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 9
      NINGRE = 10
      EPS    = 1.E-3
      EPSLIM = 1.E-6
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,CHAU)
      RETURN
      END
C
C
C
      SUBROUTINE CHAU (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL PCAV, TCAV, DPBL, WCON, HCON                   
      REAL TCON, HOUT, POUT, WTOU, PVAP, WVAP                  
      REAL HVAP, WDRA, HDRA, WTUB, HINP                 
      REAL PINP, DTSO, DTSU, DPALNOM, WALNOM           
C
C---heaters static model
C   calcolo residui
C
C---decodifica variabili e dati
C
      PCAV   = XYU(IXYU   )*P0
      TCAV   = XYU(IXYU+ 1)*T0
      WVAP   = XYU(IXYU+ 2)*W0
      WCON   = XYU(IXYU+ 3)*W0
      HCON   = XYU(IXYU+ 4)*H0
      TCON   = XYU(IXYU+ 5)*T0
      HOUT   = XYU(IXYU+ 6)*H0
      POUT   = XYU(IXYU+ 7)*P0
      WTOU   = XYU(IXYU+ 8)*W0
      PVAP   = XYU(IXYU+ 9)*P0
      AKVP   = XYU(IXYU+10)*1.
      HVAP   = XYU(IXYU+11)*H0
      WDRA   = XYU(IXYU+12)*W0
      HDRA   = XYU(IXYU+13)*H0
      WTUB   = XYU(IXYU+14)*W0
      HINP   = XYU(IXYU+15)*H0
      PINP   = XYU(IXYU+16)*P0
      DTSO   = XYU(IXYU+17)*T0
      DTSU   = XYU(IXYU+18)*T0
C
      DPALNOM  = DATI(IPD   )
      WALNOM   = DATI(IPD+ 1)
      DPVPNOM  = DATI(IPD+ 2)
      WVPNOM   = DATI(IPD+ 3)
C
      CALL SATUR(PCAV,7,TSAT,ZOT,1.)
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
      RNI(3) = ((PVAP-PCAV) -
     $          AKVP*WVAP*ABS(WVAP)/(WVPNOM*WVPNOM)*DPVPNOM)/P0
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4) = (WVAP+WDRA-WCON)/W0
C
C--residuo n.  5 (equazione algebrica)   *******
      RNI(5) = (HCON-HEV(PCAV,STEV(PCAV,TCON,0.,1),1))/H0
C
C--residuo n.  6 (equazione algebrica)   *******
      RNI(6) = (TCON-TEV(PINP,SHEV(PINP,HINP,1),1)-DTSO)/T0
C
C--residuo n.  7 (equazione algebrica)   *******
      RNI(7) = (WVAP*HVAP+WDRA*HDRA-WCON*HCON-WTUB*(HOUT-HINP))
     $         /(W0*H0)
C
C--residuo n.  8 (equazione algebrica)   *******
      RNI(8) = ((PINP-POUT)-WTUB*ABS(WTUB)/(WALNOM*WALNOM)*DPALNOM)/P0
C
C--residuo n. 9 (identita' per Legophi)   *******
      RNI(9) = (WTOU-WTUB)/W0
C
      RETURN
      END
C
C
C
      SUBROUTINE CHAUD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---heaters static model
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
