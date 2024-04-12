      SUBROUTINE STAZI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/STAZ01/IBLOC
      COMMON/STAZ02/LINAM,NVR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'STAZ'/
C
C
      CALL STAZI4(IOB,MOD)
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3007)IOB
 3007 FORMAT('WAMM',A4,2X,
     $  '--UA-- STEAM TOTAL FLOW RATE INTO THE TURBINE')
      WRITE(IFO,3006)IOB
 3006 FORMAT('HCRT',A4,2X,
     $  '--UA-- ENTHALPY OF STEAM IN THE WHEEL CHAMBER')
      WRITE(IFO,3008)IOB
 3008 FORMAT('QMEC',A4,2X,'--UA-- MECHANICAL POWER')
      WRITE(IFO,4007)IOB
 4007 FORMAT('WAM1',A4,2X,
     $  '--UA-- STEAM FLOW RATE AT VALVE 1 INLET')
      WRITE(IFO,5007)IOB
 5007 FORMAT('WAM2',A4,2X,
     $  '--UA-- STEAM FLOW RATE AT VALVE 2 INLET')
      DO I=1,NVR
      WRITE(IFO,5015)I,IOB,I
 5015 FORMAT('AR',I2,A4,2X,
     $  '--UA-- LIFT OF THE REGULATING VALVE ',I2)
      ENDDO
      DO I=1,NVR
      WRITE(IFO,6015)I,IOB,I
 6015 FORMAT('PU',I2,A4,2X,
     $  '--UA-- PRESSURE UPSTREAM THE NOZZLES ',I2)
      ENDDO
C
      IF(LINAM.EQ.2) THEN
C
      WRITE(IFO,3000) IOB
 3000 FORMAT('ZVA1',A4,2X,'--IN-- POSITION OF INLET VALVE 1')
      WRITE(IFO,3001) IOB
 3001 FORMAT('ZVA2',A4,2X,'--IN-- POSITION OF INLET VALVE 2')

      WRITE(IFO,3002)IOB
 3002 FORMAT('PAM1',A4,2X,'--IN-- PRESSURE UPSTREAM INLET VALVE 1')
      WRITE(IFO,4002)IOB

 4002 FORMAT('PAM2',A4,2X,'--IN-- PRESSURE UPSTREAM INLET VALVE 2')
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('HAM1',A4,2X,
     $  '--IN-- STEAM ENTHALPY UPSTREAM INLET VALVE 1')
      WRITE(IFO,4005)IOB
 4005 FORMAT('HAM2',A4,2X,
     $  '--IN-- STEAM ENTHALPY UPSTREAM INLET VALVE 2')
C
      ELSE
C
      WRITE(IFO,5001)IOB
 5001 FORMAT('ZVA1',A4,2X,'--IN-- POSITION OF INLET VALVE')

      WRITE(IFO,5002)IOB
 5002 FORMAT('PAMM',A4,2X,
     $  '--IN-- STEAM PRESSURE AT THE TURBINE INLET')

      WRITE(IFO,5003)IOB
 5003 FORMAT('HAMM',A4,2X,
     $  '--IN-- STEAM ENTHALPY AT THE TURBINE INLET')
      ENDIF
C
      WRITE(IFO,3009)IOB
 3009 FORMAT('PCRT',A4,2X,
     $  '--IN-- STEAM PRESSURE IN THE WHEEL CHAMBER')
C
      WRITE(IFO,3010)IOB
 3010 FORMAT('SEAV',A4,2X,
     $  '--IN-- TURBINE START BUTTON')

      WRITE(IFO,3015)IOB
 3015 FORMAT('ALZS',A4,2X,
     $  '--IN-- SERVOMOTOR POSITION OF THE REGULATING VALVES')
C
      WRITE(IFO,3016)IOB
 3016 FORMAT('RPMT',A4,2X,'--IN-- TURBINE ROTATIONAL VELOCITY')
C
      WRITE(IFO,3017)IOB
 3017 FORMAT('FARC',A4,2X,'--IN-- PARTIAL ARC (0) OR FULL ARC (1)')
C
      DO I=1,NVR
      WRITE(IFO,5016)I,IOB,I
 5016 FORMAT('AT',I2,A4,2X,
     $'--IN-- POSITION OF THE REGULATING VALVE TESTER',I2)
      ENDDO
C
      RETURN
      END
      SUBROUTINE STAZI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/STAZ01/IBLOC
      COMMON/STAZ02/LINAM,NVR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER RIS
C
      WRITE(IBLOC,'(2A4)')MOD,IOB
C
  666 WRITE(6,*)
      WRITE(6,*)'     ARE THERE TWO INLET LINES ? [Y/N]'
      READ(5,5555)RIS
 5555 FORMAT(A)
      LINAM = 0
      IF(RIS.EQ.'Y' .OR. RIS.EQ.'y') THEN
       LINAM = 2
      ELSE IF(RIS.EQ.'N' .OR. RIS.EQ.'n') THEN
       LINAM = 1
      ENDIF
      IF (LINAM.EQ.0) GOTO 666
  777 WRITE(6,*)
      WRITE(6,*)'     HOW MANY REGULATION VALVES ? [MAX=16]'
      READ(5,*) NVR
      IF (NVR.GT.16 .OR. NVR.LT.1) GOTO 777
      RETURN
      END
      SUBROUTINE STAZI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBLOC1,IBLOC2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      COMMON /NORM/  P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      CHARACTER*10 TIPXTURB
      CHARACTER*36 TIPO
      CHARACTER*4 PAVV,HAVV,WAVV
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
      DATA PAVV/ 'PAVV'/, HAVV/ 'HAVV'/, WAVV/ 'WAVV'/
C
      NVR=(NUSCIT-5)/2
      LINAM=(NINGRE-NVR-5)/3
C
      GOTO(1,10),   IFUN

   1  WRITE(14,1110)
      WRITE(14,1111) PAVV, HAVV, WAVV
 1110 FORMAT(4X,'TIP_TURB =',10X,'*',7X,'ZETAM =',10X,'*')
 1111 FORMAT(3(4X,A4,4X,' =',10X,'*'))

      RETURN
C
C----  lettura dei dati da file 14
C
 10   READ(14,1002)
 1002 FORMAT(14X,A10,1X,14X,F10.0,5X)
      READ(14,1002)TIPXTURB,ZETAM
 1003 FORMAT(3( 14X,F10.0,1X))
      READ(14,1003) PAV,HAV,WAV
C
      ITYP=0
      IF(TIPXTURB.EQ.'ANSALDO320') ITYP=1
      IF(TIPXTURB.EQ.'TOSI320')    ITYP=2
      IF(TIPXTURB.EQ.'TOSI660')    ITYP=3
      IF(TIPXTURB.EQ.'ANSALDO660') ITYP=4

C
C CALCOLO PER LA VALVOLA DI AMMISSIONE DEL VALORE MASSIMO DEL COEFFICIENTE
C DI SCARICO IN CONDIZIONE DI AVVIAMENTO
C
      SOAV = SHEV(PAV,HAV,1)
      ROAV = ROEV(PAV,SOAV,1)

      CK = 1.3
      ALFA = (CK -1.)/CK
      R = (2./ (CK + 1.))**(CK/ (CK -1.))
      CVAM = WAV/(SQRT(PAV*ROAV)* SQRT(1-R))
C
      DATI(ID1  )=LINAM
      DATI(ID1+1)=NVR
      DATI(ID1+2)=ITYP
      DATI(ID1+3)=CVAM
      DATI(ID1+4)=ZETAM
      ID2 =ID1+4
C
C
      IPRNT=2
      zvva=1.
C
C_____ CARICAMENTO , INIZIALIZZAZIONE E STAMPA DATI TURBINA
C
      CALL SXSTAZ (IPRNT,ITYP,TIPO,
     $            R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $            CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $            PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $            RCA,XF,WF,IAM,zvva)
C
C
C-----COSTANTI DI NORMALIZZAZIONE
C
   20 CONTINUE
C
      CNXYU(IV1  )= W0
      CNXYU(IV1+1)= H0
      CNXYU(IV1+2)= W0*H0
      CNXYU(IV1+3)= W0
      CNXYU(IV1+4)= W0
C_____ POSIZIONI VR
      DO I=1,NVR
      CNXYU(IV1+4+I)= 1.
      ENDDO
C_____ PRESSIONI A MONTE UGELLI
      DO I=1,NVR
      CNXYU(IV1+4+I+NVR)= P0
      ENDDO
C
      JJ=IV1+2*NVR
C___ 2 LINEE DI AMMISSIONE
      IF(LINAM.EQ.2) THEN
	CNXYU(JJ+5)= 1.
	CNXYU(JJ+6)= 1.
	CNXYU(JJ+7)= P0
	CNXYU(JJ+8)= P0
	CNXYU(JJ+9)= H0
	CNXYU(JJ+10)= H0
	CNXYU(JJ+11)= P0
	CNXYU(JJ+12)=1.
	CNXYU(JJ+13)= 1.
	CNXYU(JJ+14)= 300.
	CNXYU(JJ+15)= 1.
	JK=JJ+15
      ELSE
C___ 1 LINEA DI AMMISSIONE
	CNXYU(JJ+5)= 1.
	CNXYU(JJ+6)= P0
	CNXYU(JJ+7)= H0
	CNXYU(JJ+8)= P0
	CNXYU(JJ+9)= 1.
	CNXYU(JJ+10)=1.
	CNXYU(JJ+11)= 300.
	CNXYU(JJ+12)= 1.
	JK=JJ+12
      ENDIF
C
C_____ POSIZIONI VR PROVA VALVOLE
      DO I=1,NVR
      CNXYU(JK+I)= 1.
      ENDDO
      RETURN
      END
C
      SUBROUTINE STAZC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $                  IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      COMMON /NORM/  P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/NEQUAZ/NEQMOD
      LOGICAL KREGIM
      EXTERNAL STAZ
C
      LINAM= DATI(IPD  )
      NVR  = DATI(IPD+1)
      TYP  = DATI(IPD+2)
C
      NEQMOD=5
C
      NEQ= 5
      IF(KREGIM)NEQ=5+2*NVR
      NVAR=5+ 2* NVR +LINAM*3+5+NVR
C
      GOTO(10,20,30),   IFUN
   10 CONTINUE
C
C-----TOPOLOGIA MATRICE JACOBIANA IN TRANSITORIO
C
      DO J=1,NEQ
       DO I=1,NVAR
       AJAC(J,I)=1.
       ENDDO
      ENDDO
C
      RETURN
C
C-----CALCOLO RESIDUI
C
   20 CALL STAZ(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
   30 CONTINUE
C
C-----CALCOLO MATRICE JACOBIANA
C
      NRIG=NEQ
      NCOL=NVAR
      EPS=1.E-3
      EPSLIM=1.E-4
      CALL STAZJC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NRIG,NCOL,EPS,EPSLIM,STAZ)
      RETURN
      END
C
      SUBROUTINE STAZJC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1               NRIG,NCOL,EPS,EPSLIM,RESIDUI)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
      EXTERNAL RESIDUI
C
C
C     residui(ifun,ixyu,xyu,ipd,dati,rn)
C
      CALL RESIDUI(3,IXYU,XYU,IPD,DATI,RN)
C
      DO 30 J=1,NCOL
      VAR=EPS*XYU(IXYU+J-1)
      IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C
      DO 10 K=1,NCOL
      CXYU(K)=XYU(IXYU+K-1)
      IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
   10      CONTINUE
