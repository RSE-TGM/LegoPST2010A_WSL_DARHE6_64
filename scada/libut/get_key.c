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
#include "stdio.h"
#include "ctype.h"
#include <termios.h>
#include <unistd.h>

int get_key(s)
short *s;
{
  short key;
  *s=0;

  fflush(stdout);
  while (1)
        {
         key=getchar();
         if (key)
            {
   	     	*s=0;
            return(key);
	    		}
         else
            {
             key=getchar();
   	     	 *s=key;
             return(0);
			    }
       	}
}
