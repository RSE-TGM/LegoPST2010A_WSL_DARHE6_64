C**********************************************************************
C modulo calt.f
C tipo 
C release  3.1
C data 9/5/94
C reserver @(#)calt.f	3.1
C**********************************************************************
      SUBROUTINE CALTI3(IFO,IOB,DEBL)
      COMMON/CALT00/IBLOC,NE,NU,ISPU
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'CALT'/
C
C
C---COLLETTORE A N TUBI 
C   CON TEMPERATURA METALLO ,TEMPERATURA ESTERNA E COEFFICIENTE DI 
C   SCAMBIO ESTERNO IN EVIDENZA
C   CON DRENAGGIO DEL LIQUIDO CHE SI PUO' CONDENSARE AL SUO INTERNO.
C
      CALL CALTI4(IOB,MOD)
C
C
      NSTATI=0
      NUSCIT=3+ISPU*2
      NINGRE=2*(NE+NU)+2+ISPU
      NVAR=NUSCIT+NINGRE
C
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('HCOL',A4,2X,'--UA-- ENTALPIA FLUIDO NEL COLLETTORE')
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('PCOL',A4,2X,'--UA-- PRESSIONE FLUIDO NEL COLLETTORE')
C
      WRITE(IFO,3405)IOB
 3405 FORMAT('TCOL',A4,2X,'--UA-- TEMPERATURA METALLO DEL COLLETTORE')
C
      IF(ISPU.EQ.1) THEN
         WRITE(IFO,3406)IOB
 3406 FORMAT('WSPU',A4,2X,'--UA-- PORTATA DI SPURGO DEL COLLETTORE')
         WRITE(IFO,3407)IOB
 3407 FORMAT('HSPU',A4,2X,'--UA-- ENTALPIA DELLO SPURGO DEL COLLETTORE')
      ENDIF
C
      DO 30 J=1,NE
        WRITE(IFO,3010)J,IOB,J
 3010   FORMAT('WE',I2,A4,2X,'--IN-- PORTATA RAMO ENTRANTE  N.',I2)
        WRITE(IFO,3015)J,IOB,J
 3015   FORMAT('HE',I2,A4,2X,'--IN-- ENTALPIA RAMO ENTRANTE N.',I2)
   30 CONTINUE
C
      DO 40 J=1,NU
        WRITE(IFO,3020)J,IOB,J
 3020   FORMAT('WU',I2,A4,2X,'--IN-- PORTATA RAMO USCENTE N.',I2)
        WRITE(IFO,3025)J,IOB,J
 3025   FORMAT('HU',I2,A4,2X,'--IN-- ENTALPIA RAMO USCENTE N.',I2
     $,' (W<0)')
   40 CONTINUE
      WRITE(IFO,3415)IOB
 3415 FORMAT('TEST',A4,2X,'--IN-- TEMPERATURA FLUIDO ESTERNO COLLETT.')
      WRITE(IFO,3425)IOB
 3425 FORMAT('GEST',A4,2X,'--IN-- COEFF. SCAMBIO ESTERNO COLLETTORE')
C
      IF(ISPU.EQ.1) WRITE(IFO,3426)IOB
 3426 FORMAT('ALZA',A4,2X,'--IN-- POSIZIONE VALVOLA SPURGO COLLETTORE')
C
      RETURN
      END
      SUBROUTINE CALTI4(IOB,MOD)
      COMMON/CALT00/IBLOC,NE,NU,ISPU
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER*2 IS
C
      MAX=40
C
   10 WRITE(6,101) MAX
  101 FORMAT(10X,'NODO COLLETTORE DI PORTATE'/
     $       10X,'NUMERO RAMI ENTRANTI (01 -',I3,') ?')
      READ(5,*) NE
      IF(NE.LE.0.OR.NE.GT.MAX) THEN
      WRITE(6,102) NE
  102 FORMAT(10X,'ERRORE - N.ENT.=',I3,/)
      GOTO 10
      ENDIF
C
   15 WRITE(6,105) MAX
  105 FORMAT(10X,'NUMERO RAMI USCENTI  (01 -',I3,') ?')
      READ(5,*) NU
      IF(NU.LE.0.OR.NU.GT.MAX) THEN
      WRITE(6,106) NU
  106 FORMAT(10X,'ERRORE - N.USC.=',I3,/)
      GOTO 15
      ENDIF
C
      ISPU=0
      WRITE(6,107)
  107 FORMAT(10X,
     $'VUOI TENER CONTO DELLO SPURGO DELLA CONDENSA? (NO/SI)')
      READ(5,'(A)') IS
      IF(IS.EQ.'SI'.OR.IS.EQ.'si') ISPU=1       
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
        SUBROUTINE CALTI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
        DIMENSION VAR(MX1,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
        PARAMETER (MAX=40)
        DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
        COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C
        GO TO(100,200),IFUN
C
  100   WRITE(14,500)    'NU.TU.EN    '
     1                  ,'NU.TU.US    '
     1                  ,'VOLUME      '
     1                  ,'MASSA MET.  '
     1                  ,'CP MET.     '
     1                  ,'COND MET.   '
     1                  ,'SPESSORE MET'
     1                  ,'SUP.  EST.  '
     1                  ,'SUP.  INT.  '
        RETURN
C
C---lettura e memorizzazione dati
C
  200   READ(14,502)
        READ(14,502)     FNE
     1                  ,FNU
     1                  ,VOLUME
     1                  ,CM
     1                  ,CPM
     1                  ,COND
     1                  ,SPESS
     1                  ,SUPES
     1                  ,SUPIN
C
  500   FORMAT(3(4X,A8,' =',10X,'*'))
  502   FORMAT(3(14X,F10.2,1X))
C
C______________________________________________
C
       NE=FNE
       NU=FNU
       ISPU=0
       IF(NUSCIT.GT.3) ISPU=1
          HRIF=XYU(IV1  )
          PRIF=XYU(IV1+1)
          TEST=XYU(IV1+2+2*ISPU+2*NE+2*NU+1)
C
          ISOLATO=0
        CTMET=CM*CPM
        GAMET=2.*COND/SPESS
        DEQ=(VOLUME+SQRT(VOLUME**2+VOLUME*2.*SPESS*SUPIN))*2./SUPIN
        DATI(ID2  ) = NE  
        DATI(ID2+1) = NU  
        DATI(ID2+2) = VOLUME
        DATI(ID2+3) = CTMET
C       DATI(ID2+4) = Sk   
C       DATI(ID2+5) = PK   
C       DATI(ID2+6) = S    
C       DATI(ID2+7) = P    
        DATI(ID2+8) = PRIF
        DATI(ID2+10)= GAMET
        DATI(ID2+11)= SUPES
C        DATI(ID2+12)= TM
        DATI(ID2+13)= HRIF
        DATI(ID2+14)= ISOLATO
        DATI(ID2+15)= DEQ
        DATI(ID2+16)= 1000.
        DATI(ID2+17)= ISPU
        DATI(ID2+18)= SUPIN
C
        ID2 = ID2+18
C
C---costanti di normalizzazione
C
        CNXYU(IV1  ) = H0
        CNXYU(IV1+1) = P0
        CNXYU(IV1+2) = T0
        IF(ISPU.EQ.1) THEN
          CNXYU(IV1+3) = W0
          CNXYU(IV1+4) = H0
        ENDIF
        NT=NE+NU
        I0=IV1+2+2*ISPU
        DO J = 1,NT
          JW=2*J-1
          JH=JW+1
          CNXYU(I0+JW) = W0
          CNXYU(I0+JH) = H0
        ENDDO
        CNXYU(I0+2*NT+1) = T0
        CNXYU(I0+2*NT+2) = 1000.
        IF(ISPU.EQ.1) CNXYU(I0+2*NT+3) = 1.
C
        RETURN
        END
        SUBROUTINE CALTC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C$$$$$     !!!!!!! INIZIO ISTRUZIONI PER SCCS !!!!!!!
       CHARACTER*80 SccsID
       DATA SccsID/'@(#)calt.f	3.1\t 3.1\t 9/5/94'/          
C$$$$$     !!!!!!! FINE ISTRUZIONI PER SCCS !!!!!!!
        DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C   CALCOLO RESIDUI
C
        PARAMETER (MAX=40)
        DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
        EXTERNAL CALT
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
        NE=DATI(IPD)
        NU=DATI(IPD+1)
        ISPU=DATI(IPD+17)
        NVAR=2*ISPU+2*(NE+NU)+5+ISPU
C
        GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100   DO I=1,3+ISPU*2
        DO J =1,NVAR
          AJAC(I,J) = 1.
        END DO
        END DO
        RETURN
C
C---calcolo residui
C
  200   CONTINUE
        CALL CALT(IFUN,IXYU,XYU,IPD,DATI,RNI)
        RETURN
C
C---calcolo jacobiano 
C
 300    CONTINUE
      NSTATI =0
      NUSCIT =3+2*ISPU
      NINGRE =2*(NE+NU) +2+ISPU
C
C---------calcolo jacobiano NUMERICO 
C
      EPS   =1.E-3
      EPSLIM=1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,CALT)
C
      RETURN                
      END
        SUBROUTINE CALT(IFUN,IXYU,XYU,IPD,DATI,RNI)
        DIMENSION XYU(*),DATI(*),RNI(*)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C   CALCOLO RESIDUI
C
        PARAMETER (MAX=40)
        DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
C____________ COEFFICIENTI PER DEFINIRE LO SCAMBIO FLUIDO PARETE
C             COPIATI DA GAMTERT
        DATA CCW/4.0125/,CCV/7.495/,AAW/0.0375/,AAV/0.0167E-5/
C
C
C---calcolo residui
C
C
C---decodifica dati
C
        NE   =DATI(IPD   )
        NU   =DATI(IPD+1 )
        ISPU =DATI(IPD+17)
        VOL  =DATI(IPD+2 )
        CTMET=DATI(IPD+3 )
        PRIF = DATI(IPD+8)
        GAMET= DATI(IPD+10)
        SUPES= DATI(IPD+11)
C
        HRIF   =DATI(IPD+13)
        ISOLATO=DATI(IPD+14)
        DEQ    =DATI(IPD+15)
        SUPIN  =DATI(IPD+18)
C
C---decodifica variabili
C
        HNODO = XYU(IXYU  )
        PNODO = XYU(IXYU+1)
        TMMET = XYU(IXYU+2)
        IF(ISPU.EQ.1) THEN
          WDREN = XYU(IXYU+3)
          HDREN = XYU(IXYU+4)
        ENDIF
C
        I0=IXYU+2+2*ISPU
        DO J = 1,NE
          JW=2*J-1
          JH=JW+1
          WE(J) = XYU(I0+JW)
          HE(J) = XYU(I0+JH)
        END DO
        I0=I0+2*NE
        DO J = 1,NU
          JW=2*J-1
          JH=JW+1
          WU(J) = XYU(I0+JW)
          HU(J) = XYU(I0+JH)
        END DO
C
        TEST  = XYU(IXYU+2*(NE+NU)+3+2*ISPU)
        GAMES = XYU(IXYU+2*(NE+NU)+4+2*ISPU)*1000.
        IF(ISPU.EQ.1) ALZA  = XYU(IXYU+2*(NE+NU)+5+2*ISPU)
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
        P = PNODO*P0
        H = HNODO*H0
        C = W0*DTINT
C
        IF(ITERT.LE.0.AND.IFUN.EQ.2.OR.KREGIM) THEN
C____ AGGIORNAMENTO ENTROPIA
          S =SHEV(P,H,1)
          DATI(IPD+4)=S
C____ AGGIORNAMENTO PRESSIONE
          DATI(IPD+5)=P
C____ AGGIORNAMENTO TEMPERATURA METALLO
          DATI(IPD+12)=DATI(IPD+9)
        ENDIF
          SK =DATI(IPD+4)
          PK =DATI(IPD+5)
          TMK=DATI(IPD+12)
C
          S  =SHEV(P,H,1)
          Y  =YEV(P,S,1)
          T  =TEV(P,S,1)
          RO =ROEV(P,S,1)        
          DELTAP = 1.E-3* P
          IF(DELTP.LT.10.)DELTP=10.
          P1 = P - DELTP
          P2 = P + DELTP
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
       IF(ITERT.LE.0.AND.IFUN.EQ.2.OR.KREGIM) THEN
C
C____ QUI BISOGNA INTRODURRE IL CALCOLO DI UN COEFFCOEFF
C
          IF(Y.GT.1.) GAMI=1000.
          IF(Y.LT.1.AND.Y.GT.0.) GAMI = 15000.
          IF(Y.LT.0.)GAMI=1000.
          IF(SUME.LT.1.E-5) GAMI = 100.
          DATI(IPD+16)=GAMI
        ELSE
          GAMI= DATI(IPD+16)
        ENDIF
C
        GAMINT =SUPIN* GAMET*GAMI/(GAMET+GAMI)
        GAMEST =SUPES* GAMET*GAMES/(GAMET+GAMES)
C    
       IF(ISPU.EQ.1) THEN
C____ drenaggio del liquido
          TITOLO = Y
          IF(Y.LT.0.) TITOLO=0.
          IF(Y.GT.1.) TITOLO=1.
          WLIQ=ALZA*(RO*VOL*(1.-TITOLO)/1.)/W0 
          CALL SATUR(P,2,HLIQ,HVAP,1)
C
C______ test se calcolo di uno stazionario
        IF(KREGIM) GO TO 1000
C
C______ Integrazione equaz. energia nel metallo
          DEN=(1.+DTINT*(GAMINT+GAMEST)/CTMET)
          TM = (TMK+DTINT*(GAMINT*T/T0 + GAMEST*TEST)/CTMET)/DEN
          DATI(IPD+9)=TM
C----------------------------residui
          RNI(1)=VOL*RO*T*(S-SK)/W0/H0-DTINT*((SUMHE-SUME*HNODO
     $          -WDREN*(HDREN-HNODO))- GAMINT*(T-TM*T0)/W0/H0)
C______ Integrazione equaz. massa  nel fluido
          RNI(2)= VOL*(DRODP*(P-PK)+ DRODS*(S-SK))/W0-
     $            DTINT*(SUME+SUMU-WDREN)
          RNI(3)= TMMET-TM
          RNI(4)=WLIQ-WDREN
          RNI(5)=HLIQ/H0-HDREN
       ELSE
C______ Integrazione equaz. energia nel fluido
          RNI(1)=VOL*RO*T*(S-SK)/W0/H0-DTINT*((SUMHE-SUME*HNODO)-
     $                            GAMINT*(T-TM*T0)/W0/H0)
C______ Integrazione equaz. massa  nel fluido
          RNI(2)= VOL*(DRODP*(P-PK)+ DRODS*(S-SK))/W0-DTINT*(SUME+SUMU)
          RNI(3)= TMMET-TM
       ENDIF
       RETURN
C
C---calcolo dello stazionario
C
 1000   CONTINUE
C
       IF(ISPU.EQ.1) THEN
          RNI(1)=SUMHE+SUMU*HNODO - WDREN*HDREN
     $    - GAMINT*(T-TMMET*T0)/W0/H0
C______ Integrazione equaz. massa  nel fluido
          RNI(2)= SUME+SUMU-WDREN
          RNI(3)= (GAMEST*(TMMET-TEST)-GAMINT*(T/T0-TMMET))*T0/W0/H0
          RNI(4)=WLIQ-WDREN
          RNI(5)=HLIQ/H0-HDREN
       ELSE
          RNI(1) = SUMHE+SUMU*HNODO-GAMINT*(T-TMMET*T0)/W0/H0
          RNI(2) = SUME+SUMU
          RNI(3)= (GAMEST*(TMMET-TEST)-GAMINT*(T/T0-TMMET))*T0/W0/H0
       ENDIF
C
        DATI(IPD+4)=S        
        DATI(IPD+5)=P
        DATI(IPD+6)=S        
        DATI(IPD+7)=P
        DATI(IPD+9) =TMMET
        DATI(IPD+12)=TMMET
C
        RETURN
        END
C
        SUBROUTINE CALTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $   XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
        RETURN
        END     
