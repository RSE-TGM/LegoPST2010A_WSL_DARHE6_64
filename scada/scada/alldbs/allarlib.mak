##############################################################
#
#  16-09-1993
#  ----------	
#	ALLARMI.MAK
#	
#	makefile moduli per gestione allarmi
# alcuni moduli  sono compilati con la condizione
# #ifdef AC_SIMULATORE. E' stato tolto il riferimento da PSCS.CFG per cui
# per generare una versione per il simulatore e' necessario definire tale
# valore in attivazione : nmake SIM=-DAC_SIMULATORE allarlib.mak
#
#
#############################################################

# -- modello di default

!include \PSCS32\cflag.inc

# -- parametri necessari al < C >


CINCSEPA=   \pscs32\scada\sepacq
CSRC = \pscs32\scada	        		# directory sorgenti C 	scada
CINCC= \pscs32\incl	               	    	# include C


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D) -I$(CINCC) -I$(CSRC)\$(WORK) 
CL1=$(CC) $(CFLAGS_D) -I$(CINCC) -I$(CSRC)\$(WORK) $(SIM)
CL2=$(CC) $(CFLAGS_D) -I$(CINCC) -I$(CSRC)\$(WORK) -I$(CINCSEPA)
!ELSE
CL= $(CC) -I$(CINCC) -I$(CSRC)\$(WORK)
CL1=$(CC) -I$(CINCC) -I$(CSRC)\$(WORK) $(SIM)
CL2=$(CC) -I$(CINCC) -I$(CSRC)\$(WORK) -I$(CINCSEPA)
!ENDIF

FLIB= \PSCS32\LIB\LIBALLAR.LIB    # nome della libreria
LIB = 386LIB $(FLIB) -REPLACE              # generazione libreria
ERR= file.err


ALL : alldef.obj allcall.obj allabzon.obj allcval.obj alldec.obj allric.obj allricon.obj\
      allsel.obj allstam.obj cunita.obj gestri.obj allsev.obj allriv.obj allcomp.obj\
      allricsi.obj allrall.obj allmute.obj allpvis.obj allpag.obj allsric.obj\
      allcod.obj alllast.obj

# -- generazione oggetti <archivi>
# --------------------------------

WORK= alldbs

alldef.obj:	$(CSRC)\$(WORK)\alldef.c $(CINCC)\allstr.inc 
	$(CL2)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allcall.obj:	$(CSRC)\$(WORK)\allcall.c $(CINCC)\allstr.inc 
	$(CL1)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allabzon.obj:	$(CSRC)\$(WORK)\allabzon.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allcval.obj:	$(CSRC)\$(WORK)\allcval.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

alldec.obj:	$(CSRC)\$(WORK)\alldec.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allric.obj:	$(CSRC)\$(WORK)\allric.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allricon.obj:	$(CSRC)\$(WORK)\allricon.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allsel.obj:	$(CSRC)\$(WORK)\allsel.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allstam.obj:	$(CSRC)\$(WORK)\allstam.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

cunita.obj:	$(CSRC)\$(WORK)\cunita.c $(CINCC)\allstr.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\g1tipdb.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

gestri.obj:	$(CSRC)\$(WORK)\gestri.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g1tipdb.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allsev.obj:	$(CSRC)\$(WORK)\allsev.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allriv.obj:	$(CSRC)\$(WORK)\allriv.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allcomp.obj:	$(CSRC)\$(WORK)\allcomp.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allricsi.obj:	$(CSRC)\$(WORK)\allricsi.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allrall.obj:	$(CSRC)\$(WORK)\allrall.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allmute.obj:	$(CSRC)\$(WORK)\allmute.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allpvis.obj:	$(CSRC)\$(WORK)\allpvis.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allpag.obj:	$(CSRC)\$(WORK)\allpag.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allsric.obj:	$(CSRC)\$(WORK)\allsric.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

allcod.obj:	$(CSRC)\$(WORK)\allcod.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

alllast.obj:	$(CSRC)\$(WORK)\alllast.c $(CINCC)\allstr.inc
	$(CL)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@WOMP /fp $*.obj  
	$(LIB)  $*.obj  

