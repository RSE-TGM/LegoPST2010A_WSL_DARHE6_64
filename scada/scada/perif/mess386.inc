/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
;***
;message.inc - parametri per moduli di scambio messaggi
;
;Scopo:
;
;	definizione dei simboli usati nella configurazione dei
;	moduli di scambio messaggi 
;
;	definizione strutture dati per scambio mesaggi
;
;Storia delle revisioni:
;
;*******************************************************************************

ERSV_TO 	equ	3		;errore di time out in attesa 
ERSV_SP		equ	5		;errore	in accodamento
ERSV_FU		equ	7		;errore di coda piena
ERSV_EM		equ	9		;errore di coda vuota


QMK_NOWAIT	equ	0		;maskera test flag senza attesa
QMK_WAIT	equ	0001H		;maskera test flag richiesta attesa
QMK_CYC		equ	0002H		;maskera test flag coda ciclica


;-----------------------------------------------------------------------------
; queue packet
;-----------------------------------------------------------------------------
q_packet	struc
qp_que		dw	?	;indice coda 
qp_flg		dw	?	;flag
qp_lmsg		dw	?	;lunghezza messaggio (byte)
qp_amsg		dd	?	;indirizzo messaggio
qp_wto		dw	?	;time-out per attesa per coda piena (enquque) o vuota (dequque)
q_packet	ends

qp_len		equ	size q_packet	;lunghezza in byte


;-----------------------------------------------------------------------------
;descrittore code
;-----------------------------------------------------------------------------
que_des struc
qd_ind		DD      ?	;OFFSET INDBUF IN DESCRITTORE
qd_fin		DD 	?	;        INDFIN
qd_pin		DD 	?	; 	 POINTIN
qd_pou		DD 	?	;	 POINTOUT
qd_occ		DD	?	;        INDOCC
qd_pas		DW 	?	;	 PASSO
qd_full		DW	?	; Mail box di attesa per coda piena
qd_empt		DW	?	; Mail box di attesa per coda vuota
qd_accod	db	?	;contatore di accodamenti in corso
qd_scod		db	?	;conatatore di scodamenti in corso
qd_spare	db	4 dup(?)
que_des ends

qd_eentry	equ	5	;logaritmo in base 2 della lunghezza per shl
qd_len	equ	size que_des	;lunghezza in byte

QPACK   typedef         q_packet
