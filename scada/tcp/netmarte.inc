/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
NETBEG macro
nserver=0
nclient=0
nparent=0
ncon=0
nudp=0
endm

NETEND  macro
endm

setnomi macro i,chtx,chrx,dimtx,dimrx
CTX&i   textequ <c&chtx>
CRX&i   textequ <c&chrx>
QTX&i   textequ <chtx>
QRX&i   textequ <chrx>
DTX&i   equ dimtx
DRX&i   equ dimrx
endm

serverdef	macro	 n,chtx,chrx,dimtx,dimrx

setnomi %nparent,chtx,chrx,dimtx,dimrx
ncon=ncon+ n
nserver =nserver+1
nparent =nparent+1
endm

clientdef	macro	 chtx,chrx,dimtx,dimrx

setnomi %nparent,chtx,chrx,dimtx,dimrx
ncon=ncon+ 1
nclient =nclient+1
nparent =nparent+1
endm

;
ntasrx  macro   i,prio
        tcb     t_rx&i,prio,400,__t_rx&i,0,C
endm
ntastx  macro   i,prio
        tcb     t_tx&i,prio,400,__t_tx&i,0,C
endm

nettsk_con macro   first

prio=first
i=0
        rept    ncon
                ntasrx  %i,%prio
                i=i+1
                prio = prio+1
        endm
endm
;
;
nettsk_parent macro   first

prio=first
	tcb	parent, prio,400,netparent,0,C
        prio=prio+1
i=0
        rept    nparent
                ntastx  %i,%prio
                i=i+1
                prio = prio+1
        endm

i=0
        rept    nudp
                ntaskudp  %i,%prio
                i=i+1
                prio = prio+1
        endm

endm



que_p  macro   i
queue    %QTX&i,DTX&i,0
queue    %QRX&i,DRX&i,0
endm


netque macro 
ique=0
        rept    nparent
                que_p %ique
                ique=ique+1
        endm
ique=0
        rept    nudp
                que_udp %ique
                ique=ique+1
        endm
endm

;
; definizioni per risorse UDP
;
;

setnomiudp  macro i,chtx,chrx,dimtx,dimrx
UCTX&i   textequ <c&chtx>
UCRX&i   textequ <c&chrx>
UQTX&i   textequ <chtx>
UQRX&i   textequ <chrx>
UDTX&i   equ dimtx
UDRX&i   equ dimrx
endm

dgramdef	macro	 chtx,chrx,dimtx,dimrx

setnomiudp %nudp,chtx,chrx,dimtx,dimrx
nudp=nudp+1
endm

;
ntaskudp  macro   i,prio
        tcb     t_urx&i,prio,400,__t_urx&i,0,C
        tcb     t_utx&i,prio,400,__t_utx&i,0,C
endm

;


que_udp  macro   i
queue    %UQTX&i,UDTX&i,0
queue    %UQRX&i,UDRX&i,0
endm

;

