/**********************************************************************
*
*       C Source:               OlTree.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Aug  4 17:02:33 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: OlTree.c-16 %  (%full_filespec: OlTree.c-16:csrc:1 %)";
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "sdi_conf.h" /* Per maschere gestione allarmi */

#include <Ol/OlTreeP.h>
#include <X11/Intrinsic.h>

/* funzioni di utilita' */
Boolean hier_to_calc(char *,char *);

/* dichiarazione dei metodi (methods) */
static Boolean Initialize();
static Boolean FindChild(); 
static int AddPage();
static Boolean GetCmpHier();
static int GetPosChild();

/* Inizializzazione del class record */
OlTreeClassRec olTreeClassRec = {
  { /* tree fields */
    /* initialize		*/	Initialize,
    /* addpage                  */      AddPage,
    /* findchild 		*/      FindChild,
    /* getcmphier		*/	GetCmpHier,
    /* getposchild 		*/      GetPosChild,
  }
};



/*
        Funzione di uso esterno:	 OlCreateTree()
	per la creazione e l'inizializzazione della struttura gerarchica
	delle pagine
*/
OlTreeObject OlCreateTree(OlDatabaseTopologiaObject database_topologia,
	int pos_info_page, char *hier_resource, int *alarm_state,int tipo_pag)
{

   OlTreeObject root_oltree;
   char calc_name[MAX_LUN_NOME_VARS];
   
   /* Allocazione dell'oggetto OlTree */
   if((root_oltree=(OlTreeRec *)XtCalloc(1,sizeof(OlTreeRec)))!=NULL) {
      /* Inizializzazione */
      root_oltree->oltree.pos_info=pos_info_page;
      root_oltree->oltree.type_page=tipo_pag;
      strcpy(root_oltree->oltree.hierarchy, hier_resource);
      root_oltree->oltree.p_left=(OlTreePart *)root_oltree;
      root_oltree->oltree.p_right=(OlTreePart *)root_oltree;
      hier_to_calc(calc_name,hier_resource);
/*
Chiamo il metodo di OlTopologia che mi permette di ricavare tipo ed
indice di una var dato il nome della tag stessa.
*/
   if(!OlTagToIndS(database_topologia,calc_name,&(root_oltree->oltree.indice),&(root_oltree->oltree.tipo)))
	{
/*********
	printf("\n**************************************************\n");
	printf(" WARNING It's impossible to find allarm situation variable associated with node root !!!\n");
	printf("**************************************************\n");
**********/
	root_oltree->oltree.all_progress=ALLARMNOTFOUND;
        *alarm_state=-1;
	}
else
	root_oltree->oltree.all_progress=ALLARMFOUND;
	
printf("OlCreateTree:indice=%d\n",root_oltree->oltree.indice);
printf("OlCreateTree:tipo=%d\n",root_oltree->oltree.tipo);

/*
      printf("OlCreateTree:ROOT ALLOCATA! Hierarchy=%s\n",hier_resource );
*/
   }
   
   return(root_oltree);
}




/*
        Funzione di uso esterno:	 OlDestroyTree()
	per l'eliminazione  della struttura gerarchica
	delle pagine
*/
Boolean OlDestroyTree(OlTreeObject root_oltree)
{
OlTreeObject curr_node, curr_child,next_child;

curr_node=root_oltree;   /* parto esplorazione da radice */
if(curr_node!=NULL)
        {

        curr_child=(OlTreeObject )curr_node->oltree.p_child;
/*
Percorro albero in verticale
*/
        if(curr_child!=NULL)
                next_child=(OlTreeObject)curr_child->oltree.p_right;
        else next_child=NULL;
        OlDestroyTree((OlTreeObject)curr_node->oltree.p_child);
        curr_child=(OlTreeObject )curr_node->oltree.p_child;
        if(curr_child!=NULL)
                next_child=(OlTreeObject)curr_child->oltree.p_right;
        else next_child=NULL;


        do {
/*
Percorro albero in orizzontale
*/
        if(next_child!=curr_child)
           OlDestroyTree(curr_child);
        else
           if(curr_child!=NULL)
              OlDestroyTree(curr_child);

        curr_child=(OlTreeObject )curr_node->oltree.p_child;
        if(curr_child!=NULL)
                next_child=(OlTreeObject)curr_child->oltree.p_right;
        else next_child=NULL;

        if(next_child==curr_child)
           {
              if(curr_child==NULL) {
                 if((OlTreeObject)curr_node->oltree.p_right!=curr_node) {
                    (curr_node->oltree.p_father)->p_child=curr_node->oltree.p_right;
                    (curr_node->oltree.p_left)->p_right=curr_node->oltree.p_right;
                    (curr_node->oltree.p_right)->p_left=curr_node->oltree.p_left;
                 }
                 else {
                    if(curr_node->oltree.p_father!=NULL)
                       (curr_node->oltree.p_father)->p_child=NULL;
                 }
                 printf("Eliminazione del nodo di gerarchia: %s\n\n", curr_node->oltree.hierarchy);
                 free(curr_node);
              }
           }

        }while ((next_child!=curr_child) || ((curr_child==next_child)&&(curr_child!=NULL)));
     }
return(True);
}





