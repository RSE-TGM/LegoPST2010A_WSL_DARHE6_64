C******************************************************************************
C modulo %M%
C tipo %Y%
C release %I%
C data %G%
C reserver %W%
C******************************************************************************
C*                                                                     *
C*                   VERSIONE MODIFICATA DA S.D.I.                     *
C*                          IL 29/5/1992                               *
C*                                                                     *
C***********************************************************************
C
C=====================================================================
C
C   QUESTO FILE CONTIENE SUBROUTINES E FUNCTIONS USATE DAI MODULI
C   DI TERMOIDRAULICA PER TENER CONTO DI RICORRENTI CORRELAZIONI.
C   ELENCO DELLE ROUTINES :
C      
C     GAM01  ======> piu` tante altre 
C     GAM03
C     GAM11
C     DGAMDW
C     DITBOE
C     PARZ11
C     PARZ21
C     EPSF11
C     UC12
C     UCL12
C     UR12
C     RADL12
C
C=====================================================================
      SUBROUTINE GAM01 (P,H,S,T,RO,TIT,TW,D,CRIG,G,Q,SUP,COESCA)        
C***********************************************************************
C*                                                                     *
C*                    SUBROUTINE GAM01                                 *
C*                                                                     *
C***********************************************************************
C                                                                       
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (MAX=18,MAX1=MAX+1)                                     
C                                                                       
      INTEGER KCRIS(0:MAX1) 
      REAL MSFB,MOLT
C                                                                       
C      COMMON /UTEN/   IND1,IND2,IFCO                                    
      COMMON /FLUIDO/ NFL                                               
      COMMON /SAT/    TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                 
      COMMON /CEL01/  NTCEL,IVER,ICEL                                   
C      COMMON/REGIME/KREGIM                                              
C      COMMON/PARPAR/NUL(6),KSTP,ITERT                                   
C      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          
C                                                                       
      DATA KCRIS /0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0/              
C           IF(G.LE.50.) THEN
C           COESCA=500.
C           RETURN
C           END IF
C
C  IND2=1 ===> VENGONO FATTE LE STAMPE OPZIONALI 
C
C      IND2=0
C      IF(.NOT.KREGIM.AND.ITERT.EQ.0
C     &   .AND.KSTP.EQ.1.AND.TEMPO.GE.3.) IND2=1
C                                                                       
C  NFL = PARAMETRO DELLE LISTE DI CHIAMATA ALLE FUNCTIONS E SUBROUTINES 
C  DELLE TAVOLE ACQUA FRANCESI.  NFL = 1 =====> FLUIDO = ACQUA          
C                                                                       
C  ITRAN=0 ===> NON SI E' NELLA REGIONE DI TRANSITION BOILING           
C                                                                       
      NFL=1                                                             
      ITRAN=0                                                           
C                                                                       
C  CALCOLO DI UN FATTORE MOLTIPLICATIVO DEL COEFFICIENTE DI SCAMBIO     
C  TERMICO, BASATO SUL PARAMETRO CRIG (FORNITO DALL'UTENTE TRA I DATI   
C  DEI MODULI EVAF E TUBS)                                              
C                                                                       
      
      IF(CRIG.GE.0..AND.CRIG.LT.10.) THEN
C
C  TUBI LISCI
C
      IF(CRIG.EQ.0.)CRIG=1.
      MOLT=CRIG
      CRIG=1.
      ELSE
C
C  TUBI RIGATI
C
      IF(CRIG.EQ.10.)CRIG=11.
      MOLT=CRIG-10.
      ENDIF
C      
C-------------------------------------
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,*)'CELLA',ICEL,'   VALORI PASSATI ALLA GAM01 - TEMPO',
C     &          TEMPO
C      WRITE(6,*)'P=',P,'S=',S,'H=',H,'TIT=',TIT                         
C      WRITE(6,*)'RO=',RO,'T=',T,'TW=',TW                                
C      WRITE(6,*)'G=',G,'Q=',Q,'SUP=',SUP,'D=',D                         
C      WRITE(6,*)
C       END IF                                                           
C-------------------------------------
C                                                                       
C+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            IF(P.GE.221.2E+05) THEN                                     
C                                                                       
C                  PRESSIONI IPERCRITICHE                               
C                                                                       
C                                                                       
C  CALCOLO TEMPERATURA PSEUDOCRITICA (TPC)                              
C                                                                       
      PB=P*1.E-05                                                       
      TPC=545.584717+0.540203393*PB-0.364382286E-03*PB*PB               
C                                                                       
C  CALCOLO DELLA G DI DETERIORAMENTO                                    
C                                                                       
C  FLU = FLUSSO TERMICO IN W/CM/CM                                      
C                                                                       
      FLU=Q/SUP*1.E-04                                                  
C                                                                       
C  GDET = G AL DI SOTTO DELLA QUALE LO SCAMBIO PUO' ESSERE DETERIORATO  
C                                                                       
      GDET=(32475.6641*EXP(0.01*FLU)-279.721191*FLU-                    
     $     2.47451305*FLU*FLU-32724.1172)*(D/0.038)**0.25               
C                                                                       
C  CALCOLO DEI PARAMETRI DI DETERIORAMENTO DI POLIAKOV E DI PROTOPOPOV  
C                                                                       
C  POL = PARAMETRO DI POLIAKOV                                          
C  PRO = PARAMETRO DI PROTOPOPOV                                        
C                                                                       
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
C       POL=POLIAK (P,S,H,RO,T,TW,D,G,Q,SUP)                              
C       PRO=PROTOP (P,S,RO,T,TW,D,G)                                      
       PRO=0.
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C        IF(IND2.EQ.1) THEN                                              
C      WRITE(6,*)'PARAMETRO DI POLIAKOV   = ',POL                        
C      WRITE(6,*)'PARAMETRO DI PROTOPOPOV = ',PRO                        
C       ELSE IF(IND2.EQ.2) THEN                                          
C      TITS=POL                                                          
C      TWS=PRO                                                           
C      TS=TPC                                                            
C       END IF                                                           
C-------------------------------------
C                                                                       
C  TEST PER STABILIRE SE LO SCAMBIO TERMICO E' DETERIORATO.             
C  IL TEST VIENE FATTO SOLO SE CRIG = 1., CIOE' PER TUBI LISCI.        
C  PER TUBI RIGATI LO SCAMBIO TERMICO SI INTENDE SEMPRE NON DETERIORATO 
C                                                                       
CC       IF ((CRIG.EQ.1.).AND.(POL.GT.100.)) THEN                      
         IF ((CRIG.EQ.1.).AND.(PRO.GT.13500.)) THEN                    
CC       IF ((CRIG.EQ.1.).AND.(G.LT.GDET).AND.                         
CC      &    (T.LT.TPC).AND.(TW.GT.TPC)) THEN                           
CC    DTWPC=TW-TPC                                                      
CC    DTCON=0.67*(TW-T)                                                 
CC       IF ((KCRIS(ICEL).EQ.1).AND.(DTWPC.LT.DTCON)) GOTO 4               
C_______________________________________________________________________
C  REGIME DI SCAMBIO TERMICO DETERIORATO                                
C  CORRELAZIONE DI SWENSON MOLTLIPICATA PER UN COEFFICIENTE CORRETTIVO  
C_______________________________________________________________________
      CCORR=0.60                                                        
      COESCA=CCORR*SWENSO (P,S,H,RO,T,TW,D,G)                           
      KCRIS(ICEL)=1                                                        
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,106) COESCA                                               
C  106 FORMAT(1X,'SCAMBIO TERMICO DETERIORATO',/,1X,                     
C     @'CORRELAZIONE DI SWENSON PER 0.60',/,1X,                          
C     @'COEFFICIENTE DI SCAMBIO',5X,E12.5,//)                            
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='0.60*SWENSON'                                               
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
      RETURN                                                            
         ELSE                                                           
C_______________________________________________________________________
C  REGIME DI SCAMBIO TERMICO NON DETERIORATO                            
C  CORRELAZIONE DI SWENSON                                              
C_______________________________________________________________________
    4 CONTINUE                                                          
      COESCA=SWENSO (P,S,H,RO,T,TW,D,G)                                 
      KCRIS(ICEL)=0                                                        
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,107) COESCA                                               
C  107 FORMAT(1X,'SCAMBIO TERMICO NON DETERIORATO',/,1X,                 
C     @'CORRELAZIONE DI SWENSON',/,1X,                                   
C     @'COEFFICIENTE DI SCAMBIO',5X,E12.5,//)                            
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='SWENSON'                                                    
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
      RETURN                                                            
         END IF                                                         
            END IF                                                      
C++++++++ FINE PRESSIONI IPERCRITICHE ++++++++++++++++++++++++++++++++++
C                                                                       
C                                                                       
C  CALCOLO DI ALCUNE GRANDEZZE TERMODINAMICHE DI INTERESSE              
C                                                                       
      CALL SATUR(P,1,SL,SG,NFL)                                         
      CALL SATUR(P,2,HL,HG,NFL)                                         
      CALL SATUR(P,3,ROL,ROG,NFL)                                       
      CALL SATUR(P,7,TSAT,ZZ,NFL)                                       
C                                                                       
C  HGL = CALORE LATENTE DI VAPORIZZAZIONE                               
C                                                                       
      HGL=HG-HL                                                         
C                                                                       
C  X = TITOLO TERMODINAMICO CORRISPONDENTE ALL'ENTALPIA H               
C                                                                       
      X=(H-HL)/HGL                                                      
C                                                                       
C  ROLG = GRANDEZZA CHE COMPARE NELLE LISTE DI CHIAMATA DI ALCUNE       
C         FUNCTIONS DELLE TAVOLE DELL'ACQUA                             
C                                                                       
      ROLG=ROL/ROG                                                      
C                                                                       
C  DTS = DIFFERENZA TRA TEMPERATURA DI PARETE E TEMP. DI SATURAZIONE    
C                                                                       
      DTS=TW-TSAT                                                       
C                                                                       
C  DTBR= (TW-T) NECESSARIO SECONDO BERGLES-ROHSENOW PER INNESCO EB. NUCL
C                                                                       
      DTBR=1000.                                                        
       IF(Q.GT.0.) THEN                                                 
      DTBR=BERROH(Q,P,SUP)                                              
       END IF                                                           
C                                                                       
C  TEST PER CONVEZIONE FORZATA VERSO IL LIQUIDO SOTTORAFFREDDATO        
C                                                                       
           IF(X.LT.0..AND.DTS.LT.DTBR) THEN                             
C________________________________________________________________       
C  REGIME DI CONVEZIONE FORZATA VERSO IL LIQUIDO SOTTORAFFREDDATO       
C  CORRELAZIONE DI DITTUS-BOELTER                                       
C________________________________________________________________       
C                                                                       
      COESCA=MOLT*DITTUS(G,D,P,T,S,RO)                                       
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,100) COESCA                                               
C  100 FORMAT(1X,'CONVEZIONE FORZATA VERSO IL LIQUIDO SOTTORAFFREDDATO', 
C     @/,1X,'CORRELAZIONE DI DITTUS-BOELTER',/,1X,                       
C     @'COEFFICIENTE DI SCAMBIO',5X,E12.5,//)                            
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='DITTUS-BOELTER'                                             
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
      RETURN                                                            
C                                                                       
C  TEST PER EBOLLIZIONE SOTTORAFFREDDATA                                
C                                                                       
           ELSE IF(X.LT.0..AND.DTS.GE.DTBR) THEN                        
C_________________________________________________________              
C  REGIME DI EBOLLIZIONE SOTTORAFFREDDATA PARZIALE E PIENA              
C  CORRELAZIONE DI CHEN MODIFICATA BUTTERWORTH                          
C_________________________________________________________              
C                                                                       
C  IBUT=1 ===> LA CORRELAZIONE VA IMPIEGATA SECONDO L'INDICAZIONE       
C              DI BUTTERWORTH                                           
C                                                                       
      IBUT=1                                                            
C                                                                       
C  NITER=0 ===> VIENE CALCOLATO IL COEFFICIENTE DI SCAMBIO              
C                                                                       
      NITER=0                                                           
C                                                                       
      XM=0.
      CALL CHEN (P,XM,T,DTS,D,G,IBUT,NITER,HCON,HEBO)                  
C                                                                       
C  CALCOLO DEL COEFFICIENTE DI SCAMBIO                                  
C                                                                       
      COESCA=MOLT*(HCON+HEBO*DTS/(TW-T))                                       
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,101) COESCA                                               
C  101 FORMAT(1X,'EBOLLIZIONE SOTTORAFFREDDATA',/,1X,'CORRELAZIONE DI CHE
C     @N MODIFICATA BUTTERWORTH',/,1X,'COEFFICIENTE DI SCAMBIO',5X,E12.5,
C     @//)                                                               
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='CHEN MODIFICATA BUTTERWORTH'                                
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
      RETURN                                                            
           END IF                                                       
C                                                                       
C  IL TITOLO X E' MAGGIORE DI 0                                         
C                                                                       
      IF(X.GE.1.) GOTO 50                                               
C                                                                       
      JCRIS=1                                                           
      NITER=0                                                           
C                                                                       
C  IL TEST DI CRISI VIENE FATTO SOLO SE CRIG = 1., CIOE' PER TUBI LISCI
C  PER TUBI RIGATI SI INTENDE SEMPRE CHE NON CI SIA CRISI FINO A TITOLO 
C  UGUALE A 1.                                                          
C                                                                       
        IF(CRIG.NE.1.) GOTO 2                                          
C**********************************************                         
C                                                                       
C  CRITERIO PER STABILIRE SE FARE O MENO IL TEST DI CRISI, IN BASE AL   
C  VERSO DELLA PORTATA NEL BLOCCO LEGO E ALLA CELLA IN ESAME.           
C                                                                       
        IF(IVER.EQ.-2) GOTO 1                                           
        IF((IVER.EQ.1).AND.                                             
     $    ((ICEL.EQ.NTCEL).OR.(KCRIS(ICEL+1).EQ.1))) THEN               
      GOTO 1                                                            
        ELSE IF((IVER.EQ.-1).AND.                                       
     $    ((ICEL.EQ.1).OR.(KCRIS(ICEL-1).EQ.1))) THEN                   
      GOTO 1                                                            
        END IF                                                          
      GOTO 2                                                            
   1  CONTINUE
C**********************************************                         
C                                                                       
C  CONFRONTO TRA TW E TW CRITICA (TWC)                                  
C  PER DETERMINARE TWC SI RICORRE AD UN CALCOLO ITERATIVO BASATO SUL    
C  METODO DI NEWTON.                                                    
C  PER IL CALCOLO DEL VALORE DI PRECRISI DI TW SI FA USO DELLA          
C  CORRELAZIONE DI CHEN, CHE DIPENDE ANCHE DA TW                        
C                                                                       
C                                                                       
C  ICORR = INDICE PER LA SCELTA DELLA CORRELAZIONE DI CRISI DA IMPIEGARE
C          PER G > 200 KG/S/M**2           
C  ICORR = 1 ===> CORRELAZIONE DI BIASI                                 
C  ICORR = 2 ===> CORRELAZIONE DI BOWRING                               
C  ICORR = 3 ===> CORRELAZIONE DI KON'KOV                               
C                                                                       
      ICORR=2
      FLCRI=FICRIT(G,D,P,X,ICORR)                                       
      FLCRI=ABS(FLCRI)                                                  
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C        IF(IND2.EQ.1) THEN                                              
C      WRITE(6,*) 'FLUSSO CRITICO=',FLCRI                                
C        END IF                                                          
C-------------------------------------
C                                                                       
C  CALCOLO DEL VALORE DI PRIMO TENTATIVO DELLA TEMPERATURA DI PARETE    
C  CRITICA CON LA CORRELAZIONE DI THOM                                  
C                                                                       
      TWC=TSAT+.0225*FLCRI**.5*EXP(-P/86.87E+05)                        
C                                                                       
C  NITER= NUMERO DI ITERAZIONI                                          
C                                                                       
      NITER=0                                                           
C                                                                       
C  IBUT=0 ===> VIENE CALCOLATA LA NORMALE CORRELAZIONE DI CHEN          
C                                                                       
      IBUT=0                                                            
C                                                                       
   10 CONTINUE                                                          
C                                                                       
C  CALCOLO NUMERICO DELLA DERIVATA DEL FLUSSO DI CHEN RISPETTO A TW     
C  DFLU = DERIVATA                                                      
C                                                                       
      DTSC=TWC-TSAT                                                     
      CALL CHEN (P,X,T,DTSC,D,G,IBUT,NITER,HCON,HEBO)                 
      FLCHE=(HCON+HEBO)*(TWC-T)                                         
      TI=TWC+.01                                                        
      DTSI=DTSC+.01                                                     
      CALL CHEN (P,X,T,DTSI,D,G,IBUT,NITER,HCON,HEBO)                 
      FLI=(HCON+HEBO)*(TI-T)                                            
      DFLU=(FLI-FLCHE)/.01                                              
C                                                                       
C  CALCOLO DEL NUOVO VALORE DELLA TWC                                   
C                                                                       
C     TWC=TWC-(TWC-T)*(FLCHE-FLCRI)/FLCRI/3.                            
      TWC=TWC-(FLCHE-FLCRI)/DFLU                                        
      NITER=NITER+1                                                     
C     IF(TWC.GT.647.3) TWC=647.25                                       
      IF(TWC.LE.TSAT) TWC=TSAT+.05                                      
C                                                                       
C  SCO = VALORE ASSOLUTO DELLO SCOSTAMENTO RISPETTO AL FLUSSO CRITICO   
C                                                                       
      SCO=ABS(FLCHE-FLCRI)/FLCHE                                        
      IF(SCO.LT..01) GOTO 20                                            
      IF(NITER.LE.100) GOTO 10                                          
      WRITE(6,*) 'SUPERATO IL NUMERO MASSIMO DI ITERAZIONI NEL CALCOLO D
     $I TWC'                                                            
      WRITE(6,*) 'TWC=',TWC,'   SCOSTAMENTO=',SCO                       
   20 CONTINUE                                                          
C                                                                       
C  FINE ITERAZIONE                                                      
C                                                                       
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C        IF(IND2.EQ.1) THEN                                              
C      WRITE(6,*)'TW=',TW,'      TW CRITICA=',TWC,'   NITER=',NITER      
C        END IF                                                          
C-------------------------------------
C                                                                       
C  TEST DI CRISI                                                        
C                                                                       
           IF(TW.GE.TWC) JCRIS=2                                        
CCCCCCCCCCCCC END IF                                                         
C                                                                       
C  SE JCRIS=1 NON SI E' IN CRISI                                        
C                                                                       
    2 CONTINUE                                                          
           IF(JCRIS.EQ.1) THEN                                          
C______________________________________________________________________ 
C  REGIME DI EBOLLIZIONE SATURA E CONVEZIONE FORZATA VERSO IL FILM LIQ. 
C  CORRELAZIONE DI CHEN                                                 
C______________________________________________________________________ 
C                                                                       
C  IBUT=0 ===> VIENE CALCOLATA LA NORMALE CORRELAZIONE DI CHEN          
C                                                                       
      IBUT=0                                                            
C                                                                       
      CALL CHEN (P,X,T,DTS,D,G,IBUT,NITER,HCON,HEBO)                  
      COESCA=MOLT*(HCON+HEBO)
C                                                                       
      KCRIS(ICEL)=0                                                     
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,102) COESCA                                               
C  102 FORMAT(1X,'EBOLLIZIONE SATURA',/,1X,'CORRELAZIONE DI CHEN',/,1X,  
C     @'COEFFICIENTE DI SCAMBIO',5X,E12.5,//)                            
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='CHEN'                                                       
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
      RETURN                                                            
           END IF                                                       
C*****************************************                              
C  CONFRONTO FRA TW E LA TEMPERATURA DI                                 
C  MINIMUM STABLE FILM BOILING (TMSFB)                                  
C*****************************************                              
C                                                                       
C  CALCOLO DI TMSFB                                                     
C                                                                       
      TMSFB=MSFB(P,T)                                                   
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C        IF(IND2.EQ.1) THEN                                              
C      WRITE(6,*)'TMSFB=',TMSFB                                          
C        END IF                                                          
C-------------------------------------
C                                                                       
C  CONFRONTO FRA TW E TMSFB                                             
C                                                                       
                   IF(TW.GE.TMSFB) GO TO 40
C-----------------------------------------------------------------------
C  REGIONE DI TRANSITION BOILING                                        
C  CRITERIO DI BJORNARD E GRIFFITH                                      
C-----------------------------------------------------------------------
C                                                                       
C  ITRAN=1 ===> DOPO AVER CALCOLATO COESCA CON LA CORRELAZIONE DI       
C               GROENEVELD-DELORME (O DI HADALLER) RITORNA A 30         
C                                                                       
      ITRAN=1                                                           
      TW0=TW                                                            
      TW=TMSFB                                                          
      GOTO 40                                                           
   30 CONTINUE                                                          
C                                                                       
C  FMSFB = FLUSSO CORRISPONDENTE A TMSFB                                
C                                                                       
      FMSFB=COESCA*(TMSFB-T)/MOLT                                            
C>>   WRITE(6,*)'FLCRI=',FLCRI,'   FMSFB=',FMSFB                        
      TW=TW0                                                            
C                                                                       
C  DELTA = 'PESO' DA APPLICARE NEL CRITERIO DI BJORNARD E GRIFFITH      
C                                                                       
      DELTA=(TW-TMSFB)/(TWC-TMSFB)                                      
C>>   WRITE(6,*)'DELTA=',DELTA                                          
      IF(FMSFB.LT.FLCRI) DELTA=DELTA*DELTA                              
C>>   WRITE(6,*)'DELTA**2=',DELTA                                       
C                                                                       
C  CRITERIO DI BJORNARD E GRIFFITH                                      
C  FLTR = FLUSSO NELLA REGIONE DI TRANSITION BOILING                    
C                                                                       
      FLTR=DELTA*FLCRI+(1.-DELTA)*FMSFB                                 
C     EN1=LOG((TMSFB-TSAT)/DTS)/(LOG((TMSFB-TSAT)/(TWC-TSAT)))        
C     FLTR=FMSFB*(FLCRI/FMSFB)**EN1                                     
C>>   WRITE(6,*)'FLTR=',FLTR                                            
      COESCA=MOLT*FLTR/(TW-T)                                                
C                                                                       
      KCRIS(ICEL)=1                                                     
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C        IF(IND2.EQ.1) THEN                                              
C      WRITE(6,103) TMSFB,FMSFB,COESCA                                   
C  103 FORMAT(1X,'TRANSITION BOILING',/,1X,'CRITERIO DI BJORNARD E GRIFFI
C     @TH',/,1X,'TMSFB',5X,E12.5,10X,'FLMSFB',5X,E12.5,/,                
C     @1X,'COEFFICIENTE DI SCAMBIO',5X,E12.5,//)                         
C        ELSE IF(IND2.EQ.2) THEN                                         
C      CORR='BJORNARD E GRIFFITH'                                        
C      HTS=COESCA                                                        
C        END IF                                                          
C-------------------------------------
      RETURN                                                            
C
   40 CONTINUE                                                          
C-----------------------------------------------------------------------
C                                                                       
C  CALCOLO DEL TITOLO EMPIRICO XA DI GROENEVELD-DELORME                 
C                                                                       
C                                                                       
C  CHIAMATA ALLA SUBROUTINE CHE DA' ENTALPIA E TITOLO EFFETTIVI         
C  DELLA MISCELA                                                        
C                                                                       
      CALL GRODEL (G,D,P,X,Q,SUP,HGA,XA)                                
C                                                                       
C  TEST SU XA PER STABILIRE REGIME DI SCAMBIO TERMICO                   
C                                                                       
           IF(XA.GE.1.) GO TO 50
C_______________________________________________________                
C  REGIME DI CONVEZIONE FORZATA VERSO IL BIFASE DISPERSO                
C  CORRELAZIONE DI GROENEVELD-DELORME                                   
C_______________________________________________________                
C                                                                       
C  CALCOLO DELLA TEMPERATURA CORRISPONDENTE ALL'ENTALPIA HGA (TGA)      
C                                                                       
      ENTR=SHEV(P,HGA,NFL)                                              
      TGA=TEV(P,ENTR,NFL)                                               
C                                                                       
C  CALCOLO TEMPERATURA FILM (TF)                                        
C                                                                       
      TF=(TW+TGA)/2.                                                    
C                                                                       
      COESCA=MOLT*HADMOD(G,D,P,TF,XA)                                        
C     COESCA=COESCA*(TW-TGA)/(TW-T)                                     
C                                                                       
C-------------------------------------
        IF(ITRAN.EQ.1) THEN                                             
C      IF(IND2.EQ.1) WRITE(6,*)'H(TMSFB) CON GROENEVELD DELORME'         
        GOTO 30                                                           
        END IF                                                          
C-------------------------------------
C                                                                       
      KCRIS(ICEL)=1                                                     
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,104) X,XA,TW,T,TGA,COESCA                                 
C  104 FORMAT(1X,'CONVEZIONE FORZATA VERSO IL BIFASE DISPERSO',/,1X,     
C     @'CORRELAZIONE DI GROENEVELD-DELORME',/,1X,'TITOLO',22X,E12.5,/,   
C     @1X,'TITOLO EFFETTIVO',12X,E12.5,/,1X,'TEMPERATURA PARETE',10X,    
C     @E12.5,/,1X,'TEMPERATURA',17X,E12.5,/,1X,'TEMPERATURA EFFETTIVA',  
C     @7X,E12.5,/,1X,'COEFFICIENTE DI SCAMBIO',5X,E12.5,//)              
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='GROENEVELD-DELORME'                                         
C      TITS=TIT                                                          
C      XAS=XA                                                            
C      XS=X                                                              
C      TWS=TW                                                            
C      TS=T                                                              
C      TGAS=TGA                                                          
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
      RETURN                                                            
C
   50 CONTINUE                                                          
C_______________________________________________________                
C  REGIME DI CONVEZIONE FORZATA VERSO IL MONOFASE VAPORE                
C  CORRELAZIONE DI HADALLER                                             
C_______________________________________________________                
C                                                                       
C  CALCOLO TEMPERATURA FILM                                             
C                                                                       
      TF=(TW+T)/2.                                                      
C                                                                       
      XAS=XA                                                            
      XA=1.                                                             
C                                                                       
      COESCA=MOLT*HADMOD(G,D,P,TF,XA)                                        
C                                                                       
C-------------------------------------
        IF(ITRAN.EQ.1) THEN                                             
C      IF(IND2.EQ.1) WRITE(6,*)'H(TMSFB) CON HADALLER'                   
      GOTO 30                                                           
        END IF                                                          
C-------------------------------------
C                                                                       
      KCRIS(ICEL)=1                                                     
C-------------------------------------
C                                                                       
C  TEST PER STAMPA OPZIONALE                                            
C                                                                       
C       IF(IND2.EQ.1) THEN                                               
C      WRITE(6,105) COESCA                                               
C  105 FORMAT(1X,'CONVEZIONE FORZATA VERSO IL MONOFASE VAPORE',/,1X,     
C     @'CORRELAZIONE DI HADALLER',/,1X,'COEFFICIENTE DI SCAMBIO',        
C     @5X,E12.5,//)                                                      
C       ELSE IF(IND2.EQ.2) THEN                                          
C      CORR='HADALLER'                                                   
C      TITS=TIT                                                          
C      XS=X                                                              
C      TWS=TW                                                            
C      TS=T                                                              
C      TGAS=TGA                                                          
C      HTS=COESCA                                                        
C       END IF                                                           
C-------------------------------------
C
      RETURN                                                            
      END                                                               
                                                           
C*************************** BERROH ************************************
      REAL FUNCTION BERROH (Q,P,SUP)                                    !SNGL
C      DOUBLE PRECISION FUNCTION BERROH (Q,P,SUP)                        !DBLE
C                                                                       
C  FI = FLUSSO TERMICO ALLA PARETE                                      
C                                                                       
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      FI=Q/SUP                                                          
      PB=P*1.E-05                                                       
C                                                                       
C  SURRISCALDAMENTO NECESSARIO PER L'INNESCO DELL'EBOLLIZIONE NUCLEATA  
C                                                                       
      BERROH=0.556*(FI/(1082.*(PB**1.156)))**(.463*PB**.0234)           
      RETURN                                                            
      END                                                               
C*************************** DITTUS ************************************
      REAL FUNCTION DITTUS (G,D,P,T,S,RO)                               !SNGL
C      DOUBLE PRECISION FUNCTION DITTUS (G,D,P,T,S,RO)                   !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MU,K                                                         !SNGL
C      DOUBLE PRECISION MU,K                                             !DBLE
C      COMMON /UTEN/   IND1,IND2,IFCO                                    
      COMMON /FLUIDO/ NFL                                               
      COMMON /SAT/ TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG
C                                                                       
C  LETTURA DA TAVOLE DI PROPRIETA' DI INTERESSE                         
C                                                                       
      CP=CPEV(P,S,0.,0.5,NFL)                                            
      MU=ETEV(P,T,RO,ROLG,0.,0.5,NFL)                                    
      K=ALEV(P,T,RO,ROLG,0.,0.5,NFL)                                     
C                                                                       
C  NUMERO DI REYNOLDS                                                   
C                                                                       
      RE=G*D/MU                                                         
C      IF(IND2.EQ.1) WRITE(6,*) 'RE DIT=',RE 
C     IF(RE.LT.10000.) RE=10000.
C      IF(RE.LT.10000.) THEN
C      DITTUS=5000.
C      RETURN
C      END IF
C                                                                       
C  NUMERO DI PRANDTL                                                    
C                                                                       
      PR=CP*MU/K                                                        
C                                                                       
C  CALCOLO DEL COEFFICIENTE DI SCAMBIO                                  
C                                                                       
      DITTUS=0.023*(K/D)*RE**.8*PR**.4                                  
      RETURN                                                            
      END                                                               
C*************************** CHEN **************************************
      SUBROUTINE CHEN (P,X,T,DTS,D,G,IBUT,NITER,HCON,HEBO)            
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MUL,MUG,KL                                                   !SNGL
C      DOUBLE PRECISION MUL,MUG,KL                                       !DBLE
      COMMON /FLUIDO/ NFL                                               
      COMMON /SAT/    TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                 
C                                                                       
C  LE PROPRIETA' TERMODINAMICHE DELL'ACQUA VENGONO CALCOLATE SOLO       
C  PER NITER=0                                                          
C                                                                       
        IF(NITER.NE.0) GOTO 2
C                                                                       
C  CALCOLO DELLA TENSIONE SUPERFICIALE (SIGMA)                          
C                                                                       
      TR=(647.15-T)/647.15                                              
      SIGMA=235.8E-03*TR**1.256*(1.-.625*TR)                            
C                                                                       
C  LETTURA DA TAVOLE DI PROPRIETA' DI INTERESSE                         
C                                                                       
      CPL=CPEV(P,SL,0.,1.,NFL)                                          
      MUL=ETEV(P,TSAT,ROL,ROLG,0.,1.,NFL)                               
      MUG=ETEV(P,TSAT,ROG,ROLG,1.,0.,NFL)                               
      KL=ALEV(P,TSAT,ROL,ROLG,0.,1.,NFL)                                
C                                                                       
C  CALCOLO PARAMETRO DI LOCKHART-MARTINELLI (XTT), SOLO PER IBUT=0.     
C  SE IBUT=1 SI PONE XTT=1000. IN MODO CHE LA FUNCTION EFFE DIA EFFE=1. 
C                                                                       
      XTT=1000.                                                         
       IF(IBUT.EQ.0) THEN                                               
      XTT=((1.-X)/X)**.9*(ROG/ROL)**.5*(MUL/MUG)**.1                
       END IF                                                           
C                                                                       
C  CALCOLO COEFFICIENTI CORRETTIVI FC E SC DELLA CORRELAZIONE           
C                                                                       
      FC=EFFE(XTT)                                                      
      SC=ESSE(G,D,MUL,X,FC)                                           
C                                                                       
C  CALCOLO DEI DUE TERMINI DEL COEFFICIENTE DI SCAMBIO (HCON,HEBO)      
C                                                                       
      HC=CHCON(G,D,CPL,MUL,KL,X)                                      
C
    2 IF(ABS(DTS).GT..1) GO TO 1
C_______se il DTS e` < 0.1 ===> solo il termine convettivo
      HCON=HC*FC
      HEBO=0.  
      RETURN
    1 CONTINUE
