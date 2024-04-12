ALL : isa.obj isarc.obj isadia.obj isainv.obj isalloc.obj

#############################################################
#
#  6-11-1992
#  ----------	
#	isa.mak
#	
#	makefile moduli per gestione interfaccia rete
#
#############################################################

# -- modello di default

MODEL=L
BOARD=PC
PRE_PROC=0
SIM=
CPU=3

# -- parametri necessari al < C >

CSRC = \pscs32\scada    	      		# directory sorgenti C 	scada
CINCC= \pscs32\incl              	    	# include C
CINCAGG=\pscs32\scada\aggcfg
CINCARC=\pscs32\scada\arc
CCFGSW= \pscs32\incl\$(SYSTEM)\$(PACKET)	# include file di configurazione SW
DTCP=   \pscs32\tcp

!include \pscs32\cflag.inc

WORK6= isa

CL=$(CC) $(CFLAGS) $(CFLAGS_D) -I$(CINCC) -I$(CINCARC) -I$(DTCP) -I$(CINCAGG)

# -- parametri necessari per la gestione files errori

ERR= file.err

FLIB= \PSCS32\SCADA\ISA\LIBISA.LIB   # nome della libreria
LIB =386LIB $(FLIB) -REPLACE

ALL : isa.obj  isarc.obj isadia.obj isadescr.obj


# -- generazione oggetti <archivi>
# ------------------------------

isa.obj:	$(CSRC)\$(WORK6)\isa.c $(CSRC)\$(WORK6)\isa.h
	$(CL)   $(CSRC)\$(WORK6)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

isarc.obj:	$(CSRC)\$(WORK6)\isarc.c $(CSRC)\$(WORK6)\isarc.inc
	$(CL)   $(CSRC)\$(WORK6)\$*.c > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

isadia.obj:	$(CSRC)\$(WORK6)\isadia.c
	$(CL)   $(CSRC)\$(WORK6)\$*.c > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

isadescr.obj:	$(CSRC)\$(WORK6)\isadescr.c $(CSRC)\$(WORK6)\isa.h
	$(CL)   $(CSRC)\$(WORK6)\$*.c > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

isainv.obj:	$(CSRC)\$(WORK6)\isainv.c $(CSRC)\$(WORK6)\isa.h
	$(CL)   $(CSRC)\$(WORK6)\$*.c > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

isalloc.obj:	$(CSRC)\$(WORK6)\isalloc.c $(CSRC)\$(WORK6)\isa.h
	$(CL)   $(CSRC)\$(WORK6)\$*.c > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

