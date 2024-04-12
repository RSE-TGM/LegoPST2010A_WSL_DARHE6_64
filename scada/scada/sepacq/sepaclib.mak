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
CCFGSW= \pscs32\incl\$(SYSTEM)\$(PACKET)  # include file di configurazione SW

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D)  -I$(CINCC) -I$(CSRC)\$(WORK) -I$(CCFGSW)
!ELSE
CL= $(CC)  -I$(CINCC)  -I$(CSRC)\$(WORK) -I$(CCFGSW)
!ENDIF


FLIB= \PSCS32\SCADA\SEPACQ\LIBSEPAC.LIB
LIB= 386LIB $(FLIB) -REPLACE 
ERR= file.err

WORK= sepacq


ALL: sepabil.obj septestn.obj separmfa.obj sepiniz.obj sepacqui.obj sepgesar.obj\
     sepgesre.obj sepsetaa.obj  sepsetdi.obj sepinvao.obj sepcoman.obj seprich.obj\
     rceprn.obj rce.obj sepmast.obj setdata.obj


sepabil.obj:    $(CSRC)\$(WORK)\sepabil.c $(CSRC)\$(WORK)\sepmess.inc\
                $(CSRC)\$(WORK)\sepstruc.inc $(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

septestn.obj:	$(CSRC)\$(WORK)\septestn.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

separmfa.obj:	$(CSRC)\$(WORK)\separmfa.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepiniz.obj:	$(CSRC)\$(WORK)\sepiniz.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepacqui.obj:	$(CSRC)\$(WORK)\sepacqui.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepgesar.obj:	$(CSRC)\$(WORK)\sepgesar.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepgesre.obj:	$(CSRC)\$(WORK)\sepgesre.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepsetaa.obj:	$(CSRC)\$(WORK)\sepsetaa.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepsetdi.obj:	$(CSRC)\$(WORK)\sepsetdi.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepinvao.obj:	$(CSRC)\$(WORK)\sepinvao.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepcoman.obj:	$(CSRC)\$(WORK)\sepcoman.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

seprich.obj:	$(CSRC)\$(WORK)\seprich.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj
#
#	Rce
#
rceprn.obj:	$(CSRC)\$(WORK)\rceprn.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc $(CSRC)\$(WORK)\rce.h
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

rce.obj:	$(CSRC)\$(WORK)\rce.c $(CSRC)\$(WORK)\sepmess.inc $(CSRC)\$(WORK)\sepstruc.inc\
		$(CSRC)\$(WORK)\sepdati.inc $(CSRC)\$(WORK)\rce.h
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

sepmast.obj:	$(CSRC)\$(WORK)\sepmast.c 
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

setdata.obj:	$(CSRC)\$(WORK)\setdata.c 
         $(CL)  $(CSRC)\$(WORK)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

