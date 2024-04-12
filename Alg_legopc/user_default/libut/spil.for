      SUBROUTINE SPILI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
C---spillamento di vapore riscaldato
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'Wsp_nom '
     $             ,'Ptu_nom '
     $             ,'Wal_nom '
     $             ,'Hali_nom'
     $             ,'Halu_nom'
     $             ,'Pal_nom '
     $             ,'Vol_ali '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) WSPN
     $            ,PTURN
     $            ,WALN
     $            ,HALIN
     $            ,HALUN
     $            ,PALIN
     $            ,VOLAL
      IF(VOLAL.EQ.0.) VOLAL=10.*WALN/900.
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = WSPN
      DATI(ID2+ 1) = HALUN
      DATI(ID2+ 2) = PTURN
      DATI(ID2+ 3) = PALIN
      DATI(ID2+ 4) = WALN
      DATI(ID2+ 5) = HALIN
C
      CALL SATUR(PTURN,7,TSAT,ZOT,1)
      CALL SATUR(PTURN,2,HL,HV,1)
      SALIN= SHEV(PALIN,HALIN,1)
      SALUN= SHEV(PALIN,HALUN,1)
      TALI= TEV(PALIN,SALIN,1)
      TALU= TEV(PALIN,SALUN,1)
C
C  CALCOLI
C
      TMED=0.3*TALI+0.7*TALU
      R=HV-HL
C
      GAMMA= WSPN*R/WALN/(TSAT-TMED)
C
      DATI(ID2+6)=GAMMA
      DATI(ID2+7)=VOLAL
C---- DUE POSIZIONI SONO RISERVATE AL FILTRAGGIO DELLA PORTATA
C     ALIMENTO
c
c_____ posizione del clapet interno
      dati(id2+10)=1.
      ID2 = ID2+10
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = W0
      CNXYU(IV1+ 1) = P0
      CNXYU(IV1+ 2) = W0
      CNXYU(IV1+ 3) = H0
      CNXYU(IV1+ 4) = H0
      CNXYU(IV1+ 5) = P0
      CNXYU(IV1+ 6) = 1.
      CNXYU(IV1+ 7) = 1.
      CNXYU(IV1+ 8) = 1.
C
      RETURN
      END
C
C
C
      SUBROUTINE SPILC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL SPIL