/***************************************************

	Metodo che restituisce il numero di 
	nodi dell' OlTree data la radice.

Fuzione ricorsiva complessa dovuto al fatto che i figli
di uno stesso  nodo sono legati con una lista circolare (spostamento orizzontale p_right)
mentre   lo spostamento verticale e' terminato da null (p_child)
****************************************************/
int OlTreeCountNodes(OlTreeObject root_oltree,int *num_nodi)
{
OlTreeObject curr_node, curr_child,next_child;

curr_node=root_oltree;   /* parto esplorazione da radice */
if(curr_node!=NULL)
	{

	curr_child=(OlTreeObject )curr_node->oltree.p_child;
/*
Percorro albero in verticale
*/
	OlTreeCountNodes((OlTreeObject)curr_node->oltree.p_child,num_nodi);
	if(curr_child!=NULL)
		next_child=(OlTreeObject)curr_child->oltree.p_right;
	else next_child=NULL;
		do
	 		{

/*
Pecorro albero in orizzontale
*/
	if(next_child!=curr_child)  /* Se figlio non unico */
			OlTreeCountNodes(next_child,num_nodi);
			if(next_child!=NULL)
				{
				next_child=(OlTreeObject)next_child->oltree.p_right;

				}
/*
Incremento contatore solo se sono alla fine di una fila di figli (next_child=curr_child ma non NULL)
              if(curr_node->oltree.p_right!=curr_node) {
o se nodo e' isolato (next_child=curr_child=NULL)
*/
			if(next_child==curr_child)
				{
/* Conto nodi solo con allarmi */
				if((curr_node->oltree.all_progress==ALLARMFOUND) 
                                   && (curr_node->oltree.type_page==OL_TYPE_TELEPERM))

					{
					(*num_nodi)=(*num_nodi)+1;
/*
				printf("\nCONTEGGIATO nodo in gerarchia=%s\n",curr_node->oltree.hierarchy);
				printf("num_nodi=%d\n\n",*num_nodi);
*/
					}
/*
				else
					printf("\n NON CONTEGGIATO nodo in gerarchia=%s\n",curr_node->oltree.hierarchy);
*/
				}
	/*	
			printf("Ho esaminato nodo di gerarchia=%s\n",curr_node->oltree.hierarchy);
	*/
		 	}while(next_child!=curr_child);
	}
return(*num_nodi);
}

/*****************************************************************
	Metodo che esamina ogni nodo e spedisce un 
	messaggio per creazione pagina fittizia contenente 
	situazione allarmi.
	Ritorna True se tutto Ok.
******************************************************************/
void OlEstraiNodi(OlTreeObject root,int coda,int t_agg,int *progress,int tot_punti)
{

OlTreeObject curr_node, curr_child,next_child;
/*
Parte che prepara la spedizione del il messaggio
*/
curr_node=root;
if(curr_node!=NULL)
        {

        curr_child=(OlTreeObject)curr_node->oltree.p_child;
/*
Percorro albero in verticale
*/
        OlEstraiNodi((OlTreeObject)curr_node->oltree.p_child,coda,t_agg,progress,tot_punti);
	if(curr_child!=NULL)
        	        next_child=(OlTreeObject)curr_child->oltree.p_right;
        else next_child=NULL;
                do
                        {
/*
Pecorro albero in orizzontale
*/
        if(next_child!=curr_child)  /* Se figlio non unico */
                        OlEstraiNodi(next_child,coda,t_agg,progress,tot_punti);
                        if(next_child!=NULL)
                                {
                                next_child=(OlTreeObject)next_child->oltree.p_right;

                                }
/*
Incremento contatore solo se sono alla fine di una fila di figli
o se nodo e' isolato.Incremento solo quando al nodo sono associati
degli allarmi (cosa verificata durante costruzione OlTree.
*/
                        if(next_child==curr_child)
                                {
				if((curr_node->oltree.all_progress==ALLARMFOUND)
                                       &&(curr_node->oltree.type_page==OL_TYPE_TELEPERM))
					{
/* Assegno # progressivo al nodo */
					curr_node->oltree.all_progress=*progress;
/* Spedisco messaggio */
      					CsPrepMsgS(PAG_ALL_GERAR,coda,t_agg,
					curr_node->oltree.indice,curr_node->oltree.tipo,
                                	*progress,tot_punti);
                                	*progress=(*progress)+1;
/*
                                printf("\nESAMINATO nodo in gerarchia=%s\n",curr_node->oltree.hierarchy);
                                printf("progress=%d\n\n",*progress);
*/
					}
#ifdef HIERDEBUG
				else
                                	printf("\n NON ESAMINATO nodo in gerarchia=%s\n",curr_node->oltree.hierarchy);
#endif
                                }
			}while(next_child!=curr_child);
		}
}

