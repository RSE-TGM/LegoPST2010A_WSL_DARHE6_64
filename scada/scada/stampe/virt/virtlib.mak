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

DVIRT=   \pscs32\scada\stampe\virt
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
FLIB= LIBVIRT.lib  # nome della libreria
LIB = 386lib $(FLIB) -REPLACE

ALL:   virtinv.obj virtdisk.obj virtini.obj printalt.obj virtrese.obj\
       virttlbg.obj virtsel.obj


virtinv.obj:	$(DVIRT)\virtinv.c $(DVIRT)\virtinv.h 
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

virtini.obj:	$(DVIRT)\virtini.c
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

virtdisk.obj:	$(DVIRT)\virtdisk.c
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

virtrese.obj:	$(DVIRT)\virtrese.c
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

virttlbg.obj:	$(DVIRT)\virttlbg.c
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

virtsel.obj:	$(DVIRT)\virtsel.c
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

printalt.obj:	$(DVIRT)\printalt.c
         $(CL)  $(DVIRT)\$*.c > file.err
         WOMP   /fp $*.obj
