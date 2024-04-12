C*********************************************************************
C       Fortran Source:             toprid.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:30:06 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_toprid_f
      CHARACTER*80  RepoID
      COMMON /CM_toprid_f / RepoID
      DATA RepoID/'@(#)1,fsrc,toprid.f,2'/
      END
C**********************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE TOPRID(NBL,ISLB,NUSTA,NUSCI,NINGR,IPDATI,DATI,IP,
     $                  XYU,VAR,NX5,NOBLC,NX2,RNI,AJAC,MX5,NEQSIS,
     $                  SIVAR,VARI,NX4,NU,
C_________ uscite della subroutine
     $                  VARSYS,NX3,IPVRSV,NQALV,NQSISV,NQMODU,
     $                  IPVVSS,IPSSVV,NVART)
C
      DIMENSION ISLB(*),NUSTA(*),NUSCI(*),IPDATI(*),DATI(*),IP(*),
     $          NINGR(*),XYU(*),NOBLC(NX2,2),RNI(*),AJAC(MX5,*),
     $          IPVRSV(*),NQMODU(*),IPVVSS(*),IPSSVV(*)
C_________ uscite della subroutine

      CHARACTER*8 VAR(NX5),SIVAR(NX3),VARI(NX4),VARSYS(NX3),VAVA
C
      COMMON/NORM/P0,H0,T0,Q0,RO0,AL0,V0,DP0
      COMMON/NEQUAZ/NEQMOD
C
C     NQALV = numero equazioni ALGEBRICHE effettive da risolvere
C     NQSISV= numero equazioni DEL SISTEMA
C
      NQALV=0
      IFUN=1
      NEQDIF=0
C
      DO 500 I=1,NBL
      K=ISLB(I)
      IPD=IPDATI(I)
      IXYU=IP(I)
      NS=NUSTA(I)
      NY=NUSCI(I)
      NI=NINGR(I)
      NEBL=NS+NY
      NOBL1=NOBLC(I,1)
      NOBL2=NOBLC(I,2)
      NEQMOD=-1
C
      CALL MODC1(K,IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,NOBL1,NOBL2)
C
      IF(NEQMOD.LT.0)NEQMOD=NY
      NQMODU(I)=NEQMOD
      NQALV=NQALV+NEQMOD
      NEQDIF=NEQDIF+NS
C
  500 CONTINUE
      NQSISV=NQALV+NEQDIF
      M=0
      K=0
