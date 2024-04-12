C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETEI1(IFUN,K,IBL1,IBL2,NSTATI,NUSCIT,NINGRE)
C
C---SENSORE DI TEMPERATURA
C
       GO TO(100,200), IFUN
C
  100  WRITE(6,500)'SENSORE DI TEMPERATURA'
       NSTATI = 0
       NUSCIT = 1
       NINGRE = 3
       RETURN
C
  200  CONTINUE
       IF(K.EQ.1)              WRITE(6,501)'VARIABILI DI STATO'
       IF(K.EQ.NSTATI+1)       WRITE(6,501)'VARIABILI DI USCITA'
       IF(K.EQ.NSTATI+NUSCIT+1)WRITE(6,501)'VARIABILI DI INGRESSO'
C
       GO TO(1,2,3,4),K
C stati
C uscite
  1    WRITE(6,502)'TEMPERATURA DI USCITA'
       GO TO 400
C ingressi
  2    WRITE(6,502)'PRESSIONE DI INGRESSO'
       GO TO 400
  3    WRITE(6,502)'ENTALPIA DI INGRESSO'
       GO TO 400
  4    WRITE(6,502)'RAPPORTO PRESS. VAP/PRESS. TOT.'
       GO TO 400
C
  400  RETURN
C
500    FORMAT(//10X,A//)
501    FORMAT(//20X,A//)
502    FORMAT(14X,A)
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETEI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     1                 IBL1,IBL2,IER,CNXYU,TOL)
C
       DIMENSION VAR(MX1,1),XYU(1),DATI(1),CNXYU(1),TOL(1)
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
C
       COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
       REAL  TEMP,PRES,HENT
                           
C
C---SENSORE DI TEMPERATURA
C
       GO TO(100,200), IFUN
C
  100  RETURN
C
C---lettura e memorizzazione dati
C
  200  READ(14,501)
C
  500  FORMAT(3(4X,A8,' =',10X,'*'))
  501  FORMAT(3(14X,F10.0,1X))
C
C
C---costanti di normalizzazione
C
       CNXYU(IV1  ) = T0
       CNXYU(IV1+1) = P0
       CNXYU(IV1+2) = H0
       CNXYU(IV1+3) = 1.
C
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETEC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
       DIMENSION AJAC(MX5,1),XYU(1),DATI(1),RNI(1)
C
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
       COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
       COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
       EXTERNAL SETE
       EXTERNAL NAJAC
       EXTERNAL SETEJAC
C
       REAL  TEMP,PRES,HENT
C
C---SENSORE DI TEMPERATURA
C
       GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100  CONTINUE
       CALL SETEJAC(1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
       RETURN
C
C---calcolo residui
C
  200  CALL SETE(IFUN,IXYU,XYU,IPD,DATI,RNI)
       RETURN
C
C---calcolo jacobiano
C
C      jacobiano analitico CALL SETEJAC(2,...
C
C      jacobiano numerico  CALL SETEJAC(3,...
C
C$*$
  300  CONTINUE
       CALL SETEJAC(3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
 
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETEJAC(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
       DIMENSION AJAC(MX5,1),XYU(1),DATI(1),RNI(1)
C
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
       COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
       COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
       EXTERNAL SETE
C
       REAL  TEMP,PRES,HENT
                           
C
       GOTO(1,2,3),IFUN
C
C---topologia jacobiano
C
  1    CONTINUE
C
C   equazione n.1 (algebrica):
C    dipendenza da   TEMP
C
       AJAC(1,1)=1.
C
C    dipendenza da   PRES
C
       AJAC(1,2)=1.
C
C    dipendenza da   HENT
C
       AJAC(1,3)=1.
C
C
       AJAC(1,4)=1.
C
C
       RETURN
C
C      calcolo jacobiano analitico
C
  2    CONTINUE
       TEMP = XYU(IXYU   )
       PRES = XYU(IXYU+1 )
       HENT = XYU(IXYU+2 )
       RPVP = XYU(IXYU+3 )
C
C
C$*$
C
C--derivata del residuo n.1 (equazione algebrica)   *******
C
C      rispetto alla variabile TEMP
C      AJAC(1,1) =
C
C      rispetto alla variabile PRES
C      AJAC(1,2) =
C
C      rispetto alla variabile HENT
C      AJAC(1,3) =
                  
       RETURN
C
C---calcolo jacobiano numerico
C
  3    CONTINUE
C
       NSTATI = 0
       NUSCIT = 1
       NINGRE = 3
       EPS    = 1.E-3
       EPSLIM = 1.E-4
       CALL NAJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     1            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,SETE)
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETE(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
       DIMENSION XYU(1),DATI(1),RNI(1)
C
C
       LOGICAL KREGIM
       COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
       COMMON/REGIME/KREGIM
       COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT
       COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
       REAL  TEMP,PRES,HENT
C
C---SENSORE DI TEMPERATURA
C   calcolo residui
C
C---decodifica variabili e dati
C
       TEMP     = XYU(IXYU   )
       PRES     = XYU(IXYU+1 )
       HENT     = XYU(IXYU+2 )
       RPVP       = XYU(IXYU+3 )
C
C$*$
C---calcolo della entropia
C
       IK=1
       PRVA=PRES*RPVP*P0
       SENT=SHEV(PRVA,HENT*H0,1)
C
C---calcolo della temperatura
C
       TEM=TEV(PRVA,SENT,1)
C
C---calcolo residui
C
C
C--residuo n.1 (equazione algebrica)   *******
C
       RNI(1) = (TEM-273.15*IK)/T0-TEMP
C
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETEI3(IFO,IOB,DEBL)
C
       COMMON/SETE00/IBLOC,NCEL,NPAR
       CHARACTER*80 DEBL
       CHARACTER*8 IBLOC
       CHARACTER*4 IOB
       CHARACTER*4 MOD
       DATA MOD/'SETE'/
C
       CALL SETEI4(IOB,MOD)
       NSTATI = 0
       NUSCIT = 1
       NINGRE = 3
       WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999  FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
       WRITE(IFO,3001)IOB
 3001  FORMAT('TEMP',A4,2X,
     &57H--UA--     TEMPERATURA DI USCITA                          )
       WRITE(IFO,3002)IOB
 3002  FORMAT('PRES',A4,2X,
     &57H--IN--     PRESSIONE DI INGRESSO                          )
       WRITE(IFO,3003)IOB
 3003  FORMAT('HENT',A4,2X,
     &57H--IN--     ENTALPIA DI INGRESSO                           )
       WRITE(IFO,3004)IOB
 3004  FORMAT('RPVP',A4,2X,
     &57H--IN--     RAPPORTO PRESS. VAP./PRESS. TOT.               )
       RETURN
       END
C*********************************************************************
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*                                                                   *
C*********************************************************************
       SUBROUTINE SETEI4(IOB,MOD)
       COMMON/SETE00/IBLOC,NCEL,NPAR
       CHARACTER*8 IBLOC
       CHARACTER*4 IOB
       CHARACTER*4 MOD
C
C
       WRITE(IBLOC,1000)MOD,IOB
 1000  FORMAT(2A4)
                  
                  
       RETURN
       END
          
