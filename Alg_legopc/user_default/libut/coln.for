C***********************************************************************
C*                                                                     *
C*                   VERSIONE MODIFICATA DA S.D.I.                     *
C*                          IL 29/5/1992                               *
C*                                                                     *
C***********************************************************************
C
      SUBROUTINE COLNI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/COLN01/IBLOC
      COMMON/COLN02/NE,NU
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'COLN'/
C
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI  (MASSIMO N=20)
C---PER FLUIDI COMPRIMIBILI MONO/BIFASE
C---IL COLLETTORE PUO' ESSERE COMPLETAMENTE INTERCETTATO.
C--------------ROSSI-21/4/89---------------------
C      CAMBIATA EQUAZIONE MASSA
C      DA CARICARE CON LEGSIS MODIFICATA
C        FILE:   [ANSA.COLLE]COLX.FOR
C------------------------------------------------
C
C
      CALL COLNI4(IOB,MOD)
C
C
      NSTATI=0
      NUSCIT=2
      NINGRE=2*(NE+NU)
      NVAR=NINGRE+2
C
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('HCOL',A4,2X,'--UA-- ENTALPIA MEDIA DEL NODO')
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('PCOL',A4,2X,'--UA-- PRESSIONE NEL NODO')
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
C
      RETURN
      END
      SUBROUTINE COLNI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/COLN01/IBLOC
      COMMON/COLN02/NE,NU
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
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
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
      SUBROUTINE COLNI1(IFUN,K,IBL1,IBL2,NSTATI,NUSCIT,NINGRE)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI  (MASSIMO N=20)
C---PER FLUIDI COMPRIMIBILI MONO/BIFASE
C---IL COLLETTORE PUO' ESSERE COMPLETAMENTE INTERCETTATO.
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        SAVE NE,NU,NT,KOSA
C
        GO TO(100,200), IFUN
C
  100   WRITE(6,500)'COLLETTORE DI DISTRIBUZIONE A N TUBI'
C
   11   WRITE(6,500)'FORNISCI IL NUMERO DI TUBI ENTRANTI NEL COLLETTORE'
        READ(5,*)NE
        IF(NE.LE.0)GO TO 11
        IF(NE.LE.10)GO TO 21
        WRITE(6,500)'MASSIMO NUMERO DI TUBI ENTRANTI = 10'
        GO TO 11
C
   21   WRITE(6,500)'FORNISCI IL NUMERO DI TUBI USCENTI DAL COLLETTORE'
        READ(5,*)NU
        IF(NU.LE.0)GO TO 21
        IF(NU.LE.10)GO TO 31
        WRITE(6,500)'MASSIMO NUMERO DI TUBI USCENTI = 10'
        GO TO 21
C
   31   CONTINUE
        NSTATI = 0
        NUSCIT = 2
        NINGRE = 2*(NU+NE)
        NT=1
        KOSA=0
        RETURN
C
  200   CONTINUE
        IF(K.EQ.1)            WRITE(6,501)'NESSUNA VARIABILE DI STATO'
        IF(K.EQ.NSTATI+1)     WRITE(6,501)'VARIABILI DI USCITA'
        IF(K.EQ.NSTATI+NUSCIT+1)WRITE(6,501)'VARIABILI DI INGRESSO'
C
        IF(K.GT.2)GO TO 9
        GO TO (1,2),K
C uscite
  1     WRITE(6,502)'ENTALPIA DEL NODO'
        GO TO 400
C
  2     WRITE(6,502)'PRESSIONE NEL NODO'
                                        
        GO TO 400
C ingressi
  9     KI=1
        IF(NT.GT.NE) KI=3
        KI=KI+KOSA
C
        GO TO (3,4,5,6),KI
C
  3     WRITE(6,*)'PORTATA TUBO ',NT,' ENTRANTE'
        KOSA=1
        GO TO 400
  4     WRITE(6,*)'ENTALPIA ASSOCIATA CORRISPONDENTE'
        KOSA=0
        NT=NT+1
        GO TO 400
  5     WRITE(6,*)'PORTATA TUBO ',NT,'USCENTE'
        KOSA=1
        GO TO 400
  6     WRITE(6,*)'ENTALPIA ASSOCIATA CORRISPONDENTE'
        KOSA=0
        NT=NT+1
        GO TO 400
C
  400   RETURN
