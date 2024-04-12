C*********************************************************************
C       Fortran Source:             vapo1.f
C       Subsystem:              1
C       Description:
C       %created_by:    famgr %
C       %date_created:  Mon Apr 29 09:08:01 1996 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_vapo1_f
      CHARACTER*80  RepoID
      COMMON /CM_vapo1_f / RepoID
      DATA RepoID/'@(#)1,fsrc,vapo1.f,2'/
      END
C**********************************************************************
      SUBROUTINE CONTRO (P,S)
      COMMON/CONT/PD,SD
      IF(P-PD) 3,1,3
    1 IF(S-SD) 4,2,4
    2 RETURN
C********************************
    3 ND=3
      IF(P.LT.610.) THEN
        CALL DIAGN (ND,S,P)
        P=610.
      ENDIF
C********************************
      PD=P
      CALL TABLE
    4 ND=1
      IF(S.LT.(-.2)) THEN
        CALL DIAGN (ND,S,P)
        S=-.2
      ENDIF
C********************************
      SD=S
      CALL CALSR
      RETURN
      END
      SUBROUTINE PRST (TETA,BETS)
      DOUBLE PRECISION CK
      COMMON/TSAT/CK(9)
      DIFT=1.-TETA
      TNUM=0.
      DO 1 I=1,5
    1 TNUM=TNUM+CK(I)*DIFT**I
      DNUM=1.
      DO 2 I=1,2
    2 DNUM=DNUM+CK(I+5)*DIFT**I
      BETS=EXP(1./TETA*TNUM/DNUM-DIFT/(CK(8)*DIFT**2+CK(9)))
      RETURN
      END
      FUNCTION ROEV (P,S,NFL)
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      COMMON/THER/IPHA,IN,TITRE
      DIMENSION V(2)
      CALL CONTRO (P,S)
      ID=IN+1
      IF(IPHA.EQ.1) GO TO 3
      NWT=1
      CALL NEWT (NWT,ROEV)
      ROEV=ROEV
      RETURN
    3 DO 5 I=1,2
      NWT=0
      CALL NEWT (NWT,V(I))
    5 ID=IN+7
      ROEV=1./(V(1)*(1.-TITRE)+V(2)*TITRE)
      RETURN
      END
      FUNCTION TEV (P,S,NFL)
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      COMMON/THER/IPHA,IN,TITRE
      CALL CONTRO (P,S)
      ID=IN+2
      NWT=1
      IF(IPHA.EQ.1) NWT=0
      CALL NEWT (NWT,TEV)
      TEV=TEV
      RETURN
      END
      FUNCTION HEV (P,S,NFL)
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      COMMON/THER/IPHA,IN,TITRE
      DIMENSION V(2)
      CALL CONTRO (P,S)
      ID=IN+3
      IF(IPHA.EQ.1) GO TO 3
      NWT=1
      CALL NEWT (NWT,HEV)
      HEV=HEV
      RETURN
    3 DO 5 I=1,2
      NWT=0
      CALL NEWT (NWT,V(I))
    5 ID=IN+9
      HEV=V(1)*(1.-TITRE)+V(2)*TITRE
      RETURN
      END
      FUNCTION A2EV (P,S,NFL)
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      COMMON/THER/IPHA,IN,TITRE
      DIMENSION V(2)
      CALL CONTRO (P,S)
      IF(IPHA.EQ.1) GO TO 3
      ID=IN+4
      NWT=1
      CALL NEWT (NWT,A2EV)
      A2EV=A2EV
      RETURN
    3 L=1
    4 ID=IN+L
      DO 6 I=1,2
      NWT=0
      CALL NEWT (NWT,V(I))
    6 ID=IN+L+6
      IF(L.GT.1) GO TO 7
      VOL=V(1)*(1.-TITRE)+V(2)*TITRE
      L=4
      GO TO 4
    7 A2EV=VOL*VOL/(V(1)*(1.-TITRE)+V(2)*TITRE)
      RETURN
      END
      FUNCTION BEV (P,S,NFL)
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      COMMON/THER/IPHA,IN,TITRE
      DIMENSION V(2)
      CALL CONTRO (P,S)
      IF(IPHA.EQ.1) GO TO 3
      ID=IN+5
      NWT=1
      CALL NEWT (NWT,BEV)
      BEV=BEV
      RETURN
    3 L=1
      M=2
    4 ID=IN+L
      DO 6 I=1,M
      NWT=0
      CALL NEWT (NWT,V(I))
    6 ID=IN+L+6
      IF(L.GT.1) GO TO 7
      RHO=1./(V(1)*(1.-TITRE)+V(2)*TITRE)
      L=5
      M=1
      GO TO 4
    7 BEV=V(1)*RHO*RHO
      RETURN
      END
      FUNCTION CPEV (P,S,Y,YC,NFL)
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      COMMON/THER/IPHA,IN,TITRE
      CALL CONTRO (P,S)
      IF(IPHA.EQ.1) GO TO 3
      I=1
    1 ID=IN+6
    2 CALL NEWT (I,CPEV)
      CPEV=CPEV
      RETURN
    3 I=0
      IF(Y-YC) 1,1,4
    4 ID=IN+12
      GO TO 2
      END
      FUNCTION YEV (P,S,NFL)
      COMMON/THER/IPHA,IN,TITRE
      CALL CONTRO (P,S)
      YEV=TITRE
      RETURN
      END
      SUBROUTINE SATUR (P,NCAL,RES1,RES2,NFL)
      COMMON/CONT/PD,SD
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      DIMENSION R(2)
      IF(P.GT.221.2E5) GO TO 7
      IF(P-PD) 1,2,1
