      SUBROUTINE CATTI3 (IFO,IOB,DEBL) 
      CHARACTER*4 IOB, MOD, DEBL*80
      DATA MOD /'CATT'/
C
      CALL CATTI4(NSTADI,NSPILL)
      WRITE(IFO,2999)MOD,IOB,IOB,MOD,DEBL
      WRITE(IFO,3000)
     $ 'WMAN',IOB,'UA','AIR FLOW RATE AT COMPRESSOR OUTLET',
     $ 'TMAN',IOB,'UA','AIR TEMPERATURE AT COMPRESSOR OUTLET',
     $ 'QCOM',IOB,'UA','MECHANICAL POWER ABSORBED BY AIR COMPRESSOR'
      IF (NSTADI .GT. 1) WRITE(IFO,3000)
     $ 'WASP',IOB,'UA','AIR FLOW RATE AT COMPRESSOR INLET'
      IF (NSTADI .GT. 2) WRITE(IFO,3001) (I, IOB, I, I = 2, NSTADI-1)
      IF (NSTADI .GT. 1) WRITE(IFO,3002) (I, IOB, I, I = 1, NSTADI-1)
      IF (NSTADI .GT. 1) WRITE(IFO,3003) (I, IOB, I, I = 1, NSTADI-1)
      WRITE(IFO,3000)
     $ 'PASP',IOB,'IN','AIR PRESSURE AT TG COMPRESSOR INLET',
     $ 'TASP',IOB,'IN','AIR TEMPERATURE AT TG COMPRESSOR INLET',
     $ 'PMAN',IOB,'IN','COMPRESSOR OUTLET PRESSURE (COLD CHAMBER)',
     $ 'RPMC',IOB,'IN','ROTATIONAL SPEED OF TG GROUP SHAFT',
     $ 'AIGV',IOB,'IN','IGV DEVIATION FROM NOMINAL CONDITION [DEG]',
     $ 'ZSPO',IOB,'IN','COMPRESSOR BLADES GRITNESS DEGREE [%]'
      IF (NSPILL .GT. 0) WRITE(IFO,3004) (I, IOB, I, I = 1, NSPILL)
      RETURN
 2999 FORMAT(2A4,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
 3001 FORMAT('WST',I1,A4,2X,
     $  '--UA-- AIR FLOW RATE THROUGH COMPRESSOR STAGE N. ',I1)
 3002 FORMAT('PCA',I1,A4,2X,
     $  '--UA-- AIR PRESSURE DOWNSTREAM COMPRESSOR STAGE N. ',I1)
 3003 FORMAT('TCA',I1,A4,2X,
     $  '--UA-- AIR TEMPERATURE DOWNSTREAM COMPRESSOR STAGE N. ',I1)
 3004 FORMAT('WSP',I1,A4,2X,
     $  '--IN-- AIR FLOW RATE THROUGH COMPRESSOR BLEEDING N. ',I1)
      END
C
C
C
      SUBROUTINE CATTI4 (NSTADI,NSPILL)
C
    3 WRITE (6,1)
      READ (5,*,ERR=3) NSTADI
      IF (NSTADI .LT. 1 .OR. NSTADI .GT. 9) GOTO 3
C
    4 WRITE (6,2)
      READ (5,*,ERR=4) NSPILL
      IF (NSPILL .LT. 0 .OR. NSPILL .GT. 7) GOTO 4
C
      RETURN
    1 FORMAT (/5X,'TYPE THE NUMBER OF COMPRESSOR STAGES (MAX. 9)')
    2 FORMAT (/5X,'TYPE THE NUMBER OF COMPRESSOR BLEEDS (MAX. 7)')
      END
C
C
C
      SUBROUTINE CATTI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                   IBL1,IBL2,IER,CNXYU,TOL)
      REAL VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
      LOGICAL KREGIM
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      PARAMETER (NTIP = 4)
      DIMENSION CW(5), CE(4), CI(3), CS(4,5), CB(4,9)
      DIMENSION XSPILL(7), ISPILL(7)
