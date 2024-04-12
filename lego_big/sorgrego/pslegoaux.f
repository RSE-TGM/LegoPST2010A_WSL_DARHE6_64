C******************************************************************************
C  modulo pslegoaux.f
C  tipo 
C  release 1.6
C  data 11/15/95
C  reserved @(#)pslegoaux.f	1.6
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGBL1(NV,IPN,IPM,XLG,XBL)
      DIMENSION IPN(*),IPM(*),XLG(*),XBL(*)
C
C     TRASFERISCE IL CONTENUTO DEL VETTORE XLG (VARIAB.DEL SISTEMA)
C     NEL VETTORE XBL (VARIABILI DI OGNI BLOCCO)
C     USANDO LA MATRICE DI COLLEGAM. INVERSA IPN,IPM
C
      DO 10 I=1,NV
      I1=IPN(I)
      I2=IPN(I+1)-1
      IF(I2.LT.I1)GO TO 10
      DO 5 J=I1,I2
      K=IPM(J)
      XBL(K)=XLG(I)
    5 CONTINUE
   10 CONTINUE
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_pslegoaux
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)pslegoaux.f	1.6\t11/15/95'/
      END

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO diversificato per singola / doppia precisione         C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGGILINE(INIZ,IUNIT,FILIN,LINE,IERR)
C
      CHARACTER*32  FILIN
      CHARACTER*132  LINE
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C
      COMMON/PARPAR/NUL(7),ITERT
      COMMON/NEQUAZ/NEQMOD
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
C
      IERR=0
      IF(INIZ.EQ.1) THEN
C
       OPEN(UNIT=IUNIT,FILE=FILIN,STATUS='OLD')
C
       RETURN      
      ENDIF
C
C      LETTURA DI UNA LINEA DI UN FILE ASCII  DI 132 CAR.
C
      READ(IUNIT,1000,ERR=10,END=20)LINE
 1000 FORMAT(A)
      RETURN
C
C     ERRORI
C
 10   WRITE(6,*)'  SUB. LEGGILINE :ERRORE NELLA LETTURA DEL FILE'
      WRITE(6,*)'  ',FILIN
      IERR=1
      RETURN
 20   WRITE(6,*)'  SUB. LEGGILINE :TROVATO END OF FILE' 
      WRITE(6,*)'  ',FILIN
      IERR=2
      RETURN
      END

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO diversificato per singola / doppia precisione         C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE  SCRIVIF04(NOMF04,N002,NBL,NVART,NEQSIS,NPVRT,NU,NVRI,
     $       SIGLA,NOSUB,NOBLC,NUSTA,NUSCI,NINGR,ISLB,NMBLOC,
     $       IP,VAR,IPVRS,IPS,IPVRT,IPI,IPVRI,XY,UU,XYU,
     $       NDATI,IPDATI,DATI,NMSIVA,NMVARI)
C
C
C
      DIMENSION 
     $       NOSUB(*),NOBLC(N002,*),NUSTA(*),NUSCI(*),
     $       NINGR(*),ISLB(*),
     $       IP(*),IPVRS(*),
     $       IPS(*),IPVRT(*),
     $       IPI(*),IPVRI(*),
     $       XY(*),UU(*),XYU(*),
     $       IPDATI(*),DATI(*)
      CHARACTER*100 NMSIVA(*), NMVARI(*)
      CHARACTER*80 NMBLOC(*)
      CHARACTER*8 VAR(*)
      CHARACTER*32 NOMF04
      CHARACTER*8 SIGLA
C
      CHARACTER*8 STR8DUMMY
      CHARACTER*100 STR100DUMMY
      IDUMMY=0
      DUMMY=1.
C
      STR100DUMMY(1:9)='CIAOCIAO '
C
      XP0=20000000.
      XH0=1000000.
      XT0=1000.
      XQ0=1000.
      XR0=100.
      XAL0=10.
      XV0=50.
      XDP0=100000.
C
      NBL1=NBL+1
      NEQAL=NEQSIS
      NEQS1=NEQSIS+1
      NU1=NU+1
C
C     SCRITTURA DEL FILE 04 CONNESSIONE LEGO3 - LEGO4
C
      CLOSE(4)
      OPEN(UNIT=4,FILE=NOMF04,FORM='UNFORMATTED',STATUS='UNKNOWN')
C
      REWIND 4
      WRITE(4)NBL,NEQAL,NBL1,NVART,NEQSIS,NEQS1,NPVRT,NU,NU1,NVRI
      WRITE(4)IDUMMY,IDUMMY,NBL,SIGLA,(NOSUB(I),I=1,NBL)
      WRITE(4)(NOSUB(I),NOBLC(I,1),NOBLC(I,2),NUSTA(I),NUSCI(I),
     &       NINGR(I),ISLB(I),NMBLOC(I),I=1,NBL)
      WRITE(4)(IP(I),I=1,NBL1),(var(I),IPVRS(I),I=1,NVART)
      WRITE(4)(IPS(I),I=1,NEQS1),(STR8DUMMY,NMSIVA(I),
C     WRITE(4)(IPS(I),I=1,NEQS1),(STR8DUMMY,STR100DUMMY,
     &        IDUMMY,I=1,NEQSIS),(IPVRT(I),I=1,NPVRT)
      WRITE(4)(IPI(I),I=1,NU1),(STR8DUMMY,NMVARI(I),
C     WRITE(4)(IPI(I),I=1,NU1),(STR8DUMMY,STR100DUMMY,
     &        IDUMMY,I=1,NU),(IPVRI(I),I=1,NVRI)
C
      WRITE(4)XP0,XH0,XT0,XQ0,XR0,XAL0,XV0,XDP0
      WRITE(4)(XY(I),I=1,NEQSIS),(UU(I),I=1,NU),(XYU(I),I=1,NVART)
      WRITE(4)NDATI,(IPDATI(I),I=1,NBL1),(DATI(I),I=1,NDATI)
     &            ,(DUMMY,I=1,NVART),(DUMMY,I=1,NEQSIS)
      WRITE(4) DUMMY
C
      RETURN
      END
