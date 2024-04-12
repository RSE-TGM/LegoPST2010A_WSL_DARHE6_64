C**********************************************************************
C modulo prsc.f
C tipo 
C release  3.1
C data 19/1/95
C reserver @(#)prsc.f	3.1
C**********************************************************************
C********************************************************************
C
C    ASSORBIMENTO DI POTENZA: 
C    1) aggiunge una potenza imposta ad una data 
C    portata entalpica (Tassi 12/93).
C    2)aggiunta 6/94: entalpia calcolata internamente come stato e una 
C    temperatura media come uscita da calcolo su proprieta' acqua.
C    3)caso 1) con + davanti, con - potenza in uscita
C
C    4) BETA con dinamica (Migliavacca 10/94)
C
C********************************************************************
      SUBROUTINE PRSCI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM
      CHARACTER*1 IWP,IPIU,IMEN,IDEFAULT
      CHARACTER*4 IBLOC*8
      COMMON/PRSC01/IBLOC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
      DATA IPIU/'+'/
      DATA IMEN/'-'/
      DATA IDEFAULT/'P'/
C
      Q0=W0*H0
C---ASSORBIMENTO DI POTENZA
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'VOLUME  ','WNOM    ','GSNOM   ','TIPFL   ',
     $              'CPFLU   ','CPFLUAD ','GAMMULT '
      RETURN
C
C
C---lettura e memorizzazione dati
C
 200  WRITE(IWP,'(A1)')IBL1
      IF(IWP.EQ.IPIU)WP=1.
      IF(IWP.EQ.IMEN)WP=2.
CC Patch anti tassata...
      IF(IWP.EQ.IDEFAULT)WP=2.
      READ(14,501) 
      READ(14,501) VOL,WNOM,GSNOM,TIF,CPF,CPFAD,GAMMULT
C
      IF (TIF.GT.1..OR.TIF.LT.0.)WRITE(6,*) ' TIPO DI FLUIDO NON ASSEGNATO:
     &  TIPFL=0 PER ACQUA, TIPFL=1 PER OLIO'
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      IF(CPF.LE.0.) CPF=4186.
      IF(CPFAD.LE.0.) CPFAD=4186.
      IF(TIF.EQ.0.)THEN
        DENS=1000.      ! densita' costanti
      ELSE              ! per maggior
        DENS=880.       ! semplicita'
      ENDIF
      DATI(ID2)   = VOL * DENS
      DATI(ID2+1) = WNOM
      DATI(ID2+2) = GSNOM
      DATI(ID2+3) = WP
      DATI(ID2+4) = TIF       ! 0 = acqua, 1 = olio lubrif.
      DATI(ID2+7) = CPF
      DATI(ID2+8) = CPFAD
      DATI(ID2+9) = GAMMULT
      
C
      ID2 = ID2 + 10           ! 2 posti per stoccaggio variabili
C
C---costanti di normalizzazione
C
      GAM0 = 1000.
C
C
      IF(WP.EQ.1)THEN
       CNXYU(IV1   ) = H0
       CNXYU(IV1+ 1) = T0
       CNXYU(IV1+ 2) = GAM0
       CNXYU(IV1+ 3) = Q0
       CNXYU(IV1+ 4) = W0
       CNXYU(IV1+ 5) = H0
       CNXYU(IV1+ 6) = W0
      ELSEIF(WP.EQ.2)THEN
       CNXYU(IV1   ) = H0
       CNXYU(IV1+ 1) = T0
       CNXYU(IV1+ 2) = Q0
       CNXYU(IV1+ 3) = W0
       CNXYU(IV1+ 4) = H0
       CNXYU(IV1+ 5) = T0
       CNXYU(IV1+ 6) = GAM0
       CNXYU(IV1+ 7) = W0
      ELSE
       WRITE(6,*)'IL BLOCCO NON HA INIZIALE "+" O "-"'
      ENDIF
C
      RETURN
      END
