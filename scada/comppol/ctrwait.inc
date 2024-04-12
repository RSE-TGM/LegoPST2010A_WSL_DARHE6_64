/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* -> CTRWAIT.INC

File contenente la definizione dei vettori di terminatori e di tipi 
ammessi nella analisi sintattica istruzione WAIT

*/

/* Vettore dei terminatori lista argomenti istruzione WAIT */

char vterwait[] = {VIRGOLA,CHTONDA};

/* Vettore tipi ammissibili argomento time out istruzione WAIT */

short vttiou[] = {tintero,-1};

/* Vettore tipi ammissibili argomenti trigger  istruzione WAIT */

short vttrig[] = {tpuntan,tpuntdi,tpuntor,-1};
