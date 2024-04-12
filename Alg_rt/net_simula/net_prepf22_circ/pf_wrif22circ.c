/**********************************************************************
*
*       C Source:               pf_wrif22circ.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Feb 15 11:11:33 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pf_wrif22circ.c-7 %  (%full_filespec: pf_wrif22circ.c-7:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)pf_wrif22circ.c	5.3\t11/30/95";
/*
   modulo pf_wrif22circ.c
   tipo 
   release 5.3
   data 11/30/95
   reserved @(#)pf_wrif22circ.c	5.3
*/
# include <stdio.h>
# include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
#else
#include <unixio.h>
#include <file.h>
#include "vmsipc.h"
#endif  /* UNIX */
# include "sim_param.h"		/* parametri generali LEGO       */
# include "sim_types.h"
# include "comandi.h"
# include "sim_ipc.h"		/* parametri per semafori        */
# include "f22_circ.h"
# include "pf_macro.h"		/* macro per switch VMS-UNIX    */
# include <Rt/RtDbPunti.h>
# include <Rt/RtErrore.h>


extern int      num_var_graf;	/* numero variabili per f22      */
extern int     *iout_graf;	/* indirizzi variabili per f22   */
extern int      id_msg_prep;

extern int      append_mode;

extern RtDbPuntiOggetto dbpunti;


extern FILE    *fpda;		/* f22circ.dat file dati        */
FILE    *fpascii;		/* f22ascii.dat file dati ascii       */

float          *variabili_grafiche = NULL;	/* Vettore valori da
						 * registrare */
F22CIRC_T       istante;	/* Istante del campione salvato */
extern F22CIRC_HD header;	/* Struttura degli header       */

extern int      variabili_registrate; /* numero delle variabili effettivamente
                                     registrate     */

extern int      num_campioni;  /* numero dei campioni registrati */

int             file_full = 0;
int             prima_volta_wr = 1;
int             offheader;


pf_wrif22circ()
{
static int      iniz_mem;
static int      fine_mem;
int             i, ret, addr;
MSG_AUS         messaggio;
static float    tempo = -1;
int             offsetpunt;
int             offsetdati;
int             size_campione;
extern int	scrivi_f22_ascii;

   offheader=sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +
             sizeof(F22CIRC_VAR) * variabili_registrate;
#if defined DEBUG_PF22
   printf("\t\t pf_wrif22circ offheader=%d\n", offheader);
#endif

/* Alloca buffer-variabile dinamica  */
   offsetpunt = sizeof(HEADER_REGISTRAZIONI);

   if (prima_volta_wr == 1)
     {
     variabili_grafiche = (float *) calloc(variabili_registrate + 1, 
                                           sizeof(float));
     prima_volta_wr = 0;
     if (append_mode == 0)
       {
       header.p_iniz = 1;
       offsetdati = offheader;
       }
     else
       {
       leggi_header(&header, sizeof(F22CIRC_HD));

       offsetdati = offheader + ( (variabili_registrate + 1) * sizeof(float) ) *
                              (header.p_fine);
       if (header.p_iniz > header.p_fine)
          file_full = 1;
       else
         file_full = 0;
/* #if defined DEBUG_PF22 */
       printf("net_prepf22_circ prima lettura fp: fpi=%d fpf=%d file_full=%d\n",
               header.p_iniz, header.p_fine, file_full);
/* #endif */
       iniz_mem = header.p_iniz;
       fine_mem = header.p_fine;
       }
     size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);
#if defined DEBUG_PF22
     printf("\t\t size_campione=%d\n",size_campione);
     printf("\t\t Primo spostamento in offsetdati=%d \n",offsetdati);
#endif
     sposta(fpda, offsetdati);
     }
  else
     {
     offsetdati = offheader + ( (variabili_registrate + 1) * sizeof(float) ) *
                              (header.p_fine);
#if defined DEBUG_PF22
     printf("\t\t Sposta in offsetdati=%d \n",offsetdati);
#endif
     sposta(fpda, offsetdati);
     }


  if ((prima_volta_wr == -1) && (append_mode == 1))
     {
     prima_volta_wr--;
     header.p_iniz = iniz_mem;
     header.p_fine = fine_mem;
     }
  else if ((prima_volta_wr == 0) && (append_mode == 1))
          {
/*        Il primo campione e' gia' scritto, non si riscrive */
          prima_volta_wr--;
          messaggio.mtype = PREP_F22 + OFFSET_AUS;
          msg_snd(id_msg_prep, &messaggio, sizeof(TIPO_AUS), !IPC_NOWAIT);
          return;
          }