C
C---Compressore aria TG
C
      NSPILL = NINGRE - 6
      NSTADI = NUSCIT / 3
      NCAVIT = NSTADI - 1
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'W  nom. ','Pi nom. ','Pu nom. ',
     $              'Ti nom. ','RPM nom.','Eta nom.',
     $              'TG type ','Rid.Eta%'
      IF (NSPILL .GT. 0) WRITE(14,502) ('Bleedn.', J, J=1,NSPILL)
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) WNOM,PINOM,PUNOM,TINOM,OMNOM,ETANOM
      READ(14,501) TIPO, ETARID
      ITIPO = NINT (TIPO)
      IF (ITIPO .GE. 1 .AND. ITIPO .LE. NTIP) THEN
        CALL CATTDT (ITIPO, IER, NSTADI, CW, CE, CI, CS, CB)
      ELSE
        CALL CATTDU (ITIPO, IER, NSTADI, CW, CE, CI, CS, CB)
      ENDIF
      IF (NSPILL .GT. 0) THEN
        READ (14,501) (XSPILL(J), J=1,NSPILL)
        DO J = 1, NSPILL
          ISPILL(J) = NINT(XSPILL(J))
          IF (ISPILL(J) .LT. 1 .OR. ISPILL(J) .GE. NSTADI) THEN
            WRITE (6,*) 'ERROR: BLEED POSITION OUTSIDE COMPRESSOR'
            IER=1
          ENDIF
        ENDDO
      ENDIF
C
      CALL INITAF (3, 0., 0.)
      CALL TAVOAF (PINOM,TINOM,RINOM,HINOM,SINOM,3)
      BETNOM = PUNOM / PINOM
      OMADIM = OMNOM / SQRT(PINOM / RINOM)
      WANORM = WNOM / (RINOM * OMNOM)
C
      DATI(ID2  ) = FLOAT (NSTADI)
      DATI(ID2+1) = FLOAT (NSPILL)
      DATI(ID2+2) = ETANOM
      DATI(ID2+3) = OMADIM
      DATI(ID2+4) = WANORM
      DATI(ID2+5) = BETNOM
      DATI(ID2+6) = ETARID / 100.
C
      IDJ = ID2 + 6
      DO I = 1, 5
        IDJ = IDJ + 1
        DATI(IDJ) = CW(I)
      ENDDO
      DO I = 1, 4
        IDJ = IDJ + 1
        DATI(IDJ) = CE(I)
      ENDDO
      DO I = 1, 3
        IDJ = IDJ + 1
        DATI(IDJ) = CI(I)
      ENDDO
      DO J = 1, 5
        DO I = 1, 4
          IDJ = IDJ + 1
          DATI(IDJ) = CS(I,J)
        ENDDO
      ENDDO
      DO J = 1, NCAVIT
        DO I = 1, 4
          IDJ = IDJ + 1
          DATI(IDJ) = CB(I,J)
        ENDDO
      ENDDO
      DO J = 1, NSPILL
        IDJ = IDJ + 1
        DATI(IDJ) = FLOAT(ISPILL(J))
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
      DO I = 1, NCAVIT
        CNXYU(IPW+I) = W0
        CNXYU(IPP+I) = P0
        CNXYU(IPT+I) = T0
      ENDDO
      IPI = IPT+NCAVIT
      CNXYU(IPI+1) = P0
      CNXYU(IPI+2) = T0
      CNXYU(IPI+3) = P0
      CNXYU(IPI+4) = 300.
      CNXYU(IPI+5) = 100.
      CNXYU(IPI+6) = 100.
      IPS = IPI+6
      DO I = 1, NSPILL
        CNXYU(IPS+I) = W0
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
      SUBROUTINE CATTC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL CATT
C
C---Compressore aria TG "fisico"
C
      NSTADI = NINT(DATI(IPD))
      NSPILL = NINT(DATI(IPD + 1))
      NCAVIT = NSTADI - 1
      NSTATI = 0
      NUSCIT = NSTADI * 3
      NINGRE = 6 + NSPILL
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
  200 CALL CATT (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 EPS    = 1.E-3
      EPSLIM = 1.E-5
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,CATT)
      RETURN
      END