C
C______ SE IL NUMERO DI EQUAZIONI DA RISOLVERE E` 0.
C
      IF(NQSISV.EQ.0)GO TO 201
C
C     ORDINAMENTO DELLE VARIABILI DEL SISTEMA VARSYS
C    -TUTTE LE USCITE  -
C    -TUTTI GLI STATI  - PROCEDENDO DAL PRIMO ALL'ULTIMO BLOCCO
C
      DO 120 I=1,NBL
      NS=NUSTA(I)
      NY=NQMODU(I)
      I1=IP(I)
      IF(NS.EQ.0) GO TO 115
      I2=I1+NS-1
      DO 110 L=I1,I2
      K=K+1
      VARSYS(NQALV+K)=VAR(L)
  110 CONTINUE
      I1=I2+1
  115 IF(NY.EQ.0)GO TO 120
      I2=I1+NY-1
      DO 117 L=I1,I2
      M=M+1
      VARSYS(M)=VAR(L)
  117 CONTINUE
  120 CONTINUE
C
C     DEFINIZIONE DEL PUNTATORE DELLE VARIABILI INCOGNITE __VARSYS__
C     ALLE VARIABILI DI USCITA DEL MODELLO __SIVAR__
C
      IER=0
      DO 200 I=1,NQSISV
      VAVA=VARSYS(I)
      DO 180 J=1,NEQSIS
      IF(VAVA.EQ.SIVAR(J))GO TO 190
  180 CONTINUE
      IER=1
      WRITE(6,4312)VAVA
 4312 FORMAT(//10X,'ER- SUB. TOPRID -',
     $       /'ERRORE DURANTE DEFINIZIONE DI IPVVSS',
     $       //10X,'VARIABILE NON TROVATA = ',A8,//)
      IPVVSS(I)=0
      GO TO 200
  190 IPVVSS(I)=J
  200 CONTINUE
      IF (IER.EQ.1) CALL LGABRT
C
C DEFINIZIONE DEL PUNTATORE DELLE VARIABILI USCITA DEL MODELLO __SIVAR__
C ALLE VARIABILI INCOGNITE DEL SYSTEMA __VARSYS__
C
  201 CONTINUE
      DO 210 I=1,NEQSIS
      VAVA=SIVAR(I)
      IPSSVV(I)=-999999
C
      IF(NQSISV.EQ.0)GO TO 210
C
      DO 205 J=1,NQSISV
        IF(VAVA.EQ.VARSYS(J))THEN
          IPSSVV(I)=J
          GO TO 210
        ENDIF
  205 CONTINUE
  210 CONTINUE
C
C     CONTROLLI
C
      IF(M.EQ.NQALV)GO TO 130
      WRITE(6,3312)M,NQALV
 3312 FORMAT(//10X,'ER- SUB. TOPRID -ERRORE DURANTE ORDINAMENTO ',
     $   'VARIABILI DEL SISTEMA '//10X,'M= ',I3,'  NQALV= ',I3//)
      CALL LGABRT
C
C     RIDEFINIZIONE DEL PUNTATORE --IPVRS-- CHE DIVENTA --IPVRSV--
C     IL VETTORE VARSYS(POSITIVO) O VARI (NEGATIVO)
C
  130 CONTINUE
      DO 150 I=1,NBL
      NI=NINGR(I)
      NS=NUSTA(I)
      NY=NUSCI(I)
      N=NS+NY
      I1=IP(I)
      I2=IP(I+1)-1
      DO 140 J=I1,I2
      VAVA=VAR(J)
C
      IF(NQSISV.EQ.0)GO TO 134
C
      DO 135 KI=1,NQSISV
      IF(VAVA.EQ.VARSYS(KI))GO TO 136
  135 CONTINUE
C
  134 DO 145 KJ=1,NU
      IF(VAVA.EQ.VARI(KJ))GO TO 146
  145 CONTINUE
C
      IPVRSV(J)=-999999
      GO TO 140
  136 IPVRSV(J)=KI
      GO TO 140
  146 IPVRSV(J)=-KJ
  140 CONTINUE
  150 CONTINUE
C
C     STAMPE OPZIONALI
C
      CALL SSWTCH(1,LL)
      IF(LL.NE.1)GO TO 300
      WRITE(6,2000)
 2000 FORMAT(1H1//10X,'STAMPE DA SSWTCH 1 -SUBROUTINE TOPRID '//)
      DO 230 I=1,NBL
      WRITE(6,2001) NOBLC(I,1),NOBLC(I,2),NUSTA(I),NUSCI(I),
     $              NINGR(I),ISLB(I),IP(I)
 2001 FORMAT(10X,2X,2A4,5I6)
  230 CONTINUE
      WRITE(6,2002)IP(NBL+1)
 2002 FORMAT(48X,I6)
      WRITE(6,*)'NUMERO DI EQUAZIONI DEL SISTEMA'
      WRITE(6,*)NQSISV
      WRITE(6,*)'NUMERO DI EQUAZIONI ALGEBRICHE DEL SISTEMA'
      WRITE(6,*)NQALV
      WRITE(6,2003)(I,(VAR(I)),IPVRSV(I),I=1,NVART)
 2003 FORMAT(10X,I6,2X,A8,I10)
 2030 FORMAT(10X,I6,2X,A8,2X,I10)
      IF(NQSISV.GT.0)
     $     WRITE(6,2030)(I,(VARSYS(I)),IPVVSS(I),I=1,NQSISV)
      WRITE(6,2030)(I,(SIVAR(I)),IPSSVV(I),I=1,NEQSIS)
C
  300 CONTINUE
C
      RETURN
      END
C            
