/**********************************************************************
*
*       C Source:               bitvalue.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 15:29:17 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: bitvalue.c-3 %  (%full_filespec: bitvalue.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> bitvalue
                                                            
	 ritarna il valore di una bit all'interno di una word
     
     Parametri	buffer		word di cui si vuole settare il bit
     			indice		n. del bit da 0 a n
     	                                                            
*/
#if defined OSF1 || defined LINUX

int bitvalue(short * buffer, short indice)
{
   short mask, posiz, bitpos ;

   bitpos=15-indice ;  		/* posizione del bit nella maschera */
   mask=*buffer;
   posiz=1 ;                 	/* ricavo la maschera del bit */
   posiz=posiz << bitpos ;   
   mask=mask & posiz ;       	/* passo il bit voluto */
   mask=(mask==0) ? (0) : (1) ;
   if(mask) return(1);
   else return(0);
}

#endif
