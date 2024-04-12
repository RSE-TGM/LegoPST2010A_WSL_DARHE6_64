/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
include hcpar.inc
;
; File di personalizzazione della Stazione STOP
; ---------------------------------------------
;
;  Versione Supportate
;  -------------------
STOP_PC EQU     1
STOP_MB EQU     2
;
;  Versione Supportate per INTERPRETE
;  ----------------------------------
TY_STOP		EQU	1 ; interprete versione STOP
TY_CONFIG	EQU	2 ; intertrete versione CONFIG
;
;  Acquisizioni supportate
;
AC_SIMU		EQU	1 ; acquisizione non esistente
AC_SIMULATORE	EQU	2 ; acquisizione da simulature
AC_ETHERNET     EQU     3 ; acquisizione ethernet
AC_INET         EQU     4 ; acquisizione da inet
AC_INETDUALE	EQU	5 ; acquisizione da inet doppia rete
AC_SDS  	EQU	6 ; acquisizione da SDS Nuovo Pignone
AC_SAMP  	EQU	7 ; acquisizione da rete SAMP
AC_SERIALE  	EQU	8 ; acquisizione da SDI con protocollo Seriale
AC_PLCS5  	EQU	9 ; acquisizione da PLC Siemens
;
; Star acquisizione previste
;
STAR_SEPA  EQU  0
STAR_SDI   EQU  1
STAR_SIM   EQU  2
STAR_SDS   EQU  3
STAR_SELTA EQU  4
STAR_SIMULATORE EQU 5
STAR_PLCS5 EQU 6
;
; uso generale
; ------------
GRAF_SI   EQU   1
GRAF_NO   EQU   0
TAST_PC	  EQU	1
TAST_MMI  EQU	2
TAST_NO   EQU	3
TAB_NO	  EQU	0
TAB_SI	  EQU	1
ARCH_NO	  EQU	0
ARCH_SI	  EQU	1
ARCH_NV   EQU   2
PAS_NO	  EQU	0
PAS_SI	  EQU	1
NO_HARD	  EQU   0
SI_HARD	  EQU   1
MMI       EQU   0
SCADA     EQU   1
ISA_NO	  EQU	0
ISA_SI	  EQU	1
UCCP_BUZZ EQU   0
PC_BUZZ   EQU   1
;
; tipo hardcopy
; -------------
QUADJET 	EQU 1
PAINTJET	EQU 2
TECTRONIX	EQU 3
;
;  utente 
; ------------
ENEL            EQU 1
SEPA            EQU 2
CISE            EQU 3
SELTA           EQU 4
AEM             EQU 5
SDI             EQU 6
FORES           EQU 7
HOST_DG         EQU 99
;
;  PARAMETRO PER CICALINO
;  ----------------------
TIK_INFINITO	EQU 1	 	; 1 tick significa accensione con tempo infinito del cicalino
TIK_RESET	EQU 0	 	; 0 tick significa reset temporizzazione

; Numero di utenti ISA che possono accedere a SCADA.
; Attenzione!! Questo parametro deve essere uguale a NCHAN_ISA
; definito nel file DCONF.INC per i moduli "C".

NCHAN_ISA	EQU   4          ;Numero di client ISA Servibili
