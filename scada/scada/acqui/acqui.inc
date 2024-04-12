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
        acqui.inc

        Il file contiene le strutture di tutti i dati utilizzati
        dal task di acquisizione (vedi acqui.c)

        24 Feb. 1992    Rel. 0.01       Fc
*/

#include "defpub.h"
/*
        dati per trasferimento file da config
*/
pub union u_tlink	{	
		  TXTESTA_FILE_ETH tfile;
		  TXDATI_FILE_ETH  dfile;
		  TXFINE_FILE_ETH  ffile;
		 };
pub struct s_tlink	{ 
        	  short addr_nodo;
		  union u_tlink t ;};
/*
        messaggi da acquisizione
*/
typedef union messaggi_acqui {
#if defined (AC_INETDUALE)
		  	S_STRETE m_rete ;
			S_VARETE m_varete;
		        struct   s_tlink s;
			short 	 mmi[500];
#endif
#if defined (STAR_SDI)                     // comunicazione con star tipo sdi
                        S_MSTCFG rev;
#endif
		        char	 buff[1100]; // dimensionato per 180 analogici
			S_DANA   m_dana ;
			S_DDIG   m_ddig ;
			S_MDCOM  m_com  ; 
			S_DANAT   m_danat ;     // dati analogici
			S_DDIGT   m_ddigt ;     // dati digitali
                        S_DANAVET m_vett;       // dati analogici vettoriali
                                } U_MESS;
/*
        struttura messaggi con header per invio al sistema
        slave
*/
pub struct s_mess {
			short  mess;
  			U_MESS u; } ac;

