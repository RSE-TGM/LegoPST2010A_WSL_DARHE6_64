#############################################################
#
#  20 Aprile 1993
#  --------------	
#	sepacqu.mak
#	
#############################################################

# -- modello di default

!include \PSCS32\cflag.inc

# -- parametri necessari al < C >

CSRC = \pscs32\scada			      		# directory sorgenti C 	scada
CINCC= \pscs32\incl	                  	    	# include C
CINCA= \pscs32\scada\arc	                  	    	# include C

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D) -I$(CINCC) -I$(CSRC)\$(WORK) -I$(CINCA)
!ELSE
CL= $(CC) -I$(CINCC) -I$(CSRC)\$(WORK) -I$(CINCA)
!ENDIF

# -- parametri necessari al < ASM >

ASMSRC=   \pscs32\scada
ASMINC=   \pscs32\marte
ASMSW=    \pscs32\incl
ASMVER=   $(ASMSW)\$(SYSTEM)\$(PACKET)
ASMTNT=   \TNT\INCLUDE

FLIB= \PSCS32\SCADA\SIMACQ\LIBSIMAC.LIB
LIB= 386LIB $(FLIB) -REPLACE 
ERR= file.err

WORK= SIMACQ


ALL: SIMACQUI.obj invao.obj coman.obj simsvdbs.obj simsvall.obj\
     simcldbs.obj simclall.obj simclpag.obj simlddbs.obj simvardd.obj\
     siminit.obj simlgini.obj simsdcfg.obj simclarc.obj


SIMACQUI.obj:	$(CSRC)\$(WORK)\SIMACQUI.c\
		$(CINCC)\g2comdb.inc $(CINCC)\comunic.inc\
	        $(CINCC)\messcada.inc $(CINCC)\mesqueue.h\
                $(CINCC)\diagnodi.inc $(CINCC)\dconf.inc\
		$(CINCC)\taskwd.inc\
		simula.inc simmsg.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

invao.obj:	$(CSRC)\$(WORK)\invao.c\
		$(CINCC)\comunic.inc $(CINCC)\mesqueue.h\
                $(CINCC)\dconf.inc simmsg.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

coman.obj:	$(CSRC)\$(WORK)\coman.c\
		$(CINCC)\comunic.inc $(CINCC)\mesqueue.h\
                $(CINCC)\dconf.inc simmsg.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

simsvdbs.obj:	$(CSRC)\$(WORK)\simsvdbs.c\
		$(CINCC)\comunic.inc $(CINCC)\mesqueue.h\
                $(CINCC)\dconf.inc simmsg.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

simsvall.obj:	$(CSRC)\$(WORK)\simsvall.c\
		$(CINCC)\allar.inc $(CINCC)\allstr.inc\
		$(CINCC)\dconf.inc simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj


simcldbs.obj:	$(CSRC)\$(WORK)\simcldbs.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

simclall.obj:	$(CSRC)\$(WORK)\simclall.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj


simclpag.obj:	$(CSRC)\$(WORK)\simclpag.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj


simlddbs.obj:	$(CSRC)\$(WORK)\simlddbs.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

simvardd.obj:	$(CSRC)\$(WORK)\simvardd.c
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj


siminit.obj:	$(CSRC)\$(WORK)\siminit.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

simlgini.obj:	$(CSRC)\$(WORK)\simlgini.c\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj


simsdcfg.obj:	$(CSRC)\$(WORK)\simsdcfg.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj


simclarc.obj:	$(CSRC)\$(WORK)\simclarc.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		simula.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

