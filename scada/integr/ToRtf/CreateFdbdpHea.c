/*
   modulo CreateFdbdpHea.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFdbdpHea.c	2.4
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <ToRtf.h>
#include <db.h>
#include <dconf.inc>
#include <string.h>

extern char path_txt[FILENAME_MAX+1];
extern DB_HEADER header_ToRtf;

int CreateFdbdpHea()
{
ID_TABLE *tabella;
VAL_RET valore;
FILE *fp;
int ora,minuti,secondi,milli;
int giorno,mese,anno,gio_set,gio_anno;

printf("Creazione file [%s] fdbdp.hea\n",path_txt);

tabella = OpenTablePath(path_txt,CONFIGURAZIONEDB);
if(tabella == NULL)
	{
	fprintf(stderr,"CreateFdbdpHea: apertura tabella\n");
	return(0);
	}
if(NumRecord(tabella)<1)
	{
	fprintf(stderr,"CreateFdbdpHea: record non presenti\n");
	return(0);
	}

memset(&header_ToRtf,0,sizeof(DB_HEADER));

//  nome
if(GetVal(tabella,"Tipo",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal Tipo\n");
	return(0);
	}
strcpy(header_ToRtf.nome,valore.char_val);

//  descrizione
if(GetVal(tabella,"NomeImpianto",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal NomeImpianto\n");
	return(0);
	}
strcpy(header_ToRtf.descrizione,valore.char_val);

//  subuten
if(GetVal(tabella,"subuten",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal subuten\n");
	return(0);
	}
strcpy(header_ToRtf.subuten,valore.char_val);

// Setto data e ora creazione database

if(GetOra(&ora,&minuti,&secondi,&milli)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetOra\n");
	return(0);
	}

if(GetData(&giorno,&mese,&anno,&gio_set,&gio_anno)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetData\n");
	return(0);
	}

header_ToRtf.data.day = giorno;
header_ToRtf.data.month = mese;
header_ToRtf.data.year = anno;
header_ToRtf.data.dayofweek = gio_set;

header_ToRtf.ora.hour = ora;
header_ToRtf.ora.minute = minuti;
header_ToRtf.ora.second = secondi;
header_ToRtf.ora.hsecond = milli/10;

// setto le dimensioni del database

//  dimaa
if(GetVal(tabella,"DimAA",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimAA\n");
	return(0);
	}
header_ToRtf.dimaa=valore.int_val;

//  dimas
if(GetVal(tabella,"DimAS",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimAS\n");
	return(0);
	}
header_ToRtf.dimas=valore.int_val;

//  dimac
if(GetVal(tabella,"DimAC",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimAC\n");
	return(0);
	}
header_ToRtf.dimac=valore.int_val;

//  dimad
if(GetVal(tabella,"DimAD",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimAD\n");
	return(0);
	}
header_ToRtf.dimad=valore.int_val;

//  dimao
if(GetVal(tabella,"DimAO",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimAO\n");
	return(0);
	}
header_ToRtf.dimao=valore.int_val;

//  dimda
if(GetVal(tabella,"DimDA",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimDA\n");
	return(0);
	}
header_ToRtf.dimda=valore.int_val;

//  dimds
if(GetVal(tabella,"DimDS",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimDS\n");
	return(0);
	}
header_ToRtf.dimds=valore.int_val;

//  dimdc
if(GetVal(tabella,"DimDC",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimDC\n");
	return(0);
	}
header_ToRtf.dimdc=valore.int_val;

//  dimdd
if(GetVal(tabella,"DimDD",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimDD\n");
	return(0);
	}
header_ToRtf.dimdd=valore.int_val;

//  dimdo
if(GetVal(tabella,"DimDO",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal DimDO\n");
	return(0);
	}
header_ToRtf.dimdo=valore.int_val;

//  dimor
if(GetVal(tabella,"Organi",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal Organi\n");
	return(0);
	}
header_ToRtf.dimor=valore.int_val;

//  dimst
if(GetVal(tabella,"Stringhe",0,&valore)!=1)
	{
	fprintf(stderr,"CreateFdbdpHea: Errore GetVal Stringhe\n");
	return(0);
	}
header_ToRtf.dimst=valore.int_val;

fp=fopen("fdbdp.hea","w");
fwrite(&header_ToRtf,sizeof(DB_HEADER),1,fp);
fclose(fp);

if(!CloseTable(tabella))
	{
	fprintf(stderr,"CreateFdbdpHea: Errore chiusura tabella\n");
	return(0);
	}
return(1);
}
