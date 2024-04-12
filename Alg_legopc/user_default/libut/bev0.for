      SUBROUTINE BEV0I3(IFO,IOB,DEBL)
      COMMON/BEV000/IBLOC,NCI 
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'BEV0'/
C*******************************************************************
C   DESALINATOR EVAPORATION CELL  27.02.2001
C*******************************************************************
      CALL BEV0I4(IOB,MOD)
C
C
      NSTATI=5
      NUSCIT=11
      NINGRE=10+NCI
      NVAR=NUSCIT+NINGRE
C
C
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3000)IOB
 3000 FORMAT('PRES',A4,2X,'--US-- BRINE/STEAM PRESSURE IN CAVITY  ')
      WRITE(IFO,3001)IOB
 3001 FORMAT('LEVB',A4,2X,'--US-- BRINE LEVEL IN CAVITY           ')
      WRITE(IFO,3002)IOB
 3002 FORMAT('LEVD',A4,2X,'--US-- DISTILLATE LEVEL IN CAVITY      ')      
      WRITE(IFO,3003)IOB
 3003 FORMAT('FNAC',A4,2X,'--US-- BRINE RESIDENT MASS FRACTION    ')
      WRITE(IFO,3004)IOB
 3004 FORMAT('TMEC',A4,2X,'--US-- CASING METAL TEMPERATURE        ')
      WRITE(IFO,3005)IOB
 3005 FORMAT('HBRN',A4,2X,'--UA-- BRINE RESIDENT ENTHALPY         ')
      WRITE(IFO,3006)IOB
 3006 FORMAT('TEMP',A4,2X,'--UA-- BRINE/STEAM TEMPERATURE         ')
      WRITE(IFO,3007)IOB
 3007 FORMAT('HDIS',A4,2X,'--UA-- DISTILLATE ENTHALPY             ')
      WRITE(IFO,3008)IOB
 3008 FORMAT('TDIS',A4,2X,'--UA-- DISTILLATE TEMPERATURE          ')
      WRITE(IFO,3009)IOB
 3009 FORMAT('WEVA',A4,2X,'--UA-- BRINE EVAPORATION MASS FLOW     ')
      WRITE(IFO,3010)IOB
 3010 FORMAT('WFLA',A4,2X,'--UA-- DISTILLATE FLASH MASS FLOW      ')
      WRITE(IFO,3011)IOB
 3011 FORMAT('WCON',A4,2X,'--UA-- DISTILLATE CONDENSING MASS FLOW ') 
      WRITE(IFO,3012)IOB
 3012 FORMAT('PFBR',A4,2X,'--UA-- PRESSURE AT BRINE BOTTOM        ')
      WRITE(IFO,3013)IOB
 3013 FORMAT('PFDS',A4,2X,'--UA-- PRESSURE AT DISTILLATE BOTTOM   ')
      WRITE(IFO,3014)IOB
 3014 FORMAT('HSTE',A4,2X,'--UA-- ENTHALPY OF STEAM FOR STRIPPING ')
      WRITE(IFO,3015)IOB
 3015 FORMAT('GATU',A4,2X,'--UA-- TUBES EXCHANGING COEFFICIENT    ')
      WRITE(IFO,3016)IOB
 3016 FORMAT('WBRI',A4,2X,'--IN-- BRINE INLET MASS FLOW RATE      ')
      WRITE(IFO,3017)IOB
 3017 FORMAT('WBRO',A4,2X,'--IN-- BRINE OUTLET MASS FLOW RATE     ')
      WRITE(IFO,3018)IOB
 3018 FORMAT('FNAI',A4,2X,'--IN-- BRINE INLET MASS FRACTION       ')
      WRITE(IFO,3019)IOB
 3019 FORMAT('HBRI',A4,2X,'--IN-- BRINE INLET ENTHALPY            ')
      WRITE(IFO,3020)IOB
 3020 FORMAT('WDSI',A4,2X,'--IN-- DISTILLATE INLET MASS FLOW RATE ')
      WRITE(IFO,3021)IOB
 3021 FORMAT('WDSO',A4,2X,'--IN-- DISTILLATE OUTLET MASS FLOW RATE')
      WRITE(IFO,3022)IOB
 3022 FORMAT('HDSI',A4,2X,'--IN-- DISTILLATE INLET ENTHALPY       ')
      WRITE(IFO,3023)IOB
 3023 FORMAT('WSTP',A4,2X,'--IN-- STEAM EXTRACTED FOR STRIPPING   ')
      WRITE(IFO,3024) (I,IOB,I,I=1,NCI)
 3024 FORMAT('TMI',I1,A4,2X,'--IN-- TUBES METAL TEMPERATURE CELL ',I1)
      WRITE(IFO,3025)IOB
 3025 FORMAT('TEXT',A4,2X,'--IN-- EXTERNAL TEMPERATURE            ')
      WRITE(IFO,3026)IOB
 3026 FORMAT('AGAM',A4,2X,'--IN-- TUBES-STEAM EXCH.COEFF.CORRECTOR')
