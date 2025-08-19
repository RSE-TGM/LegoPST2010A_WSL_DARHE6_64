/**********************************************************************
*
*       C Source:               simsvdbs.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 12:23:42 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: simsvdbs.c-3 %  (%full_filespec: simsvdbs.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	Modulo:  SIMSVDBS.C
            Backup/Restore su/da file FDBDP.SAV del data base di sistema (DBS).
   
   Parametri: short opz: flag operazione voluta: 

   03.08.92  -  Rel. 1.0  - GM.Furlan

   27 Marzo 1995 Fc Porting a 32Bit
*/

#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "dconf.inc"
#include "simula.inc"
#include "pscserr.inc"

// External function declarations
extern void pscserr(int, int, int, int, int);
extern int wbyte(int, void *, long, int);
extern int rbyte(int, void *, long, int);

#define	of_dbaav		(long)ldb_header
#define  of_dbaaf		(long)of_dbaav  + ((long)h_db.dimaa*sizeof(S_DBAAV))
#define  of_dbaau 	(long)of_dbaaf  + ((long)h_db.dimaa*sizeof(S_DBAAF))
#define  of_dbaaal	(long)of_dbaau  + ((long)h_db.dimaa*sizeof(S_DBAAU))       
#define  of_dbaafa	(long)of_dbaaal + ((long)h_db.dimaa*sizeof(S_DBALL))

#define	of_dbasv		(long)of_dbaafa + ((long)h_db.dimaa*sizeof(S_DBAAFA))
#define  of_dbasf		(long)of_dbasv  + ((long)h_db.dimas*sizeof(S_DBASV))
#define  of_dbasu 	(long)of_dbasf  + ((long)h_db.dimas*sizeof(S_DBASF))
#define  of_dbasal	(long)of_dbasu  + ((long)h_db.dimas*sizeof(S_DBASU))
#define  of_dbasde	(long)of_dbasal + ((long)h_db.dimas*sizeof(S_DBALL))

#define	of_dbacv		(long)of_dbasde + ((long)h_db.dimas*sizeof(DES))
#define  of_dbacf		(long)of_dbacv  + ((long)h_db.dimac*sizeof(S_DBACV))
#define  of_dbacu 	(long)of_dbacf  + ((long)h_db.dimac*sizeof(S_DBACF))
#define  of_dbacal	(long)of_dbacu  + ((long)h_db.dimac*sizeof(S_DBACU))

#define	of_dbadv		(long)of_dbacal + ((long)h_db.dimac*sizeof(S_DBALL))
#define  of_dbadf		(long)of_dbadv  + ((long)h_db.dimad*sizeof(S_DBADV))
#define  of_dbadu 	(long)of_dbadf  + ((long)h_db.dimad*sizeof(S_DBADF))
#define  of_dbadal	(long)of_dbadu  + ((long)h_db.dimad*sizeof(S_DBADU))

#define  of_dbaof		(long)of_dbadal + ((long)h_db.dimad*sizeof(S_DBALL))
#define  of_dbaou 	(long)of_dbaof  + ((long)h_db.dimao*sizeof(S_DBAOF))
#define  of_dbaom		(long)of_dbaou  + ((long)h_db.dimao*sizeof(S_DBAOU))

#define	of_dbda		(long)of_dbaom  + ((long)h_db.dimao*sizeof(S_DBAOM))
#define  of_dbdatr	(long)of_dbda   + ((long)h_db.dimda*sizeof(S_DBDA))
#define  of_dbdau 	(long)of_dbdatr + ((long)h_db.dimda*sizeof(S_DBDATR))
#define  of_dbdaco	(long)of_dbdau  + ((long)h_db.dimda*sizeof(S_DBDAU))

#define	of_dbds		(long)of_dbdaco + ((long)h_db.dimda*sizeof(S_CALIN))
#define  of_dbdstr	(long)of_dbds   + ((long)h_db.dimds*sizeof(S_DBDS))
#define  of_dbdsu 	(long)of_dbdstr + ((long)h_db.dimds*sizeof(S_DBDSTR))
#define  of_dbdsco	(long)of_dbdsu  + ((long)h_db.dimds*sizeof(S_DBDSU))
#define  of_dbdsde	(long)of_dbdsco + ((long)h_db.dimds*sizeof(S_CALIN))

#define	of_dbdc		(long)of_dbdsde + ((long)h_db.dimds*sizeof(S_DCALC))
#define  of_dbdctr	(long)of_dbdc   + ((long)h_db.dimdc*sizeof(S_DBDC))
#define  of_dbdcu 	(long)of_dbdctr + ((long)h_db.dimdc*sizeof(S_DBDCTR))
#define  of_dbdcco	(long)of_dbdcu  + ((long)h_db.dimdc*sizeof(S_DBDCU))

