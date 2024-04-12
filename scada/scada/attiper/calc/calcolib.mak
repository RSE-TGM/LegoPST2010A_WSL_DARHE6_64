#############################################################
#
#  17-09-1993
#  ----------	
#	CALCLIB.MAK
#	
#	makefile moduli per CALCOLATE
#
#############################################################

# -- modello di default
!include \pscs32\cflag.inc

# -- parametri necessari al < C >

CSRC = \pscs32\scada			      		# directory sorgenti C 	scada
CINCC= \pscs32\incl	                  	    	# include C


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D) -I$(CINCC) -I$(CSRC)\$(WORK) 
!ELSE
CL= $(CC) -I$(CINCC) -I$(CSRC)\$(WORK)
!ENDIF


# -- parametri necessari per la gestione files errori

ERR= file.err
FLIB= \PSCS32\LIB\LIBCALC.LIB                # nome della libreria
LIB = 386lib $(FLIB) -REPLACE

ALL: initcalc.obj minimo.obj filtro.obj setpunt.obj massimo.obj media.obj scartoqm.obj\
     integral.obj mediaist.obj operaz.obj oremisur.obj oreorgan.obj portata1.obj portata2.obj\
     sommaist.obj calc.obj gettime.obj

# -- generazione oggetti <ATTIPER\CALC>
# -------------------------------------

WORK= attiper\calc

initcalc.obj:	$(CSRC)\$(WORK)\initcalc.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

minimo.obj:	$(CSRC)\$(WORK)\minimo.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

filtro.obj:	$(CSRC)\$(WORK)\filtro.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

setpunt.obj:	$(CSRC)\$(WORK)\setpunt.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

massimo.obj:	$(CSRC)\$(WORK)\massimo.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

media.obj:	$(CSRC)\$(WORK)\media.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

scartoqm.obj:	$(CSRC)\$(WORK)\scartoqm.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

integral.obj:	$(CSRC)\$(WORK)\integral.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

mediaist.obj:	$(CSRC)\$(WORK)\mediaist.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

operaz.obj:	$(CSRC)\$(WORK)\operaz.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

oremisur.obj:	$(CSRC)\$(WORK)\oremisur.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

oreorgan.obj:	$(CSRC)\$(WORK)\oreorgan.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

portata1.obj:	$(CSRC)\$(WORK)\portata1.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

portata2.obj:	$(CSRC)\$(WORK)\portata2.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj
				       
sommaist.obj:	$(CSRC)\$(WORK)\sommaist.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

calc.obj:	$(CSRC)\$(WORK)\calc.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj

gettime.obj:	$(CSRC)\$(WORK)\gettime.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g3calcdb.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp  /fp $*.obj
	$(LIB) $*.obj




