      SUBROUTINE COEXI3(IFO,IOB,DEBL)
      COMMON/COEX00/IBLOC,NE,NU,NCI 
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'COEX'/
C
C   CONDENSATION EXCHANGER  23.11.98
C   Mainfold with NE inlet tubes and NU outlet tubes, having an external 
C   metal shell exchanging with external environment and exchanging with
C   NTUB cellized tubes crossing its volume horizontally or vertically.
C   Condensed water drop down and removal explicitly considered.
C   In order to consider correctly thermal exchange in case of mono-
C   phase flux (undercooled water) an average temperature TAVE was 
C   defined, different from output temperature (defined by PFLU,HFLU),
C   and this temperature was used for thermal power calculations.
C   The thermal exchange coefficients with tubes bundle are calculated
C   using correlations and considering an average manifold section for
C   fluid speed evaluation. The same coefficients are also filtered 
C   during transient with a time constant.
C
      CALL COEXI4(IOB,MOD)
C
C
      NSTATI=0
      NUSCIT=6+NCI
      NINGRE=2*(NE+NU)+NCI+4
      NVAR=NUSCIT+NINGRE
C
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('HFLU',A4,2X,'--UA-- FLUID ENTHALPY')
      WRITE(IFO,3001)IOB
 3001 FORMAT('PFLU',A4,2X,'--UA-- FLUID PRESSURE')
      WRITE(IFO,3002)IOB
 3002 FORMAT('TAVE',A4,2X,'--UA-- FLUID AVERAGE TEMPERATURE')
      WRITE(IFO,3003) (I,IOB,I,I=1,NCI)
 3003 FORMAT('GAM',I1,A4,2X,'--UA-- THERMAL EXCH. COEFF. CELL ',I1)
      WRITE(IFO,3004)IOB
 3004 FORMAT('TSHE',A4,2X,'--UA-- SHELL METAL TEMPERATURE')
      WRITE(IFO,3005)IOB
 3005 FORMAT('WSPU',A4,2X,'--UA-- DROPDOWN WATER MASS FLOW RATE')
      WRITE(IFO,3006)IOB
 3006 FORMAT('HSPU',A4,2X,'--UA-- DROPDOWN WATER ENTHALPY')
      DO J=1,NE
        WRITE(IFO,3007)J,IOB,J
        WRITE(IFO,3008)J,IOB,J
      ENDDO 
 3007 FORMAT('WE',I2,A4,2X,'--IN-- MASS FLOW RATE INLET BRANCH N.',I2)
 3008 FORMAT('HE',I2,A4,2X,'--IN-- ENTHALPY INLET BRANCH N.',I2)
      DO J=1,NU
        WRITE(IFO,3009)J,IOB,J
        WRITE(IFO,3010)J,IOB,J
      ENDDO
 3009 FORMAT('WU',I2,A4,2X,'--IN-- MASS FLOW RATE OUTLET BRANCH N.',I2)
 3010 FORMAT('HU',I2,A4,2X,'--IN-- ENTHALPY OUTLET BRANCH ',I2,' (W<0)')
      WRITE(IFO,3011)IOB
 3011 FORMAT('TEST',A4,2X,'--IN-- EXTERNAL ENVIRONMENT TEMPERATURE')
      WRITE(IFO,3012)IOB
 3012 FORMAT('GEST',A4,2X,'--IN-- THERMAL EXCH. COEFF. WITH EXT. ENV.')
      WRITE(IFO,3013)IOB
 3013 FORMAT('ALZA',A4,2X,'--IN-- DROPDOWN VALVE STEM POSITION')
      WRITE(IFO,3014) (I,IOB,I,I=1,NCI)
 3014 FORMAT('TMI',I1,A4,2X,'--IN-- TUBES METAL TEMPERATURE CELL ',I1)
      WRITE(IFO,3015)IOB
 3015 FORMAT('CORR',A4,2X,'--IN-- THERMAL EXCHANGE CORRECTION')
C
      RETURN
      END
