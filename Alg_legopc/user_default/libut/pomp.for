      SUBROUTINE POMPI3 (IFO,IOB,DEBL)
      PARAMETER (NV=7)
C
      COMMON/POMP01/IBLOC
      COMMON/POMP02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'POMP'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV) /
     $ 'HUPM','UA','PUMP OUTLET HENTALPY                              ',
     $ 'PUPM','UA','PUMP OUTLET PRESSURE                              ', 
     $ 'WOUT','UA','OUTPUT MASS FLOW RATE                             ',
     $ 'PIPM','IN','PUMP INLET PRESSURE                               ',
     $ 'WPOM','IN','INPUT MASS FLOW RATE                              ',
     $ 'HIPM','IN','PUMP INLET HENTALPY                               ',
     $ 'OMPM','IN','PUMP SPEED                                        '/
C
      CALL POMPI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 3
      NINGRE = 4
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE POMPI4 (IOB,MOD)
      COMMON/POMP01/IBLOC
      COMMON/POMP02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE POMPI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL HUPM, PUPM, PIPM, WPOM, HIPM, WOUT                           !SNGL
      REAL OMPM, DPNOMI, OMNOMI, ETANOM, ALFA00                         !SNGL
C      DOUBLE PRECISION HUPM, PUPM, PIPM, WPOM, HIPM, WOUT               !DBLE
C      DOUBLE PRECISION OMPM, DPNOMI, OMNOMI, ETANOM, ALFA00             !DBLE
C
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C---pompa centrifuga
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'DP_NOM__'
     $             ,'OM_NOM__'
     $             ,'ETA_NOM_'
     $             ,'WPO_NOM_'
     $             ,'ALFA____'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) DPNOMI
     $            ,OMNOMI
     $            ,ETANOM
     $            ,WPONOM
     $            ,ALFA00
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C
      DATI(ID2   ) = DPNOMI
      DATI(ID2+ 1) = OMNOMI
      DATI(ID2+ 2) = ETANOM
      DATI(ID2+ 3) = WPONOM/W0
      DATI(ID2+ 4) = ALFA00
      ID2 = ID2+4
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C---costanti di normalizzazione
C
      OM0=300.
      CNXYU(IV1   ) = H0
      CNXYU(IV1+ 1) = P0
      CNXYU(IV1+ 2) = W0
      CNXYU(IV1+ 3) = P0
      CNXYU(IV1+ 4) = W0
      CNXYU(IV1+ 5) = H0
      CNXYU(IV1+ 6) = OM0
C
      RETURN
      END
C
C
C
      SUBROUTINE POMPC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL POMP
C
      REAL HUPM, PUPM, PIPM, WPOM, HIPM, WOUT                           !SNGL
      REAL OMPM, DPNOMI, OMNOMI, ETANOM, ALFA00                         !SNGL
C      DOUBLE PRECISION HUPM, PUPM, PIPM, WPOM, HIPM, WOUT               !DBLE
C      DOUBLE PRECISION OMPM, DPNOMI, OMNOMI, ETANOM, ALFA00             !DBLE
C
C---pompa centrifuga
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL POMPJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL POMP (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL POMPJC (2,...
C
C      jacobiano numerico  CALL POMPJC (3,...
C
C$*$
  300 CONTINUE
      CALL POMPJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE POMPJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL POMP
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da HUPM
      AJAC(1,1)=1.
C   ---dipendenza da PUPM
      AJAC(1,2)=1.
C   ---dipendenza da PIPM
      AJAC(1,4)=1.
C   ---dipendenza da WOUT
      AJAC(1,3)=1.
C   ---dipendenza da HIPM
      AJAC(1,6)=1.
C   ---dipendenza da OMPM
      AJAC(1,7)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da HUPM
      AJAC(2,1)=1.
C   ---dipendenza da PUPM
      AJAC(2,2)=1.
C   ---dipendenza da PIPM
      AJAC(2,4)=1.
C   ---dipendenza da WOUT
      AJAC(2,3)=1.
C   ---dipendenza da HIPM
      AJAC(2,6)=1.
C   ---dipend6nza da OMPM
      AJAC(2,7)=1.          
C                             
C--- equazione n.2 (algebrica: identita' per Legophi):
C   ---dipendenza da WOUT 
      AJAC(3,3)=1.
C   ---dipendenza da WPOM  
      AJAC(3,5)=1.
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 3
      NINGRE = 4
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,POMP)
      RETURN
      END
C
C
C
      SUBROUTINE POMP (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
      REAL HUPM, PUPM, PIPM, WPOM, HIPM, WOUT                           !SNGL
      REAL OMPM, DPNOMI, OMNOMI, ETANOM, ALFA00,WPONOM                  !SNGL
C      DOUBLE PRECISION HUPM, PUPM, PIPM, WPOM, HIPM. WOUT               !DBLE
C      DOUBLE PRECISION OMPM, DPNOMI, OMNOMI, ETANOM, ALFA00             !DBLE
C
C---pompa centrifuga
C   calcolo residui
C
C---decodifica variabili e dati
C
      OM0=300.
      HUPM   = XYU(IXYU   )
      PUPM   = XYU(IXYU+ 1) 
      WOUT   = XYU(IXYU+ 2)
      PIPM   = XYU(IXYU+ 3)
      WPOM   = XYU(IXYU+ 4)
      HIPM   = XYU(IXYU+ 5)
      OMPM   = XYU(IXYU+ 6)*OM0
C
      DPNOMI = DATI(IPD   )
      OMNOMI = DATI(IPD+ 1)
      ETANOM = DATI(IPD+ 2)
      WPONOM = DATI(IPD+ 3)
      ALFA00 = DATI(IPD+ 4)
      
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C$*$
C     ALFA00=(DP|W=0)/(DP|W=WNOM)
C
      DP=DPNOMI*(ALFA00*(OMPM/OMNOMI)**2+(1-ALFA00)*(WOUT/WPONOM)**2)
      SS=SHEV(PUPM*P0,HUPM*H0,1)
      RO=ROEV(PUPM*P0,SS,1)
C
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
      RNI(1) = HUPM-HIPM-(DP/RO/ETANOM)/H0
C
C--residuo n.  2 (equazione algebrica)   *******
      RNI(2) = PUPM-PIPM-DP/P0 
C
C--residuo n.  3 (equazione algebrica: identita' per Legophi)   *******
      RNI(3) = WOUT-WPOM 
C
      RETURN
      END
C
C
C
      SUBROUTINE POMPD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