/**********************************************************************

        Metodo: OlTreeJumpPag

Funzione ricorsiva che restituisce l' indice della pagina destinazione
per il direct jump.

Per ogni nodo esamino i figli e verifico se esiste un figlio con 
allarme settato.
Se ne esiste uno, ripeto la ricerca aprtendo da questo ultimo;
Se ne esiste + di uno, restituisco l' indice del nodo corrente;
Se non esiste, restituisco l' indice del nodo corrente.
***********************************************************************/
Boolean OlTreeJumpPage(OlTreeObject root,float *pagina_fittizia,int *indice,
		char tipo_all)
{
OlTreeObject curr_node, curr_child,next_child;
OlTreeObject primo_target,secondo_target;
float valore;
int situazione_bit;

assert(pagina_fittizia);
assert(root);
curr_node=root;
if(curr_node==NULL)
	return(False);
curr_child=(OlTreeObject)curr_node->oltree.p_child;

if(curr_child!=NULL)
	next_child=curr_child;
/*	next_child=(OlTreeObject)curr_child->oltree.p_right;*/
else next_child=NULL;

primo_target=NULL;
secondo_target=NULL;

if(next_child!=NULL) /* children exist */
	{
	do
		{
		/* Check  next_child's situation */
                printf("OlTreeJumpPage:exam node=%s\n",next_child->oltree.hierarchy);
   if(next_child->oltree.all_progress >= 0) {
		valore=pagina_fittizia[(next_child->oltree.all_progress)*2];
		situazione_bit=(int)valore;
		if(((situazione_bit & ALL_A_PEN_MASK) && (tipo_all==ALLARM_CAI)) ||
		  ((situazione_bit & ALL_W_PEN_MASK)&&(tipo_all==WARNING_CAI)) ||
                  ((situazione_bit & ALL_T_PEN_MASK)&&(tipo_all==TOLERANCE_CAI))||
                  ((situazione_bit & ALL_S_PEN_MASK)&&(tipo_all==SIMUL_CAI))   ||
		  ((situazione_bit & ALL_M_PEN_MASK)&&(tipo_all==MANUAL_CAI))   ||
		  ((situazione_bit & ALL_F_PEN_MASK)&&(tipo_all==FAULT_CAI))   )
			{ /* found node with allarm */
/*
printf("OlTreeJumpPage:allarm node=%s situation=%x\n",next_child->oltree.hierarchy,situazione_bit);
*/
			if(primo_target==NULL)
				primo_target=next_child;
			else    secondo_target=next_child;
			}
                }/* if(next_child->oltree.all_progress >= 0) */
		if(secondo_target==NULL) /* continue search among children */
			next_child=(OlTreeObject)next_child->oltree.p_right;
		else next_child=curr_child; /* found 2 nodes with all.-> exit */

		}while(next_child!=curr_child);/* end search among children */

	if((secondo_target!=NULL) || (primo_target==NULL))
		*indice=curr_node->oltree.pos_info;
	else 
		OlTreeJumpPage(primo_target,pagina_fittizia,indice,tipo_all);
	} /*end if next_child !=NULL */
/*
The node hasn't got any child: it's the target node
*/
else 
	 *indice=curr_node->oltree.pos_info;
		
}
/*
	Metodo:		Initialize()
*/
static Boolean Initialize()
{


}



