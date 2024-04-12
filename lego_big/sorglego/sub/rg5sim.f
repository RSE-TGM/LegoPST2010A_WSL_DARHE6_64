C*********************************************************************
C       Fortran Source:             rg5sim.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:48 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_rg5sim_f
      CHARACTER*80  RepoID
      COMMON /CM_rg5sim_f / RepoID
      DATA RepoID/'@(#)1,fsrc,rg5sim.f,2'/
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

      SUBROUTINE RG5SIM
C
C     CALCOLO DI UN TRANSITORIO PER UN MODELLO DI SOLI SCHEMI DI
C     REGOLAZIONE
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
C
      CHARACTER*100 DUSIVA
      CHARACTER*100 DUVARI
      CHARACTER*80  DUBLOC
      CHARACTER*8 SIGLA, DUMVAR
      DIMENSION ITITOL(20),NUL(7)
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON/PARINT/ITITOL,TFIN,TSTEP,FATOLL,INTERR,TINTER
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      COMMON/PARPAR/NUL,ITERT
      COMMON/REGIME/KREGIM
      CHARACTER*20 FILE04
      LOGICAL KREGIM
      KREGIM =.FALSE.
C
C     APERTURA FILE TAVOLE DEL VAPORE
C
      CALL INITSM
C
      FILE04='proc/f04.dat'
C
      OPEN(UNIT=04,FILE=FILE04,STATUS='OLD',FORM='UNFORMATTED')
C nota: la UNIT 04 possedeva l'attributo SHARED
C
C     LETTURA DATI DA FILE 04
C
      REWIND 04
      READ(04)NBL,NEQAL,NBL1,NVART,NEQSIS,NEQS1,NPVRT,NU,NU1,NVRI
      READ(04)N,N,NST,SIGLA,(NOSL(I),I=1,NST)
C
      READ(04) (NOSUB(I),NOBLC(I,1),NOBLC(I,2),NUSTA(I),NUSCI(I),
     $          NINGR(I),ISLB(I),DUBLOC,I=1,NBL)
      READ(04) (IP(I),I=1,NBL1),(DUMVAR,IPVRS(I),I=1,NVART)
      READ(04) (IPS(I),I=1,NEQS1),(DUMVAR,DUSIVA,IOUSIV,I=1,NEQSIS),
     $          (IPVRT(I),I=1,NPVRT)
      READ(04) (IPI(I),I=1,NU1),(DUMVAR,DUVARI,
     $          IOUVAR,I=1,NU),(IPVRI(I),I=1,NVRI)
C
      READ(04)P0,H0,T0,Q0,R0,AL0,V0,DP0
      READ(04)(XY(I),I=1,NEQSIS),(UU(I),I=1,NU),(XYU(I),I=1,NVART)
      READ(04)NDATI,(IPDATI(I),I=1,NBL1),(DATI(I),I=1,NDATI),
     $      (CNXYU(I),I=1,NVART),(TOLL,I=1,NEQSIS)
C
C     CALCOLO DEL TRANSITORIO
C
      CALL RGDYNS
C
      CLOSE(04)
C
      RETURN
      END
C            
