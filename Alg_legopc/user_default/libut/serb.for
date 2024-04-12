       SUBROUTINE SERBI1(IFUN,K,IBL1,IBL2,NSTATI,NUSCIT,NINGRE)
C
C---SERBATOIO PIEZOMETRICO
C
       GO TO(100,200), IFUN
C
  100  WRITE(6,500)'SERBATOIO PIEZOMETRICO'
       NSTATI = 0
       NUSCIT = 5
       NINGRE = 4
       RETURN
C
  200  CONTINUE
       IF(K.EQ.1)              WRITE(6,501)'VARIABILI DI USCITA'
       IF(K.EQ.NSTATI+NUSCIT+1)WRITE(6,501)'VARIABILI DI INGRESSO'
C
       GO TO(1,2,3,4,5,6,7,8,9),K
C uscite
  1    WRITE(6,502)'LIVELLO SERBATOIO'
       GO TO 400
  2    WRITE(6,502)'PRESSIONE FONDO SERBATOIO'
       GO TO 400
  3    WRITE(6,502)'ENTALPIA LIQUIDO NEL SERBATOIO'
       GO TO 400
  4    WRITE(6,502)'PORTATA VAPORE USCITA SERBATOIO'
       GO TO 400
  5    WRITE(6,502)'ENTALPIA VAPORE USCITA SERBATOIO'
       GO TO 400
C ingressi
  6    WRITE(6,502)'PORTATA INGRESSO'
       GO TO 400
  7    WRITE(6,502)'ENTALPIA INGRESSO'
       GO TO 400
  8    WRITE(6,502)'PORTATA LIQUIDO USCITA'
       GO TO 400
  9    WRITE(6,502)'PRESSIONE NEL SERBATOIO'
       GO TO 400
C
  400  RETURN
