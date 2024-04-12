/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* -> TABARC.INC 
 *       Contiene le tabelle di decodifica tra ascii e valori per il 
 *       descrittore archivi.
 */

FREQUEN tabfreq[n_freq]={	  // tabella decodifica frequenze
		   "01S",1L,
		   "05S",5L,
		   "15S",15L,
		   "30S",30L,
		   "01M",60L,
		   "30M",1800L,
		   "01H",3600L,
		   "04H",14400L,
		   "08H",28800L,
		   "24H",86400L,
		   };


NUMCAMP num_camp[combin]={	  // tabella decodifica durata campionamento
		   "01S","15M", 900,
		   "05S","02H",1440,
		   "15S","06H",1440,
		   "30S","12H",1440,
		   "01M","12H", 720,
		   "01M","01G",1440,
		   "30M","12H",  24,
		   "30M","01G",  48,
		   "30M","07G", 336,
		   "30M","01M",1488,
		   "01H","01G",  24,
		   "01H","07G", 168,
		   "01H","01M", 744,
		   "01H","02M",1488,
		   "04H","01G",   6,
		   "04H","07G",  42,
		   "04H","01M", 186,
		   "04H","08M",1488,
		   "08H","07G",  21,
		   "08H","01M",  93,
		   "08H","01A",1116,
		   "24H","01M",  31,
		   "24H","01A", 365,
		   "24H","04A",1461,
		   };

char    tabtipo[]={ 0,		  // tabella decodifica tipo
                   'C',
		   'L',
		   'E',
		  };


char *tabflag[n_flag]={"HS",	  // tabella decodifica flags
	               "LS",
		       "HC",
		       "LC",
                       "FS",
		       "FA",
		       "FZ",
		       "SL",
			};
