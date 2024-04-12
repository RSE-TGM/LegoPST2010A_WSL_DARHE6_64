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
	struttura messaggi di comunicazione 
*/

#include "defpub.h"

#define SIS_A 0
#define SIS_B 1
#define MASTER 1
#define OFF 0
#define ON 1
#define SLAVE  0

typedef struct mes386 {int tipomess;
			      } MES_386;			                            



typedef struct rxstato386 {int tipomess;
			   unsigned char status; 
			   unsigned char rete;
			   char rel_propria[4];
			   char rel_duale[4];
			} RX_STATO386;

// maschere per test byte di status

#define MASK_IDEN 	 0x40
#define MASK_MASTER 	 0x80
#define MASK_WDDUALE 	 0x10
				
