CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGJAC1(NBL,ISLB,IPDATI,IP,XYU,DATI,IPVRS,NUSCI,NUSTA,
     $                   IPCJ,ICBJ,FJ,CDT,NEQSIS,ICJ,AJAC,MMX5,
     $                   NOBLC,MX3,RNI,ICN,IRN,IGRAD,NQALV,NTER,
C***************************** TAVOLE ******************************
     $                  NOSUB)
C***************************** TAVOLE ******************************
      DIMENSION ISLB(*),IPDATI(*),IP(*),XYU(*),DATI(*),IPVRS(*),
     $          NUSCI(*),NUSTA(*),IPCJ(*),ICBJ(*),
     $          FJ(*),ICJ(*),ICN(*),IRN(*),
     $          NOBLC(MX3,2),RNI(*),AJAC(MMX5,MMX5)
      COMMON/NORM/P0,H0,T0,Q0,RO0,AL0,V0,DP0
      COMMON/DIMAJA/NRXJC,NCXJC
C********************** TAVOLE ******************************
      DIMENSION NOSUB(*)
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP .

      COMMON/LGTV01/LGTEMP,ILEGO,ICOUNT,ICNTMX
      COMMON/LGTV02/LGMODU,LGBLOC
      CHARACTER*8 LGMODU,LGBLOC
      REAL LGTEMP
      
C********************** TAVOLE ******************************

C    COSTRUZIONE DELLO JACOBIANO DEL SISTEMA ALG-DIFF A PARTIRE DALLE
C    MATRICI JACOBIANE DEI SINGOLI BLOCCHI UTILIZZANDO LE INFORMAZIONI
C    TOPOLOGICHE DEFINITE DA TOPSIS - LO JACOBIANO EST MEMORIZZ. IN FJ

      IFUN=3
      MX5=MMX5
      LY=0
      LS=IPCJ(NQALV+1)-1
      DO 500 I=1,NBL
      K=ISLB(I)
      IPD=IPDATI(I)
      IXYU=IP(I)
      IBLOC1=NOBLC(I,1)
      IBLOC2=NOBLC(I,2)
C********************** TAVOLE ******************************
      WRITE(LGMODU,'(A4)')NOSUB(I)
      WRITE(LGBLOC,'(2A4)')IBLOC1,IBLOC2
C********************** TAVOLE ******************************

      I1=IP (I)
      I2=IP (I+1)-1
      NXYU=I2-I1+1
      NY=NUSCI(I)
      NS=NUSTA(I)
      NSY=NS+NY
      DO J=1,NSY
        DO JL=1,NXYU
          AJAC(J,JL)=0.
        ENDDO
      ENDDO

      CALL MODC1(K,IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBLOC1,IBLOC2)

      I0=I1-1
      DO J=NS+1,NSY     ! trasferimento dei termini (relativi alle equaz.
        K1=IPVRS(I0+J)  ! algebriche) dello jacobiano di un blocco nello
        J1=IPCJ(K1)     ! jacobiano del sistema
        J2=IPCJ(K1+1)-1
        DO JK=J1,J2
          ICB=ICBJ(JK)
          IF(AJAC(J,ICB).NE.0.)THEN
            LY=LY+1
            FJ(LY)=AJAC(J,ICB)
            ICN(LY)=ICJ(JK)
            IRN(LY)=K1
          ENDIF
        ENDDO
      ENDDO
      IF(IGRAD.EQ.0)THEN               ! caso non gradino
        DO J=1,NS                      ! i termini relativi alle equaz. diff. 
          DO JL=1,NXYU                 ! vengono modificati per tenere conto 
            AJAC(J,JL)=-CDT*AJAC(J,JL) ! che l'equaz. alg. relativa   
          ENDDO                        !  XN-CDT.F(XN)-T(N-1)=0 
          AJAC(J,J)=1.+AJAC(J,J)
        ENDDO
        DO J=1,NS          ! trasferimento dei termini (relativi alle equaz.
          K1=IPVRS(I0+J)   ! diff.) nello jacobiano del sistema  
          J1=IPCJ(K1)
          J2=IPCJ(K1+1)-1
          DO JK=J1,J2
            ICB=ICBJ(JK)
            IF(AJAC(J,ICB).NE.0.)THEN
              LS=LS+1
              FJ(LS)=AJAC(J,ICB)
              ICN(LS)=ICJ(JK)
              IRN(LS)=K1
            ENDIF
          ENDDO
        ENDDO
      ENDIF
  500 CONTINUE

      L=LY
      IF(IGRAD.EQ.0)THEN          ! caso non gradino
        DO I=IPCJ(NQALV+1),LS     ! spostamento dei termini relativi alle
          L=L+1                   ! equaz. diff.
          FJ(L)=FJ(I)
          ICN(L)=ICN(I)
          IRN(L)=IRN(I)
        ENDDO
      ELSE                        ! perturbazione a gradino 
        DO I=NQALV+1,NEQSIS       ! la matrice jacobiana viene ridotta
          L=L+1                   ! alle sole equazioni algebriche 
          FJ(L)=1.
          ICN(L)=I
          IRN(L)=I
        ENDDO
      ENDIF
      NTER=L

      CALL SSWTCH(2,LL)           ! stampa opzionale
      IF(LL.EQ.1) THEN
        WRITE(6,1000)
        DO I=1,NTER
      	   WRITE(6,1003)IRN(I),ICN(I),FJ(I)
        ENDDO
      ENDIF
      RETURN
 1000 FORMAT(///10X,'STAMPA OPZIONALE SSWTCH-2 '//10X,'MATRICE JACOBIANA
     $ DEL SISTEMA ALG-DIFF '//)
 1003 FORMAT(10X,'RIGA ',I6,' COL. ',I6,' = ',G15.6)
      END

