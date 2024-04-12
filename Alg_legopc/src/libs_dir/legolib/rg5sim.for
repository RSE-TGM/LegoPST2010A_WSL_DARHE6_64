C******************************************************************************
C modulo rg5sim.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)rg5sim.f	2.1
C******************************************************************************
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
C      INCLUDE 'LG5_PARAMETER.F'
C**   Descrizione delle parameter di LG5
C**
C**   N000= MOLTIPLICATORE
C**
C**   N001= N. MODULI
C**   N002= N. BLOCCHI
C**   N003= N.STATI+ALG. = ORDINE MASSIMO SISTEMA ALGEBRICO
C**   N004= N. INGRESSI
C**   N005= N. VARIABILI
C**   N006= N. VAR. DI 1 BLOCCO
C**   N007= N. DI DATI
C**   N008= N. DI EQUAZIONI DI UN BLOCCO
C**   NR00= N. DI TERMINI #0 PER OGNI EQUAZIONE
C**   NP00= N. DI PERTURBAZIONI
C
      PARAMETER (N000=70, N001=N000*10, N002=N000*25, N003=N000*50,
     $           N004=N000*25, N005=N000*100, N006=100,
     $           N007=N000*500, N008=40, NR00=12, NP00=10)
C
      PARAMETER (M003 = N002+1, M004 = N003+1, M005 = N004+1,
     $           M001 = N005-N003, M002 = M001-N004)
C
C**      M006 = N. TERMINI # 0 DELLO JACOBIANO
C**      M007 = N. TERMINI # 0 DELLO JACOBIANO FATTORIZZATO
C**      M010 = N.VARIABILI IN OUTPUT
C
      PARAMETER (M006 = N003*NR00, M007 = 2*M006, M008 = 5*N003,
     $           M009 = 8*N003, M010 = N004+N003, MP01 = NP00+1,
     $           MP02 = NP00*200)
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
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_rg5sim
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)rg5sim.f	2.1\t7/10/95'/
      END
