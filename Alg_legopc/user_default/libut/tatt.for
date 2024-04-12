      SUBROUTINE TATTI3 (IFO,IOB,DEBL)
      CHARACTER*4 IOB, MOD, DEBL*80
      DATA MOD /'TATT'/
C
      CALL TATTI4(NSTADI,NINJEC)
      WRITE(IFO,2999)MOD,IOB,IOB,MOD,DEBL
      WRITE(IFO,3000)
     $ 'WSCA',IOB,'UA','EXAUST FLOW RATE AT GAS TURBINE OUTLET',
     $ 'TSCA',IOB,'UA','EXAUST TEMPERATURE AT GAS TURBINE OUTLET',
     $ 'QTUR',IOB,'UA','MECHANICAL POWER PRODUCED BY GAS TURBINE'
      IF (NSTADI .GT. 1) WRITE(IFO,3000)
     $ 'WAMM',IOB,'UA','FLUE GAS FLOW RATE AT TURBINE INLET'
      IF (NSTADI .GT. 2) WRITE(IFO,3001) (I, IOB, I, I = 2, NSTADI-1)
      IF (NSTADI .GT. 1) WRITE(IFO,3002) (I, IOB, I, I = 1, NSTADI-1)
      IF (NSTADI .GT. 1) WRITE(IFO,3003) (I, IOB, I, I = 1, NSTADI-1)
      IF (NSTADI .GT. 1) WRITE(IFO,3004) (I, IOB, I, I = 1, NSTADI-1)
      WRITE(IFO,3000)
     $ 'PAMM',IOB,'IN','GAS TURBINE INLET PRESSURE (HOT CHAMBER)',
     $ 'TAMM',IOB,'IN','FLUE GAS TEMPERATURE AT TURBINE INLET',
     $ 'PSCA',IOB,'IN','PRESSURE AT GAS TURBINE OUTLET',
     $ 'RPMC',IOB,'IN','ROTATIONAL SPEED OF TG GROUP SHAFT',
     $ 'XCOM',IOB,'IN','FUEL/AIR MASS RATIO (FLUE GAS CHEM. COMP.)',
     $ 'XH2O',IOB,'IN','H2O/AIR MASS RATIO (FLUE GAS CHEM. COMP.)',
     $ 'XXCH',IOB,'IN','H/C MOLAR RATIO (FUEL MEAN CHEM. COMP.)',
     $ 'ZMN2',IOB,'IN','INERT MASS PERCENTAGE (FUEL MEAN CHEM. COMP.)'
      IF (NINJEC .GT. 0) WRITE(IFO,3005) (I, IOB, I, I = 1, NINJEC)
      IF (NINJEC .GT. 0) WRITE(IFO,3006) (I, IOB, I, I = 1, NINJEC)
      RETURN
 2999 FORMAT(2A4,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
 3001 FORMAT('WST',I1,A4,2X,
     $  '--UA-- FLUE GAS FLOW RATE THROUGH TURBINE STAGE N. ',I1)
 3002 FORMAT('PCA',I1,A4,2X,
     $  '--UA-- FLUE GAS PRESSURE DOWNSTREAM TURBINE STAGE N. ',I1)
 3003 FORMAT('TCA',I1,A4,2X,
     $  '--UA-- FLUE GAS TEMPERATURE DOWNSTREAM TURBINE STAGE N. ',I1)
 3004 FORMAT('TMX',I1,A4,2X,
     $  '--UA-- FLUE GAS TEMPERATURE AFTER AIR MIXING IN CAV. N. ',I1)
 3005 FORMAT('WIN',I1,A4,2X,
     $  '--IN-- AIR FLOW RATE THROUGH TURBINE INJECTION N. ',I1)
 3006 FORMAT('TIN',I1,A4,2X,
     $  '--IN-- AIR TEMPERATURE AT TURBINE INJECTION INLET N. ',I1)
      END
C
C
C
      SUBROUTINE TATTI4 (NSTADI,NINJEC)
C
    3 WRITE (6,1)
      READ (5,*,ERR=3) NSTADI
      IF (NSTADI .LT. 1 .OR. NSTADI .GT. 9) GOTO 3
C
    4 WRITE (6,2)
      READ (5,*,ERR=4) NINJEC
      IF (NINJEC .LT. 0 .OR. NINJEC .GT. 7) GOTO 4
C
      RETURN
    1 FORMAT (/5X,'TYPE THE NUMBER OF GAS TURBINE STAGES (MAX. 9)')
    2 FORMAT (/5X,'TYPE THE NUMBER OF COOLING INJECTIONS (MAX. 7)')
      END
C
C
C
      SUBROUTINE TATTI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                   IBL1,IBL2,IER,CNXYU,TOL)
      REAL VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
      LOGICAL KREGIM
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      PARAMETER (NTIP = 4)
      DIMENSION CB(9), CE(4), CF(2), XC(2),
     $          AEFL(9), XINJEC(7), IINJEC(7)
