C*********************************************************************
C                                                                    *
C                             MODULO MOTO                            *
C    CON L'OPZIONE DI POTER USARE IL MODULO IN UN MODELLO IN PU      *
C                                                                    *
C*********************************************************************
C
      SUBROUTINE MOTOI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     $                    IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      REAL VAR(MX1,2)
      REAL IFE,I1,I0,ICC
      REAL IBASE, AUS, INM
      CHARACTER*5 ABC
      CHARACTER*7 UNITA
      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
C
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      QBASE=H0*W0                  !POTENZA DI BASE
C
C-------DECODIFICA DEL MOTORE
C
      IF (NSTATI.GT.2)THEN
      MECC=1
      ELSE
      MECC=0
      END IF  
C
      GO TO(100,200), IFUN
C
C
C--- Richiesta dati
C
  100 WRITE(14,500) 'S. DATI '
     $             ,'N_poli  '
     $             ,'QNOM_W  '
     $             ,'FNOM_Hz '
     $             ,'VNOM_V  '
     $             ,'VBASE_V '
     $             ,'INOM_A  '
     $             ,'SCORN_% '
     $             ,'PU? 1=SI'    ! USO DEL MODULO IN PU 
      IF(MECC.EQ.1)THEN
      WRITE(14,500) 'TA_SEC  '    ! COSTANTE DI TEMPO DELL`EQUAZIONE MECCANICA
     $             ,'COEFF   '    ! COEFFICIENTE CHE TIENE CONTO DEL ATTRITO  
                                  ! COEFF=Cattrito/CNOM
      END IF
      WRITE(14,499)
 499  FORMAT('*   Dati del mot. asin. ricavati da prove - S. DATI=1')  
      WRITE(14,500) 'I0_A    '
     $             ,'COSFI0  '
     $             ,'ICC_A_VN'
     $             ,'COSFICC '  
     $             ,'QPERD_w '
     $             ,'QPFER_w '
     $             ,'RS_ohm  '
     $             ,'XDS/XDR '
      WRITE(14,498) 
 498  FORMAT('*   Dati del mot. asin. forniti direttamente - S. DATI=2')
      WRITE(14,500) 'XM_ohm  '  
     $             ,'XDS_ohm '  
     $             ,'XDR_ohm '  
     $             ,'RS_ohm  '
     $             ,'RRSN_ohm'  
     $             ,'RRS1_ohm'  
     $             ,'QPFER_w '
      WRITE(14,497) 
 497  FORMAT('*   Dati del mot. asin. forniti in p.u.m. - S. DATI=3')
      WRITE(14,500) 'XM_pum  '  
     $             ,'XDS_pum '  
     $             ,'XDR_pum '  
     $             ,'RS_pum  '
     $             ,'RRSN_pum'  
     $             ,'RR10_pum'
     $             ,'QPFER_W '  
      RETURN
C
C---lettura dati
C
  200 READ(14,501)
      READ(14,501)  SDATI
     $             ,POLI
     $             ,QNOM
     $             ,FNOM
     $             ,VNOM
     $             ,VBASE
     $             ,INM
     $             ,SCORN
     $             ,PU
      IF(MECC.EQ.1) THEN
        READ(14,501) TA,COEFF
      ENDIF
      ISDATI=SDATI
      IF (ISDATI.LT.1.OR.ISDATI.GT.3) THEN
        IER=1
        WRITE(6,3000)IBL1,IBL2,SDATI
 3000   FORMAT(//10X,'NEL BLOCCO ',2A4,' IL DATO S.DATI DEVE ESSERE '
     $  ,'COMPRESO FRA 1. E 3.'/10X,' INVECE E` ',F10.3/,'->S.DATI=2.')
        SDATI=2.
      ENDIF
      IF (ISDATI.EQ.1) THEN
      READ(14,501)    ! LETTURA DATI RICAVATI DA PROVE S.DATI=1
      READ(14,501) I0
     $             ,COSFI0
     $             ,ICC
     $             ,COSFICC
     $             ,QPERD
     $             ,QPFER
     $             ,RS
     $             ,RXDSXDR
       DO I=1,8
       READ(14,501)
       END DO
      ELSE IF (ISDATI.EQ.2) THEN
       DO I=1,5
       READ(14,501)    ! LETTURA DATI FORNITI DIRETTAMENTE S.DATI=2
       ENDDO
      READ(14,501)  XM
     $             ,XDS
     $             ,XDR
     $             ,RS
     $             ,RRSN
     $             ,RRS1
     $             ,QPFER
       DO I=1,4
       READ(14,501)
       END DO
      ELSE 
       DO I=1,9
       READ(14,501)     ! LETTURA DATI IN P.U.M. S.DATI=3
       ENDDO
      READ(14,501)  XM_PU
     $             ,XDS_PU
     $             ,XDR_PU
     $             ,RS_PU
     $             ,RRSN_PU
     $             ,RRS1_PU
     $             ,QPFER
      ENDIF 
