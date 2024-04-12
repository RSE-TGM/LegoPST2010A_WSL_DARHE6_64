/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* wcc_pub.inc

   Questo file di include, inserito all'inizio di ogni modulo,
   evita definizioni multiple di variabili, non risolte dal 
   compilatore WATCOM. 
   La variabile _PUBLIC va definita nei moduli che contengono 
   le definizioni effettive delle variabili, che saranno invece
   extern per gli altri moduli                                   */


#if defined (_PUBLIC)
#define pub
#else
#define pub extern
#endif
