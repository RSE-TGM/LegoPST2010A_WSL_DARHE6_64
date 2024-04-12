C**********************************************************************
C modulo plen.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)plen.f	5.2
C**********************************************************************
C***********************************************************************
C*                 COLLETTORE DI CONDOTTI ARIA-FUMI                    *
C***********************************************************************
C
      SUBROUTINE PLENI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/PLEN01/IBLOC
      COMMON/PLEN02/NE,NU
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'PLEN'/
C
C
C
C
      CALL PLENI4(IOB,MOD)
C
C
      NSTATI=2
      NUSCIT=0
      NINGRE=2*(NE+NU)
      NVAR=NINGRE+2
C
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('PFPL',A4,2X,'--US-- FLUID PRESSURE IN THE PLENUM ')
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('TFPL',A4,2X,
     $  '--US-- FLUID TEMPERATURE AT THE PLENUM OUTLET')
C
      DO 30 J=1,NE
      WRITE(IFO,3010)J,IOB,J
 3010 FORMAT('WE',I2,A4,2X,
     $ '--IN-- FLUID FLOW RATE INTO THE PLENUM N. ',I2)
   30 CONTINUE
C
      DO 40 J=1,NU
      WRITE(IFO,3020)J,IOB,J
 3020 FORMAT('WU',I2,A4,2X,
     $  '--IN-- FLUID FLOW RATE FROM THE PLENUM N. ',I2)
   40 CONTINUE
C
      DO 50 J=1,NE
      WRITE(IFO,3030)J,IOB,J
 3030 FORMAT('TE',I2,A4,2X,
     $  '--IN-- TEMPERATURE OF THE FLUID ENTERING THE PLENUM N. ',I2)
   50 CONTINUE
C
      RETURN
      END
      SUBROUTINE PLENI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/PLEN01/IBLOC
      COMMON/PLEN02/NE,NU
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      MAX=10
C
   10 WRITE(6,101) MAX
  101 FORMAT(10X,'PLENUM - FLUID PIPES COLLECTOR'/
     $       10X,'NUMBER OF INLET PIPES (01 -',I3,') ?')
      READ(5,*) NE
      IF(NE.LE.0.OR.NE.GT.MAX) THEN
      WRITE(6,102) NE
  102 FORMAT(10X,'ERROR - N.INL.=',I3,/)
      GOTO 10
      ENDIF
C
   15 WRITE(6,105) MAX
  105 FORMAT(10X,'NUMBER OF OUTLET PIPES (01 -',I3,') ?')
      READ(5,*) NU
      IF(NU.LE.0.OR.NU.GT.MAX) THEN
      WRITE(6,106) NU
  106 FORMAT(10X,'ERROR - N.OUT.=',I3,/)
      GOTO 15
      ENDIF
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
      SUBROUTINE PLENI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  NOMBL1,NOMBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*)
      DIMENSION XYU(*), DATI(*),CNXYU(*),TOL(*)
      CHARACTER*4 IVOL,IWI,IWO,IERG,IUM
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON /AUSIL1/ NSTATI,NUSCIT,NINGRE
      DATA IVOL,IWI,IWO /'VOL.','NWIN','NWOU'/
      DATA IERG,IUM     /'RGAS','UMID'      /
      DATA GAMMA,PRIF /1., 1.E+05/
C
      GOTO (1,10),IFUN
C
    1 WRITE(14,1000) IVOL,IWI,IWO
      WRITE(14,1000) IERG,IUM
      RETURN
C
   10 READ(14,2000)
      READ(14,2000) VOL,WI,WO
      READ(14,2000) RGAS,UMID
      IF(RGAS .EQ.1. ) RGAS = 287.
      IF(RGAS .EQ.2. ) RGAS = 274.
      NWI = WI
      NWO = WO
      WRITE(6,1002) VOL,RGAS
      IF ((2*NWI+NWO) .NE. NINGRE) WRITE(6,1001)
      DATI(ID1  )= VOL
      DATI(ID1+1)= RGAS
      DATI(ID1+2)= NWI
      DATI(ID1+3)= NWO
      DATI(ID1+4)= UMID
C
      ID2=ID1+4
C
      CNXYU(IV1  ) = PRIF
      CNXYU(IV1+1) = T0
      DO 20 N=1,NWI+NWO
   20 CNXYU(IV1+1+N) = W0
      N=1+NWI+NWO
      DO 21 N1=1,NWI
   21 CNXYU(IV1+N+N1) = T0
      WRITE(6,700) (CNXYU(IV1+J-1),J=1,2*NWI+NWO+2)
  700 FORMAT(/,1X,5(F12.1,3X))
      RETURN