C**** Introduzione DTSABS (POLLACHINI 12/02/1990)
      DTSABS=ABS(DTS)
      HE=CHEBO(CPL,MUL,KL,ROL,ROG,SIGMA,HGL,DTSABS)                        
C                                                                       
C  CALCOLO DIFFERENZA PRESSIONI DI SATURAZIONE CORRISPONDENTI A TW      
C  E A TSAT (DPTS) CON L'EQUAZIONE DI CLAUSIUS-CLAPEYRON                
C                                                                       
      DPTS=DTSABS*HGL/(TSAT*(1./ROG-1./ROL))                               
C                                                                       
      HCON=HC*FC                                                        
      HEBO=HE*DPTS**.75*SC                                              
      RETURN                                                            
      END                                                               
C*************************** EFFE **************************************
      REAL FUNCTION EFFE (XTT)                                          !SNGL
C      DOUBLE PRECISION FUNCTION EFFE (XTT)                              !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      XTTI=1./XTT                                                       
C                                                                       
C  CALCOLO DEL COEFFICIENTE CORRETTIVO FC DELLA CORRELAZIONE DI CHEN    
C                                                                       
        IF(XTTI.LE..1) THEN                                             
      EFFE=1.                                                           
        ELSE                                                            
      EFFE=2.35*(XTTI+.213)**.736                                       
        END IF                                                          
      RETURN                                                            
      END                                                               
