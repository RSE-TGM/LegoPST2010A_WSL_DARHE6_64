/**********************************************************************
*
*       C Source:               rwdb.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:01:25 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: rwdb.c-3 %  (%full_filespec: rwdb.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> rwdb

        routine per la lettura e scrittura del data base 
        di sistema.
		  flag =0 	lettura data base
		  flag =1	scrittura completa data base
		  flag =2	scrittura dinamica ad 
*/

#include <stdio.h>
#include <string.h>

#include "pscs.cfg"
#include "g2comdb.inc"
#include "fileop.inc"
#include "dconf.inc"			 

DB_HEADER h_db;

rwdb (flag)

short  flag ;

{

FILE *fp ;
long i;
char fnome[60] ;

memset(fnome,0,sizeof(fnome));			/* costruidco il nome DATA BASE */
strcpy(fnome,&conf[RTF][0]) ;          
strcat(fnome,FDBDP) ;

if(!flag) printf("\n LETTURA D.B.S.");
else if(flag==1) printf("\n SCRITTURA D.B.S.");

fp=fopen(fnome,"rb+") ;
if(!fp){ printf("errore open file "); return(1) ;}

if(!flag)
{
	if(fread(&h_db,sizeof(DB_HEADER),1,fp)!= 1) perror(" ");
/*
	controllo congruenza dimensionamento data base in fase di
	lettura
*/
	if(h_db.dimaa!=g0dimaa || h_db.dimas!=g0dimas || h_db.dimac!=g0dimac
	|| h_db.dimad!=g0dimad || h_db.dimao!=g0dimao ||
   h_db.dimda!=g0dimda || h_db.dimds!=g0dimds || h_db.dimdc!=g0dimdc
	|| h_db.dimdd!=g0dimdd || h_db.dimdo!=g0dimdo ||
   h_db.dimor!=g0dimor || h_db.dimst!=g0dimst)
	{ printf(" INCONGRUENZA DBS ");
	  printf("\n aa: %d as %d ac %d ad %d ao %d ",g0dimaa,g0dimas,g0dimac,g0dimad,g0dimao);
	  printf("\n da: %d ds %d dc %d dd %d do %d ",g0dimda,g0dimds,g0dimdc,g0dimdd,g0dimdo);
	  printf("\n or: %d str: %d",g0dimor,g0dimst);
	  exit(0); };
}

fseek(fp,(long)ldb_header,0);

if(flag)
{
													        /* data base analogico */
	if(flag==1)											  /* salvataggio completo */
	{
		fwrite((char*)dbaav,sizeof(dbaav),1,fp) ;
		fwrite((char*)dbaaf,sizeof(dbaaf),1,fp) ;
	}
	else
	{
		fseek(fp,(long)sizeof(dbaav),SEEK_CUR) ;
		fseek(fp,(long)sizeof(dbaaf),SEEK_CUR) ;
	 }
	 fseek(fp,(long)sizeof(dbaau),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbaaal),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbaafa),SEEK_CUR) ;

	if(flag==1)											  /* salvataggio completo */
   {
	 fwrite((char*)dbasv,sizeof(dbasv),1,fp) ;
	 fwrite((char*)dbasf,sizeof(dbasf),1,fp) ;
   }
   else
   {
	 fseek(fp,(long)sizeof(dbasv),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbasf),SEEK_CUR) ;
   }
	 fseek(fp,(long)sizeof(dbasu),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbasal),SEEK_CUR) ;
	if(flag==1)											  /* salvataggio completo */
	 fwrite((char*)dbasde,sizeof(dbasde),1,fp) ;
   else
	 fseek(fp,(long)sizeof(dbasde),SEEK_CUR) ;

	 if(flag==1)											  /* salvataggio completo */
	 {
		 fwrite((char*)dbacv,sizeof(dbacv),1,fp) ;
		 fwrite((char*)dbacf,sizeof(dbacf),1,fp) ;
	 }
 	 else
	 {
		 fseek(fp,(long)sizeof(dbacv),SEEK_CUR) ;
		 fseek(fp,(long)sizeof(dbacf),SEEK_CUR) ;
	 }
	 fseek(fp,(long)sizeof(dbacu),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbacal),SEEK_CUR) ;

	 fwrite((char*)dbadv,sizeof(dbadv),1,fp) ;
	 fwrite((char*)dbadf,sizeof(dbadf),1,fp) ;
    if(flag==2) goto FINE;

	 fseek(fp,(long)sizeof(dbadu),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbadal),SEEK_CUR) ;

	 fseek(fp,(long)sizeof(dbaof),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbaou),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbaom),SEEK_CUR) ;

	 if(flag==1)											  /* salvataggio completo */
	    fwrite((char*)dbda,sizeof(dbda),1,fp) ;
	 else
		 fseek(fp,(long)sizeof(dbda),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdatr),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdau),SEEK_CUR) ;
    fseek(fp,(long)sizeof(S_CALIN)*(long)g0dimda,SEEK_CUR) ;

	 if(flag==1)											  /* salvataggio completo */
	   fwrite((char*)dbds,sizeof(dbds),1,fp) ;
	 else
	 	fseek(fp,(long)sizeof(dbds),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdstr),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdsu),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdsco),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdsde),SEEK_CUR) ;

	 if(flag==1)											  /* salvataggio completo */
	    fwrite((char*)dbdc,sizeof(dbdc),1,fp) ;
	 else
	    fseek(fp,(long)sizeof(dbdc),SEEK_CUR) ;
	 fseek(fp,(long)sizeof(dbdctr),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdcu),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdcco),SEEK_CUR) ;

    fwrite((char*)dbdd,sizeof(dbdd),1,fp) ;
    fseek(fp,(long)sizeof(dbddtr),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbddu),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbddco),SEEK_CUR) ;

    fseek(fp,(long)sizeof(dbdo),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdou),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbdom),SEEK_CUR) ;

	 if(flag==1)											  /* salvataggio completo */
	    fwrite((char*)dbosc,sizeof(dbosc),1,fp) ;
	 else
	 	 fseek(fp,(long)sizeof(dbosc),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbosa),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbosp),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbto),SEEK_CUR) ;
    fseek(fp,(long)sizeof(dbou),SEEK_CUR);
    fseek(fp,(long)sizeof(dboft),SEEK_CUR);
    fseek(fp,(long)sizeof(dbode),SEEK_CUR);

    fseek(fp,(long)sizeof(dbsttr),SEEK_CUR);
    fseek(fp,(long)sizeof(dbstu),SEEK_CUR);
    fwrite((char*)dbstv,sizeof(dbstv),1,fp);

}
else
{
	fread((char*)dbaav,sizeof(dbaav),1,fp) ;
	fread((char*)dbaaf,sizeof(dbaaf),1,fp) ;
	fread((char*)dbaau,sizeof(dbaau),1,fp) ;
	fread((char*)dbaaal,sizeof(dbaaal),1,fp) ;
	fread((char*)dbaafa,sizeof(dbaafa),1,fp) ;
	
	fread((char*)dbasv,sizeof(dbasv),1,fp) ;
	fread((char*)dbasf,sizeof(dbasf),1,fp) ;
	fread((char*)dbasu,sizeof(dbasu),1,fp) ;
	fread((char*)dbasal,sizeof(dbasal),1,fp) ;
	fread((char*)dbasde,sizeof(dbasde),1,fp) ;

	fread((char*)dbacv,sizeof(dbacv),1,fp) ;
	fread((char*)dbacf,sizeof(dbacf),1,fp) ;
	fread((char*)dbacu,sizeof(dbacu),1,fp) ;
	fread((char*)dbacal,sizeof(dbacal),1,fp) ;

	fread((char*)dbadv,sizeof(dbadv),1,fp) ;
	fread((char*)dbadf,sizeof(dbadf),1,fp) ;
	fread((char*)dbadu,sizeof(dbadu),1,fp) ;
	fread((char*)dbadal,sizeof(dbadal),1,fp) ;

	fread((char*)dbaof,sizeof(dbaof),1,fp) ;
	fread((char*)dbaou,sizeof(dbaou),1,fp) ;
	fread((char*)dbaom,sizeof(dbaom),1,fp) ;

	fread((char*)dbda,sizeof(dbda),1,fp) ;
	fread((char*)dbdatr,sizeof(dbdatr),1,fp) ;
	fread((char*)dbdau,sizeof(dbdau),1,fp) ;
	for(i=0;i<g0dimda;i++) fread((char*)&dbdaco[i],sizeof(S_CALIN),1,fp) ;
	
	fread((char*)dbds,sizeof(dbds),1,fp) ;
	fread((char*)dbdstr,sizeof(dbdstr),1,fp) ;
	fread((char*)dbdsu,sizeof(dbdsu),1,fp) ;
	fread((char*)dbdsco,sizeof(dbdsco),1,fp) ;
	fread((char*)dbdsde,sizeof(dbdsde),1,fp) ;

	fread((char*)dbdc,sizeof(dbdc),1,fp) ;
	fread((char*)dbdctr,sizeof(dbdctr),1,fp) ;
	fread((char*)dbdcu,sizeof(dbdcu),1,fp) ;
	fread((char*)dbdcco,sizeof(dbdcco),1,fp) ;

	fread((char*)dbdd,sizeof(dbdd),1,fp) ;
	fread((char*)dbddtr,sizeof(dbddtr),1,fp) ;
	fread((char*)dbddu,sizeof(dbddu),1,fp) ;
	fread((char*)dbddco,sizeof(dbddco),1,fp) ;

	fread((char*)dbdo,sizeof(dbdo),1,fp) ;
	fread((char*)dbdou,sizeof(dbdou),1,fp) ;
	fread((char*)dbdom,sizeof(dbdom),1,fp) ;

	fread((char*)dbosc,sizeof(dbosc),1,fp) ;
	fread((char*)dbosa,sizeof(dbosa),1,fp) ;
	fread((char*)dbosp,sizeof(dbosp),1,fp) ;
	fread((char*)dbto.tc,sizeof(dbto),1,fp) ;
	fread((char*)dbou,sizeof(dbou),1,fp);
	fread((char*)dboft,sizeof(dboft),1,fp);
	fread((char*)dbode,sizeof(dbode),1,fp);

	fread((char*)dbsttr,sizeof(dbsttr),1,fp);
	fread((char*)dbstu,sizeof(dbstu),1,fp);
	fread((char*)dbstv,sizeof(dbstv),1,fp);

}

FINE:

fclose(fp);

}


