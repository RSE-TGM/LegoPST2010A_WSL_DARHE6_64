#############################################################
#
#  1-10-1993
#  ----------	
#	Libut.mak
#	
#	makefile libreria moduli di uso generale contenuti 
#	nel direttorio \pscs\libut
#
#############################################################

# -- modello di default


# -- parametri necessari al < C >

!include \pscs32\cflag.inc


CINCC= \pscs32\incl
CSRC=\pscs32\libut

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D)  -I$(CINCC) -I$(CSRC)
!ELSE
CL= $(CC)  -I$(CINCC) -I$(CSRC)
!ENDIF

# -- parametri necessari al < ASM >

ASMSRC=   \pscs32\libut
ASMSW=    \pscs32\incl


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(ASMSRC) -I$(ASMSW) 
!ELSE
ML = $(ASM) -I$(ASMSRC) -I$(ASMSW) 
!ENDIF


# -- parametri necessari per la gestione files errori

ERR= file.err
FLIB=\PSCS32\LIBUT\LIBPSCS.LIB	        # nome della libreria
LIB =386LIB $(FLIB) -REPLACE

ALL :  ricerca.obj ctrlstat.obj allocdb.obj decnum.obj rwdbal.obj aggfconf.obj\
       exstati.obj readiz.obj readdb.obj readef.obj bitio.obj 

ricerca.obj:	$(CSRC)\ricerca.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

ctrlstat.obj:	$(CSRC)\ctrlstat.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

allocdb.obj:	$(CSRC)\allocdb.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

decnum.obj:	$(CSRC)\decnum.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

rwdbal.obj:	$(CSRC)\rwdbal.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

aggfconf.obj:	$(CSRC)\aggfconf.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

exstati.obj:	$(CSRC)\exstati.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

readiz.obj:	$(CSRC)\readiz.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

readdb.obj:	$(CSRC)\readdb.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

readef.obj:	$(CSRC)\readef.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
	WOMP  /fp  $*.obj
	$(LIB)  $*.obj

bitio.obj:	$(ASMSRC)\bitio.asm
	$(ML)   $(CSRC)\$*.asm  > $(ERR)
	$(LIB)  $*.obj
