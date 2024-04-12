      SUBROUTINE VENSI3 (IFO,IOB,DEBL)
      PARAMETER (NV=7)
C
      COMMON/VENS01/IBLOC
      COMMON/VENS02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50
C
      DATA MOD/'VENS'/
      DATA (NOMI(I), TIPI(I), DESC(I), I=1,NV)/
     $ 'WARI','UA','PORTATA FLUIDO VENTILATORE',
     $ 'GAMM','UA','COEFF. SCAMBIO CONVETTIVO',
     $ 'TFME','UA','TEMPERATURA MEDIA FLUIDO',
     $ 'OMPV','IN','VELOCITA'' DI ROTAZIONE',
     $ 'TING','IN','TEMPERATURA INGRESSO FLUIDO',
     $ 'CGAM','IN','CORRETTIVO COEFF. DI SCAMBIO',
     $ 'TMET','IN','TEMPERATURA PARETE METALLICA'/
C
      CALL VENSI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 3
      NINGRE = 4
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)
      RETURN
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
 3000 FORMAT(2A4,'  --',A2,'-- ',A)
      END
C
C
C
      SUBROUTINE VENSI4 (IOB,MOD)
      COMMON/VENS01/IBLOC
      COMMON/VENS02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE VENSI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2)
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
           DATA G0/1000./,OM0/314.1592/
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL WARI, GAMM, TOUT, OMPV, TING                                 !SNGL
      REAL CGAM, TMET, WNOM, TNOM, OMNOM                                !SNGL
      REAL SSCAM, SLIB, DEXT, CP, MI                                    !SNGL
      REAL K, SEPS 
C      DOUBLE PRECISION WARI, GAMM, TOUT, OMPV, TING                     !DBLE
C      DOUBLE PRECISION CGAM, TMET, WNOM, TNOM, OMNOM                    !DBLE
C      DOUBLE PRECISION SSCAM, SLIB, DEXT, CP, MI                        !DBLE
C      DOUBLE PRECISION K, SEPS 
C
C---ventilatore a pale 
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'W_NOM   '
     $             ,'T_NOM   '
     $             ,'OME_NOM '
     $             ,'SUP_SCAM'
     $             ,'SEZ_LIB '
     $             ,'DIA_EXT '
     $             ,'CP_FLU  '
     $             ,'MI_FLU  '
     $             ,'K_FLU   '
      WRITE(14,500) 'GAMNOM  '
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) WNOM
     $            ,TNOM
     $            ,OMNOM
     $            ,SSCAM
     $            ,SLIB
     $            ,DEXT
     $            ,CP
     $            ,MI
     $            ,K
      READ(14,501) GNOM
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C---------- DEFAULTS
            IF (MI.EQ.0.) MI=1812.E-8
            IF (CP.EQ.0.) CP=1100.
            IF (K.EQ.0.) K=0.026
c*            SEPS=0.01
             seps = 0.5      !prova tassi 9/05
C---------- CALCOLO GAMNOM
            IF(GNOM.EQ.0.) THEN
             GM=WNOM/SLIB 
             X=DEXT*GM/MI
             Y=X**(-0.523)
             GAMNOM=Y*CP*GM/((CP*MI/K)**0.666667)
            ELSE
             GAMNOM=GNOM
            ENDIF
      DATI(ID2   ) = WNOM/W0
      DATI(ID2+ 1) = TNOM/T0
      DATI(ID2+ 2) = OMNOM/OM0
      DATI(ID2+ 3) = SSCAM
      DATI(ID2+ 4) = SLIB
      DATI(ID2+ 5) = DEXT
      DATI(ID2+ 6) = CP
      DATI(ID2+ 7) = MI
      DATI(ID2+ 8) = K
      DATI(ID2+ 9) = SEPS
C
      DATI(ID2+ 10)= GAMNOM/G0
      ID2 = ID2+10
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C---costanti di normalizzazione
C
      CNXYU(IV1   ) = W0
      CNXYU(IV1+ 1) = G0
      CNXYU(IV1+ 2) = T0
      CNXYU(IV1+ 3) = OM0
      CNXYU(IV1+ 4) = T0
      CNXYU(IV1+ 5) = 1.
      CNXYU(IV1+ 6) = T0
