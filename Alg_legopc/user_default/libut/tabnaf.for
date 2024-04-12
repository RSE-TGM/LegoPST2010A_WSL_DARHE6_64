         SUBROUTINE TABNAF(TIP,T,RO,VISD,COND,CASP,ENTA,DRDT)
C
C        FEB 1993
C
C   Calcolo di proprieta' delle nafte impiegate nelle centrali
C   termoelettriche, in funzione della temperatura e del tipo di
C   nafta.
C   Per i tipi da 1 a 5 al momento inseriti ci si riferisce a misure
C   ed elaborazioni di dati riassunti nel rapporto CISE 4547, con il
C   supporto del "Chemical Engineer's Handbook"
C   (R.H. Perry, C.H. Chilton).
C
C        LUG 1994
C
C   Inserimento proprieta' di un sesto fluido, l' olio lubrificante di
C   turbina; la  struttura  delle  espressioni non  e' pero' sempre la
C   stessa delle nafte.
C   Inserita anche la possibilita' di calcolo di T in funzione di H, per
C   calcolare RO (usato dalla pompa).
C
C
C
      INTEGER TIPO,TIP
      REAL RO0(6), AV(6), BV(6), C1V(6), C2V(6), ALFA(8), RO1(8)
      REAL*8 ENTI,ARG2
C
C       TIPO          1        2       3        4        5        6
C
C
      DATA  RO0 /   987. ,   978. ,   985. ,   989. ,   987. ,   880. /
C
      DATA  AV  /  2.5506,  3.2149,  4.0205,  3.2819,  4.6842,   1.69 /
C
      DATA  BV  / 240.653, 240.173, 263.394,  238.11, 214.967, 119.47 /
C
      DATA  C1V / 1.1575 ,  1.1792,  1.3475,  1.2330,  1.2412, 1.3    /
C
      DATA  C2V / 1.0019 ,  0.9989,  1.0545,  1.0614,  0.9108, 1737.61/
C
C
C
      DATA ALFA/ .063, .072, .090, .108, .126, .144, .162 ,.604 /
C
      DATA RO1 / 966.,849.9,775.4,723.9,672.4,641.9,611.2,0.  /
C
      DATA ROW/1000./
C
C
      TIPO = TIP
      ITIP=0
      IF(TIPO.LT.0) THEN
        TIPO = -TIPO
        ITIP = 1
      ENDIF
C      SELEZIONE PARAMETRI
C
      R0 = RO0(TIPO)
      A  = AV(TIPO)*1.E-06
      B  = BV(TIPO)
      C1 = C1V(TIPO)
      C2 = C2V(TIPO)
      C6 = 37.683
C
C     VALUTAZIONE DI ALFA
C
        IF (R0.GT.RO1(1)) THEN
           ALF = ALFA(1)
        ELSE
           I = 2
 10        CONTINUE
           IF (R0.GT.RO1(I)) THEN
               ALF = ALFA(I-1) + (ALFA(I) - ALFA(I-1))/
     &         (RO1(I-1)-RO1(I))*(RO1(I-1)-R0)
           ELSE
            I = I+1
            GOTO 10
           ENDIF
        ENDIF
        ALF = ALF*.001
        T0 =288.15
C
C
C------ Protezione introdotta da Pagani per limitare la temperatura T
C------ entro valori sensati (0 - 2000 K)
C
        IF (T .LT. 0.) T=0.
        IF (T .GT. 2000.) T=2000.
        THETA0=T-273.15
        THETA=T-T0
        ARG=ALF*THETA
        ARG2=.5*ARG
C
C       DENSITA'
C
C        RO   = R0 * 1./(1. + ALF * THETA)
         RO   = R0 * EXP(-ARG)
C
C        T = f(H) (SOLO PER ITIP=1)
C
        IF(ITIP.EQ.1)THEN
          Z  = C2/SQRT(R0/ROW) - C6*T0
          T  = 1/C6*(-Z + SQRT(Z**2+2.*C6*(Z*T0+C6/2*T0**2+ENTA)))
          RETURN
C                L'uso di R0 anziche' RO e' buona approssimazione
        ENDIF
C
C
C
C
C       VISCOSITA` DINAMICA
C
C
C------ Protezione introdotta da Pagani per evitare FLOATING OVERFLOW
C
        IF (THETA0.LT.1.E-3 .AND. THETA0.GE.0.) THEN
           BSUTHETA0=B/1.E-3
        ELSE
           IF (THETA0.GT.-1.E-3 .AND. THETA0.LT.0.) THEN
              BSUTHETA0=-B/1.E-3
           ELSE 
              BSUTHETA0=B/THETA0
           ENDIF
        ENDIF
        IF (BSUTHETA0 .GT.  20.) BSUTHETA0=20.
        IF (BSUTHETA0 .LT. -20.) BSUTHETA0=-20.
        VISD = A * EXP(BSUTHETA0) * RO
C
C
C       CONDUCIBILITA` TERMICA
C
        COND = C1*0.1172*ROW/RO*(1.-0.00054*THETA0)
C
C
C       CALORE SPECIFICO
C
        IF(TIPO.EQ.6)THEN
          CASP = (C2 + C6*SQRT(RO/ROW)*THETA)/SQRT(RO/ROW)
        ELSE
          CASP = C2*(1735.7+3.391*THETA)/SQRT(RO/ROW)
        ENDIF
C
C       ENTALPIA
C
        IF(TIPO.EQ.6)THEN
          ENTI = (C2*SQRT(ROW/R0) - C6*288.15)*THETA0 +
     $            C6/2. * (T**2-273.15**2)
        ELSE
          ENTI = 2.*C2*SQRT(ROW/R0)*(DEXP(ARG2)*(1735.7+6.782/ALF*
     $         (ARG2-1.))-1735.7+6.782/ALF)/ALF
        ENDIF
        IF(TIPO.EQ.6.AND.THETA0.LT.0.)THEN
         CASP=1287.2
         ENTI=CASP*THETA0
        ENDIF
        ENTA=ENTI
C
C       dRO/dT
C
        DRDT = - ALF * RO
C
        RETURN
        END