C*************************** ESSE **************************************
      REAL FUNCTION ESSE (G,D,MUL,X,FC)                                 !SNGL
C      DOUBLE PRECISION FUNCTION ESSE (G,D,MUL,X,FC)                     !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MUL                                                          !SNGL
C      DOUBLE PRECISION MUL                                              !DBLE
C                                                                       
C  NUMERO DI REYNOLDS PER LA SOLA PORTATA DI LIQUIDO                    
C                                                                       
      REL=G*(1.-X)*D/MUL                                              
      IF(REL.LT.10000.) REL=10000.
C                                                                       
C  NUMERO DI REYNOLDS BIFASE                                            
C                                                                       
      RETP=REL*FC**1.25                                                 
C  NELLE FORMULE RETP E' ESPRESSO IN UNITA' DI 1.E4                     
      RETP=RETP*1.E-04                                                  
C                                                                       
C  CALCOLO DEL COEFFICIENTE CORRETTIVO SC DELLA CORRELAZIONE DI CHEN    
C                                                                       
        IF(RETP.LT.32.5) THEN                                           
      ESSE=1./(1.+.12*RETP**1.14)                                       
        ELSE IF(RETP.GE.32.5.AND.RETP.LT.70.) THEN                      
      ESSE=1./(1.+.42*RETP**.78)                                        
        ELSE                                                            
      ESSE=.1                                                           
        END IF                                                          
      RETURN                                                            
      END                                                               