C
500     FORMAT(//10X,A//)
501     FORMAT(//20X,A//)
502     FORMAT(14X,A)
        END
        SUBROUTINE COLNI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     1                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        INTEGER VAR
        DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
        PARAMETER (MAX=40)
        DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C
        GO TO(100,200),IFUN
C
  100   WRITE(14,500)    'NU.TU.EN    '
     1                  ,'NU.TU.US    '
     1                  ,'VOLUME      '
     1                  ,'CTMET       '
     1                  ,'TEMP. EST.  '
     1                  ,'HSC*S       '
        RETURN
C
C---lettura e memorizzazione dati
C
  200   READ(14,502)
        READ(14,502)     FNE
     1                  ,FNU
     1                  ,VOLUME
     1                  ,CTMET
     1                  ,TRIF
     1                  ,COSCE
C
  500   FORMAT(3(4X,A8,' =',10X,'*'))
  502   FORMAT(3(14X,F10.2,1X))
C
C____ DETERMINAZIONE SE IL COLLETTORE E` ISOLATO DAGLI ALTRI
C     COMPONENTI IDRAULICI  (SISTEMA CHIUSO)
C
        NE= FNE
        NU= FNU
        SUME=0.
        SUMU=0.
        I0=IV1+1
        DO J = 1,NE
          JW=2*J-1
          WE(J) = XYU(I0+JW)
          IF(WE(J).GT.0.)            THEN
            SUME=SUME+WE(J)
                                     ELSE
            SUMU=SUMU+WE(J)
          ENDIF
        END DO
C
        I0=I0+2*NE
        DO J = 1,NU
          JW=2*J-1
          WU(J) = XYU(I0+JW)
          IF(WU(J).LT.0.)            THEN
            SUME=SUME-WU(J)
                                     ELSE
            SUMU=SUMU-WU(J)
          ENDIF
        END DO
C______________________________________________
C
          HRIF=XYU(IV1  )
          PRIF=XYU(IV1+1)
C
        IF(SUME.LE.1.E-2) THEN
C__ LA SOMMA DELLE PORTATE ENTRANTI E` 0. (PUO` ESSERE ISOLATO)
          IF(PRIF.LE.610.) THEN
C-- IL NODO E` STATO DEFINITO ISOLATO
             ISOLATO=1
               IF(COSCE.LE.0.) THEN
C______PER NODO ADIABATICO LA PRESSIONE DI RIFER. E` 1. BAR
                  PRIF=1.E5
                  IF(COSCE.LT.0.)HRIF=2550.E3
               ELSE
                  PRIF= PSATT(TRIF)
C
C__ SE IL TITOLO (HRIF-HWS)/(HVS-HWS) DI PRIF E` < .5 NEL
C     COLLETTORE C'E` ACQUA , ALTRIMENTI VAPORE
C
                 CALL SATUR(PRIF,2,HWS,HVS,1)
                 YY = (HRIF-HWS)/(HVS-HWS)
                  IF(YY.LT..5) THEN
                   HRIF=HWS
                  ELSE
                   HRIF=HVS
                  ENDIF
               ENDIF
          ELSE
C
             IF(COSCE.LE.0.) THEN
C____ SE IL NODO E` ADIABATICO E LA PRESS. E` DIVERSA DA 1.E5
C      NON E` ISOLATO
               IF(ABS(PRIF-1.E5).LT.100.) THEN
                 ISOLATO=1.
               ELSE
                 ISOLATO=0
               ENDIF
             ELSE
               PRIF0= PSATT(TRIF)
               IF(ABS(PRIF-PRIF0).LT.100.) THEN
C-- IL NODO E` ISOLATO
                 ISOLATO=1
               ELSE
C-- IL NODO NON E` ISOLATO
                 ISOLATO=0
               ENDIF
             ENDIF
          ENDIF
        ELSE
        ISOLATO=0
        ENDIF
        XYU(IV1  )=HRIF
        XYU(IV1+1)=PRIF
C
C ! numero tubi entranti
        DATI(ID2  ) = FNE
C ! numero tubi uscenti
        DATI(ID2+1) = FNU
        DATI(ID2+2) = VOLUME
C ! cap. ter. metallo
        DATI(ID2+3) = CTMET
C ! entropia passo precedente
C       DATI(ID2+4) = Sk
C ! PRESSIONE PASSO PRECEDENTE
C       DATI(ID2+5) = PK
C ! ENTROPIA PASSO CORRENTE
C       DATI(ID2+6) = S
C ! PRESSIONE PASSO CORRENTE
C       DATI(ID2+7) = P
        DATI(ID2+8) = PRIF
        DATI(ID2+9) = TRIF
C ! coef. sc. th. esterno
        DATI(ID2+10)= COSCE
C        DATI(ID2+11)= TMK
C        DATI(ID2+12)= TM
        DATI(ID2+13)= HRIF
        DATI(ID2+14)= ISOLATO
        ID2 = ID2+14
        NU=FNU
        NE=FNE
C
C---costanti di normalizzazione
C
        CNXYU(IV1  ) = H0
        CNXYU(IV1+1) = P0
        NT=NE+NU
        I0=IV1+1
        DO J = 1,NT
        JW=2*J-1
        JH=JW+1
        CNXYU(I0+JW) = W0
        CNXYU(I0+JH) = H0
        ENDDO
C
        RETURN
        END
        SUBROUTINE COLNC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C   CALCOLO RESIDUI
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
        PARAMETER (MAX=40)
        DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                        !SNGL
C        COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                 !DBLE
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
        EXTERNAL COLN
C
C
C
C
        GO TO(100,200,3000),IFUN
C
C---topologia jacobiano
C
  100   NE=DATI(IPD)
        NU=DATI(IPD+1)
        NVAR=2*(NE+NU)+2
        DO I=1,2
        DO J =1,NVAR
        AJAC(I,J) = 1.
        END DO
        END DO
        RETURN
C
C---calcolo residui
C
  200   CONTINUE
        CALL COLN(IFUN,IXYU,XYU,IPD,DATI,RNI)
        RETURN
C
C---calcolo jacobiano
C
 3000   CONTINUE
        NE=DATI(IPD)
        NU=DATI(IPD+1)
        VOL=DATI(IPD+2)
        COSCE= DATI(IPD+10)
        NVAR=2*(NE+NU)+2
C
      IF(KREGIM) GO TO 3500
C
C___ COLLETTORE ALGEBRICO  ==> COSCE <0.
C
      IF(COSCE.LT.0.) GO TO 2000
C
C---------calcolo jacobiano NUMERICO per il transitorio
C
      NSTATI=0
      NUSCIT = 2
      NINGRE = NVAR-2
      EPS   =1.E-3
      EPSLIM=1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $             NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,COLN)
      RETURN
C
C____ COLLETTORE ALGEBRICO
C
 2000   CONTINUE
        HNODO = XYU(IXYU  )
        PNODO = XYU(IXYU+1)
C
C______ PROTEZIONE PER PRESSIONI ED ENTALPIE SBALLATE
C
        PP=PNODO*P0
        HH=HNODO*H0
        IF(PP.GT.400.E5) THEN
          PNODO=400.E5/P0
        ELSE IF(PP.LT.610.) THEN
          PNODO=610./P0
        ENDIF
        IF(HH.GT.4200.E3) THEN
          HNODO=4200.E3/H0
        ELSE IF(HH.LT.0.) THEN
          HNODO=0.
        ENDIF
C
C
        I0=IXYU+1
        DO J = 1,NE
          JW=2*J-1
          JH=JW+1
          WE(J) = XYU(I0+JW)
          HE(J) = XYU(I0+JH)
        END DO
C
        I0=I0+2*NE
        DO J = 1,NU
          JW=2*J-1
          JH=JW+1
          WU(J) = XYU(I0+JW)
          HU(J) = XYU(I0+JH)
        END DO
C
C----------------------------flussi dimassa ed energia
C
        SUME=0.
        DO J= 1,NE
          JW=2+2*J-1
          JH=JW+1
          IF(WE(J).GT.0.)            THEN
            SUME=SUME+WE(J)
            AJAC(1,JW)=-HE(J)+HNODO
            AJAC(1,JH)=-WE(J)
            AJAC(2,JW)=-1.
                                     ELSE
            AJAC(2,JW)=1.
          ENDIF
        END DO
C
C
C
        K2=2*(1+NE)
        DO J= 1,NU
          JW=K2+2*J-1
C
          IF(WU(J).LT.0.)            THEN
            SUME=SUME-WU(J)
            AJAC(1,JW)=-HU(J)
            AJAC(1,JH)= WU(J)
            AJAC(2,JW)=-1.
                                     ELSE
            AJAC(2,JW)=1.
          ENDIF
        END DO
C-----------------------------------termine diagonale
        P=PNODO*P0
        H=HNODO*H0
C
        AJAC(1,1)=SUME
C
C
C____ TEST PER SAPERE SE IL NODO E` ISOLATO
C
        IF(SUME.LE.1.E-5.AND.ABS(SUMU).LE.1.E-5) THEN
             AJAC(1,1)=1.
        ENDIF
C-----------------------------------equazione delle portate
        K1=3
        K2=2+2*NE
        DO J=K1,K2,2
        AJAC(2,J) = -1.
        END DO
        K1=K2+1
        DO J=K1,NVAR,2
        AJAC(2,J) = 1.
        END DO
C
      RETURN
C
 3500   CONTINUE
C
C---------calcolo jacobiano per il REGIME
C
        HNODO = XYU(IXYU  )
        PNODO = XYU(IXYU+1)
        PRIF  = DATI(IPD+8)
        HRIF  = DATI(IPD+13)
        ISOLATO=DATI(IPD+14)
C
        I0=IXYU+1
        DO J = 1,NE
          JW=2*J-1
          JH=JW+1
          WE(J) = XYU(I0+JW)
          HE(J) = XYU(I0+JH)
        END DO
C
C
C
        I0=I0+2*NE
        DO J = 1,NU
          JW=2*J-1
          JH=JW+1
          WU(J) = XYU(I0+JW)
          HU(J) = XYU(I0+JH)
        END DO
C
C----------------------------flussi dimassa ed energia
C
        SUME=0.
        DO J= 1,NE
          JW=2+2*J-1
          JH=JW+1
          IF(WE(J).GT.0.)            THEN
            SUME=SUME+WE(J)
            AJAC(1,JW)=-HE(J)+HNODO
            AJAC(1,JH)=-WE(J)
            AJAC(2,JW)=-1.
                                     ELSE
            AJAC(2,JW)=1.
          ENDIF
        END DO
C
C
C
        K2=2*(1+NE)
        DO J= 1,NU
          JW=K2+2*J-1
C
          IF(WU(J).LT.0.)            THEN
            SUME=SUME-WU(J)
            AJAC(1,JW)=-HU(J)
            AJAC(1,JH)= WU(J)
            AJAC(2,JW)=-1.
                                     ELSE
            AJAC(2,JW)=1.
          ENDIF
        END DO
C-----------------------------------termine diagonale
        P=PNODO*P0
        H=HNODO*H0
C
C____ TEST PER SAPERE SE IL NODO E` ISOLATO
C
        IF(ISOLATO.EQ.1) THEN
          AJAC(1,1)=1.
        ELSE
          S=SHEV(P,H,1)
          Y  =YEV(P,S,1)
          YC =0.5
          CP=CPEV(P,S,Y,YC,1)
          GAM=500.*(1.-Y)+200.
          GAM=GAM*VOL**(2./3.)
C
C___ NODO ADIABATICO E ALGEBRICO
C
          AJAC(1,1)=SUME+ GAM/CP/W0
        ENDIF
C-----------------------------------equazione delle portate
        K1=3
        K2=2+2*NE
        DO J=K1,K2,2
        AJAC(2,J) = -1.
        END DO
        K1=K2+1
        DO J=K1,NVAR,2
        AJAC(2,J) = 1.
        END DO
C
C____ TEST PER SAPERE SE IL NODO E` ISOLATO
C
        IF(ISOLATO.EQ.0)RETURN
C----------------------------------jacobiano per nodo isolato
        DO J=1,NVAR
        AJAC(2,J)=0.
        ENDDO
        AJAC(2,2)=1.
C
        RETURN
        END
        SUBROUTINE COLN(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
C---COLLETTORE DI DISTRIBUZIONE A N TUBI
C   CALCOLO RESIDUI
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        DIMENSION XYU(*),DATI(*),RNI(*)
        PARAMETER (MAX=40)
        DIMENSION WE(MAX),WU(MAX),HE(MAX),HU(MAX)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                        !SNGL
C        COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                 !DBLE
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
C
C---calcolo residui
C
C
C---decodifica dati
C
        NE   =DATI(IPD   )
        NU   =DATI(IPD+1 )
        VOL  =DATI(IPD+2 )
        CTMET=DATI(IPD+3 )
        PRIF = DATI(IPD+8)
        TRIF = DATI(IPD+9)
        COSCE= DATI(IPD+10)
        HRIF = DATI(IPD+13)
        ISOLATO=DATI(IPD+14)
C
C---decodifica variabili
C
        HNODO = XYU(IXYU  )
        PNODO = XYU(IXYU+1)
        I0=IXYU+1
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
C----------------------------flussi dimassa ed energia
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
C----------------------------stazionario o transitorio ?
        IF(KREGIM) GO TO 1000
C----------------------------calcolo transitorio
C
C___ COLLETTORE ALGEBRICO  ==> COSCE <0.
C
        IF(COSCE.LT.0.) GO TO 2000
C
        IF(ITERT.LE.0.AND.IFUN.EQ.2) THEN
C____ AGGIORNAMENTO ENTROPIA
          S =SHEV(P,H,1)
          DATI(IPD+4)=S
C____ AGGIORNAMENTO PRESSIONE
          DATI(IPD+5)=P
C____ AGGIORNAMENTO TEMPERATURA METALLO
          DATI(IPD+11)=DATI(IPD+12)
        ENDIF
          SK=DATI(IPD+4)
          PK=DATI(IPD+5)
          TMK=DATI(IPD+11)
C
          S =SHEV(P,H,1)
          Y  =YEV(P,S,1)
          T  =TEV(P,S,1)
          RO=ROEV(P,S,1)
          DRODP=1./A2EV(P,S,1)
          DRODS=BEV(P,S,1)
C
          GAM=500.*(1.-Y)+200.
          GAM=GAM* VOL**(2./3.)
C
C______ Integrazione equaz. energia nel metallo
          DEN=(1.+DTINT*(GAM+COSCE)/CTMET)
          TM  = (TMK+DTINT*(GAM*T + COSCE*TRIF)/CTMET)/DEN
          DATI(IPD+12)=TM
C----------------------------residui
        RNI(1)=VOL*RO*T*(S-SK)/W0/H0-DTINT*((SUMHE-SUME*HNODO)
     $                               -GAM*(T-TM)/W0/H0)
        RNI(2)=VOL*(DRODP*(P-PK)+ DRODS*(S-SK))/W0-DTINT*(SUME+SUMU)
        RETURN
C
 2000   CONTINUE
C
C____ COLLETTORE ALGEBRICO
C
C____ TEST PER SAPERE SE IL NODO E` ISOLATO
C
        IF(SUME.LE.1.E-5.AND.ABS(SUMU).LE.1.E-5) THEN
              RNI(1)=0.
              RNI(2)=SUME+SUMU
        ELSE
              RNI(1) = SUMHE-SUME*HNODO
              RNI(2) = SUME+SUMU
        ENDIF
C
        RETURN
C
C---calcolo dello stazionario
C
 1000   CONTINUE
C
C
C____ TEST PER SAPERE SE IL NODO E` ISOLATO
C
        IF(ISOLATO.EQ.1) THEN
              TM=TRIF
              RNI(1)=HRIF/H0-HNODO
              RNI(2)=PRIF/P0-PNODO
        ELSE
          S=SHEV(P,H,1)
          RO=ROEV(P,S,1)
          Y  =YEV(P,S,1)
          T  =TEV(P,S,1)
          GAM=500.*(1.-Y)+200.
          GAM=GAM*VOL**(2./3.)
C
C___ NODO ADIABATICO E ALGEBRICO
          IF(COSCE.LT.0.) GAM=0.
C
          TM= (GAM*T+COSCE*TRIF)/(GAM+COSCE)
             RNI(1) = SUMHE-SUME*HNODO-GAM*(T-TM)/W0/H0
             RNI(2) = SUME+SUMU
        ENDIF
C
        DATI(IPD+4)=S
        DATI(IPD+5)=P
        DATI(IPD+6)=S
        DATI(IPD+7)=P
        DATI(IPD+11)=TM
        DATI(IPD+12)=TM
C
        RETURN
        END
      REAL FUNCTION PSATT(T)                                            !SNGL
C      DOUBLE PRECISION FUNCTION PSATT(T)                                !DBLE
C
C     CALCOLA LA PRESSIONE DI SATURAZIONE
C     DATA LA TEMPERATURA T
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PSAT = 1000.
      ITER=0
C____   NEWTON
   8  IF(PSAT.LT.610.) PSAT=610.
      CALL SATUR(PSAT,7,TSAT,ZOT,1)
C____ RESIDUO
      RES=T-TSAT
C____ TEST DI CONVERGENZA
      IF(ABS(RES).LT..1) GO TO 10
      IF(ITER.GT.100) THEN
         WRITE(6,*)'PSATT NON CONVERGE'
         GO TO 10
      ENDIF
C____ DERIVATA
      DP=PSAT/10.
      CALL SATUR(PSAT+DP,7,TSATDP,ZOT,1)
      DTDP=(TSATDP-TSAT)/DP
      DELTAP=RES/DTDP
C____ AGGIORNAMENTO DI PSAT
      PSAT = PSAT + DELTAP
      ITER=ITER+1
      GO TO 8
 10   PSATT=PSAT
      RETURN
      END
