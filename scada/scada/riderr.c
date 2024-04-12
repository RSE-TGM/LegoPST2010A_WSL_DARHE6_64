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
/* ->RIDERR.C
 *       ridirige i messaggi di errore del dos alla routine handler che
 *       si limita a settare a 1 il corrispondente digitale di diagnostica
 *       Per ora Š utilizzata solo per filtrare gli errori relativi al
 *       disco A. 
 */                    
#include <dos.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "diagnodi.inc"

/*	  Decodifica byte basso	di errcode    */

#define WRPRO    0     // tentativo lettura disco write protected
#define NODISK   2     // disco non pronto
#define NOREAD   0x0a  // fallimento write 
#define NOWRITE  0x0b  // fallimento read			

/*   Decodifica bit di errore disco di deverror  */

#define BITDISK  0x80  // bit a 0 se errore disco

//register int __far handler(unsigned deverror,unsigned errcode,unsigned far *devhdr);

riderr()
{
//_harderr(handler);	
}
/*
int __far handler(unsigned deverror,unsigned errcode,unsigned __far *devhdr)
{ 
short drive;   // drive su cui si Š verificato l'errore

if((deverror &	BITDISK)==0)  // se Š un errore di disco
	{
	drive=deverror&0x0f;    // seleziona il drive
	if(drive==0)
		{
		bitset(&dbdd[diskerr],g2di_sl,1);
		}
	}
return(_HARDERR_FAIL);
}
*/