/*
	Funzione di uso esterno:	OlTreeAddPage()
	per l'inserimento di una nuova pagina nella struttura gerarchica
	a partire dalla risorsa 'gerarchia'
*/
int OlTreeAddPage(OlDatabaseTopologiaObject database_topologia,OlTreeObject root_oltree,int level,int pos_info_page,
                  char *hier_resource,int tipo_pag)
{

   OlTreeObject curr_page, child_page;
   int i, alarm_state;  

   /* La pagina corrente inizialmente e' la radice */
   curr_page=root_oltree;

/*
   printf("OlTreeAddPage: ENTRATO!!! hier_resource=%s\n", hier_resource);
*/

   if(level>1) {
      /* Si scende di livello nell'albero fino a trovare la pagina padre
         di quella da inserire						 */
      for(i=1;i<level;i++) {
         if(((olTreeClassRec.oltree_class.findchild)(curr_page,&child_page,hier_resource,i))==True) {
            /* Passaggio al livello inferiore */
            curr_page=child_page;
         }
         else {
            /* La pagina da inserire non puo' essere figlia di una pagina
               gia' esistente. Errore!!!                                */

            printf("OlTreeAddPage: Current page not inserted in hierarchy!\n");
            printf("OlTreeAddPage: Current page without father!\n");

            return(-1);
         } /* end if */
      } /* end for */
   }
   else {
      /* La pagina da inserire e' di livello 1; e' quindi figlia della 
         radice; ho gia' il suo puntatore. Si controlla se la pagina
         in esame e' veramente figlia di quella radice */
      if((olTreeClassRec.oltree_class.getcmphier)(hier_resource,curr_page->oltree.hierarchy,0)==False) {
         /* La pagina da inserire non puo' essere figlia della root */

         printf("OlTreeAddPage: Current page can't be a root child!\n");

         return(-1);
      }
   }

   /* Raggiunta la posizione in cui inserire la nuova pagina*/
//   if((olTreeClassRec.oltree_class.addpage)(database_topologia,curr_page,pos_info_page,hier_resource,level,&alarm_state,tipo_pag)<0)
   if((olTreeClassRec.oltree_class.addpage)(database_topologia,curr_page,pos_info_page,hier_resource,level,&alarm_state,tipo_pag) == False)
	{
	printf("OlTreeAddPage failed !!! Check the hierarchy\n");
	return(-2);
	}
   else
	{
#ifdef HIERDEBUG
        printf("alarm_state: %d\n",alarm_state);
#endif
        if(alarm_state==ALLARMNOTFOUND)
/*   Non trovata la variabile di descrizione allarme nel file fnomi.rtf
     per il nodo corrente.                                               */
           return(-3);
	}

/*
   printf("OlTreeAddPage: USCITA CORRETTA!!! hier_resource=%s\n", hier_resource);
*/

   return(0);
 
}  

/*
Funzione che data una gerarchia restituisce il nome della calcolata con
la situazione allarmi relativa a quel nodo in gerarchia.
*/
Boolean hier_to_calc(char *calc_name,char *hierar)
{
char gera[NUM_MAX_LIV*5],appo[NUM_MAX_LIV*5];
int ex_val;
char *token;

strcpy(gera,hierar);
#ifdef HIERDUBUG
printf("hier_to_calc:hier=%s\n",hierar);
#endif
strcpy(calc_name,CALCID);

token=strtok(gera,",");
#ifdef PROVA
token=(unsigned char *)strtok(gera,",");
#endif
do
	{
#ifdef PROVA
	sscanf(token,"%2d",&ex_val);
	if(ex_val>=0)
		sprintf(appo,"%02X",ex_val);
	else
		strcpy(appo,"FF");
	strcat(calc_name,appo);
	token=strtok(NULL,",");
#endif
        sscanf(token,"%d",&ex_val);
        if(ex_val>=0)
                sprintf(appo,"%02X",ex_val);
        else
                strcpy(appo,"FF");
/*printf("ex_val=%d\n",ex_val);*/
        strcat(calc_name,appo);
	token=strtok(NULL,",");
	}while(token);
#ifdef HIERDEBUG
printf(" hier_to_calc:calc_name=%s\n",calc_name);
#endif
return(True);
}

