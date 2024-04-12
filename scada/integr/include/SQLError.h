/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef _SQLError_h_
#define _SQLError_h_


#define SQLError(stringa)	SQLINTError(stringa,__FILE__,__LINE__)


int SQLINTError(char *, char *, int);

#endif