C
  500 FORMAT(3(4X,A8,' =',10X,'*'))
  501 FORMAT(3(14X,F10.0,1X))
C
C--- normalizzazione DELLE IMPEDENZE
C
      ZNOM=(VNOM**2.)/QNOM
C
C--- Controllo assenza valori nulli dei dati in comune,
C    in caso di valore nullo verrano stabiliti valori in base 
C    alla potenza del motore
C
       UNITA='[rad/s]'
       IF (EPSI.EQ.0.) THEN
       EPSI=.01
       END IF
       ABC='EPSI'
       WRITE(6,1002)ABC
       WRITE(6,1003)ABC,EPSI,UNITA
C      END IF
C
       UNITA='[watt]'
       IF (QPFER.EQ.0.) THEN
         IF (QNOM.LT.250.E3) THEN
            QPFER=.01*QNOM
         ELSE
            QPFER=.015*QNOM
         END IF
         ABC='QPFER'
         WRITE(6,1002)ABC
         WRITE(6,1003)ABC,QPFER,UNITA
       END IF
C
       IF(ISDATI.EQ.1)THEN
       UNITA='       '
       IF (RXDSXDR.EQ.0.) THEN
         RXDSXDR=1.
         ABC='XR/XS'
         WRITE(6,1002)ABC
         WRITE(6,1003)ABC,RXDSXDR,UNITA
       END IF
       END IF
C
C
 1002  FORMAT(/,10X,'Il dato ',A5,' e" stato fissato a priori')
 1003  FORMAT(10X,A5,' = ',F12.5,A7)
C
C--- Acquisizione dati in funzione della scelta effettuata
C
       IF (ISDATI.EQ.1) THEN  ! Acquisizione dati con S. DATI=1
C
C--- Calcolo parametri elettrici dalle misure sul motore
C
       IF ((I0.EQ.0.).OR.(COSFI0.EQ.0.).OR.(ICC.EQ.0.).OR.
     $   (COSFICC.EQ.0.).OR.(QPFER.EQ.0.).OR.(QPERD.EQ.0.))THEN
C
       WRITE(6,1020)
 1020  FORMAT(/,10X,'DATI NON SUFFICIENTI PER IL CALCOLO DEI PARAMETRI'
     $  ,/,10X,'TUTTI I DATI VENGONO ASSEGNATI A PRIORI')
C
       GOTO 4001
C
       END IF
C
C
       QP0  = SQRT(3.)*VNOM*I0*COSFI0
       QQ0  = QP0*TAN(ACOS(COSFI0))
       QPCC = SQRT(3.)*VNOM*ICC*COSFICC
       QQCC = QPCC*TAN(ACOS(COSFICC))
C
       XDS = 0.1*ZNOM                !FISSO UN PRIMO VALORE PER XDS (=0.1 pum) 
       XDR = 0.1*ZNOM/RXDSXDR        !FISSO UN PRIMO VALORE PER XDR 
       XM  = 3.0*ZNOM                !FISSO UN PRIMO VALORE PER XM  (=3.0 pum)
       DXM = 1.
       DXDS= 1.
C
       DO WHILE (DXM.GT.0.001.AND.DXDS.GT.0.001) 
C
       XM1 = XM
       XDS1= XDS
C
       XM  = (VNOM**2)/(QQ0-3*(I0**2)*XDS1)*(1/(1+XDS1/XM1)**2)
C
       XDS = (QQCC/(3*(ICC**2)*(1+XDS1/XDR+XDS1/XM)))*(XDS1/XDR+XDS1/XM)
C
       XDR = XDS/RXDSXDR             !RXDSXDR=XDS/XDR
       DXM = ABS(XM-XM1)
       DXDS= ABS(XDS-XDS1)
C
       ENDDO
C
       IF(RS.EQ.0)THEN                  !CALCOLO DELLA RS SOLO SE NON ASSEGNATA
       RS  = (QP0-QPERD-QPFER)/(3*I0**2)
       ABC='RS'
       WRITE(6,1000)ABC
       WRITE(6,1001)ABC,RS
       END IF
C
       GFE = (QPFER/(VNOM**2))*(1+XDS/XM)**2
C
       RRS1  = (QPCC/(3*ICC**2)-RS)*((1+XDR/XM)**2)-
     $     ((XDR/XDS)**2)*((XDS**2)*GFE)

C        IF (RXDSXDR.NE.1)THEN
C	IF(QNOM.GT.1000.E3)THEN
C	 RRSN=RRS1/3
C	ELSE
C	 RRSN=RRS1/2
C	END IF
C       ELSE
         RRSN = RRS1
