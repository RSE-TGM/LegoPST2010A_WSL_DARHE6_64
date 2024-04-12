C******************************************************************************
C modulo scanf04.f
C tipo 
C release 1.0
C data 10/3/95
C reserved @(#)rg5sim.f	1.0
C******************************************************************************

      SUBROUTINE SCANF04(NUSCI, IP, IPS, IPVRT, IPI, IPVRI,
     $                   XY, UU, XYU, DATI, IPDATI)
C
      DIMENSION NUSCI(*),IP(*),IPS(*),IPVRT(*),IPI(*),IPVRI(*),
     $          XY(*),UU(*),XYU(*),DATI(*),IPDATI(*)
C
C**************DATI GENERALI
C
      DIMENSION NOSL(1),NOSUB(1),NOBLC(1,2),NUSTA(1),
     $          NINGR(1),ISLB(1),IPVRS(1),
     $          CNXYU(1),
     $          AJAC(1,1)
C
      CHARACTER*100 DUSIVA
      CHARACTER*100 DUVARI
      CHARACTER*80  DUBLOC
      CHARACTER*8 SIGLA, DUMVAR
      DIMENSION ITITOL(20),NUL(7)
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      COMMON/PARPAR/NUL,ITERT
      CHARACTER*20 FILE04
C
      FILE04='proc/f04.dat'
C
      OPEN(UNIT=04,FILE=FILE04,STATUS='OLD',FORM='UNFORMATTED')
C nota: la UNIT 04 possedeva l'attributo SHARED
C
C     LETTURA DATI DA FILE 04
C
C
      WRITE(6,*)'rewinding f04...'
C
      REWIND 04
      READ(04)NBL,NEQAL,NBL1,NVART,NEQSIS,NEQS1,NPVRT,NU,NU1,NVRI
      WRITE(6,*)'NU=',NU
      WRITE(6,*)'NU1=',NU1
      WRITE(6,*)'NVRI=',NVRI
      READ(04)N,N,NST,SIGLA,(NOSL(1),I=1,NST)
C
      READ(04) (NOSUB(1),NOBLC(1,1),NOBLC(1,2),NUSTA(1),NUSCI(I),
     $          NINGR(1),ISLB(1),DUBLOC,I=1,NBL)
      WRITE(6,*)'NUSCI read'
      READ(04) (IP(I),I=1,NBL1),(DUMVAR,IPVRS(1),I=1,NVART)
      WRITE(6,*)'IP read'
      READ(04) (IPS(I),I=1,NEQS1),(DUMVAR,DUSIVA,IOUSIV,I=1,NEQSIS),
     $          (IPVRT(I),I=1,NPVRT)
      WRITE(6,*)'IPS-IPVRT read'
      WRITE(6,*)'IPS(0)-IPVRT(0)',IPS(1),IPVRT(1)
      WRITE(6,*)'NU,NU1,NVRI',NU,NU1,NVRI
      READ(04) (IPI(I),I=1,NU1),(DUMVAR,DUVARI,
     $          IOUVAR,I=1,NU),(IPVRI(I),I=1,NVRI)
      WRITE(6,*)'IPI-last read',IPI(NU1)
      WRITE(6,*)'IPVRI-last read',IPVRI(NVRI)
C
      READ(04)P0,H0,T0,Q0,R0,AL0,V0,DP0
      READ(04)(XY(I),I=1,NEQSIS),(UU(I),I=1,NU),(XYU(I),I=1,NVART)
      READ(04)NDATI,(IPDATI(I),I=1,NBL1),(DATI(I),I=1,NDATI),
     $      (CNXYU(1),I=1,NVART),(TOLL,I=1,NEQSIS)
C
      WRITE(6,*)'closing f04...'
C
C
      CLOSE(04)
C
      WRITE(6,*)'closed f04...'
C
      RETURN
      END
C
C     PRIMA SCANSIONE F04
C
      SUBROUTINE FETCH04
C
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      CHARACTER*20 FILE04
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
C
      FILE04='proc/f04.dat'
C
C
      WRITE(6,*)'opening f04...'
C
      OPEN(UNIT=04,FILE=FILE04,STATUS='OLD',FORM='UNFORMATTED')
C nota: la UNIT 04 possedeva l'attributo SHARED
C
C     LETTURA DATI DA FILE 04
C
      WRITE(6,*)'rewinding f04...'
C
      REWIND 04
      READ(04)NBL,NEQAL,NBL1,NVART,NEQSIS,NEQS1,NPVRT,NU,NU1,NVRI
      READ(04)N,N,NST,SIGLA,(N,I=1,NST)
C
      READ(04) (N,N,N,N,N,
     $          N,N,N,I=1,NBL)
      READ(04) (N,I=1,NBL1),(DUMVAR,N,I=1,NVART)
      READ(04) (N,I=1,NEQS1),(DUMVAR,DUSIVA,IOUSIV,I=1,NEQSIS),
     $          (N,I=1,NPVRT)
      READ(04) (MIP,I=1,NU1),(DUMVAR,DUVARI,
     $          IOUVAR,I=1,NU),(N,I=1,NVRI)
      WRITE(6,*)'IPI-last read',MIP
      WRITE(6,*)'NVRI=',NVRI
      WRITE(6,*)'IPVRI-last read',N
C
      READ(04)P0,H0,T0,Q0,R0,AL0,V0,DP0
      READ(04)(X,I=1,NEQSIS),(X,I=1,NU),(X,I=1,NVART)
      READ(04)NDATI
C
      WRITE(6,*)'closing f04...'
C
C
      CLOSE(04)
C
      WRITE(6,*)'closed f04...'
      WRITE(6,*)'KREGIM = ',KREGIM
C
      RETURN
      END
C
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_scanf04
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)scanf04.f 1.0\t10/3/95'/
      END
