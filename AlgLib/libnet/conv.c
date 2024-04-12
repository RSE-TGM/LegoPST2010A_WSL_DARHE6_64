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
static char SccsID[] = "@(#)conv.c	5.1\t11/7/95";
/*
   modulo conv.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)conv.c	5.1
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "libnet.h"


/* In questo modulo sono contenute delle routine di conversione fra i
formati float e interi fra le seguenti macchine:

	DEC Station (IEEE) (ULTRIX - OSF1)
	AIX 	    (IEEE)
	VAX Station (F_FLOAT)
        Motorola 68030 (IEEE)

N.B. le DEC Station e le Vax Station hanno lo stesso formato interno
degli int */

/* definizioni interne */

struct vax_float_st{
        unsigned significant_2 : 16;
        unsigned sign : 1;
        unsigned exp : 8;
        unsigned significant_1 : 7;
        };
typedef struct vax_float_st VAX_FLOAT;

struct ieee_float_st{
        unsigned sign : 1;
        unsigned exp : 8;
        unsigned significant_1 : 7;
        unsigned significant_2 : 16;
        };

typedef struct ieee_float_st IEEE_FLOAT;

/* conversione dei float fra DEC Station e VAX Station  */

void utov_float(p_vf,p_ie)
char *p_vf;
char *p_ie;
{
VAX_FLOAT vf;
IEEE_FLOAT ie;
char ddd[4];

float qq=0;

if(memcmp(p_ie,&qq,sizeof(float)))
	{
        memcpy(&ie,p_ie,sizeof(float));
        vf.significant_1=ie.significant_1;
        vf.significant_2=ie.significant_2;
        vf.sign=ie.sign;
        vf.exp=ie.exp;
        memcpy(ddd,&vf,sizeof(float));
        ++ddd[1];
        memcpy(p_vf,ddd,sizeof(float));
	}
else
	memcpy(p_vf,p_ie,sizeof(float));
	
}



/* conversione dei float fra VAX Station e DEC Station  */

void vtou_float(p_ie,p_vf)
char *p_ie;
char *p_vf;
{
VAX_FLOAT vf;
IEEE_FLOAT ie;
char ddd[4];
float qq=0;

if(memcmp(p_vf,&qq,sizeof(float)))
	{
        memcpy(ddd,p_vf,sizeof(float));
        --ddd[1];
        memcpy(&vf,ddd,sizeof(float));
        ie.significant_1=vf.significant_1;
        ie.significant_2=vf.significant_2;
        ie.sign=vf.sign;
        ie.exp=vf.exp;
        memcpy(p_ie,&ie,sizeof(float));
	}
else
	memcpy(p_ie,p_vf,sizeof(float));
}

void atou_float(p_u,p_a)
char *p_u;
char *p_a;
{
char a[4];
char b[4];

	memcpy(a,p_a,sizeof(float));
	b[0]=a[3];
	b[1]=a[2];
	b[2]=a[1];
	b[3]=a[0];
	memcpy(p_u,b,sizeof(float));
}

void mtou_float(p_u,p_a)
char *p_u;
char *p_a;
{
char a[4];
char b[4];

   memcpy(a,p_a,sizeof(float));
   b[0]=a[3];
   b[1]=a[2];
   b[2]=a[1];
   b[3]=a[0];
   memcpy(p_u,b,sizeof(float));
}

void atou_int(p_u,p_a)
char *p_u;
char *p_a;
{
char a[4];
char b[4];

        memcpy(a,p_a,sizeof(int));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_u,b,sizeof(int));
}

void mtou_int(p_u,p_a)
char *p_u;
char *p_a;
{
char a[4];
char b[4];

        memcpy(a,p_a,sizeof(int));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_u,b,sizeof(int));
}

void atou_short(p_u,p_a)
char *p_u;
char *p_a;
{
char a[2];
char b[2];

        memcpy(a,p_a,sizeof(short));
        b[0]=a[1];
        b[1]=a[0];
        memcpy(p_u,b,sizeof(short));
}

void mtou_short(p_u,p_a)
char *p_u;
char *p_a;
{
char a[2];
char b[2];

        memcpy(a,p_a,sizeof(short));
        b[0]=a[1];
        b[1]=a[0];
        memcpy(p_u,b,sizeof(short));
}

void utoa_float(p_a,p_u)
char *p_a;
char *p_u;
{
char a[4];
char b[4];

        memcpy(a,p_u,sizeof(float));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_a,b,sizeof(float));
                                      
}