C
 1000 FORMAT(3(4X,A4,5X,'=',10X,'*'),5X)
 2000 FORMAT(3(14X,F10.0,1X),5X)
 1001 FORMAT(//10X,'ERROR IN THE NUMBER OF FLOW RATES!!'//)
 1002 FORMAT(/10X,'VOLUME= ',F16.1,'  RGAS=',E10.2)
C
      END




      SUBROUTINE PLENC1(IFUN,AJAC,MX5,IXYU,XYU,ID2,
     $                  DATI,RN,NOMBL1,NOMBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER  ( NWMAX=10 )
      LOGICAL KREGIM
      DIMENSION  AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      COMMON     /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
C Common LEGO per determinare le soluzioni del passo precedente
      COMMON/PARPAR/NULL(7),ITERT
      COMMON/REGIME/KREGIM
      DIMENSION  WI(NWMAX), WO(NWMAX), TI(NWMAX), HI(NWMAX)
      DIMENSION WIP(NWMAX),WOP(NWMAX)
      DATA GAMMA,EPS,PRIF/1.,1.,1.E+05/
C
C
      NOU = DATI(ID2+3)
      NIN = DATI(ID2+2)
C
      GOTO(10,20,20), IFUN
C
   10 DO 11 K=2,NIN+NOU+2
   11 AJAC(1,K) = 1.
      DO 12 K=2,2+2*NIN+NOU
   12 AJAC(2,K) = 1.
      RETURN
C
C
   20 VOL = DATI(ID2  )
      RGAS= DATI(ID2+1)
      NIN = DATI(ID2+2)
      NOU = DATI(ID2+3)
      UMID= DATI(ID2+4)
C
      PP  = XYU(IXYU)*PRIF
      TU  = XYU(IXYU+1)*T0
      DO N=2,NIN+1
	 WI(N-1) = XYU(IXYU+N)*W0
      ENDDO
      N   = NIN+1
C
      DO 22 N1=1,NOU
   22 WO(N1)= XYU(IXYU+N+N1)*W0
      N1  = NOU
C
      DO 23 N2=1,NIN
   23 TI(N2)= XYU(IXYU+N+N1+N2)*T0
C
C
      DO 24 K=1,NIN
   24 HI(K) = HTFU(TI(K),UMID,1)
      HU    = HTFU(TU   ,UMID,1)
C
C
C
      RO= PP/RGAS/TU
      DRODP = 1./RGAS/TU/GAMMA
      C1    = VOL*DRODP*PRIF
C
C
      RN1 = 0.
      RN2 = 0.
      DO 25 N=1,NIN
   25 RN1 = RN1+WI(N)
      DO 26 N=1,NOU
   26 RN1 = RN1 -WO(N)
      IF(IFUN .EQ. 3)  GOTO 30
      RN(1) = RN1/C1
C
      DO K=1,NIN
	 IF(WI(K).GT.0.) THEN
	    RN2=WI(K)*HI(K)+RN2
	 ELSE
	    RN2=WI(K)*HU+RN2
	 ENDIF
      ENDDO

      DO K=1,NOU
	 IF(WO(K).GT.0.) THEN
	    RN2=-WO(K)*HU+RN2
	 ELSE
	    RN2=-WO(K)*HU+RN2
	 ENDIF
      ENDDO
C
      RN(2) = RN2/T0/(RO*VOL*(CPFU(TU,UMID)-RGAS))
C
      RETURN
C
   30 CONTINUE
C
C-----DERIVATA DELL'EQUAZIONE DELLA MASSA RISPETTO A TU
C
      AJAC(1,2) = RN1/TU*T0/C1
C
      C1 = 1./C1*W0
      DO 31 N=1,NIN
   31 AJAC(1,N+2) = C1
      DO 32 N=1,NOU
   32 AJAC(1,2+NIN+N) = -C1
C
C-----DERIVATE DELL'EQUAZIONE DELL'ENERGIA
C
      DEN= RO*VOL*(CPFU(TU,UMID)-RGAS)

      WTOT = 0.
      DO K=1,NOU
	 IF(WO(K).GT.0.) WTOT = WTOT+WO(K)
      ENDDO
      DO K=1,NIN
	 IF(WI(K).LT.0.) WTOT = WTOT+WI(K)
      ENDDO
C
      IF(((KREGIM).AND.(WTOT.LT.1.E-5)))THEN
	 AJAC(2,2)=-1.
	 RETURN
      ELSE
	 AJAC(2,2) = -CPFU(TU,UMID)*WTOT/DEN
      ENDIF
C
      DO K=1,NIN
	IF(WI(K).GT.0.) THEN
	   AJAC(2,K+2) =HI(K)*W0/T0/DEN
	ELSE
	   AJAC(2,K+2) =HU*W0/T0/DEN
	ENDIF
      ENDDO

      DO K=1,NOU
	IF(WO(K).GT.0.) THEN
	   AJAC(2,K+2+NIN) =-HU*W0/T0/DEN
	ELSE
	   AJAC(2,K+2+NIN) =-HU*W0/T0/DEN
	ENDIF
      ENDDO

      K1 = 2+NIN+NOU
      DO K=1,NIN
	IF(WI(K).GT.0.) THEN
	   AJAC(2,K+K1) =WI(K)*CPFU(TI(K),UMID)/DEN
	ELSE
	   AJAC(2,K+K1) = 0.
	ENDIF
      ENDDO

      RETURN
      END
C
      SUBROUTINE PLEND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $   XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 IBLOC, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
      DATA PRIF /1.E+05/
C
      NIN = DATI(IPD+2)
      NOU = DATI(IPD+3)
C
C-----Equazione n. 1 (differenziale):
C
      SIGNEQ(1) = 'MASS CONSERVATION EQUATION'
      UNITEQ(1) = 'Pa/s'
      COSNOR(1) = PRIF
C
      DO 10 I = 2,NIN+NOU+2
   10   ITOPVA(1,I) = 1
C
C-----Equazione n. 2 (differenziale):
C
      SIGNEQ(2) = 'ENERGY CONSERVATION EQUATION'
      UNITEQ(2) = 'W'
      COSNOR(2) = H0*W0
C
      DO 30 I = 1,NIN*2+NOU+2
   30   ITOPVA(2,I) = 1
C
      RETURN
      END
