#############################################################
#
#  9-09-1993
#  ----------	
#	LIBMANDB.MAK
#	
#	makefile moduli per Libreria MANDB
#
#############################################################

UT=
DEB=

PROT=CF1		# tipo di protezione scheda MATROX

!include \PSCS32\cflag.inc

# -- parametri necessari al < ASM >

ASMSRC=   .
ASMINC=   \pscs32\marte
ASMSW=    \pscs32\incl

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(ASMINC) -I$(ASMSW)
!ELSE
ML = $(ASM) -I$(ASMINC) -I$(ASMSW)
!ENDIF

# -- parametri necessari al < C >

CSRC = .
CINCC= \pscs32\incl	               	    	# include C

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D)  -I$(CINCC)  
!ELSE
CL= $(CC)  -I$(CINCC)  
!ENDIF

# -- parametri necessari per la gestione files errori

ERR= file.err
FLIB= \PSCS32\LIB\LIBMANDB.LIB                # nome della libreria
LIB = 386lib  $(FLIB) -REPLACE

ALL: MANDB.obj RTDEBUG.obj VISBLOCK.obj AGGIORNA.obj AGGIORND.obj AGGIORNS.obj\
     AGGIORNO.obj INTESTOR.obj INTESTDI.obj INTESTST.obj INTESTAN.obj MODFAN.obj\
     MODFDI.obj MODFOR.obj MODFST.obj SCRIVIAL.obj DECIND.obj VMBYTE.obj RDPB.obj GET_KEY.obj\
     striuk.obj


# -------------------------------------------------
# -- generazione oggetti WRDB
# -------------------------------------------------

MANDB.obj:       $(CSRC)\MANDB.c  $(CINCC)\dconf.inc
	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj

RTDEBUG.obj:       $(CSRC)\RTDEBUG.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

VISBLOCK.obj:       $(CSRC)\VISBLOCK.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

AGGIORNA.obj:       $(CSRC)\AGGIORNA.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

AGGIORND.obj:       $(CSRC)\AGGIORND.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

AGGIORNS.obj:       $(CSRC)\AGGIORNS.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

AGGIORNO.obj:       $(CSRC)\AGGIORNO.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

INTESTOR.obj:       $(CSRC)\INTESTOR.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

INTESTDI.obj:       $(CSRC)\INTESTDI.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
      	$(LIB)  $*.obj

INTESTST.obj:       $(CSRC)\INTESTST.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

INTESTAN.obj:       $(CSRC)\INTESTAN.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

MODFAN.obj:       $(CSRC)\MODFAN.c  $(CINCC)\dconf.inc
    	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
     	$(LIB)  $*.obj

MODFDI.obj:       $(CSRC)\MODFDI.c  $(CINCC)\dconf.inc
      	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
      	$(LIB)  $*.obj

MODFOR.obj:       $(CSRC)\MODFOR.c  $(CINCC)\dconf.inc
      	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
      	$(LIB)  $*.obj

MODFST.obj:       $(CSRC)\MODFST.c  $(CINCC)\dconf.inc
      	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
      	$(LIB)  $*.obj

SCRIVIAL.obj:       $(CSRC)\SCRIVIAL.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

DECIND.obj:       $(CSRC)\DECIND.c  $(CINCC)\dconf.inc
      	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
      	$(LIB)  $*.obj

VMBYTE.obj:       $(CSRC)\VMBYTE.c  $(CINCC)\dconf.inc
      	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
      	$(LIB)  $*.obj

RDPB.obj:       $(CSRC)\RDPB.c  $(CINCC)\dconf.inc
        $(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
    	$(LIB)  $*.obj

GET_KEY.obj:       $(CSRC)\GET_KEY.c  $(CINCC)\dconf.inc
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj

striuk.obj:       $(CSRC)\striuk.c  
       	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
       	$(LIB)  $*.obj


