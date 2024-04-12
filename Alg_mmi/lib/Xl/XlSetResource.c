/**********************************************************************
*
*       C Source:               XlSetResource.c
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Thu Oct 24 10:40:10 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XlSetResource.c-2.1.1 %  (%full_filespec: XlSetResource.c-2.1.1:csrc:1 %)";
#endif
/*
   modulo XlSetResource.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlSetResource.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XlSetResource.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*-------------------------------------------------------------------*
 *								     *
 * Module Name:   XlSetResource.c                                    *
 *							 	     *
 * Date: 13 Gennaio 1994	Ver: 1.0 			     *
 *-------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <Xm/Xm.h>
#include <Xl/XlCore.h>
#include <Xl/Xl.h>   


/*------------------------------------------------------------------
 * Function Name:   XlSetResourceByName				   *
 *								   *
 * Parameter:      						   *
 *      XrmDatabase *pRisDb;  puntatore al database delle risorse  *
 *      String nome_oggetto;  nome dello Widget 		   *
 *      char *resource_name;  nome della risorsa da settare        *
 *      char *value;          valore in forma ASCII. 		   *
 *								   *
 * Description:   effettua il set della risorsa resource_name      *
 *                dell'oggetto nome_oggetto                        *
 *                contenuta nel db pRisDb al valore value.         *
 *                						   *
 * Date: 13 Gennaio 1993	Ver: 1.0                           *
 *-----------------------------------------------------------------*/

XlSetResourceByName(XrmDatabase *pRisDb,String nome_oggetto,char *resource_name,char *value)
{
   char str_risorsa[250];

/* compongo il nome della risorsa */
   strcpy(str_risorsa,"*");
   strcat(str_risorsa,nome_oggetto);
   strcat(str_risorsa,".");
   strcat(str_risorsa,resource_name);

/* ed effettuo la Put nel database delle resource */
   XrmPutStringResource(pRisDb,str_risorsa,value);
}



/*------------------------------------------------------------------
 * Function Name:   XlSetChildResourceByName                       *
 *								   *
 * Parameter:      						   *
 *      XrmDatabase *pRisDb;  puntatore al database delle risorse  *
 *      String nome_padre;    nome dell'oggetto padre              *
 *      String nome_figlio;   nome dell'oggetto da settare         *
 *      char *resource_name;  nome della risorsa da settare        *
 *      char *value;          valore in forma ASCII.               *
 *								   *
 * Description:   effettua il set della risorsa resource_name      * 
 *                del nome_figlio il cui padre e' nome_padre       *
 *                contenuta nel db pRisDb al valore value.         *
 *                						   *
 * Date: 13 Gennaio 1993	Ver: 1.0                           *
 *-----------------------------------------------------------------*/

XlSetChildResourceByName(XrmDatabase *pRisDb,String nome_padre,String nome_figlio,char *resource_name,char *value)
{
   char str_risorsa[250];

/* compongo il nome della risorsa */
   strcpy(str_risorsa,"*");
/***
   strcat(str_risorsa,nome_padre);  
   strcat(str_risorsa,".");
***/
   strcat(str_risorsa,nome_figlio);
   strcat(str_risorsa,".");
   strcat(str_risorsa,resource_name);

/* ed effettuo la Put nel database delle resource */
   XrmPutStringResource(pRisDb,str_risorsa,value);
}


/*------------------------------------------------------------------
 * Function Name:   XlSetChildResourceByWidget                     *
 *								   *
 * Parameter:      						   *
 *      XrmDatabase *pRisDb;  puntatore al database delle risorse  *
 *      Widget w;             indice dello widget da settare       *
 *      char *resource_name;  nome della risorsa da settare        *
 *      char *value;          valore in forma ASCII.               *
 *								   *
 * Description:   effettua il set della risorsa resource_name      * 
 *                dello widget w                                   *
 *                contenuta nel db pRisDb al valore value.         *
 *                						   *
 * Date: 13 Gennaio 1993	Ver: 1.0                           *
 *-----------------------------------------------------------------*/

XlSetResourceByWidget(XrmDatabase *pRisDb,Widget w,char *resource_name,char *value)
{
   Cardinal nargs;
   Arg args[2];
   char *nome_oggetto;
   char str_risorsa[250]; 

/* recupera il nome dell'oggetto */
   nome_oggetto = XtName (w);

/* compone il nome della risorsa */
   strcpy(str_risorsa,"*");
   strcat(str_risorsa,nome_oggetto);
   strcat(str_risorsa,".");
   strcat(str_risorsa,resource_name);

/* ed effettuo la Put nel database delle resource */
   XrmPutStringResource(pRisDb,str_risorsa,value);
}

#if !(defined OSF1 || SCO_UNIX || VMS || LINUX)
/*
    Vengono definite le seguenti routine nel caso non si lavori
	sotto OSF1 o VMS perche' sotto sistemi AIX e ULTRIX tali routine
	non sono definite
*/
/*------------------------------------------------------------------
 * Function Name:   XrmGetDatabase                                 *
 *								   *
 * Parameter:      						   *
 *      Display *Displ;       puntatore al display del quale si    *
 *				vuole il database associato        *
 *								   *
 * Description:   Restituisce il database associato al display     *
 *                   passato come parametro                        * 
 *                						   *
 * Date: 09 Giugno 1994		Ver: 1.0                           *
 *-----------------------------------------------------------------*/
XrmDatabase XrmGetDatabase (Display *Displ)
{
	return (Displ->db);
}

/*------------------------------------------------------------------
 * Function Name:   XrmSetDatabase                                 *
 *								   *
 * Parameter:      						   *
 *      Display *Displ;       puntatore al display del quale si    *
 *				vuole il database associato;       *
 *      XrmDatabase DB;	      Database da associare al display;    *
 *								   *
 * Description:   Associa il database passato come parametro al    *
 *                 display passato come parametro;                 *
 *                						   *
 * Date: 09 Giugno 1994		Ver: 1.0                           *
 *-----------------------------------------------------------------*/
void XrmSetDatabase (Display *Displ,XrmDatabase DB)
{
	Displ->db = DB;
}
#endif

/*------------------------------- End_of_File ----------------------------*/