C*************************** CHCON *************************************
      REAL FUNCTION CHCON (G,D,CPL,MUL,KL,X)                            !SNGL
C      DOUBLE PRECISION FUNCTION CHCON (G,D,CPL,MUL,KL,X)                !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      COMMON /UTEN/   IND1,IND2,IFCO                                    
      REAL MUL, KL                                                      !SNGL
C      DOUBLE PRECISION MUL, KL                                          !DBLE
C>>   WRITE(6,*)'G = ',G,' D = ',D                                      
C>>   WRITE(6,*)'CPL=',CPL,' MUL=',MUL,' KL=',KL                        
      CPL=ABS(CPL) 
C                                                                       
C  NUMERO DI REYNOLDS PER LA SOLA PORTATA DI LIQUIDO                    
C                                                                       
      REL=G*(1.-X)*D/MUL                                              
C      IF(IND2.EQ.1) WRITE(6,*) 'RE CHCON=',REL 
      IF(REL.LT.10000.) REL=10000.
C      IF(REL.LT.10000.) THEN
C      CHCON=5000.
C      RETURN
C      END IF
C                                                                       
C  NUMERO DI PRANDTL                                                    
C                                                                       
      PR=CPL*MUL/KL                                                     
C>>   WRITE(6,*)'X = ',X,'REL = ',REL,'PR = ',PR                    
C                                                                       
C  CALCOLO TERMINE CONVETTIVO DELLA CORRELAZIONE DI CHEN                
C                                                                       
      CHCON=.023*(KL/D)*REL**.8*PR**.4                                  
      RETURN                                                            
      END                                                               
C*************************** CHEBO *************************************
      REAL FUNCTION CHEBO (CPL,MUL,KL,ROL,ROG,SIGMA,HGL,DTS)            !SNGL
C      DOUBLE PRECISION FUNCTION CHEBO (CPL,MUL,KL,ROL,ROG               !DBLE
C     $,SIGMA,HGL,DTS)                                                   !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MUL, KL                                                      !SNGL
C      DOUBLE PRECISION MUL, KL                                          !DBLE
      CPL=ABS(CPL)                                                             
C                 
C  CALCOLO TERMINE DI EBOLLIZIONE NUCLEATA DELLA CORRELAZIONE DI CHEN   
C                                                                       
      ENUM=KL**.79*CPL**.45*ROL**.49                                    
      EDEN=SIGMA**.5*MUL**.29*HGL**.24*ROG**.24                         
      CHEBO=.00122*(ENUM/EDEN)*DTS**.24                                 
      RETURN                                                            
      END                                                               
C*************************** MSFB **************************************
      REAL FUNCTION MSFB (P,T)                                          !SNGL
C      DOUBLE PRECISION FUNCTION MSFB (P,T)                              !DBLE
C                                                                       
C  CALCOLA LA TEMPERATURA DI MINIMUM STABLE FILM BOILING                
C                                                                       
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL KL,KW                                                        !SNGL
C      DOUBLE PRECISION KL,KW                                            !DBLE
      COMMON /FLUIDO/ NFL                                               
      COMMON /SAT/    TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                 
C
C  I VALORI DI KW,CW,ROW SONO QUELLI DELLA PARETE
C                                                                       
      KW=18.4                                                           
      CW=539.                                                           
      ROW=8220.                                                         
C                                                                       
      PB=P*1.E-05                                                       
C                                                                       
C  LETTURA DA TAVOLE DI PROPRIETA' DI INTERESSE                         
C                                                                       
      CPL=CPEV(P,SL,0.,1.,NFL)                                          
      KL=ALEV(P,TSAT,ROL,ROLG,0.,1.,NFL)                                
C                                                                       
C  TNO = TEMPERATURA DI NUCLEAZIONE OMOGENEA                            
C                                                                       
        IF(PB.LT.1.032) THEN                                            
      TNO=581.45                                                        
        ELSE IF(PB.GE.1.032.AND.PB.LT.68.95) THEN                       
      TNO=581.45+5.932*SQRT(PB-1.032)                                   
        ELSE                                                            
      TNO=630.34+1.366*SQRT(PB-68.95)                                   
        END IF                                                          
C                                                                       
        IF(PB.LT.4.826) THEN                                            
      C=127.3-26.37*PB                                                  
        ELSE                                                            
      C=0.                                                              
        END IF                                                          
C                                                                       
C  CALCOLO MSFB                                                         
C                                                                       
C>>   WRITE(6,*)'TNO=',TNO,'   C=',C                                    
      MSFB=TNO+(TNO-T)*SQRT(ROL*KL*CPL/ROW/KW/CW)-C                    
      RETURN                                                            
      END                                                               
C*************************** GRODEL ************************************
      SUBROUTINE GRODEL (G,D,P,X,POT,SUP,HGA,XA)                        
C      COMMON /UTEN/   IND1,IND2,IFCO                                    
C                                                                       
C  CALCOLA ENTALPIA E TITOLO "EFFETTIVI" DELLA MISCELA DOPO LA CRISI    
C  CON LA CORRELAZIONE DI GROENEVELD-DELORME                            
C                                                                       
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MUG,KG                                                       !SNGL
C      DOUBLE PRECISION MUG,KG                                           !DBLE
      COMMON /FLUIDO/ NFL                                               
      COMMON /SAT/    TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                 
C                                                                       
C  LETTURA DA TAVOLE DI PROPRIETA' DI INTERESSE                         
C                                                                       
      YE=YEV(P,SG,NFL)
      CPG=CPEV(P,SG,YE,0.5,NFL)                                          
      MUG=ETEV(P,TSAT,ROG,ROLG,YE,0.5,NFL)                               
      KG=ALEV(P,TSAT,ROG,ROLG,YE,0.5,NFL)                                
C                                                                       
C  NUMERO DI REYNOLDS                                                   
C                                                                       
      RE=G*D/MUG                                                        
C      IF(IND2.EQ.1) WRITE(6,*) 'RE GRO=',RE 
      IF(RE.LT.10000.) RE=10000.
C                                                                       
C  NUMERO DI PRANDTL                                                    
C                                                                       
      PR=CPG*MUG/KG                                                     
C                                                                       
C  CALCOLO FLUSSO TERMICO MEDIO ALLA PARETE                             
C                                                                       
      FI=ABS(POT/SUP)                                                        
C                                                                       
C  TEST SUL TITOLO: SE X<1. SI PONE X1=X, ALTRIMENTI X1=1.              
C                                                                       
      X1=X                                                              
        IF(X.GE.1.) THEN                                                
      X1=1.                                                             
        END IF                                                          
C                                                                       
C  CALCOLI DI GRUPPI DI VARIABILI PRESENTI NELLA CORRELAZIONE           
C                                                                       
      REM=RE*(X1+(1.-X1)*ROG/ROL)                                       
      A=FI*D*CPG/(HGL*KG)                                               
      B=1.3072-1.0833*X+.8455*X*X                                       
C                                                                       
      PSI=0.13864*PR**.2031*REM**.20006*A**(-.09232)*B                  
C                                                                       
C  TEST SU PSI                                                          
C                                                                       
        IF(PSI.LE.0.) THEN                                              
      PSI=0.                                                            
        ELSE IF(PSI.GE.1.56) THEN                                       
      PSI=1.56                                                          
        END IF                                                          
C                                                                       
C  CALCOLO ENTALPIA EFFETTIVA DEL GAS (HGA)                             
C                                                                       
      HGA=HG+HGL*EXP(-TAN(PSI))                                         
C                                                                       
C  TITOLO EFFETTIVO DELLA MISCELA                                       
C                                                                       
      XA=HGL/(HGA-HL)*X                                                 
      RETURN                                                            
      END                                                               
