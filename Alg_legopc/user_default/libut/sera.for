C**********************************************************************
C modulo sera.f
C tipo 
C release 5.4
C data 8/29/95
C reserver @(#)sera.f	5.4
C**********************************************************************
      SUBROUTINE SERAI3(IFO,IOB,DEBL)
C
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'SERA'/
C
      CALL SERAI4 (IOB, MOD, IBLOC, NE, NU)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)
     $  'PSER',IOB,'US','AIR/GAS PRESSURE IN THE RESERVOIR',
     $  'TMET',IOB,'US','TEMPERATURE OF THE RESERVOIR METAL WALL',
     $  'TSER',IOB,'US','AIR/GAS TEMPERATURE IN THE RESERVOIR'
      WRITE(IFO,3001)
     $  ('WI', I, IOB, 'FLOW RATE THROUGH IN', I, ' ',
     $  'TI', I, IOB, 'TEMPERATURE IN IN', I, ' ', I = 1, NE),
     $  ('WU', I, IOB, 'FLOW RATE THROUGH OUT', I, ' ', 'TU', I,
     $  IOB, 'TEMPERATURE IN OUT', I, ' (INV. FLOW)', I = 1, NU)
      WRITE(IFO,3000)
     $  'TEST',IOB,'IN','EXTERNAL TEMPERATURE (AMBIENT)',
     $  'XCSE',IOB,'IN','THERMAL EXTERNAL EXCHANGING COEFF.'
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
 3001 FORMAT(A2,I2,A4,'  --IN-- AIR/GAS ',A, 'LET PIPE N.', I3, A)
      END
C
C
C
      SUBROUTINE SERAI4 (IOB, MOD, IBLOC, NE, NU)
      CHARACTER*4 MOD, IOB, IBLOC*8
C
      MAX = 40
C
    1 WRITE (6,2) MAX
    2 FORMAT (/5X,'*** AIR/GAS MANIFOLD (OR RESERVOIR) ***',
     $        /5X,'ASSIGN NUMBER OF INLET PIPES (01 -',I3,'):')
      READ (5, * ,ERR=1) NE
      IF (NE .LE. 0 .OR. NE .GE. MAX) GOTO 1
C
      MAX = MAX - NE
C
    3 WRITE (6,4) MAX
    4 FORMAT (/5X,'ASSIGN NUMBER OF OUTLET PIPES (01 -',I3,'):')
      READ (5, *, ERR=3) NU
      IF (NU .LE. 0 .OR. NU .GT. MAX) GOTO 3
C
      IBLOC = MOD // IOB
      RETURN
      END
C
C
C
      SUBROUTINE SERAI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                  IBL1,IBL2,IER,CNXYU,TOL)
C
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)
      PARAMETER (PI = 3.141592654, MAX=40)
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
C---SERBATOIO ARIA NON ADIABATICO
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500)'N.TU.EN ','N.TU.US ','VolSer  ',
     $             'DiamInt ','Spess   ','DensMet ',
     $             'CalSpMet','CoefScIn','IGAS    '
       RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) FNE,FNU,VOL,DINT,SPES,ROMET,CMET,XCSI,FIGAS
C
C---verifica del numero totale di tubi
C
      NE = NINT(FNE)
      NU = NINT(FNU)
      NT = NE + NU
      NI = (NINGRE - 2) / 2
      IF (NT .NE. NI) THEN
        WRITE (6,1) IBL1, IBL2, NI, NT, NE, NU
    1   FORMAT (/5X,'******** MODULE SERA - BLOCK ', 2A4, ' ********',
     $          /5X, 'THE TOTAL NUMBER OF PIPES MUST BE EQUAL TO ',I2,
     $          /5X, 'IN FILE F14.DAT HAS BEEN ASSIGNED ',I2, ' PIPES',
     $          /5X, '(', I2, ' AS INLET AND ', I2, ' AS OUTLET)'/)
        IER = 1
        RETURN
      ENDIF
