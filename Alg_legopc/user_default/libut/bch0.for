      SUBROUTINE BCH0I3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C*******************************************************************
C   EVAPORATION CELL CONNECTION CHANNEL  26.02.2001
C*******************************************************************
C
      COMMON/BCH00/IBLOC
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 NOMAPP
      CHARACTER*4 MOD
      DATA MOD/'BCH0'/

C
      CALL BCH0I4(IOB,MOD)
C

      NSTATI=0
      NUSCIT=1
      NINGRE=11
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3000)IOB
 3000 FORMAT('WTUB',A4,2X,'--UA-- FLOW RATE THROUGH THE HEAD LOSS ')
      WRITE(IFO,3001)IOB
 3001 FORMAT('PITU',A4,2X,'--IN-- PRESSURE AT THE HEAD LOSS INLET ')
      WRITE(IFO,3002)IOB
 3002 FORMAT('PIFO',A4,2X,'--IN-- INLET BOTTOM PRESSURE           ')
      WRITE(IFO,3003)IOB
 3003 FORMAT('PUTU',A4,2X,'--IN-- PRESSURE AT THE HEAD LOSS OUTLET')
      WRITE(IFO,3004)IOB
 3004 FORMAT('PUFO',A4,2X,'--IN-- OUTLET BOTTOM PRESSURE          ')
      WRITE(IFO,3005)IOB
 3005 FORMAT('HTUB',A4,2X,'--IN-- ENTHALPY AT HEAD LOSS IN/OUT    ')
      WRITE(IFO,3006)IOB
 3006 FORMAT('AKTB',A4,2X,'--IN-- HEAD LOSS CORRECTOR COEFFICIENT ')
      WRITE(IFO,3007)IOB
 3007 FORMAT('ZUPS',A4,2X,'--IN-- LEVEL UPSTREAM HEAD LOSS        ')
      WRITE(IFO,3008)IOB
 3008 FORMAT('ZDWN',A4,2X,'--IN-- LEVEL DOWNSTREAM HEAD LOSS      ')
      WRITE(IFO,3009)IOB
 3009 FORMAT('FNAC',A4,2X,'--IN-- NaCl INLET MASS FRACTION        ') 
      WRITE(IFO,3010)IOB
 3010 FORMAT('FINV',A4,2X,'--IN-- NaCl MASS FRACTION (FLOW INVERSION)')
      WRITE(IFO,3011)IOB
 3011 FORMAT('HINV',A4,2X,'--IN-- ENTHALPY AT INLET (FLOW INVERSION) ')
C
      RETURN
      END
C******************************************************************************
      SUBROUTINE BCH0I4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/BCH00/IBLOC
      CHARACTER*4 IOB,MOD
      CHARACTER*8 IBLOC
C
      WRITE(IBLOC,'(2A4)')MOD,IOB
C
      RETURN
      END
C******************************************************************************
      SUBROUTINE BCH0I2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,NOM1,NOM2,
     $ IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 CO,FN,W1,P1,P2,H1,Z1,Z2,TC
      INTEGER VAR
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      COMMON / NORM / P0,H0,T0,Q0,R0,AL0,V0,DP0
      DATA FN/'FR.NaCl '/,TC/'CAL.TYPE'/
      DATA W1/'MASS FL.'/,P1/'P.UPSTR '/
      DATA P2/'P.DOWNS '/,H1/'ENTHALP.'/
      DATA Z1/'UPS.DEAD'/,Z2/'DWN.DEAD'/
C
      GO TO (1,10),IFUN
C
C      SCRITTURA DEI SIMBOLI SUL FILE 14
C
    1 WRITE(14,1010)
 1010 FORMAT('*   DATA TO BE ASSIGNED TO DEFINE THE HEAD LOSS')
      WRITE(14,1020) W1,P1,P2,H1,FN
      WRITE(14,1011)
 1011 FORMAT('*   UPSTREAM-DOWNSTREAM DEAD LEVELS')
      WRITE(14,1020)Z1,Z2
 1020 FORMAT(3(4X,A8,' =',10X,'*'))
      WRITE(14,1030)
 1030 FORMAT('*   CALCULATION TYPE               ')
      WRITE(14,1020)TC 
      RETURN
C
C      LETTURA  DEI DATI DAL FILE 14
C
   10 READ(14,1070)
      READ(14,1070)
      READ(14,1070) WL,PM,PV,H,FDAT,CS
      READ(14,1070)
      READ(14,1070) ZUP,ZDWN
      READ(14,1070)
      READ(14,1070) TCAL
 1070 FORMAT(3(14X,F10.0,1X))
