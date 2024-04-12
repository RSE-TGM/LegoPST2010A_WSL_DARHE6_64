/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
.386p

;
; macro per la generazione del codice 
;
; ENTRY dei TASK e routine di risposta ad interrupt
;
; le macro vengono chiamate alla fine della definizione degli
; oggetti
;
; Macro TASK_SESSION
; definisce le entry dei task di ricezione e trasmissione
; i task si chiamano _t_rx? e _t_tx? dove ? 
;
; I task non fanno altro che chiamare il modulo net_rxcom
; passando l' indice del canale
;

codicetask      macro i
        public __t_rx&i
__t_rx&i:
        PUSH    i
        call    _net_rxcom

endm

TASK_SESSION macro tot
page
        extrn _net_rxcom:near

_TEXT   segment Public Use32  'CODE'
i=0
        rept tot
        codicetask %i
        i=i+1
        endm

_TEXT   ends

endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

codiceparent macro i
        public  __t_tx&i
__t_tx&i:
        PUSH    i
        call    _net_txcom
endm




TASK_PARENT     macro tot

        extrn _net_txcom:near

_TEXT   segment Public  Use32 'CODE'

i=0
        rept tot
        codiceparent %i
        i=i+1
        endm
_TEXT   ends
endm
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Macro per la generazione degli entry point dei task UDP
;

codiceudp      macro i
        public __t_urx&i
__t_urx&i:
        PUSH    i
        call    _broad_rx

        public __t_utx&i
__t_utx&i:
        PUSH    i
        call    _broad_tx

endm
page


TASK_UDP macro tot
if tot gt 0
        extrn _broad_rx:near
        extrn _broad_tx:near

_TEXT   segment Public Use32 'CODE'
i=0
        rept tot
        codiceudp %i
        i=i+1
        endm

_TEXT   ends
endif
endm


