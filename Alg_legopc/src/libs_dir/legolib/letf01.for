C******************************************************************************
C modulo letf01.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)letf01.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LETF01(IF01,ICON,ISL,NASL,NST,NOSL,MAXBLO,
     $                   IPUNB,FIL01,IER,LG1ERR,MODEL,IPUNIN,
     $                   NLF01)
C
C_____________ LETTURA DEL FILE F01 DELLA TOPOLOGIA DEL MODELLO E
C              CONTROLLI SUI DATI
C
C
      DIMENSION NASL(*),ISL(*),NOSL(*),IPUNB(*)
C
      CHARACTER*(*) FIL01(*)
C
      CHARACTER*32 LG1ERR
      CHARACTER*30 ERR1,ERR2
      CHARACTER*4 IBL,ING,IMAG,IBLOC,ISI,ILAB,ISTAR,DMOD,BLOC,MODBLO
      CHARACTER*80 LINE
      CHARACTER*6 TP,IUA,IUS,IIN
      CHARACTER*1 TC
      CHARACTER*8 NOIN,NOBLO,MODEL
C
      DATA ISTAR/'****'/,IBL/' '/
C
      DATA ING/'--IN'/
      DATA IMAG/'>>>>'/
      DATA ILAB/'BL.-'/
      DATA IBLOC/'BLOC'/
      DATA ISI/'SI'/
      DATA IUA/'--UA--'/
      DATA IUS/'--US--'/
      DATA IIN/'--IN--'/