#define	of_dbdd		(long)of_dbdcco + ((long)h_db.dimdc*sizeof(S_CALIN))
#define  of_dbddtr	(long)of_dbdd   + ((long)h_db.dimdd*sizeof(S_DBDD))
#define  of_dbddu 	(long)of_dbddtr + ((long)h_db.dimdd*sizeof(S_DBDDTR))
#define  of_dbddco	(long)of_dbddu  + ((long)h_db.dimdd*sizeof(S_DBDDU))

#define	of_dbdo		(long)of_dbddco + ((long)h_db.dimdd*sizeof(S_CALIN))
#define  of_dbdou 	(long)of_dbdo   + ((long)h_db.dimdo*sizeof(S_DBDO))
#define  of_dbdom		(long)of_dbdou  + ((long)h_db.dimdo*sizeof(S_DBDOU))

#define	of_dbosc 	(long)of_dbdom  + ((long)h_db.dimdo*sizeof(S_DBDOM))
#define  of_dbosa	   (long)of_dbosc  + ((long)h_db.dimor*sizeof(S_DBOSC))
#define  of_dbosp 	(long)of_dbosa  + ((long)h_db.dimor*sizeof(S_DBOSA))
#define  of_dbto  	(long)of_dbosp  + ((long)h_db.dimor*sizeof(S_DBOSP))
#define	of_dbou		(long)of_dbto   + ((long)h_db.dimor*sizeof(S_DBTO))
#define  of_dboft 	(long)of_dbou   + ((long)h_db.dimor*sizeof(S_DBOU))
#define  of_dbode 	(long)of_dboft  + ((long)h_db.dimor*sizeof(S_DBOFT))

#define	of_dbsttr 	(long)of_dbode  + ((long)h_db.dimor*sizeof(S_DESORG))
#define  of_dbstu		(long)of_dbsttr + ((long)h_db.dimst*sizeof(S_DBSTTR))
#define  of_dbstv 	(long)of_dbstu  + ((long)h_db.dimst*sizeof(S_DBSTU))

extern DB_HEADER h_db;

