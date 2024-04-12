C******************************************************************************
C modulo resreg.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)resreg.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE RESREG(NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,IP,TN,
     $                  CDT,XYU,RN,ICONV,SIVAR,MX1,NEQSIS,IPVRS,TOLL,
     $                  IOK,NOBLC,MX3,RNI,
C****************** TAVOLE ********************************************
     $                  NOSUB)
C****************** TAVOLE ********************************************
      DIMENSION ISLB(*),NUSTA(*),NUSCI(*),IPDATI(*),DATI(*),IP(*),
     $          TN(*),XYU(*),RN(*),ICONV(*),
     $          IPVRS(*),TOLL(*),NOBLC(MX3,2),RNI(*)
      CHARACTER*8 SIVAR(MX1)
      DIMENSION IOUT(5)
      COMMON/NORM/P0,H0,T0,Q0,RO0,AL0,V0,DP0
      COMMON/NEQUAZ/NEQMOD
      COMMON/BLOSE/NBLSE
C********************** TAVOLE ******************************
      DIMENSION NOSUB(*)
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP .
C
      COMMON/LGTV01/LGTEMP,ILEGO,ICOUNT,ICNTMX
      COMMON/LGTV02/LGMODU,LGBLOC
      CHARACTER*8 LGMODU,LGBLOC
      REAL LGTEMP
C********************** TAVOLE ******************************
C
C     CALCOLO DEI RESIDUI DELLE EQUAZIONI ALGEBRICHE -DIFFERENZ.
C
      M=0
      IFUN=2
C
      NBLSE=0
C
      DO 500 I=1,NBL
      K=ISLB(I)
      IPD=IPDATI(I)
      IXYU=IP(I)
      NS=NUSTA(I)
      NY=NUSCI(I)
      NEBL=NS+NY
      DO 5 J=1,NEBL
      RNI(J)=0.
    5 CONTINUE
      NOBL1=NOBLC(I,1)
      NOBL2=NOBLC(I,2)
C********************** TAVOLE ******************************
      WRITE(LGMODU,'(A4)')NOSUB(I)
      WRITE(LGBLOC,'(2A4)')NOBL1,NOBL2
C********************** TAVOLE ******************************
C
      NEQMOD=-1
C
      CALL MODC1(K,IFUN,AJAC,1,IXYU,XYU,IPD,DATI,RNI,NOBL1,NOBL2)
C
C_________ NBLSE = CONTATORE DEI BLOCCHI CHE NON HANNO EQUAZIONI
C
      IF(NEQMOD.EQ.0)NBLSE=NBLSE+1
C
C     TRASFERIMENTO DI RNI (RESIDUI EQ. DI UN BLOCCO)
C     NEL VETTORE RN (RESIDUI EQ. DEL SISTEMA)
C
      DO 200 J=1,NEBL
      IF(J.LE.NS)RNI(J)=-RNI(J)
      M=M+1
  199 RN(M)=RNI(J)
  200 CONTINUE
  500 CONTINUE
      IOK=1
C
C     TEST DI CONVERGENZA SUL SISTEMA
C
      DO 505 I=1,NEQSIS
      ICONV(I)=0
      IF(ABS(RN(I)).LE.TOLL(I))GO TO 505
      ICONV(I)=1
  505 CONTINUE
      DO 506 I=1,NEQSIS
      IF(ICONV(I).EQ.1)GO TO 507
  506 CONTINUE
      GO TO 520
  507 IOK=0
C
C     STAMPE OPZIONALI -SSWTCH 2
C
  520 CALL SSWTCH(2,LL)
      IF(LL.NE.1)RETURN
C
      WRITE(6,1000)
 1000 FORMAT(///10X,'RESIDUI DELLE EQUAZIONI NON SODDISFATTE'//)
      J=0
      DO 530 I=1,NEQSIS
      IF(ICONV(I).EQ.0) GOTO 530
      J=J+1
      IOUT(J)=I
      IF(J.LT.5) GOTO 530
      WRITE(6,1007) (IOUT(K),RN(IOUT(K)),K=1,J)
      J=0
  530 CONTINUE
      IF(J.NE.0) WRITE(6,1007) (IOUT(K),RN(IOUT(K)),K=1,J)
 1007 FORMAT(5(5X,I5,3X,E12.5))
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_resreg
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)resreg.f	2.1\t7/10/95'/
      END
