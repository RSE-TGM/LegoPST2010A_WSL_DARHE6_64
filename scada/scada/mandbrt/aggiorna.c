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
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> AGGIORNAN.C
        la function aggiornan visualizza valori
        e flag dei punti analogici
        scorrendo la tabella vispun

        tipo input int tipo di analogico
*/
#include <stdlib.h>
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "tabelle.inc"
#include "deflag.inc"
#include "ansiscr.h"
#include "ctasti.inc"

aggiornan(indice)
short indice;
{
short punt;
short tot,i ;
float vatt ;    /* valore attuale */
char chvatt[50];
short flag;     /* flag generali */
short flaa;     /* flag acquisizione */
union  all { float f;
             unsigned char  c[4];
             short s[2];} valbs,valas,valac,valbc ; /* allarmi */

/*
        leggo dal data base i valori da visualizzare in
        base al tipo di analogico
*/
		  punt=vispun.punt[indice] ;
        switch (vispun.ext[indice])
        {
        case g1tipaa :
                vatt=dbaav[punt];
                flag=dbaaf[punt];
                valbs.f=dbaaal[punt].bass_sic.fval;
                valas.f=dbaaal[punt].alto_sic.fval;
                valac.f=dbaaal[punt].alto_con.fval;
                valbc.f=dbaaal[punt].bass_con.fval;
                flaa=dbaafa[punt] << 8;
                break ;
        case g1tipas :
                vatt=dbasv[punt];
                flag=dbasf[punt];
                valbs.f=dbasal[punt].bass_sic.fval;
                valas.f=dbasal[punt].alto_sic.fval;
                valac.f=dbasal[punt].alto_con.fval;
                valbc.f=dbasal[punt].bass_con.fval;
                break ;
        case g1tipac :
                vatt=dbacv[punt];
                flag=dbacf[punt];
                valbs.f=dbacal[punt].bass_sic.fval;
                valas.f=dbacal[punt].alto_sic.fval;
                valac.f=dbacal[punt].alto_con.fval;
                valbc.f=dbacal[punt].bass_con.fval;
                break ;
        case g1tipad :
                vatt=dbadv[punt];
                flag=dbadf[punt];
                valbs.f=dbadal[punt].bass_sic.fval;
                valas.f=dbadal[punt].alto_sic.fval;
                valac.f=dbadal[punt].alto_con.fval;
                valbc.f=dbadal[punt].bass_con.fval;
                break ;
		  case g1tipao :
					 flag=dbaof[punt];
					 break;
        }
/*
        scrittura dei valori e dei flag
*/
        tot=indice*num_righe+1+off_val;
		  if(vispun.ext[indice] != g1tipao)
		  {
			  scrxy(tot,val_pos);
			  printf("%#8.2f",vatt);
		  }
        tot=indice*num_righe+1+off_flag ;
        for(i=0;i<16;i++)             /* flag generici */
        {
                if(bitvalue(&flag,i))
                {     
						 	scrxy(tot,flag_pos+3*i);
							printf("%s",sigfan[i]);
                }
                else 
                {     
						 	scrxy(tot,flag_pos+3*i);
							printf("  ");
                }
        }
        if(vispun.ext[indice]==g1tipaa) /* flag acquisizione */
        {
                tot=indice*num_righe+1+off_flaa ;
                for(i=0;i<8;i++)
                {       if(bitvalue(& flaa,i))
                        {   
								 	scrxy(tot,flaa_pos+3*i);
									printf("%s",sigfaa[i]);
                        }
                        else 
                        {   
								 	scrxy(tot,flaa_pos+3*i);
									printf("  ");
                        }
                }
        }
/*
        scrittura limiti allarme		non se ao
*/
if(vispun.ext[indice] != g1tipao)
{
        scrivi_all(valas,indice*num_righe+1+off_allv,sa_pos,0);
        scrivi_all(valac,indice*num_righe+1+off_allv,ca_pos,0);
        scrivi_all(valbs,indice*num_righe+1+off_allv,sb_pos,0);
        scrivi_all(valbc,indice*num_righe+1+off_allv,cb_pos,0);
}
}

