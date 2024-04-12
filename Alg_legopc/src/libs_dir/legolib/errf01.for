C******************************************************************************
C modulo errf01.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)errf01.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE ERRF01(ICOD,LG1ERR,DMOD,MAXBLO,LINE,MODBLO,
     $                      ICON,ICB,J,FIL01,NOIN,NOBLO)
      CHARACTER*(*) FIL01(*)
      CHARACTER*32 LG1ERR
      CHARACTER*4 DMOD,MODBLO
      CHARACTER*80 LINE
      CHARACTER*8 NOIN,NOBLO
C
      DATA IPRI/0/
      IF(IPRI.EQ.1)GO TO 1
C
      OPEN(UNIT=37,FILE=LG1ERR,STATUS='UNKNOWN')
      IPRI=1
C
    1 GO TO (10,20,30,40,50,60,70,80,90,100,110,120,130,140),ICOD
C
C      ICOD=1
C
   10 WRITE(37,*)' '
      WRITE(37,*)'!!!!ERRORE!!!!'
      WRITE(37,*)' '
      WRITE(37,*)'      il modulo ',DMOD
      WRITE(37,*)'      definito nei dati topologici'
      WRITE(37,*)'non esiste nella lista dei moduli della libreria LEGO'
      GO TO 300
C
C      ICOD=2
C
   20 WRITE(37,*)' '
      WRITE(37,*)'!!!!ERRORE!!!!'
      WRITE(37,*)' '
      WRITE(37,*)'superato il massimo numero di blocchi ',MAXBLO
      WRITE(37,*)'previsto dalla versione LEGO che stai usando'
      GO TO 300
C
C      ICOD=3
C
   30 WRITE(37,*)' '
      WRITE(37,*)'!!!!ERRORE!!!!'
      WRITE(37,*)' '
      WRITE(37,*)'l''ordine dei dati topologici dei blocchi'
      WRITE(37,*)'e` diverso dall''ordine dei moduli'
      WRITE(37,*)'definiti all''inizio del file.'
      WRITE(37,*)'il blocco ',LINE(1:8),' modulo ',MODBLO
      WRITE(37,*)'e` fuori sequenza'
      GO TO 300
C
C      ICOD=4
C
   40 WRITE(37,*)' '
      WRITE(37,*)'!!!!ERRORE!!!!'
      WRITE(37,*)' '
      WRITE(37,*)'sono stati trovati ',ICON,' moduli '
      WRITE(37,*)'definiti all''inizio del file'
      WRITE(37,*)'mentre sono stati trovati ',ICB,' blocchi'
      GO TO 300
C
C      ICOD=5
C
   50 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile non e` stato(US) uscita(UA) ingresso(IN)'
      GO TO 300
C
C      ICOD=6
C
   60 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile di ingresso (connesso) ',NOIN
      WRITE(37,*)'non compare fra le connessioni'
      GO TO 300
C
C      ICOD=7
C
   70 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile di ingresso ',NOIN,' proviene'
      WRITE(37,*)'dal blocco ',NOBLO,' non presente nei dati'
      GO TO 300
C
C      ICOD=8
C
   80 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile di ingresso ',NOIN,' non e` fra'
      WRITE(37,*)'le uscite del blocco ',NOBLO
      GO TO 300
C
C      ICOD=9
C
   90 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile di ingresso ',NOIN
      WRITE(37,*)'non compare fra gli ingressi del sistema'
      GO TO 300
C
C      ICOD=10
C
  100 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile di ingresso del sistema ',FIL01(J)(1:8)
      WRITE(37,*)'non compare fra gli ingressi dei blocchi '
      GO TO 300
C
C      ICOD=11
C
  110 WRITE(37,*)' '
      WRITE(37,*)'**** TROVATO ERRORE NELLA LINEA ',J,' FILE TOPOLOGIA'
      WRITE(37,*)'>>',FIL01(J)
      WRITE(37,*)' '
      WRITE(37,*)'la variabile di ingresso ',FIL01(J)(1:8)
      WRITE(37,*)'trovata fra le connessioni del sistema'
      WRITE(37,*)'non compare fra le variabili dei blocchi '
      GO TO 300
C
C      ICOD=12
C
  120 WRITE(37,*)' '
      WRITE(37,*)'!!!!ERRORE!!!!'
      WRITE(37,*)' '
      WRITE(37,*)'superato il massimo numero di MODULI ',MAXBLO
      WRITE(37,*)'previsto dalla versione LEGO che stai usando'
      GO TO 300
C
C      ICOD=13
C
  130 REWIND 37
      WRITE(37,*)'NIENTE'
      GO TO 300
C
C      ICOD=14
C
  140 WRITE(37,*)' '
      WRITE(37,*)'!!!!ERRORE!!!!'
      WRITE(37,*)' '
      WRITE(37,*)'Le modifiche che hai apportato alla topologia '
      WRITE(37,*)'hanno dato luogo ad errori che ti sono segnalati '
      WRITE(37,*)'sul tabulato (file: [modello.PROC]LG1.OUT)'
      GO TO 300
  300 RETURN
      END
C
C Procedura contenete la variabile per l'identificazione della versione
C
      SUBROUTINE SCCS_errf01
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)errf01.f	2.1\t7/10/95'/
      END
