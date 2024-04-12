/*
   modulo isreale.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)isreale.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							                                       *
*			Procedura isreale                                           *
*          							                                       *
* 	La procedura rende 1 se la stringa passata contiene un numero     *
*  reale, -1 altrimenti.				 	                              *
*          							                                       *
*********************************************************************/

isreale(valore)

char valore[];

{

short prec,esponente,punto,i;

prec=esponente=punto=0;

if(!strcmp(valore,"'FFFFH'"))
    return(1);

for(i=0;valore[i]!=0x00;i++) {
	switch(valore[i]) {
	case 0x30 :
	case 0x31 :
	case 0x32 :
	case 0x33 :
	case 0x34 :
	case 0x35 :
	case 0x36 :
	case 0x37 :
	case 0x38 :
	case 0x39 :
			prec=0;
			break;
	case 0x2e :
			prec=0;
			if(punto==1)
				return(-1);
			else
				punto=1;
			break;
	case 0x45 :
			if(esponente==1)
				return(-1);
			else {
				esponente=1;
				prec=1;
			}
			break;
	case 0x2b :
	case 0x2d :
			if(i==0 || prec==1)
				prec=0;
 			else
				return(-1);
			break;
	default   :
			return(-1);
			break;
	}  /* case interno */
	}  /* for */
return(1);

}