C
C
C
      SUBROUTINE CATT (IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
      DIMENSION CW(5), CE(4), CI(3), CS(4,5), CB(4,9)
      DIMENSION WSTA(9),PCAV(9),TCAV(9),WSPILL(9),ISPILL(7),
     $          WSTAC(9),PCAVC(9),TCAVC(9),TSTIM(9)
C
C---Compressore aria TG
C   calcolo residui
C
C---decodifica variabili e dati
C
      NSTADI = NINT (DATI(IPD  ))
      NSPILL = NINT (DATI(IPD+1))
      NCAVIT = NSTADI - 1
C
      ETANOM = DATI(IPD+2)
      OMADIM = DATI(IPD+3)
      WANORM = DATI(IPD+4)
      BETNOM = DATI(IPD+5)
      ETARID = DATI(IPD+6)
C
      IDJ = IPD + 6
      DO I = 1, 5
        IDJ = IDJ + 1
        CW(I) = DATI(IDJ)
      ENDDO
      DO I = 1, 4
        IDJ = IDJ + 1
        CE(I) = DATI(IDJ)
      ENDDO
      DO I = 1, 3
        IDJ = IDJ + 1
        CI(I) = DATI(IDJ)
      ENDDO
      DO J = 1, 5
        DO I = 1, 4
          IDJ = IDJ + 1
          CS(I,J) = DATI(IDJ)
        ENDDO
      ENDDO
      DO J = 1, NCAVIT
        DO I = 1, 4
          IDJ = IDJ + 1
          CB(I,J) = DATI(IDJ)
        ENDDO
      ENDDO
      DO J = 1, NSPILL
        IDJ = IDJ + 1
        ISPILL(J) = NINT(DATI(IDJ))
      ENDDO
C
      WMAN = XYU(IXYU  )*W0
      TMAN = XYU(IXYU+1)*T0
      QMEC = XYU(IXYU+2)*W0*H0
      IPW = IXYU+2
      IPP = IPW+NCAVIT
      IPT = IPP+NCAVIT
      DO I = 1, NCAVIT
        WSTA(I) = XYU(IPW+I)*W0
        PCAV(I) = XYU(IPP+I)*P0
        TCAV(I) = XYU(IPT+I)*T0
        WSPILL(I) = 0.
      ENDDO
      IPI = IPT+NCAVIT
      PASP = AMAX1 (XYU(IPI+1)*P0, 5000.)
      TASP = XYU(IPI+2)*T0
      PMAN = AMAX1 (XYU(IPI+3)*P0, 5000.)
      OMEG = XYU(IPI+4)*300.
      AIGV = XYU(IPI+5)
      ZSPO = XYU(IPI+6)
C
C---AIGV e ZSPO non vengono denormalizzati (sono divisi per 100.)
C
      IPS = IPI+6
      DO I = 1, NSPILL
        WPS = XYU(IPS+I)*W0
        ISP = ISPILL(I)
        WSPILL(ISP) = WSPILL(ISP) + WPS
      ENDDO
C
      CALL INITAF (3,0.,0.)
      CALL TAVOAF (PASP,TASP,RASP,HASP,SASP,3)
C
      BETA = PMAN / PASP
      ZETA = 1. - BETA / BETNOM
      X = (BETA - 1.) / (BETNOM - 1.)
      Y = (OMEG / SQRT(PASP / RASP)) / OMADIM
C
C-----Calcolo condizioni di "surge"------
C
      J = 1
      DO WHILE (Y .GT. CS(1,J) .AND. J .LT. 5)
        J = J + 1
      ENDDO
      XS = CS(2,J) * Y * Y + CS(3,J) * Y + CS(4,J)
      IF (X .GT. XS) X = XS
C
C-----Calcolo condizioni di "choke flow"----
C
      XCC = CW(4) * Y + CW(5) * Y ** 2
      XCF = X - XCC
      IF (XCF .LT. 0.) XCF = 0.
C
C-----Calcolo ETA
C
      IF (ZETA .LT. -0.25) ZETA = -0.25
      ETA = ETANOM * (CE(1) + (1. - CE(1)) / (1. + CE(2) * ZETA**2))
      ETA = ETA * (1. - ZSPO * ETARID)
      ETAI = 1. - CE(3) * (1. - ETA)
C
C---Calcolo condizioni di uscita
C
      CALL STPIAF (SASP,TUISO,PMAN,2,3)
      CALL THINAF (TUISO,HUISO,1,3)
      HMAN = HASP + (HUISO - HASP) / ETA
      CALL THINAF (TMANC,HMAN,2,3)
C
C---Calcolo calore specifico medio del fluido
C
      TMED = 0.5 * (TASP + TMANC)
      CALL R1CPAF (TMED,R1AV,CPAV,CVAV,3)
      ESP = R1AV / CPAV
C
C-----Calcolo portata aspirazione
C
      APERC = CI(1) + CI(2) * AIGV + CI(3) * AIGV ** 2
      WASP = RASP * OMEG * WANORM * (CW(1) + CW(2) * XCF**2 +
     $       CW(3) * XCF**3) * APERC
      WMIN = AMAX1 (WASP, 5.)
C
C-----Calcolo portate negli stadi e rapp. compressione
C
      IF (ZETA .LT. 0.) ZETA = 0.
      WPREC = WASP
      TPREC = TASP
      PPREC = PASP
      DO I = 1, NCAVIT
        WSTAC(I) = WPREC
        WSUCC = WPREC - WSPILL(I)
        WSTM = AMAX1 (AMIN1 (WSUCC, WMIN), 0.)
        RAPW = WSTM / WMIN
        ALFAI = CB(1,I) + CB(2,I) * ZETA - CB(3,I) *
     $          ZETA * ZETA - CB(4,I) * AIGV
        PCAVC(I) = PASP * BETA ** ALFAI
        AKISO = (PCAVC(I) / PPREC) ** ESP
        TSTIM(I) = TPREC * (1. + (AKISO - 1.) / ETAI)
        TPREC = TSTIM(I)
        PPREC = PCAVC(I)
        WPREC = WSUCC
      ENDDO
      WMANC = WPREC
      AKISO = (PMAN / PPREC) ** ESP
      TUSTI = TPREC * (1. + (AKISO - 1.) / ETAI)
      DTCORR = (TMANC - TUSTI) / FLOAT(NSTADI)
C
C-----Correzione rendimenti stimati e calcolo potenza
C
      HPREC = HASP
      WPREC = WASP
      QMECC = 0.
      DO I = 1, NCAVIT
        TCAVC(I) = TSTIM(I) + DTCORR * FLOAT(I)
        CALL THINAF (TCAVC(I),HCAVI,1,3)
        QMECC = QMECC + WPREC * (HCAVI - HPREC)
        WPREC = WSTAC(I)
        HPREC = HCAVI
      ENDDO
      QMECC = QMECC + WPREC * (HMAN - HPREC)
      QMECC = QMECC * CE(4)
C
C---assegnazione residui
C
      IPW = 3
      IPP = IPW+NCAVIT
      IPT = IPP+NCAVIT
C
      RNI(1) = (WMAN - WMANC) / W0
      RNI(2) = (TMAN - TMANC) / T0
      RNI(3) = (QMEC - QMECC) / (W0*H0)
      DO I = 1, NCAVIT
        RNI(IPW+I) = (WSTA(I) - WSTAC(I)) / W0
        RNI(IPP+I) = (PCAV(I) - PCAVC(I)) / P0
        RNI(IPT+I) = (TCAV(I) - TCAVC(I)) / T0
      ENDDO
      RETURN
      END
C
C
C
      SUBROUTINE CATTDT (ITIPO, IER, NSTADI, CW, CE, CI, CS, CB)
C
      DIMENSION CW(5), CE(4), CI(3), CS(4,5), CB(4,9)
C
      PARAMETER (NTIP = 4)
      PARAMETER (NSTA1 = 4, NSTA2 = 4, NSTA3 = 4, NSTA4 = 4)
      DIMENSION NSTA(NTIP)
      CHARACTER *30 DESC(NTIP)
C
      DIMENSION XCW(5,NTIP), XCE(4,NTIP), XCI(3,NTIP),
     $          XCS(4,5,NTIP), XCB(4,9,NTIP)
C
      DATA NSTA / NSTA1, NSTA2, NSTA3, NSTA4 /
      DATA DESC / 'FIAT TG50D', 'Siemens V94.3', 'Siemens V94.2',
     $            'FIAT TG701F' /
C
C---Compressor data
C
      DATA XCW /
     $    1.000, -0.405,  0.000, -5.000, 6.1111,
     $    1.000, -0.405,  0.000, -5.000, 6.1111,
     $    1.000, -0.405,  0.000, -5.000, 6.1111,
     $    1.000, -0.405,  0.000, -5.000, 6.1111 /
C
      DATA XCE /
     $    0.5302, 0.7409, 0.798, 1.000,
     $    0.5302, 0.7409, 0.798, 0.984,
     $    0.5302, 0.7409, 0.798, 0.985,
     $    0.5302, 0.7409, 0.798, 0.985 /
C
      DATA XCI /
     $    1.0000, -1.3435,  1.4578,
     $    1.0000, -0.6361, -2.3125,
     $    1.0000, -0.6361, -2.3125,
     $    1.0000, -0.7218, -4.9962 /
C
      DATA XCS /
     $    0.0,  0.0000,  0.0000,  0.1000,
     $    0.5,  0.0000,  0.1000,  0.1000,
     $    0.9,  4.9625, -4.8625,1.340625,
     $    1.0, -14.100,  29.450, -14.100,
     $    2.0,  0.0000,  1.2500,  0.0000,
C
     $    0.0,  0.0000,  0.0000,  0.1000,
     $    0.5,  0.0000,  0.1000,  0.1000,
     $    0.9,  4.9625, -4.8625,1.340625,
     $    1.0, -14.100,  29.450, -14.100,
     $    2.0,  0.0000,  1.2500,  0.0000,
C
     $    0.0,  0.0000,  0.0000,  0.1000,
     $    0.5,  0.0000,  0.1000,  0.1000,
     $    0.9,  4.9625, -4.8625,1.340625,
     $    1.0, -14.100,  29.450, -14.100,
     $    2.0,  0.0000,  1.2500,  0.0000,
C
     $    0.0,  0.0000,  0.0000,  0.1000,
     $    0.5,  0.0000,  0.1000,  0.1000,
     $    0.9,  4.9625, -4.8625,1.340625,
     $    1.0, -14.100,  29.450, -14.100,
     $    2.0,  0.0000,  1.2500,  0.0000 /
C
      DATA ((XCB(J,I,1), J = 1, 4), I = 1, NSTA1-1) /
     $    0.4453,  0.1547,  0.0000,  0.4657,
     $    0.7462,  0.1238,  0.0000,  0.2903,
     $    0.8927,  0.0773,  0.0000,  0.1270 /
C
      DATA ((XCB(J,I,2), J = 1, 4), I = 1, NSTA2-1) /
     $    0.4436,  0.1547,  0.0000,  0.8849,
     $    0.7432,  0.1238,  0.0000,  0.5516,
     $    0.8903,  0.0773,  0.0000,  0.2413 /
C
      DATA ((XCB(J,I,3), J = 1, 4), I = 1, NSTA3-1) /
     $    0.4436,  0.1547,  0.0000,  0.8849,
     $    0.7432,  0.1238,  0.0000,  0.5516,
     $    0.8903,  0.0773,  0.0000,  0.2413 /
C
      DATA ((XCB(J,I,4), J = 1, 4), I = 1, NSTA4-1) /
     $    0.4306,  0.4918,  0.1685,  0.3415,
     $    0.7434,  0.2556,  0.0997,  0.2149,
     $    0.8878,  0.1439,  0.0523,  0.0931 /
C
      IF (NSTADI .NE. NSTA(ITIPO)) THEN
        WRITE (6,1) ITIPO, DESC(ITIPO), NSTA(ITIPO), NSTADI
    1   FORMAT (5X,'********* MODULE CATT ********',/,
     $    5X,'***ERROR: FOR TG TYPE =',I3,' --> ',A,/,
     $    5X,'   THE NUMBER OF STAGES MUST BE',I2,
     $       ' (ACTUAL NUMBER IS',I2,')')
        IER = 1
        RETURN
      ENDIF
      NCAVIT = NSTADI - 1
C
      DO I = 1, 5
        CW(I) = XCW(I,ITIPO)
      ENDDO
      DO I = 1, 4
        CE(I) = XCE(I,ITIPO)
      ENDDO
      DO I = 1, 3
        CI(I) = XCI(I,ITIPO)
      ENDDO
      DO J = 1, 5
        DO I = 1, 4
          CS(I,J) = XCS(I,J,ITIPO)
        ENDDO
      ENDDO
      DO J = 1, NCAVIT
        DO I = 1, 4
          CB(I,J) = XCB(I,J,ITIPO)
        ENDDO
      ENDDO
C
      WRITE (6,*) 'CATT - DATA ASSIGNED FOR TG TYPE: ', DESC(ITIPO)
C
      RETURN
      END
C
C
C
      SUBROUTINE CATTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $  XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
C
C
C
      SUBROUTINE CATTDU (ITIPO, IER, NSTADI, CW, CE, CI, CS, CB)
C
      DIMENSION CW(5), CE(4), CI(3), CS(4,5), CB(4,9)
C
      WRITE (6,1) ITIPO
    1 FORMAT (5X,'********* MODULE CATT - SUBROUTINE',
     $        ' CATTDU (USER COMPRESSOR DATA) ********',/,
     $        5X,'***ERROR: TG TYPE',I5,' IS UNKNOWN')
      IER = 1
      RETURN
      END
C
C~FORAUS_CATT~
CC
C---SUBROUTINE CATTDU:
C   used to assign data for the compressor of an user-defined TG
C   Note: IER is the CATTI2 parameter IER (set to 1 to abort LG3)
CC
C      SUBROUTINE CATTDU (ITIPO, IER, NSTADI, CW, CE, CI, CS, CB)
CC
C      DIMENSION CW(5), CE(4), CI(3), CS(4,5), CB(4,9)
CC
C      WRITE (6,1) ITIPO
C    1 FORMAT (5X,'********* MODULE CATT - SUBROUTINE',
C     $        ' CATTDU (USER COMPRESSOR DATA) ********',/,
C     $        5X,'***ERROR: TG TYPE',I5,' IS UNKNOWN')
C      IER = 1
C      RETURN
C      END
CC
C~FORAUS_CATT~
