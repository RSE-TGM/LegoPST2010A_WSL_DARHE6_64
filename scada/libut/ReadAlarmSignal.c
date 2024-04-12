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
#ifdef ALARM_SIGNAL
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "ansiscr.h"
#include "g0strdb.inc"
#include "g2ptrdb.inc"
#include "dconf.inc"
#include "fileop.inc"
#include "comunic.inc"

void ReadAlarmSignal(DB_HEADER *);
int IsAlarmSignal(short);
int GetAlarmValue(short);
int SetAlarmValue(short,char);


void ReadAlarmSignal(db)
DB_HEADER *db;
{
int i;
extern long  off_f[] ;          /* definiti nel main mpscs */
extern short nbyte[] ;          /* come sopra */
long tot;
char *app;
char nome_var[SCD_SIGLA+1];
char descr_var[SCD_DESCRIZIONE+1];
char tipo_all;

       printf("ReadAlarmSignal\n");
/*
	verifico quali dei punti digitali acquisiti corrispondono 
	a dei segnali di allarme e a quale tipo di allarme ed eventualmete
	modifico il campo trattamento nel seguente modo:
	
	setto l'ottavo bit del trattamento a 1 e setto il codice di
	evento allarme nei sei bit meno significativi
*/
for(i=0;i<db->dimda;i++)
	if(dbdau[i]>=0)
		{
		tot=off_f[g1tipda]+(long)nbyte[g1tipda]*(long)i;
		rbyte(fileno(fpp[fdde]),(short*)nome_var,tot,SCD_SIGLA);
		nome_var[SCD_SIGLA]=0;
		if((app=strstr(nome_var,"$"))==NULL)
			continue;
		tipo_all=app[1];
		if((tipo_all<'A')||(tipo_all>'Z'))
			continue;
		tipo_all -='A';
		bitset(&dbdatr[i],8,1);
		SetAlarmValue(i,tipo_all);
		}

/*
	verifico quali calcolate standard siano calcolate relative a
	dei segnali allarmi
*/
for(i=0;i<db->dimas;i++)
	if((dbasu[i]>=0)&&((dbasde[i].g.tipoc==15)||(dbasde[i].g.tipoc==16)))
		{
		dbasde[i].g.sTipoAll= -1;
		dbasde[i].g.cont_err= 0;
		tot=off_f[g1tipas]+(long)nbyte[g1tipas]*(long)i;
		rbyte(fileno(fpp[fdde]),(short*)nome_var,tot,SCD_SIGLA);
		rbyte(fileno(fpp[fdde]),(short*)descr_var,
			tot+SCD_SIGLA,SCD_DESCRIZIONE);
		nome_var[SCD_SIGLA]=0;
		descr_var[SCD_DESCRIZIONE]=0;
//printf("%4d - [%s] - [%s]\n",i,nome_var,descr_var);
		if((app=strstr(nome_var,"$"))==NULL)
			continue;
		tipo_all=app[1];
		if((tipo_all<'A')||(tipo_all>'Z'))
			continue;
		tipo_all -='A';
		dbasde[i].g.sTipoAll= tipo_all;
		}
		
}

int IsAlarmSignal(short point)
{
if(bitvalue(&dbdatr[point],8))
	return(1);
else
	return(0);

}


int GetAlarmValue(short point)
{
short mask=0x003F;

return(mask&dbdatr[point]);
}


int SetAlarmValue(short point, char val)
{
short mask=0x003F;
short app;

app = val;
app = app & mask;

dbdatr[point] = dbdatr[point] | app;
}
#endif
