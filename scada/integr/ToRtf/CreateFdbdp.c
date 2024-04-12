/*
   modulo CreateFdbdp.c
   tipo 
   release 2.11
   data 10/14/96
   reserved @(#)CreateFdbdp.c	2.11
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
#include <malloc.h>
#include <math.h>
#include <ToRtf.h>
#include <db.h>
#include <dconf.inc>
#define _PUBLIC 0
#include <g1tipdb.inc>
#include <g2comdb.inc>
#include <g2ptrdb.inc>
#include <stdlib.h>

DB_HEADER header_ToRtf;
char *dballoc,*notenmem;

static int GetZona();
static int GetTratDig();
static int GetAll();
static int GetCalcAna();
static int GetCalcDig();
static int GetInib();
static int GetInvPol();
int SetPunt();
static int ClearDB();
static int GestDBALL(char *,union valin *);
int GestCALIN();
int ClearCALIN(S_CALIN *);
static int SoglieUguali(char *,char *,char *,char *);
extern char path_txt[FILENAME_MAX+1];

int CreateFdbdp()
{
FILE *fp;
char zero = 0;
int i;
int off;

printf("Creazione file fdbdp.rtf\n");


fp=fopen("fdbdp.rtf","w");
// scrittura header_ToRtf
fwrite(&header_ToRtf,sizeof(DB_HEADER),1,fp);
if((ldb_header - sizeof(DB_HEADER)) > 0)
	{
	for(i=0;i<ldb_header - sizeof(DB_HEADER);i++)
		fwrite(&zero,1,1,fp);
	}
// allocazione database
dballoc = (char*)malloc(100);
notenmem = (char*)malloc(100);
strcpy(dballoc,"Allocati");
strcpy(notenmem,"Impossibile allocare il database");
allocdb(0,&header_ToRtf);
ClearDB();
// Riempimento strutture allocate
// Analogici acquisiti 
if(!DoAA())
	return(0);
// Analogici calcolati standard 
if(!DoAS())
	return(0);
// Analogici calcolati non standard 
if(!DoAC())
	return(0);
// Analogici di diagnostica 
if(!DoAD())
	return(0);
// Analogici di uscita 
if(!DoAO())
	return(0);
// Digitali acquisiti 
if(!DoDA())
	return(0);
// Digitali calcolati standard 
if(!DoDS())
	return(0);
// Digitali calcolati non standard 
if(!DoDC())
	return(0);
// Digitali di diagnostica 
if(!DoDD())
	return(0);
// Digitali di uscita 
if(!DoDO())
	return(0);
// Organi
if(!DoOR())
	return(0);
// Stringhe
if(!DoST())
	return(0);
// Gestione contribuzione digitali
GestCALIN();
// scrittura database
//off = ldb_header;
//printf("AA off = %d\n",off);
if(header_ToRtf.dimaa)
{
   fwrite((char *)dbaav,sizeof(S_DBAAV),header_ToRtf.dimaa,fp);
   fwrite((char *)dbaaf,sizeof(S_DBAAF),header_ToRtf.dimaa,fp);
   fwrite((char *)dbaau,sizeof(S_DBAAU),header_ToRtf.dimaa,fp);
   fwrite((char *)dbaaal,sizeof(S_DBALL),header_ToRtf.dimaa,fp);
   fwrite((char *)dbaafa,sizeof(S_DBAAFA),header_ToRtf.dimaa,fp);
}
//off += sizeof(S_DBAAV)*header_ToRtf.dimaa +sizeof(S_DBAAF)*header_ToRtf.dimaa+sizeof(S_DBAAU)*header_ToRtf.dimaa+sizeof(S_DBALL)*header_ToRtf.dimaa+sizeof(S_DBAAFA)*header_ToRtf.dimaa;
//printf("AS off = %d\n",off);
if(header_ToRtf.dimas)
{
   fwrite((char *)dbasv,sizeof(S_DBASV),header_ToRtf.dimas,fp);
   fwrite((char *)dbasf,sizeof(S_DBASF),header_ToRtf.dimas,fp);
   fwrite((char *)dbasu,sizeof(S_DBASU),header_ToRtf.dimas,fp);
   fwrite((char *)dbasal,sizeof(S_DBALL),header_ToRtf.dimas,fp);
   fwrite((char *)dbasde,sizeof(DES),header_ToRtf.dimas,fp);
}
//off += sizeof(S_DBASV)*header_ToRtf.dimas+sizeof(S_DBASF)*header_ToRtf.dimas+sizeof(S_DBASU)*header_ToRtf.dimas+sizeof(S_DBALL)*header_ToRtf.dimas+sizeof(DES)*header_ToRtf.dimas;
//printf("AC off = %d\n",off);
if(header_ToRtf.dimac)
{
   fwrite((char *)dbacv,sizeof(S_DBACV),header_ToRtf.dimac,fp);
   fwrite((char *)dbacf,sizeof(S_DBACF),header_ToRtf.dimac,fp);
   fwrite((char *)dbacu,sizeof(S_DBACU),header_ToRtf.dimac,fp);
   fwrite((char *)dbacal,sizeof(S_DBALL),header_ToRtf.dimac,fp);
}
//off += sizeof(S_DBACV)*header_ToRtf.dimac+sizeof(S_DBACF)*header_ToRtf.dimac+sizeof(S_DBACU)*header_ToRtf.dimac+sizeof(S_DBALL)*header_ToRtf.dimac;
//printf("AD off = %d\n",off);
if(header_ToRtf.dimad)
{
   fwrite((char *)dbadv,sizeof(S_DBADV),header_ToRtf.dimad,fp);
   fwrite((char *)dbadf,sizeof(S_DBADF),header_ToRtf.dimad,fp);
   fwrite((char *)dbadu,sizeof(S_DBADU),header_ToRtf.dimad,fp);
   fwrite((char *)dbadal,sizeof(S_DBALL),header_ToRtf.dimad,fp);
}
//off += sizeof(S_DBADV)*header_ToRtf.dimad+sizeof(S_DBADF)*header_ToRtf.dimad+sizeof(S_DBADU)*header_ToRtf.dimad+sizeof(S_DBALL)*header_ToRtf.dimad;
//printf("AO off = %d\n",off);
if(header_ToRtf.dimao)
{
   fwrite((char *)dbaof,sizeof(S_DBAOF),header_ToRtf.dimao,fp);
   fwrite((char *)dbaou,sizeof(S_DBAOU),header_ToRtf.dimao,fp);
   fwrite((char *)dbaom,sizeof(S_DBAOM),header_ToRtf.dimao,fp);
}
//off += sizeof(S_DBAOF)*header_ToRtf.dimao+sizeof(S_DBAOU)*header_ToRtf.dimao+sizeof(S_DBAOM)*header_ToRtf.dimao;
//printf("DA off = %d\n",off);
if(header_ToRtf.dimda)
{
        fwrite((char *)dbda,sizeof(S_DBDA),header_ToRtf.dimda,fp);
        fwrite((char *)dbdatr,sizeof(S_DBDATR),header_ToRtf.dimda,fp);
   fwrite((char *)dbdau,sizeof(S_DBDAU),header_ToRtf.dimda,fp);
        fwrite((char *)dbdaco,sizeof(S_CALIN),header_ToRtf.dimda,fp);
}
//off += sizeof(S_DBDA)*header_ToRtf.dimda+sizeof(S_DBDATR)*header_ToRtf.dimda+sizeof(S_DBDAU)*header_ToRtf.dimda+sizeof(S_CALIN)*header_ToRtf.dimda;
//printf("DS off = %d\n",off);
if(header_ToRtf.dimds)
{
        fwrite((char *)dbds,sizeof(S_DBDS),header_ToRtf.dimds,fp);
        fwrite((char *)dbdstr,sizeof(S_DBDSTR),header_ToRtf.dimds,fp);
        fwrite((char *)dbdsu,sizeof(S_DBDSU),header_ToRtf.dimds,fp);
        fwrite((char *)dbdsco,sizeof(S_CALIN),header_ToRtf.dimds,fp);
   fwrite((char *)dbdsde,sizeof(S_DCALC),header_ToRtf.dimds,fp);
}
//off += sizeof(S_DBDS)*header_ToRtf.dimds+sizeof(S_DBDSTR)*header_ToRtf.dimds+sizeof(S_DBDSU)*header_ToRtf.dimds+sizeof(S_CALIN)*header_ToRtf.dimds+sizeof(S_DCALC)*header_ToRtf.dimds;
//printf("DC off = %d\n",off);
if(header_ToRtf.dimdc)
{
        fwrite((char *)dbdc,sizeof(S_DBDC),header_ToRtf.dimdc,fp);
        fwrite((char *)dbdctr,sizeof(S_DBDCTR),header_ToRtf.dimdc,fp);
        fwrite((char *)dbdcu,sizeof(S_DBDCU),header_ToRtf.dimdc,fp);
        fwrite((char *)dbdcco,sizeof(S_CALIN),header_ToRtf.dimdc,fp);
}
//off += sizeof(S_DBDC)*header_ToRtf.dimdc+sizeof(S_DBDCTR)*header_ToRtf.dimdc+sizeof(S_DBDCU)*header_ToRtf.dimdc+sizeof(S_CALIN)*header_ToRtf.dimdc;
//printf("DD off = %d\n",off);
if(header_ToRtf.dimdd)
{
        fwrite((char *)dbdd,sizeof(S_DBDD),header_ToRtf.dimdd,fp);
        fwrite((char *)dbddtr,sizeof(S_DBDDTR),header_ToRtf.dimdd,fp);
        fwrite((char *)dbddu,sizeof(S_DBDDU),header_ToRtf.dimdd,fp);
        fwrite((char *)dbddco,sizeof(S_CALIN),header_ToRtf.dimdd,fp);
}
if(header_ToRtf.dimdo)
{
        fwrite((char *)dbdo,sizeof(S_DBDO),header_ToRtf.dimdo,fp);
        fwrite((char *)dbdou,sizeof(S_DBDOU),header_ToRtf.dimdo,fp);
        fwrite((char *)dbdom,sizeof(S_DBDOM),header_ToRtf.dimdo,fp);
}
if(header_ToRtf.dimor)
{
        fwrite((char *)dbosc,sizeof(S_DBOSC),header_ToRtf.dimor,fp);
        fwrite((char *)dbosa,sizeof(S_DBOSA),header_ToRtf.dimor,fp);
        fwrite((char *)dbosp,sizeof(S_DBOSP),header_ToRtf.dimor,fp);
        fwrite((char *)dbto,sizeof(S_DBTO),header_ToRtf.dimor,fp);
        fwrite((char *)dbou,sizeof(S_DBOU),header_ToRtf.dimor,fp);
        fwrite((char *)dboft,sizeof(S_DBOFT),header_ToRtf.dimor,fp);
        fwrite((char *)dbode,sizeof(S_DESORG),header_ToRtf.dimor,fp);
}
if(header_ToRtf.dimst)
{
        fwrite((char *)dbsttr,sizeof(S_DBSTTR),header_ToRtf.dimst,fp);
        fwrite((char *)dbstu,sizeof(S_DBSTU),header_ToRtf.dimst,fp);
        fwrite((char *)dbstv,sizeof(S_DBSTV),(header_ToRtf.dimst*g0lunst),fp);
}
fclose(fp);

return(1);
}




static int GetTratDig(ID_TABLE *tabella,int i,int point,short *s)
{
VAL_RET valore;
//  Trattamento
if(GetVal(tabella,"Trattamento",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetTratDig Trattamento\n");
         return(0);
         }
s[point]=valore.int_val;
return(1);
}

static int GetZona(ID_TABLE *tabella,int i,int point,char *au)
{
VAL_RET valore;
//  Zonaimpianto
if(GetVal(tabella,"Zonaimpianto",i,&valore)!=1)
	{
       	fprintf(stderr,"CreateFdbdp: Errore GetVal Zonaimpianto\n");
        return(0);
        }
au[point]=(char)valore.int_val;
return(1);
}

static int SoglieUguali(char *LalBC,char *LalBS,char *LalAC,char *LalAS)
{
if(strcmp(LalBC,LalBS))
	return 0;
if(strcmp(LalBS,LalAC))
	return 0;
if(strcmp(LalAC,LalAS))
	return 0;
return 1;
}

static int GetAll(ID_TABLE *tabella,int i,int point,S_DBALL *al)
{
VAL_RET valore;
VAL_RET val_LalBC,val_LalBS,val_LalAC,val_LalAS;
int BandaMorta,Trattamento,Severita;

//  LalBC
if(GetVal(tabella,"LalBC",i,&val_LalBC)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll LalBC\n");
         return(0);
         }
//  LalBS
if(GetVal(tabella,"LalBS",i,&val_LalBS)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll LalBS\n");
         return(0);
         }
//  LalAC
if(GetVal(tabella,"LalAC",i,&val_LalAC)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll LalAC\n");
         return(0);
         }
//  LalAS
if(GetVal(tabella,"LalAS",i,&val_LalAS)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll LalAS\n");
         return(0);
         }
// Esegue controllo sui valori delle soglie
// se sono tutte uguali le pone NULL
if(SoglieUguali(val_LalBC.char_val,val_LalBS.char_val,
		val_LalAC.char_val,val_LalAS.char_val))
	{
	*val_LalBC.char_val='\0';
	*val_LalBS.char_val='\0';
	*val_LalAC.char_val='\0';
	*val_LalAS.char_val='\0';
	}
GestDBALL(val_LalBC.char_val,&al[point].bass_con);
GestDBALL(val_LalBS.char_val,&al[point].bass_sic);
GestDBALL(val_LalAC.char_val,&al[point].alto_con);
GestDBALL(val_LalAS.char_val,&al[point].alto_sic);

//  BandaMorta
if(GetVal(tabella,"BandaMorta",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll BandaMorta\n");
         return(0);
         }
BandaMorta=valore.int_val;
//  Trattamento
if(GetVal(tabella,"Trattamento",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll Trattamento\n");
         return(0);
         }
Trattamento=valore.int_val;
//  Severita
if(GetVal(tabella,"Severita",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetAll Severita\n");
         return(0);
         }
Severita=valore.int_val -1;
if(Severita<0)
	Severita = 0;
al[point].tr_bdm=Trattamento*4096+Severita*1024+BandaMorta;
return(1);
}

int DoAA()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,AA);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimaa;i++)
		dbaau[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbaau)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto AA\n");
        		return(0);
        		}
		//  Soglie di allarme
                if(GetAll(tabella,i,i,dbaaal)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore Soglie allarme AA\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",AA);
}

int DoAS()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;
int primo,ultimo,prog;

	tabella = OpenTablePath(path_txt,AS);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimas;i++)
		dbasu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbasu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto AS\n");
        		return(0);
        		}
		//  Soglie di allarme
                if(GetAll(tabella,i,i,dbasal)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore Soglie allarme AS\n");
                        return(0);
                        }
		//  Campi del tipo di calcolata
                if(GetCalcAna(tabella,i,dbasde)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore tipo calc AS\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",AS);
// sistema i link e i periodi
SistPeriodiLink(1,num_record);
SistPeriodiLink(5,num_record);
SistPeriodiLink(15,num_record);
SistPeriodiLink(30,num_record);
SistPeriodiLink(60,num_record);
/**
for(i=0;i<num_record;i++)
	printf("[%d] periodo [%d] link = [%d] tipo = [%d]\n",i,
		dbasde[i].a.periodo,
		dbasde[i].a.link,dbasde[i].a.tipoc);
**/
		
}

