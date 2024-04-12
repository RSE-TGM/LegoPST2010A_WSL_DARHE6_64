      SUBROUTINE ECRII2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C 
      LOGICAL KREGIM

      COMMON/ECRI01/IBLOC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      REAL NUMT, LUNGF, LUNGT, NA,NUMF,NPER                                        !SNGL
      CHARACTER*4 IBLOC*8,NOMCAR
C
C---SCAMBIATORE DI CALORE, ECONOMIZZATORE-RISCALDATORE 
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'TIPO    '
     $             ,'DIAM_EST'
     $             ,'DIAM_INT'
     $             ,'FA      '
     $             ,'LUNGHEZZ'
     $             ,'COND_TUB'
     $             ,'CRIG    '
     $             ,'DELZ    '
      WRITE(14,500) 'DIS_ALET'
     $             ,'NUM_ALET'
     $             ,'SPES_ALE'
     $             ,'ALTE_ALE'
     $             ,'COND_ALE'
     $             ,'TEMP_EST'
     $             ,'PAS_TRAS'
     $             ,'PAS_LONG'
     $             ,'NPERFILA'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) DISCAM
     $            ,DIAE
     $            ,DIAI
     $            ,FA
     $            ,LUNGT
     $            ,CONDT
     $            ,CRIG
     $            ,DELZ
      READ(14,501) DALE
     $            ,NA
     $            ,SPA
     $            ,ALTA
     $            ,CONDA
     $            ,TEXT
     $            ,PASP
     $            ,PASL
     $            ,NPER      
C
      WRITE(NOMCAR,'(A4)')IBL1
      IWP=0
      IF(NOMCAR(1:1).EQ.'+') IWP=1
C
      IF (NPER.EQ.0) NPER=1.
      IF (DISCAM.EQ.3.AND.DALE.EQ.2) THEN
          WRITE (6,*) 'GEOMETRIA IMPOSSIBILE'
          DALE=1
      ENDIF

  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
   
      OPTL=RADL12(PASP/DIAE,PASL/DIAE,DIAE)
      DATI(ID2   ) = DISCAM
      DATI(ID2+ 1) = DIAE
      DATI(ID2+ 2) = DIAI
      DATI(ID2+ 3) = FA
      DATI(ID2+ 4) = LUNGT
      DATI(ID2+ 5) = CONDT
      DATI(ID2+ 6) = CRIG
      DATI(ID2+ 7) = DALE
      DATI(ID2+ 8) = NA
      DATI(ID2+ 9) = SPA
      DATI(ID2+10) = ALTA
      DATI(ID2+11) = CONDA
      DATI(ID2+12) = TEXT
      DATI(ID2+13) = OPTL
      DATI(ID2+14) = PASP
      DATI(ID2+15) = DELZ
      DATI(ID2+16) = PASL
      DATI(ID2+17) = NPER
      DATI(ID2+18) = IWP
      ID2 = ID2+18
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = T0
      CNXYU(IV1+ 1) = H0
      CNXYU(IV1+ 2) = P0
      CNXYU(IV1+ 3) = T0
      CNXYU(IV1+ 4) = T0
      CNXYU(IV1+ 5) = W0*H0
      CNXYU(IV1+ 6) = W0*H0/100/100/T0
      CNXYU(IV1+ 7) = 10000.
      CNXYU(IV1+ 8) = 1.
      CNXYU(IV1+ 9) = 1.
      CNXYU(IV1+10) = W0
      CNXYU(IV1+11) = T0
      CNXYU(IV1+12) = 1.
      CNXYU(IV1+13) = 1.
      CNXYU(IV1+14) = 1.
      CNXYU(IV1+15) = H0
      CNXYU(IV1+16) = W0
      CNXYU(IV1+17) = P0
      CNXYU(IV1+18) = 1.
      CNXYU(IV1+19) = 1.
      CNXYU(IV1+20) = 1.
      CNXYU(IV1+21) = 1.
C
C________RENDIMENTO EXERG.
C
      TOL(10)=1.E-2
      RETURN
      END
C
C
C
      SUBROUTINE ECRIC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
      COMMON/PARPAR/NUL(7),ITERT
C
      EXTERNAL ECRI
C
      REAL NUMT, LUNGT, NA, NUMF                                               !SNGL
C 
C---SCAMBIATORE DI CALORE 
C
     
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL ECRIJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
      RETURN
C
C---calcolo residui
C
  200 CALL ECRI (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C$*$
  300 CONTINUE
  
      CALL ECRIJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C----------
C
      SUBROUTINE ECRIJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                           !SNGL
      COMMON/PARPAR/NUL(7),ITERT
C
      EXTERNAL ECRI
C
      REAL NUMT, LUNGT, NA ,NUMF,NPER                                    !SNGL
C      DOUBLE PRECISION NUMT, LUNG, NA                                   !DBLE
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
      DO I=1,10
       DO J=1,22
       AJAC(I,J)=1.
      ENDDO    
      ENDDO     
    
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 10
      NINGRE = 12
      EPS    = 1.E-3
      EPSLIM = 1.E-6
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     &            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,ECRI) 
      RETURN
      END