C********************************
    1 ND=3
      IF(P.LT.610.) THEN
        CALL DIAGN (ND,SD,P)
        P=610.
      ENDIF  
C********************************
      PD=P
      SD=-.1
      CALL TABLE
    2 IF(NCAL-7) 4,3,3
    3 IN=NCAL+INCR+1
      N=1
      GO TO 5
    4 IN=NCAL+INCR-6
      N=2
    5 DO 6 I=1,N
      ID=IN
      NWT=0
      CALL NEWT (NWT,FONC)
      R(I)=FONC
    6 IN=IN+3
      RES1=R(1)
      RES2=R(2)
      R(2)=0.
      RETURN
C********************************
    7 ND=5
      CALL DIAGN (ND,SD,P)
      P=221.2E+05
C********************************
      RETURN
      END
      FUNCTION ETEV(P,T,R,RA,Y,YC,NFL)
      DOUBLE PRECISION  A,B,C,D,COE1,COE2,COE3,ETA1,ETA2
      COMMON/VISC/A(5),B(3),C(3),D(3),COE1,COE2,COE3,ETA1,ETA2,ET1(14),E
     &T2(14),ET3(14),ET4(10)
      COMMON/COMU/PTS(23),TES(14)
      IT=1
      TETA=T/647.3
      IF(T-573.15) 1,1,4
    1 IF(Y-YC) 2,2,5
    2 AAAA=(A(2)/(TETA-A(3)))
      ETEV=A(1)*10.**AAAA
      IF(Y) 3,3,11
    3 CALL PRST (TETA,BETS)
      ETEV=ETEV*(1.+(P/221.2E5-BETS)*A(4)*(TETA-A(5)))
      GO TO 11
    4 IT=0
    5 RHOR=R*.317E-2
      ETEV=B(1)*(TETA-B(2))+B(3)
      IF(IT.EQ.0) GO TO 8
      IF(Y-1.) 6,7,7
    6 RHOR=RHOR*((1.-Y)/RA+Y)
    7 ETEV=ETEV-RHOR*(C(1)-C(2)*(TETA-C(3)))
      GO TO 11
    8 IF(T-648.15) 12,9,9
    9 DO 10 I=1,3
   10 ETEV=ETEV+D(I)*RHOR**I
   11 ETEV=ETEV*1.E-7
      RETURN
   12 IF(P-PTS(1)) 22,22,13
   13 DO 19 I=2,14
      IF(P-PTS(I)) 14,14,19
   14 N1=I-1
      N2=I
      PRO=(P-PTS(N1))/(PTS(N2)-PTS(N1))
      IF(Y-YC) 15,15,17
   15 ETEV=ET1(N1)*(1-PRO)+ET1(N2)*PRO
      IF(Y) 16,16,11
   16 ETS=ETEV
      TS=TES(N1)*(1-PRO)+TES(N2)*PRO
      GO TO 23
   17 ETEV=ET2(N1)*(1-PRO)+ET2(N2)*PRO
      IF(Y-1.) 11,18,18
   18 ETE=ETEV
      ETS=ET3(N1)*(1-PRO)+ET3(N2)*PRO
      TE=TES(N1)*(1-PRO)+TES(N2)*PRO
      TS=648.15
      GO TO 25
   19 CONTINUE
      DO 21 I=15,23
      IF(P-PTS(I)) 20,20,21
   20 ETS=ET4(I-14)+(ET4(I-13)-ET4(I-14))*(P-PTS(I-1))/(PTS(I)-PTS(I-1))
      TS=648.15
      GO TO 23
   21 CONTINUE
   22 ETE=ETA2-RHOR*COE3
      ETS=ETA1+D(1)*RHOR+D(2)*RHOR**2+D(3)*RHOR**3
      TS=648.15
      GO TO 24
   23 ETE=COE1*(1.+(P-PTS(1))/221.2E5*COE2)
   24 TE=573.15
   25 CONTINUE
      IF (ABS(TS-TE).LE.1.E-5) THEN
	ETEV=ETS
      ELSE
        ETEV=(((ETS-ETE)/(TS-TE)*(T-TE))+ETE)
      ENDIF
      GO TO 11
      END
      FUNCTION ALEV (P,T,R,RA,Y,YC,NFL)
      DOUBLE PRECISION PA,PB,PC,ALAM,ALBM,ALCM
      COMMON/COND/PA(5),PB(4),PC(4),ALE(9),ALV(10),AL2(21),ALAM,ALBM,ALC
     &M
      COMMON/COMU/PTS(23),TES(14)
      IT=1
      TETA=T/647.3
      IF(T-623.15) 1,1,8
    1 IF(Y-YC) 2,2,6
    2 ALEV=PA(1)
      DO 3 I=2,5
    3 ALEV=ALEV+PA(I)*TETA**(I-1)
      IF(Y) 4,4,29
    4 AMO1=PB(1)
      AMO2=PC(1)
      DO 5 I=2,4
      TT=TETA**(I-1)
      AMO1=AMO1+PB(I)*TT
    5 AMO2=AMO2+PC(I)*TT
      CALL PRST (TETA,BETS)
      DIFB=P/221.2E5-BETS
      ALEV=ALEV+DIFB*AMO1+DIFB**2*AMO2
      GO TO 29
    6 IF(Y-1.) 7,9,9
    7 DELTA=(R*((1-Y)/RA+Y))*1.E-3
      GO TO 35
    8 IT=0
      TE=623.15
    9 DELTA=R*1.E-3
      IF(IT.EQ.1) GO TO 35
      IF(P.GT.350.E5) GO TO 11
      IF(P.GT.275.E5) GO TO 12
      IF(P.GT.225.E5) GO TO 13
      IF(P.GT.221.2E5)GO TO 14
      IF(P.GT.PTS(6)) GO TO 26
      GO TO 35
   11 IF(T-773.15) 15,35,35
   12 IF(T-723.15) 16,35,35
   13 IF(T-698.15) 17,35,35
   14 IF(T-673.15) 18,35,35
   15 N1=23
      N2=23
      N3=3
      TS=773.15
      GO TO 30
   16 N1=20
      N2=22
      N3=2
      TS=723.15
      GO TO 30
   17 N1=16
      N2=19
      N3=1
      TS=698.15
      GO TO 30
   18 N1=15
      N2=15
      N3=0
      TS=673.15
      GO TO 30
   19 DO 25 I=7,14
      IF(P-PTS(I)) 20,20,25
   20 PRO=(P-PTS(I-1))/(PTS(I)-PTS(I-1))
      IF(Y-YC) 21,21,23
   21 ALEV=ALE(I-6)*(1-PRO)+ALE(I-5)*PRO
      IF(Y) 22,22,29
   22 ALS=ALEV
      TS=TES(I-1)*(1-PRO)+TES(I)*PRO
      GO TO 33
   23 ALEV=ALV(I-6)*(1-PRO)+ALV(I-5)*PRO
      IF(Y-1.) 29,24,24
   24 ALI=ALEV
      TE=TES(I-1)*(1-PRO)+TES(I)*PRO
      ALS=AL2(I-6)*(1-PRO)+AL2(I-5)*PRO
      TS=673.15
      GO TO 34
   25 CONTINUE
   26 IF(T-673.15) 19,35,35
   29 RETURN
   30 DO 32 I=N1,N2
      IF(P-PTS(I)) 31,31,32
   31 N4=I-6+N3
      ALS=AL2(N4)+(AL2(N4+1)-AL2(N4))*(P-PTS(I-1))/(PTS(I)-PTS(I-1))
      GO TO 33
   32 CONTINUE
   33 DIFB=(P-PTS(6))/221.2E5
      ALI=ALAM+DIFB*ALBM+DIFB**2*ALCM
   34 ALEV=(((ALS-ALI)/(TS-TE)*(T-TE))+ALI)
      GO TO 29
   35 TT=T-273.15
      IF(TT.LE.0.) TT=.1
      AL1=17.6+5.87E-2*TT+1.04E-4*TT**2-4.51E-8*TT**3
      ALEV=(AL1+(103.51+.4198*TT-2.771E-5*TT**2)*DELTA+2.1482E14/TT**4.2
     &*DELTA**2)*1.E-3
      GO TO 29
      END
      FUNCTION SHEV(P,H,NFL)
