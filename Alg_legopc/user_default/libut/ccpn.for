C**********************************************************************
C modulo ccpn.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)ccpn.f	5.2
C**********************************************************************
C*********************************************************************
C*                                                                   *
C*  MODULO PER IL CALCOLO DELLA PRESSIONE IN CAMERA DI COMBUSTIONE   *
C*                                                                   *
C*  A PARTIRE DALLE TEMPERATURE FUMI CALCOLATE DAI MODULI CAMERA DI  *
C*                                                                   *
C*  COMUSTIONE E MODULO SCAMBIO FUMI E DALL'EQUAZ. DEI GAS PERFETTI  *
C*********************************************************************
      SUBROUTINE CCPNI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     1                 IBL1,IBL2,IER,CNXYU,TOL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NCELMAX=30,NBCMAX=9)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
      DIMENSION IBRUCC(2*NBCMAX)
      CHARACTER*4 IBRUCC
      REAL IBRUC(NBCMAX)                                               !SNGL
C       DOUBLE PRECISION IBRUC(NBCMAX)                                   !DBLE
C
      LOGICAL KREGIM
C
C--- ALFA E' LA COSTANTE DELLA LEGGE DI STATO DEI GAS PERFETTI
C
      DATA ALFA/289.433/
      DATA AM0/1.E+5/
      DATA PRIF/1.E+5/
      DATA IBRUCC/'IBRU','C_1 ','IBRU','C_2 ','IBRU','C_3 ',
     $            'IBRU','C_4 ','IBRU','C_5 ','IBRU','C_6 ',
     $            'IBRU','C_7 ','IBRU','C_8 ','IBRU','C_9 '/
C
C---MODELLO DI PRESSIONE CAMERA COMBUSTIONE
C
      GO TO(100,200), IFUN
C
 100  CONTINUE
      WRITE(14,504)
 504  FORMAT(4X,'NUM_CEL. =',10X,'*    N_C_BRU. =',10X,'*')
      NRIG=IFIX(NCELMAX/3.)
      IREST=MOD(NCELMAX,3)
      IF(NRIG.GT.0) THEN
      DO 7 II=1,NRIG
      ICONT=3*(II-1)+1
  7   WRITE(14,500) ICONT,ICONT+1,ICONT+2
      ENDIF
      IF(IREST.EQ.1) WRITE(14, 510) (3*NRIG+1)
      IF(IREST.EQ.2) WRITE(14,520) (3*NRIG+1),(3*NRIG+2)
      WRITE(14,1000)(IBRUCC(J),J=1,2*NBCMAX)
      WRITE(14,530) 1,2
  500 FORMAT(3(4X,'VOLCEL',I2,' =',10X,'*'),5X)
  510 FORMAT(4X,'VOLCEL',I2,' =',10X,'*')
  520 FORMAT(2(4X,'VOLCEL',I2,' =',10X,'*'))
  530 FORMAT(2(4X,'TAU_',I1,'    =',10X,'*'))
 1000 FORMAT(3(4X,2A4,1X,'=',10X,'*'),5X)
      RETURN
C
C---lettura e memorizzazione dati
C
200   CONTINUE
      READ(14,501)
      READ(14,501)CEL,BC
      NCEL=CEL
      NBC=BC
       DATI(ID2)=NCEL
       DATI(ID2+1)=NBC
      READ(14,501) (DATI(ID2+1+I),I=1,NCELMAX)
      READ(14,1010) (IBRUC(J),J=1,NBCMAX)
      READ(14,502) COST1,COST2
       DATI(ID2+NCEL+2)=ALFA*T0*AM0/PRIF
       DATI(ID2+NCEL+3)=AM0
C ! DELTA TI INIZIALE
       DATI(ID2+NCEL+4)=0.
       DATI(ID2+NCEL+5)=COST1
       DATI(ID2+NCEL+6)=COST2
      DO I=1,NBC
       DATI(ID2+NCEL+6+I)=IBRUC(I)
      ENDDO
      ID2=ID2+3*NCEL+8+NBC
C
  501 FORMAT(3(14X,F10.0,1X))
  502 FORMAT(2(14X,F10.0,1X))
 1010 FORMAT(3(14X,F10.0,1X),5X)
C
C
C---costanti di normalizzazione
C
      CNXYU(IV1  ) = AM0
      CNXYU(IV1+1) = PRIF
      DO 53 IK=1,2*NBC+2
53    CNXYU(IV1+IK+1) = W0
      DO 54 I=1,NCEL
54    CNXYU(IV1+2*NBC+3+I) = T0
C
      RETURN
      END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
      SUBROUTINE CCPNC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                         !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C
      EXTERNAL CCPN
C
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C
      LOGICAL KREGIM
C
      DATA PRIF/1.E+5/