int DoAC()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,AC);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimac;i++)
		dbacu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbacu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto AC\n");
        		return(0);
        		}
		//  Soglie di allarme
                if(GetAll(tabella,i,i,dbacal)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore Soglie allarme AC\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",AC);
}

int DoAD()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int point;
int i;

	tabella = OpenTablePath(path_txt,AD);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimad;i++)
		dbadu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		// IndDB
		if(GetVal(tabella,"IndDB",i,&valore)!=1)
         		{
         		fprintf(stderr,"CreateFdbdp: Errore DoAD IndDB\n");
         		return(0);
         		}
		point=valore.int_val;
		
		//  Zonaimpianto
		if(GetZona(tabella,i,point,dbadu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto AD\n");
        		return(0);
        		}
		//  Soglie di allarme
                if(GetAll(tabella,i,point,dbadal)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore Soglie allarme AD\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",AD);
}

int DoAO()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,AO);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimao;i++)
		dbaou[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbaou)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto AO\n");
        		return(0);
        		}
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",AO);
}

int DoDA()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,DA);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimda;i++)
		dbdau[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		// Clear struttura S_CALIN
		ClearCALIN(&dbdaco[i]);
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbdau)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto DA\n");
        		return(0);
        		}
		//  Trattamenti digitali
		if(GetTratDig(tabella,i,i,dbda)!=1)
			{
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetTratDig DA\n");
                        return(0);
                        }
		//  Inibizioni
		if(GetInib(tabella,i,i,dbdaco,dbdatr)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetInib DA\n");
                        return(0);
                        }
		//  Inversione di polarita'
		if(GetInvPol(tabella,i,dbdatr)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetInvPol DA\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",DA);
}