void utom_float(p_a,p_u)
char *p_a;
char *p_u;
{
char a[4];
char b[4];

        memcpy(a,p_u,sizeof(float));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_a,b,sizeof(float));

}

void utoa_int(p_a,p_u)
char *p_a;
char *p_u;
{
char a[4];
char b[4];

        memcpy(a,p_u,sizeof(int));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_a,b,sizeof(int));
}

void utom_int(p_a,p_u)
char *p_a;
char *p_u;
{
char a[4];
char b[4];

        memcpy(a,p_u,sizeof(int));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_a,b,sizeof(int));
}

void utoa_short(p_a,p_u)
char *p_a;
char *p_u;
{
char a[2];
char b[2];

        memcpy(a,p_u,sizeof(short));
        b[0]=a[1];
        b[1]=a[0];
        memcpy(p_a,b,sizeof(short));
}

void utom_short(p_a,p_u)
char *p_a;
char *p_u;
{
char a[2];
char b[2];

        memcpy(a,p_u,sizeof(short));
        b[0]=a[1];
        b[1]=a[0];
        memcpy(p_a,b,sizeof(short));
}


void atov_float(p_v,p_a)
char *p_v;
char *p_a;
{
char a[4];
char b[4];

	memcpy(a,p_a,sizeof(float));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
	utov_float(p_v,b);
}
void mtov_float(p_v,p_a)
char *p_v;
char *p_a;
{
char a[4];
char b[4];
float *ppp;

   memcpy(a,p_a,sizeof(float));
/*
(char *)ppp = a;

printf (" dato = %10.3E",*ppp);
*/
        b[0]=a[1];
        b[1]=a[0];
        b[2]=a[3];
        b[3]=a[2];
        ++b[1];
   memcpy(p_v,b,sizeof(float));
/*
(char *)ppp = p_v;

printf ("conv ... %8x\n",*ppp);
*/
}

void atov_int(p_v,p_a)
char *p_v;
char *p_a;
{
char a[4];
char b[4];

        memcpy(a,p_a,sizeof(int));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_v,b,sizeof(int));
}

void atov_short(p_v,p_a)
char *p_v;
char *p_a;
{
char a[2];
char b[2];

        memcpy(a,p_a,sizeof(short));
        b[0]=a[1];
        b[1]=a[0];
        memcpy(p_v,b,sizeof(short));
}

void vtoa_float(p_a,p_v)
char *p_a;
char *p_v;
{
char a[4];
char b[4];

	vtou_float(a,p_v);
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
	memcpy(p_a,b,sizeof(float));
}

void vtom_float(p_a,p_v)
char *p_a;
char *p_v;
{
char a[4];
char b[4];

   memcpy (a,p_v,sizeof(float));
        --a[1];
        b[0]=a[1];
        b[1]=a[0];
        b[2]=a[3];
        b[3]=a[2];
   memcpy(p_a,b,sizeof(float));
}

void vtoa_int(p_a,p_v)
char *p_a;
char *p_v;
{
char a[4];
char b[4];

        memcpy(a,p_v,sizeof(int));
        b[0]=a[3];
        b[1]=a[2];
        b[2]=a[1];
        b[3]=a[0];
        memcpy(p_a,b,sizeof(int));
}

void vtoa_short(p_a,p_v)
char *p_a;
char *p_v;
{
char a[2];
char b[2];

        memcpy(a,p_v,sizeof(short));
        b[0]=a[1];
        b[1]=a[0];
        memcpy(p_a,b,sizeof(short));
}

