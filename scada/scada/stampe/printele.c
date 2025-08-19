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
/* printele

        la function printar prepara le stringhe degli allarmi
        di tipo generico per una stampa di tutta una pagina
		  allarmi

   15 Giugno 1995
   Inizializzazione campo szvir =-1 stampante default per tabulati
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "g1tipdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"

extern long  off_f[] ;     /* definiti nel main mpscs */
extern short nbyte[] ;     /* come sopra */

// Function declarations
int rbyte(int fd, short *buffer, int offset, int count);
void decnum(char *str, int width, int precision, short value, float fvalue);
void invia(int printer, void *message);
float vsoglia();

void printele (ele)
S_STELEN *ele ;
{
char desc[rec_fdda] ;           /* dimens. come il piu' */
                                /* grande dei record descrittori */
long tot;
union u_elenchi	{	S_FOREL_AN 	an;
							S_FOREL_AL	all;
							S_FOREL_DI	di;
						} stam;
float valore;


memset(&stam.all.blank_1,' ',sizeof(S_FOREL_AL)-sizeof(HEA_STA));

/*
	se il puntatore == -1 messggio fittizio per forzare l'intestazione
	in caso di nessun punto in elenco
*/
stam.all.hea.lung=sizeof(S_FOREL_DI);
stam.all.hea.szvir=-1;
if(ele->punt==-1) goto SEND;
/*
        leggo il record dal file descrittore
*/
tot=off_f[ele->ext]+(long)nbyte[ele->ext]*(long)ele->punt;
rbyte(fileno(fpp[fdde]),(short *)desc,tot,nbyte[ele->ext]);

memcpy(stam.an.nome,desc,SCD_SIGLA);

memcpy(stam.an.desc,&desc[SCD_SIGLA],SCD_DESCRIZIONE);

switch (ele->flag)
{
case ELE_HC_HS_LC_LS:
case ELE_AL:
	stam.all.hea.lung=sizeof(S_FOREL_AL);
	memcpy(stam.all.umis,&desc[SCD_SIGLA+SCD_DESCRIZIONE],c_umis);
	decnum(stam.all.valhs,8,2,0,vsoglia(ele->punt,ele->ext,0)) ;
	decnum(stam.all.valhc,8,2,0,vsoglia(ele->punt,ele->ext,2)) ;
	decnum(stam.all.vallc,8,2,0,vsoglia(ele->punt,ele->ext,3)) ;
	decnum(stam.all.valls,8,2,0,vsoglia(ele->punt,ele->ext,1)) ;
	memcpy(&valore,ele->value,4);
	decnum(stam.all.value,8,2,0,valore) ;
	stam.all.eos=0x0D0A;
	stam.all.new=0x0D0A;
	break;
default:
	switch (ele->ext)
	{
		case g1tipaa:	case g1tipas:  case g1tipac:  case g1tipad:
		      stam.an.eos=0x0D0A;
			   stam.an.new=0x0D0A;
			   stam.an.hea.lung=sizeof(S_FOREL_AN);
				memcpy(stam.an.umis,&desc[SCD_SIGLA+SCD_DESCRIZIONE],c_umis);
				memcpy(&valore,ele->value,4);
				decnum(stam.an.value,8,2,0,valore) ;
				break;
		case g1tipda:	case g1tipds:  case g1tipdc:  case g1tipdd:
				stam.di.eos=0x0D0A;
				stam.di.new=0x0D0A;
				memcpy(stam.di.value,&desc[SCD_SIGLA+SCD_DESCRIZIONE+ele->value[0]*lun_stato],lun_stato);
				break;
		case g1tipor:
				stam.di.eos=0x0D0A;
				stam.di.new=0x0D0A;
            strncpy(stam.di.value,&stat_diz[ele->value[0]*lun_stato],lun_stato) ;
				break;
	}
	break;
}
SEND:
/*
        accodo la stringa da stampare al task gestore della 546
*/
invia(tpr_elenco,&stam) ;

return ;
}


