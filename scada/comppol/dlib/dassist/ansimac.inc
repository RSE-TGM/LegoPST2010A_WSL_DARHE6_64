/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* ->ANSIMAC.C 
 *	contiene le macro che utilizzano il drive  ANSI	per la gestione 
 * 	dello schermo
 */
#define XY(x,y)	cprintf("\033[%d;%dH",y,x) 
#define SETATTR(attr)  cprintf("\033[%dm",attr)
#define ERASEL(y,xin,xfin) XY(xfin,y);while(xfin-xin+1){putchar(' ');XY(--xfin,y);} XY(xin,y)   
#define ERASE  cprintf("\033[2J")   
#define SETATTR(attr)  cprintf("\033[%dm",attr)
