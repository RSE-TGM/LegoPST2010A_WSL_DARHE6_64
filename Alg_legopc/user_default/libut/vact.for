C**********************************************************************
C modulo vact.f
C tipo 
C release 5.1
C data 6/21/95
C reserver @(#)vact.f	5.1
C**********************************************************************
      SUBROUTINE VACTI3 (IFO,IOB,DEBL)
      PARAMETER (N0=3, N1=5, N2=5, N3=8, NV=N0+N1+N2+N3)
C
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
      DIMENSION NUVAR(4)
C
      DATA MOD /'VACT'/
      DATA NUVAR /N0, N1, N2, N3/
C
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,N0+N1+N2) /
     $ 'AEQV','UA','LIFT OF EQUIVALENT VALVE',
     $ 'AMLV','UA','MEASURE OF VALVE LIFT',
     $ 'ALZV','IN','LIFT OF THE VALVE',
C
     $ 'AEQV','UA','LIFT OF EQUIVALENT VALVE',
     $ 'AMLA','UA','MEASURE OF FIRST VALVE LIFT',
     $ 'AMLB','UA','MEASURE OF SECOND VALVE LIFT',
     $ 'ALZA','IN','LIFT OF FIRST VALVE',
     $ 'ALZB','IN','LIFT OF SECOND VALVE',
C
     $ 'AEQV','UA','LIFT OF EQUIVALENT VALVE',
     $ 'AMLA','UA','MEASURE OF BRANCH A VALVE LIFT',
     $ 'AMLB','UA','MEASURE OF BRANCH B VALVE LIFT',
     $ 'ALZA','IN','LIFT OF BRANCH A VALVE',
     $ 'ALZB','IN','LIFT OF BRANCH B VALVE'/
C
      DATA (NOMI(I), TIPI(I), DESC(I), I=1+N0+N1+N2,NV) /
     $ 'AEQA','UA','LIFT OF BRANCH A EQUIVALENT VALVE',
     $ 'AEQB','UA','LIFT OF BRANCH B EQUIVALENT VALVE',
     $ 'AML3','UA','MEASURE OF THREE WAY VALVE LIFT',
     $ 'AMLA','UA','MEASURE OF BRANCH A VALVE LIFT',
     $ 'AMLB','UA','MEASURE OF BRANCH B VALVE LIFT',
     $ 'ALZ3','IN','LIFT OF THREE WAY VALVE',
     $ 'ALZA','IN','LIFT OF BRANCH A VALVE',
     $ 'ALZB','IN','LIFT OF BRANCH B VALVE'/
C
      CALL VACTI4 (IOB,MOD,IBLOC,NC)
      I2 = 0
      DO I = 1, NC+1
        I1 = I2+1
        I2 = I2+NUVAR(I)
      ENDDO
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = I1,I2)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE VACTI4 (IOB,MOD,IBLOC,NC)
      CHARACTER*4 IOB, MOD, IBLOC*8, ICA*1
C
    1 WRITE(6,2)
      READ(5,3,ERR=1)ICA
      NC = ICHAR(ICA) - 48
      IF (NC .LT. 0 .OR. NC .GT. 3) GOTO 1
C
      IBLOC = MOD(1:3) // ICA // IOB
C
      RETURN
    2 FORMAT (/5X,'SELECT THE VALVE ARRANGEMENT:',
     $        /5X,'   0 = ONLY ONE VALVE',
     $        /5X,'   1 = TWO VALVES (SERIAL ARR.)',
     $        /5X,'   2 = TWO VALVES (PARALLEL ARR.)',
     $        /5X,'   3 = THREE WAY VALVE')
    3 FORMAT (A)
      END
C
C
C
      SUBROUTINE VACTI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C
      DIMENSION VAR(MX1,2), XYU(*),DATI(*),CNXYU(*),TOL(*)
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      CHARACTER *4 BLOCCO
C
      IF (IFUN .EQ. 1) RETURN
C
      READ(14,*)
      WRITE (BLOCCO, '(A4)') IBL1
      READ (BLOCCO, '(3X,I1)') NC
      DATI (ID2) =  NC
C
      DO I = IV1, IV2
        CNXYU(I) = 1.
      ENDDO
C
      RETURN
      END
C
C
C
      SUBROUTINE VACTC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
      COMMON/NEQUAZ/NEQMOD