int simsvdbs(opz)
short opz;     // opz=SAVE: salva DBS; opz=RESTORE: ripristina DBS
{
FILE *fp;
char filename[FILENAME_MAX+1];

strcpy(filename,conf[RTF]);
#if defined OSF1 || defined LINUX
strcat(filename,"/fdbdp.sav");
#else
strcat(filename,"\\fdbdp.sav");
#endif

switch (opz)
{
   case SAVE:      // salva DBS su FDBDP.SAV

      fp=fopen(filename,"wb");
      if(fp==NULL)
	   {
			// errore apertura file FDBDP.SAV
         pscserr(ERR_IO,TASK_SIMACQUI,ROU_SVDBS,0,SYS_CONT);
			return(-1);
		}

      // header:
      wbyte(fileno(fp),(short*)&h_db,(long)0,sizeof(DB_HEADER));
      // aa:
//printf("\n%f,%ld,%d ",*dbaav,of_dbaav,h_db.dimaa*sizeof(S_DBAAV));
      wbyte(fileno(fp),(short*)dbaav,of_dbaav,h_db.dimaa*sizeof(S_DBAAV));
      wbyte(fileno(fp),(short*)dbaaf,of_dbaaf,h_db.dimaa*sizeof(S_DBAAF));
      wbyte(fileno(fp),(short*)dbaaal,of_dbaaal,h_db.dimaa*sizeof(S_DBALL));
      wbyte(fileno(fp),(short*)dbaafa,of_dbaafa,h_db.dimaa*sizeof(S_DBAAFA));
      
      // as:
      wbyte(fileno(fp),(short*)dbasv,of_dbasv,h_db.dimas*sizeof(S_DBASV));	  
      wbyte(fileno(fp),(short*)dbasf,of_dbasf,h_db.dimas*sizeof(S_DBASF));
      wbyte(fileno(fp),(short*)dbasal,of_dbasal,h_db.dimas*sizeof(S_DBALL));
      wbyte(fileno(fp),(short*)dbasde,of_dbasde,h_db.dimas*sizeof(DES));
      
      // ac:
      wbyte(fileno(fp),(short*)dbacv,of_dbacv,h_db.dimac*sizeof(S_DBACV));
      wbyte(fileno(fp),(short*)dbacf,of_dbacf,h_db.dimac*sizeof(S_DBACF));
      wbyte(fileno(fp),(short*)dbacal,of_dbacal,h_db.dimac*sizeof(S_DBALL));
      
      // ad:
      wbyte(fileno(fp),(short*)dbadv,of_dbadv,h_db.dimad*sizeof(S_DBADV));		
      wbyte(fileno(fp),(short*)dbadf,of_dbadf,h_db.dimad*sizeof(S_DBADF));
      wbyte(fileno(fp),(short*)dbadal,of_dbadal,h_db.dimad*sizeof(S_DBALL));
      
      // da:
      wbyte(fileno(fp),(short*)dbda,of_dbda,h_db.dimda*sizeof(S_DBDA));			
      
      // ds:
      wbyte(fileno(fp),(short*)dbds,of_dbds,h_db.dimds*sizeof(S_DBDS));			
      
      // dc:
      wbyte(fileno(fp),(short*)dbdc,of_dbdc,h_db.dimdc*sizeof(S_DBDC));			
      
      // dd:
      wbyte(fileno(fp),(short*)dbdd,of_dbdd,h_db.dimdd*sizeof(S_DBDD));			
      
      // or:
      wbyte(fileno(fp),(short*)dbosc,of_dbosc,h_db.dimor*sizeof(S_DBOSC));
      wbyte(fileno(fp),(short*)dbosa,of_dbosa,h_db.dimor*sizeof(S_DBOSA));
      wbyte(fileno(fp),(short*)dbosp,of_dbosp,h_db.dimor*sizeof(S_DBOSP));
      wbyte(fileno(fp),(short*)dbto,of_dbto,h_db.dimor*sizeof(S_DBTO));
      wbyte(fileno(fp),(short*)dboft,of_dboft,h_db.dimor*sizeof(S_DBOFT));
      
      // st:
      wbyte(fileno(fp),(short*)dbstv,of_dbstv,h_db.dimst*sizeof(S_DBSTV));		
   break;


   case RESTORE:   // legge DBS da FDBDP.SAV

      fp=fopen(filename,"rb");
      if(fp==NULL)
	   {
			// errore apertura file FDBDP.SAV
         pscserr(ERR_IO,TASK_SIMACQUI,ROU_SVDBS,0,SYS_CONT);
			return(-1);
		}

      // header:
      rbyte(fileno(fp),(short*)&h_db,(long)0,sizeof(DB_HEADER));
      
      // aa:
      rbyte(fileno(fp),(short*)dbaav,of_dbaav,h_db.dimaa*sizeof(S_DBAAV));	  
      rbyte(fileno(fp),(short*)dbaaf,of_dbaaf,h_db.dimaa*sizeof(S_DBAAF));
      rbyte(fileno(fp),(short*)dbaaal,of_dbaaal,h_db.dimaa*sizeof(S_DBALL));
      rbyte(fileno(fp),(short*)dbaafa,of_dbaafa,h_db.dimaa*sizeof(S_DBAAFA));
      
      // as:
      rbyte(fileno(fp),(short*)dbasv,of_dbasv,h_db.dimas*sizeof(S_DBASV));	  
      rbyte(fileno(fp),(short*)dbasf,of_dbasf,h_db.dimas*sizeof(S_DBASF));
      rbyte(fileno(fp),(short*)dbasal,of_dbasal,h_db.dimas*sizeof(S_DBALL));
      rbyte(fileno(fp),(short*)dbasde,of_dbasde,h_db.dimas*sizeof(DES));
      
      // ac:
      rbyte(fileno(fp),(short*)dbacv,of_dbacv,h_db.dimac*sizeof(S_DBACV));
      rbyte(fileno(fp),(short*)dbacf,of_dbacf,h_db.dimac*sizeof(S_DBACF));
      rbyte(fileno(fp),(short*)dbacal,of_dbacal,h_db.dimac*sizeof(S_DBALL));
      
      // ad:
      rbyte(fileno(fp),(short*)dbadv,of_dbadv,h_db.dimad*sizeof(S_DBADV));		
      rbyte(fileno(fp),(short*)dbadf,of_dbadf,h_db.dimad*sizeof(S_DBADF));
      rbyte(fileno(fp),(short*)dbadal,of_dbadal,h_db.dimad*sizeof(S_DBALL));
      
      // da:
      rbyte(fileno(fp),(short*)dbda,of_dbda,h_db.dimda*sizeof(S_DBDA));			
      
      // ds:
      rbyte(fileno(fp),(short*)dbds,of_dbds,h_db.dimds*sizeof(S_DBDS));			
      
      // dc:
      rbyte(fileno(fp),(short*)dbdc,of_dbdc,h_db.dimdc*sizeof(S_DBDC));			
      
      // dd:
      rbyte(fileno(fp),(short*)dbdd,of_dbdd,h_db.dimdd*sizeof(S_DBDD));			
      
      // or:
      rbyte(fileno(fp),(short*)dbosc,of_dbosc,h_db.dimor*sizeof(S_DBOSC));
      rbyte(fileno(fp),(short*)dbosa,of_dbosa,h_db.dimor*sizeof(S_DBOSA));
      rbyte(fileno(fp),(short*)dbosp,of_dbosp,h_db.dimor*sizeof(S_DBOSP));
      rbyte(fileno(fp),(short*)dbto,of_dbto,h_db.dimor*sizeof(S_DBTO));
      rbyte(fileno(fp),(short*)dboft,of_dboft,h_db.dimor*sizeof(S_DBOFT));
      
      // st:
      rbyte(fileno(fp),(short*)dbstv,of_dbstv,h_db.dimst*sizeof(S_DBSTV));		
   break;
}

fclose(fp);

return(0);

}
