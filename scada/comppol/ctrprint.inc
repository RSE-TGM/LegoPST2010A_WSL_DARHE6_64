/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* ->CTRPRINT.INC
	Contiene la tabella utilizzata per la decodifica delle 
	parole chiave contenute all'interno della istruzione print
	Ogni record della tabella contiene:
		.parola chiave da individuare 
		.lunghezza della parola chiave 
		.codice	in ascii con cui sostituire la parola nel file
	         intermedio 
		.flag indicante	se la parola chiave deve essere 
		 seguita da [NOME_VARIABILE] (se flag!=0)
*/
#define lun_chiave 6   // lunghezza massima parola chiave ( sovradimensionato
		       // per eventuali nuove parole inseribili
#define lun_codif 5    // lunghezza codifica della parola chiave
typedef struct recprint {char chiave[lun_chiave];   // nome parola chiave
			 short lung;		    // lunghezza
			 char codifica[5];	    // codifica corrispondente
						    // in ASCII
			 short flag;		    // flag:
						    // == 1 ->la parola chiave
						    // deve essere seguita 
						    // da [NOMEVAR].
			 short tipamm[4];	    // vettore contenente i tipi
						    // di variabile ammessi per 
						    // NOMEVAR nella presente 
						    // istruzione (il vettore va 
						    // riempito con i tipi ammissibili
						    // seguiti dal tappo -1).
			}RECPRINT;
/*
	Tabella inizializzata con le parole chiave utilizzate
*/
#define num_chiav 11   // numero di parole chiave utilizzate
/*
	Indici associati alle parole chiave.
*/		   

#define  i_pag 	      0
#define  i_riga       1
#define  i_tim1       2
#define  i_tim2       3
#define  i_cod 	      4
#define  i_desc       5
#define  i_unmis      6
#define  i_org 	      7
#define  i_dl 	      8
#define  i_sgraf      9
#define  i_graf      10

