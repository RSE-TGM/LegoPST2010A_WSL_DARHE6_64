C-------------------------------------------------------------------------
C-----                                                               -----
C-----                            MODULO GEN5                        -----
C-----                                                               -----
C-----                  GENERATORE SINCRONO DEL 5 ORDINE             -----
C-----                                                               -----
C-----               Modificato  il 05.06.98        -----
C-----                                                               ----- 
C-------------------------------------------------------------------------
C
      SUBROUTINE GEN5I2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2), IBASE
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C

      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      REAL IR00, IX00, IFLD, IFLD0
C
C
      QBASE=H0*W0       !POTENZA DI BASE
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'TAA_s   '
     $             ,'T1D0_s  '
     $             ,'T2D_s   '
     $             ,'T2Q_s   '
     $             ,'TA_s    '
     $             ,'XD_pum  '
     $             ,'X1D_pum '
     $             ,'X2D_pum '
     $             ,'XQ_pum  ' 
      WRITE(14,500) 'X2Q_pum '
     $             ,'RF_Ohm  '
     $             ,'FNOM_Hz '
     $             ,'QNOM_VA ' 
     $             ,'VNOM_V  '
     $             ,'VBECC_V '
     $             ,'RIGIDO  '
     $             ,'PU? 1=SI'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) TAA
     $            ,T1D0
     $            ,T2D
     $            ,T2Q
     $            ,TA
     $            ,XD
     $            ,X1D
     $            ,X2D
     $            ,XQ
      READ(14,501) X2Q
     $            ,RF
     $            ,FNOM
     $            ,QNOM
     $            ,VNOM
     $            ,VBEC
     $            ,RIGIDO
     $            ,PU
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = TAA
      DATI(ID2+ 1) = T1D0
      DATI(ID2+ 2) = T2D
      DATI(ID2+ 3) = T2Q
      DATI(ID2+ 4) = TA
      DATI(ID2+ 5) = XD
      DATI(ID2+ 6) = X1D
      DATI(ID2+ 7) = X2D
      DATI(ID2+ 8) = XQ
      DATI(ID2+ 9) = X2Q
      DATI(ID2+10) = RF
      DATI(ID2+11) = FNOM
      DATI(ID2+12) = QNOM
      DATI(ID2+13) = VNOM
      DATI(ID2+14) = VBEC
      DATI(ID2+15) = RIGIDO
      DATI(ID2+16) = PU
      ID2 = ID2+17 !riservo lo spazio per DE00(t-1)
C
C---NORMALIZZAZIONE DELLE VARIABILI---
C
C---CORRENTE DI BASE PER LE CORRENTI DI REALE ED IMMAGINARIA---
C
      IBASE=QBASE/(SQRT(3.)*VNOM)
C
C---CORRENTE DI BASE PER LA CORRENTE DI ECCITAZIONE---
C
      IFLD0=VBEC/RF
C 
C
      IF (PU.EQ.1.) THEN
       DO I=1,23
        CNXYU(IV1+I-1)=1.
       ENDDO
      ELSE
       CNXYU(IV1   ) = 2*3.1416*FNOM
       CNXYU(IV1+ 1) = VNOM/(SQRT(3.))
       CNXYU(IV1+ 2) = VNOM/(SQRT(3.))
       CNXYU(IV1+ 3) = VNOM/(SQRT(3.))
       CNXYU(IV1+ 4) = 1.
       CNXYU(IV1+ 5) = VNOM
       CNXYU(IV1+ 6) = 1.
       CNXYU(IV1+ 7) = QBASE
       CNXYU(IV1+ 8) = QBASE
       CNXYU(IV1+ 9) = IBASE
       CNXYU(IV1+10) = IBASE
       CNXYU(IV1+11) = FNOM
       CNXYU(IV1+12) = IFLD0
       CNXYU(IV1+13) = 2*3.1416*FNOM
       CNXYU(IV1+14) = 1.
       CNXYU(IV1+15) = VNOM
       CNXYU(IV1+16) = VNOM
       CNXYU(IV1+17) = VBEC
       CNXYU(IV1+18) = QBASE
       CNXYU(IV1+19) = 1.
       CNXYU(IV1+20) = 1.
       CNXYU(IV1+21) = 1.
       CNXYU(IV1+22) = 2*3.1416*FNOM
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE GEN5C1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL GEN5
C
      REAL IR00, IX00, IFLD