C
C---Lift of equivalent valves (serial, parall., 3-way)
C
      NC = DATI (IPD)
      IF (.NOT. KREGIM) THEN
        NEQMOD = 1
        IF (NC .EQ. 3) NEQMOD = 2
      ENDIF
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 IF (NC .EQ. 0) THEN
        AJAC(1,1) = 1.
        AJAC(1,3) = 1.
      ELSE IF (NC .EQ. 1 .OR. NC .EQ. 2) THEN
        AJAC(1,1) = 1.
        AJAC(1,4) = 1.
        AJAC(1,5) = 1.
      ELSE
        AJAC(1,1) = 1.
        AJAC(1,6) = 1.
        AJAC(1,7) = 1.
        AJAC(2,2) = 1.
        AJAC(2,6) = 1.
        AJAC(2,8) = 1.
      ENDIF
      RETURN
C
C---calcolo residui
C
  200 IF (NC .EQ. 0) THEN
        AEQV = XYU(IXYU  )
        AMLV = XYU(IXYU+1)
        ALZV = XYU(IXYU+2)
        RNI(1) = AEQV - ALZV
        IF (KREGIM) THEN
          RNI(2) = AMLV - ALZV
        ELSE
          RNI(2) = ALZV
        ENDIF
      ELSE IF (NC .EQ. 1 .OR. NC .EQ. 2) THEN
        AEQV = XYU(IXYU  )
        AMLA = XYU(IXYU+1)
        AMLB = XYU(IXYU+2)
        ALZA = XYU(IXYU+3)
        ALZB = XYU(IXYU+4)
        IF (NC .EQ. 1) THEN
          RNI(1) = AEQV - ALZA * ALZB
        ELSE
          RNI(1) = AEQV - 0.5 * (ALZA + ALZB)
        ENDIF
        IF (KREGIM) THEN
          RNI(2) = AMLA - ALZA
          RNI(3) = AMLB - ALZB
        ELSE
          RNI(2) = ALZA
          RNI(3) = ALZB
        ENDIF
      ELSE
        AEQA = XYU(IXYU  )
        AEQB = XYU(IXYU+1)
        AML3 = XYU(IXYU+2)
        AMLA = XYU(IXYU+3)
        AMLB = XYU(IXYU+4)
        ALZ3 = XYU(IXYU+5)
        ALZA = XYU(IXYU+6)
        ALZB = XYU(IXYU+7)
        RNI(1) = AEQA - ALZA * ALZ3
        RNI(2) = AEQB - ALZB * (1.-ALZ3)
        IF (KREGIM) THEN
          RNI(3) = AML3 - ALZ3
          RNI(4) = AMLA - ALZA
          RNI(5) = AMLB - ALZB
        ELSE
          RNI(3) = ALZ3
          RNI(4) = ALZA
          RNI(5) = ALZB
        ENDIF
      ENDIF
      RETURN
C
C---calcolo jacobiano
C
  300 IF (NC .EQ. 0) THEN
        AJAC(1,1) = -1.
        AJAC(1,3) = 1.
      ELSE IF (NC .EQ. 1) THEN
        ALZA = XYU(IXYU+3)
        ALZB = XYU(IXYU+4)
        AJAC(1,1) = -1.
        AJAC(1,4) = ALZB
        AJAC(1,5) = ALZA
      ELSE IF (NC .EQ. 2) THEN
        AJAC(1,1) = -1.
        AJAC(1,4) = 0.5
        AJAC(1,5) = 0.5
      ELSE
        ALZ3 = XYU(IXYU+5)
        ALZA = XYU(IXYU+6)
        ALZB = XYU(IXYU+7)
        AJAC(1,1) = -1.
        AJAC(1,6) = ALZA
        AJAC(1,7) = ALZ3
        AJAC(2,2) = -1.
        AJAC(2,6) = -ALZB
        AJAC(2,8) = 1.-ALZ3
      ENDIF
      IF (.NOT. KREGIM) RETURN
C
      IF (NC .EQ. 0) THEN
        AJAC(2,2) = -1.
        AJAC(2,3) = 1.
      ELSE IF (NC .EQ. 1 .OR. NC .EQ. 2) THEN
        AJAC(2,2) = -1.
        AJAC(2,4) = 1.
        AJAC(3,3) = -1.
        AJAC(3,5) = 1.
      ELSE
        AJAC(3,3) = -1.
        AJAC(3,6) = 1.
        AJAC(4,4) = -1.
        AJAC(4,7) = 1.
        AJAC(5,5) = -1.
        AJAC(5,8) = 1.
      ENDIF
      RETURN
C
      END
C
C
C
      SUBROUTINE VACTD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