C*************************** HADMOD ************************************
      REAL FUNCTION HADMOD (G,D,P,TF,XA)                                !SNGL
C      DOUBLE PRECISION FUNCTION HADMOD (G,D,P,TF,XA)                    !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MUF,KF                                                       !SNGL
C      DOUBLE PRECISION MUF,KF                                           !DBLE
C      COMMON /UTEN/   IND1,IND2,IFCO                                    
      COMMON /FLUIDO/ NFL                                               
      COMMON /SAT/    TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                 
C                                                                       
C  LETTURA DA TAVOLE DI PROPRIETA' DI INTERESSE                         
C                                                                       
      SF=ENTROP(P,TF,TSAT)                                              
      YF=YEV(P,SF,NFL)
      ROF=ROEV(P,SF,NFL)                                                
      CPF=CPEV(P,SF,YF,0.5,NFL)                                          
      MUF=ETEV(P,TF,ROF,ROLG,YF,0.5,NFL)                                 
      KF=ALEV(P,TF,ROF,ROLG,YF,0.5,NFL)                                  
C                                                                       
C  NUMERO DI REYNOLDS                                                   
C                                                                       
      RE=G*D/MUF                                                        
C      IF(IND2.EQ.1) WRITE(6,*) 'RE HAD=',RE 
      IF(RE.LT.10000.) RE=10000.
C      IF(RE.LT.10000.) THEN
C      HADMOD=1000.
C      RETURN
C      END IF
C                                                                       
C  NUMERO DI PRANDTL                                                    
C                                                                       
      PR=CPF*MUF/KF                                                    
 
C                                                                       
C  CALCOLO DEL COEFFICIENTE DI SCAMBIO                                  
C                                                                       
      HADMOD=0.008348*(KF/D)*(RE*(XA+ROG/ROL*(1.-XA)))**.8774*PR**.6112 
      RETURN                                                            
      END                                                               
C*************************** FICRIT ************************************
      REAL FUNCTION FICRIT (G,D,P,X,ICORR)                              !SNGL
C      DOUBLE PRECISION FUNCTION FICRIT (G,D,P,X,ICORR)                  !DBLE
C                                                                       
C  CALCOLA IL FLUSSO CRITICO IN FUNZIONE DI VARIABILI LOCALI            
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        IF(G.LE.100.) THEN
C                                                                       
C  SE G <=100.      ===> CORRELAZIONE DI ZUBER
C
      FICRIT=ZUBER(X)
        ELSE IF(G.LT.200.) THEN
C
C  SE 100 < G < 200 ===> INTERPOLAZIONE LINEARE TRA I FLUSSI CRITICI 
C                        CALCOLATI CON LA CORR. DI ZUBER E CON LA 
C                        CORR. PER G ELEVATE
C                                                                       
      G0=200.
      FI100=ZUBER(X)
      FI200=FCR(G0,D,P,X,ICORR)                                   
      FICRIT=FI100+(FI200-FI100)/100.*(G-100.)
        ELSE
C
C  SE G >= 200     ===> CORRELAZIONE PER G ELEVATE 
C
      FICRIT=FCR(G,D,P,X,ICORR)                                   
        END IF
      RETURN                                                            
      END                                                               
C*************************** FCR **************************************
      REAL FUNCTION FCR (G,D,P,X,ICORR)                                 !SNGL
C      DOUBLE PRECISION FUNCTION FCR (G,D,P,X,ICORR)                     !DBLE
C
C  CALCOLA IL FLUSSO CRITICO NEI CASI CON G > 200 KG/S/M**2
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION PF(28),F1(28),F2(28),F3(28),F4(28)                           
      COMMON /SAT/ TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                    
C
      DATA PF/1.,5.,10.,15.,20.,25.,30.,35.,40.,45.,50.,60.,68.9,       
     $70.,80.,90.,100.,110.,                                            
     $120.,130.,140.,150.,160.,170.,180.,190.,200.,210./                
      DATA F1/.478,.478,.478,.478,.478,.480,.488,.519,.590,.707,        
     $.848,1.043,1.000,.984,.853,.743,.651,.572,.504,.446,.395,.350,    
     $.311,.277,.247,.220,.197,.174/                                    
      DATA F2/1.782,1.019,.662,.514,.441,.403,.390,.406,.462,.564,      
     $.698,.934,1.000,.995,.948,.903,.859,.816,.775,.736,.698,.662,.628,
     $.595,.564,.534,.506,.474/                                         
      DATA F3/.400,.400,.400,.400,.400,.401,.405,.422,.462,.538,.647    
     $,.890,1.000,1.003,1.033,1.060,1.085,1.108,1.129,1.149,1.168       
     $,1.186,1.203,1.219,1.234,1.249,1.263,1.274/                       
      DATA F4/.0004,.0053,.0166,.0324,.0521,.0753,.1029,.1380,.1885,    
     $.2663,.3812,.7084,1.000,1.030,1.322,1.647,2.005,2.396,2.819,3.274,
     $3.760,4.227,4.825,5.404,6.013,6.651,7.320,7.990/                  
C
C                                                                       
C  IL VALORE DI ICORR, PASSATO DALLA GAM01, STABILISCE LA CORRELAZIONE 
C  DI CRISI TERMICA DA IMPIEGARE NEL CASO DI G ELEVATA
C                                                                       
                   IF(ICORR.EQ.1) THEN                                  
C                                                                       
C  CORRELAZIONE DI BIASI ET AL.                                         
C                                                                       
C  CONVERSIONE DELLE GRANDEZZE NELLE UNITA' DI MISURA IMPIEGATE         
C  NELLA CORRELAZIONE                                                   
C                                                                       
      G1=G/10.                                                          
      D1=D*100.                                                         
      P1=P/.981E+05                                                     
C                                                                       
C  DETERMINAZIONE DELL'ESPONENTE DI D1 NELLA CORRELAZIONE               
C                                                                       
        IF(D1.LT.1.) THEN                                               
      ALFA=.6                                                           
        ELSE                                                            
      ALFA=.4                                                           
        END IF                                                          
C                                                                       
C  CALCOLO DEL PRIMO VALORE DEL FLUSSO CRITICO                          
C                                                                       
      Y=.7249+.099*P1*EXP(-.032*P1)                                     
      FICR1=1.883E3/(D1**ALFA*G1**.167)*(Y/G1**.167-X)                  
C                                                                       
C  CALCOLO DEL SECONDO VALORE DEL FLUSSO CRITICO                        
C                                                                       
      H=-1.159+.149*P1*EXP(-.019*P1)+8.99*P1/(10.+P1**2)                
      FICR2=3.78E3*H/(D1**ALFA*G1**.6)*(1.-X)                           
C                                                                       
C  IL FLUSSO CRITICO E' IL MAGGIORE TRA FICR1 E FICR2                   
C  SE PERO' G<300 KG/M**2/S ===> FLUSSO CRITICO=FICR2                   
C  SI MOLTIPLICA PER 1.E4 PERCHE' LA CORR. DA' FCR IN W/CM**2        
C                                                                       
        IF(G.LT.300.) THEN                                              
      FCR=FICR2*1.E4                                                 
        ELSE                                                            
      FCR=MAX(FICR1,FICR2)*1.E4                                      
        END IF                                                          
C-----------------------------------------------------------------------
                   ELSE IF(ICORR.EQ.2) THEN                             
C                                                                       
C  CORRELAZIONE DI BOWRING (PER TUBI)                                   
C                                                                       
C                                                                       
C  CONVERSIONE PRESSIONE IN BAR                                         
C                                                                       
      P1=P*1.E-05                                                       
C                                                                       
C  IBOWR=1 ===> I COEFFICIENTI DELLA CORR. VENGONO CALCOLATI CON FORMULE
C  IBOWR=2 ===> VIENE FATTA UN'INTERPOLAZIONE                           
C                                                                       
      IBOWR=2                                                           
        IF(IBOWR.EQ.1) THEN                                             
        PR=P1/68.95                                                     
C                                                                       
C  CALCOLO DEI COEFFICIENTI F1,F2,F3,F4 DELLA CORRELAZIONE              
C                                                                       
        IF(PR.LT.1.) THEN                                               
      FF1=(PR**18.942*EXP(20.89*(1.-PR))+.917)/1.917                    
      FF2=FF1*1.309/(PR**1.316*EXP(2.444*(1.-PR))+.309)                 
      FF3=(PR**17.023*EXP(16.658*(1.-PR))+.6671)/1.6671                 
      FF4=FF3*PR**1.649                                                 
        ELSE                                                            
      FF1=PR**(-.268)*EXP(.648*(1.-PR))                                 
      FF2=FF1/(PR**(-.448)*EXP(.245*(1.-PR)))                           
      FF3=PR**.219                                                      
      FF4=FF3*PR**1.649                                                 
        END IF                                                          
C                                                                       
C  CALCOLO DEL FLUSSO TERMICO CRITICO                                   
C                                                                       
      FCR=FBOW(G,D,P1,X,FF1,FF2,FF3,FF4)                             
        ELSE                                                            
      DO 1 I=1,28                                                       
      IF(P1.LT.PF(I)) GOTO 2                                            
    1 CONTINUE                                                          
    2 CONTINUE                                                          
      IP=I-1                                                            
      FL1=FBOW(G,D,PF(IP),X,F1(IP),F2(IP),F3(IP),F4(IP))                
      FL2=FBOW(G,D,PF(I),X,F1(I),F2(I),F3(I),F4(I))                     
      FCR=FL1+(FL2-FL1)/(PF(I)-PF(IP))*(P1-PF(IP))                   
        END IF                                                          
C-----------------------------------------------------------------------
                   ELSE IF(ICORR.EQ.3) THEN                             
C                                                                       
C  CORRELAZIONE DI KON'KOV                                              
C                                                                       
C  CONVERSIONE DELLE GRANDEZZE NELLE UNITA' DI MISURA IMPIEGATE         
C  NELLA CORRELAZIONE                                                   
C                                                                       
      P1=P*1.E-05                                                       
      D1=D*1000.                                                        
C                                                                       
C  CALCOLO DEL FLUSSO TERMICO CRITICO                                   
C                                                                       
        IF(P1.LT.29.4) THEN                                             
      FCR=(25.6*G**(-1./3.)*D1**(-0.07)*EXP(0.01715*P1)/X)**8.       
        ELSE IF((P1.GE.29.4).AND.(P1.LT.98.0)) THEN                     
      FCR=(46.0*G**(-1./3.)*D1**(-0.07)*EXP(-0.00255*P1)/X)**8.      
        ELSE IF(P1.GE.98.0) THEN                                        
      FCR=(76.6*G**(-1./3.)*D1**(-0.07)*EXP(-0.00795*P1)/X)**8.      
        END IF                                                          
                   END IF                                               
      RETURN
      END 
