/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
;       File con le espansioni Macro
;       utilizzate per la gestione delle schede iSBC546
;       ---------------------------------------
;       	        M A C R O 
;       ---------------------------------------
;--------------------------------------------------------------
;	macro per la definizione dell'area dati dei task out
;	della 546.
;       I parametri sono:
;       b -> numero della Board
;       i -> numero della Linea
;--------------------------------------------------------------

dati_linee	MACRO	b,i

        Extrn	__qperif_&b&i:abs

        Public	dataperif_&b&i

dataperif_&b&i	dati_perif  <__qperif_&b&i, (num_linee)*b+i >

		ENDM

