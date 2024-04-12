/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
        Page    60,132
        Title   Struttura Dati Task Input da Periferiche

;-----------------------------------------------------
;	Definizione struttura per area dati task input 
;-----------------------------------------------------

dati_perif      struct

coda_inp    dw  (?)	           ; indice coda caratteri da trasmettere
n_linea	    dw  (?)		   ; numero linea (0 - n)
flg_linea   dw  0                  ; segnalazione stato linea 0=ok 1=ko
m_rx	    db  max_mess dup(?)	   ; buffer per scodare messaggi 

dati_perif	ends