C*************************** ZUBER **************************************
      REAL FUNCTION ZUBER (X)                                           !SNGL
C      DOUBLE PRECISION FUNCTION ZUBER (X)                               !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON /SAT/ TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG                    
C
C  CORRELAZIONE DI ZUBER MODIFICATA 
C
C                                                                       
C  CALCOLO DELLA TENSIONE SUPERFICIALE (SIGMA)                          
C                                                                       
      TR=(647.15-TSAT)/647.15                                              
      SIGMA=235.8E-03*TR**1.256*(1.-.625*TR)                            
C
C  CALCOLO DEL GRADO DI VUOTO (ALFA)
C  VIENE UTILIZZATO IL MODELLO OMOGENEO (RAPPORTO DI SCORRIMENTO = 1)
C
      ALFA=1./(1.+ROG/ROL*(1.-X)/X)
C                                                                       
C  CALCOLO DEL FLUSSO TERMICO CRITICO                                   
C                                                                       
      ZUBER=0.2085*(1.-ALFA)*HGL*ROG**0.5*(SIGMA*(ROL-ROG))**0.25
      RETURN
      END
C*************************** FBOW **************************************
      REAL FUNCTION FBOW (G,D,PRE,X,F1,F2,F3,F4)                        !SNGL
C      DOUBLE PRECISION FUNCTION FBOW (G,D,PRE,X,F1,F2,F3,F4)            !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL N                                                            !SNGL
C      DOUBLE PRECISION N                                                !DBLE
      COMMON /SAT/ TSAT,HL,HG,HGL,ROL,ROG,ROLG,SL,SG
      GA=ABS(G)                                                         
      N=2.-.5*(PRE/68.95)                                               
      A=2.317*F1/(1.+.0143*F2*D**.5*GA)                                 
      C=.077*F3/(1.+.347*F4*((GA/1356.)**N))                            
      FBOW=.25*HGL*(A-X)/C                                              
      RETURN                                                            
      END                                                               
C*************************** SWENSO ************************************
      REAL FUNCTION SWENSO (P,S,H,RO,T,TW,D,G)                          !SNGL
C      DOUBLE PRECISION FUNCTION SWENSO (P,S,H,RO,T,TW,D,G)              !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MUM,KM                                                       !SNGL
C      DOUBLE PRECISION MUM,KM                                           !DBLE
C     DOUBLE PRECISION SW,HW,MUW,KW,CP,REW,PR,SWENSO                    
C      COMMON /UTEN/   IND1,IND2,IFCO                                    
      COMMON /FLUIDO/ NFL                                               
      COMMON /CEL01/  NTCEL,IVER,ICEL                                   
C                                                                       
C  LETTURA DA TAVOLE DI PROPRIETA' DI INTERESSE                         
C                                                                       
C      SW=ENTROP(P,TW,647.3)                                             
C      ROW=ROEV(P,SW,NFL)                                                
C      HW=HEV(P,SW,NFL)                                                  
C      MUW=ETEV(P,TW,ROW,1.,0.,0.,NFL)                                   
C      KW=ALEV(P,TW,ROW,1.,0.,0.,NFL)                                    
C                                                                       
C  CALORE SPECIFICO MEDIO                                               
C                                                                       
C      CP=(HW-H)/(TW-T)                                                  
C---------------------------                                            
      TM=0.7*T+0.3*TW
      SM=ENTROCP(P,TM,647.3,CP)                                             
      YF=YEV(P,SM,NFL)
      ROM=ROEV(P,SM,NFL)                                                
      MUM=ETEV(P,TM,ROM,1.,YF,0.5,NFL)                                   
      KM=ALEV(P,TM,ROM,1.,YF,0.5,NFL)                                    
C---------------------------                                            
C     IF(ICEL.EQ.NTCEL)THEN
C     WRITE(30,*) 'ROW=',ROW,'  MUW=',MUW                     
C     WRITE(30,*) 'KW =',KW,'  CP=',CP
C     WRITE(30,*) 'RO =',RO,'  G=',G
C     WRITE(30,*)'****************'
C     ENDIF
C
      ROM=ABS(ROM)
      MUM=ABS(MUM)
      KM=ABS(KM)
      CP=ABS(CP)
      RO=ABS(RO)
      G=ABS(G)
C
C  NUMERO DI REYNOLDS                                                   
C                                                                       
C     REW=G*D/MUW                                                       
      REM=G*D/MUM                                                       
C      IF(IND2.EQ.1) WRITE(6,*) 'RE SWE=',REM 
      IF(REM.LT.10000.) REM=10000.
C      IF(REM.LT.10000.) THEN
C      SWENSO=1000.
C      RETURN
C      END IF
C                                                                       
C  NUMERO DI PRANDTL                                                    
C                                                                       
C     PR=CP*MUW/KW                                                      
      PR=CP*MUM/KM                                                      
C                                                                       
C  CALCOLO DEL COEFFICIENTE DI SCAMBIO                                  
C                                                                       
C     SWENSO=0.00459*(KW/D)*REW**.923*PR**.613*(ROW/RO)**.231           
      SWENSO=0.00459*(KM/D)*REM**.923*PR**.613*(ROM/RO)**.231           
      RETURN                                                            
      END                                                               
C**********************************************************************
      REAL FUNCTION ENTROCP(P,T0,TSAT,CP)                               !SNGL
C      DOUBLE PRECISION FUNCTION ENTROCP(P,T0,TSAT,CP)                   !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C     CALCOLA :
C              ENTROPIA =ENTROCP
C
C     DATI : PRESSIONE =P
C            TEMPERATURA=T0
C            TEMP. DI SATURAZIONE(P) =TSAT
C
      PARAMETER (UNO=1. , RMILLE=1000.)
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
      DT=ABS(T-T0)
      IF(DT.LT..1)GO TO 20
      DS=CP*(T0-T)/T0
      DELS=MIN(ABS(DS),RMILLE)
      S=S+DELS*SIGN(UNO,DS)
      NTENT=NTENT+1
      IF(NTENT.LT.20) GOTO 10
C
      WRITE(6,99) DELS
      PRINT *,' PRESSIONE =',P,' TEMPERATURA =',T0,' ENTROPIA =',S
  99  FORMAT(1X,'....ERRORE : ENTROCP NON CONVERGE  DELTAS = ',E15.8)
  20  ENTROCP=S
      RETURN
      END
C=====================================================================
      SUBROUTINE GAM03(GAM,DGAM,W,A,D,P,T)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      REAL MU,LAM                                                       !SNGL
C      DOUBLE PRECISION MU,LAM                                           !DBLE
      GAM=0.
      G=ABS(W/A)
      IF(G.LE.1.E-3)GO TO 1
      NFL=1
        IF(P.LT.221.2E5) THEN
        CALL SATUR(P,3,ROW,ROV,NFL)
        CALL SATUR(P,7,TSAT,ZOT,NFL)
        RWV=ROW/ROV
        ELSE
        TSAT=647.3
        RWV=1.
        ENDIF
      S=ENTROP(P,T,TSAT)
      RO=ROEV(P,S,NFL)
      TIT=YEV(P,S,NFL)
      CP=CPEV(P,S,TIT,1.,NFL)
      MU=ETEV(P,T,RO,RWV,TIT,1.,NFL)
      LAM=ALEV(P,T,RO,RWV,TIT,1.,NFL)
      GAM=DITBOE(G,D,CP,MU,LAM)
  1   GAM=GAM+100.
      DGAM=0.
      RETURN
      END
C=====================================================================
      REAL FUNCTION DITBOE(G,D,CP,MU,LAM)                               !SNGL
C      DOUBLE PRECISION FUNCTION DITBOE(G,D,CP,MU,LAM)                   !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C>>>>>>>>    DITTUS BOELTER
C
      REAL MU,LAM                                                       !SNGL
C      DOUBLE PRECISION MU,LAM                                           !DBLE
      RE=G*D/MU
      PR=CP*MU/LAM
      DITBOE=.02*LAM*RE**.8*PR**.4/D
      RETURN
      END
C=====================================================================
      SUBROUTINE UC12(TFILMK,WGAS,UM,SGAS,DEQ,FA,
     $                IFUN,UCLSI,DUCDTF,DUCDTM)
C
C
C     Calcola il coefficiente di scambio termico UCLSI fra i gas di
C     combustione e le pareti dei fasci tubieri degli scambiatori
C     nella zona del retropasso di una caldaia, in condizioni di
C     flusso TRASVERSALE
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (LUM=5,LTFILM=6,LFPP=LUM*LTFILM)
      DIMENSION TABUM(LUM),TABTFILM(LTFILM),TABFPP(LFPP)
C
C----------------------------------------------------------------------
C
C                    SPELTA GEN. 92
C
C     Valori del "Physical properties factor" per gas di combustione
C     in flusso TRASVERSALE tratti da :
C
C     The Babcock & Wilcox Company - STEAM/its generation and use 
C
      DATA TABUM/0.,5.,10.,15.,20./
      DATA TABTFILM/0.,600.,1200.,1800.,2400.,3000./
      DATA TABFPP/0.0825, 0.11,  0.129, 0.142, 0.155, 0.165,
     $            0.085,  0.112, 0.132, 0.148, 0.161, 0.172,  
     $            0.087,  0.114, 0.136, 0.152, 0.167, 0.18,
     $            0.0885, 0.117, 0.139, 0.158, 0.173, 0.1872,
     $            0.09,   0.1183,0.1422,0.163, 0.18,  0.195/
C
      DATA C0,C1,C2/13.4634,172.655E-4,-28.533E-7/
C-------------------------------------------------------------------
C
C   Conversione dei valori delle varie grandezze da sistema S.I.   
C   a sistema Britannico
C
      DEI=3.28084*DEQ
      WGASI=2.20462*3600.*WGAS
      SPGASI=10.7369*SGAS
      TFILM = 9./5.*TFILMK-459.69
C------------------------------------------------------------------
C   Calcolo del flusso di massa
C
      GGAS=ABS(WGASI)/SPGASI
C
C   Calcolo della "conduttanza convettiva di base" per flusso
C   TRASVERSALE
C
      UP=0.287*GGAS**0.61/DEI**0.39
C
C   Calcolo del "physical properties factor"
C
      CALL LINTAB(TABUM,LUM,TABTFILM,LTFILM,TABFPP,TFILM,UM
     $            ,FPP,Z1,Z2)
C
C
C   Calcolo del coefficiente di scambio termico superficiale
C   per gas in flusso TRASVERSALE
C
      UCL=UP*FPP*FA
C
C   Conversione del valore del coefficiente di scambio termico
C   superficiale da sistema Britannico a sistema S.I.
C
      UCLSI=5.67826*UCL
C
      IF (IFUN.EQ.3) THEN