C     SUBROUTINE PRSCI31 (IFO,IBLOC,IOB,MOD,DEBL)
C      
C     CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
C     NSTATI = 0
C     NUSCIT = 3
C     NINGRE = 4
C     WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
C2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C     WRITE(IFO,3001)IOB
C3001 FORMAT('HURE',A4,2X,
C    $  57H--UA-- ENTALPIA DI USCITA                                )
C     WRITE(IFO,3002)IOB
C3002 FORMAT('TMED',A4,2X,
C    $  57H--UA-- TEMPERATURA MEDIA FLUIDO                          )
C     WRITE(IFO,3003)IOB
C3003 FORMAT('GAMM',A4,2X,
C    $  57H--UA-- PRODOTTO COEFF.* SUPERFICIE SCAMBIO               )
C     WRITE(IFO,3004)IOB
C3004 FORMAT('QREF',A4,2X,
C    $  57H--IN-- POTENZA ASSORBITA (>0 ENTRANTE)                   )
C     WRITE(IFO,3005)IOB
C3005 FORMAT('WREF',A4,2X,
C    $  57H--IN-- PORTATA                                           )
C     WRITE(IFO,3006)IOB
C3006 FORMAT('HIRE',A4,2X,
C    $  57H--IN-- ENTALPIA DI INGRESSO                              )
C     WRITE(IFO,3007)IOB
C3007 FORMAT('WADI',A4,2X,
C    $  57H--IN-- PORTATA FLUIDO ADIACENTE                          )
C
C     RETURN
C     END
C
C     SUBROUTINE PRSCI32 (IFO,IBLOC,IOB,MOD,DEBL)
C
C     CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80      
C     NSTATI = 0
C     NUSCIT = 3
C     NINGRE = 5
C     WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
C2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C     WRITE(IFO,3001)IOB
C3001 FORMAT('HURE',A4,2X,
C    $  57H--UA-- ENTALPIA DI USCITA                                )
C     WRITE(IFO,3002)IOB
C3002 FORMAT('TMED',A4,2X,
C    $  57H--UA-- TEMPERATURA MEDIA FLUIDO                          )
C     WRITE(IFO,3003)IOB
C3003 FORMAT('QREF',A4,2X,
C    $  57H--UA-- POTENZA CEDUTA (>0 USCENTE)                       )
C     WRITE(IFO,3004)IOB
C3004 FORMAT('WREF',A4,2X,
C    $  57H--IN-- PORTATA                                           )
C     WRITE(IFO,3005)IOB
C3005 FORMAT('HIRE',A4,2X,
C    $  57H--IN-- ENTALPIA DI INGRESSO                              )
C     WRITE(IFO,3006)IOB
C3006 FORMAT('TMAD',A4,2X,
C    $  57H--IN-- TEMPERATURA MEDIA FLUIDO ADIACENTE                )
C     WRITE(IFO,3007)IOB
C3007 FORMAT('GAMS',A4,2X,
C    $  57H--IN-- PROD. COEFF. * SUP. SCAMBIO LATO ADIACENTE        )
C     WRITE(IFO,3008)IOB
C3008 FORMAT('WADI',A4,2X,
C    $  57H--IN-- PORTATA FLUIDO ADIACENTE                          )
C     RETURN
C     END
C
C
C
C
C
C
C
      SUBROUTINE PRSCD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---ASSORBIMENTO DI POTENZA
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C$*$
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO HURE
C
C---descrizione equazione HURE in stazionario (max. 50 car)
C      SIGNEQ ( 1) = 
C
C---unita` di misura residuo HURE (max. 10 car)
C      UNITEQ ( 1) = 
C
C---costante di normalizzazione residuo HURE in stazionario
C      COSNOR ( 1) = 
C
C---topologia jacobiano in stazionario per il residuo HURE
      RETURN
      END
C
      SUBROUTINE PRSCI4(IOB,MOD)                                        
      CHARACTER*4 IBLOC*8
      COMMON/PRSC01/IBLOC                                               
      COMMON/NEWF01/ILEGICA,IBLOCC                                      
      CHARACTER*8 IBLOCC                                                
      CHARACTER*4 IOB                                                   
      CHARACTER*4 MODU                                                  
      CHARACTER*1 ICA,IMEN,IPIU                                         
      CHARACTER*1 IBL                                                   
      CHARACTER*4 MOD                                                   
      DATA IBL/' '/                                                     
      DATA IPIU/'+'/                                                    
      DATA IMEN/'-'/                                                    
C                                                                       
    2 CONTINUE                                                          
C                                                                       
      WRITE(6,2999)                                                     
 2999 FORMAT(//10X,'ASSEGNA UN CARATTERE'                               
     $ /5X,' - POTENZA IN INGRESSO  ===>  + '                    
     $ /5X,' - POTENZA IN USCITA  ===>  - ')                   
      READ(5,3001)ICA                                                   
      IF(ICA.EQ.IPIU)GO TO 1                                            
      IF(ICA.EQ.IMEN)GO TO 1                                            
      GO TO 2                                                           
 3001 FORMAT(A)                                                         
    1 CONTINUE                                                          
C                                                                       
      WRITE(MODU,'(A1,A3)')ICA,MOD                                      
      WRITE(IBLOC,'(2A4)')MODU,IOB                                      
C                                                                       
      RETURN                                                            
      END                                                               
C
C
C
      SUBROUTINE PRSCC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL PRSC
C$$$$$     !!!!!!! INIZIO ISTRUZIONI PER SCCS !!!!!!!
       CHARACTER*80 SccsID
       DATA SccsID/'@(#)prsc.f	3.1\t 3.1\t 9/5/94'/          
C$$$$$     !!!!!!! FINE ISTRUZIONI PER SCCS !!!!!!!


C
C---ASSORBIMENTO DI POTENZA
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL PRSCJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL PRSC (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL PRSCJC (2,...
C
C      jacobiano numerico  CALL PRSCJC (3,...
C
C$*$
  300 CONTINUE
      CALL PRSCJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE PRSCJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      CHARACTER*4 IBLOC*8
      LOGICAL KREGIM
      COMMON/PRSC01/IBLOC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL PRSC
C
C
      WP = DATI(IPD + 3)
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
      NVAR=8
      IF(WP.EQ.1.)  NVAR=7
C

       DO 10 I=1,NVAR
        DO 11 J=1,3
          AJAC(J,I)=1.
 11     CONTINUE
 10    CONTINUE
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
C
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 3
      NINGRE = 4
      IF(WP.EQ.2) NINGRE=5
          PRINT*,'NVAR, WP',NVAR, WP

      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,PRSC)
      RETURN
      END
C
C
C
      SUBROUTINE PRSC (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM
      REAL  MASS
      CHARACTER*4 IBLOC*8
      COMMON/PRSC01/IBLOC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      Q0 = W0 * H0
      GAM0=1000.
C
C
C
C
C---ASSORBIMENTO DI POTENZA
C   calcolo residui
C
C---decodifica variabili e dati
C
C       DATI
C
      MASS   = DATI(IPD)            !massa fluido
      WNOM   = DATI(IPD+1)          !portata nominale
      GSNOM  = DATI(IPD+2)          !prodotto gam*sup nominale
      WP     = DATI(IPD+3)          !tipo settaggio modulo
      TIF    = DATI(IPD+4)          !fluido:0 per acqua, 1 per olio
      CPF    = DATI(IPD+7)          !calore specifico fluido
      CPFAD  = DATI(IPD+8)          !calore specifico fluido adiacente
      GAMMULT= DATI(IPD+9)          !Moltiplicatore gamma in ingresso
          PRINT*,'CPFAD, GAMMULT',CPFAD, GAMMULT
C
C       VARIABILI
C
      IF(WP.EQ.1.)THEN
        HURE   = XYU(IXYU   )*H0    !entalpia usc.
        TMED   = XYU(IXYU+ 1)*T0    !t media fluido
        GAMM   = XYU(IXYU+ 2)*GAM0  !gam*sup
        QREF   = XYU(IXYU+ 3)*Q0    !potenza entrante
        WREF   = XYU(IXYU+ 4)*W0    !portata
        HIRE   = XYU(IXYU+ 5)*H0    !entalpia ingresso
        WADI   = XYU(IXYU+ 6)*W0    !portata fluido adiacente
      ENDIF
      IF(WP.EQ.2.)THEN
        HURE   = XYU(IXYU   )*H0
        TMED   = XYU(IXYU+ 1)*T0
        QREF   = XYU(IXYU+ 2)*Q0    !potenza uscente
        WREF   = XYU(IXYU+ 3)*W0
        HIRE   = XYU(IXYU+ 4)*H0
        TMAD   = XYU(IXYU+ 5)*T0    !t media fluido adiacente
        GAAD   = XYU(IXYU+ 6)*GAM0*GAMMULT  !gam * sup adiacente
        WADI   = XYU(IXYU+ 7)*W0    !portata fluido adiacente     
        IF (WREF.GT.(-0.04*WNOM)) THEN
           GAMM=GSNOM*((WREF+0.04*WNOM)/WNOM)**0.8
        ELSE
           GAMM=0.
        ENDIF
      ENDIF
C
         if(abs(wadi).lt.1.e-2) wabsdi=1.e-2
         if(abs(wref).lt.1.e-2) wabsref=1.e-2
         
         CTF=CPF*wabsref
         CTFAD=CPFAD*wabsdi
                  

         IF((CTF-CTFAD).LT.1.) THEN
          RAP=1.
         ELSE
          RAP = CTF/CTFAD
         ENDIF
         BETA=RAP/(1+RAP)
      P = 3.E5               !pressione per default (conta poco)
      


C$*$
      IF(TIF.EQ.0.)THEN                  !     
        SING   = SHEV(P,HIRE,1)            !
        TING   = TEV(P,SING,1)               !calcolo temperature per       
        SUSC   = SHEV(P,HURE,1)                !acqua o per olio
        TUSC   = TEV(P,SUSC,1)                   ! 
      ELSE                                         !
        CALL TABNAF(-6,TING,RO,VD,CD,CP,HIRE,DRDT)  !
        CALL TABNAF(-6,TUSC,RO,VD,CD,CP,HURE,DRDT)    !
      ENDIF
C---calcolo residui
C      
C--residuo n.  1                     *******
      IF(.not.kregim.and.(IFUN.EQ.2.AND.ITERT.EQ.0)) DATI(IPD+5)=HURE
      IF(KREGIM)THEN
           IF(WP.EQ.1.)THEN
             RNI(1) = ((HURE - HIRE)*WREF - QREF)/Q0
           ELSE
             RNI(1) = ((HURE - HIRE)*WREF + QREF)/Q0
           ENDIF
      ELSE
        HUPR = DATI(IPD+5)
        IF(WP.EQ.1.)THEN
          RNI(1) = (HURE- HUPR - 
     &             (QREF + WREF*(HIRE-HURE))/MASS*DTINT)/H0
        ENDIF
        IF(WP.EQ.2.)THEN
          RNI(1) = (HURE- HUPR + 
     &             (QREF - WREF*(HIRE-HURE))/MASS*DTINT)/H0      


        ENDIF
      ENDIF
C--residuo n.  2                     *******
      RNI(2) = (TMED - ((1.-BETA)*TUSC+BETA*TING))/T0
      PRINT*,'BETA, CTF, CTFAD, RAP, wabsref, wabsdi, TUSC,TING',
     $    BETA, CTF, CTFAD, RAP, wabsref, wabsdi,TUSC,TING
C
C--residuo n.  3                 potenza(+), coeff. scambio(-)
C
      IF(WP.EQ.1.)THEN
        IF (WREF.GT.(-0.04*WNOM)) THEN
          RNI(3) = (GAMM - GSNOM * ((WREF+0.04*WNOM)/WNOM)**0.8)/GAM0
        ELSE
          RNI(3) = GAMM / GAM0
        ENDIF
      ENDIF
      IF(WP.EQ.2.)THEN
          GAMTOT = GAMM*GAAD / (GAMM + GAAD)
C          RNI(3) = (QREF - GAMTOT * (TMED - TMAD) )/Q0
          RNI(3) = (QREF - GAMTOT * (TMED - TMAD) )/Q0

          PRINT*,'RNI3=',RNI(3),'RNI3Q0=',RNI(3)*Q0
          PRINT*,'QREF, GAMTOT,TMED,TMAD,GAAD,GAMM, GAMMULT',
     $   QREF,GAMTOT,TMED,TMAD,GAAD,GAMM, GAMMULT
          
      ENDIF
      RETURN
      END
C
C
C
      SUBROUTINE PRSCI3 (IFO,IOB,DEBL)
C
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*1 IWP,IPIU,IMEN
      COMMON/PRSC01/IBLOC

      NSTATI = 0
      NUSCIT = 3
      NINGRE = 5 
    
 
      DATA MOD/'PRSC'/
      DATA IPIU/'+'/
      DATA IMEN/'-'/
C
   
      CALL PRSCI4(IOB,MOD)
            WRITE(6,'(A)') 'Letto: ', IBLOC
      READ(IBLOC,'(A1)')IWP
CCCCCCCCCCCCC      
      IF(IWP.EQ.IPIU) THEN
      	     	
C CALL PRSCI31(IFO,IBLOC,IOB,MOD,DEBL)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('HURE',A4,2X,
     $  57H--UA-- ENTALPIA DI USCITA                                )
      WRITE(IFO,3002)IOB
 3002 FORMAT('TMED',A4,2X,
     $  57H--UA-- TEMPERATURA MEDIA FLUIDO                          )
      WRITE(IFO,3003)IOB
 3003 FORMAT('GAMM',A4,2X,
     $  57H--UA-- PRODOTTO COEFF.* SUPERFICIE SCAMBIO               )
      WRITE(IFO,3004)IOB
 3004 FORMAT('QREF',A4,2X,
     $  57H--IN-- POTENZA ASSORBITA (>0 ENTRANTE)                   )
      WRITE(IFO,3005)IOB
 3005 FORMAT('WREF',A4,2X,
     $  57H--IN-- PORTATA                                           )
      WRITE(IFO,3006)IOB
 3006 FORMAT('HIRE',A4,2X,
     $  57H--IN-- ENTALPIA DI INGRESSO                              )
      WRITE(IFO,3007)IOB
 3007 FORMAT('WADI',A4,2X,
     $  57H--IN-- PORTATA FLUIDO ADIACENTE                          )
      
      ENDIF
CCCCCCCCCC
      IF(IWP.EQ.IMEN) THEN
            WRITE(6,'(A)') 'Letto 2: ', IBLOC
      	
C CALL PRSCI32(IFO,IBLOC,IOB,MOD,DEBL)
      WRITE(IFO,12999)IBLOC,IOB,MOD,DEBL
12999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,13001)IOB
13001 FORMAT('HURE',A4,2X,
     $  57H--UA-- ENTALPIA DI USCITA                                )
      WRITE(IFO,13002)IOB
13002 FORMAT('TMED',A4,2X,
     $  57H--UA-- TEMPERATURA MEDIA FLUIDO                          )
      WRITE(IFO,13003)IOB
13003 FORMAT('QREF',A4,2X,
     $  57H--UA-- POTENZA CEDUTA (>0 USCENTE)                       )
      WRITE(IFO,13004)IOB
13004 FORMAT('WREF',A4,2X,
     $  57H--IN-- PORTATA                                           )
      WRITE(IFO,13005)IOB
13005 FORMAT('HIRE',A4,2X,
     $  57H--IN-- ENTALPIA DI INGRESSO                              )
      WRITE(IFO,13006)IOB
13006 FORMAT('TMAD',A4,2X,
     $  57H--IN-- TEMPERATURA MEDIA FLUIDO ADIACENTE                )
      WRITE(IFO,13007)IOB
13007 FORMAT('GAMS',A4,2X,
     $  57H--IN-- PROD. COEFF. * SUP. SCAMBIO LATO ADIACENTE        )
      WRITE(IFO,13008)IOB
13008 FORMAT('WADI',A4,2X,
     $  57H--IN-- PORTATA FLUIDO ADIACENTE                          )
      
      ENDIF
C
      RETURN
      END