int DoDS()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,DS);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimds;i++)
		dbdsu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		// Clear struttura S_CALIN
		ClearCALIN(&dbdsco[i]);
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbdsu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto DS\n");
        		return(0);
        		}
		//  Trattamenti digitali
		if(GetTratDig(tabella,i,i,dbds)!=1)
			{
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetTratDig DS\n");
                        return(0);
                        }
		//  Campi del tipo di calcolata
                if(GetCalcDig(tabella,i,dbdsde)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore tipo calc DS\n");
                        return(0);
                        }
		//  Inibizioni
		if(GetInib(tabella,i,i,dbdsco,dbdstr)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetInib DS\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",DS);
}

int DoDC()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,DC);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimdc;i++)
		dbdcu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		// Clear struttura S_CALIN
		ClearCALIN(&dbdcco[i]);
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbdcu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto DC\n");
        		return(0);
        		}
		//  Trattamenti digitali
		if(GetTratDig(tabella,i,i,dbdc)!=1)
			{
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetTratDig DC\n");
                        return(0);
                        }
		//  Inibizioni
		if(GetInib(tabella,i,i,dbdcco,dbdctr)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetInib DC\n");
                        return(0);
                        }
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",DC);
}

int DoDD()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;
int point;

	tabella = OpenTablePath(path_txt,DD);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimdd;i++)
		dbddu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		// IndDB
		if(GetVal(tabella,"IndDB",i,&valore)!=1)
         		{
         		fprintf(stderr,"CreateFdbdp: Errore DoDD IndDB\n");
         		return(0);
         		}
		point=valore.int_val;
		// Clear struttura S_CALIN
		ClearCALIN(&dbddco[point]);
		//  Zonaimpianto
		if(GetZona(tabella,i,point,dbddu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto DD\n");
        		return(0);
        		}
		//  Trattamenti digitali
		if(GetTratDig(tabella,i,point,dbdd)!=1)
			{
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetTratDig DD\n");
                        return(0);
                        }
		//  Inibizioni
		if(GetInib(tabella,i,point,dbddco,dbddtr)!=1)
                        {
                        fprintf(stderr,
                                "CreateFdbdp: Errore GetInib DD\n");
                        return(0);
                        }
//printf("DD [%d] dbdd = %x\n",i,dbdd[i]);
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",DD);
}