C
C
C
      SUBROUTINE ECRI (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
      COMMON/PARPAR/NUL(7),ITERT
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL NUMT ,LUNGT, NA, NUT ,NUMF ,MOLT,NPER                         !SNGL
C      DOUBLE PRECISION NUMT, LUNG, NA                                   !DBLE
C
C---SCAMBIATORE DI CALORE 
C   calcolo residui
C
C---decodifica variabili e dati
C
      IWP=DATI(IPD+18)
C
      TUFX   = XYU(IXYU   )
      HUVX   = XYU(IXYU+ 1)
      IF (IWP.EQ.0) THEN
         PUVX   = XYU(IXYU+ 2)
      ELSE
         PIVX   = XYU(IXYU+ 2)
      ENDIF
      TUVX   = XYU(IXYU+ 3)
      TMTX   = XYU(IXYU+ 4)
      QOTX   = XYU(IXYU+ 5)
      FSTX   = XYU(IXYU+ 6)
      SUPX   = XYU(IXYU+ 7)
      EFAL   = XYU(IXYU+ 8)
      EXER   = XYU(IXYU+ 9)
      WIFX   = XYU(IXYU+10)
      TIFX   = XYU(IXYU+11)
      PCO2   = XYU(IXYU+12)/100
      PH2O   = XYU(IXYU+13)/100
      FH2O   = XYU(IXYU+14)/100
      HIVX   = XYU(IXYU+15)
      WIVX   = XYU(IXYU+16)
      IF (IWP.EQ.0) THEN
         PIVX   = XYU(IXYU+17)
      ELSE
         PUVX   = XYU(IXYU+17)
      ENDIF
      ATTR   = XYU(IXYU+18)
      FASX   = XYU(IXYU+19)
      NUMT   = XYU(IXYU+20)
      NUMF   = XYU(IXYU+21)
C
      IF (FASX.LT.1.E-6) FASX=1.E-6
C
      DISCAM =DATI(IPD   )
      DIAE   =DATI(IPD+ 1)
      DIAI   =DATI(IPD+ 2)
      FA     =DATI(IPD+ 3)
      LUNGT  =DATI(IPD+ 4)
      CONDT  =DATI(IPD+ 5)
      CRIG   =DATI(IPD+ 6)
      DALE   =DATI(IPD+ 7)
      NA     =DATI(IPD+ 8)
      SPA    =DATI(IPD+ 9)
      ALTA   =DATI(IPD+10)
      CONDA  =DATI(IPD+11)
      TEXT   =DATI(IPD+12)
      OPTL   =DATI(IPD+13) 
      PASP   =DATI(IPD+14)
      DELZ   =DATI(IPD+15)
      PASL   =DATI(IPD+16)
      NPER   =DATI(IPD+17)
CC 
CC-- CALCOLO DELLE SUPERFICI
CC-- SA=SUPERFICIE D'ALETTE
CC-- SB=SUPERFICIE DEL TUBO SENZA ALETTA
CC-- SUPTOT=SUPERFICIE TOTALE

CC-- CASO SENZA ALETTA
      
      IF (NA.EQ.0) THEN
      SA=0
      SB=3.14*DIAE*NUMF*LUNGT*NUMT   
 
      ELSE IF (DALE.EQ.1) THEN
 
CC-- CASO CON ALETTE ELICOIDALI
     
      HAUT=.5/NA
      HYP=SQRT((DIAE+2*ALTA)**2+HAUT**2)
      COSA=(DIAE+2*ALTA)/HYP
      TANA=HAUT/(DIAE+2*ALTA)
csup      SA=(((DIAE+2*ALTA)*(DIAE+2*ALTA)-DIAE*DIAE)/2
csup     $ +SPA*(DIAE+2*ALTA))*3.14*NA*NUMT*NUMF*LUNGT/COSA

      SA=(((DIAE+2*ALTA)**2-DIAE**2)/2/cosA+SPA*
     $  2*SQRT((DIAE+2*ALTA)**2*(1+1/COSA**2)/8))
     $   *3.14*NA*NUMT*NUMF*LUNGT
    
csup     SB=(1-SPA*NA)*NUMT*NUMF*LUNGT*3.14*DIAE
      SB=(3.14*DIAE-6.28*SQRT(DIAE**2*(1+1/COSA**2)/8)*SPA*NA)
     $    *LUNGT*NUMT*NUMF
     
      ELSE IF (DALE.EQ.2) THEN

CC-- CASO CON ALETTE LONGITUDINALI

      SA=(2*ALTA+SPA)*NUMT*NUMF*LUNGT
      SB=(3.14*DIAE-SPA*NA)*NUMF*LUNGT*NUMT
     
      ELSE IF (DALE.EQ.3) THEN

CC-- CASO CON ALETTE CIRCOLARI

      SA=(((DIAE+2*ALTA)*(DIAE+2*ALTA)-DIAE*DIAE)/2
     $ +SPA*(DIAE+2*ALTA))*3.14*NA*NUMT*NUMF*LUNGT
      SB=(1-SPA*NA)*NUMT*NUMF*LUNGT*3.14*DIAE
      ENDIF     
      SUPTOT=(SA+SB)/10000.
      SI = 3.14*DIAI*DIAI*NUMT*NPER/4       !sez.= un tubo*ntubi ENTRANTI,cioe'    
CC                                                 n.ro percorsi.
CC-- SUP=SUPERFICIE DI PASSAGIO FUMO
CC-- CALCOLO DI DIAMEQ PER IL COEFFICIENTE CONVETTIVO

      IF (DALE.EQ.2) THEN      
      LARG=PASP*(NUMT+1)
      HAUT=PASL*(NUMF+1)
      SUP=LARG*HAUT

      ELSE
      LARG=PASP*(NUMT+1)
      SUP=LUNGT*LARG
      ENDIF      

      IF (NA.EQ.0) THEN 

        IF (DALE.EQ.2) THEN
           SUP=SUP-3.14*NUMF*NUMT*DIAE**2/4
           DIAMEQ=4*SUP/(3.14*DIAE*NUMT*NUMF+2*LARG+2*HAUT)
        ELSE
Csup           SUP=SUP-DIAE*LUNGT*(SUP/LUNGT/PASP-1)
           SUP=SUP*(1-DIAE/PASP)	!sezione di passaggio
           DIAMEQ=DIAE
        ENDIF

      ELSE IF (DALE.EQ.1) THEN  

CC-- CASO TUBI A ALETTE ELICOIDALI
      SUP=SUP-(DIAE+2*SPA*ALTA*NA/COSA)*LUNGT*(SUP/LUNGT/PASP-1)
      DIAMEQ=DIAE+2*SPA*ALTA*NA
c*	write(6,*)'sezione passaggio',sup
      ELSE IF (DALE.EQ.2) THEN

CC-- CASO TUBI A ALETTE LONGITUDINALI
      SUP=SUP-(3.14*DIAE**2/4+NA*SPA*ALTA)*SUP/PASP/PASL
C      DIAMEQ=4*SQRT(3.14*DIAE**2/4+NA*SPA*ALTA)/3.14
      DIAMEQ=4*SUP/(3.14*DIAE*NUMT*NUMF+NA*(2*SPA+ALTA)*NUMT*NUMF
     &                          +2*LARG+2*HAUT) 
     
      ELSE IF (DALE.EQ.3) THEN 

CC-- CASO TUBI A ALETTE CIRCOLARI
      SUP=SUP-(DIAE+2*SPA*ALTA*NA)*LUNGT*(SUP/LUNGT/PASP-1)      
      DIAMEQ=DIAE+2*SPA*ALTA*NA
	write(6,*)'sezione passaggio',sup
      ENDIF

CC-- VALORE DELLA TEMPERATURA D'INGRESSO D'ACQUA-VAPORE
      
      SI1=SHEV(PIVX*P0,HIVX*H0,1)

      TIV=TEV(PIVX*P0,SI1,1)/T0

CC--
CC-- APPROSSIMAZIONE DI QUALQUE VALORE MEDIA D'ACQUA-VAPORE
CC--

      PAC=(PIVX+PUVX)*P0/2
        IF (TIV/TUVX.LE.0.) THEN
           WRITE(6,*) '$$$$$$$$$$$$$$$ TIV/TUVX < 0 !!!',
     &                ' TIV=',TIV,' TUVX=',TUVX
        ENDIF
        TAC=(TIV-TUVX)*T0/LOG(ABS(TIV/TUVX))
 

      IF (HIVX/HUVX.LE.0.) THEN
         WRITE(6,*) '$$$$$$$$$$$$$$$ HIVX/HUVX < 0 !!!',
     &              ' HIVX=',HIVX,' HUVX=',HUVX
      ENDIF
      HAC=(HIVX-HUVX)*H0/LOG(ABS(HIVX/HUVX)) 
C     HAC=(HIVX+HUVX)*H0/2  
      SAC=SHEV(PAC,HAC,1)
      RAC=ROEV(PAC,SAC,1)
      TIT=YEV(PAC,SAC,1)
      CPAC=(HUVX-HIVX)*H0/(TUVX-TIV)/T0
CC--
CC-- TEMPERATURA MEDIA DI FUMO
CC--
      IF(ABS(TIFX-TUFX).LT.1.E-5) THEN
       TF=TUFX
      ELSE
       TF=(TUFX-TIFX)*T0/LOG(TUFX/TIFX)
      ENDIF
CC--
CC-- TEMPERATURE DI TUBO
CC-- T1=LATO FUMO
CC-- T2=LATO ACQUA-VAPORE
 
       RT2=2*CONDT/DIAE/LOG(2*DIAE/(DIAI+DIAE))
       RT3=2*CONDT/DIAE/LOG((DIAI+DIAE)/2/DIAI)
       T1=TMTX*T0+QOTX*W0*H0/RT2/SB
       T2=TMTX*T0-QOTX*W0*H0/RT3/SB
       TFILME=(TF+T1)/2

CC--
CC-- CALCOLO DEL COEFFICIENTE CONVETTIVO ESTERNO HO
CC--

      IF (DALE.NE.2) THEN

      CALL UC12(TFILME,WIFX*W0,FH2O*100,SUP,DIAMEQ,FA,
     $          IFUN,UCC,DUCDTF,DUCDTM)
      CALL UR12(TF-TMTX*T0,TMTX*T0,PH2O,PCO2,OPTL,
     $           IFUN,UR,DURDTF,DURDTM,DURDPGAS) 
    
      ELSE 

CC    BISOGNA METTERE UNA CORRELAZIONE PER IL CASO
CC    SCAMBIO LONGITUDINALE AI TUBI 

      CALL UC12(TFILME,WIFX*W0,FH2O*100,SUP,DIAMEQ,FA,
     $          IFUN,UCC,DUCDTF,DUCDTM)
      CALL UR12(TF-TMTX*T0,TMTX*T0,PH2O,PCO2,OPTL,
     $           IFUN,UR,DURDTF,DURDTM,DURDPGAS)
 
      ENDIF      
cdeb      IF (IFUN.EQ.2) THEN
cdeb         WRITE(6,*) 'UCC= ',UCC,'TFILME= ',TFILME
cdeb         WRITE(6,*) 'UR= ',UR,'TF-TMTX= ',TF-TMTX
cdeb      ENDIF

      HO=(UCC+UR)*FASX

CC--        
CC-- CALCOLO DEL COEFFICIENTE CONVETTIVO INTERNO HI
CC--     
   
      IF (CRIG.GT.0.AND.CRIG.LT.20) THEN
  
      CALL GAM01(PAC,HAC,SAC,TAC,RAC,TIT,T2,
     $      DIAI,CRIG,WIVX*W0/SI,QOTX*W0*H0,
     $            3.14*DIAI*NUMF*LUNGT*NUMT,HI)      
      ELSE
CC--
      CALL ECRIGTERT(PAC,HAC,SAC,TAC,RAC,TIT,T2,DIAI,CRIG,
     &      abs(WIVX*W0/SI),QOTX*W0*H0,3.14*DIAI*NUMF*LUNGT*NUMT,HI)
      ENDIF
cdeb      IF (IFUN.EQ.2) WRITE(6,*) 'sez. totale tubi ',SI
cdeb      IF (IFUN.EQ.2) WRITE(6,*)' velocita ',WIVX*W0/SI/RAC  
cdeb      IF (IFUN.EQ.2) WRITE(6,*) 'COEF. lato acqua =',HI
CC--
CC-- CALCOLO DELL'EFFICACIA DELL'ALETTA
CC--    
       EFFA=1
C       
       IF (NA.NE.0) THEN
C       
CC-- CALCOLO PER ALETTA LONGITUDINALE
       FCOR=0
       ALPHA=SQRT(2*HO/CONDA/SPA)
       XX=ALPHA*ALTA
       EFFA=(EXP(XX)-EXP(-XX))/(EXP(XX)+EXP(-XX))/XX
CC-- CORREZIONE PER ALETTA CIRCOLARE
       IF (DALE.NE.2) THEN
       FCOR=((DIAE+2*ALTA)/DIAE-1)*0.06
       IF (XX.LT.2.) FCOR=FCOR*XX**.585
       ENDIF
       EFFA=EFFA-FCOR
       ENDIF
C
       MOLT=1+EFAL*SA/SB
C
CC--     
CC-- CALCOLO DEL COEFFICIENTE DI SCAMBIO GLOBALE CA
CC--    
       RT=2*CONDT/DIAE/LOG(DIAE/DIAI)
       RE=HO*MOLT
       RI=HI*DIAI/DIAE
       CA=1/(1/RI+1/RT+1/RE)
C
CC-- CALCOLO DI CMIN E CMAX
C
	HIN=HTFU(TIFX*T0,FH2O,1)
	HUS=HTFU(TUFX*T0,FH2O,1)
	QFUM=WIFX*W0*(HIN-HUS)/1.e6	
        IF(ABS(TIFX-TUFX).LT.1.E-5) THEN
         CPF=CPFU(TF,FH2O) 
        ELSE
         CPF=(HIN-HUS)/(TIFX-TUFX)/T0      
C       CPF=(HIN-HUS)/(TIFX-TUFX)/T0/.955   !modifica per Trino
	ENDIF
        CFUM=WIFX*W0*CPF
        CACQ=CPAC*WIVX*W0
C
C------stampe per debug
C
C	IF(IFUN.EQ.2)THEN
C	QFUM=WIFX*W0*(HIN-HUS)/1.e6 
C       	write(6,*)'entalpie fumi in e out,potenza calc. con HTFU:'
C	        write(6,*)HIN,HUS,QFUM
C               write(6,*)'Cp fumi:',CPF
C	ENDIF
C       IF(IFUN.EQ.2) WRITE(6,*) 'CPFUMO =',CPF
C       WRITE (6,*) 'CFUM=',CFUM
C       WRITE(6,*) 'CACQ=',CPAC
C------fine
C
       IF (CACQ.LE.CFUM) THEN
             CMIN=CACQ
             CMAX=CFUM
       ELSE 
             CMIN=CFUM
             CMAX=CACQ
       ENDIF
CC--
CC-- CALCOLO DEL NUT
CC--    
       FC=1.
       IF (DISCAM.EQ.3) THEN
C
CC-- CASO FLUSSO INCROCIATO
       VI=abs((TUVX-TIV)/(TIFX-TUFX))
       EPS=abs((TUVX-TIV)/(TIFX-TIV))
       IF (EPS.GT.1) EPS=1.
       CALL CORRECRI(VI,EPS,FC)
       ENDIF    
 
       NUT=FC*FSTX*W0*H0*SUPX/CMIN/T0

CC--         
CC-- CALCOLO DELL'EFFICACIA
CC--
CC--CASO SCAMBIATORE CONTRO-CORRENTE O INCROCIATO
       IF (DISCAM.NE.2) EEFF=(1-EXP(-(1-CMIN/CMAX)*NUT))
     $      /(1-CMIN*EXP(-(1-CMIN/CMAX)*NUT)/CMAX)

CC-- CASO SCAMBIATORE PARALLELO  
       IF (DISCAM.EQ.2) EEFF=(1-EXP(-(1+CMIN/CMAX)*NUT))
     $         /(1+CMIN/CMAX)

CC--
CC-- CALCOLO DELLA POTENZA
CC--
       POT=EEFF*CMIN*(TIFX-TIV)*T0
CC--
CC-- ENTALPIA E TEMPERATURA D'USCITA VAPORE
CC--
       HUV=QOTX*H0/WIVX+HIVX*H0    
       SUV=SHEV(PUVX*P0,HUV,1)
       TUV=TEV(PUVX*P0,SUV,1)        
CC--
CC-- CADUTA DI PRESSIONE       
CC--    
C							!lunghezza percorso =
      GAMT=2*LUNGT*NUMF/(NPER*DIAI*SI**2)		!lungh*npassi/percorsi 
C      							!per fila 
      GAML=GAMT*SI/10
      WREAL=WIVX*W0
      DELTAP=ATTR*GAMT*WREAL*ABS(WREAL)/RAC+RAC*9.8*DELZ
     &    +ATTR*GAML*WREAL
      PUS=PIVX*P0-DELTAP 

CC--
CC-- TRASMITTANZA PARETE
CC--    
      CA2=1/(1/RE+1/RT2)
CC--
CC-- RENDIMENTO EXERGETICO
CC--
      DELTACQ=HUVX*H0-HIVX*H0-TEXT*(SUV-SI1)
      REND=WREAL*DELTACQ/(1-TEXT/TF)/QOTX/W0/H0
CC--
C--residuo n.  1 (equazione algebrica)   *******
      RNI(1) = QOTX-CFUM*(TIFX-TUFX)*T0/(W0*H0)
C
C--residuo n.  2 (equazione algebrica)   *******
      RNI(2) = QOTX-WREAL*(HUVX-HIVX)*H0/(W0*H0)
C
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3) = PUVX-PUS/P0
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4) = TUVX-TUV/T0
C
C--residuo n.  5 (equazione algebrica)   *******
C
      RNI(5) = CA2*SB*(TMTX*T0-TF)/(W0*H0)+QOTX
