/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
;////////////////////////////////////////////////////////////////////////////
;
;       HCPAR.INC: File include Assembler contenente i 
;
;       parametri per hard copy
;       -----------------------
;
;       28.07.92  -  GM.Furlan
;
;////////////////////////////////////////////////////////////////////////////
;
NUM_FILE_HC     EQU   7 		; NUMERO MASSIMO H_C CONTEMPORANEE
PORT_HARD	EQU   0			; PORTA PARALLELA HARD_COPY
;
;	numero di pixel della riga in funzione della zona
;
n_pixel_s equ 640
n_pixel_i equ 640
n_pixel_w equ 320

;	Definizione n. di cicli di lettura per ogni zona
;
fasi_s equ 6		; n. cicli lettura zona S
fasi_i equ 40		; n. cicli lettura zona I
fasi_w equ 12		; n. cicli lettura zona W
;
;	numero bytes letti per ogni ciclo
;
n_w_s equ (60   / fasi_s * n_pixel_s / 2) 
n_w_i equ (400  / fasi_i * n_pixel_i / 2)
n_w_w equ (180  / fasi_w * n_pixel_w / 2)
;
;	numero blocchi disco per ogni lettura hard copy
;
nb_z_s equ (n_w_s - 1)/512 + 1
nb_z_i equ (n_w_i - 1)/512 + 1
nb_z_w equ (n_w_w - 1)/512 + 1
;
;	numero blocchi disco di ogni file di memorizzazione pagina
;
lhcopy	equ (nb_z_i * fasi_i)
;
;	numero byte in ultimo blocco disco
;
last_z_s equ n_w_s - ((nb_z_s - 1)*512)
last_z_i equ n_w_i - ((nb_z_i - 1)*512)
last_z_w equ n_w_w - ((nb_z_w - 1)*512)