C
      RETURN
      END
C***********************************************************************
      SUBROUTINE BEV0I4(IOB,MOD)
      PARAMETER (MAXCI=9)
      COMMON/BEV000/IBLOC,NCI
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
   10 WRITE(6,101)
  101 FORMAT(10X,'*** DESALINATOR EVAPORATION CELL ***')
C
   16 WRITE(6,107) MAXCI
  107 FORMAT(10X,'INNER TUBES CELL NUMBER (01 -',I3,') ?')
      READ(5,*) NCI
      IF(NCI.LE.0.OR.NCI.GT.MAXCI) THEN
         WRITE(6,108) NCI,MAXCI
         GOTO 16
      ENDIF
  108 FORMAT(10X,'WRONG! - N.CEL.=',I3,'>',I3/)
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
C
      RETURN
      END
C***********************************************************************
        SUBROUTINE BEV0I2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
        DIMENSION VAR(MX1,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
C
        PARAMETER (GAMS=1000. ) ! brine-casing thermal exch. coefficient
        PARAMETER (GAMD=1000. ) ! distillate-casing thermal exch. coefficient
        PARAMETER (GAMV=1000. ) ! steam-casing thermal exch. coefficient
        PARAMETER (GAMT=5000. ) ! tubes-casing thermal exch. coefficient
        PARAMETER (GAME=1.    ) ! casing external thermal exch. coefficient
C
        PARAMETER (GAM0=1000.)  !normalization coefficient for GATU
C
        REAL LENGTH,NEXCSID,NTUB,LENTUB,MAMET
C
        PARAMETER (PI=3.14159)
        PARAMETER (MAXCI=9)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
C
C---Desalinator evaporation cell
C
        GO TO(100,200),IFUN
C
  100   WRITE(14,500)    'NET_VOL.'
     1                  ,'LENGTH  '
     1                  ,'WIDTH   '
     1                  ,'HEIGHT  '
     1                  ,'THICK   '
     1                  ,'NEXCSID '
     1                  ,'ABRIBASE'
     1                  ,'ADISTBAS'
     1                  ,'ADISTEXC'
     1                  ,'NCEL    '
     1                  ,'SUP.TUB.'
     1                  ,'NUM_TUB '
     1                  ,'LEN_TUB '
     1                  ,'DEXT_TUB'
     1                  ,'MASSA ME'
     1                  ,'CP MET. '
     1                  ,'COND.MET'
C
        RETURN
C
C---lettura e memorizzazione dati
C
  200   READ(14,502)
        READ(14,502)     VTOT
     1                  ,LENGTH
     1                  ,WIDTH
     1                  ,HEIGHT
     1                  ,THICK
     1                  ,NEXCSID
     1                  ,AS
     1                  ,AD
     1                  ,ADEXC
     1                  ,ACEL
     1                  ,STUB
     1                  ,NTUB
     1                  ,LENTUB
     1                  ,DEXTUB
     1                  ,MAMET
     1                  ,CPMET
     1                  ,COND
C
  500   FORMAT(3(4X,A8,' =',10X,'*'))
  502   FORMAT(3(14X,F10.2,1X))
C
        NCEL=ACEL
C
        BASE=LENGTH*WIDTH
        PERI=2*LENGTH+NEXCSID*WIDTH
        AEXT=BASE+HEIGHT*PERI
        IF (AS.EQ.0) AS=(LENGTH-2*THICK)*(WIDTH-2*THICK)
        IF (STUB.EQ.0) THEN
            SCEL=NTUB*PI*DEXTUB*LENTUB/NCEL
        ELSE
            SCEL=STUB/NCEL
        ENDIF
        CTMET=MAMET*CPMET
        GAMET=2.*COND/THICK
        GAMBRI =GAMET*GAMS/(GAMET+GAMS)
        GAMSTE =GAMET*GAMV/(GAMET+GAMV)
        GAMDIS =GAMET*GAMD/(GAMET+GAMD)
        GAMEXT =GAMET*GAME/(GAMET+GAME)
C
        WRITE(6,*) 'BASE   = ',BASE
        WRITE(6,*) 'PERI   = ',PERI
        WRITE(6,*) 'AEXT   = ',AEXT
        WRITE(6,*) 'AS     = ',AS  
        WRITE(6,*) 'SCEL   = ',SCEL
        WRITE(6,*) 'CTMET  = ',CTMET
        WRITE(6,*) 'GAMET  = ',GAMET
        WRITE(6,*) 'GAMBRI = ',GAMBRI
        WRITE(6,*) 'GAMSTE = ',GAMSTE
        WRITE(6,*) 'GAMDIS = ',GAMDIS
        WRITE(6,*) 'GAMEXT = ',GAMEXT
C
        DATI(ID1  ) = VTOT 
        DATI(ID1+1) = HEIGHT 
        DATI(ID1+2) = AD
        DATI(ID1+3) = ADEXC
        DATI(ID1+4) = ACEL 
        DATI(ID1+5) = BASE 
        DATI(ID1+6) = PERI
        DATI(ID1+7) = AEXT  
        DATI(ID1+8) = AS  
        DATI(ID1+9) = SCEL
        DATI(ID1+10)= CTMET
        DATI(ID1+11)= GAMBRI
        DATI(ID1+12)= GAMSTE
        DATI(ID1+13)= GAMDIS
        DATI(ID1+14)= GAMEXT
        DATI(ID1+15)= GAMT
C
        ID2 = ID2+15
C
C---costanti di normalizzazione
C
        CNXYU(IV1  ) = P0
        CNXYU(IV1+1) = 1.
        CNXYU(IV1+2) = 1.
        CNXYU(IV1+3) = 1.
        CNXYU(IV1+4) = T0
        
        CNXYU(IV1+5) = H0
        CNXYU(IV1+6) = T0
        CNXYU(IV1+7) = H0
        CNXYU(IV1+8) = T0
        CNXYU(IV1+9) = W0
        CNXYU(IV1+10) = W0
        CNXYU(IV1+11) = W0
        CNXYU(IV1+12) = P0
        CNXYU(IV1+13) = P0
        CNXYU(IV1+14) = H0
        CNXYU(IV1+15) = GAM0
        
        CNXYU(IV1+16) = W0
        CNXYU(IV1+17) = W0
        CNXYU(IV1+18) = 1.
        CNXYU(IV1+19) = H0
        CNXYU(IV1+20) = W0
        CNXYU(IV1+21) = W0
        CNXYU(IV1+22) = H0
        CNXYU(IV1+23) = W0
        DO I=1,NCEL
           CNXYU(IV1+23+I)=T0
        ENDDO
        CNXYU(IV1+NCEL+24)=T0
        CNXYU(IV1+NCEL+25)=1.
C
        RETURN
        END
C************************************************************************
        SUBROUTINE BEV0C1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
        DIMENSION AJAC(MX5,1),XYU(1),DATI(1),RNI(1)
C
C---Desalinator evaporation cell
C
        PARAMETER (MAXCI=9)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
        EXTERNAL BEV0
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
        NCI=DATI(IPD+4)
        NSTATI=5
        NUSCIT=11
        NINGRE=10+NCI
        NVAR=NSTATI+NUSCIT+NINGRE
        NEQZ=NSTATI+NUSCIT
C
        GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100   DO I=1,NEQZ
           DO J =1,NVAR
              AJAC(I,J) = 1.
           ENDDO
        ENDDO
        RETURN
C
C---calcolo residui
C
  200   CONTINUE
        CALL BEV0(IFUN,IXYU,XYU,IPD,DATI,RNI)
        RETURN
C
C---calcolo jacobiano 
C
  300   CONTINUE
C
      EPS   =1.E-3
      EPSLIM=1.E-4
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,BEV0)
C
      RETURN                
      END