C
C--residuo n.  6 (equazione algebrica)   *******
C 
      RNI(6) = QOTX-POT/W0/H0
C
C--residuo n.  7 (equazione algebrica)   *******
C
      RNI(7) = FSTX-CA*SB*T0*10000./(SA+SB)/W0/H0
C
C--residuo n.  8 (equazione algebrica)   *******
C
      RNI(8) = SUPX-(SA+SB)/10000.
C
C--residuo n.  9 (equazione algebrica)   *******
C
      RNI(9) = EFAL-EFFA
C
C--residuo n. 10 (equazione algebrica)   *******
C
      RNI(10) = EXER-REND      
C
C        
C
C STAMPA PER VERIFICA SACCADURA
C      
C      WRITE (6,*) ' VI, EPS, FC :', VI, EPS, FC
      RETURN
      END
C
C--------
C
      SUBROUTINE CORRECRI(VI,EPS,FC)
C
C     CALCOLO DEL COEFFICIENTE DI CORREZIONE PER 
C     UNO SCAMBIATORE INCROCIATO
C
C     VALORI STEAM P 4-13 
C
      PARAMETER (LVI=17,LEPS=11,LFC=LVI*LEPS)
      DIMENSION TABVI(LVI),TABEPS(LEPS),TABFC(LFC)

      DATA TABVI/0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.8,
     $          1.0,1.25,1.5,2.0,2.5,3.,4.,5.,10./
      DATA TABEPS/0.,0.1,0.2,.3,.4,.5,.6,.7,.8,.9,1./
      DATA TABFC/1.,.9,.0,.0,.0,.0,.0,.0,.0,.0,.0,
     &           1.,.97,.0,.0,.0,.0,.0,.0,.0,.0,.0,
     &           1.,.987,.75,0.,0.,0.,.0,.0,.0,.0,.0,
     &           1.,.99,.947,.65,0.,0.,0.,0.,0.,0.,0.,
     &           1.,.999,.973,.89,.5,0.,0.,0.,0.,0.,.0,
     &           1.,1.,.98,.933,.813,.4,0.,0.,0.,0.,0.,
     &           1.,1.,.987,.953,.873,.72,.3,0.,.0,.0,.0,
     &           1.,1.,.987,.97,.927,.847,.72,.523,0.,.0,.0,
     &           1.,1.,.99,.98,.953,.893,.813,.72,.52,0.,.0,
     &           1.,1.,1.,.987,.967,.927,.873,.787,.653,.473,0.,
     &           1.,1.,1.,.987,.973,.947,.9,.833,.733,.58,.3,
     &           1.,1.,1.,.99,.987,.963,.933,.887,.813,.7,.4,
     &           1.,1.,1.,.999,.987,.97,.947,.913,.86,.767,.4,
     &           1.,1.,1.,1.,.99,.98,.96,.933,.887,.813,.4,
     &           1.,1.,1.,1.,.999,.983,.973,.933,.92,.86,.4,
     &           1.,1.,1.,1.,.993,.987,.98,.967,.94,.893,.5,
     &           1.,1.,1.,1.,1.,.993,.99,.985,.973,.953,.7/ 

    
      CALL LINTAB(TABVI,LVI,TABEPS,LEPS,TABFC,EPS,VI,FC,Z1,Z2)
      IF (ABS(FC).GT.1) FC=1.
      
      RETURN
      END        