int DoDO()
{
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;

	tabella = OpenTablePath(path_txt,DO);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimdo;i++)
		dbdou[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbdou)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto DO\n");
        		return(0);
        		}
        	}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",DO);
}

static int GetCalcAna(ID_TABLE *tabella, int i, DES * des)
{
VAL_RET valore;

//printf("GetCalcAna\n");
// Periodo
if(GetVal(tabella,"Periodo",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetCalcAna Periodo\n");
         return(0);
         }
des[i].a.periodo=(unsigned char)valore.int_val;

// TipoCalc
if(GetVal(tabella,"TipoCalc",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetCalcAna TipoCalc\n");
         return(0);
         }
des[i].a.tipoc=(unsigned char)valore.int_val;
//printf("GetCalcAna: tipo = %d Periodo = %d\n",des[i].a.tipoc,des[i].a.periodo);
switch(des[i].a.tipoc){
	case 1:			// media
	case 2:			// massimo
	case 3:			// minimo
		// Freq
		if(GetVal(tabella,"Freq",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Freq\n");
         		return(0);
         		}
		des[i].a.freq=(short)valore.int_val;
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].a.indice))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		break;
	case 4:			// integrale
	case 5:			// accumulo
		// Freq
		if(GetVal(tabella,"Freq",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Freq\n");
         		return(0);
         		}
		des[i].i.freq=(short)valore.int_val;
		if(des[i].i.tipoc == 4)  // integrale
			{
			// Codice
			if(GetVal(tabella,"Codice",i,&valore)!=1)
         			{
         			fprintf(stderr,
			   	"CreateFdbdp: Errore GetCalcAna Codice\n");
         			return(0);
         			}
			des[i].i.time=(short)valore.int_val;
			}
		else
			des[i].i.time=(short)0;
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].i.indice))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		break;
	case 6: 	// portata AGA
	case 7:		// portata UNI
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].p.Dp))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].p.press))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib3
		if(GetVal(tabella,"Contrib3",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib3\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].p.temper))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib4
		if(GetVal(tabella,"Contrib4",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib4\n");
         		return(0);
         		}
		des[i].p.cost1=atof(valore.char_val);
		// Contrib5
		if(GetVal(tabella,"Contrib5",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib5\n");
         		return(0);
         		}
		des[i].p.cost2=atof(valore.char_val);
		if(CtrPort(des[i].p.tipoc,des[i].p.cost1,des[i].p.cost2,
				&des[i].p.cost1,&des[i].p.cost2)!=0)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna CtrPort\n");
         		return(0);
         		}
		break;
	case 8:
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].f.misura))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		des[i].f.cost1=atoi(valore.char_val);
		break;
	case 9:
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].m.misura[0]))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].m.misura[1]))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib3
		if(GetVal(tabella,"Contrib3",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib3\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].m.misura[2]))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib4
		if(GetVal(tabella,"Contrib4",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib4\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].m.misura[3]))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib5
		if(GetVal(tabella,"Contrib5",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib5\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].m.misura[4]))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib6
		if(GetVal(tabella,"Contrib6",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib6\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].m.misura[5]))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		break;
	case 10:
		// operazioni
		// Codice
		if(GetVal(tabella,"Codice",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Codice\n");
         		return(0);
         		}
		des[i].o.oper=valore.int_val;
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].o.misura))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].o.c_m.misura))==1)
			des[i].o.c_m.misura.ext = 
				des[i].o.c_m.misura.ext | 0xFF00;
		else
			des[i].o.c_m.cost=atof(valore.char_val);
		break;
		break;
	case 11:   // sommatoria
         	{
		PUNTATORE punt;

		des[i].s.ind_misure[0]= -1;
		des[i].s.tip_misure[0]= -1;
		des[i].s.ind_misure[1]= -1;
		des[i].s.tip_misure[1]= -1;
		des[i].s.ind_misure[2]= -1;
		des[i].s.tip_misure[2]= -1;
		des[i].s.ind_misure[3]= -1;
		des[i].s.tip_misure[3]= -1;
		des[i].s.ind_misure[4]= -1;
		des[i].s.tip_misure[4]= -1;
		des[i].s.ind_misure[5]= -1;
		des[i].s.tip_misure[5]= -1;
		des[i].s.ind_misure[6]= -1;
		des[i].s.tip_misure[6]= -1;
		des[i].s.ind_misure[7]= -1;
		des[i].s.tip_misure[7]= -1;

		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[0]=punt.punt;
			des[i].s.tip_misure[0]=punt.ext;
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[1]=punt.punt;
			des[i].s.tip_misure[1]=punt.ext;
         		}
		// Contrib3
		if(GetVal(tabella,"Contrib3",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib3\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[2]=punt.punt;
			des[i].s.tip_misure[2]=punt.ext;
         		}
		// Contrib4
		if(GetVal(tabella,"Contrib4",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib4\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[3]=punt.punt;
			des[i].s.tip_misure[3]=punt.ext;
         		}
		// Contrib5
		if(GetVal(tabella,"Contrib5",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib5\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[4]=punt.punt;
			des[i].s.tip_misure[4]=punt.ext;
         		}
		// Contrib6
		if(GetVal(tabella,"Contrib6",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[5]=punt.punt;
			des[i].s.tip_misure[5]=punt.ext;
         		}
		// Contrib7
		if(GetVal(tabella,"Contrib7",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib7\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[6]=punt.punt;
			des[i].s.tip_misure[6]=punt.ext;
         		}
		// Contrib8
		if(GetVal(tabella,"Contrib8",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib8\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&punt)==1)
         		{
			des[i].s.ind_misure[7]=punt.punt;
			des[i].s.tip_misure[7]=punt.ext;
         		}
         	}
		break;
	case 12:   //scarto Q
		// Freq
		if(GetVal(tabella,"Freq",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Freq\n");
         		return(0);
         		}
		des[i].q.freq=(short)valore.int_val;
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].q.misura))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		break;
	case 13:  // stato organi
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].r.organo))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		des[i].r.stato=GetStatoOrgano(valore.char_val);
		
		break;
	case 14:  // ore misura
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].h.misura))!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna SetPunt\n");
         		return(0);
         		}
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		if(SetPunt(valore.char_val,&(des[i].h.v_s.soglia))==1)
			des[i].h.v_s.soglia.ext = 
				des[i].h.v_s.soglia.ext | 0xFF00;
		else
			des[i].h.v_s.val=atof(valore.char_val);
		break;