C
C---Turbina fumi TG "fisica"
C
      NINJEC = (NINGRE - 8) / 2
      NSTADI = (NUSCIT + 1) / 4
      NCAVIT = NSTADI - 1
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'Pamm nom','Psca nom','Wfum nom',
     $              'Tamm nom','EtaS nom','TG type '
      IF (NINJEC .GT. 0) WRITE(14,502) ('Injecn.', J, J=1,NINJEC)
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) PAMNOM, PSCNOM, WFUNOM,
     $             TAMNOM, ETANOM, TIPO
      ITIPO = NINT (TIPO)
      IF (ITIPO .GE. 1 .AND. ITIPO .LE. NTIP) THEN
        CALL TATTDT (ITIPO, IER, NSTADI, CB, CE, CF, XC)
      ELSE
        CALL TATTDU (ITIPO, IER, NSTADI, CB, CE, CF, XC)
      ENDIF
      IF (NINJEC .GT. 0) THEN
        READ (14,501) (XINJEC(J), J=1,NINJEC)
        DO J = 1, NINJEC
          IINJEC(J) = NINT(XINJEC(J))
          IF (IINJEC(J) .LT. 1 .OR. IINJEC(J) .GE. NSTADI) THEN
            WRITE (6,*) 'ERROR: INJECTION POSITION OUTSIDE TURBINE'
            IER=1
          ENDIF
          DO K = 1, J-1
            IF (IINJEC(J) .EQ. IINJEC(K)) THEN
              WRITE (6,*) 'ERROR: MORE THAN ONE INJECTION IN THE ',
     $                    'SAME GAS TURBINE CAVITY'
              IER=1
            ENDIF
          ENDDO
        ENDDO
      ENDIF
C
      CALL INITAF (4, XC, CF)
      CALL TAVOAF (PAMNOM,TAMNOM,RAMNOM,HAMNOM,SAMNOM,4)
      PVANOM = PVECAF (PAMNOM,TAMNOM,PSCNOM,4)
      WEPS = 0.01 * WFUNOM
      BETNOM = PAMNOM / PSCNOM
      AEFGLO = SQRT (WFUNOM * (ABS(WFUNOM) + WEPS) * PAMNOM / RAMNOM /
     $         (PAMNOM ** 2 - PVANOM ** 2))
      DO I = 1, NSTADI
        AEFL(I) = AEFGLO * CB(I)
      ENDDO
C
      DATI(ID2  ) = FLOAT (NSTADI)
      DATI(ID2+1) = FLOAT (NINJEC)
      DATI(ID2+2) = BETNOM
      DATI(ID2+3) = ETANOM
      DATI(ID2+4) = WEPS
      IDJ = ID2 + 4
C
      DO I = 1, 4
        IDJ = IDJ + 1
        DATI(IDJ) = CE(I)
      ENDDO
      DO I = 1, NSTADI
        IDJ = IDJ + 1
        DATI(IDJ) = AEFL(I)
      ENDDO
      DO I = 1, NINJEC
        IDJ = IDJ + 1
        DATI(IDJ) = FLOAT(IINJEC(I))
      ENDDO
C
      ID2 = IDJ
C
C---costanti di normalizzazione
C
      CNXYU(IV1  ) = W0
      CNXYU(IV1+1) = T0
      CNXYU(IV1+2) = W0*H0
      IPW = IV1+2
      IPP = IPW+NCAVIT
      IPT = IPP+NCAVIT
      IPM = IPT+NCAVIT
      DO I = 1, NCAVIT
        CNXYU(IPW+I) = W0
        CNXYU(IPP+I) = P0
        CNXYU(IPT+I) = T0
        CNXYU(IPM+I) = T0
      ENDDO
      IPI = IPM+NCAVIT
      CNXYU(IPI+1) = P0
      CNXYU(IPI+2) = T0
      CNXYU(IPI+3) = P0
      CNXYU(IPI+4) = 300.
      CNXYU(IPI+5) = 1.
      CNXYU(IPI+6) = 1.
      CNXYU(IPI+7) = 1.
      CNXYU(IPI+8) = 1.
      IPS = IPI+8
      IPJ = IPS+NINJEC
      DO I = 1, NINJEC
        CNXYU(IPS+I) = W0
        CNXYU(IPJ+I) = T0
      ENDDO
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
  502 FORMAT(3(4X,A7,I1,' =',10X,'*'))