C-----
      SUBROUTINE ECRII3 (IFO,IOB,DEBL)
C
      COMMON/ECRI01/IBLOC
      COMMON/ECRI02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMAPP  
      DATA MOD/'ECRI'/
C
      CALL ECRII4(IOB,MOD)

      NSTATI = 0
      NUSCIT = 10
      NINGRE = 12
C
      IWP=0
      IF(IBLOC(1:1).EQ.'+')IWP=1      
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('TUFX',A4,2X,
     $  57H--UA-- TEMPERATURA USCITA FUMO                           )
      WRITE(IFO,3002)IOB
 3002 FORMAT('HUVX',A4,2X,
     $  57H--UA-- ENTALPIA USCITA ACQUA/VAPORE                      )
      IF(IWP.EQ.0) THEN
        WRITE(IFO,3003)IOB
      ELSE
        WRITE(IFO,3023)IOB
      ENDIF
 3003 FORMAT('PUVX',A4,2X,
     $  57H--UA-- PRESSIONE USCITA ACQUA/VAPORE                     )
 3023 FORMAT('PIVX',A4,2X,
     $  57H--UA-- PRESSIONE INGRESSO ACQUA/VAPORE                   )
      WRITE(IFO,3004)IOB
 3004 FORMAT('TUVX',A4,2X,
     $  57H--UA-- TEMPERATURA USCITA ACQUA/VAPORE                   )
      WRITE(IFO,3005)IOB
 3005 FORMAT('TMTX',A4,2X,
     $  57H--UA-- TEMPERATURA MEDIA TUBO                            )
      WRITE(IFO,3006)IOB
 3006 FORMAT('QOTX',A4,2X,
     $  57H--UA-- POTENZA SCAMBIATA                                 )
      WRITE(IFO,3007)IOB
 3007 FORMAT('FSTX',A4,2X,
     $  57H--UA-- FATTORE SCAMBIO TOTALE                            )
      WRITE(IFO,3008)IOB
 3008 FORMAT('SUPX',A4,2X,
     $  57H--UA-- SUPERFICIE SCAMBIO TOTALE                         )
      WRITE(IFO,3009)IOB
 3009 FORMAT('EFAL',A4,2X,
     $  57H--UA-- EFFICACIA ALETTE                                  )
      WRITE(IFO,3010)IOB
 3010 FORMAT('EXER',A4,2X,
     $  57H--UA-- RENDIMENTO EXERGETICO                             )
      WRITE(IFO,3011)IOB
 3011 FORMAT('WIFX',A4,2X,
     $  57H--IN-- PORTATA INGRESSO FUMO                             )
      WRITE(IFO,3012)IOB
 3012 FORMAT('TIFX',A4,2X,
     $  57H--IN-- TEMPERATURA INGRESSO FUMO                         )
      WRITE(IFO,3013)IOB
 3013 FORMAT('PCO2',A4,2X,
     $  57H--IN-- PRESSIONE PARZIALE CO2 FUMO                       )
      WRITE(IFO,3014)IOB
 3014 FORMAT('PH2O',A4,2X,
     $  57H--IN-- PRESSIONE PARZIALE H2O FUMO                       )
      WRITE(IFO,3015)IOB
 3015 FORMAT('FH2O',A4,2X,
     $  57H--IN-- FRAZIONE MASSICA H2O FUMO                         )
      WRITE(IFO,3016)IOB
 3016 FORMAT('HIVX',A4,2X,
     $  57H--IN-- ENTALPIA INGRESSO ACQUA/VAPORE                    )
      WRITE(IFO,3017)IOB
 3017 FORMAT('WIVX',A4,2X,
     $  57H--IN-- PORTATA INGRESSO ACQUA/VAPORE                     )
      IF(IWP.EQ.0) THEN
         WRITE(IFO,3018)IOB
      ELSE
         WRITE(IFO,3024)IOB
      ENDIF
 3018 FORMAT('PIVX',A4,2X,
     $  57H--IN-- PRESSIONE INGRESSO ACQUA/VAPORE                   )
      WRITE(IFO,3019)IOB
 3019 FORMAT('ATTR',A4,2X,
     $  57H--IN-- COEFFICIENTE ATTRITO TUBO                         )
 3024 FORMAT('PUVX',A4,2X,
     $  57H--IN-- PRESSIONE USCITA ACQUA/VAPORE                     )
      WRITE(IFO,3020)IOB
 3020 FORMAT('FASX',A4,2X,
     $  57H--IN-- FATTORE SPORCAMENTO TUBO                          )
      WRITE(IFO,3021)IOB
 3021 FORMAT('NUMT',A4,2X,
     $  57H--IN-- NUMERO TUBI PER FILA                              )
      WRITE(IFO,3022)IOB
 3022 FORMAT('NUMF',A4,2X,
     $  57H--IN-- NUMERO FILE                                       )
      RETURN
      END
