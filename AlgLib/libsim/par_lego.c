/**********************************************************************
*
*       C Source:               par_lego.c
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 12:13:03 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: par_lego.c-3 %  (%full_filespec: par_lego.c-3:csrc:3 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)par_lego.c	5.1\t11/10/95";
/*
   modulo par_lego.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)par_lego.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <Rt/RtMemory.h>

#define DEF_N000  	55
#define DEF_N001	DEF_N000*10
#define DEF_N002	DEF_N000*25
#define DEF_N003	DEF_N000*60
#define DEF_N004	DEF_N000*25
#define DEF_N005	DEF_N000*100
#define DEF_N007	DEF_N000*500
#define DEF_M001	DEF_N005-DEF_N003
#define DEF_M002	DEF_M001-DEF_N004
#define DEF_M003	DEF_N002+1
#define DEF_M004	DEF_N003+1
#define DEF_M005	DEF_N004+1


int _N000 = DEF_N000;
int _N001 = DEF_N001;
int _N002 = DEF_N002;
int _N003 = DEF_N003;
int _N004 = DEF_N004;
int _N005 = DEF_N005;
int _N007 = DEF_N007;
int _M001 = DEF_M001;
int _M002 = DEF_M002;
int _M003 = DEF_M003;
int _M004 = DEF_M004;
int _M005 = DEF_M005;

int GetParLego()
{
char * val;

/*
	N000
*/
val = getenv("N000");

// printf("GetParLego: N000 = %s\n",val);

if(val == NULL) return(0); /* errore getenv() */
_N000=atoi(val);

/*
	N001
*/
val = getenv("N001");

// printf("GetParLego: N001 = %s\n",val);

if(val == NULL) return(0); /* errore getenv() */
_N001=atoi(val);

/*
	N002
*/
val = getenv("N002");
if(val == NULL) return(0); /* errore getenv() */
_N002=atoi(val);

/*
	N003
*/
val = getenv("N003");

// printf("GetParLego: N003 = %s\n",val);

if(val == NULL) return(0); /* errore getenv() */
_N003=atoi(val);

/*
	N004
*/
val = getenv("N004");
if(val == NULL) return(0); /* errore getenv() */
_N004=atoi(val);

/*
	N005
*/
val = getenv("N005");
if(val == NULL) return(0); /* errore getenv() */
_N005=atoi(val);

/*
	N007
*/
val = getenv("N007");
if(val == NULL) return(0); /* errore getenv() */
_N007=atoi(val);

/*
	M001
*/
val = getenv("M001");

// printf("GetParLego: M001 = %s\n",val);

if(val == NULL) return(0); /* errore getenv() */
_M001=atoi(val);

/*
	M002
*/
val = getenv("M002");
if(val == NULL) return(0); /* errore getenv() */
_M002=atoi(val);

/*
	M003
*/
val = getenv("M003");
if(val == NULL) return(0); /* errore getenv() */
_M003=atoi(val);

/*
	M004
*/
val = getenv("M004");
if(val == NULL) return(0); /* errore getenv() */
_M004=atoi(val);

/*
	M005
*/
val = getenv("M005");

// printf("GetParLego: M005 = %s\n",val);

if(val == NULL) return(0); /* errore getenv() */

// printf("GetParLego: dopo test M005 = %s\n",val);

_M005=atoi(val);

// printf("GetParLego:  dopo atoi M005 = %s\n",val);

// printf("N000     %d\n",_N000);
// printf("N001     %d\n",_N001);
// printf("N002     %d\n",_N002);
// printf("N003     %d\n",_N003);
// printf("N004     %d\n",_N004);
// printf("N005     %d\n",_N005);
// printf("N007     %d\n",_N007);
// printf("M001     %d\n",_M001);
// printf("M002     %d\n",_M002);
// printf("M003     %d\n",_M003);
// printf("M004     %d\n",_M004);
// printf("M005     %d\n",_M005);


return(1); /* ritorno corretto */
}

char **cdim2(row,col)
int row,col;
{
	int i;
	register char **prow, *pdata;

	pdata = (char *) calloc(row*col,sizeof(char));
	if(pdata == (char *) NULL)
		{
		fprintf(stderr,"No heap space for data\n");
		return(NULL);
		}
	prow = (char **) calloc(row,sizeof(char *));

	if(prow == (char **) NULL)
		{
		fprintf(stderr,"No heap space for data\n");
		return(NULL);
		}
	for(i=0; i< row; i++)
		{
		prow[i] = pdata;
		pdata += col;
		}
	return(prow);
}

void cfree2(pa)
char **pa;
{
	
	free(*pa);
	free(pa);
}

int **idim2(row,col)
int row,col;
{
	int i;
	register int **prow, *pdata;

	pdata = (int *) calloc(row*col,sizeof(int));
	if(pdata == (int *) NULL)
		{
		fprintf(stderr,"No heap space for data\n");
		return(NULL);
		}
	prow = (int **) calloc(row,sizeof(int *));

	if(prow == (int **) NULL)
		{
		fprintf(stderr,"No heap space for data\n");
		return(NULL);
		}
	for(i=0; i< row; i++)
		{
		prow[i] = pdata;
		pdata += col;
		}
	return(prow);
}

void ifree2(pa)
int **pa;
{
	
	free(*pa);
	free(pa);
}
