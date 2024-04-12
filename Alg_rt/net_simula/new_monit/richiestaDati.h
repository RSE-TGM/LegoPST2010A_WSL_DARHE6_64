
/*******************************************************************************
       richiestaDati.h
       This header file is included by richiestaDati.c

*******************************************************************************/

#ifndef	_RICHIESTADATI_INCLUDED
#define	_RICHIESTADATI_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxrichiestaDati;
	int	Uxr;
	int	Uxuscita;
	Widget	Uxw;
	unsigned char	*Uxlabel_string;
	unsigned char	*Uxact;
	unsigned char	*Uxnew;
} _UxCrichiestaDati;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCrichiestaDati       *UxRichiestaDatiContext;
#define richiestaDati           UxRichiestaDatiContext->UxrichiestaDati
#define r                       UxRichiestaDatiContext->Uxr
#define uscita                  UxRichiestaDatiContext->Uxuscita
#define w                       UxRichiestaDatiContext->Uxw
#define label_string            UxRichiestaDatiContext->Uxlabel_string
#define act                     UxRichiestaDatiContext->Uxact
#define new                     UxRichiestaDatiContext->Uxnew

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

int	create_richiestaDati( Widget _Uxw, unsigned char *_Uxlabel_string, unsigned char *_Uxact, unsigned char *_Uxnew );

#endif	/* _RICHIESTADATI_INCLUDED */
