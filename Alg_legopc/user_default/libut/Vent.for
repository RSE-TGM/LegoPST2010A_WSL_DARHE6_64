      SUBROUTINE VENTI3(IFO,IOB,DEBL)
C
C     Centrifugal fan to be used in the two cases:
C     1) imposed rotational speed
C     2) imposed motor power
C                                    ( 28.07.97)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/VENT01/IBLOC
      COMMON/VENT02/ICONF
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'VENT'/
      CALL VENTI4(IOB,MOD)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      IF (ICONF.EQ.1) THEN
         WRITE(IFO,3000)IOB
 3000    FORMAT('ECIN',A4,2X,
     $          '--US-- FAN CINETIC ENERGY                   ')
         WRITE(IFO,3001)IOB
 3001    FORMAT('OMVE',A4,2X,
     $          '--UA-- FAN ROTATIONAL SPEED                 ')
      ENDIF
      WRITE(IFO,3002)IOB
 3002 FORMAT('PFVE',A4,2X,
     $  '--UA-- FLUID PRESSURE AT THE FAN OUTLET             ')
      WRITE(IFO,3003)IOB
 3003 FORMAT('TFU2',A4,2X,
     $  '--UA-- FLUID TEMPERATURE AT THE FAN OUTLET          ')
      WRITE(IFO,3004)IOB
 3004 FORMAT('TFU1',A4,2X,
     $  '--UA-- FLUID TEMP. AT THE FAN INLET (INVERTED FLOW) ')
      WRITE(IFO,3005)IOB
 3005 FORMAT('QRES',A4,2X,
     $  '--UA-- FAN RESISTENT POWER                          ')
      IF (ICONF.EQ.0) THEN
          WRITE(IFO,3006)IOB
 3006     FORMAT('OMVE',A4,2X,
     $           '--IN-- FAN ROTATIONAL SPEED                ')
      ELSE
          WRITE(IFO,3007)IOB
 3007     FORMAT('MOPW',A4,2X,
     $           '--IN-- FAN MOTOR POWER                     ')
      ENDIF
      WRITE(IFO,3008)IOB
 3008 FORMAT('WFVE',A4,2X,
     $  '--IN-- FLUID FLOW RATE INTO THE FAN                 ')
      WRITE(IFO,3009)IOB
 3009 FORMAT('PFMV',A4,2X,
     $  '--IN-- FLUID PRESSURE AT THE FAN INLET              ')
      WRITE(IFO,3010)IOB
 3010 FORMAT('ALSR',A4,2X,
     $  '--IN-- REGISTER OPENING DEGREE OF THE FAN           ')
      WRITE(IFO,3011)IOB
 3011 FORMAT('TFI1',A4,2X,
     $  '--IN-- FLUID TEMPERATURE AT THE FAN INLET           ')
      WRITE(IFO,3012)IOB
 3012 FORMAT('TFI2',A4,2X,
     $  '--IN-- FLUID TEMP. AT THE FAN OUTLET (INVERTED FLOW)')
      WRITE(IFO,3013)IOB
 3013 FORMAT('NVEN',A4,2X,
     $  '--IN-- NUMBER OF FANS IN PARALLEL                   ')
      RETURN
      END
C
      SUBROUTINE VENTI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/VENT01/IBLOC
      COMMON/VENT02/ICONF
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER*1 CONF
C
10    WRITE(6,*) 'Choose best suited module configuration:'
      WRITE(6,*) '0 =====> imposed rotational speed'
      WRITE(6,*) '1 =====> imposed motor power'
      READ(5,'(A1)') CONF
      IF(.NOT.(CONF.EQ.'0'.OR.CONF.EQ.'1')) GOTO 10
      READ(CONF,'(I1)') ICONF
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
C
      RETURN
      END
C
C
      SUBROUTINE VENTI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                   NOMBL1,NOMBL2,IER,CNXYU,TOL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      CHARACTER*4 ISPA,NORF,NER,TIPO,INER,COEF_CSI,POTNOM,OMB,QB
      REAL MINE
C
C_______ PARAMETER NTIPI = numero di tipi di caratteristiche standard dei
C                          ventilatori.
      PARAMETER (NTIPI=5)
C
C        Significato di TIPO :   1  Prementi  BRINDISI SUD
C                                2  Ricircolo BRINDISI SUD
C                                3  Aspirante BRINDISI SUD
C                                4  Desolforatori BRINDISI SUD
C                                5  Ricircolo NOXP BRINDISI SUD
C
C
C        Se TIPO < 0. il modulo chiama la subroutine Utente CARVEN
C
C
C
C
      COMMON /NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      DATA ISPA/'    '/,NORF/'ORIF'/
      DATA NER/'ERRE'/,TIPO/'TIPO'/
      DATA INER/'INER'/,POTNOM/'PNOM'/
      DATA OMB/'OMBA'/,QB/'QBASE'/
      DATA COEF_CSI/'CSI'/
      DATA PRIF/1.E+05/