C
C
C
      SUBROUTINE ECRII4 (IOB,MOD)
      COMMON/ECRI01/IBLOC
      COMMON/ECRI02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
      CHARACTER*4 MODU
      CHARACTER*1 ICA,IBL,IPIU
      DATA IBL/' '/
      DATA IPIU/'+'/
C
    2 CONTINUE
      WRITE(6,2999)
 2999 FORMAT(/5X,'INSERT A CHARACTER'
     $ /5X,' - OUTLET PRESSURE AS OUTPUT ===>   BLANK',
     $ /5X,' - INLET PRESSURE AS OUTPUT ====>   +')
      READ(5,3001)ICA
      IF(ICA.EQ.IPIU.OR.ICA.EQ.IBL)GO TO 1
      GO TO 2
 3001 FORMAT(A)
    1 CONTINUE
C
      WRITE(MODU,'(A1,A3)')ICA,MOD
      IF(ICA.EQ.IBL)MODU=MOD
      WRITE(IBLOC,'(2A4)')MODU,IOB
C
      RETURN
      END
C
      SUBROUTINE ECRID1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---SCAMBIATORE DI CALORE 
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO TUFX
C
C---descrizione equazione TUFX in stazionario (max. 50 car)
      SIGNEQ ( 1) ='TEMPERATURA USCITA FUMO'
