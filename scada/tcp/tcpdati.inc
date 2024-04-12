/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/


dim_buffer      equ     2500
udp_buffer	equ	1528

HINTINDEX	equ	1
HINTADDRESS	equ	2
HINTPAR		equ	HINTADDRESS		;handler riceve address


SERVERTYPE      equ     1
CLIENTTYPE      equ     2
UDPTYPE		equ     3
BROADTYPE	equ     4

ADDRESS struc
	fhost           dd      ?  
	fsocket         dw      ?
	lsocket         dw      ?
	protocol        db      ?
ADDRESS ends


SSERDEF	struc
        tipo            dw      ?                
	base		dw	?
	num		dw	?
	chtx		dw	?
	chrx		dw	?
	tcbtx		dd	?
SSERDEF	ends
 

SDESCCON	struc
        nd              dw      ?
        a               address <>
	spcon		db	?
	stat		db	?
	present 	db	?
	tcbrx		dd	?
	buf		db   dim_buffer dup (?)
SDESCCON	ends

sizeconn	equ	size SDESCCON


SUDPDEF	struc
        tipo            dw      ?                
	chtx		dw	?
	chrx		dw	?
	tcbtx		dd	?
	tcbrx		dd	?
SUDPDEF	ends
 

SBROADCON	struc
        nd              dw      ?
        a               address <>
	br_flag		dw	?
	upresent 	db	?
	tcbrx		dd	?
	buf_r		db   udp_buffer dup (?)
	buf_t		db   udp_buffer dup (?)
SBROADCON	ends

NET_AS_OPEN     equ     01h
NET_AS_RCV      equ     02h
NET_AS_XMT      equ     03h
NET_AS_FCLOSE   equ     05h
NET_AS_CLOSE    equ     06h
NET_AS_ERROR    equ     07h