C
C  CALCOLA S(P,H) CON LE TAVOLE COMPLETE
C
      COMMON/THER/IPHA,IN,TITRE
      COMMON/CONT/PD,SD
      COMMON/INTE/ID,IP,XY(4),INCR,PAE,PAI
      DIMENSION SWV(2)
      INTEGER NON
C
C  CONTROLLA P MIN. E CARICA LA REGIONE
C
      CALL CHI(P)
C
C  INDIVIDUA L'ISOCLINA E CALCOLA IL TITOLO
C
      CALL CERCA(H,S0,NON)
	pippo=H+1.
	pippo=S0+1.
C--- NON =1 SE FUORI DALLE TAVOLE
      IF(NON.EQ.1) THEN
        SD=S0
        GO TO 3
      ENDIF
C
      IF(IPHA.EQ.1) GO TO 1
C
C  NON SATURO : INVERTE INTERPOLAZIONE IN S
C
      ID=IN+3
      CALL TROVA(H,S0)
      GO TO 3
C
C  SATURO : CALCOLA S CON IL TITOLO
C
    1 DO 2 I=1,2
      ID=INCR-6+I*I
      NWT=0
      CALL NEWT(NWT,SWV(I))
    2 CONTINUE
      SD=SWV(1)*(1.-TITRE)+SWV(2)*TITRE
