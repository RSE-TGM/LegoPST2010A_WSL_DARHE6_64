/**********************************************************************
*
*       C Source:               del_blocchi.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:57:46 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: del_blocchi.c,2 %  (%full_filespec: 1,csrc,del_blocchi.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)del_blocchi.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/


#include "lg1.h"


del_blocchi ( bl_sel_count, bl_sel )
int    bl_sel_count, bl_sel[];
{

   CONN *lista_con,*con_change;
   int  i, j, k, buco, gap,ncanc=0;


   for ( i=0;  i<bl_sel_count; i++ )
   {

     /* Cancellla le connessioni del blocco */
     for ( lista_con = blocchi[bl_sel[i]].variabili_connesse;
           lista_con;
           lista_con = lista_con->succ
         )
       cancella_con( lista_con->blocco_esterno, bl_sel[i], 
                     lista_con->var_interna );

     /* Libera la memoria dinamica associata al blocco */
     libera_blocco( bl_sel[i] );

   }

 
   /*printf("test step 1  del_blocchi\n");*/

   /* Compattamento del vettore dei blocchi */

   /* Calcolo del gap iniziale */
   for ( gap=1, buco=1; buco < bl_sel_count; buco++ )
      if ( bl_sel[buco]-1 == bl_sel[buco-1] )
        gap++;
      else
        break; 

   /*printf("test step 2  del_blocchi\n");*/

   for ( i=bl_sel[0]; i+gap<num_blocchi; )
   {
      memcpy( blocchi+i, blocchi+(i+gap), sizeof(BLOCCO) );

      /* Calcolo del nuovo gap */
      i++;
      if ( buco < bl_sel_count  &&  i+gap == bl_sel[buco] )
        for ( buco++, gap++; buco < bl_sel_count; buco++ )
          if ( bl_sel[buco]-1 == bl_sel[buco-1] )
            gap++;
          else
            break; 
   }
       
   /*printf("test step 3  del_blocchi\n");*/

   /* Aggiorna gli indici dei blocchi nelle connessioni */
/*******************
   VERSIONE DI GIANKY - Commentata per sicurezza
   for ( i=0; i<bl_sel_count; i++ )
   {
      printf("\nAggiornamento indici %d\n",i);
      for ( j=0; j<num_blocchi-bl_sel_count; j++ )
      {
        printf("Agg. indici per blocco n. %d\n",j);
        ncanc=0;
        for ( lista_con = blocchi[j].variabili_connesse;
              lista_con;
              lista_con = lista_con->succ
            )
        {
          printf("Indici lista_con->%d\n",lista_con);
          if ( lista_con->blocco_esterno > bl_sel[i] )
          {
            (lista_con->blocco_esterno)--;  
          }
        }
      }
   }
   
  SOSTITUITA Con La seguente
**************************/

      for ( j=0; j<num_blocchi-bl_sel_count; j++ )
      {
        /*printf("Agg. indici per blocco n. %d\n",j);*/
        for ( lista_con = blocchi[j].variabili_connesse;
              lista_con;
              lista_con = lista_con->succ
            )
        {
          /*printf("Indici lista_con->%d\n",lista_con);*/
          for ( i=0; i<bl_sel_count; i++ )
          {
             if ( lista_con->blocco_esterno > bl_sel[i] )
               ncanc++;

          }
          if(ncanc)
          {
             lista_con->blocco_esterno -= ncanc;
             /*printf("il blocco esterno adesso vale %d \n",lista_con->blocco_esterno);*/
             ncanc=0;
          }
        }
      }


   /* Aggiorna il numero dei blocchi */
   num_blocchi = num_blocchi - bl_sel_count;

   /*printf("test step end del_blocchi\n");*/

}







libera_blocco( num )
int num;
{
   libera_con ( blocchi[num].variabili_connesse );
   free ( blocchi[num].variabili );
}


libera_con( lista )
CONN *lista;
{
   if ( lista )
     libera_con( lista->succ );
   free( lista );
}



cancella_con( bl1, bl2, var )
int bl1, bl2, var;
{

  CONN *cur, *rem;

  cur = blocchi[bl1].variabili_connesse;

  if ( cur->blocco_esterno == bl2 && cur->var_esterna == var )
  {
    blocchi[bl1].variabili[cur->var_interna].connessioni--;
    blocchi[bl1].variabili_connesse = cur->succ;
    free ( cur );
    return;
  }


  for ( ;
        cur->succ && ( cur->succ->blocco_esterno != bl2 ||
                       cur->succ->var_esterna != var );
        cur = cur->succ )
   ;

  if ( ! cur->succ )
  {
     printf( "Connessione non in lista !!!" );
     exit( 0 );
  }

  blocchi[bl1].variabili[cur->succ->var_interna].connessioni--;

  rem = cur->succ;
  cur->succ = cur->succ->succ;
  free ( rem );

}




