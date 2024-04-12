/**********************************************************************
*
*       C Header:               PertDef.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jul 10 12:54:20 1996 %
*
**********************************************************************/
/**********************************************************
			FILE:	PertDef.h

	Definizioni di tipi e costanti per l'editor
	delle perturbazioni.
**********************************************************/
#ifndef EDITOR_PERTURBAZIONI
#define EDITOR_PERTURBAZIONI

/******************************************
	Etichette dei bottoni dell'option menu delle perturbazioni
******************************************/
char *EditorOption[] = {"NOT",
			"STEP",
			"PULSE",
			"RAMP",
			"UP DOWN",
			"MALFUNCTION",
			"MALF STOP"};

int NumPert = XtNumber (EditorOption);

/******************************************
	Definizione delle stringhe da settare come risorsa per essere
	interpretate dal compilatore
******************************************/
char *PerturbDefinitions[] =	{"PERT_NOT",
				"PERT_SCALINO",
				"PERT_IMPULSO",
				"PERT_RAMPA",
				"PERT_UP_DOWN",
				"PERT_MALFUNCTION",
				"PERT_MALFUNCTION_STOP"};

/******************************************
	Definizione delle etichette dei textfield nei quali devono
	essere inseriti i parametri delle perturbazioni
	Vengono abilitati tutti i textfield dove non viene trovata la
	stringa uguale a NULL
******************************************/
char *EditorDefinitions[] =	{"NULL",
				"Target Value",	"NULL",
				"Target Value",	"Wide",	"NULL",
				"Target Value",	"Grad.","NULL",
				"NULL",
                                "Target Value", "Type","NULL",
                                "NULL"};

/******************************************
	Valori di default per le perturbazioni; anche nelle perturbazioni
	nelle quali non e' necessario il parametro viene inserito uno 0
	per avere compatibilita' con il compilatore
******************************************/
char *PerturbDefaults[] =	{"0.0","0.0","NULL",
			"1.0","0.0","NULL",
			"1.0","0.0","NULL",
			"0.0","0.0","NULL",
			"0.0","0.0","NULL",
			"0.0","0.0","NULL",
                        "0.0","0.0","NULL"};

#endif