/* Gestione degli indici inizio file */
   header.p_fine++;
   if (file_full)
     {
     header.p_iniz++;
     }
   if ((header.p_iniz > num_campioni))
     {
     header.p_iniz = 1;
     }
   if ((header.p_fine > num_campioni))
     {
     file_full = 1;
     header.p_fine = 1;
     header.p_iniz = 2;
     offsetdati = offheader;
#if defined DEBUG_PF22
     printf("\t\t rispostato in offsetdati=%d\n",offsetdati);
#endif
     ret = sposta(fpda, offsetdati);
     }

  /* Struttura tempo */
  RtDbPGetTime(dbpunti,&(variabili_grafiche[0]));
/*
printf("pf_wrif22circ: variabili_grafiche[0]=%f\n",variabili_grafiche[0]);
*/
  /* Buffer delle variabili */
  for (i = 0; i < variabili_registrate; i++)
     {
     if (iout_graf[i] != -1)
       {
       addr = iout_graf[i];
       RtDbPGetValue(dbpunti,addr,&variabili_grafiche[i + 1]);
       }
     }

/* Rilascia lo sked */
   messaggio.mtype = PREP_F22 + OFFSET_AUS;
   msg_snd(id_msg_prep, &messaggio, sizeof(TIPO_AUS), !IPC_NOWAIT);


/* Aggiornamento dati */
   scrivi(variabili_grafiche, sizeof(float), variabili_registrate + 1, fpda);
   fluscia(fpda);

/* Scrittura file ASCII con gli ultimi valori delle variabili */
   if ( scrivi_f22_ascii==1 && variabili_registrate >= 1)
      {
#if defined DEBUG_PF22
     printf("\t\t dentro Scrittura file ASCII variabili_registrate=%d \n", variabili_registrate);
#endif
      fpascii=fopen("f22ascii.dat", "w+");
      // Scrivo il valore del tempo
      fprintf(fpascii,"%f",variabili_grafiche[0]);
      // Scrivo il valore delle restanti variabili separate da ;
      for (i = 1; i<=variabili_registrate; i++)
          {
          fprintf(fpascii,";%f",variabili_grafiche[i]);
          }
      fclose(fpascii);
      }

   RtDbPGetTime(dbpunti,&tempo);


/* Aggiornamento header */
#if defined DEBUG_PF22
   printf("\t\t Scrittura header: sposta in offsetpunt=%d\n\n",offsetpunt);
#endif
   sposta(fpda, offsetpunt);
   scrivi(&header, sizeof(F22CIRC_HD), 1, fpda);
   fluscia(fpda);
}



/*
 * File aperti mediante fopen Legge l' header dal file f22circ.dat 
 */
int leggi_header(F22CIRC_HD * head, int size)
{
int             ret, i = 0;
int             offset=sizeof(HEADER_REGISTRAZIONI);

  fclose(fpda);
  fpda = fopen("f22circ.dat", "r+");
  sposta(fpda, offset);
  ret = fread(head, size, 1, fpda);
  while (ret <= 0)
  {
    i++;
    if (i > 100)
      break;
    printf("#");
    ret = fread(head, size, 1, fpda);
  }
  return (ret);
}
