/**********************************************************************
*
*       C Header:               OlTree.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Oct 10 16:02:41 1997 %
*
**********************************************************************/

/*
 * OlTree.h - file di include pubblico per l'utilizzo dell'oggetto OlTree 
 */
#ifndef _OlTree_h
#define _OlTree_h

#include <Rt/RtMemory.h>
#include <Ol/OlDatabaseTopologia.h>

/* dichiarazione tipi per Classe e Instanziazione di OlTree */
typedef struct _OlTreeClassRec *OlTreeObjectClass;
typedef struct _OlTreeRec *OlTreeObject;


#define NUM_MAX_LIV		6
#define MIN_CHAR_HIER		11
#define NUM_COUNT_AL		3


/*
	define per l'accesso ai contatori allarmi
 */
#define OL_COUNT_ALARM		1
#define OL_COUNT_WARN		2	
#define OL_COUNT_TOLLER		3
#define OL_COUNT_SUPERORD	4
#define OL_UNACK_ARRIV		5
#define OL_UNACK_BACK		6

#define PAG_ALL_GERAR		"pag_all_gerar" 

#define ALLARMFOUND		-1
#define ALLARMNOTFOUND		-100
#define CALCID                  "PEN$A10_" /* ID della calcolata con situazione
					      allarmi per quellq gerarchia */

/*
Definizioni del tipo di pagina 
*/
/*
Definizioni del tipo di pagina 
*/
#define OL_TYPE_UNKNOWN      0
#define OL_TYPE_TELEPERM     1
#define OL_TYPE_SINOTTICO    2
#define OL_TYPE_STAZIONI     3
/*
        procedure di uso esterno utilizzabili per l'oggetto OlTree  
*/
OlTreeObject OlCreateTree();
Boolean OlDestroyTree();
int OlTreeAddPage();
OlTreeObject OlTreeGetLeft();
OlTreeObject OlTreeGetRight();
OlTreeObject OlTreeGetTop();
Boolean	OlTreeGetSubInfo();
Boolean OlTreeGetPage();
int OlTreeGetLevel();
int OlTreeInsertAlarm();
int OlTreeCountNodes(OlTreeObject, int *);
void OlEstraiNodi(OlTreeObject , int, int , int *, int);
Boolean OlTreeJumpPage(OlTreeObject , float * , int *,char);


#endif /* _OlTree_h */

