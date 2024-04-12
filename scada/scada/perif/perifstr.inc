/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
;       ------------------------------------------------------------------
;       
;       File di configurazione delle schede di comunicazione seriale
;       Contiene la definizione degli indirizzi e delle strutture
;       ------------------------------------------------------------------

        include  perifmcr.inc
;
;       device ammessi 
;       ---------------
ty_key  equ     0
ty_prn  equ     1
ty_clk  equ     2
ty_lpt  equ     3
;
;	struttura messaggio da trasmettere
;
tras	struc

	lung	        dw	?
	ty_board        db	?
	lineas	        db	?
tras	ends
;
;	dimensione massima messaggio da trasmettere
;
max_mess 	equ	256	        ;n. bytes max rx da code verso out
;
;	indice svincolo digitale di diagnostica
;
indpri	        equ	13		; indice allarme printer 1 .. fino a 4
;
;	messaggio segnalazione diagnostica linea
;        
sdia	struc	

	lng	dw	?
	indic	db	?
	spa	db	1
	cond	dw	?
sdia	ends