float *converti_float(dato,flag)
float *dato;
int flag;
{
static int formato_dati;
static int prima_volta=1;
static float *out;
static float *inp;


if(prima_volta)
	{
	/* caricamento variabili di enviroment */
	formato_dati=atoi((char *)getenv("FORMATO_DATI"));
	prima_volta=0;
	out=(float*)malloc(sizeof(float));
	}


switch(formato_dati){
		case(AIX_AIX):		
			{
			memcpy(out,dato,sizeof(float));
			break;
			}
		case(AIX_ULTRIX):	
			{
			if(flag==TRASMISSIONE)
				atou_float((char*)out,(char*)dato);
			else
				utoa_float((char*)out,(char*)dato);
			break;
			}
      case(M68000_ULTRIX):
         {
         if(flag==TRASMISSIONE)
            mtou_float((char*)out,(char*)dato);
         else
            utom_float((char*)out,(char*)dato);
         break;
         }
      case(ULTRIX_M68000):
         {
         if(flag==TRASMISSIONE)
            utom_float((char*)out,(char*)dato);
         else
            mtou_float((char*)out,(char*)dato);
         break;
         }
		case(AIX_VMS):		
			{
			if(flag==TRASMISSIONE)
				atov_float((char*)out,(char*)dato);
			else
				vtoa_float((char*)out,(char*)dato);
			break;
			}
      case(M68000_VMS):
         {
         if(flag==TRASMISSIONE)
            mtov_float((char*)out,(char*)inp);
         else
            vtom_float((char*)out,(char*)inp);
         break;
         }
      case(VMS_M68000):
         {
         if(flag==TRASMISSIONE)
            vtom_float((char*)out,(char*)inp);
         else
            mtov_float((char*)out,(char*)inp);
         break;
         }
      case(M68000_M68000):
         {
         memcpy(out,dato,sizeof(float));
         break;
         }
		case(ULTRIX_AIX):	
			{
			if(flag==TRASMISSIONE)
				utoa_float((char*)out,(char*)dato);
			else
				atou_float((char*)out,(char*)dato);
			break;
			}
		case(ULTRIX_ULTRIX):	
			{
			memcpy(out,dato,sizeof(float));
			break;
			}
		case(ULTRIX_VMS):	
			{
			if(flag==TRASMISSIONE)
				utov_float((char*)out,(char*)dato);
			else
				vtou_float((char*)out,(char*)dato);
			break;
			}
		case(VMS_AIX):		
			{
			if(flag==TRASMISSIONE)
				vtoa_float((char*)out,(char*)dato);
			else
				atov_float((char*)out,(char*)dato);
			break;
			}
		case(VMS_ULTRIX):	
			{
			if(flag==TRASMISSIONE)
				vtou_float((char*)out,(char*)dato);
			else
				utov_float((char*)out,(char*)dato);
			break;
			}
		case(VMS_VMS):	
			{
			memcpy(out,dato,sizeof(float));
			break;
			}
		}
return(out);
}

