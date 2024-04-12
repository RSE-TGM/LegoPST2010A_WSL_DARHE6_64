/*
*  Main program   viewval TAG -t CHECK (visualizza Stato sim)
*/

#include <stdio.h>

#define TIMELOOP 2
#define TIMEMIN 0.01
#define TIMEMAX 30
#include "viewshr.h"
#include "sked.h"
#include <stdlib.h>

double timeloop, timeprint, conta;
int passo;
unsigned int timemilli;
static char *progname; /* nome di questo programma */
static char nomevar[10];
int modo, indir, stato, num_var, viewshr(), forza;
float valore, tempo, valprec, forzval;

#define stampa(str,val1,val2) printf("\t%s\t%f\t%f\n",str,val1,val2)
// #define stampaeff(str1,str2,val) printf("\t%s\t\t%s\t\t%f\r",str1,str2,val)
#define stampaeff(str1,str2,val) printf(" %s\t%s\t\t\t\t%f\r",str1,str2,val)
void usage ()
{
   

    fprintf (stderr, 
	     "\nuso:  %s nome_variabile [-opzioni ... ]\n",
	     progname);
    
    
    fprintf (stderr, 
	     "le opzioni sono:\n");
    fprintf (stderr, "    -t tempoloop       tempo di loop. \n");
    fprintf (stderr, "                       Passo di tempo di controllo di una\n"); 
    fprintf (stderr, "                       eventuale variazione nel valore della\n");
    fprintf (stderr, "                       variabile.\n\n");
    fprintf (stderr, "    -p tempoprint      tempo di stampa forzata.\n");
    fprintf (stderr, "                       Allo scadere di tempoprint viene forzata\n");
    fprintf (stderr, "                       la stampa della variabile, anche se \n");
    fprintf (stderr, "                       non e` variata.\n\n");
    fprintf (stderr, "    -f valore_forzato  valore (float) da assegnare alla variabile\n");
    fprintf (stderr, "                       Si ignorano le opzioni -t e -p\n");

/*    
    fprintf (stderr, "\n\nSi ricorda che %s legge e scrive i seguenti file.\n", progname);
    fprintf (stderr, "file di  input: LISTA_VARLOG     lista delle variabili (nome + descrizione)\n");
    fprintf (stderr, "file di output: VAR.LOG          listato degli eventi\n");
*/
    fprintf (stderr, "\n");

    return 1;
}