/*
	Metodo:		AddPage()
	Inserisce una nuova pagina nella struttura gerarchica come 
        figlia di quella corrente (curr_root) mantenendo l'ordinamento
        tra i figli			
	 
*/
static int AddPage(OlDatabaseTopologiaObject database_topologia,OlTreeObject curr_root,int pos_info_page, char *hier,
                int level, int *alarm_state,int tipo_pag)
{

   int pos_child_inser,pos_curr_child;
   OlTreeObject current_child,first_child,prew_child,last_child,new_child;
   char hier_app[50];
   char calc_name[MAX_LUN_NOME_VARS];


/*
   printf("AddPage: ENTRATO!!!", hier);
*/

   if(curr_root->oltree.p_child==NULL) 
      {
      /* Stiamo inserendo il primo figlio */
      new_child=(OlTreeRec *)XtCalloc(1,sizeof(OlTreeRec));
      new_child->oltree.p_right=(OlTreePart *)new_child;
      new_child->oltree.p_left=(OlTreePart *)new_child;
      curr_root->oltree.p_child=(OlTreePart *)new_child;
      }
   else 
      {
      /* Esistono gia' figli. Ricerca della posizione di inserimento */
      first_child=(OlTreeRec *)curr_root->oltree.p_child;
      strcpy(hier_app,hier);
      pos_child_inser=(olTreeClassRec.oltree_class.getposchild)(hier_app,level);
      strcpy(hier_app,first_child->oltree.hierarchy);
      pos_curr_child=(olTreeClassRec.oltree_class.getposchild)(hier_app,level);
      if(pos_child_inser<pos_curr_child) 
         {
         /* La pagina corrente va in prima posizione */
         new_child=(OlTreeRec *)XtCalloc(1,sizeof(OlTreeRec));
         curr_root->oltree.p_child=(OlTreePart *)new_child;
         new_child->oltree.p_right=(OlTreePart *)first_child;
         new_child->oltree.p_left=first_child->oltree.p_left;
         last_child=(OlTreeRec *)first_child->oltree.p_left;
         last_child->oltree.p_right=(OlTreePart *)new_child;
         first_child->oltree.p_left=(OlTreePart *)new_child;
          }
      else 
          {
         /* La pagina da inserire non e' in prima posizione */
         current_child=first_child;
         while((pos_child_inser>pos_curr_child)&&
               (current_child->oltree.p_right!=(OlTreePart *)first_child)) 
            {
            prew_child=current_child;
            current_child=(OlTreeRec *)current_child->oltree.p_right;
            strcpy(hier_app,current_child->oltree.hierarchy);
            pos_curr_child=(olTreeClassRec.oltree_class.getposchild)(hier_app,level);
            }
         if(pos_child_inser!=pos_curr_child) 
         {
            /* Il valore della risorsa gerarchia della pagina corrente e'
               diverso da quello delle pagine gia' presenti. Inserimento!!  */ 
            new_child=(OlTreeRec *)XtCalloc(1,sizeof(OlTreeRec));           
            if((current_child==first_child) || 
		(pos_child_inser > pos_curr_child )) 
            {
               /* Inserimento in fondo alla lista 
		  il primo test dell'if e' valido nel caso che 
		  stiamo inserendo il secondo nodo,
                  il secondo test in or
                  vale true per gli altri casi*/

               new_child->oltree.p_right=(OlTreePart*)first_child;
               new_child->oltree.p_left=(OlTreePart *)current_child;
               current_child->oltree.p_right=(OlTreePart *)new_child;
               first_child->oltree.p_left=(OlTreePart *)new_child;
            }
            else 
            {
               /* Inserimento intermedio */
               /* aggiorno i puntatori a destra e sinistra del nodo 
                  nuovo da inserire new_child.
                  Poi aggiorno il fratello di destra del nodo precedente
                  a puntare al nodo corrente,appena inserito.
                  Poi aggiorno il fratello di sinistra del nodoo successivo
                  a puntare al nodo corrente,appena inserito.
               */
               new_child->oltree.p_right=(OlTreePart *)current_child;
               new_child->oltree.p_left=(OlTreePart *)prew_child;
               prew_child->oltree.p_right=(OlTreePart *)new_child;
               current_child->oltree.p_left=(OlTreePart *)new_child;
            }
         }
         else 
         {
            /* Il valore della risorsa gerarchia della pagina corrente e'
               uguale a quello di una pagina gia' presente. Errore!! Non 
               inserimento e segnalazione!                                 */
/*
            printf("AddPage:WARNING!! A page with hierarchy resource value %s already present\n",hier);
*/
            return(-1);
         }                                
      }
   }

   /* Inserimento nel nuovo nodo delle informazioni comuni */
   new_child->oltree.pos_info=pos_info_page;
   new_child->oltree.type_page=tipo_pag;
#ifdef HIERDEBUG
   printf("TYPE_PAG=%d\n",new_child->oltree.type_page);
#endif
   strcpy(new_child->oltree.hierarchy,hier);
   hier_to_calc(calc_name,hier);

/*
Chiamo il metodo di OlTopologia che mi permette di ricavare tipo ed 
indice di una var dato il nome della tag stessa.
*/
   if(!OlTagToIndS(database_topologia,calc_name,&(new_child->oltree.indice),&(new_child->oltree.tipo)))
	{
#ifdef HIERDEBUG
	printf("\n**************************************************\n");
	printf("WARNING It's impossible to find allarm description variable in fnomi.rtf, for node with %s hierarchy !!!\n",hier);
	printf("**************************************************\n");
#endif
	new_child->oltree.all_progress=ALLARMNOTFOUND;

	}
else
	new_child->oltree.all_progress=ALLARMFOUND;
/*
printf("AddPage:indice=%d\n",new_child->oltree.indice);
printf("AddPage:tipo=%d\n",new_child->oltree.tipo);
*/
   new_child->oltree.p_father=(OlTreePart *)curr_root;
   new_child->oltree.p_child=NULL;
   *alarm_state=new_child->oltree.all_progress;
/*
   printf("AddPage: alarm_state: %d\n",*alarm_state);
   printf("AddPage: USCITO!!!\n");
*/

}



