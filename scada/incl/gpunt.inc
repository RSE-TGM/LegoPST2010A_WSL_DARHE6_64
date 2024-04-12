/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*      file gpunt.inc
        definizione della struttura del puntatore in data
        base
*/
typedef struct s_punt  { char tipo ;   		// tipo di data base
                         char ext ;	        // in caso di soglie di allarmi 
						// e' il tipo di soglia
                        short point ; } S_PUNT ;

