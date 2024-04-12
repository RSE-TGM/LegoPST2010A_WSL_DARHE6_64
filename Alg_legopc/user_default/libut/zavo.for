
C-------------------------------------------------------------------------
C-----                                                               -----
C-----                            MODULO ZAVO                        -----
C-----                                                               -----
C-----            CARICO ZAVORRA CON DIPENDENZA DALLA TENSIONE       -----
C-----                                                               -----
C-----                 (INSERIMENTO DEI PROFILI DI P & Q)            -----
C-----                                                               -----
C-----                                                               -----
C-------------------------------------------------------------------------
C
      SUBROUTINE ZAVOI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2),IBASE
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      REAL IR00, IX00, IM00, KPV, KQV                                   !SNGL
C
      QBASE=H0*W0
C
C---CARICO ZAVORRA CON DIPENDENZA ESPONENZIALE DALLA TENSIONE
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'Vnom_V  '
     $             ,'Pnom_W  '
     $             ,'Qnom_VAR'
     $             ,'P2_W    '
     $             ,'T1_s    '
     $             ,'T2_s    '
     $             ,'T3_s    '
     $             ,'KpV     '
     $             ,'KqV     '
      WRITE(14,500) 'PU?_1=SI'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) VNOM
     $            ,PNOM
     $            ,QNOM
     $            ,P2
     $            ,T1
     $            ,T2
     $            ,T3
     $            ,KPV
     $            ,KQV
      READ(14,501) PU
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C----ASSEGNAZIONE DEI DATI DI DEFAULT----      
C
      IF (P2.EQ.0.) P2=1.2*PNOM
      IF (T1.EQ.0.) T1=0.5
      IF (T2.EQ.0.) T2=900.
      IF (T3.EQ.0.) T3=0.5
      IF (KPV.EQ.0.) KPV=1.25
      IF (KQV.EQ.0.) KQV=2.5
C
      DATI(ID2   ) = VNOM
      DATI(ID2+ 1) = PNOM
      DATI(ID2+ 2) = QNOM
      DATI(ID2+ 3) = P2
      DATI(ID2+ 4) = T1
      DATI(ID2+ 5) = T2
      DATI(ID2+ 6) = T3
      DATI(ID2+ 7) = KPV
      DATI(ID2+ 8) = KQV
      DATI(ID2+ 9) = PU
      DATI(ID2+10) = 0.
      DATI(ID2+11) = 0.
      DATI(ID2+12) = 0.
      ID2 = ID2+12
C
C---costanti di normalizzazione
C
      IBASE=QBASE/(SQRT(3.)*VNOM)
C
      IF (PU.EQ.1) THEN
        DO J=1,14
          CNXYU(IV1+J-1)=1.
        END DO
      ELSE
        CNXYU(IV1   ) = IBASE
        CNXYU(IV1+ 1) = IBASE
        CNXYU(IV1+ 2) = QBASE
        CNXYU(IV1+ 3) = QBASE
        CNXYU(IV1+ 4) = IBASE
        CNXYU(IV1+ 5) = VNOM
        CNXYU(IV1+ 6) = 1.
        CNXYU(IV1+ 7) = VNOM
        CNXYU(IV1+ 8) = VNOM
        CNXYU(IV1+ 9) = QBASE
        CNXYU(IV1+10) = QBASE
        CNXYU(IV1+11) = 1.
        CNXYU(IV1+12) = 1.
        CNXYU(IV1+13) = 1.
      END IF
C
      RETURN
      END
C
C
C
      SUBROUTINE ZAVOC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/NEQUAZ/NEQMOD
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT 
C     COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL ZAVO
C
      REAL IR00, IX00, IM00, KPV, KQV                                   !SNGL
C	print*,'entro in zavoc1'
C
C---CARICO ZAVORRA CON DIPENDENZA ESPONENZIALE DALLA TENSIONE
C
      NEQMOD = 2
C
      GO TO(100,200,300),IFUN
C
  100 CONTINUE
C
C---topologia jacobiano
C      
C
      CALL ZAVOJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C      
