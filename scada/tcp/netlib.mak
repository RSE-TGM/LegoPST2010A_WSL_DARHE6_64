#############################################################
#	
#	net.mak
#
#############################################################

!include \PSCS32\cflag.inc

# -- parametri necessari al < C >

CINCC1= \pscs32\marte			  # directory sorgenti C scada
CINCC= \pscs32\incl
CSRC=\pscs32\tcp
CSPC=\pscs32\tcp\pctcp

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D)  -I$(CINCC) -I$(CINCC1) -I$(CSRC)
CL32= $(CC) $(CFLAGS_D)  -I$(CSRC)
!ELSE
CL= $(CC) -I$(CINCC) -I$(CINCC1) -I$(CSRC)
CL32= $(CC) -I$(CSRC)
!ENDIF

# -- parametri necessari al < ASM >

ASMSRC=   \pscs32\scada
ASMINC=   \pscs32\marte
ASMSW=    \pscs32\incl


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(ASMINC) -I$(ASMSW) 
!ELSE
ML = $(ASM) -I$(ASMINC) -I$(ASMSW) 
!ENDIF

FLIB=   \PSCS32\LIB\LIBNET.LIB
LIB = 386lib  $(FLIB) -REPLACE


# Sorgenti - C -
# --------------
.c.obj :
        $(CL) $< >$*.err
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        !@del  $*.err




# Sorgenti - ASM - PHARLAP - 386 -
# --------------------------------
.asm.obj :
        $(ML) $*.asm >$*.err
	$(LIB)  $*.obj
        !@del  $*.err
        



all:  rxnet.obj txnet.obj netserve.obj netinit.obj handlers.obj netdiag.obj\
      broadf.obj taskslav.obj sysc32.obj netstpor.obj


sysc32.obj:	$(CSPC)\sysc32.c 
	$(CL32) $(CSPC)\$*.c  > $*.err
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        !@del  $*.err