C
    3 SHEV=SD
      RETURN
      END
      SUBROUTINE CHI(P)
      COMMON/CONT/PD,SD
C
      IF(P-PD) 1,2,1
C
C  CONTROLLA IL VALORE MINIMO DI P
C
C********************************
    1 ND=6
      IF(P.LT.610.) THEN
        CALL DIAGN(ND,H,P)
        P=610.
      ENDIF
      IF(P.GT.400.E5) THEN
        CALL DIAGN(ND,H,P)
        P=400.E5
      ENDIF
C********************************
      PD=P
C
C  CARICA IN MEMORIA LA REGIONE CHE CONTIENE PD
C
      CALL TABLE
C
    2 RETURN
      END
C**********************************************************************
      FUNCTION PSATEV(T,ID)
C
C
C     CALCOLA LA PRESSIONE DI SATURAZIONE   
C
C     DATA LA TEMPERATURA T
C
C  ID = 1 H2O
C  ID = 2 AMMONIACA
C  ID = 6 FREON
C
C      COMMON /PT1/ P(97,6)
C
      PSATEV = ((T-273.15)/100.)**4. *100000.
C   NEWTON
   8  CALL SATUR(PSATEV,7,TSAT,TVAP,ID)
      DP = 4. *(T-273.15)**3. *1.E-3 *(T-TSAT)
      PSATEV = PSATEV + DP
