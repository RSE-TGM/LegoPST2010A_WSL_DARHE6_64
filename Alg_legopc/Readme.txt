#
# Note sulla versione Alg_legopc-2006ASP1_RHE4_jurij
#
# Paderno J. aprile 2007
#


#
# Modifiche implementate
#

- Migliorata la gestione degli errori. (Esistono ancora margini di miglioramento)
     o- File modificati: legopc.tix vers. 6, pag2f01.c vers. 1.3, cad_crealg1.sh vers. 11

- Migliorata la gestione dei grafici in fase di steady state (-> plot trends)
     o- File modificati: draw2gr.tcl vers. 4

- Modificata la funzione di lettura della pipe di dialogo con vorwahl2 in fase di preistanziazione
     o- File modificati: prefirst.tix vers. 3

- Corretto bug che non permetteva di aprire librerie aventi nome della cartella minuscolo (default versione
  Linux) e nome del file .lib contenente lettere maiuscole (come spesso accade nella versione Windows)
     o- File modificati: preinst2.tix vers. 4

- Eliminata la necessità di utilizzare il file lg1_done.out come flag per indicare il buon fine della
  fase di creazione dei file f01.dat e f14.dat. Il touch di tale file causava malfunzionamenti in legocad.
     o- File modificati: read_f01.tcl vers. 5, cad_crealg1.sh vers. 11, legopc.tix vers. 6

- Corretto bug che causava un errore nella scrittura del file temporaneo sca1.tmp nel caso in cui questo
  fosse già presente
     o- File modificati: vorwahl2.for vers. 2

- Creato il file Makefile.mk (in LegoPC/lego) che copia i file rerunlg2.mak e rerunlg2.bat necessari alla
  versione Windows di LegoPC.
     o- File modificati: Makefile.mk * (in LegoPC/lego) vers. 2, Makefile.mk vers. 3 (LegoPC)

- Effettuato porting in Linux dei file rerunlg2.mak (-->rerunlg2.mk) e rerunlg2.bat (-->rerunlg2.sh). Tuttavia
  il loro utilizzo in readf01.tcl è stato sostituito da cad_crealg1 che sfrutta le potenzialità del make
     o- File modificati: readf01.tcl vers. 5, rerunlg2.mk * vers. 1, rerunlg2.sh * vers. 1

- Corretto bug che non consentiva la compilazione di modelli contenuti in una cartella il cui percorso 
  assoluto contiene lettere maiuscole
     o- File modificati: pag2f01.c vers. 1.3


#
# Modifiche da apportare in futuro
#

- Se possibile, utilizzare il Drag&Drop per l'istanziazione di un nuovo modulo in una topologia.

- Se nella topologia è presente una variabile non legata ad alcuna equazione del sistema, la compilazione
  dà l'errore "child process exited abnormally", mentre nel file .out viene data un'informazione più
  utile (anche se perfezionabile). Si potrebbe migliorare il messaggio d'errore visualizzato.

- Se possibile, gestire le modifiche alla topologia con un approccio che comprenda il concetto di selezione
  in modo tale da poter spostare più oggetti contemporaneamente.

- I differenti valori di errore restituiti da cad_crealg1.sh non vengono utilizzati dal codice tcl perché 
  la funzione catch [exec ...] restituisce 1 per qualsiasi valore restituito diverso da 0. 

- Superate le 10 istanziazioni di un modulo l'algoritmo di preistanziazione riparte dall'istanziazione 2.

- C'è un problema sconosciuto nel funzionamento di proc/lg2: In caso di malfunzionamento non viene scritto 
  il file lgerr.out e la funzione che utilizza tale file per verificarne il comportamento non trovando il
  file genera un errore di dubbia comprensibilità. 
     o- Per replicare l'errore modificare il file f14.dat in fase di Data Assignment e salvare. Dopodiché
        lanciare Compute Steady State e, infine, cliccare su Execute Drift

- Talvolta accade che, terminata la fase di "First phase" durante la preistanziazione, la finestra di dialogo
  non si chiude.


