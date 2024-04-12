/*
   modulo CreateFdde.c
   tipo 
   release 2.9
   data 6/13/96
   reserved @(#)CreateFdde.c	2.9
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "ToRtf.h"
#include "db.h"
#include "dconf.inc"
#include "CreateFdde.h"
#include "fileop.inc"

extern DB_HEADER header_ToRtf;
extern char path_txt[FILENAME_MAX+1];

int CreateFdde()
{
FILE *fp;
VAL_RET valore;
ID_TABLE *tabella;
int i,num_record,ian,idi;
REC_FDDE fdde;

fp=fopen("fdde.rtf","w+");

ian=header_ToRtf.dimaa+header_ToRtf.dimas+header_ToRtf.dimac+header_ToRtf.dimad+header_ToRtf.dimao;
idi=header_ToRtf.dimda+header_ToRtf.dimds+header_ToRtf.dimdc+header_ToRtf.dimdd;

// Inizializzazione del file
memset(&fdde,0,sizeof(fdde));
for(i=0;i<ian;i++)
	fwrite(&fdde,1,sizeof(REC_FDDE_AN),fp);
for(i=0;i<idi;i++)
	fwrite(&fdde,1,sizeof(REC_FDDE_DIG),fp);
for(i=0;i<header_ToRtf.dimdo;i++)
	fwrite(&fdde,1,sizeof(REC_FDDE_DO),fp);
for(i=0;i<header_ToRtf.dimor;i++)
	fwrite(&fdde,1,sizeof(REC_FDDE_OR),fp);
for(i=0;i<header_ToRtf.dimst;i++)
	fwrite(&fdde,1,sizeof(REC_FDDE_ST),fp);

// An. Acquisiti
tabella=OpenTablePath(path_txt,AA);
fseek(fp,of_fdaa,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella AA\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeAn(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore AA\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_AN),fp);
}
CloseTable(tabella);

// An. Standard
tabella=OpenTablePath(path_txt,AS);
fseek(fp,of_fdas,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella AC\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeAn(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore AS\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_AN),fp);
}
CloseTable(tabella);

// An. Non Standard
tabella=OpenTablePath(path_txt,AC);
fseek(fp,of_fdac,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella AC\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeAn(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore AC\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_AN),fp);
}
CloseTable(tabella);

// An. Diagnostica
tabella=OpenTablePath(path_txt,AD);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella AD\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeAn(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore AD\n");
                return(0);
        }

	if(GetVal(tabella,"IndDB",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal IndDB\n");
		return(0);
	}

	fseek(fp,of_fdad+sizeof(REC_FDDE_AN)*valore.int_val,SEEK_SET);
	fwrite(&fdde,1,sizeof(REC_FDDE_AN),fp);
}
CloseTable(tabella);

// An. Uscita
tabella=OpenTablePath(path_txt,AO);
fseek(fp,of_fdao,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella AO\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeAn(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore AO\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_AN),fp);
}
CloseTable(tabella);

// Dig. Acquisiti
tabella=OpenTablePath(path_txt,DA);
fseek(fp,of_fdda,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella DA\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeDi(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore DA\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_DIG),fp);
}
CloseTable(tabella);

// Dig. Standard
tabella=OpenTablePath(path_txt,DS);
fseek(fp,of_fdds,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella DS\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeDi(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore DS\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_DIG),fp);
}
CloseTable(tabella);

// Dig. Non Standard
tabella=OpenTablePath(path_txt,DC);
fseek(fp,of_fddc,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella DC\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeDi(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore DC\n");
                return(0);
        }
	fwrite(&fdde,1,sizeof(REC_FDDE_DIG),fp);
}
CloseTable(tabella);

// Dig. Diagnostica
tabella=OpenTablePath(path_txt,DD);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella DD\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetFddeDi(tabella,i,&fdde)!=1)
        {
                fprintf(stderr,"CreateFdde: Errore DD\n");
                return(0);
        }

	if(GetVal(tabella,"IndDB",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal IndDB\n");
		return(0);
	}

	fseek(fp,of_fddd+sizeof(REC_FDDE_DIG)*valore.int_val,SEEK_SET);
	fwrite(&fdde,1,sizeof(REC_FDDE_DIG),fp);
}
CloseTable(tabella);

// Dig. Uscita
tabella=OpenTablePath(path_txt,DO);
fseek(fp,of_fddo,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella DO\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	memset(&fdde,' ',sizeof(REC_FDDE));

	if(GetVal(tabella,"Sigla",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Sigla\n");
		return(0);
	}
	memcpy(fdde._di.Sigla,valore.char_val,min(strlen(valore.char_val),SCD_SIGLA));

	if(GetVal(tabella,"Descrizione",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Descrizione\n");
		return(0);
	}
	memcpy(fdde._di.Descrizione,valore.char_val,min(strlen(valore.char_val),SCD_DESCRIZIONE));

	fwrite(&fdde,1,sizeof(REC_FDDE_DO),fp);
}
CloseTable(tabella);

// Organi
tabella=OpenTablePath(path_txt,OR);
fseek(fp,of_fdor,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella OR\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	memset(&fdde,' ',sizeof(REC_FDDE));

	if(GetVal(tabella,"Sigla",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Sigla\n");
		return(0);
	}
	memcpy(fdde._or.Sigla,valore.char_val,
			min(strlen(valore.char_val),SCD_SIGLA));

	if(GetVal(tabella,"Descrizione",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Descrizione\n");
		return(0);
	}
	memcpy(fdde._or.Descrizione,valore.char_val,
		min(strlen(valore.char_val),SCD_DESCRIZIONE));

	if(GetVal(tabella,"Tipo",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Tipo\n");
		return(0);
	}
	memcpy(fdde._or.Tipo,valore.char_val,
		min(strlen(valore.char_val),SCD_TIPOR));

	fwrite(&fdde,1,sizeof(REC_FDDE_OR),fp);
}
CloseTable(tabella);

// Stringhe
tabella=OpenTablePath(path_txt,ST);
fseek(fp,of_fdst,SEEK_SET);
if(!tabella)
{
	fprintf(stderr,"CreateFdde: apertura tabella ST\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	memset(&fdde,' ',sizeof(REC_FDDE));

	if(GetVal(tabella,"Sigla",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Sigla\n");
		return(0);
	}
	memcpy(fdde._st.Sigla,valore.char_val,
			min(strlen(valore.char_val),SCD_SIGLA));

	if(GetVal(tabella,"Descrizione",i,&valore)!=1)
	{
		fprintf(stderr,"Errore GetVal Descrizione\n");
		return(0);
	}
	memcpy(fdde._st.Descrizione,valore.char_val,
		min(strlen(valore.char_val),SCD_DESCRIZIONE));

	fwrite(&fdde,1,sizeof(REC_FDDE_ST),fp); 
}
CloseTable(tabella);

fclose(fp);
return(1);
}

int GetFddeAn(ID_TABLE *tabella,int i,REC_FDDE *fdde)
{
VAL_RET valore;
memset(fdde,' ',sizeof(REC_FDDE));

if(GetVal(tabella,"Sigla",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Sigla\n");
	return(0);
}
memcpy(fdde->_an.Sigla,valore.char_val,min(strlen(valore.char_val),SCD_SIGLA));

if(GetVal(tabella,"Descrizione",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Descrizione\n");
	return(0);
}
memcpy(fdde->_an.Descrizione,valore.char_val,
		min(strlen(valore.char_val),SCD_DESCRIZIONE));

if(GetVal(tabella,"Unitamisura",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Unitamisura\n");
	return(0);
}
memcpy(fdde->_an.Altro,valore.char_val,min(strlen(valore.char_val),SCD_UNIMIS));

return(1);
}

int GetFddeDi(ID_TABLE *tabella,int i,REC_FDDE *fdde)
{
VAL_RET valore;
memset(fdde,' ',sizeof(REC_FDDE));

if(GetVal(tabella,"Sigla",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Sigla\n");
	return(0);
}
memcpy(fdde->_di.Sigla,valore.char_val,min(strlen(valore.char_val),SCD_SIGLA));

if(GetVal(tabella,"Descrizione",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Descrizione\n");
	return(0);
}
memcpy(fdde->_di.Descrizione,valore.char_val,min(strlen(valore.char_val),SCD_DESCRIZIONE));

if(GetVal(tabella,"Stato0",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Stato0\n");
	return(0);
}
memcpy(fdde->_di.Stato0,valore.char_val,min(strlen(valore.char_val),SCD_STATO));

if(GetVal(tabella,"Stato1",i,&valore)!=1)
{
	fprintf(stderr,"Errore GetVal Stato1\n");
	return(0);
}
memcpy(fdde->_di.Stato1,valore.char_val,min(strlen(valore.char_val),SCD_STATO));
return(1);
}
