#############################################################
#
#  06 Maggio 1995
#  ---------------	
#	
#	VirtLib.mak
#	
#	makefile moduli per gestione linee virtuali di stampa
#
#############################################################

# -- modello di default

!include \pscs32\cflag.inc

# -- parametri necessari al < ASM >

DSTRA=   \pscs32\scada\stampe
DSCAD=   \pscs32\scada
DINCL=  \pscs32\incl
DTNT=   \TNT\INCLUDE

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(DINCL) -I$(DTNT) -I$(DMARTE)
!ELSE
ML = $(ASM) -I$(DINCL) -I$(DTNT) -I$(DMARTE)
!ENDIF

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D) -I$(DINCL)
!ELSE
CL= $(CC) -I$(DINCL)
!ENDIF

ERR= file.err
FLIB= LIBSTRA.lib  # nome della libreria
LIB = 386lib $(FLIB) -REPLACE

ALL:   stdisk.obj leggifil.obj invia.obj resetlbg.obj


stdisk.obj:	$(DSTRA)\stdisk.c 
         $(CL)  $(DSTRA)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

leggifil.obj:	$(DSCAD)\leggifil.c 
         $(CL)  $(DSCAD)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

invia.obj:	$(DSTRA)\invia.c 
         $(CL)  $(DSTRA)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

resetlbg.obj:	$(DSTRA)\resetlbg.c 
         $(CL)  $(DSTRA)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj
