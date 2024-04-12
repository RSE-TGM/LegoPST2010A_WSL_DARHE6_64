/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* -> CTRFREWR.INC

File contenente la definizione dei vettori di terminatori e di tipi 
ammessi nella analisi sintattica istruzione FREAD/FWRITE

*/

/* Vettore dei terminatori lista argomenti istruzioni FREAD/FWRITE */

char vterfrewr[] = {VIRGOLA,CHTONDA};

/* Vettore tipi ammissibili argomenti file e rec. id istruz. FREAD/FWRITE */

short vtfrwid[] = {tintero,-1};

/* Vettore tipi ammissibili argomenti istruzioni FREAD/FWRITE */

short vtfrwls[] = {tanalogico,tdigitale,torgano,treale,tintero,tlogico,
                   tstringa,tpuntan,tpuntdi,tpuntor,tpuntst,tpuntcom,-1};

