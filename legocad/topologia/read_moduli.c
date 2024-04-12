/**********************************************************************
*
*       C Source:               read_moduli.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:59:33 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: read_moduli.c,2 %  (%full_filespec: 1,csrc,read_moduli.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)read_moduli.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/


#include <stdio.h>
#include "lg1.h"
#include "errore.h"


extern ERR_LEVEL err_level;

static FILE *lis_mod;


read_moduli()
{
  int i;
  char path[1024];


  /* Apertura del file lista_moduli.dat. */
  strcpy( path, modello.path_legocad );
  strcat( path, "libut/lista_moduli.dat" );
  if ( !(lis_mod=fopen ( path, "r" )) )
  {
    err_level = ERROR;
    errore ( OPEN_LIS_MOD_ERR, modello.nome );
    return;
  }
   
  get_moduli();

  for(i=0;i<num_tot_moduli;i++)
     moduli[i].tipo = PROCESSO;

  fclose( lis_mod );


  /* Apertura del file lista_schemi.dat. */
  strcpy( path, modello.path_legocad );
  strcat( path, "libut_reg/lista_schemi.dat" );
  if ( !(lis_mod=fopen ( path, "r" )) )
  {
    err_level = ERROR;
    errore ( OPEN_LIS_SCH_ERR, modello.nome );
    return;
  }
   
  get_moduli();

  for(i;i<num_tot_moduli;i++)
    moduli[i].tipo = REGOLAZIONE;

  fclose( lis_mod );
}



get_moduli()
{
   char riga[85];

   for ( ;; num_tot_moduli++ )
   {
      if ( fgets( riga, 85, lis_mod ) )
      {
        if ( num_tot_moduli == MAX_MODULI )
        {
          err_level = ERROR;
          errore ( MAX_MOD_ERR, modello.nome );
          return;
        }

        strncpy ( moduli[num_tot_moduli].sigla, riga, 4 );
        moduli[num_tot_moduli].sigla[4] = '\0';  
        memcpy(moduli[num_tot_moduli].descr,&(riga[5]),75);
        moduli[num_tot_moduli].descr[74]= '\0';
      }
      else
        break;
   }
}
