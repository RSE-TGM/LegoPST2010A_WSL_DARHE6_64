/**********************************************************************
*
*       C Header:               legomain.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:01:36 1996 %
*
**********************************************************************/
/*
 legomain.h
*/
/*
 Definizioni utilizzate all'interno del main di legocad
*/
#define SCELTO 1
#define NON_SCELTO 0
/* definizioni utilizzate per la gestione del foraus
   (ved. Foraus.c)
*/
#define SAVE_TMP_FORAUS  90
#define SAVE_FORAUS      91
#define EDIT_FORAUS      92
#define VIEW_FORAUS      93
#define REMOVE_FORAUS    94 /* elimina dalla memoria una sezione di fortran */
#define DELETE_FORAUS    95 /* cancellazione file foraus.for */
#define MIN_LEN_RIGA    100
#define PATTERN "C~FORAUS_"
#define FILE_TMP_NAME "foraustmp.f"
#define FILE_FORAUS   "foraus.for"

#define EDIT_DESCR 80
#define VIEW_DESCR 81

/* definizioni utilizzate per descrizione modello
   ( ved. form4 )
*/
#define FILEDESCR "descr.dat"

/*        
 Definizioni utilizzate per la conferma sulle operazioni
*/
#define Q_DELETE_MODEL            1
#define Q_OVERWRITE_FILEOUTEDI14  2
#define Q_OVERWRITE_COPY_MODEL    3
/*
 Definizioni utilizzate per la gestione della interfaccia di   
 selezione del modello (select model o riordino )
*/
#define SELECT_MODEL   1
#define REORDER_MODEL  2
 
/*
 Definizioni utilizzate per fileSelection di edi14
*/
#define EDI14_INPUT_SELECTION   1
#define EDI14_OUTPUT_SELECTION  2
/*
 Definizioni utilizzate per la selezione dei diversi tipi di
 domande rivolte all'utente nella fase di creazione dello
 ambiente legocad 
*/
#define K_CREATE_LEGOCAD_ENV  1
#define K_COPY_LEGOCAD_LIBUT 2
#define K_COPY_LEGOCAD_LIBREG 4
#define K_CREATE_LEGOCAD_LIBUT	8
#define K_CREATE_LEGOCAD_LIBREG	16
/*
 definizione tipi di modello gestiti da legocad
*/
#define TIPO_PROCESSO 0
#define TIPO_REGOLAZIONE 1
#define TIPO_MIX	 2
#define TIPO_NON_LEGO	3
/*
 Definizione dei comandi di shell inviati all'interno
 del programma
*/
/*
 comandi di creazione degli eseguibili che intervengono nelle
 diverse fasi di costruzione del modello
*/
/*
 creazione per modello misto regolazione + processo
*/
#define CREA_LIBRUT "cad_crealibrut"
#define CREA_LG1 "cad_crealg1"
#define CREA_LG3 "cad_crealg3"
#define CREA_LG5SK "cad_crealg5sk"
/*
 creazione per modello di solo processo
*/
#define CREA_LIBRUT_P "cad_crealibrut p"
#define CREA_LG1_P "cad_crealg1 p"
#define CREA_LG3_P "cad_crealg3 p"
#define CREA_LG5SK_P "cad_crealg5sk p"
/*
 creazione per modello di sola regolazione
*/
#define CREA_LIBRUT_R "cad_crealibrut r"
#define CREA_LG1_R "cad_crealg1 r"
#define CREA_LG3_R "cad_crealg3 r"
#define CREA_LG5SK_R "cad_crealg5sk r"
/*
 comandi di testing dell'aggiornamento dei files per ricavare
 lo stato di avanzamento del progetto
*/
#define TEST_TOPOLOGY  "cad_crealibrut t"
/* testa se e' attivabile la fase di inserimento dati
   in F14 */
#define TEST_DATA_EDITING "cad_crealg1 t" 

/* testa se e' possibile attivare il calcolo dello stazionario */
#define TEST_STEADY "cad_crealg3 t"

/* testa se e' possibile attivare il calcolo del transitorio */
#define TEST_TRANSIENT "cad_crealg5sk t"

/* lancia il make per la copia del modello */
#define COPY_MODELLO "make -f $LEGO_BIN/cad_environment copy_model"

/* lancia il make per il test del fortran ausilizrio */
#define TEST_FORAUS "make -f $LEGO_BIN/testforaus ftmp"
