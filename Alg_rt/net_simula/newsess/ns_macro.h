/**********************************************************************
*
*       C Header:               ns_macro.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon Nov 17 15:12:01 1997 %
*
**********************************************************************/
#if defined UNIX
#define leggi(_punt_,_size_,_item_,_fp_)   fread(_punt_,_size_,_item_,_fp_)
#define scrivi(punt,size,item,fp)   fwrite(punt,size,item,fp)
#define fluscia(fp)	fflush(fp)
#define sposta(fp,off)	fseek(fp, off, SEEK_SET)
#define sposta_rel(fp,off,rel)	fseek(fp, off, rel)
#else
#define leggi(_punt_,_size_,_item_,_fp_) read(_fp_,_punt_,_size_*_item_)
#define scrivi(punt,size,item,fp) write(fp,punt,size*item)
#define fluscia(fp)	flush(fp)
#define sposta(fp,off)	lseek(fp, off, SEEK_SET)
#define sposta_rel(fp,off,rel)	lseek(fpda, off, rel)
#endif


#define NAME_F22CIRC   "f22circ"
#define NAME_F22CIRCN  "f22circn"
#define NAME_RECORDN   "recordern.edf"
#define PERTURBAZIONI  "perturbazioni.dat"
#define PERTURBAZIONIN "perturbazionin.dat"
#define NAME_BACK      "backtrack.dat"
#define NAME_BACKN     "backtrackn.dat"
#define NAME_STATO     "stato_cr.rtf"
#define NAME_STATO_MOM "stato_cr.mom"
#define NAME_STATON    "stato_crn.rtf"
#define NEWSESSDIR     "newsess/"
/*      
   Define per indentificare il confronto tra le finestre temporali
*/
#define FIN_ESTESA          1      /* Ricopre la finestra temporale del file */
#define FIN_INCLUSA         2      /* Completamente interna al file */
#define FIN_PARZ_INCLUSA_DX 3      /* Parzialmente inclusa, esce a destra */
#define FIN_PARZ_INCLUSA_SX 4      /* Parzialmente inclusa, esce a sinistra */
#define FIN_ESTERNA         5      /* Esterna al file */

#define LETTURA    "lettura"    
#define SCRITTURA  "scrittura" 
#define LETTURATMP   "tempi" 

   typedef struct tempi_st
      {
      float ti;
      float tu;
      float tx;
      }TEMPI;

   typedef struct
       {
       char *stringa;
       int lun_stringa;
       } STRIN_ST;

   typedef struct
       {
       char modello[9];   /*  Nome Modello */
       int    nblock;     /*  Numero blocchi del modello */
       char **blocchi;    /*  Nomi di tutti i blocchi */
       } BLOCCHI;


