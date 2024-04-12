C*********************************************************************
C       Fortran Source:             rgdyns.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:50 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_rgdyns_f
      CHARACTER*80  RepoID
      COMMON /CM_rgdyns_f / RepoID
      DATA RepoID/'@(#)1,fsrc,rgdyns.f,2'/
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

      SUBROUTINE RGDYNS
C
C     DEL PROGRAMMA  RG5SIM
C
C
       include '../main/lg_parameter.fh'
C
C
C**************DATI GENERALI
C
      DIMENSION NOSL(N001),NOSUB(N002),NOBLC(N002,2),NUSTA(N002),
     $          NUSCI(N002),NINGR(N002),ISLB(N002),IP(M003),IPVRS(N005),
     $          IPS(M004),IPVRT(N005),IPI(M005),IPVRI(M001),XY(N003),
     $          UU(N004),XYU(N005),DATI(N007),IPDATI(M003),CNXYU(N005),
     $          AJAC(1,1),RNI(N003),CNXY(N003),CNUU(N004)
      COMMON/C0RG5A/XY,UU,XYU,DATI,CNXYU,AJAC,RNI,CNXY,CNUU,
     $              NOSL,NOSUB,NOBLC,NUSTA,NUSCI,NINGR,ISLB,IP,
     $              IPVRS,IPS,IPVRT,IPI,IPVRI,IPDATI
      CHARACTER*8 SIGLA
C
C*****DATI UTILIZZATI PER COMUNICARE AL LEGO RUN-TIME LE DIM DEL LEGO
C
      INTEGER  KN000, KN001, KN002, KN003, KN004, KN005, KN007,
     $         KM001, KM002, KM003, KM004, KM005
      COMMON/PARSKED/KN000, KN001, KN002, KN003, KN004, KN005, KN007,
     $               KM001, KM002, KM003, KM004, KM005
C
      DIMENSION ITITOL(20),NUL(7)
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON/PARINT/ITITOL,TFIN,TSTEP,FATOLL,INTERR,TINTER
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      COMMON/PARPAR/NUL,ITERT
C********************** TAVOLE ******************************
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP.
C
      COMMON/LGTV01/LGTEMP,ILEGO,ICOUNT,ICNTMX
      COMMON/LGTV02/LGMODU,LGBLOC
      CHARACTER*8 LGMODU,LGBLOC
      REAL LGTEMP
      ILEGO    =1
C
C*****SETTAGGIO DEI DATI DA PASSARE ALLA PARTE RUN-TIME
C
      KN000 = N000
      KN001 = N001
      KN002 = N002
      KN003 = N003
      KN004 = N004
      KN005 = N005
      KN007 = N007
      KM001 = M001
      KM002 = M002
      KM003 = M003
      KM004 = M004
      KM005 = M005
C********************** TAVOLE ******************************
C
      CALL BLLEG1(IPVRS,NVART,CNXYU,CNXY,CNUU)
C
      NEQDIF=0
C
C      INIZIALIZZAZIONE
C
      ITERT=0
      JAC=0
C
C    T_PROC=1   task di processo   T_PROC=0 task di regolazione
C
      T_PROC=0
      IFUN=2
      ITERT=0
      NPAS=0
      TEMPO=0.
      LGTEMP=TEMPO
      IPR=1
      CALL REG000(IPR,XY,UU,PX,DATI,NEQSIS,NU,NEQDIF,NDATI,CNXY,CNUU
     $            ,TSTEP,IFINE,T_PROC,JAC,ITERT)
C
      GO TO (999, 1000) IFINE
C
C      LOOP DI INTEGRAZIONE
C
  999 CONTINUE
C
C      ESECUZIONE DI UN PASSO DI
C
      DTINT=TSTEP
      NPAS=NPAS+1
      TEMPO= TEMPO+ DTINT
      LGTEMP=TEMPO
C
      CALL LEGBL1(NEQSIS,IPS,IPVRT,XY,XYU)
      CALL LEGBL1(NU,IPI,IPVRI,UU,XYU)
C
C     CALCOLO DELLA RISPOSTA DELLA REGOLAZIONE
C
      M=0
      DO 500 I=1,NBL
      K=ISLB(I)
      IPD=IPDATI(I)
      NUS=NUSCI(I)
      IXYU=IP(I)
      IBLOC1=NOBLC(I,1)
      IBLOC2=NOBLC(I,2)
C********************** TAVOLE ******************************
      WRITE(LGMODU,'(A4)')NOSUB(I)
      WRITE(LGBLOC,'(2A4)')IBLOC1,IBLOC2
C********************** TAVOLE ******************************
C
      CALL MODC1(K,IFUN,AJAC,1,IXYU,XYU,IPD,DATI,RNI,IBLOC1,IBLOC2)
C
C     TRASFERIMENTO DI RNI (VALORI DELLE USCITE DI UN BLOCCO)
C     NEL VETTORE XY (VARIABILI RESIDUI EQ. DEL SISTEMA)
C
      DO 101 J=1,NUS
      M = M+1
      XY (M) = RNI(J)
C
C     TRASFERIMENTO DELLE USCITE VERSO GLI INGRESSI DEGLI ALTRI SCHEMI
C     CONNESSI (NON ESISTEVA IN REGOGRAF)
C
      KJ1=IPS(M)
      KJ2=IPS(M+1)-1
      IF(KJ2.LT.KJ1) GO TO 101
      DO 95 KJ=KJ1,KJ2
      KKJ=IPVRT(KJ)
      XYU(KKJ)=XY(M)
   95 CONTINUE
C
C     FINE AGGIUNTA TRASFERIMENTO USCITE
C
  101 CONTINUE
  500 CONTINUE
C
      IPR=2
      CALL REG000(IPR,XY,UU,PX,DATI,NEQSIS,NU,NEQDIF,NDATI,CNXY,
     $            CNUU,TSTEP,IFINE,T_PROC,JAC,ITERT)
C
C      TEST  FINE TRANSITORIO
C
      GO TO (999,1000) IFINE
 1000 CONTINUE
      RETURN
      END
C            