C        END IF
C
        ABC    = 'RRS1'
        WRITE(6,1000)ABC
        WRITE(6,1001)ABC,RRS1
        ABC    = 'RRSN'
        WRITE(6,1000)ABC
        WRITE(6,1001)ABC,RRSN
        ABC    = 'XDS'
        WRITE(6,1000)ABC
        WRITE(6,1001)ABC,XDS
        ABC    = 'XDR'
        WRITE(6,1000)ABC
        WRITE(6,1001)ABC,XDR
        ABC    = 'XM'
        WRITE(6,1000)ABC
        WRITE(6,1001)ABC,XM
C
C
 1000  FORMAT(/,10X,'Il dato ',A5,' e" calcolato dai valori di targa')
 1001  FORMAT(10X,A5,' = ',F12.5,'  [ohm]')
C
      XM_PU   = XM/ZNOM
      XDS_PU  = XDS/ZNOM
      XDR_PU  = XDR/ZNOM
      RRS1_PU = RRS1/ZNOM
      RRSN_PU = RRSN/ZNOM
      RS_PU   = RS/ZNOM

       ELSE IF (ISDATI.EQ.2) THEN  ! Acquisizione dati con S. DATI=2
C
C     SE UN DATO E` UGUALE A ZERO , ALLORA VENGONO ASSEGNATI A TUTTI I DATI 
C     VALORI USUALI CHE DIPENDONO SOLO DALLA POTENZA NOMINALE
C
       IF ((XM.EQ.0.).OR.(XDS.EQ.0.).OR.(XDR.EQ.0.).OR.
     $    (RRS1.EQ.0.).OR.(RRSN.EQ.0.).OR.(RS.EQ.0.)) THEN
C
 4001  CONTINUE 
           IF (QNOM.LT.250.E3) THEN
           XDS  = .1   *ZNOM
           XDR  = .1   *ZNOM
           RS   = 0.04 *ZNOM
           RRS1 = 0.04 *ZNOM
           RRSN = 0.04*ZNOM 
           XM   = 4.5  *ZNOM
         ELSE
           XDS  = .1   *ZNOM
           XDR  = .1   *ZNOM
           RS   = 0.005*ZNOM
           RRS1 = 0.03 *ZNOM
           RRSN = 0.03 *ZNOM
           XM   = 3.5  *ZNOM
         END IF 
C
C
        ABC='RS'
        WRITE(6,1004)ABC
        WRITE(6,1005)ABC,RS
        ABC    = 'RRS1'
        WRITE(6,1004)ABC
        WRITE(6,1005)ABC,RRS1
        ABC    = 'RRSN'
        WRITE(6,1004)ABC
        WRITE(6,1005)ABC,RRSN
        ABC    = 'XDS'
        WRITE(6,1004)ABC
        WRITE(6,1005)ABC,XDS
        ABC    = 'XDR'
        WRITE(6,1004)ABC
        WRITE(6,1005)ABC,XDR
        ABC    = 'XM'
        WRITE(6,1004)ABC
        WRITE(6,1005)ABC,XM
C
 1004  FORMAT(/,10X,'Il dato ',A5,' E" STATO FISSATO A PRIORI')
 1005  FORMAT(10X,A5,' = ',F10.2,'  [ohm]')
C
      END IF
C
      XM_PU=XM/ZNOM
      XDS_PU=XDS/ZNOM
      XDR_PU=XDR/ZNOM
      RRS1_PU=RRS1/ZNOM
      RRSN_PU=RRSN/ZNOM
      RS_PU=RS/ZNOM
C
       ENDIF
C
C--- Memorizzazione e normalizzazione dati in pum
C
C
      DATI(ID2   ) = XM_PU
      DATI(ID2+ 1) = XDS_PU
      DATI(ID2+ 2) = XDR_PU
      DATI(ID2+ 3) = RRS1_PU
      DATI(ID2+ 4) = RRSN_PU
      DATI(ID2+ 5) = POLI/2
      DATI(ID2+ 6) = QNOM
      DATI(ID2+ 7) = FNOM
      DATI(ID2+ 8) = EPSI
      DATI(ID2+ 9) = VNOM
      DATI(ID2+10) = RS_PU
      DATI(ID2+11) = QPFER/QNOM
      DATI(ID2+12) = INM/(QNOM/(SQRT(3.)*VNOM)) 
      DATI(ID2+13) = SCORN
      DATI(ID2+14) = MECC
      DATI(ID2+15) = VBASE
      IF (MECC.EQ.1)THEN
       DATI(ID2+16) = TA
       DATI(ID2+17) = COEFF
      END IF
      ID2 = ID2+15+2*MECC
C
C
C     NORMALIZZAZIONE DELLE VARIABILI
C
      IBASE=QBASE/(SQRT(3.)*VBASE)
      OMBA=2*3.1416*FNOM
C
C
      IF (PU.EQ.1.) THEN
       DO I =1,22+MECC
       CNXYU(IV1+I-1) = 1.
       ENDDO
       CNXYU(IV1+ 6+MECC) = 100.
        IF (MECC.EQ.1)THEN
         CNXYU(IV1   ) = OMBA
        ELSE 
         CNXYU(IV1+18) = OMBA
        END IF
       CNXYU(IV1+ 10+MECC) = QNOM/QBASE
       CNXYU(IV1+ 11+MECC) = QNOM/QBASE
       CNXYU(IV1+ 13+MECC) = QNOM/QBASE
       CNXYU(IV1+ 14+MECC) = QNOM/QBASE
       CNXYU(IV1+ 15+MECC) = QNOM/QBASE
      ELSE                              
       IF (MECC.EQ.1) CNXYU(IV1) = OMBA     ! USCITE DI STATO
       CNXYU(IV1   +MECC) = 1.              
       CNXYU(IV1+ 1+MECC) = 1.
       CNXYU(IV1+ 2+MECC) = IBASE           ! USCITE ALGEBRICHE
       CNXYU(IV1+ 3+MECC) = IBASE
       CNXYU(IV1+ 4+MECC) = QBASE/OMBA        
       CNXYU(IV1+ 5+MECC) = QBASE           
       CNXYU(IV1+ 6+MECC) = 100.
       CNXYU(IV1+ 7+MECC) = VBASE
       CNXYU(IV1+ 8+MECC) = VBASE
       CNXYU(IV1+ 9+MECC) = 1.
       CNXYU(IV1+10+MECC) = QNOM
       CNXYU(IV1+11+MECC) = QNOM
       CNXYU(IV1+12+MECC) = 100.
       CNXYU(IV1+13+MECC) = QNOM
       CNXYU(IV1+14+MECC) = QNOM
       CNXYU(IV1+15+MECC) = QNOM
       CNXYU(IV1+16+MECC) = VBASE            ! INGRESSI
       CNXYU(IV1+17+MECC) = VBASE
       IF (MECC.EQ.1)THEN
         CNXYU(IV1+19) = QBASE
       ELSE
         CNXYU(IV1+18) = OMBA
       END IF
       CNXYU(IV1+19+MECC) = 1.
       CNXYU(IV1+20+MECC) = 1.
       CNXYU(IV1+21+MECC) = 1. 
      ENDIF
C
      RETURN
      END
C
C
C
      SUBROUTINE MOTOC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/NEQUAZ/NEQMOD
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL MOTO
C
      NEQMOD=7
C
C---Motore asin del 3 ordine 
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL MOTOJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL MOTO (IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
C      jacobiano numerico  CALL MOTOJC (2,...
C
C$*$
  300 CONTINUE
      CALL MOTOJC (2,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
C
C
C
      SUBROUTINE MOTOJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
      LOGICAL KREGIM
      REAL IR00,IXOO,KE00,IMMA,ICC,I0,INM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      EXTERNAL MOTO
C
C---Inizializzazione ad 1. dello Jacobiano
C
       MECC = DATI(IPD+14)
C
       VARIAB = 22+MECC 
       NEQ    = 16+MECC
       IF(.NOT.KREGIM) NEQ=9+MECC
C
      GOTO (1,3), IFUN
C
C---topologia jacobiano
C
    1 CONTINUE
C
       DO I=1,NEQ
          DO J=1,VARIAB
          AJAC(I,J)=1.
          END DO
       END DO
C
      RETURN
C
C---calcolo jacobiano numerico
C
    3 CONTINUE
C
      MECC=DATI(IPD+14)
C
      NSTATI = 2+MECC
      NUSCIT = 14
      NINGRE = 6
      EPS    = 1.E-3
      EPSLIM = 1.E-4
C
C----Definizione del num righe e colonne dello Jacobiano numerico----
C
      NRIG = 9+MECC
      IF (KREGIM) NRIG = 16+MECC
      NCOL = 22+MECC
C
      CALL MOTOJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,
     $             NRIG,NCOL,NSTATI,EPS,EPSLIM,MOTO)
C
      RETURN
      END
C
C----Subroutine NAJAC con aggiornamento non equazioni----
C
      SUBROUTINE MOTOJAC(AJAC,MX5,IXYU,XYU,IPD,DATI,RN,
     1               NRIG,NCOL,NSTATI,EPS,EPSLIM,RESIDUI)
C
C routine generale di calcolo jacobiano numerico
C con incremento EPS in p.u. ( valore minimo assoluto EPSLIM )
C i residui devono essere calcolati dalla routine ( da dich.EXTERNAL )
C SUBROUTINE RESIDUI(IFUN,IXYU,XYU,IPD,DATI,RN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !
C
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RN(*)
      DIMENSION CRN(50),CXYU(100)
      EXTERNAL RESIDUI
C
C     residui(ifun,ixyu,xyu,ipd,dati,rn)
C
      CALL RESIDUI(3,IXYU,XYU,IPD,DATI,RN)
C
      DO 30 J=1,NCOL
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
C
C
      DO 20 I=1,NRIG
      AJAC(I,J)=(CRN(I)-RN(I))/VAR
      IF(I.GT.NSTATI) AJAC(I,J)=-AJAC(I,J)
   20      CONTINUE
C
   30      CONTINUE
C
C
      RETURN
      END
C
C
C
      SUBROUTINE MOTO (IFUN,IXYU,XYU,IPD,DATI,RNI)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
      LOGICAL KREGIM,STIN,MOTOJFLO,SMAL
      REAL IR00,IX00,IMMA,KE00,IN1,INM
      REAL I0R, I0X, IAUR, IAUX, ICCR, ICCX, IMOD
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      DIMENSION XYU(*),DATI(*),RNI(*)
C
C---Motore asin del 3 ordine 
C   calcolo residui
C
C---decodifica dati e  variabili 
C
C
      XM     = DATI(IPD   )
      XDS    = DATI(IPD+ 1)
      XDR    = DATI(IPD+ 2)
      RRS1   = DATI(IPD+ 3)
      RRSN   = DATI(IPD+ 4)
      CPOLI  = DATI(IPD+ 5)
      QNOM   = DATI(IPD+ 6)
      FNOM   = DATI(IPD+ 7)
      EPSI   = DATI(IPD+ 8)
      VNOM   = DATI(IPD+ 9)
      RS     = DATI(IPD+10)
      QPFER  = DATI(IPD+11)
      INM    = DATI(IPD+12)
      SCORN  = DATI(IPD+13)
      MECC   = DATI(IPD+14)
      VBASE  = DATI(IPD+15)
      IF (MECC.EQ.1)THEN
         TA     = DATI(IPD+16)
         COEFF  = DATI(IPD+17)
      ENDIF
C
      QBASE=H0*W0
      CQ=QNOM/QBASE
      CV=VNOM/VBASE
      OMBA=FNOM*2*3.141592654
C
      IF (MECC.EQ.1)THEN
      OMROT  = XYU(IXYU)
      OMMA   = OMROT*CPOLI
      END IF
      ED00   = XYU(IXYU   +MECC)           ! STATI
      EQ00   = XYU(IXYU+ 1+MECC)
      IR00   = XYU(IXYU+ 2+MECC)*CV/CQ     ! USCITE
      IX00   = XYU(IXYU+ 3+MECC)*CV/CQ
      KE00   = XYU(IXYU+ 4+MECC)/(CQ*CPOLI)
      QM00   = XYU(IXYU+ 5+MECC)/CQ
      SCOR   = XYU(IXYU+ 6+MECC)
      VRM0   = XYU(IXYU+ 7+MECC)/CV
      VXM0   = XYU(IXYU+ 8+MECC)/CV
      FDP0   = XYU(IXYU+ 9+MECC)
      QPE0   = XYU(IXYU+10+MECC)
      QQE0   = XYU(IXYU+11+MECC)
      IMMA   = XYU(IXYU+12+MECC)
      QPST   = XYU(IXYU+13+MECC)
      QPRO   = XYU(IXYU+14+MECC)
      QPFE   = XYU(IXYU+15+MECC)
      VR00   = XYU(IXYU+16+MECC)/CV        ! INGRESSI
      VX00   = XYU(IXYU+17+MECC)/CV
      IF (MECC.EQ.1)THEN
        QRES   = XYU(IXYU+19)/CQ
      ELSE
        OMMA   = XYU(IXYU+18)*CPOLI
      END IF
      STIN   = MOTOJFLO(XYU(IXYU+19+MECC))
      SMAL   = MOTOJFLO(XYU(IXYU+20+MECC))
      FREQ   = XYU(IXYU+21+MECC)
C
C---Scorrimento rispetto al riferimento in [rad/s]
C
      DELTOM = (FREQ/FNOM-OMMA)*OMBA
C
C--- Modulo della corrente assorbita dal motore
C
      IMOD=SQRT(IR00**2+IX00**2)  
C
C---Parametri del circuito equivalente della macchina asincrona
C      
      XR = XDR+XM
      XS = XDS+XM
C
      IF (OMMA.GT.0.001) EPSI=0
C
      IF(STIN) THEN
       DELTAR = (RRS1 -RRSN)/(1.-SCORN/100.)
       RR     = RRSN + DELTAR*((SCOR) - SCORN/100.)
       T01    = XR/(OMBA*RR)
      ELSE
       T01    = XR/(OMBA*RRSN)
      ENDIF
C
      XS1    = XS-((XM**2)/XR)
C
C---Modulo tensione di alimentazione, potenza elettrica attiva
C   e reattiva
C
      QPE1   = (-VR00*IR00-VX00*IX00)
      QQE1   = (-VX00*IR00+VR00*IX00)
C
      I0R = VRM0*QPFER
      I0X = VXM0*QPFER
C
      IAUR = IR00+I0R
      IAUX = IX00+I0X
C
      IF (SMAL) THEN
         IAUR =0.
         IAUX =0.
      END IF
C
      IF (FREQ.LT..5) FREQ=.5
C
C---calcolo residui
C
C     LA VARIABILE ALT SERVE PER IMPEDIRE UNA INVERSIONE DEL MOTO 
C     DURANTE LA FASE DI RALLENTAMENTO O A REGIME
C
      IF (MECC.EQ.1)THEN
	 IF(KREGIM.AND.OMROT.LE.0.0)THEN
           RNI(1)=OMROT
         ELSE
           IF (OMMA.LE.0.001) THEN
              RNI(1)=KE00*CPOLI/TA
           ELSE
              RNI(1)=(KE00*CPOLI-QRES/OMROT-COEFF)/TA
           ENDIF
         ENDIF
      ENDIF
C
      IF(STIN) THEN           ! INTERRUTTORE CHIUSO
C
C
C--residuo n.  1 (equazione di stato)   *******
      RNI(1+MECC) = -(ED00-(XS-XS1)*IAUX)/T01+EQ00*DELTOM
C
C--residuo n.  2 (equazione di stato)   *******
      RNI(2+MECC) = -(EQ00+(XS-XS1)*IAUR)/T01-ED00*DELTOM
C
      IF (SMAL) THEN   ! MALFUNZIONAMENTO
         RCT0 = .075*QNOM/VNOM**2.
         XCT0 = .075*QNOM/VNOM**2.
         ZCT0 = SQRT(RCT0**2.+XCT0**2.)
C
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3+MECC) = IR00+(VR00*RCT0+VX00*XCT0)/ZCT0**2.
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4+MECC) = IX00+(VX00*RCT0-VR00*XCT0)/ZCT0**2.
C
      ELSE      ! NON MALFUNZIONAMENTO
C  
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3+MECC) = -IAUR-(VX00/(FREQ/FNOM*XS1)-EQ00/XS1+
     $          RS*IAUX/(FREQ/FNOM*XS1))
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4+MECC) = -IAUX-(-VR00/(FREQ/FNOM*XS1)+ED00/XS1-
     $          RS*IAUR/(FREQ/FNOM*XS1))
C
      ENDIF
C
C--residuo n.  5 (equazione algebrica)   *******
      RNI(5+MECC) = KE00+ED00*IAUR+EQ00*IAUX 
C
C--residuo n.  6 (equazione algebrica)   *******
      RNI(6+MECC) = QM00-KE00*(OMMA+EPSI)
C
C--residuo n.  7 (equazione algebrica)   *******
      RNI(7+MECC) = SCOR-(FREQ/FNOM-OMMA)/(FREQ/FNOM)
C
C--residuo n.  18 (equazione algebrica)   *******
      RNI(8+MECC) = VRM0-VR00
C
C--residuo n.  9 (equazione algebrica)   *******
      RNI(9+MECC) = VXM0-VX00
C
      IF (KREGIM) THEN       ! 7 NON-EQUAZIONI
C
C--residuo n.  10 (equazione algebrica)   *******
      QSE1   = SQRT(QPE1**2.+QQE1**2.)
      IF(QSE1.GT.0.05)THEN
       FDP1  = QPE1/QSE1
      ELSE
       FDP1  = 0.
      ENDIF 
      RNI(10+MECC) = -FDP0+FDP1
C
C--residuo n.  11 (equazione algebrica)   *******
      RNI(11+MECC) = -QPE0 +VR00*IR00+VX00*IX00
C
C--residuo n.  12 (equazione algebrica)   *******
      RNI(12+MECC) =- QQE0 +VX00*IR00-VR00*IX00
C
C--residuo n.  13 (equazione algebrica)   *******
      RNI(13+MECC) = -IMMA+IMOD/INM
C
C--residuo n.  14 (equazione algebrica)   *******
      RNI(14+MECC) = -QPST+RS*(IAUR**2.+IAUX**2.)
C
C--residuo n.  15 (equazione algebrica)   *******
      RNI(15+MECC) = -QPRO+(-QPE0-QPFE-QPST)*SCOR
C
C--residuo n.  16 (equazione algebrica)   *******
      RNI(16+MECC) = -QPFE+(VR00**2.+VX00**2.)*QPFER
C
      ELSE 
C
C--residuo n.  10 (equazione algebrica)   *******
      QSE1   = SQRT(QPE1**2.+QQE1**2.)
      IF(QSE1.GT.0.05)THEN
       FDP1  = QPE1/QSE1
      ELSE
       FDP1  = 0.
      ENDIF 
      RNI(10+MECC) = FDP1
C
C--residuo n.  11 (equazione algebrica)   *******
      RNI(11+MECC) = VR00*IR00+VX00*IX00
C
C--residuo n.  12 (equazione algebrica)   *******
      RNI(12+MECC) = VX00*IR00-VR00*IX00
C
C--residuo n.  13 (equazione algebrica)   *******
      RNI(13+MECC) = IMOD/INM
C
C--residuo n.  14 (equazione algebrica)   *******
      RNI(14+MECC) = RS*(IAUR**2.+IAUX**2.)
C
C--residuo n.  15 (equazione algebrica)   *******
      RNI(15+MECC) = (-QPE0-QPFE-QPST)*SCOR
C
C--residuo n.  16 (equazione algebrica)   *******
      RNI(16+MECC) = (VR00**2.+VX00**2.)*QPFER
C
      END IF
C
      ELSE    ! INTERRUTTORE APERTO
C
      IF(.NOT.KREGIM) THEN            
C--residuo n.  1 (equazione di stato)   *******
      RNI(1+MECC) = -(ED00-(XS-XS1)*IAUX)/T01
C
C--residuo n.  2 (equazione di stato)   *******
      RNI(2+MECC) = -(EQ00+(XS-XS1)*IAUR)/T01 
C
      ELSE
C 
C--residuo n.  1 (equazione di stato)   *******
      RNI(1+MECC) = -ED00
C
C--residuo n.  2 (equazione di stato)   *******
      RNI(2+MECC) = -EQ00
C
      END IF
C
C--residuo n.  3 (equazione algebrica)   *******
      RNI(3+MECC) = -IR00
C
C--residuo n.  4 (equazione algebrica)   *******
      RNI(4+MECC) = -IX00
C
C--residuo n.  5 (equazione algebrica)   *******
      RNI(5+MECC) = KE00+ED00*IAUR+EQ00*IAUX 
C
C--residuo n.  6 (equazione algebrica)   *******
      RNI(6+MECC) = QM00-KE00*OMMA
C
C--residuo n.  7 (equazione algebrica)   *******
      RNI(7+MECC) = -SCOR
C
C--residuo n.  12 (equazione algebrica)   *******
      RNI(8+MECC) = -VRM0 + ED00*OMMA
C
C--residuo n.  13 (equazione algebrica)   *******
      RNI(9+MECC) = -VXM0 + EQ00*OMMA
C
	IF (KREGIM)THEN    ! 7 NON EQUAZIONI
C
C--residuo n.  10 (equazione algebrica)   *******
      RNI(10+MECC) = -FDP0
C   
C--residuo n.  11 (equazione algebrica)   *******
      RNI(11+MECC) = -QPE0
C
C--residuo n.  12 (equazione algebrica)   *******
      RNI(12+MECC) = -QQE0
C
C--residuo n.  13 (equazione algebrica)   *******  
      RNI(13+MECC) = -IMMA
C 
C--residuo n.  14 (equazione algebrica)   *******
      RNI(14+MECC) = -QPST
C 
C--residuo n.  15 (equazione algebrica)   *******
      RNI(15+MECC) = -QPRO
C 
C--residuo n.  16 (equazione algebrica)   *******
      RNI(16+MECC) = -QPFE
C
      ELSE
C
C--residuo n.  10 (equazione algebrica)   *******
      RNI(10+MECC) = 0
C   
C--residuo n.  11 (equazione algebrica)   *******
      RNI(11+MECC) = 0
C
C--residuo n.  12 (equazione algebrica)   *******
      RNI(12+MECC) = 0
C
C--residuo n.  13 (equazione algebrica)   *******
      RNI(13+MECC) = 0
C 
C--residuo n.  14 (equazione algebrica)   *******
      RNI(14+MECC) = 0
C 
C--residuo n.  15 (equazione algebrica)   *******
      RNI(15+MECC) = 0
C 
C--residuo n.  16 (equazione algebrica)   *******
      RNI(16+MECC) = 0
C
      END IF
C
      ENDIF     ! END INTERRUTTORE
C
      RETURN
      END
C
C
C
      SUBROUTINE MOTOI3 (IFO,IOB,DEBL)
C
      COMMON/MOTO01/IBLOC
      COMMON/MOTO02/NCEL,NPAR
      COMMON/SCELTA/MECC
      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80
      DATA MOD/'MOTO'/
C
      CALL MOTOI4(IOB,MOD)
      NSTATI = 2+MECC
      NUSCIT = 14
      NINGRE = 6+MECC
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      IF(MECC.EQ.1)THEN
      WRITE(IFO,3101)IOB
 3101 FORMAT('OMMA',A4,2X,
     $  57H--US-- PULSAZIONE MECCANICA ALBERO [rad/sec]             ) 
      END IF
C
      WRITE(IFO,3001)IOB
 3001 FORMAT('ED00',A4,2X,
     $  57H--US-- FEM TRANSITORIA ASSE DIRETTO [pu]                 )
      WRITE(IFO,3002)IOB
 3002 FORMAT('EQ00',A4,2X,
     $  57H--US-- FEM TRANSITORIA ASSE IN QUADRATURA [pu]           )
      WRITE(IFO,3003)IOB
 3003 FORMAT('IR00',A4,2X,
     $  57H--UA-- CORRENTE REALE EROGATA [A]                        )
      WRITE(IFO,3004)IOB
 3004 FORMAT('IX00',A4,2X,
     $  57H--UA-- CORRENTE IMMAGINARIA EROGATA [A]                  )
      WRITE(IFO,3005)IOB
 3005 FORMAT('KE00',A4,2X,
     $  57H--UA-- COPPIA ELETTROMAGNETICA [N*m]                     )
      WRITE(IFO,3006)IOB
 3006 FORMAT('QM00',A4,2X,
     $  57H--UA-- POTENZA MOTRICE [W]                               )
      WRITE(IFO,3008)IOB
 3008 FORMAT('SCOR',A4,2X,
     $  57H--UA-- SCORRIMENTO [%]                                   )
      WRITE(IFO,3012)IOB
 3012 FORMAT('VRM0',A4,2X,
     $  57H--UA-- TENSIONE REALE AI MORSETTI [V]                    )
      WRITE(IFO,3013)IOB
 3013 FORMAT('VXM0',A4,2X,
     $  57H--UA-- TENSIONE IMMAG AI MORSETTI [V]                    )
      WRITE(IFO,3007)IOB
 3007 FORMAT('FDP0',A4,2X,
     $  57H--UA-- FATTORE DI POTENZA                                )
      WRITE(IFO,3009)IOB
 3009 FORMAT('QPE0',A4,2X,
     $  57H--UA-- POTENZA ATTIVA EROGATA  DAL MOTORE [W]            )
      WRITE(IFO,3010)IOB
 3010 FORMAT('QQE0',A4,2X,
     $  57H--UA-- POTENZA REATTIVA EROGATA DAL MOTORE [W]           )
      WRITE(IFO,3011)IOB
 3011 FORMAT('IMMA',A4,2X,
     $  57H--UA-- PERCENTUALE DI CARICO [%]                         )
      WRITE(IFO,3014)IOB
 3014 FORMAT('QPST',A4,2X,
     $  57H--UA-- PERDITE RAME STATORICHE [W]                       )
      WRITE(IFO,3015)IOB
 3015 FORMAT('QPRO',A4,2X,
     $  57H--UA-- PERDITE RAME ROTORICHE [W]                        )
      WRITE(IFO,3016)IOB
 3016 FORMAT('QPFE',A4,2X,
     $  57H--UA-- PERDITE NEL FERRO [W]                             )
      WRITE(IFO,3017)IOB
 3017 FORMAT('VR00',A4,2X,
     $  57H--IN-- TENSIONE REALE DI SBARRA [V]                      )
      WRITE(IFO,3018)IOB
 3018 FORMAT('VX00',A4,2X,
     $  57H--IN-- TENSIONE IMMAG DI SBARRA [V]                      )
C     
      IF(MECC.NE.1) THEN
        WRITE(IFO,3019)IOB
 3019   FORMAT('OMMA',A4,2X,
     $  57H--IN-- PULSAZIONE MECCANICA ALBERO [rad/s]               )
      ELSE
        WRITE(IFO,3021)IOB
 3021   FORMAT('QRES',A4,2X,
     $  57H--IN-- POTENZA MECCANICA RESISTENTE [W]                  )
      ENDIF
      WRITE(IFO,3020)IOB
 3020 FORMAT('STIN',A4,2X,
     $  57H--IN-- STATO INTERRUTTORE (1.-->chiuso)                  )
      WRITE(IFO,3022)IOB
 3022 FORMAT('SMAL',A4,2X,
     $  57H--IN-- MALFUNZIONAMENTO DEL MOTORE (1-->cto-cto)         )
      WRITE(IFO,3023)IOB
 3023 FORMAT('FREQ',A4,2X,
     $  57H--IN-- FREQUENZA DI ALIMENTAZIONE STATORE [Hz]           )
      RETURN
      END
C
C
C
      SUBROUTINE MOTOI4 (IOB,MOD)
      COMMON/MOTO01/IBLOC,NSVA
      COMMON/MOTO02/NCEL,NPAR
      CHARACTER*4 IOB, MOD, IBLOC*8
      COMMON/SCELTA/MECC
C
100   WRITE(6,101)
101   FORMAT(10X,'VELOCITA` MECCANICA:',/,10X,'0-->INGRESSO',
     $     /,10X,'1-->USCITA')
      READ(5,102)MECC
102   FORMAT(I1)
      IF (MECC.NE.1.AND.MECC.NE.0) GOTO 100
C
      WRITE(IBLOC,1)MOD,IOB
    1 FORMAT(2A4)
      RETURN
      END
C
C
C
C
      SUBROUTINE MOTOD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
C---Motore asin del 3 ordine 
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      COMMON/SCELTA/NING
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
C
      RETURN
      END
C
      LOGICAL FUNCTION MOTOJFLO(VAL)
C
      IF (VAL.GT.0.5) THEN
         MOTOJFLO=.TRUE.
      ELSE
         MOTOJFLO=.FALSE.
      ENDIF
C
      RETURN
      END