C
C---unita` di misura residuo TUFX (max. 10 car)
      UNITEQ ( 1) = 'K'
C
C---costante di normalizzazione residuo TUFX in stazionario
      COSNOR ( 1) = T0
C
C---topologia jacobiano in stazionario per il residuo TUFX
C---equazione n.1 (algebrica):
C   ---dipendenza da TUFX
      ITOPVA(1,1)=1.
C   ---dipendenza da QOTX
      ITOPVA(1,6)=1.

C      IF (IWP.EQ.0) THEN
C   ---dipendenza da WIFX
      ITOPVA(1,11)=1.
C   ---dipendenza da TIFX
      ITOPVA(1,12)=1.
C   ---dipendenza da FH2O
      ITOPVA(1,15)=1.
           
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO HUVX
C
C---descrizione equazione HUVX in stazionario (max. 50 car)
      SIGNEQ ( 2) = 'ENTALPIA USCITA VAPORE'
C
C---unita` di misura residuo HUVX (max. 10 car)
      UNITEQ ( 2) = 'KJ/KG'
C
C---costante di normalizzazione residuo HUVX in stazionario
      COSNOR ( 2) = H0
C
C---topologia jacobiano in stazionario per il residuo HUVX
C   ---dipendenza da HUVX
      ITOPVA(2,2)=1.

C   ---dipendenza da PUVX
      ITOPVA(2,3)=1.
C   ---dipendenza da TUVX
      ITOPVA(2,4)=1.

C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO PUVX
C
C---descrizione equazione PUVX in stazionario (max. 50 car)
      SIGNEQ ( 3) = 'PRESSIONE VAPORE USCITA'
C
C---unita` di misura residuo PUVX (max. 10 car)
      UNITEQ ( 3) = 'Pa'
C
C---costante di normalizzazione residuo PUVX in stazionario
      COSNOR ( 3) = P0
C
C---topologia jacobiano in stazionario per il residuo PUVX
C   ---dipendenza da HUVX
      ITOPVA(3,2)=1.
C   ---dipendenza da PUVX
      ITOPVA(3,3)=1.

C   ---dipendenza da HIVX
      ITOPVA(3,16)=1.
C   ---dipendenza da WIVX
      ITOPVA(3,17)=1.
C   ---dipendenza da PIVX
      ITOPVA(3,18)=1.
C   ---dipendenza da ATTR
      ITOPVA(3,19)=1.
C   ---dipendenza da NUMT
      ITOPVA(3,21)=1.
C   ---dipendenza da NUMF
      ITOPVA(3,22)=1.
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO TUVX
C
C---descrizione equazione TUVX in stazionario (max. 50 car)
      SIGNEQ ( 4) ='TEMPERATURA USCITA VAPORE' 
C
C---unita` di misura residuo TUVX (max. 10 car)
      UNITEQ ( 4) ='K' 
C
C---costante di normalizzazione residuo TUVX in stazionario
      COSNOR ( 4) = P0 
C
C---topologia jacobiano in stazionario per il residuo TUVX
C   ---dipendenza da TUVX
      ITOPVA(4,4)=1.
C   ---dipendenza da PUVX
      ITOPVA(4,3)=1.
C   ---dipendenza da HUVX
      ITOPVA(4,2)=1.

C   ---dipendenza da QOTX
      ITOPVA(4,6)=1.
C   ---dipendenza da HIVX
      ITOPVA(4,20)=1.
C   ---dipendenza da PIVX
      ITOPVA(4,22)=1.
C   ---dipendenza da WIVX
      ITOPVA(4,21)=1.
C      ENDIF
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO TMTX
C
C---descrizione equazione TMTX in stazionario (max. 50 car)
      SIGNEQ ( 5) ='TEMPERATURA PARETE' 