C
500    FORMAT(//10X,A//)
501    FORMAT(//20X,A//)
502    FORMAT(14X,A)
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SERBI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     1                 IBL1,IBL2,IER,CNXYU,TOL)
C
       DIMENSION VAR(MX1,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
C
       COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
       REAL  LIVS,PFSE,HSER,WVAP,HVAP,WING,HING,WOUT,PSER
       REAL  SEZ,LMAX
C
C---SERBATOIO PIEZOMETRICO
C
       GO TO(100,200), IFUN
C
  100  WRITE(14,500)'SEZ        '
     1             ,'LMAX        '
       RETURN
C
C---lettura e memorizzazione dati
C
  200  READ(14,501)
       READ(14,501) SEZ
     1             ,LMAX
C
  500  FORMAT(3(4X,A8,' =',10X,'*'))
  501  FORMAT(3(14X,F10.0,1X))
C
       DATI(ID2   ) = SEZ
       DATI(ID2+1 ) = LMAX
C
C_____ RISERVO DUE POSTI PER GLI STATI INTERNI (LIVELLO ED ENTALPIA)
C
       DATI(ID2+2  )=0.
       DATI(ID2+3  )=0.
       ID2 = ID2+3
C
C---costanti di normalizzazione
C
       CNXYU(IV1  ) = AL0
       CNXYU(IV1+1) = P0
       CNXYU(IV1+2) = H0
       CNXYU(IV1+3) = W0
       CNXYU(IV1+4) = H0
       CNXYU(IV1+5) = W0
       CNXYU(IV1+6) = H0
       CNXYU(IV1+7) = W0
       CNXYU(IV1+8) = P0
C
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SERBC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
       DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
       COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
       COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
       EXTERNAL SERB
       EXTERNAL NAJAC
       EXTERNAL SERBJAC
C
       REAL  LIVS,PFSE,HSER,WVAP,HVAP,WING,HING,WOUT,PSER,LIVC
       REAL  SEZ,LMAX
       LOGICAL SAT
C
C---SERBATOIO PIEZOMETRICO
C
       GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100  CONTINUE
       CALL SERBJAC(1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
       RETURN
C
C---calcolo residui
C
  200  CALL SERB(IFUN,IXYU,XYU,IPD,DATI,RNI)
       RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL SERBJAC(2,...
C
C      jacobiano numerico  CALL SERBJAC(3,...
C
C$*$
  300  CONTINUE
       CALL SERBJAC(3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SERBJAC(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
       DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
       COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
       COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
       EXTERNAL SERB
C
       REAL  LIVS,PFSE,HSER,WVAP,HVAP,WING,HING,WOUT,PSER
       REAL  SEZ,LMAX,HLS,HLS0,HVS,HVS0,SING,TITOLO,MSER,RO
       LOGICAL SAT
C
       GOTO(1,2,3),IFUN
C
C---topologia jacobiano
C
  1    CONTINUE
       DO 111 J=1,5
        DO 111 I=1,9
         AJAC(J,I)=1.
  111  CONTINUE
C
       RETURN
C
C      calcolo jacobiano analitico
C
  2    CONTINUE
       LIVS = XYU(IXYU   )
       PFSE = XYU(IXYU+1 )
       HSER = XYU(IXYU+2 )
       WVAP = XYU(IXYU+3 )
       HVAP = XYU(IXYU+4 )
       WING = XYU(IXYU+5 )
       HING = XYU(IXYU+6 )
       WOUT = XYU(IXYU+7 )
       PSER = XYU(IXYU+8 )
C
       SEZ  = DATI(IPD   )
       LMAX = DATI(IPD+1 )
       HSERP= DATI(IPD+3 )
C
      SLSER=SHEV(PSER*P0,HSER*H0,1)
      RO=ROEV(PSER*P0,SLSER,1)
      CALL SATUR(PSER*P0,2,HLS,HVS,1)
      HLS0=HLS/H0
      HVS0=HVS/H0
      IF (HING.LE.HLS0) THEN
         HLIN=HING
         WLIN=WING
         HVIN=HVS0
         WVIN=0.
      ELSE
         IF (HING.GE.HVS0) THEN
            HLIN=HLS0
            WLIN=0.
            HVIN=HING
            WVIN=WING
         ELSE
            HLIN=HLS0
            HVIN=HVS0
            TITOLO= (HING - HLS0)/(HVS0-HLS0)
            WLIN=(1.-TITOLO)*WING
            WVIN=WING-WLIN
         ENDIF
      ENDIF
C
      MSER=RO*SEZ*LIVS*AL0
C
C
C--derivata del residuo n.1 (equazione algebrica)   *******
C
       IF (KREGIM) THEN
C
C____ Jacobiano a regime
C
        IF(LIVS.GT.0. .AND. LIVS.LT.LMAX/AL0) THEN
          AJAC(1,6)=-1.
          AJAC(1,8)=1.
        ELSE
          AJAC(1,1)=-1.
        ENDIF
C
      ELSE
C
C____ Jacobiano in transitorio
C
        IF(LIVS.GT.0. .AND. LIVS.LT.LMAX/AL0) THEN
          AJAC(1,1)=-1.
          AJAC(1,6)=DTINT/(RO*SEZ) * W0/AL0
          AJAC(1,8)=-DTINT/(RO*SEZ) * W0/AL0
        ELSE
          AJAC(1,1)=-1.
        ENDIF
C
      ENDIF
C
C
C
C--derivata del residuo n.2 (equazione algebrica)   *******
C
C      rispetto alla variabile LIVS
C
      AJAC(2,1) =-9.81*RO * AL0/P0
C
C
C      rispetto alla variabile PFSE
C
      AJAC(2,2) =1.
C
C
C      rispetto alla variabile PSER
C
      AJAC(2,9) =-1.
C
C
C
C--derivata del residuo n.3 (equazione algebrica)   *******
C
      IF (KREGIM) THEN
C
C----- a regime
C
C      rispetto alla variabile HSER
C
         AJAC(3,3) =1.  
C
C
C      rispetto alla variabile HING
C
         IF (HING.LE.HLS0) THEN
            AJAC(3,7) =-1.
         ELSE
            AJAC(3,7) =0.
         ENDIF
C
      ELSE
C
C----- in transitorio
C
C
C      rispetto alla variabile LIVS
C
        AJAC(3,1) = -RO*SEZ*(HSER-HSERP)
C         AJAC(3,1) =0.
C
C
C      rispetto alla variabile HSER
C
         AJAC(3,3) = -(MSER/W0 + WLIN*DTINT)
C
C
C      rispetto alla variabile WING
C
         AJAC(3,6) = (HLIN-HSER)*DTINT
C
C
C      rispetto alla variabile HING
C
        AJAC(3,7) = WLIN*DTINT
C
      ENDIF
C
C
C
C--derivata del residuo n.4 (equazione algebrica)   *******
C
      AJAC(4,4)=1.
C
      IF (HING.LE.HLS0) THEN
        AJAC(4,5) = 0.
      ELSE
        IF (HING.GE.HVS0) THEN
          AJAC(4,6) = -1.
        ELSE
          AJAC(4,6) = -TITOLO
        ENDIF
      ENDIF
C
C
C--derivata del residuo n.5 (equazione algebrica)   *******
C
C
C      rispetto alla variabile HVAP
C
         AJAC(5,5) = 1.
C
      RETURN
C
C---calcolo jacobiano numerico
C
  3   CONTINUE
C
       NSTATI = 0
       NUSCIT = 5
       NINGRE = 4
       EPS    = 1.E-3
       EPSLIM = 1.E-4
       CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     1            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,SERB)
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SERB(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
       DIMENSION XYU(*),DATI(*),RNI(*)
C
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
       COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
       COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
       REAL  LIVS,PFSE,HSER,WVAP,HVAP,WING,HING,WOUT,PSER
       REAL  HLS,HLS0,HVS,HVS0,WLIN,HLIN,WVIN,HVIN,LIVC
       REAL  HSERP,MSER,LIVSP
       REAL  SING,TITOLO,SLSER,RO
       REAL  SEZ,LMAX
C
C---SERBATOIO PIEZOMETRICO
C
C   calcolo residui
C
C---decodifica variabili e dati
C
       LIVS     = XYU(IXYU   )
       PFSE     = XYU(IXYU+1 )
       HSER     = XYU(IXYU+2 )
       WVAP     = XYU(IXYU+3 )
       HVAP     = XYU(IXYU+4 )
       WING     = XYU(IXYU+5 )
       HING     = XYU(IXYU+6 )
       WOUT     = XYU(IXYU+7 )
       PSER     = XYU(IXYU+8 )
C
       SEZ       = DATI(IPD   )
       LMAX      = DATI(IPD+1 )
C
      SLSER=SHEV(PFSE*P0,HSER*H0,1)
      RO=ROEV(PFSE*P0,SLSER,1)
      MSER=RO*SEZ*LIVS*AL0
      CALL SATUR(PSER*P0,2,HLS,HVS,1)
      HLS0=HLS/H0
      HVS0=HVS/H0
        TIT = (HSER - HLS0)/(HVS0-HLS0)
        IF(TIT.LT.0.) THEN
           WEV=0.
        ELSE IF(TIT.GT.1.) THEN
           WEV = MSER/10./W0
        ELSE
           WEV = MSER*TIT/10./W0        
        ENDIF
      IF (HING.LE.HLS0) THEN
         HLIN=HING
         WLIN=WING
         HVIN=HVS0
         WVIN=0.
      ELSE
         IF (HING.GE.HVS0) THEN
            HLIN=HLS0
            WLIN=0.
            HVIN=HING
            WVIN=WING
         ELSE
            HLIN=HLS0
            HVIN=HVS0
            TITOLO= (HING - HLS0)/(HVS0-HLS0)
            WLIN=(1.-TITOLO)*WING
            WVIN=WING-WLIN
         ENDIF
      ENDIF
C
C
      IF(KREGIM) THEN
C
C___ a regime
C
         RNI(  1) = WLIN - WOUT
C
         DATI(IPD+2) = LIVS
C
      ELSE
C
C___ in transitorio
C
C
C_____ memorizzazione dello stato
C
           IF(ITERT.EQ.0.AND.IFUN.EQ.2) THEN
             LIVSP=LIVS
             DATI(IPD+2)=LIVS
           ELSE
             LIVSP=DATI(IPD+2)
           ENDIF
C
C------ calcolo livello
C
          LIVC=LIVSP+W0*(WLIN-WOUT-WEV)/(RO*SEZ*AL0)*DTINT
C
          IF(LIVC.GT.LMAX/AL0)LIVC=LMAX/AL0
C
          IF(LIVC.LT.0.)LIVC=0.
C
          RNI(1)=LIVS-LIVC
C
      ENDIF
C
C
C--residuo n.2 (equazione algebrica)   *******
C
C----- calcolo pressione fondo serbatoio
C
      RNI(2) =(PSER+RO*9.81*LIVS*AL0/P0) - PFSE
C
C
C
C--residuo n.3 (equazione differenziale)   *******
C
C----- calcolo entalpia liquido serbatoio
C
C
         IF (KREGIM) THEN
C
C ------ regime
C
         RNI(3)=HLIN-HSER 
C
C_____ memorizzazione dello stato
C
         DATI(IPD+3) = HSER
C
C           
      ELSE  
C
C
C_____ memorizzazione dello stato
C
           IF(ITERT.EQ.0.AND.IFUN.EQ.2) THEN
             HSERP = HSER 
             DATI(IPD+3)=HSERP
           ELSE
             HSERP=DATI(IPD+3)
           ENDIF
C
C----- integrazione equazione conservazione dell'energia
C
      RNI(3)=MSER/W0*(HSER - HSERP) + WLIN*(HSER-HLIN)*DTINT 
     $                              - WEV*(HSER-HVS0)*DTINT         
C
      ENDIF
C
C
C
C--residuo n.4 (equazione algebrica)   *******
C
C----- calcolo portata vapore uscita serbatoio
C
      RNI(4)=WVIN-WVAP+WEV 
C
C
C
C--residuo n.5 (equazione algebrica)   *******
C
C----- calcolo entalpia vapore uscita serbatoio
C
      RNI(5)= HVIN - HVAP
C           
C
      RETURN
      END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SERBI3(IFO,IOB,DEBL)
C
       COMMON/SERB00/IBLOC,NCEL,NPAR
       CHARACTER*80 DEBL
       CHARACTER*8 IBLOC
       CHARACTER*4 IOB
       CHARACTER*4 MOD
       DATA MOD/'SERB'/
C
       CALL SERBI4(IOB,MOD)
       NSTATI = 0
       NUSCIT = 5
       NINGRE = 4
       WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999  FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
       WRITE(IFO,3001)IOB
 3001  FORMAT('LIVS',A4,2X,
     &57H--UA--     LIVELLO SERBATOIO                              )
       WRITE(IFO,3002)IOB
 3002  FORMAT('PFSE',A4,2X,
     &57H--UA--     PRESSIONE FONDO SERBATOIO                      )
       WRITE(IFO,3003)IOB
 3003  FORMAT('HSER',A4,2X,
     &57H--UA--     ENTALPIA SERBATOIO                             )
       WRITE(IFO,3004)IOB
 3004  FORMAT('WVAP',A4,2X,
     &57H--UA--     PORTATA VAPORE USCITA SERBATOIO                )
       WRITE(IFO,3005)IOB
 3005  FORMAT('HVAP',A4,2X,
     &57H--UA--     ENTALPIA VAPORE USCITA SERBATOIO               )
       WRITE(IFO,3006)IOB
 3006  FORMAT('WING',A4,2X,
     &57H--IN--     PORTATA INGRESSO                               )
       WRITE(IFO,3007)IOB
 3007  FORMAT('HING',A4,2X,
     &57H--IN--     ENTALPIA INGRESSO                              )
       WRITE(IFO,3008)IOB
 3008  FORMAT('WOUT',A4,2X,
     &57H--IN--     PORTATA LIQUIDO USCITA                         )
       WRITE(IFO,3009)IOB
 3009  FORMAT('PSER',A4,2X,
     &57H--IN--     PRESSIONE NEL SERBATOIO                        )
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SERBI4(IOB,MOD)
       COMMON/SERB00/IBLOC,NCEL,NPAR
       CHARACTER*8 IBLOC
       CHARACTER*4 IOB
       CHARACTER*4 MOD
C
C
       WRITE(IBLOC,1000)MOD,IOB
 1000  FORMAT(2A4)

       RETURN
       END
CC
      SUBROUTINE SERBD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,IX
     $YU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