C
      IF(IV2-IV1+1.EQ.11) THEN
         ICONF=0
      ELSE
         ICONF=1
      ENDIF
C
C-------SCRITTURA SIMBOLI E DATI
C
      GOTO(1,10),IFUN
C
1     WRITE(14,101) TIPO,ISPA,NORF,ISPA,NER,ISPA
      IF (ICONF.EQ.1)
     $    WRITE(14,101) INER,ISPA,COEF_CSI,ISPA,
     $                  POTNOM,ISPA,OMB,ISPA,
     $                  QB,ISPA
101   FORMAT(3(4X,2A4,' =',10X,'*'),5X)
      RETURN
C
C------LETTURA DATI
C
10    READ(14,102)
      READ(14,102) TYP,ORIF,ERRE
      IF (ICONF.EQ.1)
     $    READ(14,102) MINE,CSI,PNOM,OMBA,QBASE
102   FORMAT(3(14X,F10.2,1X),5X)
C
C-------MEMORIZZAZIONE DATI
C
      IF(TYP.LT.0.)GO TO 11
      IF(TYP.GT.0.AND.TYP.LE.NTIPI)GO TO 11
      WRITE(6,3001)IBLOC1,IBLOC2,TYP
 3001 FORMAT(//10X,'***DATA ERROR IN VENT**** MODULO***'/
     $ 10X,'*****BLOCK: ',2A4,' ***** TYPE = ',F10.3//)
      IER=1
C
11    CONTINUE
      DATI(ID2)=ICONF
      DATI(ID2+1)=TYP
      DATI(ID2+2)=ORIF
      DATI(ID2+3)=ERRE
C Riserva 5 posti per:    portata del passo precedente
C                         temperatura u2 del passo precedente
C                         temperatura u1  "   "       "
C                         temperatura i1  "   "       "
C                         temperatura i2  "   "       "
      IF (ICONF.EQ.1) THEN
          DATI(ID2+9)=MINE
          IF (CSI.LE.0) CSI=0.004
          DATI(ID2+10)=CSI
          DATI(ID2+11)=PNOM
          ECNOM=0.5*MINE*(ORIF**2)
          DATI(ID2+12)=ECNOM
          DATI(ID2+13)=QBASE
          DATI(ID2+14)=OMBA
      ENDIF
      IF (ICONF.EQ.0) THEN
          ID2=ID2 + 8
      ELSE
          ID2=ID2 +14
      ENDIF
C
C-------COSTANTI DI NORMALIZZAZIONE
C
      IREF=0
      IF (ICONF.EQ.1) THEN
          IREF=2
          CNXYU(IV1)=1.
          CNXYU(IV1+1)=314.1592
      ENDIF
      CNXYU(IV1+IREF)  =PRIF
      CNXYU(IV1+IREF+1)=T0
      CNXYU(IV1+IREF+2)=T0
      CNXYU(IV1+IREF+3)=W0*H0
      IF (ICONF.EQ.0) THEN
          CNXYU(IV1+IREF+4)=314.1592
      ELSE
          CNXYU(IV1+IREF+4)=QBASE
      ENDIF
      CNXYU(IV1+IREF+5)=W0
      CNXYU(IV1+IREF+6)=PRIF
      CNXYU(IV1+IREF+7)=1.
      CNXYU(IV1+IREF+8)=T0
      CNXYU(IV1+IREF+9)=T0
C
      RETURN
      END
C
      SUBROUTINE VENTC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,
     $                   RNI,IBLOC1,IBLOC2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      EXTERNAL VENT
      COMMON/VENTCFG/ICONF
C
C----MODULO VENTILATORE
C
      ICONF=DATI(IPD)
C
      GOTO(100,200,300),IFUN
C
C------ TOPOLOGIA JACOBIANO
C
100   IF (ICONF.EQ.0) THEN 
          NEQ=4
          NVAR=11
      ELSE
          NEQ=6
          NVAR=13
      ENDIF
      DO  I=1,NEQ
         DO  J=1,NVAR
            AJAC(I,J)=1.
         ENDDO
      ENDDO
      RETURN
C
C----CALCOLO RESIDUI
C
  200 CALL VENT(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano numerico
C
  300 IF (ICONF.EQ.0) THEN
          NSTATI = 0
          NUSCIT = 4
          NINGRE = 7
      ELSE
          NSTATI = 1
          NUSCIT = 6
          NINGRE = 7
      ENDIF
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     1    NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,VENT)
      RETURN
      END
C
      SUBROUTINE VENT(IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      LOGICAL KREGIM
      REAL NVENT                                                        !SNGL
C      DOUBLE PRECISION NVENT                                            !DBLE
C
C_______ PARAMETER NTIPI = numero di tipi di caratteristiche standard dei
C                          ventilatori.
      PARAMETER (NTIPI=5)
C
C        Significato di TIPO :   1  Prementi  BRINDISI SUD
C                                2  Ricircolo BRINDISI SUD
C                                3  Aspirante BRINDISI SUD
C                                4  Desolforatori BRINDISI SUD
C                                5  Ricircolo NOXP BRINDISI SUD
C
C
C
C        Se TIPO < 0. il modulo chiama la subroutine Utente CARVENUT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
      COMMON /NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C Common LEGO per determinare le soluzioni del passo precedente:
      COMMON/PARPAR/NULL(7),ITERT
C      COMMON/INTEGR/PS1,TEMPO,PS3,NPAS,CDT
      COMMON/INTEG1/PS1,TEMPO,PS3,CDT,ALFADT,NPAS
C
      COMMON/VENTCFG/ICONF
C
      REAL MINE,MOPW,MOPWDEN
C
      DATA UMID/0.01/
      DATA WMIN/1./
      DATA PAV/101300./
      DATA PRIF/1.E+05/
      DATA CP/1005./
      DATA TAU/100./
      DATA DTINT/0.3/
C
C
C--------DECODIFICA DATI
C
      TYP =DATI(IPD+1)
      ORIF=DATI(IPD+2)
      ERRE=DATI(IPD+3)
      IF (ICONF.EQ.1) THEN
          MINE=DATI(IPD+9)
          CSI=DATI(IPD+10)
          PNOM=DATI(IPD+11)
          ECNOM=DATI(IPD+12)
          QBASE=DATI(IPD+13)
          OMBA =DATI(IPD+14)
      ENDIF
C--------------------- MODIFICA C.I.S.E. 26/2/1990 ---
C
C      Cp=1005. J/Kg/K     Calore specifico dell'aria
C
      HH0=CP*T0
C
C-----------------------------------------------------
C
C-------DECODIFICA DELLE VARIABILI
C
      IREF=0
      IF (ICONF.EQ.1) THEN
          IREF=2
          ECIN=XYU(IXYU)
          OMDEN=XYU(IXYU+1)*314.1592
      ENDIF
      P2 =XYU(IXYU+IREF)
      TU2 =XYU(IXYU+IREF+1)
      TU1 =XYU(IXYU+IREF+2)
      QRES=XYU(IXYU+IREF+3)
      IF (ICONF.EQ.0) THEN
          OMDEN=XYU(IXYU+IREF+4)*314.1592
      ELSE
          MOPW=XYU(IXYU+IREF+4)
      ENDIF
      W  =XYU(IXYU+IREF+5)
      P1 =XYU(IXYU+IREF+6)
      TET=XYU(IXYU+IREF+7)
      TI1 =XYU(IXYU+IREF+8)
      TI2 =XYU(IXYU+IREF+9)
      NVENT=XYU(IXYU+IREF+10)
C
C------DENORMALIZZAZIONE DELLE VARIABILI
C
      IF (ICONF.EQ.1) THEN
          ECINDEN=ECIN*1.
          MOPWDEN=MOPW*QBASE
      ENDIF
C
      P2DEN =P2*PRIF
      TU2DEN =TU2*T0
      TU1DEN =TU1*T0
      WDEN  =W*W0/NVENT
      P1DEN =P1*PRIF
      TETDEN=TET*1.
      TI1DEN =TI1*T0
      TI2DEN =TI2*T0
C
      RO=PAV/(ERRE*TI1DEN)
C
C-------CALCOLO DEI RESIDUI
C
C
C________ SE TYP < 0. SI USA LA SUBROUTINE UTENTE CARVENUT
C
      IF(TYP.GT.0.)GO TO 10
      CALL CARVENUT(TYP,OMDEN,ORIF,WDEN,TETDEN,RO,DELTAP,CRDEN)
      GO TO 11
C
C________ SE TYP > 0. (1.,2.,3.,4.,5.) SI USA LA SUBROUTINE CARVEN
C
C
  10  CONTINUE
      CALL CARVEN(TYP,OMDEN,ORIF,WDEN,TETDEN,RO,DELTAP,CRDEN)
C
  11  CONTINUE
C
C     CR=CRDEN/ORIF
C
C---------------------------------RESIDUI DEL MODULO  
      IRES=0
      IF (ICONF.EQ.1) THEN
         IRES=2
         RNI(1)=(MOPWDEN-CRDEN*OMDEN-CSI*PNOM*(OMDEN/ORIF))
     $          /ECNOM
         RNI(2)=ECINDEN-0.5*MINE*OMDEN*ABS(OMDEN)/ECNOM
      ENDIF
C
      RNI(1+IRES)=-P2+P1+DELTAP/PRIF
C     
      IF(KREGIM) go to 707
C           
      IF(ITERT.EQ.0) THEN
C SALVA  W,TU2,TU1,TI1,TI2  DEL PASSO PRECEDENTE
      DATI(IPD+4)=W
      DATI(IPD+5)=TU2DEN
      DATI(IPD+6)=TU1DEN
      DATI(IPD+7)=TI1DEN
      DATI(IPD+8)=TI2DEN
      END IF
C
      WP=DATI(IPD+4)
      TU2DENP=DATI(IPD+5)
      TU1DENP=DATI(IPD+6)
      TI1DENP=DATI(IPD+7)
      TI2DENP=DATI(IPD+8)
C
      IF(ABS(WP).LT.WMIN/W0) THEN
      IF(IFUN.EQ.2) THEN
      IF (.NOT.KREGIM) THEN
	RNI(2+IRES)=-TU2*(1.+DTINT/TAU)+TU2DENP/T0+DTINT/TAU*TI1
	RNI(3+IRES)=-TU1*(1.+DTINT/TAU)+TU1DENP/T0+DTINT/TAU*TI2
      ELSE
	RNI(2+IRES)=-TU2+TU2DENP/T0
	RNI(3+IRES)=-TU1+TU1DENP/T0
      ENDIF
C
      ELSE
      RNI(2+IRES)=-TU2
      RNI(3+IRES)=-TU1
      END IF
C
      ELSE
 707  CONTINUE
      DELTAH=OMDEN*CRDEN/ABS(WDEN)
      IF(WP.LT.0.)THEN
      H1=HTFU(TI2DEN,UMID,1)/HH0
      H2=HTFU(TU1DEN,UMID,1)/HH0
      RNI(2+IRES)=-TU2+TI2
      RNI(3+IRES)=-H2+H1+DELTAH/HH0
      ELSE
      H1=HTFU(TI1DEN,UMID,1)/HH0
      H2=HTFU(TU2DEN,UMID,1)/HH0
      RNI(2+IRES)=-H2+H1+DELTAH/HH0
      RNI(3+IRES)=-TU1+TI1
      ENDIF
      ENDIF
C
      IF((KREGIM).AND.(ABS(WP).LT.WMIN/W0))THEN
      RNI(2+IRES)=-TU2+TI1
      RNI(3+IRES)=-TU1+TI1
      ENDIF
C
      RNI(4+IRES)=QRES-CRDEN*OMDEN/(W0*H0)
C
      RETURN
      END
C
      SUBROUTINE CARVEN(TYP,OM,OM0,W,TET,RO,DELTAP,CR)
C
C        Significato di TIPO :   1  Prementi  BRINDISI SUD
C                                2  Ricircolo BRINDISI SUD
C                                3  Aspirante BRINDISI SUD
C                                4  Desolforatori BRINDISI SUD
C                                5  Ricircolo NOXP BRINDISI SUD
C
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      ITY=TYP
      GO TO (10,20,30,40,50),ITY
   10 CONTINUE
C
C  TABELLE PER VENTILATORI PREMENTI (BRINDISI SUD)
C
      CALL VEXPREM(OM,OM0,W,TET,RO,DELTAP,CR)
      RETURN
   20 CONTINUE
C
C  TABELLE PER VENTILATORI DI RICIRCOLO (BRINDISI SUD)
C
      CALL VEXRICI(OM,OM0,W,TET,RO,DELTAP,CR)
      RETURN
   30 CONTINUE
C
C  TABELLE PER VENTILATORI ASPIRANTI (BRINDISI SUD)
C
      CALL VEXASPI(OM,OM0,W,TET,RO,DELTAP,CR)
      RETURN
   40 CONTINUE
C
C  TABELLE PER VENTILATORI DEL DESOLFORATORE (BRINDISI SUD)
C
      CALL VEXDESO(OM,OM0,W,TET,RO,DELTAP,CR)
      RETURN
   50 CONTINUE
C
C  TABELLE PER VENTILATORI DI RICIRCOLO NOX PORTS (BRINDISI SUD)
C
      CALL VEXRNOX(OM,OM0,W,TET,RO,DELTAP,CR)
      RETURN
      END
      SUBROUTINE VEXPREM(OM,OM0,W,TET,RO,DELTAP,CR)
C
C  Opera su grandezze non normalizzate
C
C
C======================================================================
C  CURVE DELLA PREVALENZA DEL VENTILATORE DATE PER PUNTI
C
C
C  TABELLE PER VENTILATORI PREMENTI (BRINDISI SUD)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION VETXDP(13),VETDP(78),VETPDP(6)
C  TABELLA PORTATE(V. PREM. BRINDISI SUD)
      DATA VETXDP/0.,40.,80.,120.,160.,200.,240.,
     1 280.,320.,360.,400.,440.,480./
C  TABELLA PREVALENZE (V. PREM. BRINDISI SUD) DELTAP/RO
C
C  TETA=0.0:
      DATA VETDP/5894.,630.,-4630.,-9900.,-15150.,-20000.,
     1 -25000.,-29000.,-32000.,-34000.,-36000.,
     1 -38000.,-39000.,
C
C  TETA=0.2:
     1        5894.,5490.,4210.,2020.,-670.,-2016.,
     1 -3386.,-4756.,-6126.,-7496.,-8866.,
     1 -10236.,-11606.,
C  TETA=0.4:
     1 5894.,5793.,5473.,4841.,3790.,2357.,1515.,
     1 -169.,-1853.,-3537.,-5221.,-6905.,-8589.,
C  TETA=0.6:
     1 5894.,5890.,5790.,5557.,5120.,4630.,3974.,
     1 3073.,1852.,505.,-842.,-2189.,-3536.,
C  TETA=0.8:
     1 5894.,5890.,5790.,5780.,5760.,5680.,5390.,
     1 5052.,4420.,3536.,2357.,842.,-673.,
C  TETA=1.:
     1 5894.,5890.,5820.,5790.,5770.,5750.,5740.,
     1 5726.,5389.,4757.,3831.,2694.,1094./
C
      DATA LXDP,LPDP/13,6/
C
      DATA RO0/1.165/
C
C  INLET VANES VENT. PREMENTI (BRINDISI SUD):
      DATA VETPDP/0.,0.2,0.4,0.6,0.8,1./
C  COEFFICIENTI DELLA PARABOLA DELLA POTENZA:
C  P=A*X**2+B*X+C
      DATA A,B,C/-12.1875,9750.,700.E3/
C
C=========================================================================
C
      DATA EPS/1.E-4/
C-------CALCOLO DELTAP
C
      X=OM0/(OM+EPS)*W/RO
      CALL LINTAB(VETPDP,LPDP,VETXDP,LXDP,VETDP,X,TET,
     $     DPSRO,DDPDX,DDPTE)
      DELTAP=RO*(OM/OM0)**2*DPSRO
C-------CALCOLO POTENZA ASSORBITA ALLA VELOCITA' OM0:
      POT0=A*X*X+B*ABS(X)+C
C Applico le leggi dei ventilatori per calcolare la coppia
C resistente effettiva:
      CR=POT0*RO/RO0*(OM/OM0)**2/OM0
      IF(OM.LT.(OM0*EPS))CR=0.
      RETURN
      END
      SUBROUTINE VEXRICI(OM,OM0,W,TET,RO,DELTAP,CR)
C
C  Opera su grandezze non normalizzate
C
C
C======================================================================
C  CURVE DELLA PREVALENZA DEL VENTILATORE DATE PER PUNTI
C
C  TABELLE PER VENTILATORI RICIRCOLO (BRINDISI SUD)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION VETXDP(13),VETDP(65),VETPDP(5)
C  TABELLA PORTATE(V. RICIRCOLO BRINDISI SUD)
      DATA VETXDP/0.,27.8,55.6,83.3,111.1,138.9,
     1 166.7,194.4,222.2,250.,277.8,305.5,
     1 333.3/
C  TABELLA PREVALENZE (V. RICIRCOLO BRINDISI SUD) DELTAP/RO
C
C  TETA=0.2:
      DATA VETDP/5040.,4900.,4170.,2780.5,695.,-1390.,
     1 -3474.,-5560.,-7644.,-9729.,-11814.,
     1 -13900.,-15984.,
C  TETA=0.4:
     1 5178.,5126.,4970.,4622.,4083.,3214.,2085.,
     1 695.,-694.,-2084.,-3474.,-4864.,-6524.,
C  TETA=0.6:
     1 5317.,5283.,5213.,5143.,4952.,4587.,4170.,
     1 3406.,2502.,1216.,-348.,-1912.,-3476.,
C  TETA=0.8:
     1 5630.,5561.,5491.,5457.,5352.,5283.,4935.,
     1 4692.,4136.,3389.,2328.,1042.,-592.,
C  TETA=1.:
     1 5735.,5700.,5665.,5650.,5595.,5580.,5526.,
     1 5387.,4592.,4344.,3562.,2190.,1251./
C
      DATA LXDP,LPDP/13,5/
C
      DATA RO0/0.5645/
C
C  INLET VANES VENT. RICIRCOLO (BRINDISI SUD):
      DATA VETPDP/0.2,0.4,0.6,0.8,1./
C  COEFFICIENTI DELLA PARABOLA DELLA POTENZA:
C  P=A*X**2+B*X+C
C  PER I VENTILATORI RICIRCOLO SI HA UNA LEGGE LINEARE:
      DATA A,B,C/0.,3200.,170.E3/
C
C=========================================================================
C
      DATA EPS/1.E-4/
C-------CALCOLO DELTAP
C
      X=OM0/(OM+EPS)*W/RO
      CALL LINTAB(VETPDP,LPDP,VETXDP,LXDP,VETDP,X,TET,
     $     DPSRO,DDPDX,DDPTE)
      DELTAP=RO*(OM/OM0)**2*DPSRO
C-------CALCOLO POTENZA ASSORBITA ALLA VELOCITA' OM0:
      POT0=A*X*X+B*ABS(X)+C
C Applico le leggi dei ventilatori per calcolare la coppia
C resistente effettiva:
      CR=POT0*RO/RO0*(OM/OM0)**2/OM0
      IF(OM.LT.(OM0*EPS))CR=0.
      RETURN
      END
      SUBROUTINE VEXASPI(OM,OM0,W,TET,RO,DELTAP,CR)
C
C  Opera su grandezze non normalizzate
C
C
C======================================================================
C  CURVE DELLA PREVALENZA DEL VENTILATORE DATE PER PUNTI
C
C
C  TABELLE PER VENTILATORI ASPIRANTI (BRINDISI SUD)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION VETXDP(11),VETDP(77),VETPDP(7)
C  TABELLA PORTATE(V. ASPIR. BRINDISI SUD)
      DATA VETXDP/0.,100.,200.,300.,400.,500.,600.,
     1 700.,800.,900.,1000./
C  TABELLA PREVALENZE (V. ASPIR. BRINDISI SUD) DELTAP/RO
C
C  TETA=0.01:
      DATA VETDP/8823.,-8823.,-26000.,-44100.,-61746.,
     1           -79400.,-97038.,-114000.,-132300.,
     1           -150000.,-167600.,
C  TETA=0.15:
     1 8823.,6385.,4063.,1625.,-1270.,-4179.,
     1 -7082.,-9984.,-12886.,-15789.,-18690.,
C  TETA=0.3:
     1 8823.,7850.,7081.,5978.,4353.,2437.,521.,
     1 -1395.,-3311.,-5227.,-7143.,
C  TETA=0.45
     1 8823.,8474.,8126.,7604.,6849.,5804.,4353.,
     1 2786.,1219.,-347.,-1914.,
C  TETA=0.6:
     1 8823.,8707.,8532.,8416.,8184.,7430.,6269.,
     1 4934.,3076.,1219.,-638.,
C  TETA=0.75:
     1 8823.,8765.,8707.,8590.,8474.,8068.,7197.,
     1 5978.,4353.,2728.,1103.,
C  TETA=1.:
     1 8823.,8770.,8700.,8649.,8591.,8474.,7720.,
     1 6559.,5282.,3773.,1741./
C
      DATA LXDP,LPDP/11,7/
C
      DATA RO0/0.845/
C
C  INLET VANES VENT. ASPIRANTI (BRINDISI SUD):
      DATA VETPDP/0.01,0.15,0.3,0.45,0.6,0.75,1./
C  COEFFICIENTI DELLA PARABOLA DELLA POTENZA:
C  P=A*X**2+B*X+C
      DATA A,B,C/-4.94,8400.,1290.E3/
C
C=========================================================================
C
      DATA EPS/1.E-4/
C-------CALCOLO DELTAP
C
      X=OM0/(OM+EPS)*W/RO
      CALL LINTAB(VETPDP,LPDP,VETXDP,LXDP,VETDP,X,TET,
     $     DPSRO,DDPDX,DDPTE)
      DELTAP=RO*(OM/OM0)**2*DPSRO
C-------CALCOLO POTENZA ASSORBITA ALLA VELOCITA' OM0:
      POT0=A*X*X+B*ABS(X)+C
C Applico le leggi dei ventilatori per calcolare la coppia
C resistente effettiva:
      CR=POT0*RO/RO0*(OM/OM0)**2/OM0
      IF(OM.LT.(OM0*EPS))CR=0.
      RETURN
      END
      SUBROUTINE VEXDESO(OM,OM0,W,TET,RO,DELTAP,CR)
C
C  Opera su grandezze non normalizzate
C
C
C======================================================================
C  CURVE DELLA PREVALENZA DEL VENTILATORE DATE PER PUNTI
C
C
C  TABELLE PER VENTILATORI DEL DESOLFORATORE (BRINDISI SUD)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION VETXDP(11),VETDP(77),VETPDP(7)
C  TABELLA PORTATE(V. ASPIR. BRINDISI SUD)
      DATA VETXDP/0.,100.,200.,300.,400.,500.,600.,
     1 700.,800.,900.,1000./
C  TABELLA PREVALENZE (V. ASPIR. BRINDISI SUD) DELTAP/RO
C  TETA=0.01
      DATA VETDP/8823.,-8823.,-26000.,-44100.,-61746.,
     1           -79400.,-97038.,-114000.,-132300.,
     1           -150000.,-167600.,
C  TETA=0.15:
     1       8823.,6385.,4063.,1625.,-1270.,-4179.,
     1 -7082.,-9984.,-12886.,-15789.,-18690.,
C  TETA=0.3:
     1 8823.,7850.,7081.,5978.,4353.,2437.,521.,
     1 -1395.,-3311.,-5227.,-7143.,
C  TETA=0.45
     1 8823.,8474.,8126.,7604.,6849.,5804.,4353.,
     1 2786.,1219.,-347.,-1914.,
C  TETA=0.6:
     1 8823.,8707.,8532.,8416.,8184.,7430.,6269.,
     1 4934.,3076.,1219.,-638.,
C  TETA=0.75:
     1 8823.,8765.,8707.,8590.,8474.,8068.,7197.,
     1 5978.,4353.,2728.,1103.,
C  TETA=1.:
     1 8823.,8770.,8700.,8649.,8591.,8474.,7720.,
     1 6559.,5282.,3773.,1741./
C
      DATA LXDP,LPDP/11,7/
C
      DATA RO0/0.845/
C
C  INLET VANES  (BRINDISI SUD):
      DATA VETPDP/0.01,0.15,0.3,0.45,0.6,0.75,1./
C  COEFFICIENTI DELLA PARABOLA DELLA POTENZA:
C  P=A*X**2+B*X+C
      DATA A,B,C/-4.94,8400.,1290.E3/
C
C=========================================================================
C
      DATA EPS/1.E-4/
C-------CALCOLO DELTAP
C
      X=OM0/(OM+EPS)*W/RO
      CALL LINTAB(VETPDP,LPDP,VETXDP,LXDP,VETDP,X,TET,
     $     DPSRO,DDPDX,DDPTE)
      DELTAP=RO*(OM/OM0)**2*DPSRO
C-------CALCOLO POTENZA ASSORBITA ALLA VELOCITA' OM0:
      POT0=A*X*X+B*ABS(X)+C
C Applico le leggi dei ventilatori per calcolare la coppia
C resistente effettiva:
      CR=POT0*RO/RO0*(OM/OM0)**2/OM0
      IF(OM.LT.(OM0*EPS))CR=0.
      RETURN
      END
      SUBROUTINE VEXRNOX(OM,OM0,W,TET,RO,DELTAP,CR)
C
C  Opera su grandezze non normalizzate
C
C
C======================================================================
C  CURVE DELLA PREVALENZA DEL VENTILATORE DATE PER PUNTI
C
C  TABELLE PER VENTILATORI RICIRCOLO NOX PORTS (BRINDISI SUD)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION VETXDP(13),VETDP(65),VETPDP(5)
C  TABELLA PORTATE(V. RICIRCOLO NOX PORTS BRINDISI SUD)
      DATA VETXDP/0.,27.8,55.6,83.3,111.1,138.9,
     1 166.7,194.4,222.2,250.,277.8,305.5,
     1 333.3/
C  TABELLA PREVALENZE (V. RICIRCOLO NOX PORTS BRINDISI SUD) DELTAP/RO
C
C  TETA=0.2:
      DATA VETDP/9040.,8900.,8170.,6780.5,4695.,2610.,
     1 526.,-1560.,-3644.,-5729.,-7814.,
     1 -9900.,-11984.,
C  TETA=0.4:
     1 9178.,9126.,8970.,8622.,8083.,7214.,6085.,
     1 4695.,3306.,1916.,526.,-864.,-2524.,
C  TETA=0.6:
     1 9317.,9283.,9213.,9143.,8952.,8587.,8170.,
     1 7406.,6502.,5216.,3652.,2088.,524.,
C  TETA=0.8:
     1 9630.,9561.,9491.,9457.,9352.,9283.,8935.,
     1 8692.,8136.,7389.,6328.,5042.,3408.,
C  TETA=1.:
     1 9735.,9700.,9665.,9650.,9595.,9580.,9526.,
     1 9387.,8592.,8344.,7562.,6190.,5251./
C
      DATA LXDP,LPDP/13,5/
C
      DATA RO0/0.5645/
C
C  INLET VANES VENT. RICIRCOLO NOX PORTS (BRINDISI SUD):
      DATA VETPDP/0.2,0.4,0.6,0.8,1./
C  COEFFICIENTI DELLA PARABOLA DELLA POTENZA:
C  P=A*X**2+B*X+C
C  PER I VENTILATORI RICIRCOLO NOX PORTS SI HA UNA LEGGE LINEARE:
      DATA A,B,C/0.,3200.,170.E3/
C
C=========================================================================
C
      DATA EPS/1.E-4/
C-------CALCOLO DELTAP
C
      X=OM0/(OM+EPS)*W/RO
      CALL LINTAB(VETPDP,LPDP,VETXDP,LXDP,VETDP,X,TET,
     $     DPSRO,DDPDX,DDPTE)
      DELTAP=RO*(OM/OM0)**2*DPSRO
C-------CALCOLO POTENZA ASSORBITA ALLA VELOCITA' OM0:
      POT0=A*X*X+B*ABS(X)+C
C Applico le leggi dei ventilatori per calcolare la coppia
C resistente effettiva:
      CR=POT0*RO/RO0*(OM/OM0)**2/OM0
      IF(OM.LT.(OM0*EPS))CR=0.
      RETURN
      END
C
C
C
      SUBROUTINE VENTD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $ XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      CHARACTER*8 BLOCCO, SYMVAR(*), UNITEQ(*)*10, SIGNEQ(*)*50
      DIMENSION XYU(*), DATI(*), COSNOR(*), ITOPVA(MXT,*)
C
      COMMON /NORM/ P0,H0,T0,W0,RO0,AL0,V0,DP0
      DATA PRIF/1.E+05/
C
C---equazione numero 1 (algebrica)
C
      SIGNEQ(1) = 'FAN OUTLET PRESSURE COMPUTATION'
      UNITEQ(1) = 'Pa'
      COSNOR(1) = PRIF
      ITOPVA(1, 1) = 1
      ITOPVA(1, 4) = 1
      ITOPVA(1, 5) = 1
      ITOPVA(1, 6) = 1
      ITOPVA(1, 7) = 1
      ITOPVA(1, 8) = 1
      ITOPVA(1,10) = 1
C
C---equazione numero 2 (algebrica)
C
      SIGNEQ(2) = 'FAN OUTLET TEMPERATURE COMPUTATION'
      UNITEQ(2) = 'K'
      COSNOR(2) = T0
      ITOPVA(2, 2) = 1
      ITOPVA(2, 3) = 1
      ITOPVA(2, 4) = 1
      ITOPVA(2, 5) = 1
      ITOPVA(2, 7) = 1
      ITOPVA(2, 8) = 1
      ITOPVA(2, 9) = 1
      ITOPVA(2,10) = 1
C
C---equazione numero 3 (algebrica)
C
      SIGNEQ(3) = 'FAN INLET TEMPERATURE COMP. (FOR FLOW INVERSION)'
      UNITEQ(3) = 'K'
      COSNOR(3) = T0
      ITOPVA(3, 3) = 1
      ITOPVA(3, 4) = 1
      ITOPVA(3, 5) = 1
      ITOPVA(3, 8) = 1
      ITOPVA(3,10) = 1
C
      RETURN
      END
C
C
C
C~FORAUS_VENT~C
C
C FORTRAN AUSILIARIO DEL MODULO VENTILATORE
C PER LA SUA SCRITTURA VEDERE MANUALE D'USO
C O UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD
C
C
C******* BREVE SPIEGAZIONE DEI PARAMETRI DELLA SUBROUTINE **********
C
CC        SUBROUTINE CARVENUT(TYP,OM,OM0,W,TET,RO,DELTAP,CR)
CC
CC Parametri d'ingresso :  TYP, OM, OM0, W, TET, RO
CC Parametri d'uscita   :  DELTAP, CR
CC
CC [ ]       TYP     corrisponde  al  dato  TIPO  richiesto in input (vedi
CC                   scheda C1);  puo` essere utilizzato come indice di
CC                   selezione  delle curve caratteristiche, qualora si voglia
CC                   utilizzare un unico sottoprogramma utente per piu` tipi di
CC                   ventilatori
CC
CCC [rad/s]   OM      velocita' angolare del ventilatore
CC
CCC [rad/s]  OM0      velocita'angolare nominale (velocita' di riferimento
CC                    delle caratteristiche fornite dal costruttore)
CC
CC  [kg/s]    W       portata di fluido nel ventilatore
CC
CC  [p.u.]    TET     valore del parametro di comando del sistema di regolazione
CC                    della portata
CC
CC  [kg/m**3] RO      densita' del fluido che attraversa il ventilatore
CC
CC  [Pa]      DELTAP  prevalenza del ventilatore
CC
CC  [Nw*m]    CR      coppia resistente del ventilatore
CC
CC
CC
CC********* ESEMPIO DI SOTTOPROGRAMMA UTENTE *******************
CC
CC
C      SUBROUTINE CARVENUT(TYP,OM,OM0,W,TET,RO,DELTAP,CR)
CC
CC      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      ITY=-TYP
C      GO TO (10,20),ITY
C   10 CONTINUE
CC
CC  DATI PER I VENTILATORI DI TAVAZZANO
CC
C       DELTAPNOM= 0.730*9.81*990.
C       DELTAPMAX= 0.814*9.81*990.
C       QVOLNOM  = 196.83
C       POTNOM   =1.720E6
C       COPNOM   =POTNOM/OM0
C       VELNOM   =OM0*30./3.141592
C       ETANOM   = QVOLNOM*DELTAPNOM/POTNOM
C       ALFA     = 1.5
C       C =0.1*SQRT((ALFA-1.)/ALFA)
CC
C       QVR= W/RO/QVOLNOM
C       OMR= OM/OM0
C       ZETA   = 3.141592/2.*TET
C       BETA   = SIN(ZETA)+ C*(1. - 2./3.141592*ZETA)
C       DELTAP =DELTAPNOM*(-(ALFA-1.)*QVR*ABS(QVR)/BETA/BETA+ALFA*OMR**2)
C       IF(DELTAP.GT.DELTAPMAX) DELTAP=DELTAPMAX
CC
C       CR = COPNOM*(OMR * DELTAP/DELTAPNOM/(2.*OMR-QVR))
CC
C   20 CONTINUE
C      RETURN
C      END
CC
C~FORAUS_VENT~C