C***********************************************************************
      SUBROUTINE COEXI4(IOB,MOD)
      PARAMETER (MAXIO=40,MAXCI=9)
      COMMON/COEX00/IBLOC,NE,NU,NCI
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER*2 IS
C
   10 WRITE(6,101) MAXIO
  101 FORMAT(10X,'***** CONDENSATION EXCHANGER *****'/
     $       10X,'INLET BRANCHES NUMBER (01 -',I3,') ?')
      READ(5,*) NE
      IF(NE.LE.0.OR.NE.GT.MAXIO) THEN
         WRITE(6,102) NE
         GOTO 10
      ENDIF
  102 FORMAT(10X,'WRONG! - N.ENT.=',I3,/)
C
   15 WRITE(6,105) MAXIO
  105 FORMAT(10X,'OUTLET BRANCHES NUMBER (01 -',I3,') ?')
      READ(5,*) NU
      IF(NU.LE.0.OR.NU.GT.MAXIO) THEN
         WRITE(6,106) NU
         GOTO 15
      ENDIF
  106 FORMAT(10X,'WRONG! - N.USC.=',I3,/)
C
   16 WRITE(6,107) MAXCI
  107 FORMAT(10X,'INNER TUBES CELL NUMBER (01 -',I3,') ?')
      READ(5,*) NCI
      IF(NCI.LE.0.OR.NCI.GT.MAXCI) THEN
         WRITE(6,108) NCI
         GOTO 16
      ENDIF
  108 FORMAT(10X,'WRONG! - N.CEL.=',I3,/)
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
C***********************************************************************
        SUBROUTINE COEXI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
        DIMENSION VAR(MX1,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
C
        PARAMETER (PI=3.14159)
        PARAMETER (MAXIO=40,MAXCI=9)
        PARAMETER (GAM0=1000.) !compatibile EXCH e FUMN
C
        COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
        REAL LENTUB
C
C---Condensation exchanger
C
        GO TO(100,200),IFUN
C
  100   WRITE(14,500)    'NU.TU.EN'
     1                  ,'NU.TU.US'
     1                  ,'INT.VOL.'
     1                  ,'AV.SECT.'
     1                  ,'SH.MASS '
     1                  ,'SH.CP.  '
     1                  ,'SH.COND.'
     1                  ,'SH.THICK'
     1                  ,'SH.EXT.S'
     1                  ,'SH.INT.S'
     1                  ,'TUB.NCEL'
     1                  ,'TUB.NUMB'
     1                  ,'TUB.DEXT'
     1                  ,'TUB.LENG'
     1                  ,'TUB.SURF'
     1                  ,'TUB. H/V'
     1                  ,'TUB.FORS'
        RETURN
C
C---lettura e memorizzazione dati
C
  200   READ(14,502)
        READ(14,502)     FNE
     1                  ,FNU
     1                  ,VOLUME
     1                  ,AVSECT
     1                  ,CM
     1                  ,CPM
     1                  ,COND
     1                  ,SPESS
     1                  ,SUPES
     1                  ,SUPIN
     1                  ,FNCEL
     1                  ,FNTUB
     1                  ,DEXTUB
     1                  ,FLENTUB
     1                  ,TUBSUP
     1                  ,DISPOV
     1                  ,FORS
C
  500   FORMAT(3(4X,A8,' =',10X,'*'))
  502   FORMAT(3(14X,F10.2,1X))
C
C______________________________________________
C
       NE=FNE
       NU=FNU
       NCEL=FNCEL
       NTUB=FNTUB
       LENTUB=FLENTUB
C
        CTMET=CM*CPM
        GAMET=2.*COND/SPESS
        DCOL=4*VOLUME/SUPIN !esatto trascurando le basi
        IF (TUBSUP.EQ.0.) THEN
           SCEL=NTUB*PI*DEXTUB*LENTUB/NCEL
        ELSE
           SCEL=TUBSUP/NCEL
           DEXTUB=TUBSUP/(PI*NTUB*LENTUB) !diametro medio a pari sup. e lungh.
        ENDIF
        SEZC=PI*(DCOL**2)/4.-NTUB*PI*(DEXTUB**2)/4. !sezione netta di passaggio
        VOLC=VOLUME-NTUB*PI*(DEXTUB**2)*LENTUB/4. !volume disponibile cavita'
        IF (VOLC.LE.0) THEN
         WRITE(6,*) 'TUBES VOLUME CAN''T BE BIGGER THAN ENCLOSURE!'
         STOP
        ENDIF
        DEQ=4*SEZC/(PI*DCOL+NTUB*PI*DEXTUB) !diametro idraulico equivalente
C
        DATI(ID2  ) = NE  
        DATI(ID2+1) = NU  
        DATI(ID2+2) = VOLUME
        DATI(ID2+3) = CTMET
C       DATI(ID2+4) = SK   
C       DATI(ID2+5) = PK   
C       DATI(ID2+6) = TMK
C       DATI(ID2+7) = S    
C       DATI(ID2+8) = P    
C       DATI(ID2+9) = TM   
        DATI(ID2+10)= GAMET
C       DATI(ID2+11)= GAMI
        DATI(ID2+12)= SUPES
        DATI(ID2+13)= SUPIN
        DATI(ID2+14)= NCEL
        DATI(ID2+15)= NTUB   
        DATI(ID2+16)= SCEL
        DATI(ID2+17)= DEQ
        DATI(ID2+18)= DISPOV 
        DATI(ID2+19)= FORS
        DATI(ID2+20)= SEZC
        DATI(ID2+21)= VOLC
        DATI(ID2+22)= AVSECT
        DATI(ID2+23)= LENTUB
        DATI(ID2+24)= DEXTUB
C
        ID2 = ID2+24+2*NCEL !lasciati NCEL posti per memorizzazione GTUB(I)
                            !e NCEL posti per GFLT(I), variabile filtrata
C
C---costanti di normalizzazione
C
        CNXYU(IV1  ) = H0
        CNXYU(IV1+1) = P0
        CNXYU(IV1+2) = T0
        DO I=1,NCEL
	   CNXYU(IV1+2+I)=GAM0
        ENDDO
        CNXYU(IV1+NCEL+3) = T0
        CNXYU(IV1+NCEL+4) = W0
        CNXYU(IV1+NCEL+5) = H0
        NT=NE+NU
        I0=IV1+NCEL+5
        DO J = 1,NT
          JW=2*J-1
          JH=JW+1
          CNXYU(I0+JW) = W0
          CNXYU(I0+JH) = H0
        ENDDO
        CNXYU(I0+2*NT+1) = T0
        CNXYU(I0+2*NT+2) = GAM0 
        CNXYU(I0+2*NT+3) = 1.
        DO I=1,NCEL
           CNXYU(I0+2*NT+3+I)=T0
        ENDDO
        CNXYU(I0+2*NT+4+NCEL)=1.
C
        RETURN
        END
C************************************************************************
        SUBROUTINE COEXC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
        DIMENSION AJAC(MX5,1),XYU(1),DATI(1),RNI(1)
C
C---Condensation exchanger
C   CALCOLO RESIDUI
C
        PARAMETER (MAXIO=40,MAXCI=9)
C
        DIMENSION WE(MAXIO),WU(MAXIO),HE(MAXIO),HU(MAXIO)
        DIMENSION GAM(MAXCI),TMI(MAXCI)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
        EXTERNAL COEX
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
        NE=DATI(IPD)
        NU=DATI(IPD+1)
        NCI=DATI(IPD+14)
        NUSC=6+NCI
        NVAR=10+2*(NE+NU)+2*NCI
C
        GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100   DO I=1,NUSC
        DO J =1,NVAR
          AJAC(I,J) = 1.
        END DO
        END DO
        RETURN
C
C---calcolo residui
C
  200   CONTINUE
        CALL COEX(IFUN,IXYU,XYU,IPD,DATI,RNI)
        RETURN
C
C---calcolo jacobiano 
C
 300    CONTINUE
      NSTATI =0
      NUSCIT =NUSC
      NINGRE =2*(NE+NU)+4+NCI 
C
      EPS   =1.E-3
      EPSLIM=1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,COEX)
