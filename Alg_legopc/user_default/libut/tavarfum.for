C******************************************************************************
C modulo tavarfum.f
C tipo 
C release 4.2
C data 2/9/95
C reserver @(#)tavarfum.f	4.2
C******************************************************************************
C*                                                          *
C*       T A V A R F U M   ( tavole aria e fumi )           *
C*                                                          *
C************************************************************
C
      SUBROUTINE INITAF (IFLU, XHCOMB, RRCOMB)
      PARAMETER (T0=273.15, P0=101325., CUGP=8314.)
      DIMENSION A(5),B(5),C(5),G(5),U(5),Z(5)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
C
      DATA A / 3.283,  3.094,  3.652,  3.127,  1.641/
      DATA B / 0.629,  1.561,  1.157,  5.232, -0.177/
      DATA C /-0.001, -0.465,  0.142, -1.784,  0.109/
      DATA Z /74.535, 22.837, 1.303, 0.049, 1.275/
      DATA G /28.014, 31.998, 18.015, 44.009, 39.948/
      DATA GH, GC /1.008, 12.011/
C
C...Nota: i valori di Z assegnati definiscono la composizione
C         MASSICA dell'aria media (umid.rel. 65% a 18^C).
C         I gas considerati sono: N2, O2, H20, CO2 ed Ar
C         Il vettore G contiene le loro masse molecolari. 
C         GH e GC sono le masse atomiche di H e C.
C         A, B e C forniscono il Cp dei gas in funzione di T
C
      TMIN = 250.
      TMAX = 2500.
C
      IF (IFLU .EQ. 1) THEN
        DO 1 I = 1, 5
    1     U(I) = Z(I) / 100. 
        IOK(1) = 1.
      ELSE IF (IFLU .EQ. 2) THEN
        X = XHCOMB
        IF (X .LT. 0.) X = 0.
        IF (X .GT. 4.) X = 4.
        GX = GC + X * GH 
        Y = 100. * RRCOMB
        YMOLT = (1. + 0.25 * X) * G(2) / GX
        YSTECH = Z(2) / YMOLT
        IF (Y .LT. 0.) Y = 0.
        IF (Y .GT. YSTECH) Y = YSTECH
        UDIV = 1. / (100. + Y)
        U(1) = UDIV *  Z(1)
        U(2) = UDIV * (Z(2) - Y * YMOLT)
        U(3) = UDIV * (Z(3) + G(3) * 0.5 * X * Y / GX)
        U(4) = UDIV * (Z(4) + G(4) * Y / GX) 
        U(5) = UDIV *  Z(5)
        IOK(2) = 1.
      ELSE
        PRINT *, 'Tipo di gas richiesto = ', IFLU
        STOP 'Errore (dovrebbe essere 1 o 2)'
      ENDIF
C
      GEQ(IFLU) = 0.
      AEQ(IFLU) = 0.
      BEQ(IFLU) = 0.
      CEQ(IFLU) = 0.
      DO 2 I = 1, 5
        GEQ(IFLU) = GEQ(IFLU) + U(I) / G(I)
        AEQ(IFLU) = AEQ(IFLU) + U(I) / G(I) * A(I)
        BEQ(IFLU) = BEQ(IFLU) + U(I) / G(I) * B(I)
        CEQ(IFLU) = CEQ(IFLU) + U(I) / G(I) * C(I)
    2 CONTINUE
C
      REQ(IFLU) = CUGP * GEQ(IFLU)
      GEQ(IFLU) = 1. / GEQ(IFLU)
      AEQ(IFLU) = AEQ(IFLU) * CUGP
      BEQ(IFLU) = BEQ(IFLU) * CUGP * 1.E-3
      CEQ(IFLU) = CEQ(IFLU) * CUGP * 1.E-6
C
C  CUGP = Costante Universale dei Gas Perfetti (8314. J/kmolK)
C
      CPMAX(IFLU)= CASPAF(TMAX,IFLU)
      CPMIN(IFLU)= CASPAF(TMIN,IFLU)
      HMIN(IFLU) = AEQ(IFLU)*(TMIN - T0)+ 0.5 * BEQ(IFLU)
     $   * (TMIN**2 - T0**2) + CEQ(IFLU)*(TMIN**3 - T0**3)/3.
      HMAX(IFLU) = AEQ(IFLU)*(TMAX - T0)+ 0.5 * BEQ(IFLU)
     $   * (TMAX**2 - T0**2) + CEQ(IFLU)*(TMAX**3 - T0**3)/3.
      SMIN(IFLU) = AEQ(IFLU)*LOG(TMIN/T0)+BEQ(IFLU)*(TMIN-T0)+
     $   0.5*CEQ(IFLU)*(TMIN**2 - T0**2)
      SMAX(IFLU) = AEQ(IFLU)*LOG(TMAX/T0)+BEQ(IFLU)*(TMAX-T0)+
     $   0.5*CEQ(IFLU)*(TMAX**2 - T0**2)
      CPMIN(IFLU)= AEQ(IFLU)+BEQ(IFLU)*TMIN+CEQ(IFLU)*TMIN**2 
      CPMAX(IFLU)= AEQ(IFLU)+BEQ(IFLU)*TMAX+CEQ(IFLU)*TMAX**2 
      RETURN
      END
C
C
C
      FUNCTION CASPAF (T,IFLU)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      IF (T .LE. TMIN) THEN
        CASPAF = AEQ(IFLU) + BEQ(IFLU) * TMIN + CEQ(IFLU) * TMIN**2
      ELSE IF (T .GE. TMAX) THEN
        CASPAF = AEQ(IFLU) + BEQ(IFLU) * TMAX + CEQ(IFLU) * TMAX**2
      ELSE
        CASPAF = AEQ(IFLU) + BEQ(IFLU) * T    + CEQ(IFLU) * T**2
      END IF
      RETURN
      END
C
C
C
      FUNCTION ERREAF (IFLU)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      ERREAF = REQ(IFLU)
      RETURN
      END
C
C
C
      SUBROUTINE THINAF (T,H,INDEX,IFLU)
      PARAMETER (T0 = 273.15, EPS = 0.5, NITMAX = 10)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      CALL CHCKAF (5, 0., IFLU)
C
      IF (INDEX .EQ. 1) THEN
        CALL CHCKAF (2, T, IFLU)
        IF (T .LT. TMIN) THEN
          H = (T - TMIN) * CPMIN(IFLU) + HMIN(IFLU)
        ELSE IF (T .GT. TMAX) THEN
          H = (T - TMAX) * CPMAX(IFLU) + HMAX(IFLU)
        ELSE
          H = AEQ(IFLU) * (T - T0) + 0.5 * BEQ(IFLU) *
     $        (T**2 - T0**2) + CEQ(IFLU) * (T**3 - T0**3) / 3.
        END IF
C
      ELSE IF (INDEX .EQ. 2) THEN
        CALL CHCKAF (4, H, IFLU)
        IF (H .LT. HMIN(IFLU)) THEN
          T = (H - HMIN(IFLU)) / CPMIN(IFLU) + TMIN
        ELSE IF (H .GT. HMAX(IFLU)) THEN
          T = (H - HMAX(IFLU)) / CPMAX(IFLU) + TMAX
        ELSE
C------ Metodo delle tangenti -------
          IF (BEQ(IFLU) .EQ. 0.) THEN
            T = H / AEQ(IFLU) + T0
          ELSE
            T = (SQRT (AEQ(IFLU)**2 + BEQ(IFLU) * (2. *
     $          (H + AEQ(IFLU) * T0) + BEQ(IFLU) * T0**2)) -
     $           AEQ(IFLU)) / BEQ(IFLU)
          ENDIF
          HH = AEQ(IFLU) * (T - T0) + 0.5 * BEQ(IFLU) *
     $         (T**2 - T0**2) + CEQ(IFLU) * (T**3 - T0**3) / 3.
          DO 2 I = 1, NITMAX
            T  = T - (HH - H) / (AEQ(IFLU) + 2. * BEQ(IFLU) * T
     $                                     + 3. * CEQ(IFLU) * T**2)
            HH = AEQ(IFLU) * (T - T0) + 0.5 * BEQ(IFLU) * (T**2 -
     $           T0**2) + CEQ(IFLU) / 3. * (T**3 - T0**3)
            IF (ABS(H-HH) .LT. EPS) GOTO 1
    2     CONTINUE
          CALL CHCKAF (6, 1., IFLU)
    1     CONTINUE
        END IF
      ELSE
        PRINT '(A,I3)',' Opzione non riconosciuta:',INDEX
        STOP 'Errore in THINAF'
      ENDIF
      RETURN
      END
C
C
C
      SUBROUTINE RTPIAF (RO,T,P,INDEX,IFLU)
      CALL CHCKAF(5, 0.,IFLU)
      R1 = ERREAF(IFLU)
      IF (INDEX .EQ. 1) THEN
        CALL CHCKAF (2, T, IFLU)
        CALL CHCKAF (3, RO, IFLU)
        P = RO * T * R1
      ELSE IF (INDEX .EQ. 2) THEN
        CALL CHCKAF (1, P, IFLU)
        CALL CHCKAF (3, RO, IFLU)
        T = P / (RO * R1)
      ELSE
        PRINT '(A,I3)',' Opzione non riconosciuta:',INDEX
        STOP 'Errore in RTPIAF'
      ENDIF
      RETURN
      END
C
C
C
      SUBROUTINE STPIAF (S,T,P,INDEX,IFLU)
      PARAMETER (T0 = 273.15, P0 = 101325., EPS = 0.001, NITMAX = 10)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      CALL CHCKAF(5, 0., IFLU)
C
      IF (INDEX .EQ. 1) THEN
        CALL CHCKAF (2, T, IFLU)
        IF (T .LT. TMIN) THEN
          P = P0 * EXP ((CPMIN(IFLU) * LOG(T / TMIN) - S + SMIN(IFLU)) /
     $        REQ (IFLU))
        ELSE IF (T .GT. TMAX) THEN
          P = P0 * EXP ((CPMAX(IFLU) * LOG(T / TMAX) - S + SMAX(IFLU)) /
     $        REQ (IFLU))
        ELSE
          P = P0 * EXP ((AEQ(IFLU) * LOG(T / T0) + BEQ(IFLU) *
     $        (T - T0) + 0.5 * CEQ(IFLU) * (T**2 - T0**2) - S) /
     $        REQ(IFLU))
        END IF
      ELSE IF (INDEX .EQ. 2)THEN
        CALL CHCKAF (1, P, IFLU)
        SSMIN = SMIN(IFLU) - REQ(IFLU) * LOG(P / P0)
        SSMAX = SMAX(IFLU) - REQ(IFLU) * LOG(P / P0)
        IF (S .LE. SSMIN) THEN
          T = TMIN * EXP ((REQ(IFLU) * LOG(P / P0) + S - SSMIN) /
     $        CPMIN(IFLU))
        ELSE IF (S .GE. SSMAX) THEN
          T = TMAX * EXP ((REQ(IFLU) * LOG(P / P0) + S - SSMAX) /
     $        CPMAX(IFLU))
        ELSE
C------ Metodo delle tangenti -------
          CPSTIM = 0.5 * (CPMIN(IFLU) + CPMAX(IFLU))
          T = T0 * EXP ((REQ(IFLU) * LOG(P / P0) + S) / CPSTIM)
          SS = AEQ(IFLU) * LOG(T / T0) + BEQ(IFLU) * (T - T0) +
     $         0.5 * CEQ(IFLU) * (T**2 - T0**2) -
     $         LOG(P / P0) * REQ(IFLU)
          DO 2 I = 1, NITMAX
            T  = T - (SS - S) / (AEQ(IFLU)/T + BEQ(IFLU) + CEQ(IFLU)*T)
            SS = AEQ(IFLU) * LOG(T / T0) + BEQ(IFLU) * (T - T0) +
     $           0.5 * CEQ(IFLU) * (T**2 - T0**2) -
     $           LOG(P / P0) * REQ(IFLU)
            IF (ABS(S-SS) .LT. EPS) GOTO 1
    2     CONTINUE
          CALL CHCKAF (6, 2., IFLU)
    1     CONTINUE
        END IF
      ELSE
        PRINT '(A,I3)',' Opzione non riconosciuta:',INDEX
        STOP 'Errore in STPIAF'
      ENDIF
      RETURN
      END
C
C
C
      SUBROUTINE TAVOAF (P,T,RO,H,S,IFLU)
      PARAMETER (T0 = 273.15, P0 = 101325.) 
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      CALL CHCKAF (5, 0.,IFLU)
      CALL CHCKAF (1, P, IFLU)
      CALL CHCKAF (2, T, IFLU)
C
      RO = P / (REQ(IFLU) * T)
C   
      IF (T .LE. TMIN) THEN
       H = CPMIN(IFLU) * (T - TMIN) + HMIN(IFLU)
       S = CPMIN(IFLU) * LOG (T / TMIN) - REQ(IFLU) * 
     $     LOG (P / P0) + SMIN(IFLU)
      ELSE IF (T .GE. TMAX) THEN
       H = CPMAX(IFLU) * (T - TMAX) + HMAX(IFLU)
       S = CPMAX(IFLU) * LOG (T / TMAX) - REQ(IFLU) *
     $     LOG (P / P0) + SMAX(IFLU)
      ELSE
       H = AEQ(IFLU) * (T - T0) + 0.5 * BEQ(IFLU) * (T**2 - T0**2) +
     $     CEQ(IFLU) * (T**3 - T0**3) / 3.
       S = AEQ(IFLU) * LOG(T / T0) + BEQ(IFLU) * (T - T0) +
     $     0.5 * CEQ(IFLU) * (T**2 - T0**2) - LOG(P / P0) * REQ(IFLU)
      END IF
C
      RETURN
      END
C
C
C
      SUBROUTINE R1CPAF (T,R1,CP,CV,IFLU)
      CALL CHCKAF(5, 0., IFLU)
      R1 = ERREAF(IFLU)
      CP = CASPAF(T,IFLU)
      CV = CP - R1
      RETURN 
      END
C
C
C
      SUBROUTINE DRPSAF (P,T,DRDP,DRDS,IFLU)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      CALL CHCKAF (5, 0.,IFLU)
      CALL CHCKAF (1, P, IFLU)
      CALL CHCKAF (2, T, IFLU)
      CP = CASPAF (T, IFLU)
      R1 = ERREAF (IFLU)
      DEN = CP * R1 * T
      DRDP = (CP - R1) / DEN
      DRDS = - P / DEN
      RETURN
      END
C
C
C
      SUBROUTINE DRPTAF (P,T,DRDP,DRDT,IFLU)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      CALL CHCKAF (5, 0.,IFLU)
      CALL CHCKAF (1, P, IFLU)
      CALL CHCKAF (2, T, IFLU)
      CP = CASPAF(T,IFLU)
      R1 = ERREAF(IFLU)
      DRDP = 1. / (R1 * T)
      DRDT = - P * DRDP / T
      RETURN
      END
C
C
C
      FUNCTION PVECAF (P,T,PV,IFLU)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      CALL CHCKAF (5, 0.,IFLU)
      CALL CHCKAF (1, P, IFLU)
      CALL CHCKAF (2, T, IFLU)
      CP = CASPAF(T,IFLU)
      R1 = ERREAF(IFLU)
      AK = CP / (CP - R1)
      RC = (2. / (AK + 1.)) ** (AK / (AK - 1.))
      PVECAF = MAX (PV, P * RC)
      RETURN
      END
C
C
C
      SUBROUTINE CHCKAF (INDEX,ARG,IFLU)
      COMMON/VALEAF/GEQ(2),AEQ(2),BEQ(2),CEQ(2),REQ(2),IOK(2)
      COMMON/LIMIAF/TMIN,TMAX,HMIN(2),HMAX(2),CPMIN(2),CPMAX(2),
     $   SMIN(2),SMAX(2)
      IF (INDEX .EQ. 1) THEN
        IF (ARG .LE. 0.) THEN
          PRINT 3, 'Pressione non positiva [in Pa] = ', ARG
          ARG = 500.
        ENDIF
      ELSE IF (INDEX .EQ. 2) THEN
        IF (ARG .LE. 0.) THEN
          PRINT 3, 'Temperatura non positiva [in K] = ', ARG
          ARG = 1.
        ENDIF
      ELSE IF (INDEX .EQ. 3) THEN
        IF (ARG .LE. 0.) THEN
          PRINT 3, 'Densita` non positiva [in kg/m^2] = ', ARG
          ARG = 1.E-4
        ENDIF
      ELSE IF (INDEX .EQ. 4) THEN
        H0K = - CPMIN(IFLU)  * TMIN + HMIN(IFLU)
        IF (ARG .LE. H0K) THEN
          PRINT 3, 'Entalpia non ammissibile [in J/kg] = ' , ARG
          ARG = 0.995 * H0K
        ENDIF
      ELSE IF (INDEX .EQ. 5) THEN
        IF (IFLU .NE. 1 .AND. IFLU .NE. 2)THEN
          PRINT 2, 'Tipo di gas richiesto non corretto = ', IFLU
          CALL INITAF (1,0.,0.)
        ELSE IF (IOK(IFLU) .NE. 1) THEN
          PRINT 2, 'Tavole g.p. non inizializzate per gas = ', IFLU
          CALL INITAF (IFLU,0.,0.)
        END IF
      ELSE IF (INDEX .EQ. 6) THEN
        IF (ARG .EQ. 1.)THEN
          PRINT 1, 'Convergenza non raggiunta in THINAF'
        ELSE IF (ARG .EQ. 2.)THEN
          PRINT 1, 'Convergenza non raggiunta in STPIAF'
        END IF
      ELSE
        PRINT 2, 'Opzione errata in CHCKAF = ', INDEX
      ENDIF
      RETURN
    1 FORMAT (1X, A)
    2 FORMAT (1X, A, I3)
    3 FORMAT (1X, A, G12.5)
      END
