/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo f22.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)f22.h	5.1
*/
/*
 * F22.H
 *   - contiene le definizioni delle strutture appartenenti ai file
 *     f22 utilizzati nella applicazione GRAF per LEGOCAD.
 *   - contiene i dimensionamenti relativi ai medesimi files.
 */

/*
 *  File F22_HEADER.DAT o header del file F22.DAT
 */
#define NUM_VAR 600
#define LUN_TITOLO 80
#define LUN_SIMB 80
#if defined SCADA_MMI
#define LUN_NOME 10 /* lunghezza nome variabili su file f22 */
#else
#define LUN_NOME 8 /* lunghezza nome variabili su file f22 */
#endif

#if defined AIX || VMS
#define MDIM 365

typedef struct dati_graf{
        int npu;
        float ord[MDIM][NUM_VAR];
        float asc[MDIM];
        } DATI_GRAF;


                             
typedef struct s_dati {
                        char spare[2];  /* per VMS */
                        float t;
                        float mis[NUM_VAR];
                        } S_DATI;
typedef struct s_mis {
                      float mis[NUM_VAR];
                     } S_MIS;
#else

typedef struct s_head1 {
		char titolo[LUN_TITOLO];
		int nvar;  /* numero variabili presenti */
		} S_HEAD1;

typedef struct s_head2 {
		char nome_mod[LUN_NOME];
		int ncasi; /* numero record tabella dei simboli */
		} S_HEAD2;

/*
 *  File F22.DAT (=file dati dalla simulazione)
 */
typedef struct s_dati {
			float t;
			float mis[NUM_VAR];
			} S_DATI;

#endif

/*
   parametri in uso alle routine di accesso al file f22
*/

#define AGGIORNA 0
#define TUTTI    1

typedef struct s_min_max {
                        float min;
                        float max;
                        } S_MIN_MAX;