C
C---spillamento di vapore riscald
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL SPILJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL SPIL (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL SPILJC (2,...
C
C      jacobiano numerico  CALL SPILJC (3,...
C
C$*$
  300 CONTINUE
      CALL SPILJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE SPILJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL SPIL
C
      GOTO (1,2,2), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da WSPI
      AJAC(1,1)=1.
C   ---dipendenza da PTUR
      AJAC(1,2)=1.
C   ---dipendenza da WALI
      AJAC(1,3)=1.
C   ---dipendenza da HALI
      AJAC(1,4)=1.
C   ---dipendenza da HALU
      AJAC(1,5)=1.
C   ---dipendenza da PALI
      AJAC(1,6)=1.
C   ---dipendenza da ALZ1
      AJAC(1,7)=1.
C   ---dipendenza da ALZC
      AJAC(1,8)=1.
C   ---dipendenza da ALZ2
      AJAC(1,9)=1.
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
      WSPI   = XYU(IXYU   )
      PTUR   = XYU(IXYU+ 1)
      WALI   = XYU(IXYU+ 2)
      HALI   = XYU(IXYU+ 3)
      HALU   = XYU(IXYU+ 4)
      PALI   = XYU(IXYU+ 5)
      ALZ1   = XYU(IXYU+ 6)
      ALZC   = XYU(IXYU+ 7)
      ALZ2   = XYU(IXYU+ 8)
C
      WSPN   = DATI(IPD   )
      HALUN  = DATI(IPD+ 1)
      PTURN  = DATI(IPD+ 2)
      PALIN  = DATI(IPD+ 3)
      WALN   = DATI(IPD+ 4)
      HALIN  = DATI(IPD+ 5)
      alzcint= dati(ipd+10)
C
C_____ CASO IN CUI LO SPILLAMENTO E` CHIUSO
C
      IF (ALZ1*ALZ2*ALZC*alzcint.LT.1.E-4) THEN
       AJAC(1,1) = -1.
       RETURN
      ENDIF
C
C$*$
C
C--derivata del residuo n.  1 (equazione algebrica)   *******
C     --- rispetto alla variabile WSPI
C      AJAC(1,1) =
C     --- rispetto alla variabile PTUR
C      AJAC(1,2) =
C     --- rispetto alla variabile WALI
C      AJAC(1,3) =
C     --- rispetto alla variabile HALI
C      AJAC(1,4) =
C     --- rispetto alla variabile HALU
C      AJAC(1,5) =
C     --- rispetto alla variabile PALI
C      AJAC(1,6) =
C     --- rispetto alla variabile ALZ1
C      AJAC(1,7) =
C     --- rispetto alla variabile ALZC
C      AJAC(1,8) =
C     --- rispetto alla variabile ALZ2
C      AJAC(1,9) =
C
C
C---calcolo jacobiano numerico
C
C
      NSTATI = 0
      NUSCIT = 1
      NINGRE = 8
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,SPIL)
      RETURN
      END
C
C
C
      SUBROUTINE SPIL (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
C---spillamento di vapore riscald
C   calcolo residui
C
C---decodifica variabili e dati
C
      WSPI   = XYU(IXYU   )
      PTUR   = XYU(IXYU+ 1)*P0
      WALI   = XYU(IXYU+ 2)
      HALI   = XYU(IXYU+ 3)*H0
      HALU   = XYU(IXYU+ 4)*H0
      PALI   = XYU(IXYU+ 5)*P0
      ALZ1   = XYU(IXYU+ 6)
      ALZC   = XYU(IXYU+ 7)
      ALZ2   = XYU(IXYU+ 8)
C
      WSPN   = DATI(IPD   )
      HALUN  = DATI(IPD+ 1)
      PTURN  = DATI(IPD+ 2)
      PALIN  = DATI(IPD+ 3)
      WALN   = DATI(IPD+ 4)
      HALIN  = DATI(IPD+ 5)
      GAMMA  = DATI(IPD+6)
      VOLAL  = DATI(IPD+7)
      alzcint= dati(ipd+10)
C$*$
      SALI= SHEV(PALI,HALI,1)
      SALU= SHEV(PALI,HALU,1)
      TALI=  TEV(PALI,SALI,1)
      TALU=  TEV(PALI,SALU,1)
      AMAL= ROEV(PALI,SALI,1)*VOLAL
      WALX =WALI*W0
      IF(WALX.LT.0.1) WALX=0.1
      TAU = AMAL/WALX
      DELT = DTINT
C
      IF(.NOT.KREGIM) THEN
	 IF(IFUN.EQ.2.AND.ITERT.EQ.0) THEN
	   DATI(IPD+8) = DATI(IPD+9)
	 ENDIF
	WALIFP=DATI(IPD+8)
C____ CALCOLO LA PORTATA ALIMENTO FILTRATA
	  WALIF = (WALIFP + WALI*DELT/TAU)/(1.+DELT/TAU)
	  DATI(IPD+9) = WALIF
      ELSE
	WALIF=WALI
	DATI(IPD+8)=WALI
	DATI(IPD+9)=WALI
      ENDIF
C
      IF (ALZ1*ALZ2*ALZC.LT.1.E-4) THEN
	RNI(1) =WSPI
	RETURN
      ENDIF
C
      if(itert.ne.0.and.ifun.eq.2.and.alzcint.eq.0.) then
	rni(1) =wspi
	return
      endif
C
      if(ptur.lt.610) ptur=610.
      if(ptur.gt.221.e5) ptur=221.e5
c
      CALL SATUR(PTUR,7,TSAT,ZOT,1)
      CALL SATUR(PTUR,2,HL,HV,1)
C
C  CALCOLI
C
      TMED=0.3*TALI+0.7*TALU
      R=HV-HL
C
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
      WSPC=ALZ1*ALZC*ALZ2*GAMMA*WALIF*(TSAT-TMED)/R
      IF(WSPC.LT.0.) then
	 WSPC=0.
	 alzcint=0.
      else
	 alzcint=1.
      endif
      dati(ipd+10)=alzcint
      RNI(1) =WSPI-WSPC
      RETURN
      END
C
C
C
      SUBROUTINE SPILI3 (IFO,IOB,DEBL)
C
      COMMON/SPIL01/IBLOC
      COMMON/SPIL02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'SPIL'/
C
      CALL SPILI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 1
      NINGRE = 8
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('WSPI',A4,2X,
     $  '--UA-- BLEEDING STEAM FLOW RATE FROM THE TURBINE')
      WRITE(IFO,3002)IOB
 3002 FORMAT('PTUR',A4,2X,
     $  '--IN-- PRESSURE OF THE STEAM BLED FROM THE TURBINE')
      WRITE(IFO,3003)IOB
 3003 FORMAT('WALI',A4,2X,
     $  '--IN-- FLOW RATE OF PRE-HEATED WATER')
      WRITE(IFO,3004)IOB
 3004 FORMAT('HALI',A4,2X,
     $  '--IN-- WATER ENTHALPY AT THE HEATER INLET')
      WRITE(IFO,3005)IOB
 3005 FORMAT('HALU',A4,2X,
     $  '--IN-- WATER ENTHALPY AT THE HEATER OUTLET')
      WRITE(IFO,3006)IOB
 3006 FORMAT('PALI',A4,2X,
     $  '--IN-- PRE-HEATED WATER PRESSURE')
      WRITE(IFO,3007)IOB
 3007 FORMAT('ALZ1',A4,2X,
     $  '--IN-- LIFT OF THE MOTOR-OPERATED BLEEDING VALVE')
      WRITE(IFO,3008)IOB
 3008 FORMAT('ALZC',A4,2X,
     $  '--IN-- LIFT OF THE CHECK-VALVE')
      WRITE(IFO,3009)IOB
 3009 FORMAT('ALZ2',A4,2X,
     $  '--IN-- LIFT OF THE MOTOR-OPERATED VALVE UPSTREAM THE HEATER')
      RETURN
      END
C
C
C
      SUBROUTINE SPILI4 (IOB,MOD)
      COMMON/SPIL01/IBLOC
      COMMON/SPIL02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE SPILD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---spillamento di vapore riscald
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C$*$
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO WSPI
C
C---descrizione equazione WSPI in stazionario (max. 50 car)
C      SIGNEQ ( 1) =
C
C---unita` di misura residuo WSPI (max. 10 car)
C      UNITEQ ( 1) =
C
C---costante di normalizzazione residuo WSPI in stazionario
C      COSNOR ( 1) =
C
C---topologia jacobiano in stazionario per il residuo WSPI
C------dipendenza dalla variabile WSPI
      ITOPVA ( 1, 1) = 1
C------dipendenza dalla variabile PTUR
      ITOPVA ( 1, 2) = 1
C------dipendenza dalla variabile WALI
      ITOPVA ( 1, 3) = 1
C------dipendenza dalla variabile HALI
      ITOPVA ( 1, 4) = 1
C------dipendenza dalla variabile HALU
      ITOPVA ( 1, 5) = 1
C------dipendenza dalla variabile PALI
      ITOPVA ( 1, 6) = 1
C------dipendenza dalla variabile ALZ1
      ITOPVA ( 1, 7) = 1
C------dipendenza dalla variabile ALZC
      ITOPVA ( 1, 8) = 1
C------dipendenza dalla variabile ALZ2
      ITOPVA ( 1, 9) = 1
      RETURN
      END