/*
	Metodo:		FindChild()
	Restituisce il puntatore alla pagina figlia di quella data
	(curr_root) rispettando la risorsa 'gerarchia' (hier) fino al livello
	specificato (curr_lev). 
*/
static Boolean FindChild(OlTreeObject curr_root,OlTreeObject *child_found,char *hier,int curr_lev)
{

   OlTreeObject current_child,first_child;
   int i;
   char *hier_root,*hier_child;

   hier_root=hier;

   current_child=first_child=(OlTreeObject)curr_root->oltree.p_child;
   if(current_child==NULL) {
/* La pagina corrente non fa parte della gerarchia 
      printf("FindChild: USCITO CON ERRORE\n");
*/
      return(False);
   } 
   hier_child=current_child->oltree.hierarchy;
   if((olTreeClassRec.oltree_class.getcmphier)(hier_root,hier_child,curr_lev)==True) {
      /* Trovato il nodo */
      *child_found=current_child;
/*
      printf("FindChild: USCITO CORRETTAMENTE!!\n");
*/
      return(True);
   }
   else {
      current_child=(OlTreeObject)current_child->oltree.p_right;
      while(current_child!=first_child) {
         /* Esiste il figlio */
         hier_child=current_child->oltree.hierarchy;
         if((olTreeClassRec.oltree_class.getcmphier)(hier_root,hier_child,curr_lev)==True) {
            /* Trovato il nodo */
            *child_found=current_child;
/*
            printf("FindChild: USCITO CORRETTAMENTE!!\n");
*/
            return(True);
         }
         current_child=(OlTreeObject)current_child->oltree.p_right;
      }
   }
   /* La pagina da inserire non e' figlia di alcuna pagina gia' in gerarchia */
   *child_found=NULL;
/*
   printf("FindChild: USCITO CON ERRORE\n");
*/
   return(False); 

}



/*
	Metodo:		GetPosChild()		
	A partire dalla risorsa 'gerarchia' restituisce la posizione al
        livello curr_lev
          
*/
static int GetPosChild(char *hier, int curr_lev)
{
   char    *string,*string1,str_liv[50];
   int     i,lungh,int_liv;  

   string=hier;

   for(i=0;i<curr_lev;i++) {
      string1=strchr(string, ',');
      strcpy(string,(string1+1));
   }
   if(curr_lev<(NUM_MAX_LIV-1)) {
      string1=strchr(string, ',');
      lungh=strlen(string)-strlen(string1);
      strncpy(str_liv,string,lungh);
      str_liv[lungh]='\0';
   }
   else
      strcpy(str_liv,string);

   int_liv = atoi(str_liv);

/*
printf("GetPosChild: hier=%s   str_liv=%s  int_liv=%d\n",hier,str_liv,int_liv);
*/

   return(int_liv);
}



/*
	Metodo:		GetCmpHier()
	Confronta la risorsa 'gerarchia' di due pagine fino al livello
        specificato (curr_lev)
*/
static Boolean GetCmpHier(char *hier_res1,char *hier_res2,int curr_lev)
{

   char    *string1,*string2,*string_app1,*string_app2,str_liv1[50],
           str_liv2[50];
   int     j;

   string1=hier_res1;
   string2=hier_res2;

   if(curr_lev==(NUM_MAX_LIV-1)) {
      strcpy(str_liv1,string1);
      strcpy(str_liv2,string2);
   }
   else {
      for(j=0;j<=curr_lev;j++) {
         string_app1=strchr(string1, ',');
         string1=(string_app1+1);
         string_app2=strchr(string2, ',');
         string2=(string_app2+1);
      }
      strncpy(str_liv1,hier_res1,strlen(hier_res1)-strlen(string1));
      strncpy(str_liv2,hier_res2,strlen(hier_res2)-strlen(string2));
      str_liv1[strlen(hier_res1)-strlen(string1)]='\0';
      str_liv2[strlen(hier_res2)-strlen(string2)]='\0';
   }

   if(!strcmp(str_liv1,str_liv2)) {
      /* Confronto OK */
      return(True);
   }
   else {
      /* Confronto KO */
      return(False);
   }

}



