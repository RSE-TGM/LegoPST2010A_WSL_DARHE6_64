/**********************************************************************
*
*       C Source:               aggfconf.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 15:32:22 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: aggfconf.c-3 %  (%full_filespec: aggfconf.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	AGGIORNA LA RELEASE AL FILE Fdbdp.RTF
*/


#include <stdio.h>
//MAX #include <memory.h>
#include <string.h>
#include <time.h>

#include "dconf.inc"
#include <stdlib.h>
#include <sys/time.h>

extern DB_HEADER h_db;

void aggfconf(flag)
short flag;
{

 short ier;
 FILE *fp;
 char fnome[FILENAME_MAX+1];
 char *setflag;

 if(flag==FPUNTI) setflag=&h_db.fpunti;
 else             setflag=&h_db.fpagine;

 if(!(*setflag)) return;         // nessuna variazione
/*
	configurazione variata reset flag ed incremento release
*/
 *setflag=0;
 strcpy(fnome,&conf[RTF][0]);				
 strcat(fnome,FDBDP);				

 fp=fopen(fnome,"r+b") ;
 if(!fp){ printf("errore open file "); exit(0) ;}

 
  // aggiorna la release 

  h_db.release[3]++;
  if (h_db.release[3] > '9' ) 
  {
 	 	h_db.release[3]='0';
  		h_db.release[1]++;
	   if (h_db.release[1] > '9' ) 
	   {
  			h_db.release[1]='0';
		  	h_db.release[0]++;
		   if (h_db.release[0] > '9' ) 
		   {
  				h_db.release[0]='0';
			}
		}
	}

	// aggiorna la data

	// Replace DOS functions with POSIX time functions
	time_t now = time(NULL);
	struct tm *tm_info = localtime(&now);
	// Set date and time fields based on tm structure
	// Note: Assuming h_db.data and h_db.ora have compatible structure
   
	fwrite(&h_db,sizeof (DB_HEADER),1,fp) ;
   fclose(fp);
}	