C      IF (PSATEV .LT. P(1,ID)) PSATEV = P(1,ID)
      IF(ABS(DP/PSATEV).GT.1.E-4)GOTO 8
      RETURN
      END
C**********************************************************************
      FUNCTION STEV(P,T,Y,N)
C
C     CALCOLA L' ENTROPIA   DATI:
C
C     PRESSIONE   P
C     TEMPERATURA T
C     TITOLO      Y
C

      if(P.GT.221.2E5)then
	      TSAT=647.
	      STEV = ENTROP(P,T,TSAT)
      else
C
	        CALL SATUR(P,7,TSAT,Z,N)
		IF(Y.EQ.0.) THEN
C--- ACQUA SOTTORAFFREDDATA O SATURA
		      	IF(T.GT.TSAT) T=TSAT
	      		STEV = ENTROP(P,T-1.E-4,TSAT)
C      
		ELSE IF(Y.EQ.1.) THEN
C--- VAPORE SURRISCALDATO O SATURO
	      		IF(T.LT.TSAT) T=TSAT
	      		STEV = ENTROP(P,T+1.E-4,TSAT)
C
      		ELSE
C--- MISCELA
                CALL SATUR(P,1,SA,SV,N)
	        STEV =  SA*(1.-Y)+SV*Y
	        ENDIF
C
      endif
      RETURN
      END      
C**********************************************************************
      FUNCTION ENTROP(P,T0,TSAT)
C
C     CALCOLA :
C              ENTROPIA =ENTROP
C
C     DATI : PRESSIONE =P
C            TEMPERATURA=T0
C            TEMP. DI SATURAZIONE(P) =TSAT
C
      NTENT=1
      FASE=0.
      IF(P.GT.221.2E5) GOTO 3
      CALL SATUR(P,1,SW,SV,1)
      T=TSAT
      IF(T0-T) 1,2,2
   1  S=SW
      GOTO 4
   2  S=SV
      FASE=1.
      GOTO 4
   3  S=4442.9
C
  10  T=TEV(P,S,1)
   4  CP=CPEV(P,S,FASE,.5,1)
      DS=CP*(T0-T)/T0
      DELS=AMIN1(ABS(DS),1000.)
      S=S+DELS*SIGN(1.,DS)
      IF(DELS.LE.0.01) GOTO 20
      NTENT=NTENT+1
      IF(NTENT.LT.20) GOTO 10
C
      WRITE(6,99) DELS
  99  FORMAT(1X,'....ERRORE : ENTROP NON CONVERGE  DELTAS = ',E15.8)
  20  ENTROP=S
      RETURN
      END
