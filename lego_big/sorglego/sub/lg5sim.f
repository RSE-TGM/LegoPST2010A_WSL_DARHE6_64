C*********************************************************************
C       Fortran Source:             lg5sim.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:27:18 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_lg5sim_f
      CHARACTER*80  RepoID
      COMMON /CM_lg5sim_f / RepoID
      DATA RepoID/'@(#)1,fsrc,lg5sim.f,2'/
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

      SUBROUTINE LG5SIM
C
C     CALCOLO DI UN TRANSITORIO
C
C
       include '../main/lg_parameter.fh'
C
C**************DATI GENERALI
C
      DIMENSION NOSL(N001),NOSUB(N002),NOBLC(N002,2),NUSTA(N002),
     $          NUSCI(N002),NINGR(N002),ISLB(N002),IP(M003),IPVRS(N005),
     $          IPS(M004),IPVRT(N005),IPI(M005),IPVRI(M001),
     $          XY(N003),UU(N004),XYU(N005),DATI(N007),IPDATI(M003),
     $          CNXYU(N005),IPLOT(N003),ISTMP(N003),TOLL(N003),
     $          IVPER(NP00),ITPER(NP00),IPPER(MP01),DATPER(MP02)
      COMMON/C0LG5A/XY,UU,XYU,DATI,CNXYU,TOLL,DATPER,NOSL,NOSUB,NOBLC,
     $              NUSTA,NUSCI,NINGR,ISLB,IP,IPVRS,IPS,IPVRT,IPI,
     $              IPVRI,IPDATI,IPLOT,ISTMP,IVPER,ITPER,IPPER
C
C*********MEMORIA PER LA MATRICE JACOBIANA
C
      DIMENSION IPCJ(M004),ICJ(M006),ICBJ(M006),FJ(M007),ICN(M007),
     $          IRN(M007),IKEEP(M008),IW(M009),W(N003),RHS(N003),
     $          AJAC(N008,N006),RNI(N003),RIGA(N003)
      COMMON/C0LG5B/FJ,W,RHS,AJAC,RNI,RIGA,
     $              IPCJ,ICJ,ICBJ,ICN,IRN,IKEEP,IW
C
C*********MEMORIA PER RIDEFINIZIONE DELLE REALI DIMENSIONI DEL SISTEMA
C
      DIMENSION NQMODU(N002),IPVRSV(N005),
     $          IPVVSS(N003),IPSSVV(N003),RNV(N003),XYV(N003)
      COMMON/C0LG5C/RNV,XYV,NQMODU,IPVRSV,IPVVSS,IPSSVV
C
C*********VARIABILI DI TIPO CARATTERE
C
      CHARACTER*8 VAR(N005),SIVAR(N003),VARI(N004),VARSYS(N003)
      COMMON/C0LG5D/VAR,SIVAR,VARI,VARSYS
C
      CHARACTER*100 NMSIVA(N003)
      CHARACTER*100 NMVARI(N004)
      CHARACTER*80  NMBLOC(N002)
      DIMENSION IOUSIV(N003),IOUVAR(N004),ITITOL(20)
C
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON/DIMAJA/NRXJC,NCXJC
      COMMON/PARINT/ITITOL,TFIN,TSTEP,FATOLL,INTERR,TINTER
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
      COMMON/REGIME/KREGIM
      COMMON/RSTRT1/TREST,IREGIM
      COMMON/FILOTP/FILE21,FILE22
      CHARACTER*50 FILE22,FILE21,FILE04
      LOGICAL KREGIM,RESTAR
      CHARACTER * 8 SIGLA
C
      KREGIM=.FALSE.
      RESTAR=.FALSE.
      TREST=0.
C
      NRXJC=N008
      NCXJC=N006
C
C     APERTURA FILE TAVOLE DEL VAPORE
C
      CALL INITSM
C
      FILE04='proc/f04.dat'
      FILE21='proc/f21.dat'
      FILE22='proc/f22.dat'
C
      OPEN(UNIT=04,FILE=FILE04,STATUS='OLD',FORM='UNFORMATTED')
C
C       Il file 21 viene aperto dalla reg_000.c -> libsim.a
C       10/12/'93
C
C     OPEN(UNIT=21,FILE=FILE21,STATUS='UNKNOWN',FORM='UNFORMATTED')
C
C   Nota: le UNIT 04 e 21 possedevano l'attributo "SHARED"
C
C     LETTURA DATI DA FILE 04
C
      REWIND 04
      READ(04)NBL,NEQAL,NBL1,NVART,NEQSIS,NEQS1,NPVRT,NU,NU1,NVRI
      READ(04)N,N,NST,SIGLA,(NOSL(I),I=1,NST)
C
      READ(04) (NOSUB(I),NOBLC(I,1),NOBLC(I,2),NUSTA(I),NUSCI(I),
     $          NINGR(I),ISLB(I),NMBLOC(I),I=1,NBL)
      READ(04) (IP(I),I=1,NBL1),(VAR(I),IPVRS(I),I=1,NVART)
      READ(04) (IPS(I),I=1,NEQS1),(SIVAR(I),NMSIVA(I),
     $          IOUSIV(I),I=1,NEQSIS),(IPVRT(I),I=1,NPVRT)
      READ(04) (IPI(I),I=1,NU1),(VARI(I),NMVARI(I),
     $          IOUVAR(I),I=1,NU),(IPVRI(I),I=1,NVRI)
C
      READ(04)P0,H0,T0,Q0,R0,AL0,V0,DP0
      READ(04)(XY(I),I=1,NEQSIS),(UU(I),I=1,NU),(XYU(I),I=1,NVART)
      READ(04)NDATI,(IPDATI(I),I=1,NBL1),(DATI(I),I=1,NDATI),
     $        (CNXYU(I),I=1,NVART),(TOLL(I),I=1,NEQSIS)
      READ(04)IREGIM
C
C     COSTRUZIONE DELLA TOPOLOGIA DEL SISTEMA
C     DIFF. - ALG. E FATTORIZZAZIONE AD INDICI
C
      CALL LGTOPS
C
C     CALCOLO DEL TRANSITORIO
C
      CALL LGDYNS(RESTAR)
C
C_____CHIUSURA DI TUTTI I FILES
C
      CLOSE(UNIT=04)
      CLOSE(UNIT=21)
C
      RETURN
      END
C            
