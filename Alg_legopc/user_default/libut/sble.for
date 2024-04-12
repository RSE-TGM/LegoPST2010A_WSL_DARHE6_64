C***************************************************************************
C
C     Nodulo sbarra elettrica
C     Modificato:  06.04.98
C
C***************************************************************************
C
      SUBROUTINE SBLEI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
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
      REAL I1RE, I1IM, I2RE, I2IM, ICRE                                 !SNGL
      REAL ICIM                                                         !SNGL
C      DOUBLE PRECISION I1RE, I1IM, I2RE, I2IM, ICRE                     !DBLE
C      DOUBLE PRECISION ICIM                                             !DBLE
C
      QBASE=H0*W0                    !POTENZA DI BASE
C
C---MODULO SBARRA PER INTERCONNESSIONE MODULI LINE CON OPZIONE IN PU
C
      GO TO(100,200), IFUN
C
  100 WRITE(14,500) 'VNOM_V'
     $             ,'PU?_1=Y'
      RETURN
C
C---lettura e memorizzazione dati
C
  200 READ(14,501)
      READ(14,501) VNOM
     $            ,PU
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
      DATI(ID2   ) = VNOM
      DATI(ID2+ 1) = PU
      ID2=ID2+1
C
C---costanti di normalizzazione
C
      IBASE=QBASE/(SQRT(3.)*VNOM)
C
      IF (PU.EQ.1.) THEN
        DO I=1,9
         CNXYU(IV1+I-1)=1.
        ENDDO
      ELSE
       CNXYU(IV1  ) = VNOM
       CNXYU(IV1+1) = VNOM
       CNXYU(IV1+2) = IBASE
       CNXYU(IV1+3) = IBASE
       CNXYU(IV1+4) = IBASE
       CNXYU(IV1+5) = IBASE
       CNXYU(IV1+6) = IBASE
       CNXYU(IV1+7) = IBASE
       CNXYU(IV1+8) = 1.
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE SBLEC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL SBLE
C
      REAL I1RE, I1IM, I2RE, I2IM, ICRE                                 !SNGL
      REAL ICIM                                                         !SNGL
C      DOUBLE PRECISION I1RE, I1IM, I2RE, I2IM, ICRE                     !DBLE
C      DOUBLE PRECISION ICIM                                             !DBLE
C
C---Modulo sbarra per linee
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL SBLEJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL SBLE (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 CONTINUE
      CALL SBLEJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE SBLEJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
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
      EXTERNAL SBLE
C
      REAL I1RE, I1IM, I2RE, I2IM, ICRE                                 !SNGL
      REAL ICIM                                                         !SNGL
C      DOUBLE PRECISION I1RE, I1IM, I2RE, I2IM, ICRE                     !DBLE
C      DOUBLE PRECISION ICIM                                             !DBLE
C
      GOTO (1,3,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
      DO I=1,2
       DO J=1,9
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
      NUSCIT = 2
      NINGRE = 7
      EPS    = 1.E-3
      EPSLIM = 1.E-4
      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,SBLE)
      RETURN
      END
C
C
C
      SUBROUTINE SBLE (IFUN,IXYU,XYU,IPD,DATI,RNI)
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
C
      LOGICAL LISO
      REAL I1RE, I1IM, I2RE, I2IM, ICRE                                 !SNGL
      REAL ICIM                                                         !SNGL
C      DOUBLE PRECISION I1RE, I1IM, I2RE, I2IM, ICRE                     !DBLE
C      DOUBLE PRECISION ICIM                                             !DBLE
C
C---Modulo sbarra per linee
C   calcolo residui
C
C---decodifica variabili e dati
C
      V1RE = XYU(IXYU  )
      V1IM = XYU(IXYU+1)
      I1RE = XYU(IXYU+2)
      I1IM = XYU(IXYU+3)
      I2RE = XYU(IXYU+4)
      I2IM = XYU(IXYU+5)
      ICRE = XYU(IXYU+6)
      ICIM = XYU(IXYU+7)
      SBIS = XYU(IXYU+8)
C
      IF (SBIS.LT.0.5) THEN
         LISO=.FALSE.
      ELSE
         LISO=.TRUE.
      ENDIF
C
      VNOM   = DATI(IPD   )
      PU     = DATI(IPD+ 1)
C
C---calcolo residui
C
      IF (LISO) THEN
         RNI(1) = V1RE
         RNI(2) = V1IM
      ELSE
         RNI(1) = I1RE+I2RE+ICRE 
         RNI(2) = I1IM+I2IM+ICIM
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE SBLEI3 (IFO,IOB,DEBL)
C
      COMMON/SBLE01/IBLOC
      COMMON/SBLE02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'SBLE'/
C
      CALL SBLEI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 2
      NINGRE = 6
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('V1RE',A4,2X,
     $  57H--UA-- Tensione reale di sbarra                          )
      WRITE(IFO,3002)IOB
 3002 FORMAT('V1IM',A4,2X,
     $  57H--UA-- Tensione immaginaria di sbarra                    )
      WRITE(IFO,3003)IOB
 3003 FORMAT('I1RE',A4,2X,
     $  57H--IN-- Corrente reale linea 1                            )
      WRITE(IFO,3004)IOB
 3004 FORMAT('I1IM',A4,2X,
     $  57H--IN-- Corrente immaginaria linea 1                      )
      WRITE(IFO,3005)IOB
 3005 FORMAT('I2RE',A4,2X,
     $  57H--IN-- Corrente reale linea 2                            )
      WRITE(IFO,3006)IOB
 3006 FORMAT('I2IM',A4,2X,
     $  57H--IN-- Corrente immaginaria linea 2                      )
      WRITE(IFO,3007)IOB
 3007 FORMAT('ICRE',A4,2X,
     $  57H--IN-- Corrente reale carico                             )
      WRITE(IFO,3008)IOB
 3008 FORMAT('ICIM',A4,2X,
     $  57H--IN-- Corrente immaginaria carico                       )
      WRITE(IFO,3009)IOB
 3009 FORMAT('SBIS',A4,2X,
     $  57H--IN-- Logica di sbarra isolata                          )
C
      RETURN
      END
C
C
C
      SUBROUTINE SBLEI4 (IOB,MOD)
      COMMON/SBLE01/IBLOC
      COMMON/SBLE02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
      SUBROUTINE SBLED1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C$*$
      RETURN
      END
