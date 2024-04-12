C*********************************************************************
C       Fortran Source:             lgtops.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:27:27 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_lgtops_f
      CHARACTER*80  RepoID
      COMMON /CM_lgtops_f / RepoID
      DATA RepoID/'@(#)1,fsrc,lgtops.f,2'/
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

      SUBROUTINE LGTOPS
C
C     DEL PROGRAMMA  LG5
C
C
       include '../main/lg_parameter.fh'
C
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
C*********MEMORIA PER COSTRUIRE LA TOPOLOGIA DELLO JACOBIANO
C
      DIMENSION IRA(M004),IRD(M004),ICDS(M006),ICDB(M006),ICAS(M006),
     $          ICAB(M006),IDJ(N003)
C
      DIMENSION ITITOL(20)
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON/DIMAJA/NRXJC,NCXJC
      COMMON/PARINT/ITITOL,TFIN,TSTEP,FATOLL,INTERR,TINTER
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
      COMMON/INPARV/NQALV,NQSISV
C
      NX1=N001
      NX2=N002
      NX3=N003
      NX4=N004
      NX5=N005
      NX6=N006
      NX7=N007
      NX8=N008
      MX1=M001
      MX2=M002
      MX6=M006
      MX7=M007
      MX8=M008
      MX10=M010
C
C______ RIDUZIONE DEL SISTEMA DI EQUAZIONI DA RISOLVERE
C       A QUELLO EFFETTIVAMENTE DICHIARATO DAI MODULI
C
      CALL TOPRID(NBL,ISLB,NUSTA,NUSCI,NINGR,IPDATI,DATI,IP,
     $            XYU,VAR,NX5,NOBLC,NX2,RNI,AJAC,NX8,NEQSIS,
     $            SIVAR,VARI,NX4,NU,
C_________ uscite della subroutine
     $            VARSYS,NX3,IPVRSV,NQALV,NQSISV,NQMODU,
     $            IPVVSS,IPSSVV,NVART)
C
C______ nel modello ci SONO EQUAZIONI CHE LEGO DEVE RISOLVERE?
C
      IF(NQSISV.EQ.0)RETURN
C
C**   COSTRUZIONE DELLA TOPOLOGIA DELLO JACOBIANO
C
      CALL TOPSIS(IRA,IRD,AJAC,NX8,NBL,ISLB,NUSTA,NUSCI,NINGR,
     $            IPVRSV,ICDS,ICDB,ICAS,ICAB,NQALV,NQSISV,
     $            IPCJ,ICJ,ICBJ,FJ,RIGA,IDJ,NOBLC,NX2,IP,
     $            IPDATI,DATI,XYU,RNI,NQMODU)
C
      RETURN
      END
C            