C
C---MODULO PRESSIONE CAMERA COMBUSTIONE
C
C
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL CCPNJAC(1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL CCPN(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL CCPNJAC(2,...
C
C      jacobiano numerico  CALL CCPNJAC(3,...
C
C$*$
  300 CONTINUE
      CALL CCPNJAC(3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
      SUBROUTINE CCPNJAC(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                         !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C
      EXTERNAL CCPN
C
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C
      LOGICAL KREGIM
      REAL  MFUM                                                       !SNGL
C      DOUBLE PRECISION  MFUM                                           !DBLE
C
      DATA PRIF/1.E+5/
C
      NBC=DATI(IPD+1)
      NCEL=DATI(IPD)
      GOTO(1,2,3),IFUN
C
C---topologia jacobiano
C
  1   CONTINUE
C
C   equazione n.1 (di stato):
C    dipendenza da   MFUM
C
      AJAC(1,1)=1.
C
C    dipendenza dalle portate di combustibile
C
       DO I=1,NBC
	  AJAC(1,2+I)=1.
       END DO
C
C    dipendenza dalle portate di aria
C
       DO I=1,NBC
	  AJAC(1,2+NBC+I)=1.
       END DO
C
C    dipendenza da   WRIC
C
       AJAC(1,2+2*NBC+1)=1.
C
C    dipendenza da   WFUC
C
       AJAC(1,2+2*NBC+2)=1.
C
C
C   equazione n.2 (algebrica):
C    dipendenza da   MFUM
C
       AJAC(2,1)=1.
C
C    dipendenza da   PFUM
C
       AJAC(2,2)=1.
C
C    dipendenza dalle temperature delle celle
C
       DO I=1,NCEL
	  AJAC(2,2+2*NBC+2+I)=1.
       END DO
C
       RETURN
C
C      calcolo jacobiano analitico
C
  2    CONTINUE
       MFUM = XYU(IXYU   )
       PFUM = XYU(IXYU+1 )
C
C$*$
C
C--derivata del residuo n.1 (equazione di stato)   *******
C
C      rispetto alla variabile MFUM
C      AJAC(1,1) =
C
C      rispetto alla variabile WC
C      AJAC(1,3) =
C
C      rispetto alla variabile WA
C      AJAC(1,4) =
C
C      rispetto alla variabile WRIC
C      AJAC(1,5) =
C
C      rispetto alla variabile WFUC
C      AJAC(1,6) =
C
C--derivata del residuo n.2 (equazione algebrica)   *******
C
C      rispetto alla variabile MFUM
C      AJAC(2,1) =
C
C      rispetto alla variabile PFUM
C      AJAC(2,2) =
C
C      rispetto alla variabile TF
C      AJAC(2,7) =
       RETURN
C
C---calcolo jacobiano numerico
C
  3   CONTINUE
C
      NSTATI = 1
      NUSCIT = 1
      NINGRE = 2*NBC+NCEL+2
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     1            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,CCPN)
      RETURN
      END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
      SUBROUTINE CCPN(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NBCMAX=9,NCELMAX=30)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                         !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
      DIMENSION WC(NBCMAX),WA(NBCMAX),TF(NCELMAX),VOL(NCELMAX)
      DIMENSION TFXNON(NCELMAX), TFXPREC(NCELMAX)
      DIMENSION IBRUC(NBCMAX)
C
      LOGICAL KREGIM
      REAL  MFUM                                                       !SNGL
C      DOUBLE PRECISION  MFUM                                           !DBLE
C
      DATA PRIF/1.E+5/
C
C---PRESSIONE CAMERA COMBUSTIONE
C   calcolo residui
C
C---decodifica variabili e dati
C
      NCEL     =DATI(IPD       )
      NBC      =DATI(IPD     +1)
      TAU1     =DATI(IPD+NCEL+5)
      TAU2     =DATI(IPD+NCEL+6)
      DO I=1,NBC
      IBRUC(I) =DATI(IPD+NCEL+6+I)
      ENDDO
      MFUM     = XYU(IXYU   )
      PFUM     = XYU(IXYU+1 )
      DO 69 I=1,NBC
 69   WC(I)    = XYU(IXYU+I+1)
      DO 70 I=1,NBC
 70   WA(I)    = XYU(IXYU+1+NBC+I)
      WRIC     = XYU(IXYU+2*NBC+2)
      WFUC     = XYU(IXYU+2*NBC+3)
       IF (KREGIM) THEN
	 DO I=1,NCEL
	   TF(I) = XYU(IXYU+2*NBC+3+I)
	 ENDDO
       ELSE
	  DELTATI  = DATI(IPD+NCEL+4)
C ! ATTENZIONE AI GRADINI
	  IF (DTINT.NE.DELTATI.AND.DTINT.GT.0.0) THEN
	    A1 = EXP(-DTINT/TAU1)
	    A2 = EXP(-DTINT/TAU2)
	    DATI(IPD+NCEL+7+NBC) = A1
	    DATI(IPD+NCEL+8+NBC) = A2
	  ELSE
	    A1 = DATI(IPD+NCEL+7+NBC)
	    A2 = DATI(IPD+NCEL+8+NBC)
	  ENDIF
	  DATI(IPD+NCEL+4) = DTINT
	  IF (ITERT.EQ.0) THEN
	      DO I=1,NCEL
		 DATI(IPD+NCEL+8+I+NBC)=DATI(IPD+2*NCEL+8+I+NBC)
	      ENDDO
	  ENDIF
C ! INDICE PROGRESSIVO DEL PIANO DI BRUCIATORI
	  K=1
	  DO I=1,NCEL
	    TFXNON(I)    = XYU(IXYU+2*NBC+3+I)
	    TFXPREC(I)   = DATI(IPD+NCEL+8+I+NBC)
	    IF ( I.NE.IBRUC(K) ) THEN
C ! ZONA CONVETTIVA
	      TF(I) = A1*TFXPREC(I)+TFXNON(I)*(1.-A1)
	    ELSE
	      IF ( K.LT.NBC ) K = K + 1
C ! ZONA IRRAGGIATA
	      TF(I) = A2*TFXPREC(I)+TFXNON(I)*(1.-A2)
	    ENDIF
	    IF (IFUN.EQ.2) THEN
	      DATI(IPD+2*NCEL+8+I+NBC) = TF(I)
	    ENDIF
	  ENDDO
       ENDIF
C
      DO 72 I=1,NCEL
 72   VOL(I)       = DATI(IPD+I+1)
      COEFF=DATI(IPD+NCEL+2)
      AM0=DATI(IPD+NCEL+3)
C$*$
C
C---calcolo residui
C
C
C--residuo n.1 (equazione di stato)   *******
      WCTOT=0.
      WATOT=0.
      DO 73 I=1,NBC
      WCTOT=WCTOT+WC(I)
 73   WATOT=WATOT+WA(I)
      RNI(1) =( WCTOT+WATOT+WRIC-WFUC )*W0 / AM0
C
C--residuo n.2 (equazione algebrica NON RISOLTA ITERATIVAMENTE)  ***
C
      CTEMP=0.
      DO 74 I=1,NCEL
 74   CTEMP=CTEMP+VOL(I)/TF(I)
      RNI(2) = PFUM-COEFF*MFUM/CTEMP
C-----------------------------------------------------------
      RETURN
      END
C*********************************************************************
      SUBROUTINE CCPNI3(IFO,IOB,DEBL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/CCPN01/IBLOC
      COMMON/CCPN02/NBC,NCEL
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'CCPN'/
C
      CALL CCPNI4(IOB,MOD)
      NSTATI = 1
      NUSCIT = 1
      NINGRE = 2*NBC+NCEL+2
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('MFUM',A4,2X,
     $  '--US-- MASS OF FLUE GAS INSIDE THE COMBUSTION CHAMBER')
      WRITE(IFO,3002)IOB
 3002 FORMAT('PFUM',A4,2X,
     $  '--UA-- PRESSURE INSIDE THE COMBUSTION CHAMBER')
      DO 30 K=1,NBC
 30   WRITE(IFO,3003) K,IOB,K
 3003 FORMAT('WC',I2,A4,2X,
     $  '--IN-- FUEL FLOW RATE INTO CELL', I2,' OF THE CHAMBER')
      DO 31 K=1,NBC
 31   WRITE(IFO,3004) K,IOB,K
 3004 FORMAT('WA',I2,A4,2X,
     $  '--IN-- AIR FLOW RATE INTO CELL', I2,' OF THE CHAMBER')
      WRITE(IFO,3005)IOB
 3005 FORMAT('WRIC',A4,2X,
     $  '--IN-- FLOW RATE OF RECIRCULATING GAS INSIDE THE CHAMBER')
      WRITE(IFO,3006)IOB
 3006 FORMAT('WFUC',A4,2X,
     $  '--IN-- FLUE GAS FLOW RATE AT CHAMBER EXIT')
      DO 32 K=1,NCEL
 32   WRITE(IFO,3007)K,IOB,K
 3007 FORMAT('TF',I2,A4,2X,
     $  '--IN-- MEAN TEMPERATURE OF THE FLUE GAS IN CELL ', I2)
      RETURN
      END
C
C
C
      SUBROUTINE CCPNI4(IOB,MOD)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NBCMAX=9,NCELMAX=30)
      COMMON/CCPN01/IBLOC
      COMMON/CCPN02/NBC,NCEL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
C
 100  WRITE(6,101) NBCMAX
 101  FORMAT(//10X,
     $   'NUMBER OF BURNERS IN THE COMBUSTION CHAMBER (1-',I2,') ?')
      READ(5,102) NBC
 102  FORMAT(I2)
       IF(NBC.GE.1.AND.NBC.LE.NBCMAX) GO TO 15
      WRITE (6,103) NBC
103   FORMAT(/10X,'ERROR - NUMBER OF BURNERS =',I3,/)
      GO TO 100
15    WRITE(6,104) NCELMAX
104   FORMAT(//10X,'NUMBER OF FLUE GAS CELLS ',
     $       'INSIDE THE CHAMBER (1-',I2,') ?')
      READ(5,102) NCEL
      IF(NCEL.GE.1.AND.NCEL.LE.NCELMAX) GO TO 16
      WRITE (6,105) NCEL
105   FORMAT(/10X,'ERROR - NUMBER OF BURNERS =',I3,/)
      GO TO 15
C
 16   WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
      RETURN
      END
CC
      SUBROUTINE CCPND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $           XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
