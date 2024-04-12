/**********************************************************************
*
*	C Source:		trapfpe.c
*	Instance:		1
*	Description:	
*	%created_by:	lomgr %
*	%date_created:	Wed Mar 23 12:25:02 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: trapfpe.c-1 %  (%full_filespec: trapfpe.c-1:csrc:1 %)";
#endif

#define _GNU_SOURCE 1
#include <fenv.h>
static void __attribute__ ((constructor))
trapfpe ()
{
  /* Enable some exceptions.  At startup all exceptions are masked.  */

  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
}

