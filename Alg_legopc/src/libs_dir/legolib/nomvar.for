C******************************************************************************
C modulo nomvar.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)nomvar.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE  NOMVAR(NBL,IPUNB,IPUNIN,NLF01,FIL01,
     $                   NEQAL,NMSIVA,NMVARI,NMBLOC,
     $                   IOUSIV,IOUVAR)
C
      CHARACTER*(*) FIL01(*)
      CHARACTER*(*) NMSIVA(*)
      CHARACTER*(*) NMVARI(*)
      CHARACTER*(*) NMBLOC(*)
      CHARACTER*2 FF
      CHARACTER*8 NOIN
      DIMENSION IPUNB(*),IOUSIV(*),IOUVAR(*)
C
      KST=0
      KAL=0
C
C______CARICAMENTO DEI DATI TOPOLOGICI CONTENUTI NELL'AREA FIL01
C      NEI VETTORI DATI 'OLD-LEGO'
C
      DO 500 I=1,NBL
C
      K1=IPUNB(I)
      K2=IPUNB(I+1)-3
      IF(I.GE.NBL)K2=IPUNIN-2
C
      NMBLOC(I)=FIL01(K1)
C
      DO 300 J=K1+1,K2
      FF=FIL01(J)(13:14)
C
      IF(FF.NE.'US')GO TO 200
      KST=KST+1
      NMSIVA(NEQAL+KST)=FIL01(J)(1:16)//'BL.('//FIL01(K1)(1:8)//')'
     $   //FIL01(J)(17:80)
      IOUSIV(NEQAL+KST)=0
      IF(FIL01(J)(10:10).EQ.'*')IOUSIV(NEQAL+KST)=1
      GO TO 300
C
  200 IF(FF.NE.'UA')GO TO 250
      KAL=KAL+1
      NMSIVA(KAL)=FIL01(J)(1:16)//'BL.('//FIL01(K1)(1:8)//')'
     $   //FIL01(J)(17:80)
      IOUSIV(KAL)=0
      IF(FIL01(J)(10:10).EQ.'*')IOUSIV(KAL)=1
      GO TO 300
C
  250 IF(FIL01(J)(18:18).EQ.'#')GO TO 300
              NOIN=FIL01(J)(1:8)
              KL=0
              DO 10 L=IPUNIN+1,NLF01-1
              KL=KL+1
              IF(FIL01(L)(1:8).EQ.NOIN)GO TO 20
   10         CONTINUE
              WRITE(6,*)'ERRORE SUBROUTINE NOMVAR'
   20         NMVARI(KL)=FIL01(J)(1:16)//'BL.('//FIL01(K1)(1:8)//')'
     $                     //FIL01(J)(17:80)
              IOUVAR(KL)=0
      IF(FIL01(J)(10:10).EQ.'*')IOUVAR(KL)=1
  300 CONTINUE
C
C
  500 CONTINUE
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_nomvar
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)nomvar.f	2.1\t7/10/95'/
      END