/*
	Funzione di uso esterno:	OlTreeGetPage()
	Restituisce il puntatore ad una pagina presente nell'oggetto OlTree
	e il riferimento alle sue informazioni a partire dalla risorsa
	'gerarchia'
*/ 
Boolean OlTreeGetPage(OlTreeObject root,OlTreeObject *curr_found,int *progress,int *pos_info_page,char *hier)
{

   OlTreeObject curr_page,child_page,first_child;
   int page_lev,i;

   /* Chiamata alla funzione che a partire dalla gerarchia della pagina
      restituisce il livello						*/
/*
   printf("OlTreeGetPage: ENTRATO!!\n");
*/
   page_lev=OlTreeGetLevel(hier);

/* carlo per gestione gerarchia -1
*/
   if(page_lev == -1 )
   {
       *curr_found=NULL;
       return(False);
   }

/*
   printf("OlTreeGetPage: Livello=%d\tHierarchy=%s\n",page_lev,hier);
*/
  
   if(page_lev==0) {
      *curr_found=root;
      *pos_info_page=root->oltree.pos_info;
      *progress=root->oltree.all_progress;
      return(True);
   }
   else {
      curr_page=root;
      if(page_lev>1) {
      /* La pagina e' almeno di secondo livello. Cerco il padre. */
         for(i=1;i<page_lev;i++) {
            if(((olTreeClassRec.oltree_class.findchild)(curr_page,&child_page,hier,i))==True) {
               /* Passaggio al livello inferiore */
               curr_page=child_page;
            }
            else {
/*
               printf("OlTreeGetPage: USCITO!! PAGINA NON TROVATA\n");
*/
               *curr_found=NULL;
               return(False);
            }
         }
      }
   }
   /* Siamo posizionati sul padre della pagina da recuperare. */
   child_page=(OlTreeObject)curr_page->oltree.p_child;
   first_child=child_page;
   while((child_page!=NULL) ) {
      if(!strcmp(hier,child_page->oltree.hierarchy)) {
         *curr_found=child_page;
	 *pos_info_page=child_page->oltree.pos_info;
	 *progress=child_page->oltree.all_progress;
/*
         printf("OlTreeGetPage: USCITO!! PAGINA TROVATA\n"); 
*/
         return(True);
      }
      else 
         {
/*
Se non trovo la pagina tra i figli return(False)
*/
         if((OlTreeObject)child_page->oltree.p_right!=first_child)
             child_page=(OlTreeObject)child_page->oltree.p_right;
         else
             {
             *curr_found=NULL;
             return(False);
             }
             
         
      }
   }
/*
   printf("OlTreeGetPage: USCITO!! PAGINA NON TROVATA\n");
*/
   *curr_found=NULL;
   return(False);

}





/*
	Funzione di uso esternoi: 	OlTreeGetLeft()
	Restituisce il puntatore alla pagina a sinistra di quella data
	e il riferimento alle sue informazioni
*/
OlTreeObject OlTreeGetLeft(OlTreeObject curr_page, int *pos_info_page)
{

   OlTreeObject left_page;

   left_page=(OlTreeObject)curr_page->oltree.p_left;

   if(curr_page==left_page)
      printf("OlTreeGetLeft: nothing on left\n");


   if(left_page->oltree.type_page==OL_TYPE_STAZIONI)
      {
      left_page=curr_page;
      printf("OlTreeGetLeft: Impossible to open a not correct type page!!!\n");
      }

   *pos_info_page=left_page->oltree.pos_info;   
     
   return(left_page);

}




/*
	Funzione di uso esterno:	OlTreeGetRight()
	Restituisce il puntatore alla pagina a destra della pagina data 
	e il riferimento alle sue informazioni
*/
OlTreeObject OlTreeGetRight(OlTreeObject curr_page,int *pos_info_page)
{

   OlTreeObject right_page;

   right_page=(OlTreeObject)curr_page->oltree.p_right;

   if(curr_page==right_page)
      printf("OlTreeGetRight: nothing on right\n");

   if(right_page->oltree.type_page==OL_TYPE_STAZIONI)
      {
      right_page=curr_page;
      printf("OlTreeGetRight: Impossible to open a not correct type page!!!\n");
      }

   *pos_info_page=right_page->oltree.pos_info;
 
   return(right_page);


}



/*
	Funzione di uso esterno:	OlTreeGetTop()
	Restituisce il puntatore alla pagina padre di quella data
	e il riferimento alle sue informazioni
*/
OlTreeObject OlTreeGetTop(OlTreeObject curr_page,int *pos_info_page)
{

   OlTreeObject top_page;

   if(curr_page->oltree.p_father!=NULL) {
      /* Non ancora arrivati alla root */
      top_page=(OlTreeObject)curr_page->oltree.p_father;
   }
   else {
      printf("OlTreeGetTop: already in root\n");
      top_page=curr_page;
   }
   if(top_page->oltree.type_page==OL_TYPE_STAZIONI)
      {
      top_page=curr_page;
      printf("OlTreeGetTop: Impossible to open a not correct type page!!!\n");
      }
   *pos_info_page=top_page->oltree.pos_info;
 
   return(top_page);


}