void main(argc,argv)
int argc;
char **argv;

 {
chdir ("e:/La_spezia/sked/spezia_r0/");


  SetUp (argc, argv);
  viewshr( INIZIALIZZA, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
  if ( !viewshr( GETIND, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval)) 
     {
	
	switch (stato)
		{ 
		case 0:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato  STOP</H2></CENTER>\n");
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");	
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");	
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		break;
		case 1:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato  RUN</H2></CENTER>\n");	
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");	
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");	
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		break;
		case 2:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato FREEZE</H2></CENTER>\n");	
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);	
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");		
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		break;
		case 3:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");	
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato BACKTRACK</H2></CENTER>\n");
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");		
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");	
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		break;
		case 4:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");	
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato REPLAY</H2></CENTER>\n");	
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");	
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");	
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		break;
		case 5:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato ERRORE</H2></CENTER>\n");	
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);	
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");	
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		break;
	       default:
			printf("Content-Type:text/html\n\n\n");
     		        printf("<HTML>\n");
	                printf("<BODY>\n");
			printf("<body bgcolor=#e3ffe3 text=#000000 bgproperties=fixed>\n");
			printf("<H1><IMG height=75 src=http://txpuerto9/wwwLEGO/images/Logo-enel.gif style=HEIGHT:20px; WIDTH:10px width=50 >&nbsp;&nbsp;&nbsp;&nbsp;<FONT size=2>&nbsp;<FONT color=mediumblue><SUB>Unità Automazione e Sistemi di Diagnostica </SUB></FONT></FONT></H1>\n");
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
	                printf("<CENTER><H2>stato NON DEFINITO</H2></CENTER>\n");	
	                printf("<H3>tempo di simulazione %f [sec] </H3>\n",tempo);	
			printf("<p>&nbsp;&nbsp;&nbsp;&nbsp;</p>\n");
			printf("<form action=http://txpuerto9/wwwLEGO/La_spezia.asp method=post name=agg id=FORM1><p><input type=submit name=B1 value=<----  style=BACKGROUND-COLOR:#3399ff; BORDER-BOTTOM-COLOR:black; BORDER-TOP-COLOR:white; CURSOR:hand; HEIGHT:34px; WIDTH:192px></p>\n");
			printf("<META HTTP-EQUIV=Refresh CONTENT=4;URL=http://txpuerto9:81/cgi-bin/shellL.bat>\n");	
	                printf("</BODY>\n");
	                printf("</HTML>\n");
		}
        return 0;
     }
  viewshr( GETVAR, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
  printf("\n\tVariabile\tValore\t\tTempo\n");
  stampa(nomevar,valore,tempo);
    
  if (forza) {
        viewshr( PUTVAR, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
        viewshr( GETVAR, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
        printf("-->\b\b\b");
	stampa(nomevar,valore,tempo);

	  
	return 0;
  }
  	
  if ( (timeloop <= 0) && (timeprint <= 0) )
	 
  return 0;
  valprec=valore;
  
  if ( timeloop > 0 ) timemilli= (unsigned int)(timeloop * 1000.);
  else timemilli= (unsigned int)(timeprint * 1000.);
  
  while (1)
  {
        viewshr( CHECK, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
        if( stato == STATO_STOP )
        {
         fprintf( stderr, "\n---------\n%s termina. Simulatore in STOP \n---------\n", argv[0]);
 
	return 0;
        }
        else if( stato == STATO_ERRORE ) 
        {
         fprintf( stderr, "\n---------\n%s termina. Simulatore in ERRORE \n---------\n", argv[0]);
	
         return 0;
        }
                                                              
	  
//         sleep ( (unsigned int)timeloop );
          sospendi( timemilli ); 
// DEBUG fprintf( stderr, "\n---------> %d %d %d\n",++passo,timemilli,timeloop );
        if (timeprint >= 0)
        {
           conta=conta - timeloop;
           if ( (conta <= 0) || (timeloop <= 0) ) 
              {
               viewshr( GETVAR, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
               stampa(nomevar,valore,tempo);
               conta = timeprint;
              }
        }
        if( stato == STATO_FREEZE )
        {
         continue;
// DEBUG        fprintf( stderr, "Simulatore in FREEZE \n");
        }
        else 
	{
	   viewshr( GETVAR, nomevar, &indir, &valore ,&stato, &tempo, &num_var, forzval);
           if (valprec != valore ) stampa(nomevar,valore,tempo);
	   valprec=valore;
	}
  }



}

SetUp (argc, argv)
  int argc;
  char **argv;
   {
  int i;
  
  progname  = argv[0];

  timeprint = -1;
  timeloop  = -1;
  //forza = FALSE;
     /* Parse command line */
     for (i = 1; i < argc; i++) {
       char *arg = argv[i];

       if (arg[0] == '-') {

	   switch (arg[1]) {
	       case 't':				/* -t tempo di loop */
		   if (++i >= argc) usage ();
		   timeloop = atof(argv[i]);
		   fprintf(stderr,"Valore timeloop=%lf\n",timeloop);
		   if (timeloop <= TIMEMIN ) {
		        fprintf(stderr,"Valore non corretto del tempo di loop\n Si imposta il valore minimo %lf\n",TIMEMIN);
			timeloop=TIMEMIN;
		   }
		   else if  (timeloop >= TIMEMAX )  {
                        fprintf(stderr,"Valore non corretto del tempo di loop\n Si imposta il valore massimo %lf\n",TIMEMAX);
                        timeloop=TIMEMAX;
                   }
		   continue;
	       case 'p':				/* -p tempo di stampa */
		   if (++i >= argc) usage ();
		   timeprint = atof(argv[i]);
		   conta = timeprint;
		   fprintf(stderr,"Valore timeprint=%lf\n",timeprint);
		   continue;
	       case 'f':				/* -p tempo di stampa */
		   if (++i >= argc) usage ();
		   forzval = atof(argv[i]);
		   fprintf(stderr,"Valore forzato=%lf\n",forzval);
		   //forza = TRUE ;
		   continue;
	       default:
		  // usage ();
		   continue;
	   }
       } 
       else 
    	  strcpy(nomevar,argv[1]);	   
     }
  }
