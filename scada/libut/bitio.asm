page  60,132                                                                 
title  -- routine per la gestione bit


;*********************************************************************************
;
; scope:
; ******
; contiene le routine che manipolano i bit di un vettore.
; le routine sono le seguenti:
;          
; 1 - bitset  = setta un bit in una determinata posizione  
;               di un array.
;
; 2 - bitvalue= ritorna il valore del bit in una specificata
;               posizione.
;
; 3 - DecFl86=  converte float86 -> ascii format.
;
; *******************************************************************
;
; history:
; ********
;
; 22/02/1992	td	created
; 10/07/1992	td	modificato decfl86: caso numero cifre dec=0
;
; *******************************************************************
page


	public	bitset, bitvalue, DecFl86

.386p
.387
.model	small,syscall

        .xlist

datageneral     equ 1           ; tipo formato dati
.const
wbmask  label word
ifdef   datageneral    
;
; maschera per manipolazione dei bits
; formato datageneral ( swapping )
; -----------------------------------
        dw      8000h,4000h,2000h,1000h,0800h,0400h,0200h,0100h
        dw      0080h,0040h,0020h,0010h,0008h,0004h,0002h,0001h
else
; formato intel
; -------------
        dw      0001h,0002h,0004h,0008h,0010h,0020h,0040h,0080h
        dw      0100h,0200h,0400h,0800h,1000h,2000h,4000h,8000h
endif

subttl	routine bitset
page
; ****
; name:	
;	bitset
;
; scope:
;	setta un bit partendo da un indice assoluto in
; 	un array.
;
; params:
;	buffer pointer, bit position, bit value
;                      
; return:
;
; call:
;	void bitset ((char *)buffer, (short)pos, (short)value) 
; ********************************************************
;
.code

bitset	proc    uses  edi ebx ,
	pbuff:  ptr byte,
        pos:    word,
        value:  word

	mov     edi, pbuff	    ; punto sul buffer
        movzx   ebx,pos
        mov     eax,ebx
        and     bx,000fh              ; punto sulla maskera da settare
        shl     bx,1                  ; passo word
        mov     dx,wbmask[ebx]        ; leggo la maschera 
        mov     bx,ax                 ; trovo la posizione nel buffer
        shr     bx,3
        and     bx,0fffeh
        not     dx
        and     [edi+ebx],dx          ; resetto bit
        cmp     value,0               ; testo se set= 1 o reset= 0
        jz      bitset_end
        not     dx
        or      [edi+ebx],dx          ; setto bit
bitset_end:
	ret
		
bitset	endp

subttl	routine bitvalue
page
; ****
; name:	
;	bitvalue
;
; scope:
;	ritorna valore del bit in una data posizione all'interno di una word
;
; params:
;	buffer pointer, bit position
;                      
; return:
;       eax = valore del bit
; call:
;	char bitvalue ((char *)buffer, (short)pos) 
; ***************************************************
;	
bitvalue proc    uses edi ebx ,
	pbuff:  ptr byte,
        pos:    word

	mov   edi, pbuff	    ; punto sul buffer
        movzx ebx,pos
        mov   eax,ebx
        and   bx,000fh              ; punto sulla maskera da settare
        shl   bx,1                  ; passo word
        mov   dx,wbmask[ebx]        ; leggo la maschera 
        mov   bx,ax                 ; riprendo la posizione nel buffer
        shr   bx,3                  ; vedo se Š maggiore di 8
        and   bx,0fffeh
        mov   ax,[edi+ebx]          ; leggo il dato del buffer
        and   eax,0ffffh
        and   ax,dx
        or    ax,ax 
        jz    bitvalue_end
        mov   eax,1
bitvalue_end:
	ret
		
bitvalue endp

;
; costanti per eliminare la vigola
; --------------------------------
tabpot10  label dword  
        dd	1.e0
        dd      1.e1
        dd      1.e2
        dd      1.e3
        dd      1.e4
        dd      1.e5
        dd      1.e6
        dd      1.e7
        dd      1.e8
        dd      1.e9
        dd      1.e10
        dd      1.e11
        dd      1.e12
        dd      1.e13
        dd      1.e14
        dd      1.e15
        dd      1.e16
        dd	1.e17
        dd	1.e18
        dd	1.e19

subttl	routine DecFl86
page
; ****
; name:	
;	DecFl86
;
; scope:
;	decodifica un valore float86 in una stringa ascii
;
; params:
;	buffer pointer, float, n§ cifre max., n§ cifre decimali
;                      
; return:
;
; call:
;	void DecFl86 ((char *)buffer, (dword)value, nmax, ndec)
; *************************************************************
;	
DecFl86 proc    uses esi edi ebx,
	pbuff:  ptr byte,               ;ascii buffer pointer
        value:  dword,                  ;dword value
        nmax:   word,                   ;numero massimo di cifre
        ndec:   word                    ;numero cifre decimali

        local   btemp: tbyte, ppoint: word

        movzx   eax,ndec
        mov     ppoint,ax
        fld     value
        movzx   ebx,ndec
        shl     ebx,2                    ;passo dword
        fmul    tabpot10[ebx]	        ;st = misura * (10 ** numdec)
        fbstp   btemp                   ;rileggo come bcd
        fwait
        movzx   ebx,nmax
        lea     edi,btemp                
        mov     ecx,size btemp-2
        add     edi,ecx
        std
        xor     al,al                   ;ricerco primo carattere diverso da zero
  repe  scasb   

        cld
        jnz     sk_cont
        movzx   ecx,ndec
        inc     cx
        test    byte ptr [edi],0f0h      ; testo se esiste la seconda cifra
        jz      pari
        inc     cx
        jmp     pari
sk_cont:
        add     cx,2
        shl     cx,1                    ; cx = n. caratteri = (n. bytes * 2)
        test    byte ptr [edi+1],0f0h    ;stringa dispari
        jnz     pari
        dec     cx
pari:
	mov	edi, pbuff	        ;punto sul buffer
        mov     esi,edi
        mov     dx,cx
        movzx   ecx,bx                   ;riempio la stringa dest. con blank
        mov     al,' '
   rep  stosb

        mov     edi,esi
        mov     cx,dx
        inc     dx                      ; dx = n.caratteri + punto
        test    byte ptr btemp[9],80h   ;testo bit di segno
        jz      segno_pos
        inc     dx                      ; conto anche segno
segno_pos:

        cmp     bx,dx
        jb      ofw_err
        lea     esi,btemp
l_conv:

        lodsb
        mov     ah,al
        and     al,0fh
        add     al,30h
        mov     [edi+ebx-1],al
        dec     ebx
        dec     ppoint
        jnz     sk_1
        mov     byte ptr [edi+ebx-1],'.'
        dec     ebx
sk_1:
        dec     cx
        jcxz    end_conv
        mov     al,ah
        and     al,0f0h
        shr     al,4
        add     al,30h
        mov     byte ptr [edi+ebx-1],al
        dec     ebx
        dec     ppoint
        jnz     sk_2
        mov     byte ptr [edi+ebx-1],'.'
        dec     ebx
sk_2:                 

        loop    l_conv
end_conv:

        test    byte ptr btemp[9],80h   ;testo bit di segno
        jz      exit
        and     ebx,ebx                   ;ho spazio per segno meno ?
        jz      ofw_err
        mov     byte ptr [edi+ebx-1],'-'
exit:
        ret        
ofw_err:
        mov     al,'*'
        movzx   ecx, nmax
    rep stosb
        ret


DecFl86 endp
	end	