C
C_____ CALCOLO DELLE DERIVATE DEL COEFF. DI SCAMBIO RISPETTO ALLE
C      TEMPERATURE AVENDO DESCRITTO LA FUNZIONE FPP(TFILM) COME
C      PARABOLA (UMIDITA` 10%) COSI` COME SI FACEVA UN TEMPO.
C
        FPP1= C1+C2*TFILMK
        FPP = C0+FPP1*TFILMK
        FD=.287/(DEQ**.39*SGAS**.61)
        UC = FPP*FA*FD*(ABS(WGAS)**0.61)
        DU1= FPP1*UC/FPP
        DUCDTF= DU1*0.25
        DUCDTM = DU1*0.5
      ENDIF
C
      RETURN
      END
      SUBROUTINE UCL12(TFILMK,TBULKK,WGAS,UM,SGAS,DEQ,UCLSI)
C
C     Calcola il coefficiente di scambio termico UCLSI fra i gas di
C     combustione e le pareti dei fasci tubieri che delimitano
C     la zona del retropasso di una caldaia, in condizioni di
C     flusso longitudinale
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (LUM=5,LTFILM=12,LFPP=60)
      DIMENSION TABUM(LUM),TABTFILM(LTFILM),TABFPP(LFPP)
C
C------------------------------------------------------------------------
C                                                                       |
C                    CISE 10 Ott. 1991                                  v
C
C     Valori del "Physical properties factor" per gas di combustione
C     in flusso longitudinale tratti da :
C
C     The Babcock & Wilcox Company - STEAM/its generation and use - fig 7.
C
C
C
      DATA TABUM/0.,5.,10.,15.,20./
      DATA TABTFILM/0.,200.,400.,600.,800.,1000.,1200.,1400.,
     $              1600.,2000.,2400.,2800./
      DATA TABFPP/.152,.166,.18,.19,.198,.205,.212,.217,
     $            .221,.229,.236,.242,
     $            .158,.171,.184,.195,.204,.211,.218,.222,
     $            .228,.236,.244,.251,
     $            .163,.176,.189,.2,.209,.216,.224,.229,
     $            .234,.244,.252,.26,
     $            .17,.183,.194,.205,.214,.222,.229,.237,
     $            .24,.25,.26,.268,
     $            .178,.189,.2,.211,.22,.228,.234,.241,
     $            .247,.256,.266,.275/
C                                                                  ^
C                                                                  |
C-------------------------------------------------------------------
C                                                                  |
C   Conversione dei valori delle varie grandezze da sistema S.I.   v
C   a sistema Britannico
C
C
      DEI=3.28084*DEQ
      WGASI=2.20462*3600.*WGAS
      SPGASI=10.7369*SGAS
      TBULK = 9./5.*TBULKK-459.69
      TFILM = 9./5.*TFILMK-459.69
C                                                                 ^
C                                                                 |
C------------------------------------------------------------------
C
C   Calcolo del flusso di massa
C
      GGAS=ABS(WGASI)/SPGASI
C
C   Calcolo della "conduttanza convettiva di base" per flusso
C   longitudinale
C
      UP=0.023*GGAS**0.6/DEI**0.2
C
C   Calcolo del "physical properties factor"
C
      CALL LINTAB(TABUM,LUM,TABTFILM,LTFILM,TABFPP,TFILM,UM
     $            ,FPP,Z1,Z2)
C
C   Calcolo del "fattore di temperatura"
C
      FT = (TBULK/TFILM)**0.8
C
C   Calcolo del coefficiente di scambio termico superficiale
C   per gas in flusso longitudinale
C
      UCL=UP*FPP*FT
C
C   Conversione del valore del coefficiente di scambio termico
C   superficiale da sistema Britannico a sistema S.I.
C
      UCLSI=5.67826*UCL
C
C************  FINE  SUBROUTINE
C
      RETURN
      END
      SUBROUTINE UR12(DELTAT,TCOLD,PH2O,PCO2,BEAML,IFUN,UR,
     $                DURDTF,DURDTC,DURDPGAS)
C
C     CALCOLA IL COEFFICIENTE DI SCAMBIO PER IRRAGGIAMENTO.
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (LDT=9,LTC=4,LUR=LDT*LTC)
      DIMENSION TABDT(LDT),TABTC(LTC),TABUR(LUR)
C
      PARAMETER (LPL=6,LRAP=4,LK2=LPL*LRAP)
      DIMENSION TABPL(LPL),TABRAP(LRAP),TABK2(LK2)
C
C***************************************************************
C
C                    CISE 05 NOV. 1990
C
C     Valori del coefficiente di irraggiamento base di cavita`
C     tratti da :  D. Annaratone - GENERATORI DI VAPORE - fig. 9.8.6
C                  The Babcock & Wilcox Company - STEAM - fig 26.
C
C     I valori corrispondenti ad una temperatura di parete di 1366.483
C     (2000. F) (tratti da STEAM) sono stati ottenuti supponendo la cur
C     va una retta ed operando una conversione di unita` di misura:
C
C                               7.75      9
C         Ur = 5.67826*[15.5 + ------- * --- DELTAT(K)]
C                               1500.     5
C
C
      DATA TABDT/0.,100.,200.,400.,600.,800.,1000.,1400.,1500./
      DATA TABTC/273.15,523.15,773.15,1366.483333/
C
      DATA TABUR/1.163,1.977,2.56,6.63,12.793,22.446,35.82,59.89,65.94,
     $          6.98,10.23,14.54,25.586,37.216,49.08,61.06,84.9,90.714,
     $         30.59,36.64,42.22,54.08,65.128,76.76,88.39,110.48,116.3,
     $      88.01,93.29,98.57,109.14,119.7,130.26,140.82,161.94,167.23/
C
C
C**********************************************************************
C
C     MODIFICA INTRODOTTA DA SPELTA PER TENER CONTO DELL'INFLUENZA
C     DI COMBUSTIBILI DIVERSI (RAPPORTO PH2O/PCO2) GEN. 92
C
C
      DATA TABPL/0.,0.06,0.12,0.18,0.24,0.30/
      DATA TABRAP/0.3,0.4,0.76,2./
C
      DATA TABK2/0.13, 0.372, 0.517, 0.626, 0.725, 0.815,
     $           0.13, 0.38,  0.545, 0.675, 0.792, 0.882, 
     $           0.13, 0.392, 0.592, 0.75,  0.875, 0.985,
     $           0.13, 0.429, 0.67,  0.862, 1.027, 1.1647/
C
C
C**********************************************************************
C
      DATA A0,A1,A2/0.13,4.477778,-5.3703704/
      PGAS=PH2O+PCO2
      RAP=PH2O/PCO2
      IF((DELTAT.GT.0.).AND.(BEAML.GT.0.)) GOTO 1
      UR=0.
      DURDTF=0.
      DURDTC=0.
      DURDPGAS=0.
      GOTO 4
   1  CALL LINTAB(TABTC,LTC,TABDT,LDT,TABUR,DELTAT,TCOLD,UPRIM,Z1,Z2)
C
      PPERL = PGAS*BEAML
C____ CALCOLO  K2 PER INTERPOLAZIONE SU TABELLA FUNZIONE DEL TIPO
C     DI COMBUSTIBILE ( PH2O/PCO2 )      
      CALL LINTAB(TABRAP,LRAP,TABPL,LPL,TABK2,PPERL,RAP,AK,DYX,DYP)
C
      UR = UPRIM*AK
      IF (IFUN-3)   4,3,3
  3   DURDTF = Z1*0.5*AK
      DURDTC = (Z2-Z1)*AK
      DAKPGAS=(A1+2.*A2*PPERL)*BEAML
      DURDPGAS=UPRIM*DAKPGAS
  4   RETURN
      END
C=====================================================================
      REAL FUNCTION RADL12(PASPD,PASLD,DIAE)                            !SNGL
C      DOUBLE PRECISION FUNCTION RADL12(PASPD,PASLD,DIAE)                !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C     CALCOLA IL CAMMINO OTTICO MEDIO.
C
      PARAMETER (LPD=6,LLD=4,LT=24)
      DIMENSION TABOPT(LT)
      DIMENSION TABPD(LPD),TABLD(LLD)
      DATA TABPD/1.,1.6,2.2,3.,3.6,6./
      DATA  TABLD/1.,2.,3.,4./
      DATA TABOPT/0.4,1.,2.3,5.1,6.8,12.,
     $            1.7,3.1,5.,7.1,8.5,13.1,
     $            5.1,6.3,7.5,9.1,10.2,14.3,
     $            7.7,8.7,9.7,11.,11.9,16./
      IF(PASLD.GT.0.) GOTO 1
      RADL12=0.
      GOTO 2
    1 CALL LINTAB(TABLD,LLD,TABPD,LPD,TABOPT,PASPD,PASLD,OPT,Z1,Z2)
      RADL12 = OPT*DIAE
    2 RETURN
      END
C=====================================================================
      REAL FUNCTION GAM11(QF,S,TF,TM)                                   !SNGL
C      DOUBLE PRECISION FUNCTION GAM11(QF,S,TF,TM)                       !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C  CALCOLO COEFFICIENTE DI SCAMBIO IN LONG FLOW
C  DA 'STEAM' 11-30
C  S=D**2
C
      DATA A,B,C/123.2,105.7E-3,-27.3E-6/
      TFILM=0.5*(TF+TM)
      FPP=A+(B+C*TFILM)*TFILM
      G=ABS(QF)/S
      UPCL=0.023*(G*TF/TFILM)**0.8/S**0.1
      GAM11=UPCL*FPP
      RETURN
      END
C=====================================================================
      SUBROUTINE PARZ11(AST,XN2,XC,XH2,XS,UMAR,CST,PCO2,PH2O,XH2O,
     $                  YO2,PTOT,ISTA,FUMI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DATA RMWAWN /2.E6/
C  CALCOLO PRESSIONI PARZIALI
      IF(CST.LT.RMWAWN) GO TO 10
      AMOIST= UMAR                      ! in questo caso si ricordi che
      AECC  = 1. - UMAR                 ! le X sono quelle dell' aria.
      GO TO 20       
C****ARIA SECCA  KG/KGFUEL
   10 ECCAR=CST/(AST*(1.+UMAR))-1.      !eccesso stechiometrico "umido"
      AECC=AST*ECCAR                    !eccesso in kg secchi/kg fuel
      ADRY=AST+AECC                     !kg immessi di aria secca/kg fuel
C****ARIA UMIDA  KG/KGFUEL
      AMOIST=ADRY*UMAR                  !kg di aria umida /kg fuel
C****COMPOSIZIONE FUMI  KG/KGFUEL
   20 XH2O=XH2+AMOIST                   !
      XN2P=0.7685*AECC+XN2              !
      XXO2=0.2315*AECC                  !
C****FUMI  KG/KGFUEL
      FUMI=XC+XH2O+XS+XN2P+XXO2         !
C****FRAZIONI IN PESO
      XCO2=XC/FUMI                 
      XH2O=XH2O/FUMI
      XSO2=XS/FUMI
      XN2P=XN2P/FUMI
      XXO2=XXO2/FUMI
C****FRAZIONI IN VOLUME
      YCO2=XCO2/44.01
      YH2O=XH2O/18.016
      YSO2=XSO2/64.06
      YN2 =XN2P/28.016
      YO2 =XXO2/32.
      PTOT=YCO2+YH2O+YSO2+YN2+YO2
      YCO2=YCO2/PTOT
      PH2O=YH2O/PTOT
      YSO2=YSO2/PTOT
      YN2 =YN2 /PTOT
      YO2 =YO2 /PTOT
      PCO2=YCO2+YSO2      
      PTOT=PTOT*FUMI
      IF(ISTA.EQ.0) RETURN
      WRITE(6,1000)XCO2,YCO2,XH2O,PH2O,XSO2,YSO2,XN2P,YN2,XXO2,YO2
 1000 FORMAT(//10X,'COMPOSIZIONE FUMI',7X,'IN PESO       IN VOLUME'//
     $   22X,'CO2 ',2(5X,F10.4)//22X,'H2O ',2(5X,F10.4)//
     $   22X,'SO2 ',2(5X,F10.4)//22X,'N2  ',2(5X,F10.4)//
     $   22X,'O2  ',2(5X,F10.4)//)
      RETURN
      END
C=====================================================================
      SUBROUTINE PARZ21(AST,XN2,XC,XH2,XS,FNII,FDII,FO2I,FWAI,CST,
     $                  PCO2,PH2O,XH2O,YO2,PTOT,ISTA,FUMI)
C
C     calcolo pressioni parziali con comburente generico (H2O, CO2, O2)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DATA RMWAWN /2.E6/
C  CALCOLO PRESSIONI PARZIALI
      IF(CST.LT.RMWAWN) GO TO 10
      AMOIST=   FWAI                      ! in questo caso si ricordi che
      AECC  =   1.                        ! le X sono quelle dell' aria.
      GO TO 20
C****ARIA SECCA  KG/KGFUEL
   10 ECGAS= CST/AST - 1.
      AECC = AST*ECGAS                    !eccesso in kg secchi/kg fuel
   20 XH2O = FWAI*AECC + XH2              !
      XN2P = FNII*AECC + XN2              !
      XXO2 = FO2I*AECC
      XXDI = FDII*AECC + XC               !
C****FUMI  KG/KGFUEL
      FUMI=XXDI+XH2O+XS+XN2P+XXO2         !
C****FRAZIONI IN PESO
      XCO2=XXDI/FUMI
      XH2O=XH2O/FUMI
      XSO2=XS/FUMI
      XN2P=XN2P/FUMI
      XXO2=XXO2/FUMI
C****FRAZIONI IN VOLUME
      YCO2=XCO2/44.01
      YH2O=XH2O/18.016
      YSO2=XSO2/64.06
      YN2 =XN2P/28.016
      YO2 =XXO2/32.
      PTOT=YCO2+YH2O+YSO2+YN2+YO2
      YCO2=YCO2/PTOT
      PH2O=YH2O/PTOT
      YSO2=YSO2/PTOT
      YN2 =YN2 /PTOT
      YO2 =YO2 /PTOT
      PCO2=YCO2+YSO2
      PTOT=PTOT*FUMI
      IF(ISTA.EQ.0) RETURN
      WRITE(6,1000)XCO2,YCO2,XH2O,PH2O,XSO2,YSO2,XN2P,YN2,XXO2,YO2
 1000 FORMAT(//10X,'COMPOSIZIONE FUMI',7X,'IN PESO       IN VOLUME'//
     $   22X,'CO2 ',2(5X,F10.4)//22X,'H2O ',2(5X,F10.4)//
     $   22X,'SO2 ',2(5X,F10.4)//22X,'N2  ',2(5X,F10.4)//
     $   22X,'O2  ',2(5X,F10.4)//)
      RETURN
      END
C=====================================================================
      SUBROUTINE EPSF11(TF,PCO2, PH2O,OPTL,EPSF,DEPST,DEPSC,DEPSH)
C  CALCOLO EMISSIVITA' DEI FUMI
C  IN BASE A TABELLE HOTTEL SAROFIM
C
C  DEPST E' LA DERIVATA RISPETTO ALLA TEMPERATURA DEI FUMI
C  DEPSC E' LA DERIVATA RISPETTO ALLA PRESSIONE PARZIALE DELLA CO2
C  DEPSH E' LA DERIVATA RISPETTO ALLA PRESSIONE PARZIALE DELL' H2O
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION TABTF(10),PTLCO2(10),PTLH2O(10),PCLPWL(7)
      DIMENSION TEPSCO2(80),TEPSH2O(80),CSOCOR(77),RACCH(11)
      DIMENSION PWL(3),XPW(4),CWCOR(12)
      DATA TABTF/ 555.500, 833.300,1111.100,1388.900,1666.700,
     $            1944.400,2222.200,2500.000,2777.800,   0./
      DATA LTF,NPTL,NPCLPWL,NRACCH,NXPW,NPWL/9,8,7,11,4,3/
      DATA PTLCO2/.01,.1,.4,.8,1.5,2.,3.,5.,2*0./
      DATA PTLH2O/.05,.2,1.,2.,3.,5.,10.,20.,2*0./
      DATA TEPSCO2/.029,.03,.027,.0205,.0155,.0115,.0082,.006,
     $     .0043,.07,.078,.076,.063,.05,.038,.03,.023,.0175,
     $     .105,.115,.118,.102,.083,.067,.054,.043,.034,
     $     .122,.135,.142,.128,.107,.087,.07,.056,.045,
     $       0.14000, 0.16000, 0.16800, 0.15500, 0.13000,
     $              .11000, 0.08800, 0.07000, 0.05600, 0.15000,
     $              .17000, 0.18000, 0.17000, 0.14500, 0.12000,
     $              .09800, 0.07800, 0.06200, 0.16000, 0.18500,
     $              .20000, 0.18800, 0.16000, 0.13500, 0.11000,
     $              .09000, 0.07300, 0.17800, 0.20300, 0.22500,
     $              .21500, 0.18500, 0.15500, 0.13000, 0.10500,
     $              .08500, 5*0.   , 0.     , 0.     , 0.     /
      DATA TEPSH2O/.06,.045,.0315,.022,.0155,.011,.0075,.005,
     $   .0038,.14,.11,.085,.065,.05,.039,.03,.023,.018,
     $         .28,.25,.21,.175,.145,.118,.097,.08,.066,
     $       0.36000, 0.33000, 0.28000, 0.23500, 0.20000,
     $              .17000, 0.14400, 0.12000, 0.10400, 0.41000,
     $              .38000, 0.32500, 0.28000, 0.23500, 0.20000,
     $              .17000, 0.14300, 0.12200, 0.46000, 0.44000,
     $              .38000, 0.33000, 0.28000, 0.24000, 0.20800,
     $              .17500, 0.15000, 0.54000, 0.52000, 0.45500,
     $              .39500, 0.34000, 0.29500, 0.25500, 0.22000,
     $  .19,.6,.58,.53,.46,.4,.35,.305,.27,.23,8*0./
      DATA PCLPWL/.1,.25,.5,.75,1.,2.,5./
      DATA RACCH/0.,.1,.2,.3,.4,.5,.6,.7,.8,.9,1./
      DATA CSOCOR/0.,.5,1.,1.45,1.8,1.95,2.,2.,1.75,1.2,0.,
     $            0.,1.1,2.,2.8,3.2,3.5,3.75,3.7,3.3,2.7,0.,
     $            0.,2.,3.2,4.05,4.7,5.,5.2,5.2,4.9,4.,0.,
     $            0.,2.6,3.95,4.9,5.5,6.,6.2,6.2,5.8,5.,0.,
     $            0.,3.2,4.6,5.5,6.2,6.6,6.8,6.8,6.5,5.6,0.,
     $            0.,3.9,5.2,6.1,6.75,7.2,7.4,7.4,7.1,6.25,0.,
     $            0.,4.2,5.5,6.4,7.1,7.5,7.8,7.8,7.5,6.75,0./
      DATA PWL/0.,1.,10./
      DATA XPW/0.,0.1,0.3,0.5/
      DATA CWCOR/1.,1.13,1.38,1.58,
     $           1.,1.1,1.27,1.4,
     $           1.,1.06,1.12,1.2/
      PLCO2=PCO2*OPTL
      PLH2O=PH2O*OPTL
      PLTOT=PLCO2+PLH2O
      CSUCH=PCO2/(PCO2+PH2O)
      PW=0.5*PH2O
      CALL LINTAB(PTLCO2,NPTL,TABTF,LTF,TEPSCO2,TF,PLCO2,EPSCO2,DC,VC)
      CALL LINTAB(PTLH2O,NPTL,TABTF,LTF,TEPSH2O,TF,PLH2O,EPSH2O,DH,VH)
      CALL LINTAB(PCLPWL,NPCLPWL,RACCH,NRACCH,CSOCOR,CSUCH,PLTOT,CSO,
     $            DCSUCH,DPL)
      CALL LINTAB(PWL,NPWL,XPW,NXPW,CWCOR,PW,PLH2O,CW,DPW,DPLH2O)
      EPSF=(EPSCO2+EPSH2O*CW)*(1.-CSO/100.)
      DEPST=(DC+CW*DH)*(1.-CSO/100.)
      DEPSC=VC*OPTL*(1.-CSO/100.)-(EPSCO2+CW*EPSH2O)*(DCSUCH*PH2O/
     $      (PCO2+PH2O)**2+DPL*OPTL)/100.
      DEPSH=(CW*VH*OPTL+EPSH2O*(DPLH2O*OPTL+0.5*DPW))*(1.-CSO/100.)-
     $ (EPSCO2+CW*EPSH2O)*(DCSUCH*(-PCO2/(PCO2+PH2O)**2)+DPL*OPTL)/100.
      RETURN
      END
C=====================================================================
      REAL FUNCTION DGAMDW(QF,S,TF,TM)                                  !SNGL
C      DOUBLE PRECISION FUNCTION DGAMDW(QF,S,TF,TM)                      !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C  CALCOLO DELLA DERIVATA DEL COEFFICIENTE DI SCAMBIO IN LONG FLOW
C
C  S=D**2
C
      DATA A,B,C/123.2,105.7E-3,-27.3E-6/
      TFILM=0.5*(TF+TM)
      FPP=A+(B+C*TFILM)*TFILM
      G=ABS(QF)/S
      IF(G.LT.1.E-5) G=1.E-5
      UPCL=0.023*(G*TF/TFILM)**0.8/S**0.1
      DGAMDW=0.8*UPCL/(G*S)*FPP
      RETURN
      END
C=====================================================================