C
C---per default si assume il gas aria
C
      IGAS = NINT(FIGAS)
      IF (IGAS .LE. 0) IGAS = 1
      ALTZ = VOL / (PI * DINT**2 / 4.)
      AMMAS = (ALTZ*PI*DINT + PI*DINT**2 / 2.) * SPES*ROMET
      XAINT = ALTZ*PI*DINT + PI*DINT**2 / 2.
      XAEST = ALTZ*PI*(DINT + 2.*SPES) + 2.*PI*(SPES + DINT)**2 / 4.
      IF (XCSI .EQ. 0.) XCSI = 300.
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = VOL
      DATI(ID2+ 1) = DINT
      DATI(ID2+ 2) = SPES
      DATI(ID2+ 3) = ROMET
      DATI(ID2+ 4) = CMET
      DATI(ID2+ 5) = XCSI
      DATI(ID2+ 6) = AMMAS
      DATI(ID2+ 7) = XAINT
      DATI(ID2+ 8) = XAEST
      DATI(ID2+ 9) = NE
      DATI(ID2+10) = NU
      DATI(ID2+11) = IGAS
      ID2 = ID2+11
C
C---costanti di normalizzazione
C
      CNXYU(IV1  ) = P0
      CNXYU(IV1+1) = T0
      CNXYU(IV1+2) = T0
      I0 = IV1 + 2
      DO J = 1, NT
        JW = 2 * J - 1
        JT = JW + 1
        CNXYU(I0+JW) = W0
        CNXYU(I0+JT) = T0
      ENDDO
      I0 = I0 + 2 * NT
      CNXYU(I0+1) = T0
      CNXYU(I0+2) = 10000.
C
      RETURN
      END
C
C
C
      SUBROUTINE SERAC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      PARAMETER (MAX = 40)
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      DIMENSION WI(MAX),WU(MAX),TI(MAX),TU(MAX)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL SERA
C
C---SERBATOIO ARIA NON ADIABATICO
C
      NE = DATI(IPD+9)
      NU = DATI(IPD+10)
      NVAR = 2*(NE+NU) + 5
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 DO I = 1,3
        DO J = 1, NVAR
          AJAC(I,J) = 1.
        ENDDO
      ENDDO
      RETURN
C
C---calcolo residui
C
  200 CALL SERA(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 NSTATI = 3
      NUSCIT = 0
      NINGRE = 2 * (NE + NU) + 2
      EPS    = 1.E-3
      EPSLIM = 1.E-5
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,SERA)
      RETURN
C
      END