C
      RETURN
      END
C
C
C
      SUBROUTINE VENSC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL VENS
C
      REAL WARI, GAMM, TOUT, OMPV, TING                                 !SNGL
      REAL CGAM, TMET, WNOM, TNOM, OMNOM                                !SNGL
      REAL SSCAM, SLIB, DEXT, CP, MI                                    !SNGL
      REAL K, SEPS
C      DOUBLE PRECISION WARI, GAMM, TOUT, OMPV, TING                     !DBLE
C      DOUBLE PRECISION CGAM, TMET, WNOM, TNOM, OMNOM                    !DBLE
C      DOUBLE PRECISION SSCAM, SLIB, DEXT, CP, MI                        !DBLE
C      DOUBLE PRECISION K, SEPS
C
C---ventilatore a pale 
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL VENSJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL VENS (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL VENSJC (2,...
C
C      jacobiano numerico  CALL VENSJC (3,...
C
C$*$
  300 CONTINUE
      CALL VENSJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE VENSJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL VENS
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL WARI, GAMM, TOUT, OMPV, TING                                 !SNGL
      REAL CGAM, TMET, WNOM, TNOM, OMNOM                                !SNGL
      REAL SSCAM, SLIB, DEXT, CP, MI                                    !SNGL
      REAL K, SEPS 
C      DOUBLE PRECISION WARI, GAMM, TOUT, OMPV, TING                     !DBLE
C      DOUBLE PRECISION CGAM, TMET, WNOM, TNOM, OMNOM                    !DBLE
C      DOUBLE PRECISION SSCAM, SLIB, DEXT, CP, MI                        !DBLE
C      DOUBLE PRECISION K, SEPS 
C
      GOTO (1,2,2), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
C---equazione n.1 (algebrica):
C   ---dipendenza da WARI
      AJAC(1,1)=1.
C   ---dipendenza da GAMM
      AJAC(1,2)=1.
C   ---dipendenza da TOUT
      AJAC(1,3)=1.
C   ---dipendenza da OMPV
      AJAC(1,4)=1.
C   ---dipendenza da TING
      AJAC(1,5)=1.
C   ---dipendenza da CGAM
      AJAC(1,6)=1.
C   ---dipendenza da TMET
      AJAC(1,7)=1.
C
C---equazione n.2 (algebrica):
C   ---dipendenza da WARI
      AJAC(2,1)=1.
C   ---dipendenza da GAMM
      AJAC(2,2)=1.
C   ---dipendenza da TOUT
      AJAC(2,3)=1.
C   ---dipendenza da OMPV
      AJAC(2,4)=1.
C   ---dipendenza da TING
      AJAC(2,5)=1.
C   ---dipendenza da CGAM
      AJAC(2,6)=1.
C   ---dipendenza da TMET
      AJAC(2,7)=1.
C
C---equazione n.3 (algebrica):
C   ---dipendenza da WARI
      AJAC(3,1)=1.
C   ---dipendenza da GAMM
      AJAC(3,2)=1.
C   ---dipendenza da TOUT
      AJAC(3,3)=1.
C   ---dipendenza da OMPV
      AJAC(3,4)=1.
C   ---dipendenza da TING
      AJAC(3,5)=1.
C   ---dipendenza da CGAM
      AJAC(3,6)=1.
C   ---dipendenza da TMET
      AJAC(3,7)=1.
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
      WARI   = XYU(IXYU   )
      GAMM   = XYU(IXYU+ 1)
      TOUT   = XYU(IXYU+ 2)
      OMPV   = XYU(IXYU+ 3)
      TING   = XYU(IXYU+ 4)
      CGAM   = XYU(IXYU+ 5)
      TMET   = XYU(IXYU+ 6)
C
      WNOM   = DATI(IPD   )
      TNOM   = DATI(IPD+ 1)
      OMNOM  = DATI(IPD+ 2)
      SSCAM  = DATI(IPD+ 3)
      SLIB   = DATI(IPD+ 4)
      DEXT   = DATI(IPD+ 5)
      CP     = DATI(IPD+ 6)
      MI     = DATI(IPD+ 7)
      K      = DATI(IPD+ 8)
      SEPS   = DATI(IPD+ 9)
C
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C$*$
C
C--derivata del residuo n.  1 (equazione algebrica)   *******
C     --- rispetto alla variabile WARI
C      AJAC(1,1) = 
C     --- rispetto alla variabile GAMM
C      AJAC(1,2) = 
C     --- rispetto alla variabile TOUT
C      AJAC(1,3) = 
C     --- rispetto alla variabile OMPV
C      AJAC(1,4) = 
C     --- rispetto alla variabile TING
C      AJAC(1,5) = 
C     --- rispetto alla variabile CGAM
C      AJAC(1,6) = 
C     --- rispetto alla variabile TMET
C      AJAC(1,7) = 
C
C--derivata del residuo n.  2 (equazione algebrica)   *******
C     --- rispetto alla variabile WARI
C      AJAC(2,1) = 
C     --- rispetto alla variabile GAMM
C      AJAC(2,2) = 
C     --- rispetto alla variabile TOUT
C      AJAC(2,3) = 
C     --- rispetto alla variabile OMPV
C      AJAC(2,4) = 
C     --- rispetto alla variabile TING
C      AJAC(2,5) = 
C     --- rispetto alla variabile CGAM
C      AJAC(2,6) = 
C     --- rispetto alla variabile TMET
C      AJAC(2,7) = 
C
C--derivata del residuo n.  3 (equazione algebrica)   *******
C     --- rispetto alla variabile WARI
C      AJAC(3,1) = 
C     --- rispetto alla variabile GAMM
C      AJAC(3,2) = 
C     --- rispetto alla variabile TOUT
C      AJAC(3,3) = 
C     --- rispetto alla variabile OMPV
C      AJAC(3,4) = 
C     --- rispetto alla variabile TING
C      AJAC(3,5) = 
C     --- rispetto alla variabile CGAM
C      AJAC(3,6) = 
C     --- rispetto alla variabile TMET
C      AJAC(3,7) = 
C
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      NUSCIT = 3
      NINGRE = 4
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,VENS)
      RETURN
      END
C
C
C
      SUBROUTINE VENS (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C          DATA G0/1000./,OM0/314.1592/
C
C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE
C
C
      REAL WARI, GAMM, TOUT, OMPV, TING                                 !SNGL
      REAL CGAM, TMET, WNOM, TNOM, OMNOM                                !SNGL
      REAL SSCAM, SLIB, DEXT, CP, MI                                    !SNGL
      REAL K, SEPS 
C      DOUBLE PRECISION WARI, GAMM, TOUT, OMPV, TING                     !DBLE
C      DOUBLE PRECISION CGAM, TMET, WNOM, TNOM, OMNOM                    !DBLE
C      DOUBLE PRECISION SSCAM, SLIB, DEXT, CP, MI                        !DBLE
C      DOUBLE PRECISION K, SEPS 
C
      G0=1000.
      OM0=314.1592
C
C---ventilatore a pale 
C   calcolo residui
C
C---decodifica variabili e dati
C
      WARI   = XYU(IXYU   )
      GAMM   = XYU(IXYU+ 1)
      TOUT   = XYU(IXYU+ 2)
      OMPV   = XYU(IXYU+ 3)
      TING   = XYU(IXYU+ 4)
      CGAM   = XYU(IXYU+ 5)
      TMET   = XYU(IXYU+ 6)
C
      WNOM   = DATI(IPD   )
      TNOM   = DATI(IPD+ 1)
      OMNOM  = DATI(IPD+ 2)
      SSCAM  = DATI(IPD+ 3)
      SLIB   = DATI(IPD+ 4)
      DEXT   = DATI(IPD+ 5)
      CP     = DATI(IPD+ 6)
      MI     = DATI(IPD+ 7)
      K      = DATI(IPD+ 8)
      SEPS   = DATI(IPD+ 9)
      GAMNOM = DATI(IPD+ 10)
C
C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE
C--- (LIBRARIAN)
C
C
C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE
C
C$*$
C
C---calcolo residui
C
C--residuo n.  1 (equazione algebrica)   *******
            RNI(1) = WARI - WNOM*(OMPV/OMNOM)/(TING/TNOM)
C
            IF(WARI.GE.0.) THEN
              WCALC=WARI
            ELSE
              WCALC=0.
            ENDIF
C--residuo n.  2 (equazione algebrica)   *******
            RNI(2) = GAMM-CGAM*(SEPS*GAMNOM+(1.-SEPS)*GAMNOM*
     &               (WCALC/WNOM)**0.477)
C     &              ABS((WARI/WNOM))**0.477)
C
C--residuo n.  3 (equazione algebrica)   *******
            RNI(3) = TOUT - (2*W0*WARI*CP*TING + G0*GAMM*SSCAM*TMET)
     &               /(2*W0*WARI*CP+G0*GAMM*SSCAM)
C
      RETURN
      END
C
C
C
      SUBROUTINE VENSD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---ventilatore a pale 
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C$*$
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO WARI
C
C---descrizione equazione WARI in stazionario (max. 50 car)
       SIGNEQ ( 1) = ' '
C
C---unita` di misura residuo WARI (max. 10 car)
       UNITEQ ( 1) = ' '
C
C---costante di normalizzazione residuo WARI in stazionario
       COSNOR ( 1) = W0
C
C---topologia jacobiano in stazionario per il residuo WARI
C------dipendenza dalla variabile WARI
      ITOPVA ( 1, 1) = 1
C------dipendenza dalla variabile GAMM
      ITOPVA ( 1, 2) = 1
C------dipendenza dalla variabile TOUT
      ITOPVA ( 1, 3) = 1
C------dipendenza dalla variabile OMPV
      ITOPVA ( 1, 4) = 1
C------dipendenza dalla variabile TING
      ITOPVA ( 1, 5) = 1
C------dipendenza dalla variabile CGAM
      ITOPVA ( 1, 6) = 1
C------dipendenza dalla variabile TMET
      ITOPVA ( 1, 7) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO GAMM
C
C---descrizione equazione GAMM in stazionario (max. 50 car)
       SIGNEQ ( 2) = ' '
C
C---unita` di misura residuo GAMM (max. 10 car)
       UNITEQ ( 2) = ' '
C
C---costante di normalizzazione residuo GAMM in stazionario
       COSNOR ( 2) = 1000.
C
C---topologia jacobiano in stazionario per il residuo GAMM
C------dipendenza dalla variabile WARI
      ITOPVA ( 2, 1) = 1
C------dipendenza dalla variabile GAMM
      ITOPVA ( 2, 2) = 1
C------dipendenza dalla variabile TOUT
      ITOPVA ( 2, 3) = 1
C------dipendenza dalla variabile OMPV
      ITOPVA ( 2, 4) = 1
C------dipendenza dalla variabile TING
      ITOPVA ( 2, 5) = 1
C------dipendenza dalla variabile CGAM
      ITOPVA ( 2, 6) = 1
C------dipendenza dalla variabile TMET
      ITOPVA ( 2, 7) = 1
C
C DATI RELATIVI ALL'EQUAZIONE ALGEBRICA RESIDUO TOUT
C
C---descrizione equazione TOUT in stazionario (max. 50 car)
       SIGNEQ ( 3) = ' '
C
C---unita` di misura residuo TOUT (max. 10 car)
       UNITEQ ( 3) = ' '
C
C---costante di normalizzazione residuo TOUT in stazionario
       COSNOR ( 3) = T0 
C
C---topologia jacobiano in stazionario per il residuo TOUT
C------dipendenza dalla variabile WARI
      ITOPVA ( 3, 1) = 1
C------dipendenza dalla variabile GAMM
      ITOPVA ( 3, 2) = 1
C------dipendenza dalla variabile TOUT
      ITOPVA ( 3, 3) = 1
C------dipendenza dalla variabile OMPV
      ITOPVA ( 3, 4) = 1
C------dipendenza dalla variabile TING
      ITOPVA ( 3, 5) = 1
C------dipendenza dalla variabile CGAM
      ITOPVA ( 3, 6) = 1
C------dipendenza dalla variabile TMET
      ITOPVA ( 3, 7) = 1
      RETURN
      END