#ifdef GERARC
	case 15:  // gerarchie allarmi pendenti
	case 16:  // gerarchie allarmi archiviati
		// Contrib1
		if(GetVal(tabella,"Contrib1",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib1\n");
         		return(0);
         		}
		des[i].g.gerac.chLivello[0]=atoi(valore.char_val);
		// Contrib2
		if(GetVal(tabella,"Contrib2",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib2\n");
         		return(0);
         		}
		des[i].g.gerac.chLivello[1]=atoi(valore.char_val);
		// Contrib3
		if(GetVal(tabella,"Contrib3",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib3\n");
         		return(0);
         		}
		des[i].g.gerac.chLivello[2]=atoi(valore.char_val);
		// Contrib4
		if(GetVal(tabella,"Contrib4",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib4\n");
         		return(0);
         		}
		des[i].g.gerac.chLivello[3]=atoi(valore.char_val);
		// Contrib5
		if(GetVal(tabella,"Contrib5",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib5\n");
         		return(0);
         		}
		des[i].g.gerac.chLivello[4]=atoi(valore.char_val);
		// Contrib6
		if(GetVal(tabella,"Contrib6",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib6\n");
         		return(0);
         		}
		des[i].g.gerac.chLivello[5]=atoi(valore.char_val);
		// Contrib7
		if(GetVal(tabella,"Contrib7",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib7\n");
         		return(0);
         		}
		des[i].g.sZona=atoi(valore.char_val);
		// Contrib8
		if(GetVal(tabella,"Contrib8",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore GetCalcAna Contrib8\n");
         		return(0);
         		}
		des[i].g.sDbAll=atoi(valore.char_val);
		break;
#endif
	}

return(1);
}

static int GetCalcDig(ID_TABLE *tabella, int i, S_DCALC * des)
{
PUNTATORE punt;
VAL_RET valore;

des[i].punt[0]= -1;
des[i].ext[0]= -1;
des[i].punt[1]= -1;
des[i].ext[1]= -1;
des[i].punt[2]= -1;
des[i].ext[2]= -1;
des[i].punt[3]= -1;
des[i].ext[3]= -1;

// TipoCalc
if(GetVal(tabella,"TipoCalc",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetCalcAna TipoCalc\n");
         return(0);
         }
des[i].tipc=(unsigned char)valore.int_val;
// SiglaDig1
if(GetVal(tabella,"SiglaDig1",i,&valore)!=1)
	{
       	fprintf(stderr,
	   "CreateFdbdp: Errore GetCalcDig SiglaDig1\n");
       	return(0);
       	}
if(SetPunt(valore.char_val,&punt)==1)
	{
	des[i].punt[0]=punt.punt;
	des[i].ext[0]=punt.ext;
       	}
// SiglaDig2
if(GetVal(tabella,"SiglaDig2",i,&valore)!=1)
	{
       	fprintf(stderr,
	   "CreateFdbdp: Errore GetCalcDig SiglaDig2\n");
       	return(0);
       	}
if(SetPunt(valore.char_val,&punt)==1)
	{
	des[i].punt[1]=punt.punt;
	des[i].ext[1]=punt.ext;
       	}
// SiglaDig3
if(GetVal(tabella,"SiglaDig3",i,&valore)!=1)
	{
       	fprintf(stderr,
	   "CreateFdbdp: Errore GetCalcDig SiglaDig3\n");
       	return(0);
       	}
if(SetPunt(valore.char_val,&punt)==1)
	{
	des[i].punt[2]=punt.punt;
	des[i].ext[2]=punt.ext;
       	}
// SiglaDig4
if(GetVal(tabella,"SiglaDig4",i,&valore)!=1)
	{
       	fprintf(stderr,
	   "CreateFdbdp: Errore GetCalcDig SiglaDig4\n");
       	return(0);
       	}
if(SetPunt(valore.char_val,&punt)==1)
	{
	des[i].punt[3]=punt.punt;
	des[i].ext[3]=punt.ext;
       	}

return(1);
}

int SetPunt(char *var,PUNTATORE *punt)
{
short point,ext,posiz;
long blocco;
char nome_var[100];
FILE *fp;
int ret;

if(var==NULL)
	return(0);
if(!strlen(var))
	return(0);

memset(nome_var,0,100);
strcpy(nome_var,var);

fp=fopen("fnomi.rtf","r");
ret = ricerca((short *)nome_var,&point,&ext,&blocco,&posiz,fp);
fclose(fp);

//printf("SetPunt [%s] %d %d %d ret = %d\n",nome_var,point,ext,posiz,ret);
if(ret == 1)
	return(0);

punt->ext = ext;
punt->punt = point;

return(1);
}

int SistPeriodiLink(int per,int num_record)
{
int primo = -1;
int ultimo = -1;
int prog=0;
int tot,i,j;

tot= 0;
for(i=0;i<num_record;i++)
  if(dbasde[i].a.periodo==per)
	tot++;
if(!tot)
	return(1);


// setto il campo link
for(i=0;i<num_record;i++)
  if(dbasde[i].a.periodo==per)
	{
	for(j=i+1;j<num_record;j++)
		if(dbasde[j].a.periodo==per)
			break;
	if(j>=num_record)
		dbasde[i].a.link =-1;
	else
		dbasde[i].a.link = j;
	}

// setto il primo periodo
for(i=0;i<num_record;i++)
	if(dbasde[i].a.periodo==per)
		{
		dbasde[i].a.periodo = dbasde[i].a.periodo | 0x80;
		break;
		}
}

static int ClearDB()
{
if(header_ToRtf.dimaa)
{
   memset((char *)dbaav,0,sizeof(S_DBAAV)*header_ToRtf.dimaa);
   memset((char *)dbaaf,0,sizeof(S_DBAAF)*header_ToRtf.dimaa);
   memset((char *)dbaau,0,sizeof(S_DBAAU)*header_ToRtf.dimaa);
   memset((char *)dbaaal,0,sizeof(S_DBALL)*header_ToRtf.dimaa);
   memset((char *)dbaafa,0,sizeof(S_DBAAFA)*header_ToRtf.dimaa);
}
if(header_ToRtf.dimas)
{
   memset((char *)dbasv,0,sizeof(S_DBASV)*header_ToRtf.dimas);
   memset((char *)dbasf,0,sizeof(S_DBASF)*header_ToRtf.dimas);
   memset((char *)dbasu,0,sizeof(S_DBASU)*header_ToRtf.dimas);
   memset((char *)dbasal,0,sizeof(S_DBALL)*header_ToRtf.dimas);
   memset((char *)dbasde,0,sizeof(DES)*header_ToRtf.dimas);
}
if(header_ToRtf.dimac)
{
   memset((char *)dbacv,0,sizeof(S_DBACV)*header_ToRtf.dimac);
   memset((char *)dbacf,0,sizeof(S_DBACF)*header_ToRtf.dimac);
   memset((char *)dbacu,0,sizeof(S_DBACU)*header_ToRtf.dimac);
   memset((char *)dbacal,0,sizeof(S_DBALL)*header_ToRtf.dimac);
}
if(header_ToRtf.dimad)
{
   memset((char *)dbadv,0,sizeof(S_DBADV)*header_ToRtf.dimad);
   memset((char *)dbadf,0,sizeof(S_DBADF)*header_ToRtf.dimad);
   memset((char *)dbadu,0,sizeof(S_DBADU)*header_ToRtf.dimad);
   memset((char *)dbadal,0,sizeof(S_DBALL)*header_ToRtf.dimad);
}
if(header_ToRtf.dimao)
{
   memset((char *)dbaof,0,sizeof(S_DBAOF)*header_ToRtf.dimao);
   memset((char *)dbaou,0,sizeof(S_DBAOU)*header_ToRtf.dimao);
   memset((char *)dbaom,0,sizeof(S_DBAOM)*header_ToRtf.dimao);
}
if(header_ToRtf.dimda)
{
        memset((char *)dbda,0,sizeof(S_DBDA)*header_ToRtf.dimda);
        memset((char *)dbdatr,0,sizeof(S_DBDATR)*header_ToRtf.dimda);
   memset((char *)dbdau,0,sizeof(S_DBDAU)*header_ToRtf.dimda);
        memset((char *)dbdaco,0,sizeof(S_CALIN)*header_ToRtf.dimda);
}
if(header_ToRtf.dimds)
{
        memset((char *)dbds,0,sizeof(S_DBDS)*header_ToRtf.dimds);
        memset((char *)dbdstr,0,sizeof(S_DBDSTR)*header_ToRtf.dimds);
        memset((char *)dbdsu,0,sizeof(S_DBDSU)*header_ToRtf.dimds);
        memset((char *)dbdsco,0,sizeof(S_CALIN)*header_ToRtf.dimds);
   memset((char *)dbdsde,0,sizeof(S_DCALC)*header_ToRtf.dimds);
}
if(header_ToRtf.dimdc)
{
        memset((char *)dbdc,0,sizeof(S_DBDC)*header_ToRtf.dimdc);
        memset((char *)dbdctr,0,sizeof(S_DBDCTR)*header_ToRtf.dimdc);
        memset((char *)dbdcu,0,sizeof(S_DBDCU)*header_ToRtf.dimdc);
        memset((char *)dbdcco,0,sizeof(S_CALIN)*header_ToRtf.dimdc);
}
if(header_ToRtf.dimdd)
{
        memset((char *)dbdd,0,sizeof(S_DBDD)*header_ToRtf.dimdd);
        memset((char *)dbddtr,0,sizeof(S_DBDDTR)*header_ToRtf.dimdd);
        memset((char *)dbddu,0,sizeof(S_DBDDU)*header_ToRtf.dimdd);
        memset((char *)dbddco,0,sizeof(S_CALIN)*header_ToRtf.dimdd);
}
if(header_ToRtf.dimdo)
{
        memset((char *)dbdo,0,sizeof(S_DBDO)*header_ToRtf.dimdo);
        memset((char *)dbdou,0,sizeof(S_DBDOU)*header_ToRtf.dimdo);
        memset((char *)dbdom,0,sizeof(S_DBDOM)*header_ToRtf.dimdo);
}
if(header_ToRtf.dimor)
{
        memset((char *)dbosc,0,sizeof(S_DBOSC)*header_ToRtf.dimor);
        memset((char *)dbosa,0,sizeof(S_DBOSA)*header_ToRtf.dimor);
        memset((char *)dbosp,0,sizeof(S_DBOSP)*header_ToRtf.dimor);
        memset((char *)dbto,0,sizeof(S_DBTO)*header_ToRtf.dimor);
        memset((char *)dbou,0,sizeof(S_DBOU)*header_ToRtf.dimor);
        memset((char *)dboft,0,sizeof(S_DBOFT)*header_ToRtf.dimor);
        memset((char *)dbode,0,sizeof(S_DESORG)*header_ToRtf.dimor);
}
if(header_ToRtf.dimst)
{
        memset((char *)dbsttr,0,sizeof(S_DBSTTR)*header_ToRtf.dimst);
        memset((char *)dbstu,0,sizeof(S_DBSTU)*header_ToRtf.dimst);
        memset((char *)dbstv,0,sizeof(S_DBSTV)*(header_ToRtf.dimst*g0lunst));
}
}

static int GestDBALL(char *riga,union valin *al)
{
PUNTATORE punt;
if(riga == NULL)
	{
	al->cval[0]= -2;
	return;
	}
if(strlen(riga)==0)
	{
	al->cval[0]= -2;
	return;
	}
if(SetPunt(riga,&punt)==1)
	{
	// soglia variabile
	al->cval[0]= -1;
	al->cval[1]= punt.ext;
	al->sval[1]= punt.punt;
	return;
	}
// soglia fissa
al->fval=atof(riga);
}

static int GetInib(ID_TABLE *tabella,int i,int point,S_CALIN *inib,short *trat)
{
VAL_RET valore;
PUNTATORE punt;

inib[point].inib[0]= -1;
inib[point].tipo_inib[0]= -1;
inib[point].inib[1]= -1;
inib[point].tipo_inib[1]= -1;
inib[point].tin_an = 0;

//  TagPP1
if(GetVal(tabella,"TagPP1",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetInib TagPP1\n");
         return(0);
         }
if(SetPunt(valore.char_val,&punt)==1)
	{
	inib[point].inib[0]=punt.punt;
	inib[point].tipo_inib[0]=punt.ext;
	bitset(&trat[point],g2di_io,1);
	}
//  TagPP2
if(GetVal(tabella,"TagPP2",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetInib TagPP2\n");
         return(0);
         }
if(SetPunt(valore.char_val,&punt)==1)
	{
	inib[point].inib[1]=punt.punt;
	inib[point].tipo_inib[1]=punt.ext;
	bitset(&trat[point],g2di_io,1);
	}
//  TInib
if(GetVal(tabella,"TInib",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetInib TInib\n");
         return(0);
         }
inib[point].tin_an = valore.int_val;
return(1);
}

int DoOR()
{
PUNTATORE punt;
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;
int sev;
int contrib;

	tabella = OpenTablePath(path_txt,OR);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimor;i++)
		dbou[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbou)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto OR\n");
			}
		//  Timeout
		if(GetVal(tabella,"Timeout",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR Timeout\n");
         		return(0);
         		}
		dbode[i].time_out=valore.int_val;
		//  Tipo
		if(GetVal(tabella,"Tipo",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR Tipo\n");
         		return(0);
         		}
		dbode[i].tipo=GetTipoOrgano(valore.char_val);
		contrib=GetContribOrgano(valore.char_val);
		dbode[i].punt[0]= 0;
		dbode[i].ext[0]= -1;
		dbode[i].punt[1]= 0;
		dbode[i].ext[1]= -1;
		dbode[i].punt[2]= 0;
		dbode[i].ext[2]= -1;
		dbode[i].punt[3]= 0;
		dbode[i].ext[3]= -1;
		dbode[i].punt[4]= 0;
		dbode[i].ext[4]= -1;
		dbode[i].pinib[0].tipin=0;
		dbode[i].pinib[0].punt=0;
		dbode[i].pinib[0].ext= -1;
		dbode[i].pinib[1].tipin=0;
		dbode[i].pinib[1].punt=0;
		dbode[i].pinib[1].ext= -1;
		//  SCont1
		if(GetVal(tabella,"SCont1",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR SCont1\n");
         		return(0);
         		}
		if((SetPunt(valore.char_val,&punt)==1)&&(contrib>0))
			{
			dbode[i].punt[0]=punt.punt;
			dbode[i].ext[0]=punt.ext;
			}
		//  SCont2
		if(GetVal(tabella,"SCont2",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR SCont2\n");
         		return(0);
         		}
		if((SetPunt(valore.char_val,&punt)==1)&&(contrib>1))
			{
			dbode[i].punt[1]=punt.punt;
			dbode[i].ext[1]=punt.ext;
			}
		//  SCont3
		if(GetVal(tabella,"SCont3",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR SCont3\n");
         		return(0);
         		}
		if((SetPunt(valore.char_val,&punt)==1)&&(contrib>2))
			{
			dbode[i].punt[2]=punt.punt;
			dbode[i].ext[2]=punt.ext;
			}
		//  SCont4
		if(GetVal(tabella,"SCont4",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR SCont4\n");
         		return(0);
         		}
		if((SetPunt(valore.char_val,&punt)==1)&&(contrib>3))
			{
			dbode[i].punt[3]=punt.punt;
			dbode[i].ext[3]=punt.ext;
			}
		//  SCont5
		if(GetVal(tabella,"SCont5",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR SCont5\n");
         		return(0);
         		}
		if((SetPunt(valore.char_val,&punt)==1)&&(contrib>4))
			{
			dbode[i].punt[4]=punt.punt;
			dbode[i].ext[4]=punt.ext;
			}
		// STProt
		if(GetVal(tabella,"STProt",i,&valore)!=1)
         		{
         		fprintf(stderr,
			   "CreateFdbdp: Errore DoOR STProt\n");
         		return(0);
         		}
		dbode[i].stprot=GetStatoOrgano(valore.char_val);
		//  Trattamento
		if(GetVal(tabella,"Trattamento",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR Trattamento\n");
         		return(0);
         		}
		dbode[i].trat=valore.int_val;
		// i tratamenti seguenti non sono ammessi per gli organi
		if((dbode[i].trat == 2)||
			(dbode[i].trat == 3) || 
			(dbode[i].trat == 5) ||
			(dbode[i].trat == 8))
				dbode[i].trat = 4;
		//  Severita
		if(GetVal(tabella,"Severita",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoOR Trattamento\n");
         		return(0);
         		}
		sev=valore.int_val;
		if(sev>0)
			sev -= 1;
		dbode[i].trat += sev*16;
		}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",OR);
}

int DoST()
{
PUNTATORE punt;
ID_TABLE *tabella;
int num_record;
VAL_RET valore;
int i;
int sev;

	tabella = OpenTablePath(path_txt,ST);
	if(tabella == NULL)
        	{
        	fprintf(stderr,"CreateFdbdp: apertura tabella\n");
        	return(0);
        	}
	// setta a -1 le zone di impianto
	for(i=0;i<header_ToRtf.dimst;i++)
		dbstu[i]=-1;
	num_record = NumRecord(tabella);
	for(i=0;i<num_record;i++)
        	{
		//  Zonaimpianto
		if(GetZona(tabella,i,i,dbstu)!=1)
        		{
        		fprintf(stderr,
			    	"CreateFdbdp: Errore Zonaimpianto ST\n");
			}
		//  Trattamento
		if(GetVal(tabella,"Trattamento",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoST Trattamento\n");
         		return(0);
         		}
		dbsttr[i]=valore.int_val +1;
		//  Severita
/*
		if(GetVal(tabella,"Severita",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoST Trattamento\n");
         		return(0);
         		}
		sev=valore.int_val;
		if(sev>0)
			sev -= 1;
		dbsttr[i] += sev*256;
*/
		//  Valore
		if(GetVal(tabella,"Valore",i,&valore)!=1)
         		{
         		fprintf(stderr,
				"CreateFdbdp: Errore DoST Trattamento\n");
         		return(0);
         		}
		strncpy(&dbstv[i],valore.char_val,g0lunst-1);
		}
	if(!CloseTable(tabella))
        	printf("Errore chiusura tabella %s\n",ST);
}


ClearCALIN(S_CALIN *calin)
{
calin->tipo_cont[0] = -1;
calin->cont[0] = 0;
calin->tipo_cont[1] = -1;
calin->cont[1] = 0;
calin->tipo_cont[2] = -1;
calin->cont[2] = 0;
calin->tipo_cont[3] = -1;
calin->cont[3] = 0;
calin->tin_an = 0;
calin->tipo_inib[0] = -1;
calin->inib[0] = -1;
calin->tipo_inib[1] = -1;
calin->inib[1] = -1;
}

GestCALIN()
{
int i,j,k;
S_CALIN *calin;
short *trat;

for(i=0;i<header_ToRtf.dimds;i++)
   if(dbdsu[i]!=-1)
      for(j=0;j<ds_cont;j++)
	{
	calin = NULL;
	trat = NULL;
	switch(dbdsde[i].ext[j])
		{
		case g1tipda:
			calin = &dbdaco[dbdsde[i].punt[j]];
			trat = &dbdatr[dbdsde[i].punt[j]];
			break;
		case g1tipds:
			calin = &dbdsco[dbdsde[i].punt[j]];
			trat = &dbdstr[dbdsde[i].punt[j]];
			break;
		case g1tipdc:
			calin = &dbdcco[dbdsde[i].punt[j]];
			trat = &dbdctr[dbdsde[i].punt[j]];
			break;
		case g1tipdd:
			calin = &dbddco[dbdsde[i].punt[j]];
			trat = &dbddtr[dbdsde[i].punt[j]];
			break;
		}
	if(calin==NULL) 
		continue;
	for(k=0;k<di_cont;k++)
		if(calin->tipo_cont[k] == -1)
			break;
	if(k == di_cont) 
		{
		printf("superato max di_cont(%d)\n",di_cont);
		continue;
		}
	calin->tipo_cont[k]=g1tipds;
	calin->cont[k]=i;
	bitset(trat,g2di_ic,1);
	}

/*
	contribuzione organi
*/
for(i=0;i<header_ToRtf.dimor;i++)
   if(dbou[i]!=-1)
      for(j=0;j<or_cont;j++)
	{
	calin = NULL;
	trat = NULL;
	switch(dbode[i].ext[j])
		{
		case g1tipda:
			calin = &dbdaco[dbode[i].punt[j]];
			trat = &dbdatr[dbode[i].punt[j]];
			break;
		case g1tipds:
			calin = &dbdsco[dbode[i].punt[j]];
			trat = &dbdstr[dbode[i].punt[j]];
			break;
		case g1tipdc:
			calin = &dbdcco[dbode[i].punt[j]];
			trat = &dbdctr[dbode[i].punt[j]];
			break;
		case g1tipdd:
			calin = &dbddco[dbode[i].punt[j]];
			trat = &dbddtr[dbode[i].punt[j]];
			break;
		}
	if(calin==NULL) 
		continue;
	for(k=0;k<di_cont;k++)
		if(calin->tipo_cont[k] == -1)
			break;
	if(k == di_cont) 
		{
		printf("superato max di_cont(%d) (organo=%d/%d)\n",
				di_cont,i,j);
		continue;
		}
	calin->tipo_cont[k]=g1tipor;
	calin->cont[k]=i;
	bitset(trat,g2di_ic,1);
	}
}

static int GetInvPol(ID_TABLE *tabella,int i,short *trat)
{
VAL_RET valore;

//  Contatto
if(GetVal(tabella,"Contatto",i,&valore)!=1)
         {
         fprintf(stderr,"CreateFdbdp: Errore GetInvPol Contatto\n");
         return(0);
         }
bitset(&trat[i],g2di_ip,(short)valore.int_val);

return(1);
}