C
C---GENERATORE SINCRONO
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL GEN5JC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL GEN5 (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 CONTINUE
      CALL GEN5JC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE GEN5JC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL GEN5
C
      REAL IR00, IX00, IFLD
C
      GOTO (1,2,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C  
C    
        NEQ =13
        NVAR=23
        DO I=1,NEQ
         DO J=1,NVAR
          AJAC(I,J)=1.
         ENDDO
        ENDDO
C
      RETURN
C
C     calcolo jacobiano analitico
C
    2 CONTINUE
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      NSTATI = 4
      NUSCIT = 9
      NINGRE = 10
      EPS    = 1.E-3
      EPSLIM = 1.E-4
C
      CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $           NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,GEN5)
C 
      RETURN
      END
C
C
C
      SUBROUTINE GEN5 (IFUN,IXYU,XYU,IPD,DATI,RNI)
C
      PARAMETER (PI=3.141592)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
      REAL IR00, IX00, IFLD, ID00, IQ00
C
      INTEGER TRASF
      LOGICAL LINT,LFER,LMRI,LRIG
C
C---decodifica variabili e dati
C
      OMGA   = XYU(IXYU   )
      E1Q0   = XYU(IXYU+ 1)
      E2Q0   = XYU(IXYU+ 2)
      E2D0   = XYU(IXYU+ 3)
      DE00   = XYU(IXYU+ 4)
      VMMA   = XYU(IXYU+ 5)
      FAMA   = XYU(IXYU+ 6)
      QATT   = XYU(IXYU+ 7)
      QREA   = XYU(IXYU+ 8)
      IR00   = XYU(IXYU+ 9)
      IX00   = XYU(IXYU+10)
      FREQ   = XYU(IXYU+11)
      IFLD   = XYU(IXYU+12)
      ORIN   = XYU(IXYU+13)
      DRIN   = XYU(IXYU+14)
      VR00   = XYU(IXYU+15)
      VX00   = XYU(IXYU+16)
      VF00   = XYU(IXYU+17)
      QMEC   = XYU(IXYU+18)
      SINT   = XYU(IXYU+19)
      SFER   = XYU(IXYU+20)
      SMRI   = XYU(IXYU+21)
      OMRI   = XYU(IXYU+22)
C
      IF (SINT.GT.0.5) THEN
         LINT=.TRUE.
      ELSE
         LINT=.FALSE.
      ENDIF
C
      IF (SFER.GT.0.5) THEN
         LFER=.TRUE.
      ELSE
         LFER=.FALSE.
      ENDIF
C
      IF (SMRI.GT.0.5) THEN
         LMRI=.TRUE.
      ELSE
         LMRI=.FALSE.
      ENDIF
C
      TAA    = DATI(IPD   )
      T1D0   = DATI(IPD+ 1)
      T2D    = DATI(IPD+ 2)
      T2Q    = DATI(IPD+ 3)
      TA     = DATI(IPD+ 4)
      XD     = DATI(IPD+ 5)
      X1D    = DATI(IPD+ 6)
      X2D    = DATI(IPD+ 7)
      XQ     = DATI(IPD+ 8)
      X2Q    = DATI(IPD+ 9)
      RF     = DATI(IPD+10)
      FNOM   = DATI(IPD+11)
      QNOM   = DATI(IPD+12)
      VNOM   = DATI(IPD+13)
      VBEC   = DATI(IPD+14)
      RIGIDO = DATI(IPD+15)
      PU     = DATI(IPD+16)
C
      IF (RIGIDO.GT.0.5) THEN
         LRIG=.TRUE.
      ELSE
         LRIG=.FALSE.
      ENDIF
C
      QBASE=H0*W0   !potenza di base
C
C     -----calcolo parametri
C
      T1D  = X1D*T1D0/XD
      T2D0 = X1D*T2D/X2D
      T2Q0 = XQ*T2Q/X2Q
      CAMD = T2D/T1D0*(XD-X1D)
      A1   = 1./T2D0
      A2   = 1./T2D0*(X1D-X2D+CAMD)
      A3   = TAA/(T1D0*T2D0)
      A4   = 1./T1D0
      A5   = 1./T1D0*(XD-X1D-CAMD)
      A6   = 1./T1D0*(1-TAA/T1D0) 
      B1   = 1./T2Q0
      B2   = 1./T2Q0*(XQ-X2Q) 
      CK   = (QNOM/QBASE)
      GAM3 = (QNOM*RF*TAA)/((VBEC*VBEC)*2*PI*FNOM*T1D0*T2D0)
C     VV   = SQRT(VR00**2+VX00**2)
C     Q1   = (XQ*QREA/CK)/VV
C     P1  =  (XQ*QATT/CK)/VV
C     A7   = SQRT((VV+Q1)**2+(QATT/CK)**2)
C
C---calcolo residui
C
      IF (KREGIM) THEN
C
C============ condizioni stazionarie
C
         IF (LINT) THEN !macchina connessa in rete
             IF (LMRI) THEN !macchina di riferimento
                OM=OMRI
                DELASS=DE00
             ELSE
                OM=ORIN
                DELASS=DE00+DRIN
             ENDIF
             DATI(IPD+16)=DE00
             ID00=(VR00*SIN(DELASS)-VX00*COS(DELASS)+E2Q0)/X2D
             IQ00=(VR00*COS(DELASS)+VX00*SIN(DELASS)-E2D0)/X2Q
             RNI(1)  = QMEC-QATT
             RNI(2)  = -E1Q0-(XD-X1D-CAMD)*ID00+(1-TAA/T1D0)*VF00
             RNI(3)  = -E2Q0+E1Q0-(X1D-X2D+CAMD)*ID00+TAA/T1D0*VF00
             RNI(4)  = -E2D0+(XQ-X2Q)*IQ00
             RNI(5)  = OMGA-OM
             RNI(6)  = VMMA-SQRT(VR00**2+VX00**2)
             RNI(7)  = FAMA-ATAN2(VX00,VR00)
             RNI(8)  = QATT-VR00*IR00-VX00*IX00
             RNI(9)  = QREA-VX00*IR00+VR00*IX00
             RNI(10) = IR00-ID00*CK*COS(DELASS)+IQ00*CK*SIN(DELASS)
             RNI(11) = IX00-IQ00*CK*COS(DELASS)-ID00*CK*SIN(DELASS)
             RNI(12) = FREQ-OMGA
             RNI(13) = IFLD-E2Q0-GAM3*ID00
C            RNI(13) = IFLD-A7-((XD/XQ)-1)*(Q1*(VV+Q1)+P1**2)/A7
         ELSE IF (VF00.EQ.0.OR.LFER) THEN  !non connessa ed eccitazione nulla
             DATI(IPD+16)=DE00             !oppure macchina ferma
             RNI(1)  = DE00
             RNI(2)  = E1Q0
             RNI(3)  = E2Q0
             RNI(4)  = E2D0
             RNI(5)  = OMGA
             RNI(6)  = VMMA
             RNI(7)  = FAMA
             RNI(8)  = QATT
             RNI(9)  = QREA
             RNI(10) = IR00
             RNI(11) = IX00
             RNI(12) = FREQ
             RNI(13) = IFLD
         ELSE !non connessa ed eccitazione non nulla
             DATI(IPD+16)=DE00             
             IF (LRIG) THEN !montante rigido
                ID00=(VR00*SIN(DE00)-VX00*COS(DE00)+E2Q0)/X2D
                IQ00=(VR00*COS(DE00)+VX00*SIN(DE00)-E2D0)/X2Q
                RNI(1)  = QMEC-QATT
                RNI(2)  = -E1Q0-(XD-X1D-CAMD)*ID00+(1-TAA/T1D0)*VF00
                RNI(3)  = -E2Q0+E1Q0-(X1D-X2D+CAMD)*ID00+TAA/T1D0*VF00
                RNI(4)  = -E2D0+(XQ-X2Q)*IQ00
                RNI(5)  = OMGA-OMRI
                RNI(6)  = VMMA-SQRT(VR00**2+VX00**2)
                RNI(7)  = FAMA-ATAN2(VX00,VR00)
                RNI(8)  = QATT-VR00*IR00-VX00*IX00
                RNI(9)  = QREA-VX00*IR00+VR00*IX00
                RNI(10) = IR00-ID00*CK*COS(DE00)+IQ00*CK*SIN(DE00)
                RNI(11) = IX00-IQ00*CK*COS(DE00)-ID00*CK*SIN(DE00)
             ELSE !montante flessibile
                RNI(1)  = QMEC
                RNI(2)  = -E1Q0+(1-TAA/T1D0)*VF00
                RNI(3)  = -E2Q0+E1Q0+TAA/T1D0*VF00
                RNI(4)  = -E2D0
                RNI(5)  = OMGA-OMRI
                RNI(6)  = VMMA-ABS(E2Q0)
                RNI(7)  = FAMA-DE00-PI/2.
                RNI(8)  = QATT
                RNI(9)  = QREA
                RNI(10) = IR00
                RNI(11) = IX00
             ENDIF
             RNI(12) = FREQ-OMGA
             RNI(13) = IFLD-E2Q0
C            RNI(13) = IFLD-A7-((XD/XQ)-1)*(Q1*(VV+Q1)+P1**2)/A7
         ENDIF
C
C=================  condizioni transitorie
C
      ELSE !in transitorio
         DE_P   = DATI(IPD+16)
         IF (.NOT.LINT) THEN !macchina non connessa in rete
             IF (LMRI) THEN
                OM=OMGA
             ELSE
                OM=OMRI
             ENDIF
             DELTOM  = (OMGA-OM)*2*PI*FNOM
             DELREL  = DE_P+DELTOM*DTINT
             IF (DELREL.NE.0.) THEN
                 DO WHILE (DELREL.GT.PI/2.) 
                    DELREL=DELREL-2.*PI
                 ENDDO
                 DO WHILE (DELREL.LT.-3./2*PI)
                    DELREL=DELREL+2.*PI
                 ENDDO
             ENDIF
             IF (ITERT.LE.0.AND.IFUN.EQ.2) THEN
                 DATI(IPD+16)=DELREL
             ENDIF
             IF (LFER) THEN
                RNI(1) = 0.
                RNI(2) = 0.
                RNI(3) = 0.
                RNI(4) = 0.
                RNI(5) = DE00-DE_P
             ELSE
                RNI(1)  = 1./(TA*OMGA)*(QMEC/CK-QATT/CK)
                IF (LRIG) THEN !montante rigido
                   ID00=(VR00*SIN(DELREL)-VX00*COS(DELREL)+E2Q0)/X2D
                   IQ00=(VR00*COS(DELREL)+VX00*SIN(DELREL)-E2D0)/X2Q
                   RNI(2)  = -A4*E1Q0-A5*ID00+A6*VF00
                   RNI(3)  = -A1*E2Q0+A1*E1Q0-A2*ID00+A3*VF00
                   RNI(4)  = -B1*E2D0+B2*IQ00
                ELSE !montante flessibile
                   RNI(2)  = -A4*E1Q0+A6*VF00
                   RNI(3)  = -A1*E2Q0+A1*E1Q0+A3*VF00
                   RNI(4)  = -B1*E2D0
                ENDIF
                RNI(5)  = DE00-DELREL
             ENDIF
             IF (LRIG) THEN !montante rigido
                RNI(6)  = VMMA-SQRT(VR00**2+VX00**2)
                RNI(7)  = FAMA-ATAN2(VX00,VR00)
                RNI(8)  = QATT-VR00*IR00-VX00*IX00
                RNI(9)  = QREA-VX00*IR00+VR00*IX00
                RNI(10) = IR00-ID00*CK*COS(DELREL)+IQ00*CK*SIN(DELREL)
                RNI(11) = IX00-IQ00*CK*COS(DELREL)-ID00*CK*SIN(DELREL)
                RNI(12) = FREQ-OMGA
                RNI(13) = IFLD-E2Q0-GAM3*ID00
C               RNI(13) = IFLD-A7-((XD/XQ)-1)*(Q1*(VV+Q1)+P1**2)/A7
             ELSE !montante flessibile
                RNI(6)  = VMMA-ABS(E2Q0)
                RNI(7)  = FAMA-DE00-PI/2.
                RNI(8)  = QATT
                RNI(9)  = QREA
                RNI(10) = IR00
                RNI(11) = IX00
                RNI(12) = FREQ-OMGA
                RNI(13) = IFLD-E2Q0
C               RNI(13) = IFLD-A7-((XD/XQ)-1)*(Q1*(VV+Q1)+P1**2)/A7
             ENDIF
         ELSE !macchina connessa
             IF (LMRI) THEN
                OM=OMGA !macchina di riferimento
             ELSE
                OM=ORIN !macchina riferita
             ENDIF
             DELTOM  = (OMGA-OM)*2*PI*FNOM
             DELREL  = DE_P+DELTOM*DTINT
             IF (DELREL.NE.0.) THEN
                DO WHILE (DELREL.GT.PI/2.)
                   DELREL=DELREL-2.*PI
                ENDDO
                DO WHILE (DELREL.LT.-3./2*PI)
                   DELREL=DELREL+2.*PI
                ENDDO
             ENDIF
             IF (ITERT.LE.0.AND.IFUN.EQ.2) THEN
                 DATI(IPD+16)=DELREL
             ENDIF
             IF (LMRI) THEN
                DELASS=DE00
             ELSE
                DELASS=DE00+DRIN
             ENDIF             
             ID00=(VR00*SIN(DELASS)-VX00*COS(DELASS)+E2Q0)/X2D
             IQ00=(VR00*COS(DELASS)+VX00*SIN(DELASS)-E2D0)/X2Q
             RNI(1)  = 1./(TA*OMGA)*(QMEC/CK-QATT/CK)
             RNI(2)  = -A4*E1Q0-A5*ID00+A6*VF00
             RNI(3)  = -A1*E2Q0+A1*E1Q0-A2*ID00+A3*VF00
             RNI(4)  = -B1*E2D0+B2*IQ00
             RNI(5)  = DE00-DELREL
             RNI(6)  = VMMA-SQRT(VR00**2+VX00**2)
             RNI(7)  = FAMA-ATAN2(VX00,VR00)
             RNI(8)  = QATT-VR00*IR00-VX00*IX00
             RNI(9)  = QREA-VX00*IR00+VR00*IX00
             RNI(10) = IR00-ID00*CK*COS(DELASS)+IQ00*CK*SIN(DELASS)
             RNI(11) = IX00-IQ00*CK*COS(DELASS)-ID00*CK*SIN(DELASS)
             RNI(12) = FREQ-OMGA
             RNI(13) = IFLD-E2Q0-GAM3*ID00
C            RNI(13) = IFLD-A7-((XD/XQ)-1)*(Q1*(VV+Q1)+P1**2)/A7
         ENDIF
      ENDIF
      RETURN
      END
C
C
C
      SUBROUTINE GEN5I3 (IFO,IOB,DEBL)
C
      COMMON/GEN501/IBLOC
      COMMON/GEN502/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'GEN5'/
C
      CALL GEN5I4(IOB,MOD)
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3002)IOB
 3002 FORMAT('OMGA',A4,2X,
     $  57H--US-- VELOCITA' ANGOLARE                                )
      WRITE(IFO,3004)IOB
 3004 FORMAT('E1Q0',A4,2X,
     $  57H--US-- TENSIONE TRANSITORIA ASSE Q                       )
      WRITE(IFO,3003)IOB
 3003 FORMAT('E2Q0',A4,2X,
     $  57H--US-- TENSIONE SUBTRANSITORIA ASSE Q                    )
      WRITE(IFO,3005)IOB
 3005 FORMAT('E2D0',A4,2X,
     $  57H--US-- TENSIONE SUBTRANSITORIA ASSE D                    )
      WRITE(IFO,3001)IOB
 3001 FORMAT('DE00',A4,2X,
     $  57H--UA-- ANGOLO DELL'ASSE D DEL ROTORE RIFERITO (RAD)      )
      WRITE(IFO,3006)IOB
 3006 FORMAT('UMMA',A4,2X,
     $  57H--UA-- MODULO TENSIONE MORSETTI MACCHINA [V]             )
      WRITE(IFO,3007)IOB
 3007 FORMAT('FAMA',A4,2X,
     $  57H--UA-- FASE TENSIONE MORSETTI MACCHINA [rad]             )
      WRITE(IFO,3008)IOB
 3008 FORMAT('QATT',A4,2X,
     $  57H--UA-- POTENZA ELETTRICA ATTIVA [W]                      )
      WRITE(IFO,3009)IOB
 3009 FORMAT('QREA',A4,2X,
     $  57H--UA-- POTENZA ELETTRICA REATTIVA [VAR]                  )
      WRITE(IFO,3010)IOB
 3010 FORMAT('IR00',A4,2X,
     $  57H--UA-- CORRENTE ATTIVA EROGATA                           )
      WRITE(IFO,3011)IOB
 3011 FORMAT('IX00',A4,2X,
     $  57H--UA-- CORRENTE REATTIVA EROGATA                         )
      WRITE(IFO,3013)IOB
 3013 FORMAT('FREQ',A4,2X,
     $  57H--UA-- FREQUENZA [Hz]                                    )
       WRITE(IFO,3030)IOB
 3030 FORMAT('IFLD',A4,2X,
     $  57H--UA-- CORRENTE DI ECCITAZIONE                           )
      WRITE(IFO,3014)IOB
 3014 FORMAT('ORIN',A4,2X,
     $  57H--IN-- VELOCITA ANGOLARE DEL SISTEMA DI RIFERIMENTO      )
      WRITE(IFO,3012)IOB
 3012 FORMAT('DRIN',A4,2X,
     $  57H--IN-- ANGOLO DEL ROTORE DEL SISTEMA DI RIFERIMENTO      )
      WRITE(IFO,3015)IOB
 3015 FORMAT('UR00',A4,2X,
     $  57H--IN-- TENSIONE ATTIVA AI MORSETTI DI RETE               )
      WRITE(IFO,3016)IOB
 3016 FORMAT('UX00',A4,2X,
     $  57H--IN-- TENSIONE REATTIVA AI MORSETTI DI RETE             )
      WRITE(IFO,3017)IOB
 3017 FORMAT('UF00',A4,2X,
     $  57H--IN-- TENSIONE DI ECCITAZIONE                           )
      WRITE(IFO,3018)IOB
 3018 FORMAT('QMEC',A4,2X,
     $  57H--IN-- POTENZA MECCANICA                                 )
      WRITE(IFO,3019)IOB
 3019 FORMAT('SINT',A4,2X,
     $  57H--IN-- VARIABILE LOGICA MACCHINA CONNESSA IN RETE        )      
      WRITE(IFO,3020)IOB
 3020 FORMAT('SFER',A4,2X,
     $  57H--IN-- VARIABILE LOGICA MACCHINA ARRESTATA               )
      WRITE(IFO,3021)IOB
 3021 FORMAT('SMRI',A4,2X,
     $  57H--IN-- VARIABILE LOGICA MACCHINA AUTORIFERITA            )
      WRITE(IFO,3022)IOB
 3022 FORMAT('OMRI',A4,2X,
     $  57H--IN-- VELOCITA ANGOLARE PER MACCHINA AUTORIFERITA       )
      RETURN
      END
C
C
C
      SUBROUTINE GEN5I4 (IOB,MOD)
      COMMON/GEN501/IBLOC
      COMMON/GEN502/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE GEN5D1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      RETURN
      END