c
C---calcolo residui
C
  200 CALL ZAVO (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C     
C
  300 CONTINUE
C
C	print*,'calcola lo jacobiano'
C
      CALL ZAVOJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
C      print*,'fine calcolo jacobiano'
C	print*,'esco da ZAVOc1'
C
      RETURN
      END
C
C
C
      SUBROUTINE ZAVOJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM,JFLOLOG,SISC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
C     COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL ZAVO
C
      REAL IR00, IX00, IM00, KPV, KQV                                  !SNGL
C	print*,'entro in jc'
C
      NEQ    = 2
      IF(KREGIM) NEQ = 2 + 5
      NVAR = 14
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
      DO J=1,NEQ
        DO I=1,NVAR
        IF(I.LT.3.OR.I.GT.7) THEN
         AJAC(J,I)=1.
        ENDIF
        END DO 
      END DO
C
C
      RETURN
C
    2 CONTINUE
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 0
      EPS    = 1.E-3
      EPSLIM = 1.E-4
C
      CALL ZAVOJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $             NEQ,NVAR,NSTATI,EPS,EPSLIM,ZAVO)
C
C	print*,'esco da jc'
      RETURN
      END
C
C----Subroutine NAJAC con aggiornamento non equazioni----
      SUBROUTINE ZAVOJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1               NRIG,NCOL,NSTATI,EPS,EPSLIM,RESIDUI)
