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
/*
	allocdb.c	la funzione alloca o rilascia la memoria necessaria
					al data base

					la struttura DB_HEADER  contiene
					il dimensionamento del DB che si vuole allocare	o
					rilasciare
				   flag=0 alloco memoria
					flag=1 rilascio
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "dconf.inc"
#include "g0strdb.inc" 
#include "g2ptrdb.inc"

extern char*   dballoc,
               notenmem;

allocdb(flag,db)
short flag;
DB_HEADER *db;
{
unsigned prova;
long size;
#define call_mall(STR,dim)   (STR*)malloc(sizeof(STR)*dim)
/*
	lunghezza record utilizzato per allocare area Huge con 
	dimensioni > 128K allineata al segmento
*/
#define RECHALL 32  
#define call_malh(STRU,dim)   (STRU*)_halloc((long)dim,RECHALL)

if(db->dimaa)
{
		if(flag)
		{
			free((void*)dbaav);
			free((void*)dbaaf);	
			free((void*)dbaau);	
			free((void*)dbaaal);	
			free((void*)dbaafa);	
#ifdef GERARC
			free((void*)dbaag);	
#endif
		}
		else
		{
        dbaav=call_mall(S_DBAAV,db->dimaa);        
        dbaaf=call_mall(S_DBAAF,db->dimaa);        
        dbaau=call_mall(S_DBAAU,db->dimaa);        
        dbaaal=call_mall(S_DBALL,db->dimaa);
		  dbaafa=call_mall(S_DBAAFA,db->dimaa); 
#ifdef GERARC
		  dbaag=call_mall(S_DBGERA,db->dimaa); 
#endif
		  if(dbaav==NULL || dbaaf==NULL || dbaau==NULL || dbaaal==NULL
#ifdef GERARC
		     || dbaag==NULL 
#endif
			  				  || dbaafa==NULL ) 
            { printf("\nAA"); goto ERROR;}
         else 
            printf("\n %d AA %s, %d bytes!",db->dimaa,dballoc,db->dimaa*(sizeof(S_DBAAV)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBAAF)+sizeof(S_DBAAU)+sizeof(S_DBALL)+sizeof(S_DBAAFA))); 
         }
}
if(db->dimas)
{
		if(flag)
		{
			free((void *)dbasv);
			free((void*)dbasf);	
			free((void*)dbasu);	
			free((void*)dbasal);	
			free((void*)dbasde);	
#ifdef GERARC
			free((void*)dbasg);	
#endif
		}
		else
		{
        dbasv=call_mall(S_DBASV,db->dimas);        
        dbasf=call_mall(S_DBASF,db->dimas);        
        dbasu=call_mall(S_DBASU,db->dimas);        
        dbasal=call_mall(S_DBALL,db->dimas);
        dbasde=call_mall(DES,db->dimas);
#ifdef GERARC
        dbasg=call_mall(S_DBGERA,db->dimas);
#endif
		  if(dbasv==NULL || dbasf==NULL || dbasu==NULL || dbasal==NULL
#ifdef GERARC
                     
                     || dbasg==NULL 
#endif
			  || dbasde==NULL) 
               { printf("\nAS"); goto ERROR;}
        else 
            printf("\n %d AS %s, %d bytes!",db->dimas,dballoc,(db->dimas)*(sizeof(S_DBASV)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBASF)+sizeof(S_DBASU)+sizeof(S_DBALL)+sizeof(DES))); 
	   }
}
if(db->dimac)
{
		if(flag)
		{
			free((void *)dbacv);
			free((void*)dbacf);	
			free((void*)dbacu);	
			free((void*)dbacal);	
#ifdef GERARC
			free((void*)dbacg);	
#endif
		}
		else
		{
        dbacv=call_mall(S_DBACV,db->dimac);        
        dbacf=call_mall(S_DBACF,db->dimac);        
        dbacu=call_mall(S_DBACU,db->dimac);        
        dbacal=call_mall(S_DBALL,db->dimac);
#ifdef GERARC
        dbacg=call_mall(S_DBGERA,db->dimac);
#endif
		  if(dbacv==NULL || dbacf==NULL || dbacu==NULL || dbacal==NULL
#ifdef GERARC
                     || dbacg==NULL 
#endif
                    )
               { printf("\nAC"); goto ERROR;}
        else 
            printf("\n %d AC %s, %d bytes!",db->dimac,dballoc,(db->dimac)*(sizeof(S_DBACV)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBACF)+sizeof(S_DBACU)+sizeof(S_DBALL))); 
	   }
}
if(db->dimad)
{
		if(flag)
		{
			free((void *)dbadv);
			free((void*)dbadf);	
			free((void*)dbadu);	
			free((void*)dbadal);	
#ifdef GERARC
			free((void*)dbadg);	
#endif
		}
		else
		{
        dbadv=call_mall(S_DBADV,db->dimad);        
        dbadf=call_mall(S_DBADF,db->dimad);        
        dbadu=call_mall(S_DBADU,db->dimad);        
        dbadal=call_mall(S_DBALL,db->dimad);
#ifdef GERARC
        dbadg=call_mall(S_DBGERA,db->dimad);
#endif
		  if(dbadv==NULL || dbadf==NULL || dbadu==NULL || dbadal==NULL
#ifdef GERARC
                     || dbadg==NULL 
#endif
                    )
               { printf("\nAD"); goto ERROR;}
        else 
            printf("\n %d AD %s, %d bytes!",db->dimad,dballoc,(db->dimad)*(sizeof(S_DBADV)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBADF)+sizeof(S_DBADU)+sizeof(S_DBALL))); 
	   }
}
if(db->dimao)
{
		if(flag)
		{
			free((void*)dbaof);	
			free((void*)dbaou);	
			free((void*)dbaom);	
#ifdef GERARC
			free((void*)dbaog);	
#endif
		}
		else
		{
        dbaof=call_mall(S_DBAOF,db->dimao);        
        dbaou=call_mall(S_DBAOU,db->dimao);        
        dbaom=call_mall(S_DBAOM,db->dimao);
#ifdef GERARC
        dbaog=call_mall(S_DBGERA,db->dimao);
#endif
		  if(dbaof==NULL || dbaou==NULL || dbaom==NULL
#ifdef GERARC
                     || dbaog==NULL 
#endif
                    )
               { printf("\nAO"); goto ERROR;}
        else 
            printf("\n %d AO %s, %d bytes!",db->dimao,dballoc,(db->dimao)*(sizeof(S_DBAOF)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBAOU)+sizeof(S_DBAOM))); 
	   }
}
if(db->dimda)
{
		if(flag)
		{
			free((void *)dbda);
			free((void*)dbdatr);	
			free((void*)dbdau);	
         free((void*)dbdaco);	
#ifdef GERARC
			free((void*)dbdag);	
#endif
//MAX			hfree((void*)dbdaco);	
		}
		else
		{
			dbda=call_mall(S_DBDA,db->dimda);
			dbdatr=call_mall(S_DBDATR,db->dimda);
         dbdau=call_mall(S_DBDAU,db->dimda); 
 			dbdaco=call_mall(S_CALIN,db->dimda);
#ifdef GERARC
 			dbdag=call_mall(S_DBGERA,db->dimda);
#endif

//MAX			size=(long)db->dimda*(long)sizeof(S_CALIN);
//MAX			if(size%RECHALL)
//MAX				size+=RECHALL;
//MAX			dbdaco=call_malh(S_CALIN_H,(size/(long)RECHALL));

		   if(dbda==NULL || dbdatr==NULL || dbdau==NULL || dbdaco==NULL
#ifdef GERARC
                      || dbdag==NULL 
#endif
                     )
{ printf("\nDA"); goto ERROR;}
            else
            printf("\n %d DA %s, %d bytes!",db->dimda,dballoc,(db->dimda)*(sizeof(S_DBDA)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBDATR)+sizeof(S_DBDAU)+sizeof(S_CALIN))); 
//  goto ERROR;
	   }
}
if(db->dimds)
{
		if(flag)
		{
			free((void *)dbds);
			free((void*)dbdstr);	
			free((void*)dbdsu);	
			free((void*)dbdsco);	
			free((void*)dbdsde);	
#ifdef GERARC
			free((void*)dbdsg);	
#endif
		}
		else
		{
 	     dbds=call_mall(S_DBDS,db->dimds);
 	     dbdstr=call_mall(S_DBDSTR,db->dimds);
 	     dbdsu=call_mall(S_DBDSU,db->dimds);
 	     dbdsco=call_mall(S_CALIN,db->dimds);
        dbdsde=call_mall(S_DCALC,db->dimds);
#ifdef GERARC
        dbdsg=call_mall(S_DBGERA,db->dimds);
#endif
	     if(dbds==NULL || dbdstr==NULL || dbdsu==NULL || dbdsco==NULL
#ifdef GERARC
                || dbdsg==NULL 
#endif
			  || dbdsde==NULL)  
{ printf("\nDS"); goto ERROR;}
         else
            printf("\n %d DS %s, %d bytes!",db->dimds,dballoc,(db->dimds)*(sizeof(S_DBDS)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBDSTR)+sizeof(S_DBDSU)+sizeof(S_CALIN)+sizeof(S_DCALC))); 
//goto ERROR;
	   }
}
if(db->dimdc)
{
		if(flag)
		{
			free((void *)dbdc);
			free((void*)dbdctr);	
			free((void*)dbdcu);	
			free((void*)dbdcco);	
#ifdef GERARC
			free((void*)dbdcg);	
#endif
		}
		else
		{
 	     dbdc=call_mall(S_DBDC,db->dimdc);
 	     dbdctr=call_mall(S_DBDCTR,db->dimdc);
 	     dbdcu=call_mall(S_DBDCU,db->dimdc);
 	     dbdcco=call_mall(S_CALIN,db->dimdc);
#ifdef GERARC
 	     dbdcg=call_mall(S_DBGERA,db->dimdc);
#endif
	     if(dbdc==NULL || dbdctr==NULL || dbdcu==NULL || dbdcco==NULL
#ifdef GERARC
                || dbdcg==NULL 
#endif
               )  
{ printf("\nDC"); goto ERROR;}
         else
            printf("\n %d DC %s, %d bytes!",db->dimdc,dballoc,(db->dimdc)*(sizeof(S_DBDC)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBDCTR)+sizeof(S_DBDCU)+sizeof(S_CALIN))); 
//goto ERROR;
	   }
}
if(db->dimdd)
{
		if(flag)
		{
			free((void *)dbdd);
			free((void*)dbddtr);	
			free((void*)dbddu);	
			free((void*)dbddco);	
#ifdef GERARC
			free((void*)dbddg);	
#endif
		}
		else
		{
 	     dbdd=call_mall(S_DBDD,db->dimdd);
 	     dbddtr=call_mall(S_DBDDTR,db->dimdd);
 	     dbddu=call_mall(S_DBDDU,db->dimdd);
 	     dbddco=call_mall(S_CALIN,db->dimdd);
#ifdef GERARC
 	     dbddg=call_mall(S_DBGERA,db->dimdd);
#endif
	     if(dbdd==NULL || dbddtr==NULL || dbddu==NULL || dbddco==NULL
#ifdef GERARC
                ||dbddg==NULL 
#endif
               )
{ printf("\nDD"); goto ERROR;}
         else
            printf("\n %d DD %s, %d bytes!",db->dimdd,dballoc,(db->dimdd)*(sizeof(S_DBDD)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBDDTR)+sizeof(S_DBDDU)+sizeof(S_CALIN))); 
//goto ERROR;
	   }
}
if(db->dimdo)
{
		if(flag)
		{
			free((void *)dbdo);
			free((void*)dbdou);	
			free((void*)dbdom);	
#ifdef GERARC
			free((void*)dbdog);	
#endif
		}
		else
		{
 	     dbdo=call_mall(S_DBDO,db->dimdo);
 	     dbdou=call_mall(S_DBDOU,db->dimdo);
 	     dbdom=call_mall(S_DBDOM,db->dimdo);
#ifdef GERARC
 	     dbdog=call_mall(S_DBGERA,db->dimdo);
#endif
	     if(dbdo==NULL || dbdou==NULL || dbdom==NULL
#ifdef GERARC
                ||dbdog==NULL 
#endif
               )
{ printf("\nDO"); goto ERROR;}
         else
            printf("\n %d DO %s, %d bytes!",db->dimdo,dballoc,(db->dimdo)*(sizeof(S_DBDO)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBDOU)+sizeof(S_DBDOM))); 
//goto ERROR;
	   }
}
if(db->dimor)
{
		if(flag)
		{
			free((void *)dbosc);
			free((void*)dbosa);	
			free((void*)dbosp);	
			free((void*)dbto);	
			free((void*)dbou);	
			free((void*)dboft);	
			free((void*)dbode);	
#ifdef GERARC
			free((void*)dbog);	
#endif
		}
		else
		{
 	     dbosc=call_mall(S_DBOSC,db->dimor);
 	     dbosa=call_mall(S_DBOSA,db->dimor);
 	     dbosp=call_mall(S_DBOSP,db->dimor);
 	     dbto=call_mall(S_DBTO,db->dimor);
 	     dbou=call_mall(S_DBOU,db->dimor);
 	     dboft=call_mall(S_DBOFT,db->dimor);
 	     dbode=call_mall(S_DESORG,db->dimor);
#ifdef GERARC
 	     dbog=call_mall(S_DBGERA,db->dimor);
#endif
	     if(dbosc==NULL || dbosa==NULL || dbosp==NULL || dbto==NULL ||
#ifdef GERARC
                dbog==NULL || 
#endif
		     dbou==NULL || dboft==NULL || dbode==NULL)  
{ printf("\nORG"); goto ERROR;}
        else 
            printf("\n %d OR %s, %d bytes!",db->dimor,dballoc,(db->dimor)*(sizeof(S_DBOSC)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBOSA)+sizeof(S_DBOSP)+sizeof(S_DBTO)+sizeof(S_DBOU)+sizeof(S_DBOFT)+sizeof(S_DESORG))); 
//goto ERROR;
	   }
}
if(db->dimst)
{
		if(flag)
		{
			free((void*)dbsttr);	
			free((void*)dbstu);	
			free((void*)dbstv);	
#ifdef GERARC
			free((void*)dbstg);	
#endif
		}
		else
		{
 	     dbsttr=call_mall(S_DBSTTR,db->dimst);
 	     dbstu=call_mall(S_DBSTU,db->dimst);
 	     dbstv=call_mall(S_DBSTV,(size_t) db->dimst * (size_t) g0lunst);
#ifdef GERARC
 	     dbstg=call_mall(S_DBGERA,db->dimst);
#endif
	     if(dbsttr==NULL || dbstu==NULL || dbstv==NULL
#ifdef GERARC
                || dbstg==NULL 
#endif
               )  
				{ printf("\nSTR"); goto ERROR;}
        else
            {
            printf("\n %d ST %s, %d bytes! \n",db->dimst,dballoc,(db->dimst)*(sizeof(S_DBSTTR)+
#ifdef GERARC
            sizeof(S_DBGERA)+
#endif
            sizeof(S_DBSTU)+sizeof(S_DBSTV)*g0lunst));
            }
	   }
}
return;
ERROR:
printf("\n %s",notenmem);
exit(0);
}
