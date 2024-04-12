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
   modulo XlResources.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlResources.h	5.1
*/
/*
 *  XlResources.h - 
 */


typedef struct _XlResources{
	char *resource_name;
	char *resource_class;
	char *resource_type;
	size_t resource_size;
	size_t resource_offset;
	char *default_type;
	char *default_addr;
	} XlResources;
	
