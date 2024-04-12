/**********************************************************************
*
*       C Header:               preset_messaggi.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:41:45 1997 %
*
**********************************************************************/

/*
 *  preset_messaggi.h
 *
 *  contiene tutte le stringhe di messaggio del sistema
 *  (divisione per lingua)
 */
#ifndef PRESET_MESSAGGI_H_
#define PRESET_MESSAGGI_H_
/************************************************************************/
char DEFAULT_TITLE[] =   " INIT FROM DEFAULT " ; 
char DEFAULT_INIT[] =    " STATIONARY STATE "; 
char INIT_SIM[] =        " INIZIALIZZAZIONE SIMULATORE ";
char SEL_VAR_TITLE[] =   " File selezionato";
char LOAD_FILESEL[] =    " CARICA FILE ";
char SAVE_FILESEL[] =    " SALVA FILE ";
/************************************************************************/
char OPER_FALLITA[] =    "FALLITA <<<<<";
char FALLITA[] =         ">>>>>      FALLITA      <<<<<";

char ABORTING[] =        "        TERMINE PROGRAMMA        ";
char ERRORE_INIT[] =     " BANCO ISTRUTTORE NON AGGANCIATO ";
char ERRORE_AGGANCIO[] = "  ERRORE CONNESSIONE DISPATCHER  ";
char WARN_CUT_CI[] =	    "    RIMOZIONE C.I. ";
char WARN_REPLACE_CI[] = " SOSTITUZIONE C.I. " ;
char NOT_EXECUTABLE[] =  "    RICHIESTA NON ESEGUIBILE ";
char BAD_STATE[] =       " STATO SIMULATORE NON CONGRUENTE ";
char RESTORE_DEF_CI[] =  " RITORNA ALLA SESSIONE PRECEDENTE ";
char NO_BT_LIST[] =      " Nessun backtrack registrato ";
char ERROR_SIM[] =       " SIMULATORE IN ERRORE ";
char REINIT[] =          " REINIZIALIZZARE IL SIMULATORE ";

char CUT_CI[] =          "Cancellazione C.I. ";
char COPY_CI[] =         "Copiatura C.I. ";
char PASTE_CI[] =        "Paste buffer in C.I. ";
char SAVE_CI[] =         "Snapshot in C.I. ";
char SAVE_BT[] =         "Registrazione B.T. ";
char LOAD_CI[] =         "Caricamento C.I. ";
char LOAD_BT[] =         "Caricamento BT ";
char RUN_SIM[] =         "Commutazione a RUN";
char FREEZE_SIM[] =      "Commutazione a FREEZE";
char BACKTRACK_SIM[] =   "Commutazione a BACKTRACK";
char REPLAY_SIM[] =      "Commutazione a REPLAY";
char STEP_SIM[] =        "Esecuzione STEP";
char CLEAR_SIM[] =       "Reset tempo simulazione e registrazioni";
char DEFAULT_SNAP[] =    "Snapshot di default";
char NEW_STAT_REQ[] =    "Nuova richiesta statistiche";
char NEW_SESSION_NAME[] ="Nuovo titolo sessione";
char READ_SNAP_VIEW[] =  " Lettura dati da snap ";
char READ_BT_VIEW[] =    " Lettura dati da bt ";
char NEW_DELTAT_BT[] =   "Modifica passo reg. BT ";
char NEW_SPEED[] =       "Modifica velocita' simulatore ";
char LAST_BT_READ[] =    "Lettura ultimo B.T. registrato ";
char VALIDATE_BT_OK[] =  "Validazione database caricata da BT ";
char NEW_VAR_CR[] =      "Aggiornamento elenco variabili per registrazione ";
char PROGRAM_ACT[] =     "Programma attivato ";
char SAVE_FILE_CR[] =    "Salva configurazione su file ";
char SAVE_FILE_PREV[] =  "Salva configurazione su file ";
char LOAD_FILE_CR[] =    "Carica configurazione da file ";
char LOAD_FILE_PREV[] =  "Carica configurazione da file ";
char NOT_PERMITTED[] =   "Operazione non permessa";
char OUT_OF_PATH[] =     "Utente non corretto";
char NAME_RESERVED[] =   "File riservato";
char NOT_EXISTENT[] =    "File non esistente";
char NOT_ACCESSIBLE[] =  "File non accessibile";
char VAR_NOT_EXIST[] =   "Variabile non esistente";
char ENTRY_AVAILABLE[] = "<<< ENTRY DISPONIBILE >>>";
char ENTRY_NOT_SEL[] =   "TARGET NON SELEZIONATO";
/************************************************************************/
char RUN_LABEL[] =       "RUN";
char FREEZE_LABEL[] =    "FREEZE";
char STEP_LABEL[] =      "STEP";
/************************************************************************/
char SIMTIME_LABEL[] =   "Tempo sim. ";
char RITARDO_LABEL[] =   "Tempo rit. ";
char SPEED_LABEL[] =     "Velocita'  ";
/************************************************************************/
char DELTAT_REC_BT[] =   "INTERVALLO REGISTRAZIONE BT";
/************************************************************************/
char MALF_SUMMARY[] =    "SOMMARIO MALFUNZIONI ATTIVE";
char FREM_SUMMARY[] =    "SOMMARIO FUNZIONI REMOTE ATTIVE";

char MALF_SCEN_LIST[] =  "LISTA SCENARI MALFUNZIONI";
char FREM_SCEN_LIST[] =  "LISTA SCENARI FUNZIONI REMOTE";
/************************************************************************/
/* labels selVarCr e selVar */
char SYSTEM_LIST[] =     "Sistemi";
char BLOCK_LIST[] =      "Blocchi";
char VAR_TO_SELECT[] =   "Variabili selezionabili";
char VAR_SELECTED[] =    "Variabili selezionate";
char CONF_ACCEPT[] =     "SAVE";
char SELVAR_CONFIRM[] =  "SELECT";
char CONF_DISCARD[] =    "QUIT";
char SELECT_ALL[] =      "Tutte";
char SELECT_VAR[] =      "Seleziona";
char UNSELECT_VAR[] =    "Elimina";
/************************************************************************/
#endif