C*********************************************************************
        SUBROUTINE BEV0(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
        REAL LEVB,LEVD
C
        DIMENSION XYU(1),DATI(1),RNI(1)
C
C---Desalinator evaporation cell
C                     
        PARAMETER (GI=9.81)
        PARAMETER (MAXCI=9)
        PARAMETER (GAM0=1000.)
C
        DIMENSION TM(MAXCI)
C
        COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
        COMMON/PARPAR/NUL(7),ITERT
        COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
        LOGICAL KREGIM
        COMMON/REGIME/KREGIM
C
C---decodifica dati
C
        VTOT   = DATI(IPD  )
        HEIGHT = DATI(IPD+1)
        AD     = DATI(IPD+2)
        ADIS   = DATI(IPD+3)
        ACEL   = DATI(IPD+4)
        BASE   = DATI(IPD+5)
        PERI   = DATI(IPD+6)
        AEXT   = DATI(IPD+7)
        AS     = DATI(IPD+8)
        SCEL   = DATI(IPD+9)
        CTMET  = DATI(IPD+10)
        GAMBRI = DATI(IPD+11)
        GAMSTE = DATI(IPD+12)
        GAMDIS = DATI(IPD+13)
        GAMEXT = DATI(IPD+14)
        GAMT   = DATI(IPD+15)
C
        NCEL = ACEL
C
C---decodifica variabili
C
        P    = XYU(IXYU  )*P0
        LEVB = XYU(IXYU+1)
        LEVD = XYU(IXYU+2)
        FNAC = XYU(IXYU+3)
        TMEC = XYU(IXYU+4)*T0
        HBRN = XYU(IXYU+5)*H0
        T    = XYU(IXYU+6)*T0
        HDIS = XYU(IXYU+7)*H0
        TDIS = XYU(IXYU+8)*T0
        WEV  = XYU(IXYU+9)*W0
        WFL  = XYU(IXYU+10)*W0
        WCOND= XYU(IXYU+11)*W0
        PFBR = XYU(IXYU+12)*P0
        PFDS = XYU(IXYU+13)*P0
        HSTE = XYU(IXYU+14)*H0
        GATU = XYU(IXYU+15)*GAM0
        WBRI = XYU(IXYU+16)*W0
        WBRO = XYU(IXYU+17)*W0
        FNAI = XYU(IXYU+18)
        HBRI = XYU(IXYU+19)*H0
        WDI  = XYU(IXYU+20)*W0
        WDO  = XYU(IXYU+21)*W0
        HDI  = XYU(IXYU+22)*H0
        WSTP = XYU(IXYU+23)*W0
        DO I=1,NCEL
           TM(I)=XYU(IXYU+23+I)*T0
        ENDDO
        TEST = XYU(IXYU+NCEL+24)*T0
        AGAM = XYU(IXYU+NCEL+25)

C
C---calcolo superfici e coefficienti di scambio
C
        ABRI = LEVB * PERI
        ASTE = BASE + (HEIGHT-LEVB) * PERI - ADIS
C
        GAMBRI =ABRI * GAMBRI
        GAMSTE =ASTE * GAMSTE
        GAMDIS =ADIS * GAMDIS
        GAMEXT =AEXT * GAMEXT
C
C---calcolo proprietà fluidi
C
        CALL TSAT_FOR(P,FNAC,TSATS)
        CALL ROC_FOR(FNAC,TSATS,P,ROS)
        CALL H_FOR(TSATS,P,ROS,FNAC,HS)
        CALL DUSATDP_FOR(P,FNAC,DUSATDPS)
        CALL DHSATDF_FOR(P,TSATS,FNAC,DHSATDFS)
        
        CALL SATUR(P,3,ROWS,ROVS,1)
        CALL SATUR(P,2,HWS,HVS,1)
        CALL SATUR(P,7,TSAT,NUL,1)
        HVAP = HEV(P,STEV(P,T,1.,1),1)
        
        PPLUS = 1.1*P
        CALL SATUR(PPLUS,3,ROWSPLUS,ROVSPLUS,1)
        CALL SATUR(PPLUS,2,HWSPLUS,HVSPLUS,1)
        DRWSDP=(ROWSPLUS-ROWS)/(0.1*P)
        DRVSDP=(ROVSPLUS-ROVS)/(0.1*P)
        DHWSDP=(HWSPLUS-HWS)/(0.1*P)

C       WRITE(6,*) HS,TSATS,HWS,HVS,HVAP
C
C---calcolo residui
C
        POWTUB = 0.
        DO I=1,NCEL
           POWTUB = POWTUB+(T-TM(I))
        ENDDO
        POWTUB = POWTUB*GATU*SCEL
C
        IF(KREGIM) GO TO 1000
C
C------------------------------------ TRANSITORIO
C 
        PPOINT = (WEV-WCOND+WFL-WSTP)/(DRVSDP*(VTOT-AS*LEVB-AD*LEVD))
        FPOINT = (WBRI*(FNAI-FNAC)+FNAC*WEV)/(ROS*AS*LEVB)
        HPOINT = (DUSATDPS+1./ROS)*PPOINT+DHSATDFS*FPOINT
C
        RNI(1) = PPOINT/P0
        RNI(2) = (WBRI-WBRO-WEV)/(ROS*AS)
        RNI(3) = (WDI-WDO-WFL+WCOND-DRWSDP*PPOINT*AD*LEVD)/(ROWS*AD)
        RNI(4) = FPOINT
        RNI(5) = (GAMBRI*(T-TMEC)+GAMDIS*(TDIS-TMEC)+
     $            GAMSTE*(T-TMEC)+GAMEXT*(TEST-TMEC))/(CTMET*T0)
        RNI(6) = (HBRN-HS)/H0
        RNI(7) = (T-TSATS)/T0
        RNI(8) = (HDIS-HWS)/H0
        RNI(9) = (TDIS-TSAT)/T0
        RNI(10)= (-WEV*(HVAP-HS)+WBRI*(HBRI-HS)-GAMBRI*(T-TMEC)
     $            -ROS*AS*LEVB*(HPOINT-PPOINT/ROS))/(W0*H0)
        RNI(11)= (-WFL*(HVS-HWS)+WDI*(HDI-HWS)-GAMDIS*(TDIS-TMEC)
     $            -ROWS*AD*LEVD*(DHWSDP-1./ROWS)*PPOINT)/(W0*H0)
        RNI(12)= (-WCOND*(HVAP-HWS)+POWTUB)/(W0*H0)
        RNI(13)= (PFBR-P-ROS*GI*LEVB)/P0
        RNI(14)= (PFDS-P-ROWS*GI*LEVD)/P0
        RNI(15)= (HSTE-HVAP)/H0
        RNI(16)= (GATU-AGAM*GAMT)/GAM0
C
        RETURN
C
C------------------------------------ STAZIONARIO
C
 1000   CONTINUE
        RNI(1) = (WEV-WCOND+WFL-WSTP)/W0
        RNI(2) = (WBRI-WBRO-WEV)/W0
        RNI(3) = (WDI-WDO-WFL+WCOND)/W0
        RNI(4) = (WBRI*(FNAI-FNAC)+FNAC*WEV)/W0
        RNI(5) = (GAMBRI*(T-TMEC)+GAMDIS*(TDIS-TMEC)+
     $            GAMSTE*(T-TMEC)+GAMEXT*(TEST-TMEC))/(W0*H0)
        RNI(6) = (HBRN-HS)/H0
        RNI(7) = (T-TSATS)/T0
        RNI(8) = (HDIS-HWS)/H0
        RNI(9) = (TDIS-TSAT)/T0
        RNI(10)= (-WEV*(HVAP-HS)+WBRI*(HBRI-HS)-GAMBRI*(T-TMEC))
     $           /(W0*H0)
        RNI(11)= (-WFL*(HVS-HWS)+WDI*(HDI-HWS)-GAMDIS*(TDIS-TMEC))
     $           /(W0*H0)
        RNI(12)= (-WCOND*(HVAP-HWS)+POWTUB)/(W0*H0)
        RNI(13)= (PFBR-P-ROS*GI*LEVB)/P0
        RNI(14)= (PFDS-P-ROWS*GI*LEVD)/P0
        RNI(15)= (HSTE-HVAP)/H0  
        RNI(16)= (GATU-AGAM*GAMT)/GAM0      
C
        RETURN
        END
C************************************************************************
       SUBROUTINE BEV0D1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C       IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
       RETURN
       END