C
C
C
      SUBROUTINE SERA(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      DIMENSION XYU(*),DATI(*),RNI(*)
      PARAMETER (MAX=40)
      DIMENSION WI(MAX),WU(MAX),TI(MAX),TU(MAX)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C---SERBATOIO ARIA NON ADIABATICO
C
C---decodifica dati e variabili
C
      VOL   = DATI(IPD   )
      DINT  = DATI(IPD+ 1)
      SPES  = DATI(IPD+ 2)
      ROMET = DATI(IPD+ 3)
      CMET  = DATI(IPD+ 4)
      XCSI  = DATI(IPD+ 5)
      AMMAS = DATI(IPD+ 6)
      XAINT = DATI(IPD+ 7)
      XAEST = DATI(IPD+ 8)
      NE    = DATI(IPD+ 9)
      NU    = DATI(IPD+10)
      IGAS  = DATI(IPD+11)
C
      PSER = XYU(IXYU  ) * P0
      TMET = XYU(IXYU+1) * T0
      TSER = XYU(IXYU+2) * T0
C
      I0 = IXYU + 2
      DO J = 1, NE
        JW = 2 * J - 1
        JT = JW + 1
        WI(J) = XYU(I0+JW) * W0
        TI(J) = XYU(I0+JT)*  T0
      ENDDO
      I0 = I0 + 2 * NE
      DO J = 1, NU
        JW = 2 * J - 1
        JT = JW + 1
        WU(J) = XYU(I0+JW) * W0
        TU(J) = XYU(I0+JT) * T0
      ENDDO
C
      I0 = IXYU + 2 * (NE+NU) + 3
      TEST = XYU(I0  ) * T0
      XCSE = XYU(I0+1) * 10000.
C
      CALL R1CPGP (R1,CP,CV,IGAS)
      RSER = PSER / (R1*TSER)
      DRSDP = RSER/PSER
      DRSDT = -RSER/TSER
C
C---flussi di massa ed energia
C
      SUMI = 0.
      SUMHI = 0.
      SUMU = 0.
      DO J = 1, NE
        IF (WI(J) .GE. 0.) THEN
          SUMI = SUMI + WI(J)
          SUMHI = SUMHI + WI(J) * TI(J)
        ELSE
          SUMU = SUMU + WI(J)
        ENDIF
      ENDDO
      DO J = 1, NU
        IF (WU(J) .LT. 0.) THEN
          SUMI = SUMI - WU(J)
          SUMHI = SUMHI - WU(J) * TU(J)
        ELSE
          SUMU = SUMU - WU(J)
        ENDIF
      ENDDO
      SUMHI = SUMHI * CP
C
      QINT = XCSI * XAINT * (TSER - TMET)
      QEST = XCSE * XAEST * (TMET - TEST)
C
      IF (KREGIM) THEN
        RNI(1) = (SUMI + SUMU) / W0
        RNI(2) = ((XCSI * XAINT * TSER + XCSE * XAEST * TEST) /
     $            (XCSI * XAINT + XCSE * XAEST) - TMET) / T0
        RNI(3) = ((SUMHI + XCSI * XAINT * TMET) /
     $            (SUMI * CP + XCSI * XAINT) - TSER) / T0
      ELSE
        C11 = DRSDT
        C12 = DRSDP
        C21 = RSER * CP
        C22 = -1.
C
        TN1 = (SUMI + SUMU) / VOL
        TN2 = (SUMHI + SUMU * CP * TSER - QINT) / VOL
C
        DET = C11 * C22 - C12 * C21
C
        DTSDT = (TN1 * C22 - C12 * TN2) / DET
        DPSDT = (C11 * TN2 - TN1 * C21) / DET
        DTMDT = (QINT - QEST) / (AMMAS * CMET)
C
        RNI(1) = DPSDT / P0
        RNI(2) = DTMDT / T0
        RNI(3) = DTSDT / T0
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE SERAD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 IBLOC, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
C
      NE = DATI(IPD+9)
      NU = DATI(IPD+10)
      NVAR= NSTATI + NUSCIT + NINGRE
C      
C-----Equazione n. 1 (Algebrica):
C

      SIGNEQ(1) = 'eq. of fluid mass conservation'
      UNITEQ(1) = '[kg/s]'
      COSNOR(1) = W0
      DO I=1,NE
       J = 2 + 2*I
       ITOPVA(1,J) = 1
      ENDDO 
      DO I=1,NU
       IZ = 2 * (NE+2) + 2*I - 1
       ITOPVA(1,IZ) = 1
      ENDDO
C
C-----Equazione n.2 (Algebrica)
C
      SIGNEQ(2) = 'eq. of energy conservation in the wall'
      UNITEQ(2)          = '[K]'
      COSNOR(2)          = T0
      ITOPVA(2,2)        = 1
      ITOPVA(2,3)        = 1
      ITOPVA(2,NVAR - 1) = 1
      ITOPVA(2,NVAR )    = 1
C      
C-----Equazione n.3 (Algebrica)
C
      SIGNEQ(3) = 'eq. of energy conservation in the fluid'
      UNITEQ(3) = '[K]'
      COSNOR(3) = T0
      DO I=2 , NVAR-2
       ITOPVA(3,I) = 1
      ENDDO
      RETURN
      END