int *converti_int(dato,flag)
int *dato;
int flag;
{
static int formato_dati;
static int prima_volta=1;
static int *out;
static int *inp;



if(prima_volta)
	{
	/* caricamento variabili di enviroment */
	formato_dati=atoi((char *)getenv("FORMATO_DATI"));
	prima_volta=0;
	out=(int*)malloc(sizeof(int));
	}


switch(formato_dati){
                case(AIX_AIX):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(AIX_ULTRIX):
                        {
			if(flag==TRASMISSIONE)
                        	atou_int((char*)out,(char*)dato);
			else
                        	utoa_int((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_ULTRIX):
                        {
					         if(flag==TRASMISSIONE)
                           mtou_int((char*)out,(char*)dato);
 		       	         else
                           utom_int((char*)out,(char*)dato);
                        break;
                        }
                case(ULTRIX_M68000):
                        {
         					if(flag==TRASMISSIONE)
                           utom_int((char*)out,(char*)dato);
         					else
                           mtou_int((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_M68000):
                        {
         					memcpy(out,dato,sizeof(int));
                        break;
                        }

                case(AIX_VMS):
                        {
			if(flag==TRASMISSIONE)
                        	atov_int((char*)out,(char*)dato);
			else
                        	vtoa_int((char*)out,(char*)dato);
                        break;
                        }
                case(ULTRIX_AIX):
                        {
			if(flag==TRASMISSIONE)
                        	utoa_int((char*)out,(char*)dato);
			else
                        	atou_int((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_VMS):
                        {
         if(flag==TRASMISSIONE)
                           atov_int((char*)out,(char*)inp);
         else
                           vtoa_int((char*)out,(char*)inp);
                        break;
                        }
                case(VMS_M68000):
                        {
         if(flag==TRASMISSIONE)
                           vtoa_int((char*)out,(char*)inp);
         else
                           atov_int((char*)out,(char*)inp);
                        break;
                        }
                case(ULTRIX_ULTRIX):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(ULTRIX_VMS):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(VMS_AIX):
                        {
			if(flag==TRASMISSIONE)
                        	vtoa_int((char*)out,(char*)dato);
			else
                        	atov_int((char*)out,(char*)dato);
                        break;
                        }
                case(VMS_ULTRIX):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(VMS_VMS):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                }
return(out);
}

short *converti_short(dato,flag)
short *dato;
int flag;
{
static int formato_dati;
static int prima_volta=1;
static short *out;
static short *inp;



if(prima_volta)
        {
        /* caricamento variabili di enviroment */
        formato_dati=atoi((char *)getenv("FORMATO_DATI"));
        prima_volta=0;
	out=(short*)malloc(sizeof(short));
        }


switch(formato_dati){
                case(AIX_AIX):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(AIX_ULTRIX):
                        {
                        if(flag==TRASMISSIONE)
                                atou_short((char*)out,(char*)dato);
                        else
                                utoa_short((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_ULTRIX):
                        {
                        if(flag==TRASMISSIONE)
                                mtou_short((char*)out,(char*)dato);
                        else
                                utom_short((char*)out,(char*)dato);
                        break;
                        }
                case(ULTRIX_M68000):
                        {
                        if(flag==TRASMISSIONE)
                                utom_short((char*)out,(char*)dato);
                        else
                                mtou_short((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_M68000):
                        {
         					memcpy(out,dato,sizeof(short));
                        break;
                        }

                case(AIX_VMS):
                        {
                        if(flag==TRASMISSIONE)
                                atov_short((char*)out,(char*)dato);
                        else
                                vtoa_short((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_VMS):
                        {
                        if(flag==TRASMISSIONE)
                                atov_short((char*)out,(char*)inp);
                        else
                                vtoa_short((char*)out,(char*)inp);
                        break;
                        }
                case(VMS_M68000):
                        {
                        if(flag==TRASMISSIONE)
                                vtoa_short((char*)out,(char*)inp);
                        else
                                atov_short((char*)out,(char*)inp);
                        break;
                        }
                case(ULTRIX_AIX):
                        {
                        if(flag==TRASMISSIONE)
                                utoa_short((char*)out,(char*)dato);
                        else
                                atou_short((char*)out,(char*)dato);
                        break;
                        }
                case(ULTRIX_ULTRIX):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(ULTRIX_VMS):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(VMS_AIX):
                        {
                        if(flag==TRASMISSIONE)
                                vtoa_short((char*)out,(char*)dato);
                        else
                                atov_short((char*)out,(char*)dato);
                        break;
                        }
                case(VMS_ULTRIX):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(VMS_VMS):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                }
return(out);
}

float *converti_float_f(dato,flag,formato_dati)
float *dato;
int flag;
int formato_dati;
{
static float *out=NULL;
static float *inp;

if(out==NULL)
	out=(float*)malloc(sizeof(float));



switch(formato_dati){
		case(AIX_AIX):		
			{
			memcpy(out,dato,sizeof(float));
			break;
			}
		case(AIX_ULTRIX):	
			{
			if(flag==TRASMISSIONE)
				atou_float(out,dato);
			else
				utoa_float(out,dato);
			break;
			}
		case(AIX_VMS):		
			{
			if(flag==TRASMISSIONE)
				atov_float(out,dato);
			else
				vtoa_float(out,dato);
			break;
			}
		case(ULTRIX_AIX):	
			{
			if(flag==TRASMISSIONE)
				utoa_float(out,dato);
			else
				atou_float(out,dato);
			break;
			}
      case(M68000_ULTRIX):
         {
         if(flag==TRASMISSIONE)
            mtou_float((char*)out,(char*)dato);
         else
            utom_float((char*)out,(char*)dato);
         break;
         }
      case(ULTRIX_M68000):
         {
         if(flag==TRASMISSIONE)
            utom_float((char*)out,(char*)dato);
         else
            mtou_float((char*)out,(char*)dato);
         break;
         }
      case(M68000_M68000):
         {
         memcpy(out,dato,sizeof(float));
         break;
         }
		case(ULTRIX_ULTRIX):	
			{
			memcpy(out,dato,sizeof(float));
			break;
			}
		case(ULTRIX_VMS):	
			{
			if(flag==TRASMISSIONE)
				utov_float(out,dato);
			else
				vtou_float(out,dato);
			break;
			}
		case(VMS_AIX):		
			{
			if(flag==TRASMISSIONE)
				vtoa_float(out,dato);
			else
				atov_float(out,dato);
			break;
			}
		case(VMS_ULTRIX):	
			{
			if(flag==TRASMISSIONE)
				vtou_float(out,dato);
			else
				utov_float(out,dato);
			break;
			}
		case(VMS_VMS):	
			{
			memcpy(out,dato,sizeof(float));
			break;
			}
      case(M68000_VMS):
         {
         if(flag==TRASMISSIONE)
            mtov_float((char*)out,(char*)inp);
         else
            vtom_float((char*)out,(char*)inp);
         break;
         }
		}
return(out);
}

int *converti_int_f(dato,flag,formato_dati)
int *dato;
int flag;
int formato_dati;
{
static int *out=NULL;
static int *inp=NULL;

if(out==NULL)
	out=(int*)malloc(sizeof(int));



switch(formato_dati){
                case(AIX_AIX):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(AIX_ULTRIX):
                        {
			if(flag==TRASMISSIONE)
                        	atou_int(out,dato);
			else
                        	utoa_int(out,dato);
                        break;
                        }
                case(AIX_VMS):
                        {
			if(flag==TRASMISSIONE)
                        	atov_int(out,dato);
			else
                        	vtoa_int(out,dato);
                        break;
                        }
                case(M68000_ULTRIX):
                        {
                        if(flag==TRASMISSIONE)
                           mtou_int((char*)out,(char*)dato);
                        else
                           utom_int((char*)out,(char*)dato);
                        break;
                        }
                case(ULTRIX_M68000):
                        {
                        if(flag==TRASMISSIONE)
                           utom_int((char*)out,(char*)dato);
                        else
                           mtou_int((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_M68000):
                        {
         					memcpy(out,dato,sizeof(int));
                        break;
                        }

                case(ULTRIX_AIX):
                        {
			if(flag==TRASMISSIONE)
                        	utoa_int(out,dato);
			else
                        	atou_int(out,dato);
                        break;
                        }
                case(ULTRIX_ULTRIX):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(ULTRIX_VMS):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(VMS_AIX):
                        {
			if(flag==TRASMISSIONE)
                        	vtoa_int(out,dato);
			else
                        	atov_int(out,dato);
                        break;
                        }
                case(VMS_ULTRIX):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(VMS_VMS):
                        {
			memcpy(out,dato,sizeof(int));
                        break;
                        }
                case(M68000_VMS):
                        {
         if(flag==TRASMISSIONE)
                           atov_int((char*)out,(char*)inp);
         else
                           vtoa_int((char*)out,(char*)inp);
                        break;
                        }
                }
return(out);
}

short *converti_short_f(dato,flag,formato_dati)
short *dato;
int flag;
int formato_dati;
{
static short *out=NULL;
static short *inp;

if(out==NULL)
	out=(short*)malloc(sizeof(short));




switch(formato_dati){
                case(AIX_AIX):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(AIX_ULTRIX):
                        {
                        if(flag==TRASMISSIONE)
                                atou_short(out,dato);
                        else
                                utoa_short(out,dato);
                        break;
                        }
                case(M68000_ULTRIX):
                        {
                        if(flag==TRASMISSIONE)
                                mtou_short((char*)out,(char*)dato);
                        else
                                utom_short((char*)out,(char*)dato);
                        break;
                        }
                case(ULTRIX_M68000):
                        {
                        if(flag==TRASMISSIONE)
                                utom_short((char*)out,(char*)dato);
                        else
                                mtou_short((char*)out,(char*)dato);
                        break;
                        }
                case(M68000_M68000):
                        {
         					memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(AIX_VMS):
                        {
                        if(flag==TRASMISSIONE)
                                atov_short(out,dato);
                        else
                                vtoa_short(out,dato);
                        break;
                        }
                case(ULTRIX_AIX):
                        {
                        if(flag==TRASMISSIONE)
                                utoa_short(out,dato);
                        else
                                atou_short(out,dato);
                        break;
                        }
                case(ULTRIX_ULTRIX):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(ULTRIX_VMS):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(VMS_AIX):
                        {
                        if(flag==TRASMISSIONE)
                                vtoa_short(out,dato);
                        else
                                atov_short(out,dato);
                        break;
                        }
                case(VMS_ULTRIX):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(VMS_VMS):
                        {
			memcpy(out,dato,sizeof(short));
                        break;
                        }
                case(M68000_VMS):
                        {
                        if(flag==TRASMISSIONE)
                                atov_short((char*)out,(char*)inp);
                        else
                                vtoa_short((char*)out,(char*)inp);
                        break;
                        }
                }
return(out);
}