C
      CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(-CRN(I)+RN(I))/VAR
   20      CONTINUE
C
   30      CONTINUE
C
      RETURN
      END
      SUBROUTINE STAZ(IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION XYU(*),DATI(*),RNI(*)
      COMMON /NORM/  P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
      DIMENSION AZVR(16),APVR(16),ACVR(16),PMUG(16),PMUGC(16)
      CHARACTER*36 TIPO
      LOGICAL SEAV
      DATA ILETT/0/
C
C-----DECODIFICA DATI
C
      LINAM= DATI(IPD  )
      NVR  = DATI(IPD+1)
      ITYP = DATI(IPD+2)
      CVAM = DATI(IPD+3)
      ZETAM= DATI(IPD+4)
      zvva=1.
C
C
C-----CARICAMENTO DEI DATI DA SUBROUTINE
C
      IF(ILETT.EQ.0) THEN
      CALL SXSTAZ (0,ITYP,TIPO,
     $            R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $            CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $            PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $            RCA,XF,WF,IAM,zvva)
C
      CALL STAZCVA(CEME,CVAM,ZETAM,A2,B1,C0)
C
      ILETT= 1
      ENDIF
C
C
C-----DECODIFICA VARIABILI
C
C
      WCR=XYU(IXYU  )*W0
      HCR = XYU(IXYU+1)*H0
      PMEC= XYU(IXYU+2)
      WVA1= XYU(IXYU+3)*W0
      WVA2= XYU(IXYU+4)*W0
      DO I=1,NVR
       AZVR(I)=XYU(IXYU+4+I)
      ENDDO
      DO I=1,NVR
       PMUG(I)=XYU(IXYU+4+I+NVR)
      ENDDO
C
      JJ=IXYU+2*NVR
      IF(LINAM.EQ.2) THEN
C
       ZVA1= XYU(JJ+5)
       ZVA2= XYU(JJ+6)
       PSH1= XYU(JJ+7)*P0
       PSH2= XYU(JJ+8)*P0
       HSH1= XYU(JJ+9)*H0
       HSH2= XYU(JJ+10)*H0
       PCR = XYU(JJ+11)*P0
       ISEAV= ABS(XYU(JJ+12))+.1
       IF(MOD(ISEAV,2).NE.0) THEN
	SEAV=.TRUE.
       ELSE
	SEAV=.FALSE.
       ENDIF
       X   = XYU(JJ+13)
C ! FREQUENZA IN HERTZ
       RPS = XYU(JJ+14)*5.
       FARC= XYU(JJ+15)
       JK=JJ+15
      ELSE
       ZVA1= XYU(JJ+5)
       PSH1= XYU(JJ+6)*P0
       HSH1= XYU(JJ+7)*H0
       PCR = XYU(JJ+8)*P0
       ISEAV= ABS(XYU(JJ+9))+.1
       IF(MOD(ISEAV,2).NE.0) THEN
	SEAV=.TRUE.
       ELSE
	SEAV=.FALSE.
       ENDIF
       X   = XYU(JJ+10)
C ! FREQUENZA IN HERTZ
       RPS = XYU(JJ+11)*5.
       FARC= XYU(JJ+12)
       JK=JJ+12
      ENDIF
C____ POSIZIONE DATA DAL PROVAVALVOLE VR
      DO I=1,NVR
       APVR(I)=XYU(JK+I)
      ENDDO
C
C-----CALCOLO RESIDUI
C
      IF (SEAV) THEN
C-----CALCOLO RESIDUI IN CONDIZIONI DI AVVIAMENTO
C
      CALL STAZAV(PSH1,PSH2,HSH1,HSH2,PCR,RPS,WCR,X,WF20,
     $HF20,WAM1,WAM2,LINAM,ZETAM,ZVA1,ZVA2,NVR,ACVR,APVR,
     $PMUG,PMUGC,R,AALAM,UDVU,CCR,AETA,BETA,NVALV,CA,CCF,
     $AUG,NIA,CAV,NIPF,CPVF,ALFA,HRIF,IAM,CVAM,A2,B1,C0)
      ELSE
C-----CALCOLO RESIDUI DOPO IL PARALLELO
C
      CALL SXMGT18(PSH1,PSH2,HSH1,HSH2,PCR,RPS,WCR,X,FARC,
     $          WF20,HF20,WAM1,WAM2,LINAM,NVR,ACVR,APVR,PMUG,PMUGC,
     $          R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $          CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $          PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $          RCA,XF,WF,IAM,zva1,zva2)
C
      ENDIF
 101  IF(WF20 .LT..01) THEN
	RNI(1)=WCR/W0
	RNI(4)=  WVA1/W0
	RNI(5)=  WVA2/W0
	RNI(2)=(HCR-HSH1)/H0/100.
	RNI(3)=PMEC
C
      ELSE
	RNI(1)=  (WCR-WVA1-WVA2)/W0
	RNI(2)=  (HCR-HF20)/H0/100.
	IF(LINAM.EQ.2) THEN
	   RNI(3)=  PMEC-(WVA1*(HSH1-HCR)+WVA2*(HSH2-HCR))/(W0*H0)
	ELSE
	   RNI(3)=  PMEC-WCR*(HSH1-HCR)/(W0*H0)
	ENDIF
	RNI(4)=  (WVA1-WAM1)/W0
	RNI(5)=  (WVA2-WAM2)/W0
      ENDIF
C
C
C_______ VARIABILI DI USCITA (NON EQUAZIONI)
C        NVR POSIZIONI DI VALVOLE REGOLANTI
C        NVR PRESSIONI A MONTE UGELLI
C
      IF(KREGIM) THEN
	DO I=1,NVR
	RNI(5+I)=AZVR(I)- ACVR(I)
	ENDDO
	DO I=1,NVR
	RNI(5+I+NVR)= PMUG(I)-PMUGC(I)/P0
	ENDDO
      ELSE
C
	DO I=1,NVR
	RNI(5+I)= ACVR(I)
	  IF(IFUN.EQ.3)RNI(5+I)= 0.
	ENDDO
	DO I=1,NVR
	RNI(5+I+NVR)= PMUGC(I)/P0
	  IF(IFUN.EQ.3)RNI(5+I+NVR)= 0.
	ENDDO
      ENDIF
C
      RETURN
      END
C
      SUBROUTINE STAZAV(PSH1,PSH2,HSH1,HSH2,PCR,RPS,WCR,X,
     $WF20,HF20,WAM1,WAM2,LINAM,ZETAM,ZVA1,ZVA2,NVR,ACVR,
     $APVR,PMUG,PMUGC,R,AALAM,UDVU,CCR,AETA,BETA,NVALV,CA,CCF,
     $AUG,NIA,CAV,NIPF,CPVF,ALFA,HRIF,IAM,CVAM,A2,B1,C0)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              CPVF(10,4),IAM(16)
C
      COMMON /SXAF2018/ W(16)
      DIMENSION ACVR(16),APVR(16),PMUG(16),PMUGC(16)
C
      HW = 0.
C
C____ LOOP SUL NUMERO DI LINEE DI AMMISSIONE
      DO II=1,2
      IF (LINAM.EQ.1.OR.II.EQ.1) THEN
	PSH=PSH1
	HSH=HSH1
	ZEVA=ZVA1
      ELSE
	PSH=PSH2
	HSH=HSH2
	ZEVA=ZVA2
      ENDIF
C-----CALCOLO DELLA PORTATA
C_____PROTEZIONE PER HSH < HRIF
      WF20=0.
      IF(HSH.LE.HRIF) GO TO 500
      U=UDVU*RPS
      PSRO=ALFA*(HSH-HRIF)
      ROSH=PSH/PSRO
      IF (PCR.GT.PSH) GOTO 500
      TET=2.*PSRO/PCR/PCR*ALFA
      SPSRO=SQRT(PSRO)
C
C_____ CALCOLO DELLA PORTATA NELLE VALVOLE DI AMMISSIONE E DI REGOLAZIONE
C      IPOTIZZANDO SEMPRE UN "SALTO CRITICO".
C
      CALL STAZPORT(PSH,ROSH,X,WF20,II,APVR,ACVR,R,
     $UDVU,NVALV,CA,CCF,AUG,NIA,CAV,NIPF,CPVF,ALFA,
     $HRIF,IAM,ZEVA,ZETAM,CVAM,A2,B1,C0,PCR)
C
      IF(II.EQ.1) THEN
       WAM1=WF20
      ELSE
       WAM2=WF20
      ENDIF
C
C-----CALCOLO ENTALPIA IN CAMERA RUOTA
C
      DO 285 IV=1,NVALV
C____ TEST PER VEDERE SE LA VALVOLA REGOLANTE APPARTIENE AL SETTORE
C      DELLA VALVOLA DI AMMISSIONE II
       IF(II. NE. IAM(IV)) GO TO 285
C
      IF(W(IV).LE.0.) THEN
       PMUGC(IV)=PCR
       GOTO 285
      ENDIF
C
      PUSS = W(IV)/AUG(IV)/AALAM*SPSRO
      IF(PUSS.LT.(PCR/R)) GO TO 201
C
C-----UGELLI CRITICI
C
      PUG= PUSS
C____ MEMORIZZAZIONE PRESSIONE A MONTE UGELLI
      PMUGC(IV)=PUSS
C*******(SPELTA 21-5-90)
      PCRPUA=(ABS(PCR/PUG))**ALFA
C*******
      GOTO 215
C
C-----UGELLI SOTTOCRITICI
  201 CONTINUE

      PCRPUA=2./(1.+SQRT(1.+TET*(W(IV)/AUG(IV))**2))
C____ MEMORIZZAZIONE PRESSIONE A MONTE UGELLI
      PMUGC(IV)=PCR/(PCRPUA**(1./ALFA))
215      CONTINUE
C
      HISO=HRIF+(HSH-HRIF)*PCRPUA
      DHSH=HSH-HISO
      IF(DHSH.LE.0.) THEN
	 C=0.
	 RUC=0.
      ELSE
	 C=SQRT(2.*DHSH)
	 IF(C.LT.1.E-3) THEN
	  RUC=0.
	 ELSE
	  RUC=U/C
	 ENDIF
      ENDIF
      ETA=(AETA*RUC+BETA)*RUC
      IF(ETA.LT..1)ETA=.1
      HUG=HSH-ETA*(HSH-HISO)
      HW= HW+HUG*W(IV)
C
C
  285 CONTINUE
C____ FINE LOOP SULLE VALVOLE DI AMMISSIONE
      ENDDO
C
C____ PORTATA TOTALE
      WF20=WAM1+WAM2
C
C
      HF20=HSH1
C !!!! protezione per portata nulla
      IF(WF20.GE..01)HF20 = HW/WF20
	RETURN
C
  500 CONTINUE
      WF20=0.
      HF20=HSH
      RETURN
      END
      SUBROUTINE STAZPORT(PSH,ROSH,X,WF20,II,APVR,ACVR,
     $R,UDVU,NVALV,CA,CCF,AUG,NIA,CAV,NIPF,CPVF,ALFA,
     $HRIF,IAM,ZEVA,ZETAM,CVAM,A2,B1,C0,PCR)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              CPVF(10,4),IAM(16),WNOR(16),WCRI(16)
C
      COMMON /SXAF2018/ W(16)
      DIMENSION ACVR(16),APVR(16)
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      G02 (X,A,B,C) = (A*X+B)*X+C
C
      CEP=0.0
      AGT=0.0
C
C____ ZETAV = POSIZIONE DELLE VALVOLE VR (IN FULL-ARC)
C
      ZETAV = SXF2318(X,NIPF,CPVF,10)
      DO 100 IV=1,NVALV
      IF(II.NE.IAM(IV)) GOTO 100
C
C____ SOMMA DELLA POSIZIONE DEI PROVAVALVOLE
	ZETAV=ZETAV+APVR(IV)
	IF(ZETAV.GT.1.) ZETAV=1.
	IF(ZETAV.LT.0.) ZETAV=0.
C____ CARICAMENTO PASIZIONE VALVOLA REGOLANTE
	ACVR(IV)=ZETAV
C____ CALCOLO COEFF. DI SCARICO E AREA DI PASSAGGIO TOTALE
	CF = G02 (ZETAV,CCF(IV,1),CCF(IV,2),CCF(IV,3))
	AVA = SXF2218(IV,ZETAV,NIA(IV),CAV,3)
	CEP = CEP +0.807*CA(IV)*AVA*CF
	AGT = AGT + AUG(IV)
  100 CONTINUE
C____ SE LE VA SONO CHIUSE O LE VR SONO CHIUSE LA PORTATA E` NULLA
      IF (ZEVA.LT.0.00001.OR.CEP.LT..00001) THEN
	  WLIN = 0.0
	  GOTO 150
      ENDIF
      CVET=0.
C____ CALCOLO COEFF. DI SCARICO DELLE VA
      CALL CALCCVA(ZEVA,CVA,CVAM,A2,B1,C0,ZETAM)
      IF (CVA.GE.0.00001) THEN
C____ CALCOLO DEL COEFFICIENTE DI SCARICO VA , VR
	  CVET =SQRT( 1/((1/CEP**2)+(1/CVA**2)))
      ENDIF
C____ CALCOLO PORTATA SULLA LINEA DI AMMISIONE COME "SALTO CRITICO"
	 WLIN = CVET * SQRT(PSH * ROSH)* SQRT(1-R)
C
  150 DO 200 IV=1,NVALV
C____ CALCOLO LE PORTATE NELLE VALVOLE REGOLANTI
      IF (II.NE.IAM(IV)) GOTO 200
	  W(IV)=WLIN/AGT*AUG(IV)
  200 CONTINUE
      WF20=WLIN
      RETURN
      END
      SUBROUTINE SXMGT18(PSH1,PSH2,HSH1,HSH2,PCR,RPS,WTOT,PXN,FARC,
     $          WF20,HF20,WAM1,WAM2,LINAM,NVR,ACVR,APVR,PMUG,PMUGC,
     $          R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $          CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $          PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $          RCA,XF,WF,IAM,zva1,zva2)
C
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
C
      COMMON /SXAF2018/ W(16)
      DIMENSION ACVR(16),APVR(16),PMUG(16),PMUGC(16)
C
      HW = 0.
C
C____ LOOP SUL NUMERO DI LINEE DI AMMISSIONE
      DO II=1,2
       IF(LINAM.EQ.1.OR.II.EQ.1)THEN
	 PSH =PSH1
	 HSH =HSH1
       ELSE
	 PSH =PSH2
	 HSH =HSH2
       ENDIF
C
C-----CALCOLO DELLA PORTATA TOTALE WF20
C
C_____PROTEZIONE PER HSH < HRIF
      WF20=0.
      IF(HSH.LE.HRIF) GO TO 500
C
      U=UDVU*RPS
      PSRO=ALFA*(HSH-HRIF)
      ROSH=PSH/PSRO
      PP = PSH -CEME*WTOT**2./ROSH
      IF(PCR.GT.PP) GOTO 500
      TET=2.*PSRO/PCR/PCR*ALFA
      SPSRO=SQRT(PSRO)
      R2 = (PP-PCR)/PP
      Y=PP/SPSRO
c
      IF(II.EQ.1) THEN
       zvva=-zva1*zva1+2.*zva1
      ELSE
       zvva=-zva2*zva2+2.*zva2
      ENDIF
c
      CALL SXF2018(PXN,FARC,Y,R2,WF20,II,APVR,ACVR,
     $          R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $          CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $          PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $          RCA,XF,WF,IAM,zvva)
C
      IF(II.EQ.1) THEN
       WAM1=WF20
      ELSE
       WAM2=WF20
      ENDIF
C
C-----CALCOLO ENTALPIA IN CAMERA RUOTA
C
C
      DO 285 IV=1,NVALV
C____ TEST PER VEDERE SE LA VALVOLA REGOLANTE APPARTIENE AL SETTORE
C      DELLA VALVOLA DI AMMISSIONE II
       IF(II. NE. IAM(IV)) GO TO 285
C
      IF(W(IV).LE.0.) THEN
       PMUGC(IV)=PCR
       GOTO 285
      ENDIF
C
      PUSS = W(IV)/AUG(IV)/AALAM*SPSRO
      IF(PUSS.LT.(PCR/R)) GO TO 201
C
C-----UGELLI CRITICI
C
      PUG= PUSS
C____ MEMORIZZAZIONE PRESSIONE A MONTE UGELLI
      PMUGC(IV)=PUSS
C*******(SPELTA 21-5-90)
      PCRPUA=(ABS(PCR/PUG))**ALFA
C*******
      GOTO 215
C
C-----UGELLI SOTTOCRITICI
  201 CONTINUE
      PCRPUA=2./(1.+SQRT(1.+TET*(W(IV)/AUG(IV))**2))
C____ MEMORIZZAZIONE PRESSIONE A MONTE UGELLI
      PMUGC(IV)=PCR/(PCRPUA**(1./ALFA))
215      CONTINUE
C
      HISO=HRIF+(HSH-HRIF)*PCRPUA
      DHSH=HSH-HISO
      IF(DHSH.LE.0.) THEN
	 C=0.
	 RUC=0.
      ELSE
	 C=SQRT(2.*DHSH)
	 IF(C.LT.1.E-3) THEN
	  RUC=0.
	 ELSE
	  RUC=U/C
	 ENDIF
      ENDIF
      ETA=(AETA*RUC+BETA)*RUC
      IF(ETA.LT..1)ETA=.1
      HUG=HSH-ETA*(HSH-HISO)
      HW= HW+HUG*W(IV)
C
C
  285 CONTINUE
C____ FINE LOOP SULLE VALVOLE DI AMMISSIONE
      ENDDO
C
C____ PORTATA TOTALE
      WF20=WAM1+WAM2
C
C
      HF20=HSH1
C !!!! protezione per portata nulla
      IF(WF20.GE..01)HF20 = HW/WF20
	RETURN
C
  500 CONTINUE
      WF20=0.
      HF20=HSH
      RETURN
      END
C
      SUBROUTINE SXF2018 (PSERV,FARC,Y,R2,WSOM,II,APVR,ACVR,
     $          R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $          CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $          PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $          RCA,XF,WF,IAM,zvva)
C
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
C
      COMMON /SXAF2018/ W(16)
      DIMENSION APVR(16),ACVR(16)
      G02 (X,A,B,C) = (A*X+B)*X+C
C
      WSOM = 0.
      IF(FARC) 1,1,2
2      ZETAF=SXF2318(PSERV,NIPF,CPVF,10)
1      CONTINUE
      DO 300 IV=1,NVALV
C
      IVV = IV
C____ TEST PER VEDERE SE LA VALVOLA REGOLANTE APPARTIENE AL SETTORE
C      DELLA LINEA DI AMMISSIONE II
C___ II=0 QUANDO SI CALCOLANO LE CAPACITA` DI SCARICO A VALVOLA APERTA
       IF(II.EQ.0) GO TO 5
       IF(II. NE. IAM(IV)) GO TO 300
C
    5 IF(FARC)      20,20,10
   10 IF(FARC-1.)   30,40,40
   20 CONTINUE
C-----FUNZIONAMENTO AD ARCO PARZIALE: FARC<=0.
      ZETA  = SXF2218(IVV,PSERV,NIP(IV),CPV,10)
      GOTO 50
   30 CONTINUE
C-----FUNZIONAMENTO IN TRANSIZIONE
      ZETAP=SXF2218(IVV,PSERV,NIP(IV),CPV,10)
      ZETA =(1.-FARC)*ZETAP+FARC*ZETAF
      GO TO 50
   40 CONTINUE
C-----FUNZIONAMENTO AD ARCO TOTALE: FARC >=1.
C
      ZETA=ZETAF
   50 CONTINUE
C
C____ SOMMA ALLA POZIONE ZETA LA POSIZIONE DEL PROVA VALVOLE
      IF(II.NE.0) THEN
       ZETA=ZETA+APVR(IV)
       IF(ZETA.GT.1.)ZETA=1.
       IF(ZETA.LT.0.)ZETA=0.
C____ CARICAMENTO POSIZIONE VALVOLA REGOL. IV
      ACVR(IV)=ZETA
      ENDIF
C
c
c_____ correzione della posizione delle valvole in funzione delle posizioni
c      delle valvole di ammissione
c
      zeta = zeta*zvva
      IF(ZETA.GT.0.) GO TO 120
      W(IV) = 0.
      GO TO 200
  120 IF(ZETA.LE.1.  ) GO TO 140
      ZETA = 1.
  140 CF = G02 (ZETA,CCF(IV,1),CCF(IV,2),CCF(IV,3))
      AVA  = SXF2218 (IVV,ZETA ,NIA(IV),CAV, 3)
      R3 = CA(IV)*AVA/AUG(IV)
      CALL SXABC018(R3,CF,ARC,BRC)
      CAB=CA(IV)*AVA*BRC*Y
      IF(R2.GE.ARC)    GOTO 160
C
C-----UGELLI E VALVOLE SOTTOCRITICI
C
C___ PROTEZIONE PER RADICE NEGATIVA
      QQQ=(1.-R2/ARC)**2
      IF(QQQ.GT.1.) THEN
	 W(IV) =0.
      ELSE
	 D02= SQRT(1.-QQQ)
	 W(IV) = CAB*D02
      ENDIF
      GOTO 200
  160 CONTINUE
C
C-----UGELLI O VALVOLE CRITICI
      W(IV) = CAB
C
  200 WSOM = WSOM+W(IV)
  300 CONTINUE
      RETURN
      END
C
      SUBROUTINE STAZCVA(CEME,CVAM,ZETAM,A2,B1,C0)
C DETERMINA I COEFFICIENTI DELLA PARABOLA PASSANTE PER I PUNTI
C (ZETAM,CVAM) E (1,CVAP) E TANGENTE NEL PUNTO (ZETAM,CVAM)
C ALLA RETTA PASSANTE PER L'ORIGINE
      CVAP=1./SQRT(CEME)
      DEN = (1 - ZETAM)** 2
      A2 = (CVAP -(CVAM/ZETAM))/DEN
      B1 = (CVAM*(1+ ZETAM**2)-2*CVAP*(ZETAM**2))/(ZETAM * DEN)
      C0 = (CVAP*(ZETAM**2)-CVAM*ZETAM)/DEN
      RETURN
      END
C
C CALCOLA IL COEFFICIENTE DI SCARICO DELLA VALVOLA DI AMMISSIONE
C
      SUBROUTINE CALCCVA(ZEVA,CVA,CVAM,A2,B1,C0,ZETAM)
      IF(ZEVA.LE.ZETAM) THEN
      CVA = CVAM/ZETAM * ZEVA
      ELSE
      CVA = (A2* ZEVA + B1)*ZEVA +C0
      ENDIF
      RETURN
      END

      FUNCTION SXF2218 (IV,P2,N3,P4,N5)
C      CALCOLA FUNZIONE DI GRADO 2 CON LIMITI                  8 AGO 79
C
C IN INGRESSO
C IV  = N. VALVOLA
C P2  = VARIABILE DI CONFRONTO CON LIMITI
C N3  = N. DI INTERVALLI
C P4  = MATRICE
C N5  = DIMENSIONE MATRICE
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION P4(16,N5,4)
      G02 (X,A,B,C) = (A*X+B)*X+C
C
      DO 120 L=1,N3
      LL=L
      IF(P2.GT.P4(IV,LL,1)) GO TO 120
      GO TO 140
  120 CONTINUE
C     PRINT,'      ERRORE NELLA F22   FUORI LIMIT'
  140 SXF2218 = G02 (P2, P4(IV,LL,2), P4(IV,LL,3), P4(IV,LL,4))
      RETURN
      END
C
      SUBROUTINE  SXSTAZ (IPRNT,ITYP,TIPO,
     $            R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $            CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $            PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $            RCA,XF,WF,IAM,zvva)
C
C      LETTURA DATI ED INIZIALIZZAZIONE                        6 AGO 79
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
C
       CHARACTER*36 TIPO
      G02 (X,A,B,C) = (A*X+B)*X+C
   20 FORMAT(1H1/  1X,'TIPO         : ',A,
     $ //1X,'PSHNOM (PASCAL) :',E12.5, 8X,'TSHNOM (.K) :',F6.1,'+273.15'
     $ , 8X,'VUNOM (GIRI/SEC) :',F5.1, 8X,'WNOM (KG/SEC) :',F7.2
     $ // 1X,'RAGGIO (M)   : ',F 7.4
     $ // 1X,'CCR (KG/(SEC*PA)) : ',  E12.5
     $ // 1X,'AETA, BETA   : ',2F10.4
     $ // 1X,'DPVE (PASCAL) : ',E12.5, 8X,'CEME (N*SEC/M5) : ',F 8.3
     $ // 1X,'PER CALCOLO CA1 :   PSHF (PASCAL) :',E12.5, 8X,'TSHF (.K)
     $:',F6.1,'+273.15', 8X,'XF :',F6.3, 8X,'WF (KG/SEC) :',F7.2
     $ // 1X,'N. VALVES : ',I2)
   22 FORMAT(/11X,'VALVE N.',I2 ,35X,'CA/CA1'
     $        , 5X,'CA',15X,'COEFF. PER CF',12X,'NOZZLES AREA (M2)'
     $       / 57X,F7.4,1X,F 9.6,2X,3F10.4,7X,F10.7)
   24 FORMAT(/11X,'VALVE N.',I2)
   26 FORMAT(  1X,'SUP. LIMIT AND VALVE AREA COEFF. ('
     $ ,I2,' INTERVALLI)')
   28 FORMAT(  1X,F7.3,2X,3F15.7)
   30 FORMAT(/ 1X,'SUP. LIMIT AND VALVE POSITION COEFF. IN PA ('
     $ ,I2,' INTERVALLI)')
   31 FORMAT(/1X,'SUP. LIMIT AND VALVE POSITION COEFF. IN
     $ FA (',I2,'INTERVALLI)')
C
      CK=1.3
      IF(ITYP.EQ.0) THEN

       CALL DXSTAZ (TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
      GO TO 18
      ELSE
C
      GO TO (15,16,17,175),ITYP
C
   15 CALL DXANS320(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C
      GO TO 18
   16 CALL DXTOS320(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C
      GO TO 18
   17 CALL DXTOS660(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C
      GO TO 18
  175 CALL DXANS660(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
      ENDIF
   18 CONTINUE
C
C
C
C                      STAMPE DI ERRORE
C
      IF(NVALV.LT.1.OR.NVALV.GT.16) 
     $  WRITE(6,*)'NVALV MUST BE LIMITED BETWEEN 1 AND 16'
      DO 88 IV=1,NVALV
88    IF(NIA(IV).LT.1.OR.NIA(IV).GT. 3)  
     $   WRITE (6,*)'NIA MUST BE LIMITED BETWEEN 1 AND 3'
      IF(RCA(1).NE.1.)  WRITE (6,*)'RCA(1) MUST BE = 1'
      DO 99 IV=1,NVALV
99    IF(NIP(IV).LT.1.OR.NIP(IV).GT.10)  
     $    WRITE (6,*)'NIP MUST BE LIMITED BETWEEN 1 AND 10'
      IF(NIPF.LT.1.OR.NIPF.GT.10)
     $   WRITE (6,*)'NIPF MUST BE LIMITED BETWEEN 1 AND 10'
C
      ALFA=(CK-1.)/CK
      R = (2./(CK+1.))**(CK/(CK-1.))
      AALAM = SQRT(CK*(2./(CK+1.))**((CK+1.)/(CK-1.)))
      UDVU = RAGGIO*3.14159*2.
      SSHNOM=STEV(PSHNOM,TSHNOM,1.,1)
      ROSHNOM = ROEV(PSHNOM,SSHNOM,1)
      HSHNOM=HEV(PSHNOM,SSHNOM,1)
      HRIF=HSHNOM-PSHNOM/ROSHNOM/ALFA
      CEME = DPVE*ROSHNOM/WNOM**2
C
C-----CALCOLO DEI CA(I)
C
      SSHF = STEV(PSHF,TSHF,1.,1)
      HSHF = HEV(PSHF,SSHF,1)
      PCR = WF/CCR
      ROSHF = ROEV(PSHF,SSHF,1)
      PP = PSHF -CEME*WF**2./ROSHF
      SP = SHEV(PP,HSHF,1)
      ROP = ROEV(PP,SP,1)
      SPPROP = SQRT(PP*ROP)
      R2 = (PP-PCR)/PP
      CA1 = 10.
      DO 1200 IV=1,NVALV
      IVV = IV
      ZETA = SXF2218 (IVV,XF,NIP(IV),CPV,10)
      IF(ZETA.LE.0.) ZETA = 0.
      IF(ZETA.GE.1.) ZETA = 1.
      CF = G02 (ZETA,CCF(IV,1),CCF(IV,2),CCF(IV,3))
      AVA  = SXF2218 (IVV,ZETA ,NIA(IV),CAV, 3)
      S1 = 250.*AUG(IV)/AVA
      S2 = 10.
      IF(CF.GT.1.12) S2 = .9*(.3-CF)/(1.12-CF)*AUG(IV)/AVA
      CA(IV) = AMIN1(S1,S2)/RCA(IV)
      IF(CA(IV).LT.CA1) CA1 = CA(IV)
 1200 CONTINUE
      DO 230 IV=1,NVALV
  230 CA(IV) = CA1*RCA(IV)
      II=0
      CALL SXF2018(XF,-1.,SPPROP,R2,WF20,II,PSEUDO,PSEUDO,
     $          R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $          CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $          PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $          RCA,XF,WF,IAM,zvva)
C
      FXN = WF  -WF20
      IF(FXN.LT.0.) GO TO 235
      WRITE(6,54)
   54 FORMAT(/// 1X,'ERROR IN THE INIZIALIZATION')
      STOP
  235 IF(ABS(FXN).LE. 1.E-02 ) GO TO 300
C
C      CONVERGENZA CON METODO DICOTOMICO
      ITER = 0
      SA = 0.
      SB = CA1
  240 CA1 = (SA+SB)*.5
      DO 250 IV=1,NVALV
  250 CA(IV) = CA1*RCA(IV)
      II=0
      CALL SXF2018(XF,-1.,SPPROP,R2,WF20,II,PSEUDO,PSEUDO,
     $          R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $          CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $          PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $          RCA,XF,WF,IAM,zvva)
C
      FXN = WF  -WF20
      IF(ABS(FXN).LT. 1.E-02 ) GO TO 300
      IF(ITER.GT.30) GO TO 290
      ITER = ITER+1
      IF(FXN.GT.0.) GO TO 260
      SB = CA1
      GO TO 240
  260 SA = CA1
  280 GO TO 240
  290 CONTINUE
C     PRINT,'      ERROR IN S10: IT DOES NOT CONVERGE'
      STOP
  300 CONTINUE
      IF(IPRNT.LT.1)    GOTO 301
      TSH = TSHNOM -273.15
      TF  = TSHF   -273.15
      WRITE(6,20) TIPO,PSHNOM,TSH,VUNOM,WNOM,RAGGIO,CCR,AETA,BETA,
     $ DPVE,CEME,PSHF,TF,XF,WF,NVALV
  301 CONTINUE
      DO 340 IV=1,NVALV
      CA(IV) = CA1*RCA(IV)
      IF(IPRNT.LT.2) GOTO 340
      WRITE(6,22) IV, RCA(IV), CA(IV), (CCF(IV,L),L=1,3), AUG(IV)
      WRITE(6,26) NIA(IV)
      DO 320 I02=1,NIA(IV)
  320 WRITE(6,28) (CAV(IV,I02,L),L=1,4)
  340 CONTINUE
      IF(IPRNT.LT.2)  RETURN
      WRITE(6,42) CK,R,AALAM
   42 FORMAT(/// 1X,'CK =',F 8.4,10X,'R =',F10.6,10X,'AALAM ='
     $,F10.6,//,1X)
      DO 420 IV=1,NVALV
      WRITE(6,24) IV
      WRITE(6,30) NIP(IV)
      DO 400 I02=1,NIP(IV)
  400 WRITE(6,28) (CPV(IV,I02,L),L=1,4)
  420 CONTINUE
      WRITE(6,31) NIPF
      DO 401 I02=1,NIPF
401      WRITE(6,28) (CPVF(I02,L),L=1,4)
      RETURN
      END
C
      SUBROUTINE SXABC018 (R3,R4,A,B)
C FORNISCE A E B  IN FUNZIONE DI R3,R4
C
C CALCOLO  A
C
      A = 1.+1.75*(R4-0.8)*EXP(-0.3*R3)
      T=(R4-.3)/(1.12-R4)
	T=(T+4.27-4.8*R4*R4)/(R3+T)
	T=COS(6.2832/(T*T*T+1.))
	A=A*(.554-.1*T)
C
C CALCOLO  B
C
      B=(.13-R4)/2.2
      C=-1./B
      T=R4/1.23
      B=.667*T*(1.+(R3*T)**C)**B
      RETURN
      END
C
      FUNCTION SXF2318 (P2,N3,P4,N5)
C      CALCOLA FUNZIONE DI GRADO 2 CON LIMITI   PER F. A.  31 MAR 83
C
C IN INGRESSO
C P2  = VARIABILE DI CONFRONTO CON LIMITI
C N3  = N. DI INTERVALLI
C P4  = MATRICE
C N5  = DIMENSIONE MATRICE
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION P4(N5,4)
      G02 (X,A,B,C) = (A*X+B)*X+C
C
      DO 120 L=1,N3
      LL=L
      IF(P2.GT.P4(LL,1)) GO TO 120
      GO TO 140
  120 CONTINUE
C     PRINT,'      ERROR IN THE F23: OUT OF LIMITS'
  140 SXF2318 = G02 (P2, P4(LL,2), P4(LL,3), P4(LL,4))
      RETURN
      END
C
C****** SUBROUTINE DI ACQUISIZIONE DATI PER LA TURBINA TOSI DA 320 MW *****
C
       SUBROUTINE DXTOS320(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
       DIMENSION
     $             DXCA(16),DXCCF(16,3),DXAUG(16),IDXNIA(16),
     $             DXCAV(16,3,4),IDXNIP(16),DXCPV(16,10,4),
     $             DXCPVF(10,4),DXRCA(16),IDXIAM(16)
      CHARACTER*36 TIPO
      CHARACTER*37 DXTIPO
C
      DATA DXTIPO/'      TURBINA TOSI DA 320 MW         '/
C
      DATA DXPSHNOM,DXTSHNOM,DXVUNOM,DXWNOM,DXRAGGIO,DXCCR,DXAETA,
     $     DXBETA,DXDPVE,DXPSHF,DXTSHF,DXXF,DXWF,IDXNVALV,IDXNIPF
C
     $/ 16671000.,   811.15  ,  50.      , 284.25    , .456      ,
C        PSHNOM      TSHNOM     VUNOM       WNOM       RAGGIO
C
     $  .0000265 ,    -7.617 ,   4.875   ,  166700.  , 16671000. ,
C          CCR         AETA      BETA        DPVE        PSHF
C
     $    811.15 ,      1.   ,  293.44   ,    8      ,    1      /
C          TSHF         XF        WF        NVALV        NIPF
C
      DATA (IDXIAM(I),I=1,8)/1,2,1,2,1,2,1,2/
C
C                  CARICAMENTO VETTORE RCA
C
      DATA (DXRCA(I),I=1,  8   )
C                       NVALV
C
     $/   1.  ,   1.  ,   1.  ,   1.  ,  1.  ,   1.  ,  1.  ,   1.  /
C        (1)     (2)     (3)     (4)    (5)     (6)    (7)     (8)
C
C
C                  CARICAMENTO VETTORE CCF
C
      DATA ((DXCCF(I,J),J=1,  3   ),I=1, 8 )
C                                    NVALV
C
     $/   .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (1,1)    (1,2)    (1,3)      (2,1)     (2,2)    (2,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (3,1)    (3,2)    (3,3)      (4,1)     (4,2)    (4,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (5,1)    (5,2)    (5,3)      (6,1)     (6,2)    (6,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    /
C        (7,1)    (7,2)    (7,3)      (8,1)     (8,2)    (8,3)
C
C                  CARICAMENTO VETTORE AUG
C
      DATA (DXAUG(I),I=1,  8   )
C                       NVALV
C
     $/.0022340,.0022340,.0022340,.0022340,
C        (1)       (2)      (3)      (4)
     $ .0022340,.0022340,.0022340,.0022340/
C        (5)       (6)      (7)      (8)
C
C
C                  CARICAMENTO VETTORE NIA
C
      DATA (IDXNIA(I),I=1,  8   )
C                       NVALV
C
     $/    2   ,    2    ,    2    ,   2    ,
C         (1)      (2)       (3)      (4)
     $     2   ,    2    ,    2    ,   2     /
C         (5)      (6)       (7)      (8)
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 1
C
      DATA ((DXCAV(1,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(1)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 2
C
      DATA ((DXCAV(2,I02,L),L=1,4),I02=1,  2   )
C                                       NIA(2)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 3
C
      DATA ((DXCAV(3,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(3)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 4
C
      DATA ((DXCAV(4,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(4)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 5
C
      DATA ((DXCAV(5,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(5)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 6
C
      DATA ((DXCAV(6,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(6)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 7
C
      DATA ((DXCAV(7,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(7)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 8
C
      DATA ((DXCAV(8,I02,L),L=1,4),I02=1,  2   )
C                                        NIA(8)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C                  CARICAMENTO VETTORE NIP
C
      DATA (IDXNIP(I),I=1,  8  )
C                       NVALV
C
     $/   4   ,    4    ,   4   ,   4    ,
C        (1)      (2)      (3)     (4)
     $    4   ,    4    ,   5   ,   5    /
C        (5)      (6)      (7)     (8)
C
C               CARICAMENTO VETTORE CPV VALVOLA 1
C
      DATA ((DXCPV(1,I02,L),L=1,4),I02=1,  4   )
C                                       NIP(1)
C
     $/ .02     ,     0.   ,       5.01  ,      0.    ,
C        x            a            b            c
     $  .291    ,     0.   ,       1.3815,      .07242,
C        x            a            b            c
     $  .341    ,     0.   ,      10.521 ,     -2.5908,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C                  CARICAMENTO VETTORE CPV VALVOLA 2
C
      DATA ((DXCPV(2,I02,L),L=1,4),I02=1,  4   )
C                                       NIP(2)
C
     $/ .02     ,     0.   ,       5.01  ,      0.    ,
C        x            a            b            c
     $  .291    ,     0.   ,       1.3815,      .07242,
C        x            a            b            c
     $  .341    ,     0.   ,      10.521 ,     -2.5908,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 3
C
      DATA ((DXCPV(3,I02,L),L=1,4),I02=1,  4   )
C                                       NIP(3)
C
     $/ .24     ,     0.   ,       0.    ,      0.    ,
C        x            a            b            c
     $  .423    ,     0.   ,       2.5054,      -.6   ,
C        x            a            b            c
     $  .463    ,     0.   ,      13.51  ,     -5.2561,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 4
C
      DATA ((DXCPV(4,I02,L),L=1,4),I02=1,  4   )
C                                       NIP(4)
C
     $/ .379    ,     0.   ,       0.    ,      0.    ,
C        x            a            b            c
     $  .547    ,     0.   ,       2.5641,    -0.97023,
C        x            a            b            c
     $  .599    ,     0.   ,      10.9826,     -5.5764,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 5
C
      DATA ((DXCPV(5,I02,L),L=1,4),I02=1,  4   )
C                                       NIP(5)
C
     $/ .479    ,     0.   ,       0.    ,      0.    ,
C        x            a            b            c
     $  .671    ,     0.   ,       2.4269,     -1.1624,
C        x            a            b            c
     $  .739    ,     0.   ,      7.8792 ,     -4.8188,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 6
C
      DATA ((DXCPV(6,I02,L),L=1,4),I02=1,  4   )
C                                       NIP(6)
C
     $/ .604    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .782    ,      0.  ,     2.577   ,    -1.5562,
C        x            a            b            c
     $  .854    ,      0.  ,      7.5104 ,    -5.4161,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.     /
C        x            a            b            c
C
C                  CARICAMENTO VETTORE CPV VALVOLA 7
C
      DATA ((DXCPV(7,I02,L),L=1,4),I02=1,  5   )
C                                       NIP(7)
C
     $/ .679    ,     0.   ,       0.    ,      0.    ,
C        x            a            b            c
     $  .874    ,     0.   ,       1.4315,     -.9714 ,
C        x            a            b            c
     $  .954    ,     0.   ,      2.0651 ,     -1.5253,
C        x            a            b            c
     $  1.      ,     0.   ,      12.0915,    -11.0915,
C        x            a            b            c
     $  1.05    ,     0.   ,      15.    ,      1.    /
C        x            a            b            c
C
C                  CARICAMENTO VETTORE CPV VALVOLA 8
C
      DATA ((DXCPV(8,I02,L),L=1,4),I02=1,  5   )
C                                       NIP(8)
C
     $/ .679    ,     0.   ,       0.    ,      0.    ,
C        x            a            b            c
     $  .874    ,     0.   ,       1.4315,     -.9714 ,
C        x            a            b            c
     $  .954    ,     0.   ,      2.0651 ,     -1.5253,
C        x            a            b            c
     $  1.      ,     0.   ,      12.0915,    -11.0915,
C        x            a            b            c
     $  1.05    ,     0.   ,      15.    ,      1.    /
C        x            a            b            c
C
C                  CARICAMENTO VETTORE CPVF
C
      DATA ((DXCPVF(I02,L),L=1,4),I02=1, 1  )
C                                      NIPF
C
     $/   1.05  ,     0.   ,       1.    ,       0.  /
C          x          a            b             c
C
      TIPO=DXTIPO
C
      PSHNOM=DXPSHNOM
      TSHNOM=DXTSHNOM
      VUNOM =DXVUNOM
      WNOM  =DXWNOM
      RAGGIO=DXRAGGIO
      CCR   =DXCCR
      AETA  =DXAETA
      BETA  =DXBETA
      DPVE  =DXDPVE
      PSHF  =DXPSHF
      TSHF  =DXTSHF
      XF    =DXXF
      WF    =DXWF
      NVALV =IDXNVALV
      NIPF  =IDXNIPF
C
      DO I=1,16
      CA(I)  =DXCA(I)
      AUG(I) =DXAUG(I)
      NIA(I) =IDXNIA(I)
      NIP(I) =IDXNIP(I)
      RCA(I) =DXRCA(I)
      IAM(I) =IDXIAM(I)
       DO J=1,3
       CCF(I,J)=DXCCF(I,J)
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,3
	DO K=1,4
	CAV(I,J,K)=DXCAV(I,J,K)
	ENDDO
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,10
	DO K=1,4
	CPV(I,J,K)=DXCPV(I,J,K)
	ENDDO
       ENDDO
      ENDDO
       DO J=1,10
	DO K=1,4
	CPVF(J,K)=DXCPVF(J,K)
	ENDDO
       ENDDO
C
      RETURN
      END
C
C****** SUBROUTINE DI ACQUISIZIONE DATI PER LA TURBINA ANSALDO DA 320 MW *****
C
       SUBROUTINE DXANS320(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
       DIMENSION
     $             DXCA(16),DXCCF(16,3),DXAUG(16),IDXNIA(16),
     $             DXCAV(16,3,4),IDXNIP(16),DXCPV(16,10,4),
     $             DXCPVF(10,4),DXRCA(16),IDXIAM(16)
      CHARACTER*36 TIPO
      CHARACTER*37 DXTIPO
C
      DATA DXTIPO/'      TURBINA ANSALDO DA 320 MW      '/
C
C
      DATA DXPSHNOM,DXTSHNOM,DXVUNOM,DXWNOM,DXRAGGIO,DXCCR,DXAETA,
     $     DXBETA,DXDPVE,DXPSHF,DXTSHF,DXXF,DXWF,IDXNVALV,IDXNIPF
C
     $/ 16670000.,   811.15  ,  50.      , 299.145   , .4826     ,
C        PSHNOM      TSHNOM     VUNOM       WNOM       RAGGIO
C
     $  .00002132,    -3.57  ,   3.228   ,  294000.  , 16670000. ,
C          CCR         AETA      BETA        DPVE        PSHF
C
     $    811.15 ,      1.   ,  299.145  ,    4      ,    1      /
C          TSHF         XF        WF        NVALV        NIPF
C
      DATA (IDXIAM(I),I=1,4)/1,2,1,2/
C
C                  CARICAMENTO VETTORE RCA
C
		     DATA (DXRCA(I),I=1,  4   )
C                                     NVALV
C
     $/   1.    ,  .84037   , .84037  ,    1.     /
C        (1)         (2)        (3)       (4)
C
C
C                  CARICAMENTO VETTORE CCF
C
		DATA ((DXCCF(I,J),J=1,  3   ),I=1, 4 )
C                                               NVALV
C
     $/   .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (1,1)    (1,2)    (1,3)      (2,1)     (2,2)    (2,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    /
C        (3,1)    (3,2)    (3,3)      (4,1)     (4,2)    (4,3)
C
C                  CARICAMENTO VETTORE AUG
C
		     DATA (DXAUG(I),I=1,  4   )
C                                     NVALV
C
     $/.0063904,.0053541 , .0053541, .006394/
C        (1)       (2)       (3)       (4)
C
C                  CARICAMENTO VETTORE NIA
C
		     DATA (IDXNIA(I),I=1,  4   )
C                                     NVALV
C
     $/    2   ,    2    ,    2    ,   2    /
C         (1)      (2)       (3)      (4)
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 1
C
	DATA ((DXCAV(1,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(1)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 2
C
	DATA ((DXCAV(2,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(2)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 3
C
	DATA ((DXCAV(3,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(3)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 4
C
	DATA ((DXCAV(4,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(4)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C
C                  CARICAMENTO VETTORE NIP
C
		     DATA (IDXNIP(I),I=1,  4  )
C                                     NVALV
C
     $/   9   ,     7    ,    5    ,    3    /
C        (1)       (2)       (3)       (4)
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 1
C
       DATA ((DXCPV(1,I02,L),L=1,4),I02=1,  9   )
C                                NIP(1)
C
C
     $/  .15   ,  1.2444444,     0.      ,    0.     ,
C          x         a            b            c
     $  .275   ,  -.574359 ,  .7401026   , -.07009231,
C         x          a            b            c
     $  .35    ,  2.142857 , -.7392857   ,   .13125  ,
C        x           a            b            c
     $  .45     ,     0.   ,     .83     ,  -.1555   ,
C        x            a            b            c
     $  .575    , 2.246154 , -1.206308   , .3059923  ,
C        x            a            b            c
     $  .725    , -1.777778,  3.711111   ,  -1.191111,
C        x            a            b            c
     $  .8      , 19.285714, -26.210714  ,  9.430714 ,
C        x            a            b            c
     $  .865    ,    -30.  ,    52.95    ,  -22.355  ,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.   /
C         x           a            b            c
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 2
C
       DATA ((DXCPV(2,I02,L),L=1,4),I02=1,  7   )
C                                NIP(2)
C
C
     $/ .2      ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .4      ,    1.55  ,    -.155    ,    -.031  ,
C        x            a            b            c
     $  .525    , -2.461538,    3.116923 ,  -.697923 ,
C        x            a            b            c
     $  .75     ,  5.155555,    -5.017778,  1.473333 ,
C        x            a            b            c
     $  .825    ,     0.   ,    2.866667 ,    -1.54  ,
C        x            a            b            c
     $  .93     ,-9.6969697,   18.684848 ,    -7.99  ,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.   /
C        x            a            b            c
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 3
C
       DATA ((DXCPV(3,I02,L),L=1,4),I02=1,  5   )
C                                NIP(3)
C
C
     $/ .715    ,     0.   ,      0.     ,      0.   ,
C        x            a           b             c
     $  .8      , 9.344538 ,-12.604034   ,  4.234723 ,
C        x            a            b            c
     $  .875    , 35.73333 ,  -54.94666  ,    21.22  ,
C        x            a            b            c
     $  .96     ,-41.37255 ,   81.03627  , -38.73088 ,
C        x            a            b            c
     $  1.05    ,     0.   ,   .7222222  ,  .2416667 /
C        x            a            b            c
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 4
C
       DATA ((DXCPV(4,I02,L),L=1,4),I02=1,  3   )
C                                NIP(4)
C
C
C
     $/ .865    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .95     , 24.20168 ,  -41.57311  ,     17.8  ,
C         x            a            b            c
     $  1.05    ,   57.6   ,   -105.48   ,     48.4  /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPVF
C
		DATA ((DXCPVF(I02,L),L=1,4),I02=1, 1  )
C                                        NIPF
C
     $/   1.05  ,     0.   ,       1.    ,       0.  /
C          x          a            b             c
C
C
      TIPO=DXTIPO
C
      PSHNOM=DXPSHNOM
      TSHNOM=DXTSHNOM
      VUNOM =DXVUNOM
      WNOM  =DXWNOM
      RAGGIO=DXRAGGIO
      CCR   =DXCCR
      AETA  =DXAETA
      BETA  =DXBETA
      DPVE  =DXDPVE
      PSHF  =DXPSHF
      TSHF  =DXTSHF
      XF    =DXXF
      WF    =DXWF
      NVALV =IDXNVALV
      NIPF  =IDXNIPF
C
      DO I=1,16
      CA(I)  =DXCA(I)
      AUG(I) =DXAUG(I)
      NIA(I) =IDXNIA(I)
      NIP(I) =IDXNIP(I)
      RCA(I) =DXRCA(I)
      IAM(I) =IDXIAM(I)
       DO J=1,3
       CCF(I,J)=DXCCF(I,J)
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,3
	DO K=1,4
	CAV(I,J,K)=DXCAV(I,J,K)
	ENDDO
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,10
	DO K=1,4
	CPV(I,J,K)=DXCPV(I,J,K)
	ENDDO
       ENDDO
      ENDDO
       DO J=1,10
	DO K=1,4
	CPVF(J,K)=DXCPVF(J,K)
	ENDDO
       ENDDO
C
       RETURN
       END
C
C****** SUBROUTINE DI ACQUISIZIONE DATI PER LA TURBINA TOSI DA 660 MW *****
C
       SUBROUTINE DXTOS660(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
       DIMENSION
     $             DXCA(16),DXCCF(16,3),DXAUG(16),IDXNIA(16),
     $             DXCAV(16,3,4),IDXNIP(16),DXCPV(16,10,4),
     $             DXCPVF(10,4),DXRCA(16),IDXIAM(16)
      CHARACTER*36 TIPO
      CHARACTER*37 DXTIPO
C
      DATA DXTIPO/'      TURBINA TOSI DA 660 MW         '/
C
C
      DATA DXPSHNOM,DXTSHNOM,DXVUNOM,DXWNOM,DXRAGGIO,DXCCR,DXAETA,
     $     DXBETA,DXDPVE,DXPSHF,DXTSHF,DXXF,DXWF,IDXNVALV,IDXNIPF
C
     $/ 24222000.,   811.15  ,  50.      , 581.03    , .48      ,
C        PSHNOM      TSHNOM     VUNOM       WNOM       RAGGIO
C
     $  .00003173,    -3.1   ,   3.1     ,  231900.  , 24222000.,
C          CCR         AETA      BETA        DPVE        PSHF
C
     $    811.15 ,      1.   ,  597.43   ,    8      ,    1      /
C          TSHF         XF        WF        NVALV        NIPF
C
      DATA (IDXIAM(I),I=1,8)/1,2,1,2,1,2,1,2/
C
C                  CARICAMENTO VETTORE RCA
C
		     DATA (DXRCA(I),I=1,  8   )
C                                     NVALV
C
     $/   1.  ,   1.  ,   1.  ,   1.  ,  1.  ,   1.  ,  1.  ,   1.  /
C        (1)     (2)     (3)     (4)    (5)     (6)    (7)     (8)
C
C
C                  CARICAMENTO VETTORE CCF
C
		DATA ((DXCCF(I,J),J=1,  3   ),I=1, 8 )
C                                               NVALV
C
     $/   .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (1,1)    (1,2)    (1,3)      (2,1)     (2,2)    (2,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (3,1)    (3,2)    (3,3)      (4,1)     (4,2)    (4,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (5,1)    (5,2)    (5,3)      (6,1)     (6,2)    (6,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    /
C        (7,1)    (7,2)    (7,3)      (8,1)     (8,2)    (8,3)
C
C                  CARICAMENTO VETTORE AUG
C
		     DATA (DXAUG(I),I=1,  8   )
C                                     NVALV
C
     $/.0035670,.0035670,.0035670,.0035670,
C        (1)       (2)      (3)      (4)
     $ .0035670,.0035670,.0035670,.0035670/
C        (5)      (6)      (7)      (8)
C
C
C                  CARICAMENTO VETTORE NIA
C
		     DATA (IDXNIA(I),I=1,  8   )
C                                     NVALV
C
     $/    2   ,    2    ,    2    ,   2    ,
C         (1)      (2)       (3)      (4)
     $     2   ,    2    ,    2    ,   2     /
C         (5)      (6)       (7)      (8)
C
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 1
C
	DATA ((DXCAV(1,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(1)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 2
C
	DATA ((DXCAV(2,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(2)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C                  CARICAMENTO VETTORE CAV VALVOLA 3
C
	DATA ((DXCAV(3,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(3)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         z         a            b            c
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 4
C
	DATA ((DXCAV(4,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(4)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 5
C
	DATA ((DXCAV(5,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(5)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 6
C
	DATA ((DXCAV(6,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(6)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 7
C
	DATA ((DXCAV(7,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(7)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 8
C
	DATA ((DXCAV(8,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(8)
C
     $/  .55   ,    0.     ,   1.24      ,    0.   ,
C         z         a            b            c
     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
C         x         a            b            c
C
C
C                  CARICAMENTO VETTORE NIP
C
		   DATA (IDXNIP(I),I=1,   8   )
C                                     NVALV
     $/   4    ,   3    ,   4   ,   4    ,
C        (1)      (2)      (3)     (4)
     $    3   ,    4   ,    4   ,   4   /
C        (5)      (6)      (7)     (8)
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 1
C
       DATA ((DXCPV(1,I02,L),L=1,4),I02=1,  4   )
C                                NIP(1)
C
C
C
     $/ .310    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .625    ,      0.  ,     1.2228  ,   -0.37907,
C         x            a            b            c
     $  .700    ,      0.  ,     8.19753 ,   -4.73827,
C         x            a            b            c
     $  1.050   ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 2
C
       DATA ((DXCPV(2,I02,L),L=1,4),I02=1,  3   )
C                                NIP(2)
C
C
C
     $/ .310    ,     0.   ,    1.24253  ,      0.   ,
C        x            a            b            c
     $  .365    ,      0.  ,    11.17845 ,   -3.08013,
C         x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 3
C
       DATA ((DXCPV(3,I02,L),L=1,4),I02=1,  4   )
C                                NIP(3)
C
C
C
     $/ .885    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .955    ,      0.  ,     6.13756 ,   -5.43174,
C         x            a            b            c
     $  .985    ,      0.  ,     19.01223,   -17.7271,
C         x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 4
C
       DATA ((DXCPV(4,I02,L),L=1,4),I02=1,  4   )
C                                NIP(4)
C
C
     $/ .625    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .885    ,      0.  ,    1.48148  ,   -0.92592,
C         x            a            b            c
     $  .940    ,      0.  ,     11.17845,   -9.50774,
C         x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 5
C
       DATA ((DXCPV(5,I02,L),L=1,4),I02=1,  3   )
C                                NIP(5)
C
C
C
     $/ .310    ,     0.   ,    1.24253  ,      0.   ,
C        x            a            b            c
     $  .365    ,      0.  ,    11.17845 ,   -3.08013,
C         x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 6
C
       DATA ((DXCPV(6,I02,L),L=1,4),I02=1,  4   )
C                                NIP(6)
C
C
     $/ .310    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .625    ,      0.  ,     1.2228  ,   -0.37907,
C         x            a            b            c
     $  .700    ,      0.  ,     8.19753 ,   -4.73827,
C         x            a            b            c
     $  1.050   ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 7
C
       DATA ((DXCPV(7,I02,L),L=1,4),I02=1,  4   )
C                                NIP(7)
C
C
C
     $/ .625    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  .885    ,      0.  ,    1.48148  ,   -0.92592,
C         x            a            b            c
     $  .940    ,      0.  ,     11.17845,   -9.50774,
C         x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.    /
C        x            a            b            c
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 8
C
       DATA ((DXCPV(8,I02,L),L=1,4),I02=1,  4   )
C                                NIP(8)
C
C
C
     $/ .955    ,     0.   ,       0.    ,      0.   ,
C        x            a            b            c
     $  0.980   ,      0.  ,     5.92592 ,   -5.6592 ,
C         x            a            b            c
     $  1.00    ,     0.   ,   42.5925   ,   -41.5925,
C        x            a            b            c
     $  1.05    ,     0.   ,       0.    ,      1.      /
C        x            a            b            c
C
C
C
C                  CARICAMENTO VETTORE CPVF
C
		DATA ((DXCPVF(I02,L),L=1,4),I02=1, 2  )
C                                        NIPF
C
     $/   1.    ,     0.   ,       1.    ,       0.  ,
C          x          a            b             c
     $    1.05  ,     0.   ,       0.    ,       1.  /
C          x          a            b             c
C
C
C
      TIPO=DXTIPO
C
      PSHNOM=DXPSHNOM
      TSHNOM=DXTSHNOM
      VUNOM =DXVUNOM
      WNOM  =DXWNOM
      RAGGIO=DXRAGGIO
      CCR   =DXCCR
      AETA  =DXAETA
      BETA  =DXBETA
      DPVE  =DXDPVE
      PSHF  =DXPSHF
      TSHF  =DXTSHF
      XF    =DXXF
      WF    =DXWF
      NVALV =IDXNVALV
      NIPF  =IDXNIPF
C
      DO I=1,16
      CA(I)  =DXCA(I)
      AUG(I) =DXAUG(I)
      NIA(I) =IDXNIA(I)
      NIP(I) =IDXNIP(I)
      RCA(I) =DXRCA(I)
      IAM(I) =IDXIAM(I)
       DO J=1,3
       CCF(I,J)=DXCCF(I,J)
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,3
	DO K=1,4
	CAV(I,J,K)=DXCAV(I,J,K)
	ENDDO
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,10
	DO K=1,4
	CPV(I,J,K)=DXCPV(I,J,K)
	ENDDO
       ENDDO
      ENDDO
       DO J=1,10
	DO K=1,4
	CPVF(J,K)=DXCPVF(J,K)
	ENDDO
       ENDDO
C
       RETURN
       END
C
C****** SUBROUTINE DI ACQUISIZIONE DATI PER LA TURBINA ANSALDO DA 660 MW *****
C
       SUBROUTINE DXANS660(TIPO,
     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
     $              RCA,XF,WF,IAM)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       DIMENSION   
     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
       DIMENSION   
     $             DXCA(16),DXCCF(16,3),DXAUG(16),IDXNIA(16),
     $             DXCAV(16,3,4),IDXNIP(16),DXCPV(16,10,4),
     $             DXCPVF(10,4),DXRCA(16),IDXIAM(16)
      CHARACTER*36 TIPO
      CHARACTER*36 DXTIPO
C
      DATA DXTIPO/'      TURBINA ANSALDO DA 660 MW      '/
C
C
      DATA DXPSHNOM,DXTSHNOM,DXVUNOM,DXWNOM,DXRAGGIO,DXCCR,DXAETA,
     $     DXBETA,DXDPVE,DXPSHF,DXTSHF,DXXF,DXWF,IDXNVALV,IDXNIPF
C
     $/ 24222300.,   811.15  ,  50.      , 580.625   , .52375    , 
C        PSHNOM      TSHNOM     VUNOM       WNOM       RAGGIO    
C
     $  .00003,      -3.57  ,   3.228   ,  200000.  , 24022300. ,
C          CCR         AETA      BETA        DPVE        PSHF
C
     $    810.38  ,      1.   ,  580.625 ,    4      ,    1      /
C          TSHF         XF        WF        NVALV        NIPF
C
      DATA (IDXIAM(I),I=1,4)/1,2,1,2/
C
C                  CARICAMENTO VETTORE RCA
C
                     DATA (DXRCA(I),I=1,  4   )
C                                     NVALV
C
     $/   1.    ,  .84037   , .84037  ,    .84037     /
C        (1)         (2)        (3)       (4)
C
C
C                  CARICAMENTO VETTORE CCF
C
                DATA ((DXCCF(I,J),J=1,  3   ),I=1, 4 )
C                                               NVALV
C
     $/   .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
C        (1,1)    (1,2)    (1,3)      (2,1)     (2,2)    (2,3)
     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    /
C        (3,1)    (3,2)    (3,3)      (4,1)     (4,2)    (4,3)
C
C                  CARICAMENTO VETTORE AUG
C
C
                     DATA (DXAUG(I),I=1,  4   )
C                                     NVALV
C
ccc8     $/.00797813,.00670556 , .00670556, .00670556/
     $/.007023,.007023 , .007023, .007023/
C        (1)       (2)       (3)       (4)
C
C                  CARICAMENTO VETTORE NIA
C
                     DATA (IDXNIA(I),I=1,  4   )
C                                     NVALV
C
     $/    2   ,    2    ,    2    ,   2    /
C         (1)      (2)       (3)      (4)
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 1
C
        DATA ((DXCAV(1,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(1)
C
     $/  .2255   ,  0.1387  ,   0.7193    ,    0.   ,
C         z         a            b            c
     $   1.0   , -1.3839 ,    2.7819   ,  -.3877/            
C         z         a            b            c     
C
C                  CARICAMENTO VETTORE CAV VALVOLA 2
C
        DATA ((DXCAV(2,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(2)
C
     $/  .275   ,    0.     ,   .846      ,   0.   ,
C         z         a            b            c
     $   1.0   , -1.200   ,   2.588   ,    -.3883/            
C         z         a            b            c     
C
C                  CARICAMENTO VETTORE CAV VALVOLA 3
C
        DATA ((DXCAV(3,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(3)
C
     $/  .275   ,    0.     ,   .846      ,   0.   ,
C         z         a            b            c
     $   1.0   , -1.200   ,   2.588   ,    -.3883/            
C         z         a            b            c     
C
C
C                  CARICAMENTO VETTORE CAV VALVOLA 4
C
        DATA ((DXCAV(4,I02,L),L=1,4),I02=1,  2   )
C                                 NIA(4)
C
     $/  .275   ,    0.     ,   .846      ,   0.   ,
C         z         a            b            c
     $   1.0   , -1.200   ,   2.588   ,    -.3883/            
C         z         a            b            c     
C
C
C                  CARICAMENTO VETTORE NIP
C
                     DATA (IDXNIP(I),I=1,  4  )
C                                     NVALV
C
     $/   4   ,     4    ,    5    ,    5    /
C        (1)       (2)       (3)       (4)
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 1
C
       DATA ((DXCPV(1,I02,L),L=1,4),I02=1,  4   )
C                                NIP(1)
C
C
     $/ .548   ,    0.   ,      .515      ,    0.     ,                     
C          x         a            b            c
     $  .627   ,   14.28 ,     -15.14   ,    4.29     ,                  
C         x          a            b            c     
     $  .664   ,  354.73 ,    -442.07   ,   138.13   ,                   
C        x           a            b            c     
     $  1.05    ,     0.   ,       0.    ,      1.   /                      
C         x           a            b            c     
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 2
C
       DATA ((DXCPV(2,I02,L),L=1,4),I02=1,  4   )
C                                NIP(2)
C
C
     $/ .548   ,    0.   ,       .5529    ,    0.     ,                     
C          x         a            b            c
     $  .627   ,   10.43 ,     -10.88   ,    3.13     ,                  
C         x          a            b            c     
     $  .664   ,  370.14 ,    -461.95   ,   144.54   ,                   
C        x           a            b            c     
     $  1.05    ,     0.   ,       0.    ,      1.   /                      
C         x           a            b            c     
C
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 3
C
       DATA ((DXCPV(3,I02,L),L=1,4),I02=1,  5   )
C                                NIP(3)
C
C
     $/ .627    ,     0.   ,      0.     ,      0.   ,     
C        x            a           b             c     
     $  .838    ,     0. ,     1.1468   ,     -.719  ,    
C        x            a            b            c     
     $  .878    ,   58.83 ,   -97.44  ,      40.59 ,      
C        x            a            b            c     
     $  .897    ,  1403.53,   -2458.74 ,       1077.2 ,   
C        x            a            b            c     
     $  1.05    ,     0.   ,      0.  ,      1. /    
C        x            a            b            c     
C
C
C
C                  CARICAMENTO VETTORE CPV VALVOLA 4
C
       DATA ((DXCPV(4,I02,L),L=1,4),I02=1,  5   )
C                                NIP(4)
C
C
     $/ .878    ,     0.   ,      0.     ,      0.   ,     
C        x            a           b             c     
     $  .950    ,     0. ,     1.8055   ,    -1.585  ,    
C        x            a            b            c     
     $  .990    ,   67.984 ,   -127.366 ,       59.77 ,      
C        x            a            b            c     
     $  1.    ,    6164.54  , -12198.55 ,      6035.01 ,   
C        x            a            b            c     
     $  1.05    ,     0.   ,      0.  ,        1. /    
C        x            a            b            c     
C
C
C
C
C                  CARICAMENTO VETTORE CPVF
C
                DATA ((DXCPVF(I02,L),L=1,4),I02=1, 1  )
C                                        NIPF
C
     $/   1.05  ,     0.   ,       1.    ,       0.  /
C          x          a            b             c     
C
C
      TIPO=DXTIPO
C
      PSHNOM=DXPSHNOM
      TSHNOM=DXTSHNOM
      VUNOM =DXVUNOM
      WNOM  =DXWNOM
      RAGGIO=DXRAGGIO
      CCR   =DXCCR
      AETA  =DXAETA
      BETA  =DXBETA
      DPVE  =DXDPVE
      PSHF  =DXPSHF
      TSHF  =DXTSHF
      XF    =DXXF
      WF    =DXWF
      NVALV =IDXNVALV
      NIPF  =IDXNIPF
C
      DO I=1,16
       CA(I)  =DXCA(I)
       AUG(I) =DXAUG(I)
       NIA(I) =IDXNIA(I)
       NIP(I) =IDXNIP(I)
       RCA(I) =DXRCA(I)
       IAM(I) =IDXIAM(I)
       DO J=1,3
        CCF(I,J)=DXCCF(I,J)
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,3
        DO K=1,4
        CAV(I,J,K)=DXCAV(I,J,K)
        ENDDO
       ENDDO
      ENDDO
C
      DO I=1,16
       DO J=1,5
        DO K=1,4
         CPV(I,J,K)=DXCPV(I,J,K)
        ENDDO
       ENDDO
      ENDDO
       DO J=1,10
        DO K=1,4
         CPVF(J,K)=DXCPVF(J,K)
        ENDDO
       ENDDO
C
       RETURN 
       END
C
C~FORAUS_STAZ~C
C
C****** SUBROUTINE DI ACQUISIZIONE DATI PER LA TURBINA ANSALDO DA 320 MW *****
C
C       SUBROUTINE   DXSTAZ (TIPO,
C     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
C     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
C     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
C     $              RCA,XF,WF,IAM)
CC
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C       DIMENSION
C     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
C     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
CC
CC
CC      SUBROUTINE DA COMPILARE ACURA DELL'UTENTE
CC
C      WRITE(6,*)'***ATTENZIONE . DAI DATI DEL FILE 14 DEL MODULO STAZ'
C      WRITE(6,*)' RISULTA CHE VUOI FORNIRE I DATI DI UNA TURBINA '
C      WRITE(6,*)' DIVERSA DA QUELLE INCLUSE NEL MODULO'
C      WRITE(6,*)' OVVERO : TOSIX320,TOSIX660,ANSX320'
C      WRITE(6,*)' MA NON HAI FORNITO LA SUBROUTINE'
C      WRITE(6,*)' *****   DXSTAZ   ****'
CC
C      STOP
CC
C      END
CC
CC FORTRAN AUSILIARIO DEL MODULO TURBINA STADIO AD AZIONE
CC PER LA SUA SCRITTURA VEDERE MANUALE D'USO O
CC UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD.
C
CC********************* ESEMPIO DI SUBROUTINE UTENTE **************************
CC****** SUBROUTINE DI ACQUISIZIONE DATI PER LA TURBINA ANSALDO DA 320 MW *****
CC
C       SUBROUTINE DXSTAZ(TIPO,
C     $              R,AALAM,UDVU,CCR,AETA,BETA,CEME,NVALV,
C     $              CA,CCF,AUG,NIA,CAV,CK,NIP,CPV,NIPF,CPVF,ALFA,HRIF,
C     $              PSHNOM,TSHNOM,VUNOM,WNOM,RAGGIO,DPVE,PSHF,TSHF,
C     $              RCA,XF,WF,IAM)
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C       DIMENSION
C     $              CA(16),CCF(16,3),AUG(16),NIA(16),CAV(16,3,4),
C     $              NIP(16),CPV(16,10,4),CPVF(10,4),RCA(16),IAM(16)
C       DIMENSION
C     $             DXCA(16),DXCCF(16,3),DXAUG(16),IDXNIA(16),
C     $             DXCAV(16,3,4),IDXNIP(16),DXCPV(16,10,4),
C     $             DXCPVF(10,4),DXRCA(16),IDXIAM(16)
C      CHARACTER*36 TIPO
C      CHARACTER*37 DXTIPO
CC
C      DATA DXTIPO/'      TURBINA ANSALDO DA 320 MW      '/
CC
CC
C      DATA DXPSHNOM,DXTSHNOM,DXVUNOM,DXWNOM,DXRAGGIO,DXCCR,DXAETA,
C     $     DXBETA,DXDPVE,DXPSHF,DXTSHF,DXXF,DXWF,IDXNVALV,IDXNIPF
CC
C     $/ 16670000.,   811.15  ,  50.      , 299.145   , .4826     ,
CC        PSHNOM      TSHNOM     VUNOM       WNOM       RAGGIO
CC
C     $  .00002132,    -3.57  ,   3.228   ,  294000.  , 16670000. ,
CC          CCR         AETA      BETA        DPVE        PSHF
CC
C     $    811.15 ,      1.   ,  299.145  ,    4      ,    1      /
CC          TSHF         XF        WF        NVALV        NIPF
CC
C      DATA (IDXIAM(I),I=1,4)/1,2,1,2/
CC
CC                  CARICAMENTO VETTORE RCA
CC
C                     DATA (DXRCA(I),I=1,  4   )
CC                                     NVALV
CC
C     $/   1.    ,  .84037   , .84037  ,    1.     /
CC        (1)         (2)        (3)       (4)
CC
CC
CC                  CARICAMENTO VETTORE CCF
CC
C                DATA ((DXCCF(I,J),J=1,  3   ),I=1, 4 )
CC                                               NVALV
CC
C     $/   .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    ,
CC        (1,1)    (1,2)    (1,3)      (2,1)     (2,2)    (2,3)
C     $    .14  ,  -.49   ,  .93    ,   .14   ,  -.49   ,  .93    /
CC        (3,1)    (3,2)    (3,3)      (4,1)     (4,2)    (4,3)
CC
CC                  CARICAMENTO VETTORE AUG
CC
C                     DATA (DXAUG(I),I=1,  4   )
CC                                     NVALV
CC
C     $/.0063904,.0053541 , .0053541, .006394/
CC        (1)       (2)       (3)       (4)
CC
CC                  CARICAMENTO VETTORE NIA
CC
C                     DATA (IDXNIA(I),I=1,  4   )
CC                                     NVALV
CC
C     $/    2   ,    2    ,    2    ,   2    /
CC         (1)      (2)       (3)      (4)
CC
CC
CC                  CARICAMENTO VETTORE CAV VALVOLA 1
CC
C        DATA ((DXCAV(1,I02,L),L=1,4),I02=1,  2   )
CC                                 NIA(1)
CC
C     $/  .55   ,    0.     ,   1.24      ,    0.   ,
CC         z         a            b            c
C     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
CC         z         a            b            c
CC
CC                  CARICAMENTO VETTORE CAV VALVOLA 2
CC
C        DATA ((DXCAV(2,I02,L),L=1,4),I02=1,  2   )
CC                                 NIA(2)
CC
C     $/  .55   ,    0.     ,   1.24      ,    0.   ,
CC         z         a            b            c
C     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
CC         z         a            b            c
CC
CC                  CARICAMENTO VETTORE CAV VALVOLA 3
CC
C        DATA ((DXCAV(3,I02,L),L=1,4),I02=1,  2   )
CC                                 NIA(3)
CC
C     $/  .55   ,    0.     ,   1.24      ,    0.   ,
CC         z         a            b            c
C     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
CC         z         a            b            c
CC
CC
CC                  CARICAMENTO VETTORE CAV VALVOLA 4
CC
C        DATA ((DXCAV(4,I02,L),L=1,4),I02=1,  2   )
CC                                 NIA(4)
CC
C     $/  .55   ,    0.     ,   1.24      ,    0.   ,
CC         z         a            b            c
C     $   1.0   ,-1.1851852 , 2.5437037   , -.35851852/
CC         x         a            b            c
CC
CC
CC                  CARICAMENTO VETTORE NIP
CC
C                     DATA (IDXNIP(I),I=1,  4  )
CC                                     NVALV
CC
C     $/   9   ,     7    ,    5    ,    3    /
CC        (1)       (2)       (3)       (4)
CC
CC
CC                  CARICAMENTO VETTORE CPV VALVOLA 1
CC
C       DATA ((DXCPV(1,I02,L),L=1,4),I02=1,  9   )
CC                                NIP(1)
CC
CC
C     $/  .15   ,  1.2444444,     0.      ,    0.     ,
CC          x         a            b            c
C     $  .275   ,  -.574359 ,  .7401026   , -.07009231,
CC         x          a            b            c
C     $  .35    ,  2.142857 , -.7392857   ,   .13125  ,
CC        x           a            b            c
C     $  .45     ,     0.   ,     .83     ,  -.1555   ,
CC        x            a            b            c
C     $  .575    , 2.246154 , -1.206308   , .3059923  ,
CC        x            a            b            c
C     $  .725    , -1.777778,  3.711111   ,  -1.191111,
CC        x            a            b            c
C     $  .8      , 19.285714, -26.210714  ,  9.430714 ,
CC        x            a            b            c
C     $  .865    ,    -30.  ,    52.95    ,  -22.355  ,
CC        x            a            b            c
C     $  1.05    ,     0.   ,       0.    ,      1.   /
CC         x           a            b            c
CC
CC
CC
CC                  CARICAMENTO VETTORE CPV VALVOLA 2
CC
C       DATA ((DXCPV(2,I02,L),L=1,4),I02=1,  7   )
CC                                NIP(2)
CC
CC
C     $/ .2      ,     0.   ,       0.    ,      0.   ,
CC        x            a            b            c
C     $  .4      ,    1.55  ,    -.155    ,    -.031  ,
CC        x            a            b            c
C     $  .525    , -2.461538,    3.116923 ,  -.697923 ,
CC        x            a            b            c
C     $  .75     ,  5.155555,    -5.017778,  1.473333 ,
CC        x            a            b            c
C     $  .825    ,     0.   ,    2.866667 ,    -1.54  ,
CC        x            a            b            c
C     $  .93     ,-9.6969697,   18.684848 ,    -7.99  ,
CC        x            a            b            c
C     $  1.05    ,     0.   ,       0.    ,      1.   /
CC        x            a            b            c
CC
CC
CC
CC                  CARICAMENTO VETTORE CPV VALVOLA 3
CC
C       DATA ((DXCPV(3,I02,L),L=1,4),I02=1,  5   )
CC                                NIP(3)
CC
CC
C     $/ .715    ,     0.   ,      0.     ,      0.   ,
CC        x            a           b             c
C     $  .8      , 9.344538 ,-12.604034   ,  4.234723 ,
CC        x            a            b            c
C     $  .875    , 35.73333 ,  -54.94666  ,    21.22  ,
CC        x            a            b            c
C     $  .96     ,-41.37255 ,   81.03627  , -38.73088 ,
CC        x            a            b            c
C     $  1.05    ,     0.   ,   .7222222  ,  .2416667 /
CC        x            a            b            c
CC
CC
CC
CC                  CARICAMENTO VETTORE CPV VALVOLA 4
CC
C       DATA ((DXCPV(4,I02,L),L=1,4),I02=1,  3   )
CC                                NIP(4)
CC
CC
CC
C     $/ .865    ,     0.   ,       0.    ,      0.   ,
CC        x            a            b            c
C     $  .95     , 24.20168 ,  -41.57311  ,     17.8  ,
CC         x            a            b            c
C     $  1.05    ,   57.6   ,   -105.48   ,     48.4  /
CC        x            a            b            c
CC
C
CC                  CARICAMENTO VETTORE CPVF
CC
C                DATA ((DXCPVF(I02,L),L=1,4),I02=1, 1  )
CC                                        NIPF
CC
C     $/   1.05  ,     0.   ,       1.    ,       0.  /
CC          x          a            b             c
CC
CC
C      TIPO=DXTIPO
CC
C      PSHNOM=DXPSHNOM
C      TSHNOM=DXTSHNOM
C      VUNOM =DXVUNOM
C      WNOM  =DXWNOM
C      RAGGIO=DXRAGGIO
C      CCR   =DXCCR
C      AETA  =DXAETA
C      BETA  =DXBETA
C      DPVE  =DXDPVE
C      PSHF  =DXPSHF
C      TSHF  =DXTSHF
C      XF    =DXXF
C      WF    =DXWF
C      NVALV =IDXNVALV
C      NIPF  =IDXNIPF
CC
C      DO I=1,16
C      CA(I)  =DXCA(I)
C      AUG(I) =DXAUG(I)
C      NIA(I) =IDXNIA(I)
C      NIP(I) =IDXNIP(I)
C      RCA(I) =DXRCA(I)
C      IAM(I) =IDXIAM(I)
C       DO J=1,3
C       CCF(I,J)=DXCCF(I,J)
C       ENDDO
C      ENDDO
CC
C      DO I=1,16
C       DO J=1,3
C        DO K=1,4
C        CAV(I,J,K)=DXCAV(I,J,K)
C        ENDDO
C       ENDDO
C      ENDDO
CC
C      DO I=1,16
C       DO J=1,10
C        DO K=1,4
C        CPV(I,J,K)=DXCPV(I,J,K)
C        ENDDO
C       ENDDO
C      ENDDO
C       DO J=1,10
C        DO K=1,4
C        CPVF(J,K)=DXCPVF(J,K)
C        ENDDO
C       ENDDO
CC
C       RETURN
C       END
C******************** FINE ESEMPIO DATI TURBINA *****************************
C~FORAUS_STAZ~C
CC
      SUBROUTINE STAZD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $  XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