C
C---unita` di misura residuo TMTX (max. 10 car)
      UNITEQ ( 5) = 'K'
C
C---costante di normalizzazione residuo TMTX in stazionario
      COSNOR ( 5) = T0
C
C---topologia jacobiano in stazionario per il residuo TMTX
C   ---dipendenza da TUFX
      ITOPVA(5,1)=1.
C   ---dipendenza da TMTX
      ITOPVA(5,5)=1.
C   ---dipendenza da QOTX
      ITOPVA(5,6)=1.
C   ---dipendenza da EFAL
      ITOPVA(5,9)=1.
C   ---dipendenza da WIFX
      ITOPVA(5,11)=1.
C   ---dipendenza da TIFX
      ITOPVA(5,12)=1.
C   ---dipendenza da PCO2
      ITOPVA(5,13)=1.
C   ---dipendenza da PH2O
      ITOPVA(5,14)=1.
C   ---dipendenza da FH2O
      ITOPVA(5,15)=1.
C   ---dipendenza da FASX
      ITOPVA(5,20)=1.
C   ---dipendenza da NUMT
      ITOPVA(5,21)=1.
C   ---dipendenza da NUMF
      ITOPVA(5,22)=1.

C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO QOTX
C
C---descrizione equazione POTX in stazionario (max. 50 car)
      SIGNEQ ( 6) = 'POTENZA '
C
C---unita` di misura residuo POTX (max. 10 car)
      UNITEQ ( 6) = 'W'
C
C---costante di normalizzazione residuo POTX in stazionario
      COSNOR ( 6) = W0*H0
C
C---topologia jacobiano in stazionario per il residuo QOTX
C   ---dipendenza da HUVX
      ITOPVA(6,2)=1.
C   ---dipendenza da QOTX
      ITOPVA(6,6)=1.
C   ---dipendenza da TUFX
      ITOPVA(6,1)=1.
C   ---dipendenza da TUVX
      ITOPVA(6,4)=1.
C   ---dipendenza da SUPX
      ITOPVA(6,8)=1.
                
C   ---dipendenza da HIVX
      ITOPVA(6,16)=1.
C   ---dipendenza da WIVX
      ITOPVA(6,17)=1.
C   ---dipendenza da WIFX
      ITOPVA(6,11)=1.
C   ---dipendenza da PIVX
      ITOPVA(6,18)=1.
C   ---dipendenza da TIFX
      ITOPVA(6,12)=1.
C   ---dipendenza da FH2O
      ITOPVA(6,15)=1.
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO FSTX
C
C---descrizione equazione FSTX in stazionario (max. 50 car)
      SIGNEQ ( 7) = 'COEFFICIENTE DI SCAMBIO'
C
C---unita` di misura residuo FSTX (max. 10 car)
      UNITEQ ( 7) = 'W/M**2/K'
C
C---costante di normalizzazione residuo FSTX in stazionario
      COSNOR ( 7) =W0*H0/100/100/T0 

C
C---topologia jacobiano in stazionario per il residuo FSTX
C---equazione n.7 (algebrica):
C   ---dipendenza da TUFX
      ITOPVA(7,1)=1.
C   ---dipendenza da HUVX
      ITOPVA(7,2)=1.
C   ---dipendenza da PUVX
      ITOPVA(7,3)=1.
C   ---dipendenza da TUVX
      ITOPVA(7,4)=1.
C   ---dipendenza da TMTX
      ITOPVA(7,5)=1.
C   ---dipendenza da POTX
      ITOPVA(7,6)=1.
C   ---dipendenza da FSTX
      ITOPVA(7,7)=1.
C   ---dipendenza da EFAL
      ITOPVA(7,9)=1.
C   ---dipendenza da WIFX
      ITOPVA(7,11)=1.
C   ---dipendenza da TIFX
      ITOPVA(7,12)=1.
C   ---dipendenza da PCO2
      ITOPVA(7,13)=1.
C   ---dipendenza da PH2O
      ITOPVA(7,14)=1.
C   ---dipendenza da FH2O
      ITOPVA(7,15)=1.
C   ---dipendenza da HIVX
      ITOPVA(7,16)=1.
C   ---dipendenza da WIVX
      ITOPVA(7,17)=1.
C   ---dipendenza da PIVX
      ITOPVA(7,18)=1.
C   ---dipendenza da FASX
      ITOPVA(7,20)=1.
C   ---dipendenza da NUMT
      ITOPVA(7,21)=1.
C   ---dipendenza da NUMF
      ITOPVA(7,22)=1.

C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO FSTX
C
C---descrizione equazione FSTX in stazionario (max. 50 car)
      SIGNEQ ( 8) = 'SUPERFICIE DI SCAMBIO'
C
C---unita` di misura residuo FSTX (max. 10 car)
      UNITEQ ( 8) = 'M*M'
C
C---costante di normalizzazione residuo FSTX in stazionario
      COSNOR ( 8) =10000. 

C------dipendenza dalla variabile SUPX
      ITOPVA ( 8, 8) = 1
C------dipendenza dalla variabile NUMT
      ITOPVA ( 8,21) = 1
C   ---dipendenza da NUMT
      ITOPVA(8,21)=1.
C   ---dipendenza da NUMF
      ITOPVA(8,22)=1.

C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO EFAL
C
C---descrizione equazione EFAL in stazionario (max. 50 car)
      SIGNEQ ( 9) ='EFFICACIA ALETTA' 
C
C---unita` di misura residuo EFAL (max. 10 car)
      UNITEQ ( 9) =' ' 
C
C---costante di normalizzazione residuo EFAL in stazionario
      COSNOR ( 9) =1. 
C
C---topologia jacobiano in stazionario per il residuo EFAL

C---equazione n.9 (algebrica):
C   ---dipendenza da TUFX
      ITOPVA(9,1)=1.
C   ---dipendenza da TMTX
      ITOPVA(9,5)=1.
C   ---dipendenza da EFAL
      ITOPVA(9,9)=1.
C   ---dipendenza da QOTX
      ITOPVA(9,6)=1.

C   ---dipendenza da WIFX
      ITOPVA(9,11)=1.
C   ---dipendenza da TIFX
      ITOPVA(9,12)=1.
C   ---dipendenza da PCO2
      ITOPVA(9,13)=1.
C   ---dipendenza da PH2O
      ITOPVA(9,14)=1.
C   ---dipendenza da FH2O
      ITOPVA(9,15)=1.
C   ---dipendenza da FASX
      ITOPVA(9,20)=1.
C   ---dipendenza da NUMT
      ITOPVA(9,21)=1.
C   ---dipendenza da NUMF
      ITOPVA(9,22)=1.
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO EXER
C
C---descrizione equazione EXER in stazionario (max. 50 car)
      SIGNEQ (10) ='RENDIMENTO EXERGETICO' 
C
C---unita` di misura residuo EXER (max. 10 car)
      UNITEQ (10) = ' '
