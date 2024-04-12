C*********************************************************************
C       Fortran Source:             list1.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Thu Apr 22 09:41:00 2004 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_list1_f
      CHARACTER*80  RepoID
      COMMON /CM_list1_f / RepoID
      DATA RepoID/'@(#)1,fsrc,list1.f,2'/
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

      SUBROUTINE LIST1 (
     $   IGO, NBL, NMBLOC, IP, IPVRS, NMSIVA, IOUSIV, NMVARI,
     $   IOUVAR, NOMF01, LUNF01)
C----------------------------------------------------------------------+
C     SUBROUTINE LIST1
C----------------------------------------------------------------------+
C     descrizione:                                                     |
C------                                                                |
C     attua le operazioni necessarie alla preparazione di un vettore
C     contenente, raggruppata secondo il blocco di origine, la lista:
C     .1) di tutte le variabili del modello che siano state registrate
C         nel corso di un transitorio;
C     .2) delle sole variabili in ingresso del modello;
C     .3) di tutte le variabili del modello.
C                                                                      |
C----------------------------------------------------------------------+
C     argomenti in lista di chiamata:                                  |
C------                                                                |
C     IGO:        codice numerico indicante quale lista si desideri
C                 realizzare (ved. descrizione precedente per 1,2,3)
C     NBL:        contatore dei blocchi (origine record 1 di F04)
C     NMBLOC:   vettore contenente il nome dei blocchi (rec.3/F04)
C     IP:         vettore degli indici di inizio registrazioni per il
C                 blocco di variabili (rec.4/F04)
C     IPVRS:      vettore degli indici delle variabili, organizzato per
C                 blocco; per valori >0 si riferisce a SIVAR e XY,
C                 per valori <0 si riferisce a VARI ed UU.
C     NMSIVA:  vettore contenente il nome e la descrizione delle
C                 variabili del sistema algebrico
C     IOUSIV: vettore
C     NMVARI:   vettore contenente il nome e la descrizione delle
C                 variabili di ingresso
C     IOUVAR:  vettore
C     LUNF01:    contatore degli elementi considerati
C     NOMF01:    vettore contenente la lista prescelta delle
C                 variabili (nome e descrizione)
C                                                                      |
C----------------------------------------------------------------------+
      DIMENSION
     $   IP(*), IPVRS(*), IOUSIV(*), IOUVAR(*)
C------
      CHARACTER*(*)
     $   NMSIVA(*), NMVARI(*), NMBLOC(*), NOMF01(*)
C----------------------------------------------------------------------+
C     Inizio delle istruzioni esecutive di LIST1                     |
C----------------------------------------------------------------------+
C     si determina quale passo operativo deve essere eseguito, per
C     IGO-->1,->2,-->3
C------
      GOTO (9, 99, 999), IGO
C------
C     Realizza quanto definito per il passo n.1: costruisce la lista di
C     tutte le variabili del modello registrate durante un transitorio;
C     le variabili sono raggruppate in funzione del blocco d'origine;
C     terminata la lista, ritorna il controllo al programma chiamante.
C------
9     CONTINUE
C------
      K = 0
C           ! contatore elementi considerati
C------
C-----<<<<<--- start: do I = 1,NBL --->>>>>
      DO 71 I = 1,NBL
         I1 = IP(I)
         I2 = IP(I+1) - 1
C         K = K+1
C         NOMF01(K) = NMBLOC(I)
C                                 ! nome del blocco
         IPO = 0
C---------
         DO 72 J = I1, I2
            JJ = IPVRS(J)
C------------
            IF (JJ .GT. 0) THEN
C------
C     per valori positivi di IPVRS si deve riferire a SIVAR
C------
               IF (IOUSIV(JJ) .EQ. 0) GOTO 1
               K = K+1
               IPO = 1
               NOMF01(K) = NMSIVA(JJ)(1:16)//NMSIVA(JJ)(30:100)
            ELSE
C------
C     per valori negativi di IPVRS si deve riferire a VARI
C------
               JJ = -JJ
               IF (IOUVAR(JJ) .EQ. 0) GOTO 1
               K = K+1
               IPO = 1
               NOMF01(K) = NMVARI(JJ)(1:16)//NMVARI(JJ)(30:100)
            ENDIF
C------------
    1       CONTINUE
C------
   72    CONTINUE
C---------
         IF (IPO .EQ. 0) K = K-1
   71    CONTINUE
C-----<<<<<--- end: do I = 1,NBL --->>>>>
      LUNF01 = K
      RETURN
C------
C------
C     Realizza quanto definito per il passo n.2: costruisce la lista
C     delle variabili di ingresso del modello; le variabili sono
C     raggruppate in funzione del blocco d'origine; al termine della
C     lista, viene ritornato il controllo al programma chiamante.
C------
   99 CONTINUE
C------
      K = 0
C-----<<<<<--- start: do I = 1,NBL --->>>>>
      DO 73 I = 1,NBL
         I1 = IP(I)
         I2 = IP(I+1)-1
C         K = K+1
C         NOMF01(K) = NMBLOC(I)
C                                 ! nome del blocco
         IPAS = 0
C------
         DO 74 J = I1, I2
            JJ = IPVRS(J)
C------
            IF (JJ .LT. 0) THEN
C------
C     riferendosi a VARI si considereranno soltanto valori negativi
C------
               JJ = -JJ
               K = K+1
               IPAS = 1
               NOMF01(K) = NMVARI(JJ)(1:16)//NMVARI(JJ)(30:100)
C------
            ENDIF
C------
   74    CONTINUE
         IF (IPAS .EQ. 0) K = K-1
   73 CONTINUE
C-----<<<<<--- end: do I = 1,NBL --->>>>>
      LUNF01 = K
C------
      RETURN
C------
C     Realizza quanto definito per il passo n.3: costruisce la lista
C     di tutte le variabili del modello; le variabili sono ancora
C     raggruppate in funzione del blocco d'origine; al termine della
C     lista, viene ritornato il controllo al programma chiamante.
C------
  999 CONTINUE
C------
      K = 0
C-----<<<<<--- start: do I = 1,NBL --->>>>>
      DO 75 I = 1,NBL
         I1 = IP(I)
         I2 = IP(I+1) - 1
C         K = K+1
C         NOMF01(K) = NMBLOC(I)
C                                 ! nome del blocco
C------
         DO 76 J = I1, I2
            JJ = IPVRS(J)
C------
            IF (JJ .GT. 0) THEN
C------
C     per valori positivi di IPVRS si deve riferire a SIVAR
C------
               K = K+1
               NOMF01(K) = NMSIVA(JJ)(1:16)//NMSIVA(JJ)(30:100)
            ELSE
C------
C     per valori negativi di IPVRS si deve riferire a VARI
C------
               JJ = -JJ
               K = K+1
               NOMF01(K) = NMVARI(JJ)(1:16)//NMVARI(JJ)(30:100)
            ENDIF
C------
   76    CONTINUE
C------
   75 CONTINUE
C-----<<<<<--- end: do I = 1,NBL --->>>>>
      LUNF01 = K
      RETURN
C----------------------------------------------------------------------+
C     Termine delle istruzioni esecutive di LIST1                      |
C----------------------------------------------------------------------+
      END
C            
