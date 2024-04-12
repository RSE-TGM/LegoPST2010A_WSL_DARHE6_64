C******************************************************************************
C modulo cercno.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)cercno.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE CERCNO(IP,NBL1,IPVRS,NOBLC,NX2,VAR,NX5,CNXYU,
     $                  NVART,K,L,ICRAC)
C
C  controlla che le costanti di normalizzazione di variabili
C  "legate" (sia nel senso uscita-ingresso che ingresso di
C  sistema comune a piu' blocchi) siano coincidenti.
C
C  ICRAC = 0 : OK , ICRAC = 1 : ERRORE cnxyu incongruenti.
C
C  Se ICRAC=1 segnala le incongruenze e continua l'esecuzione.
C
C  IP , IPVRS   vettori di collegamento blocchi - LEGO
C  NOBLC , VAR  nomi blocchi e variabili
C  K            ipvrs(i) gia' esaminati
C  L            indici variabili legate
C
      DIMENSION IP(*),IPVRS(*),CNXYU(*),K(*),L(*),
     $           NOBLC(NX2,*)
      CHARACTER*8 VAR(NX5)
C
      KM=0
      IER=0
      ICRAC=0
C
      DO 100 I=1,NVART-1
      IT=IPVRS(I)
      IF(I.EQ.1) GOTO 20
C
      DO 10 IK=1,KM
   10 IF(IT.EQ.K(IK)) GOTO 100
C                              (variabile gia' esaminata)
C
   20 KM=KM+1
      K(KM)=IT
C
      LM=1
      L(LM)=I
C             (inizializza variabili "legate")
C
      DO 50 J=I+1,NVART
      IF(IT.NE.IPVRS(J)) GOTO 50
      LM=LM+1
C             (variabile legata)
      L(LM)=J
C             ! IPVRS(I) = IPVRS(J)
      IF(CNXYU(J).NE.CNXYU(I)) IER=1
50      CONTINUE
C
      IF(IER.EQ.0) GOTO 100
C
      WRITE(90,1001)
 1001 FORMAT(//'  LG - ERRORE : INCONGRUENZA COSTANTI DI NORMALIZZ.',
     $       //'       BLOCCO      VARIABILE      NORMALIZZAZIONE'/)
C
      DO 80 J=1,LM
      INOW=L(J)
      DO 60 JB=2,NBL1
   60 IF(IP(JB).GT.INOW) GOTO 70
      WRITE(90,*) '  LG - ERRORE IN CERCNO  INOW = ',INOW
      CALL LGABRT
   70 JB=JB-1
C               (N. blocco variabile INOW)
C
   80 WRITE(90,1002) NOBLC(JB,1),NOBLC(JB,2),VAR(INOW),CNXYU(INOW)
 1002 FORMAT(7X,2A4,4X,A8,6X,E12.5)
      IER=0
      ICRAC=1
  100 CONTINUE
      IF (ICRAC.EQ.1) THEN
        WRITE(90,*) ' LG - FATAL ERROR'
        CALL LGABRT
      ENDIF
      RETURN
      END