C
C     LETTURA DEL FILE F01.DAT
C
      WRITE(6,7000)
 7000 FORMAT(///10X,'PROGRAMMA  LG1 - ACQUISIZIONE DELLA TOPOLOGIA'
     $         /10X,'                 DEL MODELLO '//)
C
      WRITE(6,7001)
 7001 FORMAT(///10X,'STAMPA DEL FILE F01'///)
C
      IER=0
      IL=0
      ICB=0
      IPUNIN=0
C
      REWIND IF01
  100 READ(IF01,1000,END=222)LINE
 1000 FORMAT(A)
      WRITE(6,7002)LINE
 7002 FORMAT(1X,A)
C
      IL=IL+1
      FIL01(IL)=LINE
      DMOD=LINE(1:4)
      BLOC=LINE(11:14)
C
C_______ LETTURA DEL NOME DEL MODELLO
C
      IF(LINE(1:4).NE.'****'.AND.LINE(11:16).EQ.'      ') THEN
         MODEL=LINE(1:8)
      ENDIF
C
C______DEFINIZIONE PUNTATORE AGLI INGRESSI DEL SISTEMA
C
      IF(BLOC.EQ.IMAG)IPUNIN=IL
C
C______DEFINIZIONE PUNTATORE ALLE VARIABILI CONNESSE DEL SISTEMA
C      OVVERO LA FINE DEL FILE UTILE DELLA TOPOLOGIA
C
      IF(DMOD.EQ.ISTAR.AND.IL.GT.IPUNIN)IPUNCN=IL
C
C________ SE SI TRATTA DELLE PRIME LINEE CHE DESCRIVONO QUALI SONO I
C         BLOCCHI DEL MODELLO FACCIO UNA SERIE DI CONTROLLI
C
      IF(BLOC.EQ.IBLOC)THEN
C
C========== CONTROLLI SUI BLOCCHI
C
         READ(DMOD,'(A4)') IDMOD
C
C_____DETERMINAZIONE DEL PUNTATORE DEL MODULO VERSO
C     LA LISTA DEI MODULI DI LIBRERIA
C
         DO 700 J=1,NST
         IF(NOSL(J).EQ.IDMOD)GO TO 112
  700    CONTINUE
C
C______________________ ERRORE _______________
         IER=1
C
         ICOD=1
         CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
         ERR1='Trovato un modulo non presente'
         ERR2='nella libreria'
C
      PRINT *,' '
      PRINT *,'!!!!ERRORE!!!!'
      PRINT *,' '
      PRINT *,'      il modulo ',DMOD
      PRINT *,'      definito nei dati topologici'
      PRINT *,'non esiste nella lista dei moduli della libreria LEGO'
C
         GO TO 100
C
  112    IMOD=J
C
         ICON=ICON+1
C
C_________ CONTROLLO SUL NUMERO DEI BLOCCHI < MAXBLO
C
         IF(ICON.LT.MAXBLO)GO TO 111
C_______________ERRORE_________________________
C
         IER=1
         ICOD=2
         CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
         ERR1='Superato il massimo numero'
         ERR2='di blocchi utilizzabili'
C
      PRINT *,' '
      PRINT *,'!!!!ERRORE!!!!'
      PRINT *,' '
      PRINT *,'superato il massimo numero di blocchi ',MAXBLO
      PRINT *,'previsto dalla versione LEGO che stai usando'
C
      GO TO 1999
C
  111 CONTINUE
         ISL(ICON)=IMOD
         NASL(ICON)=IDMOD
         GO TO 100
      ENDIF
C
C______DEFINIZIONE PUNTATORE AI DATI DEI BLOCCHI
C
      IF(BLOC.NE.ILAB)GO TO 100
C
C_____ STO LEGGENDO I DATI DEI BLOCCHI
      ICB=ICB+1
      IPUNB(ICB)=IL
C
C______CONTROLLO SULLA SEQUENZA DEI BLOCCHI
C
      MODBLO=LINE(33:36)
      READ(MODBLO,'(A4)') IMODBL
      IF(IMODBL.EQ.NASL(ICB))GO TO 100
C______________________ ERRORE _______________
      IER=1
C
      ICOD=3
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
      ERR1='Trovato errore nella sequenza'
      ERR2='della definizione dei blocchi'
C
      PRINT *,' '
      PRINT *,'!!!!ERRORE!!!!'
      PRINT *,' '
      PRINT *,'l''ordine dei dati topologici dei blocchi'
      PRINT *,'e` diverso dall''ordine dei moduli'
      PRINT *,'definiti all''inizio del file.'
      PRINT *,'il blocco ',LINE(1:8),' modulo ',MODBLO
      PRINT *,'e` fuori sequenza'
C
      GO TO 100
C
C
  222 CONTINUE
      NLF01=IL
      IPUNB(ICB+1)=IPUNIN+1
C
      IF(IL.EQ.0)RETURN
      IF(ICON.LE.0)GO TO 1999
C
      IF(ICB.NE.ICON)THEN
C______________________ ERRORE _______________
      IER=1
C
      ICOD=4
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
      ERR1='Trovato errore di sequenza'
      ERR2='dei moduli rispetto ai blocchi'
C
      PRINT *,' '
      PRINT *,'!!!!ERRORE!!!!'
      PRINT *,' '
      PRINT *,'sono stati trovati ',ICON,' moduli '
      PRINT *,'definiti all''inizio del file'
      PRINT *,'mentre sono stati trovati ',ICB,' blocchi'
      GO TO 1999
C
      ENDIF
C
C================ CONTROLLI GENERALI SUI DATI TOPOLOGICI ==========
C
      IER2=0
      DO 300 I=1,ICON
      IP1=IPUNB(I)+1
      IP2=IPUNB(I+1)-3
      DO 210 J=IP1,IP2
C_____________ CONTROLLO CHE LA VARIABILE DI UN MODULO SIA
C              STATO,USCITA,INGRESSO
      TP=FIL01(J)(11:16)
      IF(TP.NE.IUA.AND.TP.NE.IUS.AND.TP.NE.IIN)THEN
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=5
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile non e` stato(US) uscita(UA) ingresso(IN)'
      GO TO 210
C
      ENDIF
C
      IF(TP.NE.IIN)GO TO 210
C
      TC=FIL01(J)(18:18)
      IF(TC.NE.'#')GO TO 202
      TC=FIL01(J)(19:19)
      IF(TC.EQ.' ')GO TO 210
C_________ INGRESSO CONNESSO >> controllo che figuri fra le connesssioni
      NOIN=FIL01(J)(19:26)
      DO 800 KK=IPUNCN,NLF01
      IF(FIL01(KK)(1:8).EQ.NOIN)GO TO 201
  800 CONTINUE
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=6
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile di ingresso (connesso) ',NOIN
      PRINT *,'non compare fra le connessioni'
      GO TO 210
  201 FIL01(KK)(9:9)='?'
C_________________ CONTROLLO CHE ESISTA L'USCITA CORRISPONDENTE
C
      NOIN=FIL01(J)(1:8)
      NOBLO=FIL01(J)(52:59)
      DO 204 KI=1,ICON
      IP=IPUNB(KI)
      IF(NOBLO.EQ.FIL01(IP)(1:8))GO TO 206
  204 CONTINUE
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=7
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile di ingresso ',NOIN,' proviene'
      PRINT *,'dal blocco ',NOBLO,' non presente nei dati'
      GO TO 210
C
  206 IP1=IP+1
      IP2=IPUNB(KI+1)-3
      DO 205 KJ=IP1,IP2
      IF(FIL01(KJ)(1:8).EQ.NOIN)GO TO 210
  205 CONTINUE
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=8
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile di ingresso ',NOIN,' non e` fra'
      PRINT *,'le uscite del blocco ',NOBLO
      GO TO 210
C
  202 CONTINUE
C_______ INGRESSO >> controllo che figuri fra gli ingressi del modello
      NOIN=FIL01(J)(1:8)
      DO 801 KK=IPUNIN,IPUNCN
      IF(FIL01(KK)(1:8).EQ.NOIN)GO TO 203
  801 CONTINUE
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=9
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile di ingresso ',NOIN
      PRINT *,'non compare fra gli ingressi del sistema'
      GO TO 210
  203 FIL01(KK)(9:9)='?'
C
  210 CONTINUE
  300 CONTINUE
C
C_____________CONTROLLO CHE TUTTI GLI INGRESSI DEL SISTEMA
C             SIANO STATI RITROVATI COME INGRESSI DEI BLOCCHI
C
      I1=IPUNIN+1
      I2=IPUNCN-1
      DO 350 J=I1,I2
      IF(FIL01(J)(9:9).EQ.'?')GO TO 350
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=10
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile di ingresso del sistema ',FIL01(J)(1:8)
      PRINT *,'non compare fra gli ingressi dei blocchi '
  350 CONTINUE
C
C_____________CONTROLLO CHE TUTTE LE CONNESSIONI DEL SISTEMA
C             SIANO STATE RITROVATE NEI BLOCCHI
C
      I1=IPUNCN+1
      I2=NLF01
      DO 360 J=I1,I2
      IF(FIL01(J)(9:9).EQ.'?')GO TO 360
C__________________ ERRORE
      IER=1
      IER2=1
      ICOD=11
      CALL ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
C
      PRINT *,' '
      PRINT *,'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      PRINT *,'>>',FIL01(J)
      PRINT *,' '
      PRINT *,'la variabile di ingresso ',FIL01(J)(1:8)
      PRINT *,'trovata fra le connessioni del sistema'
      PRINT *,'non compare fra le variabili dei blocchi '
  360 CONTINUE
C
      IF(IER2.EQ.1)THEN
        ERR1='Trovati errori nei dati'
        ERR2=' '
      ELSE
        RETURN
      ENDIF
 1999 CONTINUE
C
C_______ LA FINE DEL FILE COINCIDE CON L'INIZIO DELLA CONNESSSIONI
C
      NLF01=IPUNCN
C
      RETURN
      END
C
C Procedura contenete la variabile per l'identificazione della versione
C
      SUBROUTINE SCCS_letf01
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)letf01.f	2.1\t7/10/95'/
      END
