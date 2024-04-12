/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef _RtMemory_h_
#define _RtMemory_h_
#include <stdlib.h>
#include <Rt/Rt.h>
#if defined DEBUG_MALLOC
#ifndef DESIGN_TIME /* per AIC */


void *RtMalloc(size_t,char *,int);
void *RtCalloc(size_t,size_t,char *,int);
void *RtRealloc(void *,size_t,char *,int);
void  RtFree(void *,char *, int);
char *  RtNewString(char *,char *,int);
size_t RtMemoryAllocated(void *);
Boolean RtCheckPointer(void *);
void * RtIntRecord(void *, char *, int);

/*
	ridefinizione delle chiamate 
*/
#define RtRecord(punt)  RtIntRecord(punt,__FILE__,__LINE__)
#define malloc(size)	RtMalloc(size,__FILE__,__LINE__)
#define free(punt)	RtFree(punt,__FILE__,__LINE__)
#define realloc(punt,size)	RtRealloc(punt,size,__FILE__,__LINE__)
#define calloc(num_elet,size_ele)	RtCalloc(num_elet,size_ele,__FILE__,__LINE__)

#define XtMalloc(size)	RtMalloc(size,__FILE__,__LINE__)
#define XtFree(punt)	RtFree(punt,__FILE__,__LINE__)
#define XtRealloc(punt,size)	RtRealloc(punt,size,__FILE__,__LINE__)
#define XtCalloc(num_elet,size_ele)	RtCalloc(num_elet,size_ele,__FILE__,__LINE__)
#define XtNewString(stringa)	RtNewString(stringa,__FILE__,__LINE__)


#endif
#endif
#endif
