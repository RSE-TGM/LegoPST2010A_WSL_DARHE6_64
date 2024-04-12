/**********************************************************************
*
*       C Header:               OlTreeP.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon Jul 14 18:09:56 1997 %
*
**********************************************************************/

/*
 * OlTreeP.h - definizioni private per l'oggetto OlTree
 */
#ifndef _OlTreeP_h
#define _OlTreeP_h


/*
 Inclusione dell'header file pubblico
*/
#include <Ol/OlTree.h>
#include <Cs/Cs.h>

typedef Boolean (*InitializeProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*AddPageProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlFindChildProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlGetCmpHierProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlGetPosChildProc) (
#if NeedFunctionPrototypes
#endif
);

/*
Nella struttura del nodo sono stati introdotti i campi tipo ed indice
corrispondenti a tipo e ad indice della calcolata associata al nodo,
contenente la situazione allarmi di quella gerarchia e all_progress,
contenente il progressivo del nodo nella shared-memory della pagina
fittizia con situazione allarmi. E' stato inoltre introdotto il campo
type_page che specifica il tipo di pagina associata al nodo.
by Fabio
*/

typedef struct _ol_tree_part {
   int        type_page;             /* Tipologia della pagina associata al
                                        nodo.                             */ 
   int        pos_info;		     /* Posizione della pagina corrente nello
		                        array delle informazioni: 
		                        (AN_PAG *pagine)                  */
   char       hierarchy[50];	     /* Valore della risorsa gerarchia per la
			                pagina corrente                   */
   int        alarm[NUM_COUNT_AL];   /* Array contenente i contatori relativi
                                        agli 'allarmi'                    */
   int        warning[NUM_COUNT_AL]; /* Array contenente i contatori relativi
                                        agli 'warning'                    */
   int        toller[NUM_COUNT_AL];  /* Array contenente i contatori relativi
                                        alle 'tollerance'                 */
   int        superord[NUM_COUNT_AL];/* Array contenente i contatori relativi
                                        ai 'Superordinate I&C fault'      */
   int        all_progress;          /* progressivo della locazione (offset) 
					della pag fittizia contenente
				        situazione allarmi                */
   int	      tipo;		     /* Tipo calcolata associata alla gerar-
					chia del nodo			  */
   int	      indice;		     /*  Indice calcolata associata alla ge-
					rarchia del nodo		  */
   struct _ol_tree_part *p_father;   /* Puntatore al nodo padre		  */
   struct _ol_tree_part *p_child;    /* Puntatore al primo figlio 	  */
   struct _ol_tree_part *p_left;     /* Puntatore al fratello di sinistra */
   struct _ol_tree_part *p_right;    /* Puntatore al fratello di destra   */
		} OlTreePart;
	

typedef struct _ol_tree_class_part {
	InitializeProc		initialize;
	AddPageProc		addpage;
	OlFindChildProc		findchild;
        OlGetCmpHierProc	getcmphier;
	OlGetPosChildProc	getposchild;
	} OlTreeClassPart;

typedef struct _OlTreeClassRec {
	OlTreeClassPart		oltree_class;
	} OlTreeClassRec;

extern OlTreeClassRec olTreeClassRec;


typedef struct _OlTreeRec {
        OlTreePart oltree;
        } OlTreeRec;

#endif /* _OlTreeP_h */
