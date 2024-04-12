/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
#include <unixio.h>
#include <file.h>
#include <stdio.h>

#include "define.h"
#include "documentaz.h"

#define ABILITA		0
#define DISABILITA 	1

#define SX_DX		0
#define	UP_DOWN		1



static struct dsc$descriptor_s _tmp = {0,DSC$K_DTYPE_T,DSC$K_CLASS_S,0};
struct unita_misura unimis[14];
short keymap[4];
int termin;

$DESCRIPTORA(_keymap ,keymap ,short);

main()
{
  short j,i,index,temp;
  char curs;

  init_unimis(unimis);
  if ( !access("unimis_doc.dat",0) )
      leggi_file(unimis);

  fdv$aterm(&_tcarea,&12,&2);
  statoFMS();
  fdv$awksp(&_workspace,&5400);
  statoFMS();
  fdv$cdisp($DESCR("UNI_MIS"));

  fdv$spada(&1);
/* Visualizza i tipi delle variabili con le possibili unita di misura */
  for (j=0; j < N_UNITA_MISURA ;j++)
     {
       POINTER(_tmp) = unimis[j].nome_tipo;
       LENGTH (_tmp) = 8;
       temp=j+1;
       fdv$put(&_tmp,$DESCR("NSEL"),&temp);
       for (i=0; i<5; i++)
          {
            POINTER(_tmp) = unimis[j].codm[i];
            LENGTH (_tmp) = 6;
            temp=j*5+i+1;
            fdv$put(&_tmp,$DESCR("NO"),&temp);
          }
     }
  for (j=1 ; j<= N_UNITA_MISURA ;j++)
    {
      temp=(j-1)*5+unimis[j-1].sele;
      fdv$afva( &4,$DESCR("NO"),&temp); 
    }

  index=1;
  while (1)
    {

      POINTER(_tmp) = &curs;
      LENGTH (_tmp) = 1;

      fdv$afva(&4,$DESCR("NSEL"),&index);
      statoFMS();
      defkey(UP_DOWN,ABILITA);
      defkey(SX_DX,ABILITA);
      fdv$get(&_tmp,&termin,$DESCR("SEL"),&index);
      statoFMS();
      defkey(UP_DOWN,DISABILITA);
      defkey(SX_DX,DISABILITA);

      switch (termin)
        {
         case FDV$K_AR_RIGHT: fdv$afva(&0,$DESCR("NSEL"),&index);
                              index=(index >= 14) ? 1 : index+1;
                              fdv$afva(&4,$DESCR("NSEL"),&index);
                              break;

         case FDV$K_AR_LEFT : fdv$afva(&0,$DESCR("NSEL"),&index);
                              index=(index <= 1) ? 14 : index-1;
                              fdv$afva(&4,$DESCR("NSEL"),&index);
                              break;

         case FDV$K_AR_DOWN : selez_uni(index); 
                              break;
        }
      if (termin == FDV$K_KP_0 || termin == FDV$K_KP_PER)
        break;
    }
  if (termin == FDV$K_KP_0)
    salva_unita();

/* chiudi le maschere FMS ed esci */
  fdv$clear();
  fdv$clear_va();
  fdv$dwksp(&_workspace);
  fdv$dwksp(&_tcarea);
  exit(0);
}

/* funzione selez_uni(index,unimis)
  seleziona l'unita' di misura relativo al tipo considerato*/
selez_uni(index)
int index;
{
char curs;
short int ind_uni;

while(1)
 {
   POINTER(_tmp) = &curs; 
   LENGTH (_tmp) = 1;

   ind_uni=(index-1)*5+unimis[index-1].sele;
   defkey(UP_DOWN,ABILITA);
   fdv$get(&_tmp,&termin,$DESCR("CU"),&ind_uni);
   defkey(UP_DOWN,DISABILITA);
   fdv$afva(&0,$DESCR("NO"),&ind_uni);

   switch (termin) {
   case FDV$K_AR_DOWN: unimis[index-1].sele++;
                       if (unimis[index-1].sele > 5 || 
                           empty(unimis[index-1].codm[unimis[index-1].sele-1]))
                         unimis[index-1].sele=1;
                       break;

   case FDV$K_AR_UP  : fdv$afva(&0,$DESCR("NO"),&ind_uni);
                       unimis[index-1].sele--;
                       if (unimis[index-1].sele < 1 )
                         unimis[index-1].sele=5;
                       while (
                           empty(unimis[index-1].codm[unimis[index-1].sele-1])
                             ) unimis[index-1].sele--;
                       break;
   }
   ind_uni=(index-1)*5+unimis[index-1].sele;
   fdv$afva(&4,$DESCR("NO"),&ind_uni);
   if (termin == FDV$K_FT_NTR || termin == FDV$K_KP_0 ||
       termin == FDV$K_KP_PER)
     return;
 }
}
 

/* funzione salva_unita()
 salva nel file UNIMIS_DOC.DAT le unita di misura selezionate
 per ogni tipo di variabile */
salva_unita()
{
  char buffer[9];
  short n,i;
  FILE *fd;
  struct rec_umis *punt = (struct rec *) buffer;

  cancella_file("unimis_doc.dat");
  fd=fopen("unimis_doc.dat","w+");
/* O_WRONLY,777); */
  if (fd == NULL)
    pr_errore("FOPEN(): errore apertura UNIMIS_DOC.DAT");
  for (i=0; i < N_UNITA_MISURA; i++ )
     {
       strncpy(punt->nome_tipo,unimis[i].nome_tipo,8);
       punt->sele = unimis[i].sele;
       n = write(fileno(fd),punt,sizeof(struct rec_umis));
       if ( n == EOF )
         pr_errore("WRITE(): errore scrittura su disco");

    }
  fclose(fd);
}

/* funzione defkey()
 Abilita/disabilita la funzionalita dei tasti freccia */
defkey( tasti,funzione)
short tasti,funzione;
{
  if ( funzione == ABILITA )
    {
      keymap[1] = FDV$K_KF_NONE;
      keymap[3] = FDV$K_KF_NONE;     
    }
  else
    {
      keymap[1] = FDV$K_KF_DFLT;
      keymap[3] = FDV$K_KF_DFLT;
    }

  if ( tasti == UP_DOWN )
    {
      keymap[0] = FDV$K_KF_SBK;
      keymap[2] = FDV$K_KF_SFW;
    }
  else
    {
      keymap[0] = FDV$K_KF_CRSRT;
      keymap[2] = FDV$K_KF_CRSLF;
    }
  fdv$dfkbd(&_keymap,&2);
}
  
