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

include tcpdati.inc



netbeg	macro

SERCLIDEF	segment	public Use32  'CODE'
	public	_SerCliDef
_SerCliDef	label	byte
SERCLIDEF	ends

CCONDEF		segment	public Use32  'CODE'
	public	_iParent
_iParent	label	byte
CCONDEF	ends

TCONDEF	segment	public  Use32 'CODE'
	public	_T_Rx
_T_Rx	label	byte
TCONDEF	ends

UDPDEF	segment public Use32 'CODE'
	public _UdpDef
_UdpDef	label byte
UDPDEF	ends

nserver=0
nclient=0
nparent=0
ncon=0
nudp=0

endm


;
; definizione vettore TCB task di ricezione
;

deftaskrx	macro		i
	extrn	__t_rx&i&_tcb :byte
TCONDEF	segment
	dd	__t_rx&i&_tcb
TCONDEF	ends

endm
;
; Main Macro di definizione Server
;
serv1	macro	base,num,parent,chtx,chrx

ifndef	__&chtx
	extrn	__&chtx:abs
endif
ifndef	__&chrx
	extrn	__&chrx:abs
endif
	extrn	__t_tx&parent&_tcb :byte


SERCLIDEF	segment
        SSERDEF <SERVERTYPE,base,num,__&chtx,__&chrx,__t_tx&parent&_tcb>
;       dw      SERVERTYPE
;	dw	base
;	dw	num
;	dw	chtx
;	dw	chrx
;	dd	t_tx&parent&_tcb
SERCLIDEF	ends

CCONDEF	segment
	rept	num
	dw	nparent         ; indice di CLIENT/SERVER di appartenenza
	endm
CCONDEF	ends

j=base
	
	rept	num
	deftaskrx	%j
	j=j+1
	endm

endm



serverdef	macro	 n,chtx,chrx,dimtx,dimrx

	serv1	%ncon,n,%nparent,chtx,chrx
nserver=nserver+1
nparent=nparent+1
ncon=ncon+n
endm

page



client1 	macro	base,parent,chtx,chrx

ifndef	__&chtx
	extrn	__&chtx:abs
endif
ifndef	__&chrx
	extrn	__&chrx:abs
endif
	extrn	__t_tx&parent&_tcb :byte


SERCLIDEF	segment
        SSERDEF <CLIENTTYPE,base,1,__&chtx,__&chrx,__t_tx&parent&_tcb>
;        dw      CLIENTTYPE
;	dw	base
;        dw      1
;	dw	chtx
;	dd	t_tx&parent&_tcb
SERCLIDEF	ends

CCONDEF	segment
	dw	nparent
CCONDEF	ends

	deftaskrx	base

endm


clientdef	macro	 chtx,chrx,dimtx,dimrx

	client1	%ncon,%nparent,chtx,chrx
nclient=nclient+1
nparent=nparent+1
ncon=ncon+1
endm

page

netend	macro

CONDATA	segment	para	public 'FAR_BSS'
	public	_beg_con_data
_beg_con_data	label	byte
	public	_Conn
_Conn	label	byte
	rept	ncon
		SDESCCON <>
	endm
        public _buftx
_buftx  label byte
        rept    nparent
        db      dim_buffer dup (?)
        endm
;
; vettori di controllo
;
        public _byteinviati
_byteinviati    dd      ncon dup (?)
        public  _acknoledge
_acknoledge     dd      ncon dup (?)
        public  _difference
_difference     dd      ncon dup (?)

	public	_end_con_data
_end_con_data	label	byte
CONDATA	ends

CONST	segment	byte public 'DATA'
	public _nServer
_nServer	dw	nserver
	public _nClient
_nClient	dw	nclient
	public _nConn
_nConn	dw	ncon
	public _nParent
_nParent	dw	nparent
	public _nUdp
_nUdp		dw	nudp

CONST	ends

UDPDATA	segment	para	public 'FAR_BSS'
	public	_beg_udp_data
_beg_udp_data	label	byte
	public	_UdpConn
_UdpConn	label	byte
	rept	nudp
		SBROADCON <>
	endm

	public	_end_udp_data
_end_udp_data	label	byte
UDPDATA	ends


TASK_SESSION    ncon
TASK_PARENT     nparent
TASK_UDP     	nudp

endm

page

;
; definizione risorsa UDP
;

udp1 	macro	ind,chtx,chrx

ifndef	__&chtx
	extrn	__&chtx:abs
endif
ifndef	__&chrx
	extrn	__&chrx:abs
endif
	extrn	__t_utx&ind&_tcb :byte
	extrn	__t_urx&ind&_tcb :byte


UDPDEF	segment
        SUDPDEF <UDPTYPE,__&chtx,__&chrx,__t_utx&ind&_tcb,__t_urx&ind&_tcb>
;        dw      UDPTYPE
;	dw	chtx
;	dw	chrx
;	dd	t_utx&ind&_tcb
;	dd	t_urx&ind&_tcb
UDPDEF	ends

endm


dgramdef	macro	 chtx,chrx,dimtx,dimrx

	udp1	%nudp,chtx,chrx
nudp=nudp+1
endm