C
C routine generale di calcolo jacobiano numerico
C con incremento EPS in p.u. ( valore minimo assoluto EPSLIM )
C i residui devono essere calcolati dalla routine ( da dich.EXTERNAL )
C SUBROUTINE RESIDUI(IFUN,IXYU,XYU,IPD,DATI,RN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      EXTERNAL RESIDUI
C
C     residui(ifun,ixyu,xyu,ipd,dati,rn)
C
      CALL RESIDUI(3,IXYU,XYU,IPD,DATI,RN)
C
      DO 30 J=1,NCOL
      IF(KREGIM.OR.J.LT.3.OR.J.GT.7) THEN
      VAR=EPS*XYU(IXYU+J-1)
      IF(ABS(VAR).LT.EPSLIM) VAR=EPSLIM
C
      DO 10 K=1,NCOL
      CXYU(K)=XYU(IXYU+K-1)
      IF(K.EQ.J) CXYU(K)=CXYU(K)+VAR
   10      CONTINUE
C
      CALL RESIDUI(3,1,CXYU,IPD,DATI,CRN)
C
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(CRN(I)-RN(I))/VAR
      IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
   20      CONTINUE
       ENDIF
   30      CONTINUE
C
C
      RETURN
      END
C
C
C
      SUBROUTINE ZAVO (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM,JFLOLOG,SISC,STATO,STATO_PREC
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/NEQUAZ/NEQMOD
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C     COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                    !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL IR00, IX00, IM00, DTINT, KPV, KQV, GV, BV                   !SNGL
C
C--- CARICO ZAVORRA CON DIPENDENZA DALLA TENSIONE (esponenziale) 
C
C--- decodifica variabili e dati
C
C	print*,'inizio ZAVO'
      IR00   = XYU(IXYU   )            ! Uscite
      IX00   = XYU(IXYU+ 1)
      QATT   = XYU(IXYU+ 2)
      QREA   = XYU(IXYU+ 3)
      IM00   = XYU(IXYU+ 4)
      VM00   = XYU(IXYU+ 5)
      FDIP   = XYU(IXYU+ 6)
      VR00   = XYU(IXYU+ 7)            ! Ingressi
      VX00   = XYU(IXYU+ 8)
      P100   = XYU(IXYU+ 9)            ! Ingressi
      Q100   = XYU(IXYU+10)
      FP00   = XYU(IXYU+11)
      FQ00   = XYU(IXYU+12)
      SISC   = JFLOLOG(XYU(IXYU+13))
C
C
      VNOM   = DATI(IPD   )
      PNOM   = DATI(IPD+ 1)
      QNOM   = DATI(IPD+ 2)
      P2     = DATI(IPD+ 3)
      T1     = DATI(IPD+ 4)
      T2     = DATI(IPD+ 5)
      T3     = DATI(IPD+ 6)
      KPV    = DATI(IPD+ 7)
      KQV    = DATI(IPD+ 8)
      PU     = DATI(IPD+ 9)
C$*$
C
C******************** CALCOLO PARAMETRI ******************
C
      QBASE = H0*W0
      VV = SQRT(abs(VR00*VR00+VX00*VX00))
C
      IF (KREGIM) THEN
        IF (SISC) THEN
          DATI(IPD+11)=1.E6
          STATO=.TRUE.
          DATI(IPD+10)=STATO
          DATI(IPD+12)=STATO
          GV = FP00*(PNOM/QBASE)*VV**(KPV-2.)
          BV = -FQ00*(QNOM/QBASE)*VV**(KQV-2.)
C
          RNI(1) = -IR00-VR00*GV+VX00*BV
          RNI(2) = -IX00-VX00*GV-VR00*BV
          RNI(3) = -QATT-VR00*IR00-VX00*IX00
          RNI(4) = -QREA-VX00*IR00+VR00*IX00
          RNI(5) = -IM00+SQRT(IR00*IR00+IX00*IX00)
          RNI(6) = -VM00+SQRT(VR00*VR00+VX00*VX00)
          QAPP =SQRT(QATT*QATT+QREA*QREA) 
          IF (QAPP.GT.0.001) THEN
           FDP0 = ABS(QATT)/QAPP
          ELSE
           FDP0 = 0.
          END IF
          RNI(7) = -FDIP+FDP0
C
        ELSE
          DATI(IPD+11)=0.
          STATO=.FALSE.
          DATI(IPD+10)=STATO
          DATI(IPD+12)=STATO
C
          RNI(1) = IR00
          RNI(2) = IX00
	  RNI(3) = QATT
	  RNI(4) = QREA
	  RNI(5) = IM00
	  RNI(6) = VM00
          RNI(7) = FDIP
C          
        ENDIF
        RETURN
      ELSE
C----
C----              TRANSITORIO
C----
C
      IF (ITERT.EQ.0.AND.IFUN.EQ.2) THEN
        IF(SISC.AND.(SQRT(VR00*VR00+VX00*VX00).GT.0.1)) THEN 
          STATO =.TRUE.     ! Carico alimentato
        ELSE
          STATO =.FALSE.    ! carico disalimentato
        ENDIF
        DATI(IPD+12)=STATO
      ELSE
        STATO=DATI(IPD+12)
      ENDIF 
C
      STATO_PREC =   DATI(IPD+10)
      TEMPO_ATTUALE= DATI(IPD+11)
C
C
      IF (ITERT.EQ.0.AND.IFUN.EQ.2) THEN
        IF(STATO_PREC.NE.STATO) THEN 
          DATI(IPD+10) = STATO
          DATI(IPD+11) = 0.
        ENDIF
      ENDIF
C--
C----- Espressioni delle potenze attiva e reattiva
C--
C
      IF(STATO) THEN                                     !Carico alimentato
        TEMPO_ATTUALE = DATI(IPD+11)
        IF (ITERT.EQ.0.AND.IFUN.EQ.2) THEN
           TEMPO_ATTUALE=TEMPO_ATTUALE+DTINT
           DATI(IPD+11)=TEMPO_ATTUALE
        ENDIF
C
C
        IF (TEMPO_ATTUALE.GE.T2) THEN
          GV = FP00*(PNOM/QBASE)*VV**(KPV-2.)
        ELSE IF (TEMPO_ATTUALE.GE.T1) THEN
          GV = FP00*((P2/QBASE)+((PNOM/QBASE)-(P2/QBASE))
     $            *(TEMPO_ATTUALE-T1)/(T2-T1))*VV**(KPV-2.)
        ELSE
          GV = FP00*(P100-(P100-(P2/QBASE))
     $            *TEMPO_ATTUALE/T1)*VV**(KPV-2.)
        ENDIF
C
C
        IF (TEMPO_ATTUALE.GE.T3) THEN
          BV = -FQ00*(QNOM/QBASE)*VV**(KQV-2.)
        ELSE
          BV = -FQ00*(Q100-(Q100-(QNOM/QBASE))* 
     $            (1-EXP(-TEMPO_ATTUALE/(T3/3)))/ 
     $            (1-EXP(-3.)))*VV**(KQV-2.) 
        ENDIF
C
      ENDIF
C--
C----- Calcolo Residui
C--
C
      IF (STATO) THEN
          RNI(1) = -IR00-VR00*GV+VX00*BV
          RNI(2) = -IX00-VX00*GV-VR00*BV
          RNI(3) = -VR00*IR00-VX00*IX00
          RNI(4) = -VX00*IR00+VR00*IX00
          RNI(5) = SQRT(IR00*IR00+IX00*IX00)
          RNI(6) = SQRT(VR00*VR00+VX00*VX00)
C
c- cambiato 22 gen 99
          QAPP =SQRT(abs(QATT*QATT+QREA*QREA)) 
c-
C
          IF (QAPP.GT.0.001) THEN
          FDP0 = ABS(QATT)/QAPP
          ELSE
          FDP0 = 0.
          END IF
          RNI(7) = FDP0
      ELSE
        RNI(1) = IR00
        RNI(2) = IX00
	  RNI(3) = 0.
	  RNI(4) = 0.
	  RNI(5) = 0.
	  RNI(6) = 0.
	  RNI(7) = 0.
      END IF
C	print*,'fine ZAVO'
C
      RETURN
      ENDIF
C
C	
      END
C
C
C
      SUBROUTINE ZAVOI3 (IFO,IOB,DEBL)
C
      COMMON/ZAVO01/IBLOC
      COMMON/ZAVO02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'ZAVO'/
C
      CALL ZAVOI4(IOB,MOD)
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('IR00',A4,2X,
     $  57H--UA-- CORRENTE REALE DI CARICO                          )
      WRITE(IFO,3002)IOB
 3002 FORMAT('IX00',A4,2X,
     $  57H--UA-- CORRENTE IMMAG. DI CARICO                         )
      WRITE(IFO,3003)IOB
 3003 FORMAT('QATT',A4,2X,
     $  57H--UA-- POTENZA ATTIVA DI CARICO                          )
      WRITE(IFO,3004)IOB
 3004 FORMAT('QREA',A4,2X,
     $  57H--UA-- POTENZA REATTIVA DI CARICO                        )
      WRITE(IFO,3005)IOB
 3005 FORMAT('IM00',A4,2X,
     $  57H--UA-- MODULO CORRENTE DI CARICO                         )
      WRITE(IFO,3006)IOB
 3006 FORMAT('VM00',A4,2X,
     $  57H--UA-- MODULO TENSIONE AI MORSETTI                       )
      WRITE(IFO,3014)IOB
 3014 FORMAT('FDIP',A4,2X,
     $  57H--UA-- FATTORE DI POTENZA                                )
      WRITE(IFO,3007)IOB
 3007 FORMAT('VR00',A4,2X,
     $  57H--IN-- TENSIONE REALE DEL CARICO                         )
      WRITE(IFO,3008)IOB
 3008 FORMAT('VX00',A4,2X,
     $  57H--IN-- TENSIONE IMMAG. DEL CARICO                        )
      WRITE(IFO,3009)IOB
 3009 FORMAT('P100',A4,2X,
     $  57H--IN-- PICCO DI POTENZA ATTIVA                           )
      WRITE(IFO,3010)IOB
 3010 FORMAT('Q100',A4,2X,
     $  57H--IN-- PICCO DI POTENZA REATTIVA                         )
      WRITE(IFO,3011)IOB
 3011 FORMAT('FP00',A4,2X,
     $  57H--IN-- MOLTIPLICATORE DI POTENZA ATTIVA                  )
      WRITE(IFO,3012)IOB
 3012 FORMAT('FQ00',A4,2X,
     $  57H--IN-- MOLTIPLICATORE DI POTENZA REATTIVA                )
      WRITE(IFO,3013)IOB
 3013 FORMAT('SISC',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE CARICO (1=on)                  )
      RETURN
      END
C
C
C 
      SUBROUTINE ZAVOI4 (IOB,MOD)
      COMMON/ZAVO01/IBLOC
      COMMON/ZAVO02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE ZAVOD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---CARICO SEZIONABILE AD AMMETTENZA VARIABILE 
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
