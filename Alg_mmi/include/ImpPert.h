/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo ImpPert.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)ImpPert.h	5.1
*/
/**********************************************************
			FILE:	ImpPert.h

	Dichiarazioni di extern delle variabili globali
	dichiarate in PertDef.h
**********************************************************/

/******************************************
	Etichette dei bottoni dell'option menu delle perturbazioni
******************************************/
extern char *EditorOption[];

extern int NumPert;

/******************************************
	Definizione delle stringhe da settare come risorsa per essere
	interpretate dal compilatore
******************************************/
extern char *PerturbDefinitions[];

/******************************************
	Definizione delle etichette dei textfield nei quali devono
	essere inseriti i parametri delle perturbazioni
	Vengono abilitati tutti i textfield dove non viene trovata la
	stringa uguale a NULL
******************************************/
extern char *EditorDefinitions[];

/******************************************
	Valori di default per le perturbazioni; anche nelle perturbazioni
	nelle quali non e' necessario il parametro viene inserito uno 0
	per avere compatibilita' con il compilatore
******************************************/
extern char *PerturbDefaults[];