C
      RETURN
      END
C
C
C
      SUBROUTINE TATTC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL TATT
C
C---Compressore aria TG "fisico"
C
      NSTADI = NINT(DATI(IPD))
      NINJEC = NINT(DATI(IPD + 1))
      NCAVIT = NSTADI - 1
      NSTATI = 0
      NUSCIT = NSTADI * 4 - 1
      NINGRE = NINJEC * 2 + 8
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 DO I = 1, NUSCIT
        DO J = 1, NUSCIT+NINGRE
          AJAC (I,J) = 1.
        ENDDO
      ENDDO
      RETURN
C
C---calcolo residui
C
  200 CALL TATT (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 EPS    = 1.E-4
      EPSLIM = 1.E-6
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,TATT)
      RETURN
      END
C
C
C
      SUBROUTINE TATT (IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
      DIMENSION TCAV(9),PCAV(9),WSTA(9),TMIX(9),WSTAC(9),TCAVC(9),
     $          TMIXC(9),RMON(9),PMON(9),PVAL(9),WINJEC(7),TINJEC(7),
     $          IINJEC(7),AEFL(9),XC(2),CE(4),CF(2)
C
C---decodifica variabili e dati
C
      NSTADI = NINT (DATI(IPD  ))
      NINJEC = NINT (DATI(IPD+1))
      NCAVIT = NSTADI - 1
      BETNOM = DATI (IPD+2)
      ETANOM = DATI (IPD+3)
      WEPS   = DATI (IPD+4)
      IDJ = IPD + 4
C
      DO I = 1, 4
        IDJ = IDJ + 1
        CE(I) = DATI(IDJ)
      ENDDO
      DO I = 1, NSTADI
        IDJ = IDJ + 1
        AEFL(I) = DATI(IDJ)
      ENDDO
      DO I = 1, NINJEC
        IDJ = IDJ + 1
        IINJEC(I) = NINT(DATI(IDJ))
      ENDDO
C
      WSCA = XYU(IXYU  )*W0
      TSCA = XYU(IXYU+1)*T0
      QMEC = XYU(IXYU+2)*W0*H0
      IPW = IXYU+2
      IPP = IPW+NCAVIT
      IPT = IPP+NCAVIT
      IPM = IPT+NCAVIT
      DO I = 1, NCAVIT
        WSTA(I) = XYU(IPW+I)*W0
        PCAV(I) = AMAX1(XYU(IPP+I)*P0, 5000.)
        TCAV(I) = XYU(IPT+I)*T0
        TMIX(I) = XYU(IPM+I)*T0
        WINJEC(I) = 0.
        TINJEC(I) = TCAV(I)
      ENDDO
      IPI = IPM+NCAVIT
      PAMM = AMAX1(XYU(IPI+1)*P0, 5000.)
      TAMM = XYU(IPI+2)*T0
      PSCA = AMAX1(XYU(IPI+3)*P0, 5000.)
      OMEG = XYU(IPI+4)*300.
      CF(1) = XYU(IPI+5)
      CF(2) = XYU(IPI+6)
      XC(1) = XYU(IPI+7)
      XC(2) = XYU(IPI+8)/100.
      IPS = IPI+8
      IPJ = IPS+NINJEC
      DO I = 1, NINJEC
        WPS = XYU(IPS+I)*W0
        TPS = XYU(IPJ+I)*T0
        ISP = IINJEC(I)
        WINJEC(ISP) = WPS
        TINJEC(ISP) = TPS
      ENDDO
C
      CALL INITAF (3,0.,0.)
      CALL INITAF (4,XC,CF)
      CALL TAVOAF (PAMM, TAMM, RAMM, HAMM, SAMM, 4)
C
C---Calcolo rendimento di espansione
C
      BETA = PAMM / PSCA
      ZETA = 1. - BETA / BETNOM
      ETA = ETANOM * (CE(1) + (1. - CE(1)) / (1. + CE(2) * ZETA**2))
      ETAI = 1. - CE(3) * (1. - ETA)
C
C---Calcolo condizioni di uscita
C
      CALL STPIAF (SAMM,TUISO,PSCA,2,4)
      CALL THINAF (TUISO,HUISO,1,4)
      HUSC = HAMM - ETA * (HAMM - HUISO)
      WSOM = AMAX1 (WSTA(1), WEPS)
      QSOM = WSOM * HUSC
      DO I = 1, NCAVIT
        WINJ = AMAX1(WINJEC(I), 0.)
        CALL THINAF (TINJEC(I),HINJ,1,3)
        WSOM = WSOM + WINJ
        QSOM = QSOM + WINJ * HINJ
      ENDDO
      HSCA = QSOM / WSOM
      CALL THINAF (TSCAC,HSCA,2,4)
C
C---Calcolo calore specifico medio del fluido
C
      TMED = 0.5 * (TAMM + TSCAC)
      CALL R1CPAF (TMED,R1AV,CPAV,CVAV,4)
      ESP = R1AV / CPAV
C
C---Calcolo temperature cavita`
C
      TPREC = TAMM
      PPREC = PAMM
      DO I = 1, NCAVIT
        PSUCC = PCAV(I)
        PVAL(I) = PVECAF (PPREC, TPREC, PSUCC, 4)
        AKISO = (PSUCC / PPREC) ** ESP
        TCAVC(I) = TPREC * (1. - ETAI * (1. - AKISO))
        WFUM = AMAX1 (WSTA(I), WEPS)
        WINJ = AMAX1 (WINJEC(I), 0.)
        TMIXC(I) = (TCAVC(I) * WFUM + TINJEC(I) * WINJ) / (WFUM + WINJ)
        TPREC = TMIXC(I)
        PPREC = PSUCC
      ENDDO
      PVAL(NSTADI) = PVECAF (PPREC, TPREC, PSCA, 4)
      AKISO = (PSCA / PPREC) ** ESP
      TUSTI = TPREC * (1. - ETAI * (1. - AKISO))
      DTCORR = (TSCAC - TUSTI) / FLOAT(NSTADI)
C
      QMECC = 0.
      HPREC = HAMM
      RMON(1) = RAMM
      PMON(1) = PAMM
      DO I = 1, NCAVIT
        TCAVC(I) = TCAVC(I) + DTCORR * FLOAT(I)
        TMIXC(I) = TMIXC(I) + DTCORR * FLOAT(I)
        CALL THINAF (TCAVC(I),HSUCC,1,4)
        QMECC = QMECC + WSTA(I) * (HPREC - HSUCC)
        CALL TAVOAF (PCAV(I),TMIXC(I),RMON(I+1),HPREC,SPREC,4)
        PMON(I+1) = PCAV(I)
      ENDDO
      QMECC = QMECC + WSCA * (HPREC - HSCA)
      QMECC = QMECC * CE(4)
      WSTA(NSTADI) = WSCA
C
      IPW = 3
      IPP = IPW+NCAVIT
      IPT = IPP+NCAVIT
      IPM = IPT+NCAVIT
C
C---assegnazione residui
C
      RNI(1) = (WSCA * (ABS(WSCA) + WEPS) -
     $         AEFL(NSTADI)**2 * (PMON(NSTADI)**2 - PVAL(NSTADI)**2) *
     $         RMON(NSTADI) / PMON(NSTADI)) / W0**2
      RNI(2) = (TSCA - TSCAC) / T0
      RNI(3) = (QMEC - QMECC) / (W0*H0)
      DO I = 1, NCAVIT
        RNI(IPW+I) = (WSTA(I) - WSTA(I+1) + WINJEC(I)) / W0
        RNI(IPP+I) = (WSTA(I) * (ABS(WSTA(I)) + WEPS) -
     $               AEFL(I)**2 * (PMON(I)**2 - PVAL(I)**2) *
     $               RMON(I) / PMON(I)) / W0**2
        RNI(IPT+I) = (TCAV(I) - TCAVC(I)) / T0
        RNI(IPM+I) = (TMIX(I) - TMIXC(I)) / T0
      ENDDO
      RETURN
      END
C
C
C
      SUBROUTINE TATTDT (ITIPO, IER, NSTADI, CB, CE, CF, XC)
C
      DIMENSION CB(9), CE(4), CF(2), XC(2)
C
      PARAMETER (NTIP = 4)
      PARAMETER (NSTA1 = 4, NSTA2 = 4, NSTA3 = 4, NSTA4 = 4)
      DIMENSION NSTA(NTIP), XCE(4,NTIP), XCF (2,NTIP), XXC (2,NTIP),
     $          XCB(9,NTIP)
      CHARACTER *30 DESC(NTIP)
C
      DATA NSTA / NSTA1, NSTA2, NSTA3, NSTA4 /
      DATA DESC / 'FIAT TG50D', 'Siemens V94.3', 'Siemens V94.2',
     $            'FIAT TG701F' /
C
C---Turbine data
C
      DATA XCE /
     $    0.0551,  0.1383, 1.253, 1.000,
     $    0.0551,  0.1383, 1.253, 1.016,
     $    0.0551,  0.1383, 1.253, 1.015,
     $    0.0551,  0.1383, 1.253, 1.023 /
C
      DATA XCF /
     $    0.02069, 0.00000,
     $    0.02069, 0.02906,
     $    0.01805, 0.00000,
     $    0.02692, 0.00000 /
C
      DATA XXC /
     $    3.82935, 0.0000000,
     $    3.82935, 0.0083206,
     $    3.84500, 0.0000000,
     $    3.82900, 0.0000000 /
C
      DATA (XCB(I,1), I = 1, NSTA1) /
     $    0.9436, 1.7348, 2.9915, 5.2204 /
C
      DATA (XCB(I,2), I = 1, NSTA2) /
     $    1.0000, 1.8386, 3.1704, 5.5326 /
C
      DATA (XCB(I,3), I = 1, NSTA3) /
     $    1.0000, 1.8319, 2.8784, 4.5972 /
C
      DATA (XCB(I,4), I = 1, NSTA3) /
     $    1.0000, 1.7691, 3.3506, 6.3372 /
C
      IF (NSTADI .NE. NSTA(ITIPO)) THEN
        WRITE (6,1) ITIPO, DESC(ITIPO), NSTA(ITIPO), NSTADI
    1   FORMAT (5X,'********* MODULE TATT ********',/,
     $    5X,'***ERROR: FOR TG TYPE =',I3,' --> ',A,/,
     $    5X,'   THE NUMBER OF STAGES MUST BE',I2,
     $       ' (ACTUAL NUMBER IS',I2,')')
        IER = 1
        RETURN
      ENDIF
C
      DO I = 1, 4
        CE(I) = XCE(I,ITIPO)
      ENDDO
      DO I = 1, 2
        CF(I) = XCF(I,ITIPO)
      ENDDO
      DO I = 1, 2
        XC(I) = XXC(I,ITIPO)
      ENDDO
      DO I = 1, NSTADI
        CB(I) = XCB(I,ITIPO)
      ENDDO
C
      WRITE (6,*) 'TATT - DATA ASSIGNED FOR TG TYPE: ', DESC(ITIPO)
C
      RETURN
      END
C
C
C
      SUBROUTINE TATTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $  XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
C
C
C
      SUBROUTINE TATTDU (ITIPO, IER, NSTADI, CB, CE, CF, XC)
C
      DIMENSION CB(9), CE(4), CF(2), XC(2)
C
      WRITE (6,1) ITIPO
    1 FORMAT (5X,'********* MODULE TATT - SUBROUTINE',
     $        ' TATTDU (USER TURBINE DATA) ********',/,
     $        5X,'***ERROR: TG TYPE',I5,' IS UNKNOWN')
      IER = 1
      RETURN
      END

C
C~FORAUS_TATT~
CC
C---SUBROUTINE TATTDU:
C   used to assign data for the compressor of an user-defined TG
C   Note: IER is the TATTI2 parameter IER (set to 1 to abort LG3)
CC
C      SUBROUTINE TATTDU (ITIPO, IER, NSTADI, CB, CE, CF, XC)
CC
C      DIMENSION CB(9), CE(4), CF(2), XC(2)
CC
C      WRITE (6,1) ITIPO
C    1 FORMAT (5X,'********* MODULE TATT - SUBROUTINE',
C     $        ' TATTDU (USER TURBINE DATA) ********',/,
C     $        5X,'***ERROR: TG TYPE',I5,' IS UNKNOWN')
C      IER = 1
C      RETURN
C      END
CC
C~FORAUS_TATT~