C
C---costante di normalizzazione residuo EXER in stazionario
      COSNOR (10) = 1.

C
C---topologia jacobiano in stazionario per il residuo EXER
C   ---dipendenza da TUFX
      ITOPVA(10,1)=1.
C   ---dipendenza da HUVX
      ITOPVA(10,2)=1.
C   ---dipendenza da PUVX
      ITOPVA(10,3)=1.
C   ---dipendenza da POTX
      ITOPVA(10,6)=1.
C   ---dipendenza da EXER
      ITOPVA(10,10)=1.
                    
C   ---dipendenza da TIFX
      ITOPVA(10,12)=1.
C   ---dipendenza da HIVX
      ITOPVA(10,16)=1.
C   ---dipendenza da PIVX
      ITOPVA(10,18)=1.
C   ---dipendenza da WIVX
      ITOPVA(10,21)=1.
                 
      RETURN
      END
C**************************************************************************
      SUBROUTINE ECRIGTERT(P,H,S,T,RO,TIT,TP,D,CRIG,G,Q,SUP,HTC)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C
C**************** correlazioni: Dittus-Boelter per acqua (X<=X1)
C                               Hadaller per vapore (X>=X4)
C                               Valore costante GCONST per X2=<X<=X3
C                               Raccordo lineare per X1<X<X2 e X3<X<X4
C                               ALPHA stabilisce la temperatura di film
C                       
C                             -X2 vale 0.1 (da0.3)
C                             -GCONST vale 50000 (da 15000)
C                             -tra X3(escluso) ed X4 raccordo lineare
C                                  tra Hadaller calc. in X4 ed Had/2
C                                  posto in X3
C
      PARAMETER (ALPHA=1.)
      DATA X1/0./,X2/0.1/,X3/0.7/,X4/1./  !titoli di confine tra le correl.
C
      IF (TIT.GE.X1.AND.TIT.LE.X4) THEN !sotto la campana di Mollier
         IF(P.GT.1.E+05) THEN
            GCONST=50000.
         ELSE !protez. da condens. celle non riscaldate con W=0
            GCONST=.4995E-05*P*P+50. 
         ENDIF
      ENDIF
      IF (TIT.LT.X2) THEN
         DB=ECRIDB(P,S,T,RO,TIT,TP,D,G,X1,ALPHA)
      ELSE IF (TIT.GT.X3) THEN
         HAD=ECRIHAD(P,S,T,RO,TIT,TP,D,G,X4,ALPHA)
      ENDIF
C        
      IF (TIT.LE.X1) THEN
         HTC=DB
      ELSE IF (TIT.GT.X1.AND.TIT.LE.X2) THEN
         A=(GCONST-DB)/(X2-X1)
         B=DB-A*X1
         HTC=A*TIT+B
      ELSE IF (TIT.GT.X2.AND.TIT.LT.X3) THEN
         HTC=GCONST
      ELSE IF (TIT.GT.X3.AND.TIT.LT.X4) THEN
         HTC=0.5*HAD*(1+ (TIT-X3)/(X4-X3))
      ELSE
         HTC=HAD
      ENDIF
      RETURN
      END
C
C**************************************************************************
      REAL FUNCTION ECRIDB(P,S,T,RO,TIT,TP,D,G,X1,ALPHA)
C
      REAL MU,LAM,MUMIN,LAMMIN
      DATA MUMIN/9.E-06/,LAMMIN/18.E-03/,CPMIN/1000./
C
      NFL=1
      IF (P.LT.221.2E5) THEN !caso sottocritico
         CALL SATUR(P,1,SW,SV,1)
         CALL SATUR(P,3,ROW,ROV,NFL)
         RWV=ROW/ROV
         IF (TIT.LE.X1) THEN
            SS=S
            RR=RO
            TT=TIT
         ELSE 
            SS=SW
            RR=ROW
            TT=0.
         ENDIF
      ELSE      !caso supercritico
         RWV=1.
         SS=S
         RR=RO
         TT=TIT
      ENDIF
C
      TF=ALPHA*T+(1-ALPHA)*TP
      CP=CPEV(P,SS,TT,0.5,NFL)
      MU=ETEV(P,TF,RR,RWV,TT,0.5,NFL)
      LAM=ALEV(P,TF,RR,RWV,TT,0.5,NFL)
C     IF(MU.LT.MUMIN)MU=MUMIN
C     IF(LAM.LT.LAMMIN)LAM=LAMMIN
C     IF(CP.LT.CPMIN)CP=CPMIN
      RE=G*D/MU
      PR=CP*MU/LAM
      ECRIDB=.023*LAM*RE**.8*PR**.4/D
C
      RETURN
      END
C
C**************************************************************************
      REAL FUNCTION ECRIHAD(P,S,T,RO,TIT,TP,D,G,X4,ALPHA)
C
      REAL MU,LAM,MUMIN,LAMMIN
      DATA MUMIN/9.E-06/,LAMMIN/18.E-03/,CPMIN/1000./
C
      NFL=1
      IF (P.LT.221.2E5) THEN !caso sottocritico
         CALL SATUR(P,1,SW,SV,1)
         CALL SATUR(P,3,ROW,ROV,NFL)
         RWV=ROW/ROV
         IF (TIT.GE.X4) THEN
            SS=S
            RR=RO
            TT=TIT
         ELSE
            SS=SV
            RR=ROV
            TT=1.
         ENDIF
      ELSE      !caso supercritico
         RWV=1.
         SS=S
         RR=RO
         TT=TIT
      ENDIF
C
      TF=ALPHA*T+(1-ALPHA)*TP
      CP=CPEV(P,SS,TT,0.5,NFL)
      MU=ETEV(P,TF,RR,RWV,TT,0.5,NFL)
      LAM=ALEV(P,TF,RR,RWV,TT,0.5,NFL)
      IF(MU.LT.MUMIN)MU=MUMIN
      IF(LAM.LT.LAMMIN)LAM=LAMMIN
      IF(CP.LT.CPMIN)CP=CPMIN
      RE=G*D/MU
      PR=CP*MU/LAM
      ECRIHAD=.008348*LAM*RE**.8774*PR**.6112/D
C
      RETURN
      END
