C**********************************************************************
C modulo degn.f
C tipo 
C release 5.3
C data 10/3/96
C reserver @(#)degn.f	5.3
C**********************************************************************
C
      SUBROUTINE DEGNI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/DEGN01/IBLOC
      COMMON/DEGN02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'DEGN'/
C
C**********CAVITA` DEGASATORE SEMPLIFICATO (DIC.1988) **********
C
      CALL DEGNI4(IOB,MOD)
C
      NSTATI = 4
      NUSCIT = 1
      NINGRE = 11
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
C---stati
C
      WRITE(IFO,3001)IOB
 3001 FORMAT('HLDG',A4,2X,
     $    '--US-- WATER ENTH. AT THE OUTLET OF DEGASIFIER TANK')
      WRITE(IFO,3002)IOB
 3002 FORMAT('HVDG',A4,2X,
     $    '--US-- STEAM MEAN ENTH. INSIDE THE DEGASIFIER')
      WRITE(IFO,3003)IOB
 3003 FORMAT('LIVD',A4,2X,
     $    '--US-- WATER LEVEL INSIDE THE DEGASIFIER TANK')
      WRITE(IFO,3004)IOB
 3004 FORMAT('PVDG',A4,2X,
     $    '--US-- STEAM MEAN PRESSURE INSIDE THE DEGASIFIER')
C
C---uscite
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('PLDG',A4,2X,
     $   '--UA-- PRESSURE ON THE BOTTOM OF DEGASIFIER TANK')
   50 CONTINUE
C
C---ingressi
C
      WRITE(IFO,3006)IOB
 3006 FORMAT('WSPD',A4,2X,
     $   '--IN-- BLEEDING FLOW RATE FROM THE DEGASIFIER')
      WRITE(IFO,3007)IOB
 3007 FORMAT('HSPD',A4,2X,
     $   '--IN-- ENTHALPY OF STEAM BLED FROM THE DEGASIFIER')
      WRITE(IFO,3008)IOB
 3008 FORMAT('WALI',A4,2X,
     $   '--IN-- FEEDWATER FLOW RATE AT THE DOME INLET')
      WRITE(IFO,3009)IOB
 3009 FORMAT('HALI',A4,2X,
     $   '--IN-- FEEDWATER ENTHALPY AT THE DOME INLET')
      WRITE(IFO,3010)IOB
 3010 FORMAT('WDRE',A4,2X,
     $   '--IN-- DRAINAGES FLOW RATE AT THE DOME INLET')
      WRITE(IFO,3011)IOB
 3011 FORMAT('HDRE',A4,2X,
     $   '--IN-- DRAINAGES WATER ENTHALPY AT THE DOME INLET')
      WRITE(IFO,3012)IOB
 3012 FORMAT('WOUT',A4,2X,
     $   '--IN-- WATER FLOW RATE AT THE DEGASIFIER TANK OUTLET')
      WRITE(IFO,3013)IOB
 3013 FORMAT('WRIS',A4,2X,
     $   '--IN-- STEAM FLOW RATE AT THE START TROUGH THE TANK')
      WRITE(IFO,3014)IOB
 3014 FORMAT('HRIS',A4,2X,
     $   '--IN-- STEAM ENTHALPY AT THE START INSIDE THE TANK')
      WRITE(IFO,3015)IOB
 3015 FORMAT('WRIC',A4,2X,
     $   '--IN-- RECIRCULATING FLOW RATE OF THE FEEDWATER PUMP')
      WRITE(IFO,3016)IOB
 3016 FORMAT('HRIC',A4,2X,
     $   '--IN-- RECIRC. LIQUID ENTH. OF THE FEEDWATER PUMP')
  100 CONTINUE
C
      RETURN
      END
      SUBROUTINE DEGNI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/DEGN01/IBLOC
      COMMON/DEGN02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
      SUBROUTINE DEGNI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     1 IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C**********CAVITA` DEGASATORE**********
C
      GO TO (100,200), IFUN
C
C---scrittura simboli dati su file 14
C
C  100 WRITE(14,500)'**********   DEGASIFIER '
  100   CONTINUE
       WRITE(14,501) 'VOL.CAV.','D. SERB.',
     1       'L. SERB.'
      RETURN
C
C---lettura dei dati
C
  200 READ(14,502)
      READ(14,502) VCAV,DSERB,ALSERB
C
  500 FORMAT(A)
  501 FORMAT(3(4X,A8,' =',10X,'*'))
  502 FORMAT(3(14X,F10.0,1X))
C
C---memorizzazione dei dati
C
      PIGR = 3.1415926
      G = 9.80665
C
      DATI(ID2+  0)  =  VCAV
      DATI(ID2+  1)  =  DSERB/2.
      DATI(ID2+  2)  =  ALSERB
      ID2 = ID2+2
C
C---costanti di normalizzazione
C
      CNXYU(IV1   )  =  H0
      CNXYU(IV1+ 1)  =  H0
      CNXYU(IV1+ 2)  =  100.
      CNXYU(IV1+ 3)  =  P0
      CNXYU(IV1+ 4)  =  P0
C
      CNXYU(IV1+ 5)  =  W0
      CNXYU(IV1+ 6)  =  H0
      CNXYU(IV1+ 7)  =  W0
      CNXYU(IV1+ 8)  =  H0
      CNXYU(IV1+ 9)  =  W0
      CNXYU(IV1+10)  =  H0
      CNXYU(IV1+11)  =  W0
      CNXYU(IV1+12)  =  W0
      CNXYU(IV1+13)  =  H0
      CNXYU(IV1+14)  =  W0
      CNXYU(IV1+15)  =  H0
C
C---tolleranze (default)
C
      RETURN
      END
      SUBROUTINE DEGNC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C**********CAVITA` DEGASATORE**********
C
C---subroutine chiamate:
C
C       DGNDEC  - DECODIFICA VARIABILI E DATI
C       DGNTAV  - CHIAMATE ALLE TAVOLE H2O
C       DGNTYP  - CALCOLO DI VL E DVLDY
C       DGNTAU  - CALCOLO DELLE COSTANTI DI TEMPO
C       DGNDER  - CALCOLO DERIVATE E RESIDUI
C       DGNSOL  - CALCOLO DI X=TAU.E-1*B
C       DGNJAC  - CALCOLO DELLO JACOBIANO
C-------------------------------------------------
C
      NSTATI = 4
      NUSCIT = 1
      NINGRE = 11
      NEQ = NSTATI + NUSCIT
      NVAR = NEQ + NINGRE
C
      GO TO (100,200,300), IFUN
C
C---topologia jacobiano
C
  100 DO I = 1,NEQ
      DO J = 1,NVAR
      AJAC(I,J) = 1.
      END DO
      END DO
      RETURN
C
C---chiamata routines per la decodifica e per il calcolo di
C---residui e derivate
C
  200 CALL   DGNDEC(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1 HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,VCAV,RSERB,ALSERB,
     1 XYU,IXYU,DATI,IPD)
C
      CALL   DGNTAV(P,HL,HV,ROL,ROV,ROWS,BELI,BEVA,A2LI,
     1       A2VA,XL,XV,TLS,TV,HLS,HVS,PF)
C
      CALL   DGNTYP(Y,VL,DVLDY,RSERB,ALSERB)
C
      CALL   DGNTAU(A2LI,BELI,ROL,TLS,A2VA,BEVA,ROV,TV,Y,
     1       VCAV,VL,DVLDY,TAU11,TAU14,TAU22,TAU24,TAU31,
     1       TAU33,TAU34,TAU42,TAU43,TAU44)
C
      CALL   DGNDER(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1       HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,
     1       VCAV,RSERB,ALSERB,VL,DVLDY,
     1       ROL,ROV,ROWS,XL,XV,HLS,HVS,TLS,TV,
     1       IFUN,TAU11,TAU14,TAU22,TAU24,TAU31,TAU33,TAU34,
     1       TAU42,TAU43,TAU44,DATI,IPD,RNI)
      RETURN
C
C---chiamata routine per il calcolo dello jacobiano numerico e, di
C---seguito, tutte le routines chiamate in DEGNC1
C
  300 CALL   DGNJAC(AJAC,MX5,IXYU,XYU,DATI,IPD,RNI,IFUN,NEQ,NVAR)
C
      RETURN
      END
      SUBROUTINE DGNDEC(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1           HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,VCAV,RSERB,ALSERB,
     1           XYU,IXYU,DATI,IPD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION XYU(*),DATI(*)
C
C**********CAVITA` DEGASATORE**********
C
C---routine di decodifica variabili e dati
C
C---------------------uscite e stati
      HL = XYU(IXYU   )
      HV = XYU(IXYU+ 1)
      Y = XYU(IXYU+ 2)*100.
      P = XYU(IXYU+ 3)
C
      PF = XYU(IXYU+ 4)
C---------------------ingressi
      QV = XYU(IXYU+ 5)
      HVI = XYU(IXYU+ 6)
      QCOND = XYU(IXYU+ 7)
      HCOND = XYU(IXYU+ 8)
      QDR = XYU(IXYU+ 9)
      HDR = XYU(IXYU+10)
      QEC = XYU(IXYU+11)
      QVV = XYU(IXYU+12)
      HVV = XYU(IXYU+13)
      QWR = XYU(IXYU+14)
      HWR = XYU(IXYU+15)
C---------------------dati
      VCAV = DATI(IPD   )
      RSERB = DATI(IPD+ 1)
      ALSERB = DATI(IPD+ 2)
C
      RETURN
      END
      SUBROUTINE DGNTAV(P,HL,HV,ROL,ROV,ROWS,BELI,BEVA,A2LI,
     1           A2VA,XL,XV,TLS,TV,HLS,HVS,PF)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/QQDRDPVS/DRDPVS
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/PARPAR/N1,N2,N3,N4,N5,N6,N7,ITERT
      COMMON/REGIME/KREGIM
      LOGICAL  KREGIM
C
C**********CAVITA` DEGASATORE**********
C
      NFL = 1
      PRE = P*P0
      PRF = PF*P0
      HLRE = HL*H0
      HVRE = HV*H0
C
      CALL SATUR(PRE,2,HLS,HVS,NFL)
C
      SL=SHEV(PRE,HLRE,NFL)
      TLS=TEV(PRE,SL,NFL)
      CALL SATUR(PRE,7,TV,ZOT,NFL)
      CALL SATUR(PRE,3,ROWS,ROVS,NFL)
      CALL SATUR(PRE+.1E5,3,ROWS1,ROVS1,NFL)
      DRDPVS= (ROVS1-ROVS)/.1E5
      ROL  = ROWS
      ROV  = ROVS
      XL = (HLRE-HLS)/(HVS-HLS)
      XV = (HVRE-HLS)/(HVS-HLS)
C
      HLS = HLS/H0
      HVS = HVS/H0
C
      RETURN
      END
      SUBROUTINE DGNTYP(Y,VL,DVLDY,RSERB,ALSERB)
C
C**********CAVITA` DEGASATORE**********
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      YR=Y/RSERB
      IF(YR.LE..1E-5) THEN
	VL=1.
	DVLDY=1.
	RETURN
      ENDIF
      IF(YR.GT.2.)THEN
        WRITE(6,*)' WARNING :  DEGN    Y=',Y
        WRITE(6,*)' WARNING :  LEVEL > INTERNAL DIAMETER '
        WRITE(6,*)' WARNING :  PROGRAM GOES ON WITH DEFAULT'
        WRITE(6,*)' WARNING :  LEVEL = INTERNAL DIAMETER'
        VL  = 3.14159*(RSERB**2.)*ALSERB
        DVLDY  = 0.0001
      ELSEIF(YR.LE.0.)THEN
        WRITE(6,*)' WARNING :  DEGN    Y=',Y
        WRITE(6,*)' WARNING :  LEVEL < 0.'
        WRITE(6,*)' WARNING :  PROGRAM GOES ON WITH DEFAULT'
        WRITE(6,*)' WARNING :  LEVEL = 0.001 '
        ALFA  = ACOS(1.-0.001/RSERB)
        VL  = (RSERB**2.*ALFA-RSERB*(RSERB-0.001)*SIN(ALFA))*ALSERB
        DVLDY  = 2.*RSERB*SIN(ALFA)*ALSERB
      ELSE
        ALFA  = ACOS(1.-YR)
        VL  = (RSERB**2.*ALFA-RSERB*(RSERB-Y)*SIN(ALFA))*ALSERB
        DVLDY  = 2.*RSERB*SIN(ALFA)*ALSERB
      ENDIF
C
      IF(DVLDY.LT..1E-5)DVLDY = 0.
C
      RETURN
      END
      SUBROUTINE DGNTAU(A2LI,BELI,ROL,TLS,A2VA,BEVA,ROV,TV,Y,
     1           VCAV,VL,DVLDY,TAU11,TAU14,TAU22,TAU24,TAU31,
     1           TAU33,TAU34,TAU42,TAU43,TAU44)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/QQDRDPVS/DRDPVS
C
      DATA TAUV/1./
C
C**********CAVITA` DEGASATORE**********
C
      W0H0 =  W0*H0
C
      TAU11 =  ROL*VL/W0
      TAU14 =  -VL*P0/W0H0
      TAU22 =  TAUV
      TAU24   =  0.
      TAU31 =  0.
      TAU33 =  DVLDY*ROL/W0
      TAU34 =  0.
      TAU42   =  0.
      TAU43 =   -DVLDY*ROV/W0
      TAU44 =  (VCAV-VL)*DRDPVS*P0/W0
C
      RETURN
      END
      SUBROUTINE DGNDER(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1           HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,
     1           VCAV,RSERB,ALSERB,VL,DVLDY,
     1           ROL,ROV,ROWS,XL,XV,HLS,HVS,TLS,TV,
     1           IFUN,TAU11,TAU14,TAU22,TAU24,TAU31,TAU33,TAU34,
     1           TAU42,TAU43,TAU44,DATI,IPD,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      DIMENSION RNI(*),DATI(*)
C
      DATA TAUL/10./, TAUV/1./
      DATA GAMSUP/1.E7/
C
C**********CAVITA` DEGASATORE**********
C
C---routine per il calcolo di derivate e residui
C
C---derivate e residui
C
      QSUP=GAMSUP*(TV-TLS)/W0/H0
      IF (VL.LE.0.)THEN
       AMASEV=0.
      ELSE
       AMASEV=VL*ROWS*XL
      ENDIF
      IF(AMASEV.LT.0)AMASEV=0.
C
C  QEV = Portata di evaporazione
C  QC  = Portata di condensazione
C
      QEV=AMASEV/TAUL/W0
C
      DHVI=HVI-HV
      DHVVI=HVV-HV
      IF(QV.LT.0.)DHVI=0.
      IF(QVV.LT.0.)DHVVI=0.
C
      QC = (QV*DHVI+QVV*DHVVI-QSUP+
     1      QEV*(HVS-HV)-QCOND*(HLS-HCOND))/(HLS-HV)
      IF(QC.LT.0)QC=0.
C
C-Conservazione dell` energia nella zona liquida
C
      R1 = QDR*(HDR-HL)+QC*(HLS-HL)-QEV*(HVS-HL)+
     1     QWR*(HWR-HL)+QCOND*(HLS-HL)+QSUP
C
C-Conservazione dell` energia nella zona vapore
C
      R2 = HVS-HV
C
C-Conservazione della massa nella zona liquida
C
      R3 = (QDR+QC-QEC-QEV+QWR+QCOND)/100.
C
C-Conservazione della massa DI VAPORE nel DEGASATORE
C
      R4 = QV+QVV+QEV-QC
C
C---per calcolare il regime si considerano nulli i primi membri
C---delle equazioni differenziali
C
      IF(KREGIM)THEN
	 RNI(1)=R1
	 RNI(2)=R2
	 RNI(3)=R3
	 RNI(4)=R4
	 GO TO 600
      ENDIF
C
C---per calcolare il transitorio si ordinano i secondi membri delle
C---equazioni differenziali con Gauss (TAU*X=R)
C
  500   CONTINUE
C
      CALL  DGNSOL(TAU11,TAU14,TAU22,TAU24,TAU31,
     1      TAU33,TAU34,TAU42,TAU43,TAU44,R1,R2,R3,R4,
     1      RNI(1),RNI(2),RNI(3),RNI(4))
C
      IF(Y.LT.1.E-2) RNI(3)=0.
C
C---calcolo residui
C
  600 continue
C
C-Calcolo pressione sul fondo
      RNI(5) = PF-P-9.80665*ROWS*Y/P0
C
      RETURN
      END
      SUBROUTINE  DGNSOL(A11,A14,A22,A24,A31,A33,A34,A42,
     1            A43,A44,B1,B2,B3,B4,X1,X2,X3,X4)
C
C**********CAVITA` DEGASATORE**********
C
C---risoluzione con Gauss A*X=B
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      X2=B2/A22
      X3=B3/A33
      X4=(B4-A43*X3)/A44
      X1=(B1-A14*X4)/A11
C
      RETURN
      END
      SUBROUTINE DGNJAC(AJAC,MX5,IXYU,XYU,DATI,IPD,RNI,IFUN,NEQ,NVAR)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION G1(8),RNI(*),AJAC(MX5,*),DATI(*),VAR(19), XYU(*)
C**********************21/11/88 SPELTA ****************************************
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C**********************21/11/88 SPELTA ****************************************
C
C**********CAVITA` DEGASATORE**********
C
C---calcolo jacobiano numerico
C
      CALL  DGNDEC(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1      HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,VCAV,RSERB,ALSERB,
     1      XYU,IXYU,DATI,IPD)
C
      CALL  DGNTAV(P,HL,HV,ROL,ROV,ROWS,BELI,BEVA,A2LI,
     1      A2VA,XL,XV,TLS,TV,HLS,HVS,PF)
C
      CALL  DGNTYP(Y,VL,DVLDY,RSERB,ALSERB)
C
      CALL  DGNTAU(A2LI,BELI,ROL,TLS,A2VA,BEVA,ROV,TV,Y,
     1      VCAV,VL,DVLDY,TAU11,TAU14,TAU22,TAU24,TAU31,
     1      TAU33,TAU34,TAU42,TAU43,TAU44)
C
      CALL  DGNDER(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1      HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,
     1      VCAV,RSERB,ALSERB,VL,DVLDY,
     1      ROL,ROV,ROWS,XL,XV,HLS,HVS,TLS,TV,
     1      IFUN,TAU11,TAU14,TAU22,TAU24,TAU31,TAU33,TAU34,
     1      TAU42,TAU43,TAU44,DATI,IPD,RNI)
C
C**********************21/11/88 SPELTA ****************************************
      EPSP=10./P0
C**********************21/11/88 SPELTA ****************************************
      DO 10 I = 1,NEQ
      G1(I) = RNI(I)
      IF(I.GT.4)G1(I) = -RNI(I)
   10 CONTINUE
      DO 30 I = 1,NVAR
      EPS = XYU(IXYU+I-1)*.001
      IF(ABS(EPS).LT.1.E-4)EPS = 1.E-4
C**********************21/11/88 SPELTA ****************************************
      IF(I.EQ.4.OR.I.EQ.7)EPS=EPSP
C**********************21/11/88 SPELTA ****************************************
      DO 15 J = 1,NVAR
      VAR(J) = XYU(IXYU+J-1)
      IF(J.EQ.I)VAR(J) = VAR(J)+EPS
   15 CONTINUE
C
      CALL  DGNDEC(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1      HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,VCAV,RSERB,ALSERB,
     1      VAR,1,DATI,IPD)
C
      CALL  DGNTAV(P,HL,HV,ROL,ROV,ROWS,BELI,BEVA,A2LI,
     1      A2VA,XL,XV,TLS,TV,HLS,HVS,PF)
C
      CALL  DGNTYP(Y,VL,DVLDY,RSERB,ALSERB)
C
      CALL  DGNDER(P,HL,HV,Y,PF,QV,HVI,QCOND,
     1      HCOND,QDR,HDR,QEC,QVV,HVV,QWR,HWR,
     1      VCAV,RSERB,ALSERB,VL,DVLDY,
     1      ROL,ROV,ROWS,XL,XV,HLS,HVS,TLS,TV,
     1      IFUN,TAU11,TAU14,TAU22,TAU24,TAU31,TAU33,TAU34,
     1      TAU42,TAU43,TAU44,DATI,IPD,RNI)
C
      DO 25 J = 1,NEQ
      IF(J.GT.4)RNI(J) = -RNI(J)
      AJAC(J,I) = (RNI(J)-G1(J))/EPS
   25 CONTINUE
   30 CONTINUE
C
      RETURN
      END
CC
      SUBROUTINE DEGND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $    XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