C
C   CALCOLO DEL COEFFICIENTE DI PERDITA DI CARICO
C
        ICAL=TCAL
        IF(ICAL.NE.1.AND.ICAL.NE.2) THEN
         WRITE(6,*) 'CAL.TYPE may only be set to 1 or 2!!'
         STOP
        ENDIF
C
	RK0=0.
        PMD=0.5*PM+0.5*PV
C
	IFL=1
C       S=SHEV(PMD,H,IFL)
C       RO=ROEV(PMD,S,IFL)
        CALL T_FOR(PMD,H,FDAT,T)
        CALL ROC_FOR(FDAT,T,PMD,RO)
C       WRITE(6,*) 'BCH0 = ',PMD,H,RO
        IF(ICAL.EQ.1) THEN
	   RK0=2.*(PM-PV)*RO/(WL*WL+.1*WL)*Q0*Q0/P0
        ELSE
           RK0=WL/SQRT((PM-PV)*RO)
        ENDIF
C
C       MEMORIZZAZIONE DATI
C
      DATI(ID1)=RK0
      DATI(ID1+1)=ZUP
      DATI(ID1+2)=ZDWN
      DATI(ID1+3)=TCAL
      ID2=ID2+3
C
C   COSTANTI DI NORMALIZZAZIONE
C
      CNXYU(IV1   )=Q0
      CNXYU(IV1+1 )=P0
      CNXYU(IV1+2 )=P0
      CNXYU(IV1+3 )=P0
      CNXYU(IV1+4 )=P0
      CNXYU(IV1+5 )=H0
      CNXYU(IV1+6 )=1.
      CNXYU(IV1+7 )=1.
      CNXYU(IV1+8 )=1.
      CNXYU(IV1+9 )=1.
      CNXYU(IV1+10)=1.
      CNXYU(IV1+11)=H0

C
      RETURN
      END
C******************************************************************************
      SUBROUTINE BCH0C1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,NOM1,NOM2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
C
      EXTERNAL BCH0
C
C     IFL=1
      GO TO (10,20,30),IFUN
C
C     DEFINIZIONE DELLA TOPOLOGIA
C
   10 CALL BCH0JC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
      RETURN
C
   20 CALL BCH0(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
   30 CALL BCH0JC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)    
      RETURN
C      
      END
C******************************************************************************
      SUBROUTINE BCH0 (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      RK0= DATI(IPD  )
      ZDUP=DATI(IPD+1)
      ZDDW=DATI(IPD+2)
      TCAL=DATI(IPD+3)
C
      ICAL=TCAL
C
      W   =XYU(IXYU   )
      PCM =XYU(IXYU+1 )
      PFM =XYU(IXYU+2 )
      PCV =XYU(IXYU+3 )
      PFV =XYU(IXYU+4 )
      HDIR=XYU(IXYU+5 )
      FC  =XYU(IXYU+6 )
      ZUP =XYU(IXYU+7 )
      ZDW =XYU(IXYU+8 )
      FDIR=XYU(IXYU+9 )
      FINV=XYU(IXYU+10)
      HINV=XYU(IXYU+11)
C
      IF (W .GE. 0) THEN
        F=FDIR
        H=HDIR
      ELSE
        F=FINV
        H=HINV
      ENDIF
C
      IF (ZUP.LE.ZDUP) THEN
         PM=PCM
      ELSE
         PM=PCM+(PFM-PCM)*(ZUP-ZDUP)/ZUP
      ENDIF
      IF (ZDW.LE.ZDDW) THEN
         PV=PCV
      ELSE
         PV=PCV+(PFV-PCV)*(ZDW-ZDDW)/ZDW
      ENDIF
C
      DP = PM-PV
      PMED=(0.5*PM+0.5*PV)*P0
C     S=SHEV(PMED,H*H0,IFL)
C     RO=ROEV(PMED,S,IFL)
      CALL T_FOR(PMED,H*H0,F,T)
      CALL ROC_FOR(F,T,PMED,RO) 
C
      IF(ICAL.EQ.1) THEN
         RNI(1) = DP-FC*RK0/RO/2.*(W*ABS(W)+.1/Q0*W)
      ELSE
         IF (DP.GE.0) THEN
            RNI(1) = W-(FC*RK0*SQRT(RO*DP*P0))/Q0
         ELSE
            RNI(1) = W+(FC*RK0*SQRT(RO*ABS(DP)*P0))/Q0
         ENDIF
      ENDIF
C
      RETURN
C
      END
C******************************************************************************      
      SUBROUTINE BCH0JC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      EXTERNAL BCH0
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 DO I=1,11
         AJAC(1,I)=1.
      ENDDO
      RETURN
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 1
      NINGRE = 11
      EPS    = 1.E-3
      EPSLIM = 1.E-4
C
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,BCH0)
C
      RETURN
      END
C******************************************************************************
      SUBROUTINE BCH0D1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $ XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