/*
	Funzione di uso esterno:	OlTreeGetSubInfo()
	Restituisce i riferimenti alle informazioni sui figli della pagina
	corrente
        I figli  cui indici saranno restituiti nella lista int puntata da 
	pos_child_info, non devono essere di tipo Stazione (es.: O.W.).


*/
Boolean OlTreeGetSubInfo(OlTreeObject curr_root, int *pos_child_info)
{

   OlTreeObject curr_child,first_child;
   int i=0;

   /* Memorizzo primo figlio a sx */
   first_child=(OlTreeObject)curr_root->oltree.p_child;
   if(first_child!=NULL) {
      if(first_child->oltree.type_page!=OL_TYPE_STAZIONI)
         {
      	 pos_child_info[i]=first_child->oltree.pos_info;
	 i++;
	 }
/*
	Scorro tutti i figli 
*/
      curr_child=(OlTreeObject)first_child->oltree.p_right;
      while(curr_child!=first_child) 
         {
	 if(curr_child->oltree.type_page!=OL_TYPE_STAZIONI)
	    {
            pos_child_info[i]=curr_child->oltree.pos_info;
            i++;
	    }
         curr_child=(OlTreeObject)curr_child->oltree.p_right;
         }
/*
      Segnalo fine lista 
*/
      pos_child_info[i]=-1;

      return(True);
   }
   else {
      /* La radice corrente non ha figli */
      return(False);
   }

}


/*
	Funzione di uso esterno:		OlTreeGetLevel()
	Data la risorsa 'gerarchia' di una pagina restituisce il livello
        a cui appartiene

*/
int OlTreeGetLevel(char *hier)
{

   char string[50],*string1,str_liv[10];
   int  lungh,i=-1,j=0;

   strcpy(string,hier);
/*
   printf("OlTreeGetLevel: hier=%s\n", hier);
*/
   if(strlen(string)>=MIN_CHAR_HIER) {
      while ((string1=strchr(string, ','))!=NULL) {
         strcpy(string,(string1+1));
         j++;
      }
      if((j==(NUM_MAX_LIV-1))&&(strlen(string)>0)) {
         strcpy(string,hier);
         /* La stringa 'risorsa gerarchia' non e' vuota e il formato e' corretto */
         while ((string1=strchr(string, ',')) != NULL) {
            lungh = strlen(string) - strlen(string1);
            strncpy(str_liv, string, lungh);
            str_liv[lungh] = '\0';
            if(!strcmp(str_liv, "-1")) {
/*
	       printf("OlTreeGetLevel: level=%d\n",i);
*/
               /* La pagina e' di livello i.  */
               return(i);
            }
            i++;
            strcpy(string,(string1+1));
         }
         if(strcmp(string,"-1")) {
            /* La pagina e' di livello NUM_MAX_LIV-1 */
            i++;
         }
      }
   }
/*
   printf("OlTreeGetLevel: level=%d\n",i);
*/
   return(i);
}


 
/*
	Funzione di uso esterno:		OlTreeInsertAlarm()
	aggiorna i contatori allarmi in corrispondenza dell'inserimento
	di un nuovo allarme
*/
int OlTreeInsertAlarm(OlTreeObject curr_page,int alarm_type,int al_stat)
{

   int ind_stat;

   /* Stato dell'allarme da inserire */
   if(al_stat==OL_UNACK_ARRIV) {
      /* Allarme in arrivo non riconosciuto */
      ind_stat=0;
   }
   else {
      /* Allarme di rientro non riconosciuto */
      ind_stat=2;
   }
   while(curr_page!=NULL) {
      /* Aggiornamento dei contatori allarmi del tipo specificato */ 
      switch (alarm_type) {
         case (OL_COUNT_ALARM):
            (curr_page->oltree.alarm[ind_stat])++;
            (curr_page->oltree.alarm[ind_stat+1])++;
            break;
         case (OL_COUNT_WARN):
            (curr_page->oltree.warning[ind_stat])++;
            (curr_page->oltree.warning[ind_stat+1])++;
            break;
         case (OL_COUNT_TOLLER):
            (curr_page->oltree.toller[ind_stat])++;
            (curr_page->oltree.toller[ind_stat+1])++;
            break;
         case (OL_COUNT_SUPERORD):
            (curr_page->oltree.superord[ind_stat])++;
            (curr_page->oltree.superord[ind_stat+1])++;
            break;
         default:
            break;
      }
      curr_page=(OlTreeObject)curr_page->oltree.p_father;
   }
}


/*
        Funzione di uso esterno:        OlTreeGetPosInfo()
        Restituisce la pos_info dell oggetto
*/
int OlTreeGetPosInfo(OlTreeObject curr_page,int *pos_info_page)
{

   if( curr_page == NULL )
      return(False);

   *pos_info_page = curr_page->oltree.pos_info;

   return(True);

}


