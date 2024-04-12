C******************************************************************************
C modulo inizbl.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)inizbl.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE INIZBL(ISLB,IPDATI,DATI,IP,XYU,IPVRS,NOBLC,MX3,
     $                     NUSTA,NUSCI,NVART)
      DIMENSION ISLB(*),IPDATI(*),DATI(*),IP(*),
     $                  XYU(*),IPVRS(*),NOBLC(MX3,2),NUSTA(*),NUSCI(*)
      COMMON/NORM/P0,H0,T0,Q0,RO0,AL0,V0,DP0
C
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
      DIMENSION NUL(7)
      COMMON/PARPAR/NUL,ITERT
      COMMON/NEQUAZ/NEQMOD
      COMMON/BLOSE/NBLSE
C_________ NBLSE = NUMERO DI BLOCCHI SENZA EQUAZIONI
C
C     INIZIALIZZAZIONE DELLE VARIABILI DI INGRESSSO E DI USCITA
C     DEI BLOCCHI CHE NON HANNO EQUAZIONI
C
      M=0
      IFUN=2
C
C______ ITERT=-1 DICE AI BLOCCHI SENZA EQUAZIONI CHE POSSONO EFFETTUARE
C       IL CALCOLO DI INIZIALIZZAZIONE
C
      ITERT=-1
C
      DO 600 IJ=1,NBLSE
      DO 500 I=1,NBLSE
      K=ISLB(I)
      IPD=IPDATI(I)
      IXYU=IP(I)
      I1=IP(I)
      I2=IP(I+1)-1
      NE=NUSTA(I)+NUSCI(I)
      NOBL1=NOBLC(I,1)
      NOBL2=NOBLC(I,2)
C
      CALL MODC1(K,IFUN,AJAC,1,IXYU,XYU,IPD,DATI,RNI,NOBL1,NOBL2)
C
C     TRASFERIMENTO DELLE VARIABILI DI USCITA
C     DI UN BLOCCO SENZA EQUAZIONI VERSO TUTTI I BLOCCHI
C     A CUI E` CONNESSO
C
        DO 71 L=1,NE
        J=I1+L-1
        KI=IPVRS(J)
          DO 72 JJ=1,NVART
            IF(J.NE.JJ) THEN
              IF(IPVRS(JJ).EQ.KI)XYU(JJ)=XYU(J)
            ENDIF
   72     CONTINUE
   71   CONTINUE
  500 CONTINUE
  600 CONTINUE
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_inizbl
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)inizbl.f	2.1\t7/10/95'/
      END