C
C---sostituzione righe jacobiano relative a GAM(I) con elementi nulli
C---con 1 sulla diagonale (per evitare di considerare le derivate dei
C---valori GTUB(I) rispetto alle variabili di stato (RNI=K-GAM)
C
      DO I = 4,3+NCI
         DO J = 1,NVAR
            IF (I.EQ.J) THEN
                AJAC(I,J)=1.
            ELSE
                AJAC(I,J)=0.
            ENDIF
         ENDDO
      ENDDO
C
      RETURN                
      END
C*********************************************************************
        SUBROUTINE COEX(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
        PARAMETER (TAU=1.)   !costante di tempo di condensazione
        PARAMETER (TFLT=10.) !costante di tempo di filtraggio GTUB
C
        DIMENSION XYU(1),DATI(1),RNI(1)
C
C---Condensation exchanger
C                     
        PARAMETER (MAXIO=40,MAXCI=9)
        PARAMETER (GAM0=1000.)
        PARAMETER (ALPHA=0.63) !parametro per calcolo temperatura media
C
        DIMENSION WE(MAXIO),WU(MAXIO),HE(MAXIO),HU(MAXIO)
        DIMENSION GAM(MAXCI),GTUB(MAXCI),GFLT(MAXCI),TMI(MAXCI)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
        REAL LTUB
C
C---decodifica dati
C
        NE   = DATI(IPD   )
        NU   = DATI(IPD+1 )
        VOL  = DATI(IPD+2 )
        CTMET= DATI(IPD+3 )
        GAMET= DATI(IPD+10)
        SUPES= DATI(IPD+12)
        SUPIN= DATI(IPD+13)
        NCEL = DATI(IPD+14)
        NTUB = DATI(IPD+15)
        SCEL = DATI(IPD+16)
        DEQ  = DATI(IPD+17)
        VERT = DATI(IPD+18)
        FORS = DATI(IPD+19)
        SEZC = DATI(IPD+20)
        VOLC = DATI(IPD+21)
        AVSE = DATI(IPD+22)
        LTUB = DATI(IPD+23)
        DETB = DATI(IPD+24)
C
C---decodifica variabili
C
        HNODO = XYU(IXYU  )*H0
        PNODO = XYU(IXYU+1)*P0
        TAV   = XYU(IXYU+2)*T0
        DO I=1,NCEL
	   GAM(I)=XYU(IXYU+2+I)*GAM0
        ENDDO
        TMMET = XYU(IXYU+NCEL+3)*T0
        WDREN = XYU(IXYU+NCEL+4)*W0
        HDREN = XYU(IXYU+NCEL+5)*H0
        I0=IXYU+NCEL+5
        DO J = 1,NE
          JW=2*J-1
          JH=JW+1
          WE(J) = XYU(I0+JW)*W0
          HE(J) = XYU(I0+JH)*H0
        END DO
        I0=I0+2*NE
        DO J = 1,NU
          JW=2*J-1
          JH=JW+1
          WU(J) = XYU(I0+JW)*W0
          HU(J) = XYU(I0+JH)*H0
        END DO
        TEST  = XYU(IXYU+2*(NE+NU)+NCEL+6)*T0
        GAMES = XYU(IXYU+2*(NE+NU)+NCEL+7)*GAM0
        ALZA  = XYU(IXYU+2*(NE+NU)+NCEL+8)*1.
        DO I=1,NCEL
           TMI(I)=XYU(IXYU+2*(NE+NU)+NCEL+8+I)*T0
        ENDDO
        CORR=XYU(IXYU+2*(NE+NU)+2*NCEL+9)
C
C----------------------------flussi di massa ed energia
        SUME=0.
        SUMHE=0.
        SUMU=0.
        DO J= 1,NE
          IF(WE(J).GT.0.)            THEN
            SUME=SUME+WE(J)
            SUMHE=SUMHE+WE(J)*HE(J)
                                     ELSE
            SUMU=SUMU+WE(J)
          ENDIF
        END DO
        DO J= 1,NU
          IF(WU(J).LT.0.)            THEN
            SUME=SUME-WU(J)
            SUMHE=SUMHE-WU(J)*HU(J)
                                     ELSE
            SUMU=SUMU-WU(J)
          ENDIF
        END DO
C
        P=PNODO
        H=HNODO
C
C--------------------------aggiornamento registro a scorrimento
C
        IF(ITERT.LE.0.AND.IFUN.EQ.2.OR.KREGIM) THEN
          S =SHEV(P,H,1)
          DATI(IPD+4)=S
          DATI(IPD+5)=P
          DATI(IPD+6)=DATI(IPD+9) !temperatura metallo
        ENDIF
          SK =DATI(IPD+4)
          PK =DATI(IPD+5)
          TMK=DATI(IPD+6)
C
          S=SHEV(P,H,1)
          CALL SATUR(P,2,HLS,HVS,1)
          Y=(H-HLS)/(HVS-HLS)
          T=TEV(P,S,1)
          RO =ROEV(P,S,1)        
          DELTAP = 1.E-3* P
          IF(DELTAP.LT.10.)DELTAP=10.
          P1 = P - DELTAP
          P2 = P + DELTAP
C
          RO1   =ROEV(P1,S,1)        
          DRODP1=1./A2EV(P1,S,1)
          DRODS1=BEV(P1,S,1)
C
          RO2   =ROEV(P2,S,1)        
          DRODP2=1./A2EV(P2,S,1)
          DRODS2=BEV(P2,S,1)
C
          ROM  =(RO1+RO2)/2.
          DRODP=(DRODP1+DRODP2)/2.
          DRODS=(DRODS1+DRODS2)/2.
C
C---------------------------calcolo coefficiente conv. lato shell
C
       IF(ITERT.LE.0.AND.IFUN.EQ.2.OR.KREGIM) THEN
          IF(Y.GT.1.) GAMI=1000.
          IF(Y.GE.0.AND.Y.LE.1.) GAMI = 15000.
          IF(Y.LT.0.)GAMI=1000.
          IF(SUME.LT.1.E-5) GAMI = 100.
          DATI(IPD+11)=GAMI
        ELSE
          GAMI= DATI(IPD+11)
        ENDIF
C
        GAMINT =SUPIN* GAMET*GAMI/(GAMET+GAMI)
        GAMEST =SUPES* GAMET*GAMES/(GAMET+GAMES)
C    
C---------------------------calcolo coefficienti conv. lato tubi
C
       IF ((ITERT.EQ.0.OR.KREGIM).AND.IFUN.EQ.2) THEN
          IF (FORS.GE.0.) THEN
             DO I=1,NCEL
                CALL COEXTERT(P,H,S,T,ROM,Y,TMI(I),DEQ,VERT,
     $               SUME,AVSE,SEZC,SCEL,LTUB,DETB,FORS,GTUB(I))
                DATI(IPD+24+I)=GTUB(I)
             ENDDO
          ELSE
             DO I=1,NCEL
	        CALL COEXGAMUT(P,H,S,T,ROM,Y,TMI(I),DEQ,VERT,
     $               SUME,AVSE,SEZC,SCEL,LTUB,DETB,FORS,GTUB(I))
                DATI(IPD+24+I)=GTUB(I)
             ENDDO
          ENDIF
       ELSE
          DO I=1,NCEL
             GTUB(I)=DATI(IPD+24+I)          
          ENDDO
       ENDIF
C
C---------------------------calcolo coefficienti conv. filtrati
C
      IF (KREGIM.AND.IFUN.EQ.2) THEN              !a regime (inizializ.)
         DO I=1,NCEL
            DATI(IPD+NCEL+24+I)=GTUB(I)
         ENDDO
      ELSE IF (ITERT.EQ.0.AND.IFUN.EQ.2.) THEN    !prima iteraz. transit.
         DO I=1,NCEL
            GFLT(I)=(TFLT*DATI(IPD+NCEL+24+I)+DTINT*GTUB(I))/
     $              (TFLT+DTINT)
            DATI(IPD+NCEL+24+I)=GFLT(I)
         ENDDO   
      ELSE                                        !negli altri casi
         DO I=1,NCEL
            GFLT(I)=DATI(IPD+NCEL+24+I)
         ENDDO
      ENDIF
C
C---- calcolo portata drenaggio del liquido
C
       IF(Y.LT.0.OR.Y.GT.1.) THEN
         CSI=1.
       ELSE
         CSI=Y
       ENDIF
       WLIQ=ALZA*(RO*VOLC*(1.-CSI)/TAU) 
       HLIQ=HLS
       HVAP=HVS
C
C---- calcolo temperatura media per scambi termici
C
       IF (SUME.EQ.0.) THEN
          TAVE=T
       ELSE
          HAVE=0.
          DO I=1,NE
             HAVE=HAVE+WE(I)*HE(I)
          ENDDO
          HAVE=HAVE/SUME
          TIN=TEV(P,SHEV(P,HAVE,1),1)
          TAVE=(1-ALPHA)*TIN+ALPHA*T
       ENDIF
C
       IF(KREGIM) GO TO 1000
C
C------------------------------------- CALCOLO TRANSITORIO
C
       DEN=(1.+DTINT*(GAMINT+GAMEST)/CTMET)
       TM = (TMK+DTINT*(GAMINT*TAVE+ GAMEST*TEST)/CTMET)/DEN
       DATI(IPD+9)=TM
       GAMTUB=0.
       DO I=1,NCEL
          GAMTUB=GAMTUB+GFLT(I)*(TMI(I)-TAVE)
       ENDDO
C______ Integrazione equaz. energia
       RNI(1)=(VOL*RO*T*(S-SK)-DTINT*(SUMHE-SUME*HNODO
     $       -WDREN*(HDREN-HNODO)+ GAMINT*(TM-TAVE)+GAMTUB*CORR*SCEL))
     $       /W0/H0
C______ Integrazione equaz. massa  nel fluido
       RNI(2)= (VOL*(DRODP*(P-PK)+ DRODS*(S-SK))-
     $         DTINT*(SUME+SUMU-WDREN))
     $         /W0
       RNI(3)= (TAV-TAVE)/T0
       DO I=1,NCEL
          RNI(3+I)= (CORR*GFLT(I)-GAM(I))/GAM0
       ENDDO
       RNI(NCEL+4)= (TMMET-TM)/T0
       RNI(NCEL+5)=(WLIQ-WDREN)/W0
       RNI(NCEL+6)=(HLIQ-HDREN)/H0
       RETURN
C
C------------------------------------ CALCOLO STAZIONARIO
C
 1000  CONTINUE
       GAMTUB=0.
       DO I=1,NCEL
          GAMTUB=GAMTUB+GTUB(I)*(TMI(I)-TAVE)
       ENDDO
       RNI(1)=(SUMHE+SUMU*HNODO - WDREN*HDREN
     $        +GAMINT*(TMMET-TAVE)+GAMTUB*CORR*SCEL)/W0/H0
C______ Integrazione equaz. massa  nel fluido
       RNI(2)= (SUME+SUMU-WDREN)/W0
       RNI(3)= (TAV-TAVE)/T0
       DO I=1,NCEL
          RNI(3+I)= (CORR*GTUB(I)-GAM(I))/GAM0
       ENDDO
       RNI(NCEL+4)= (GAMEST*(TMMET-TEST)-GAMINT*(TAVE-TMMET))/W0/H0
       RNI(NCEL+5)=(WLIQ-WDREN)/W0
       RNI(NCEL+6)=(HLIQ-HDREN)/H0
C
       DATI(IPD+4)=S        
       DATI(IPD+5)=P
       DATI(IPD+7)=S        
       DATI(IPD+8)=P
       DATI(IPD+6)=TMMET
       DATI(IPD+9)=TMMET
C
       RETURN
       END
C************************************************************************
      SUBROUTINE COEXD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      RETURN
      END
C************************************************************************
      SUBROUTINE COEXTERT(P,H,S,T,RO,TIT,TP,D,VERT,W,AVSE,SEZ,SUP,LTUB,
     $                    DETB,FORS,HTC)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)				 !DBLE
C 
C**************** correlazioni: Dittus-Boelter per acqua (X<XMIN)
C                               Hadaller per vapore (X>XMAX)
C                               Correlazione condensaz. per XMIN<=X<=XMAX
C                               ALPHA stabilisce la temperatura di film
      PARAMETER (PI=3.14159,G=9.81)
      PARAMETER (XMIN=0.,XMAX=1.,ALPHA=1.)
      PARAMETER (GCONST=10000.) !GAMMA costante di condensazione
      REAL H,HT,LTUB
      REAL HTC,MU,LAM,LUNG,LF,MF
      DATA X1/0.1/,X2/0.9/      !titoli di confine tra le correl.
C
      NFL=1
C
      IF (AVSE.EQ.0.) THEN !sez. utile per calcolo coeff. scambio
         SECTEX=SEZ        !sez. netta cavita
      ELSE
         SECTEX=AVSE       !sez. equivalente per calcolo velocita
      ENDIF
C
      IF(P.LT.221.2E5) THEN
       CALL SATUR(P,3,ROW,ROV,NFL)
       CALL SATUR(P,2,HLS,HVS,NFL)
       CALL SATUR(P,7,TSAT,ZOT,NFL)
       RWV=ROW/ROV
      ELSE
       TSAT=647.3
       RWV=1.
      ENDIF
      TF=ALPHA*T+(1-ALPHA)*TP
      CP=CPEV(P,S,TIT,0.5,NFL)
      MU=ETEV(P,TF,RO,RWV,TIT,0.5,NFL)
      LAM=ALEV(P,TF,RO,RWV,TIT,0.5,NFL)
      RE=ABS(W)*D/(SECTEX*MU)
      PR=CP*MU/LAM
C
      DB=.023*LAM*RE**.8*PR**.4/D
      HAD=.008348*LAM*RE**.8774*PR**.6112/D
C
      IF (FORS.EQ.0.) THEN
         GCOND=GCONST
      ELSE
         IF (VERT.EQ.0.) THEN
            COE=0.7235  !tubi orizzontali
            LUNG=DETB
         ELSE
            COE=0.94    !tubi verticali
            LUNG=LTUB
         ENDIF
         LF=ALEV(P,TF,ROW,RWV,0.,0.5,NFL)
         MF=ETEV(P,TF,ROW,RWV,0.,0.5,NFL) 
         DHVAP=HVS-HLS
         DTWALL=ABS(T-TP)
         GCOND=COE*(((LF**3)*(ROW**2)*G*DHVAP)/(MF*LUNG*DTWALL))**0.25
      ENDIF
C
      IF (TIT.LT.XMIN) THEN
         HTC=DB
      ELSE IF (TIT.GT.XMIN.AND.TIT.LE.X1) THEN
         A=(GCOND-DB)/(X1-XMIN)
         B=DB-A*XMIN
         HTC=A*TIT+B
      ELSE IF (TIT.GT.X1.AND.TIT.LE.X2) THEN
         HTC=GCOND
      ELSE IF (TIT.GT.X2.AND.TIT.LE.XMAX) THEN
         A=(HAD-GCOND)/(XMAX-X2)
         B=HAD-A*XMAX
         HTC=A*TIT+B
      ELSE
         HTC=HAD
      ENDIF 
      RETURN
      END
C~FORAUS_COEX~C
C
C      SUBROUTINE COEXGAMUT(P,H,S,T,ROM,Y,TMI,DEQ,VERT,
C     $                     SUME,AVSE,SEZC,SCEL,LTUB,DETB,FORS,GAMMA)
C      GAMMA = 5000.
C      RETURN
C      END
C
C~FORAUS_COEX~C
