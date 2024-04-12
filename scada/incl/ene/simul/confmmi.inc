/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
;
;       Confmmi.inc
;       contiene la configurazione del sistema Enel Simulatore CRA
;
;
include confdef.inc
.list
subttl	configurazione
page

; ---------------------------------------------
;        CONFIGURAZIONE IMPOSTATA
; ---------------------------------------------
	TY_INTERP    	EQU   TY_STOP
	TIPO_STOP    	EQU   STOP_PC    
	SYS_DUALE	EQU   1
	TIPO_AC	     	EQU   AC_SIMULATORE
	TIPO_STAR	EQU   STAR_SIMULATORE
	GEST_GRAF    	EQU   GRAF_SI
	UTENTE 	     	EQU   ENEL
	TIPO_TAST    	EQU   TAST_MMI
	TABULATI     	EQU   TAB_SI
	ARCHIVI	     	EQU   ARCH_NV
	PAS	     	EQU   PAS_SI
	NPASTOP	        EQU   4
	TIPO_HARD_COPY 	EQU   PAINTJET
	HARDCOPY     	EQU   SI_HARD
        HCOPY_DOVE      EQU   SCADA
	ISA		EQU   ISA_SI
        TIPO_BUZZER     EQU   UCCP_BUZZ

	num_printer	equ	2

;
;	Parametri per linee di comunicazione per Scada
;	------------------------------------------------
;
	iSDx507		equ	1
        num_linee	equ	2		;
        num_linee_ser	equ	2		;numero linee seriali
