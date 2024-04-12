#############################################################
#
#  14-10-1993
#  ----------	
#	ACQUILIB.MAK
#	
#	makefile moduli per ACQUI
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


# -- parametri necessari per la gestione files errori

ERR= file.err
FLIB = LIBACQUI.LIB
LIB= 386LIB $(FLIB) -REPLACE

ALL:  acqui.obj setaac.obj setdic.obj setcom.obj diagnodi.obj coman.obj invao.obj inetmast.obj\
      gesarm.obj setdata.obj

# -- generazione oggetti <ACQUI>
# -------------------------------

WORK= acqui

acqui.obj:	$(CSRC)\$(WORK)\acqui.c\
                $(CINCC)\fileop.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mesest.inc $(CINCC)\comunic.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
	$(CL)   $(CSRC)\$(WORK)\acqui.c > $(ERR)
        WOMP    /fp acqui.obj
        $(LIB)  acqui.obj
 
setaac.obj:	$(CSRC)\$(WORK)\setaac.c\
                $(CINCC)\fileop.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mesest.inc $(CINCC)\comunic.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
	$(CL)   $(CSRC)\$(WORK)\setaac.c > $(ERR)
        WOMP    /fp setaac.obj
        $(LIB)  setaac.obj

setdic.obj:	$(CSRC)\$(WORK)\setdic.c\
                $(CINCC)\fileop.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mesest.inc $(CINCC)\comunic.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
	$(CL)   $(CSRC)\$(WORK)\setdic.c > $(ERR)
        WOMP    /fp setdic.obj
        $(LIB)  setdic.obj

setcom.obj:       $(CSRC)\$(WORK)\setcom.c\
                $(CINCC)\fileop.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mesest.inc $(CINCC)\comunic.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
	$(CL) $(CSRC)\$(WORK)\setcom.c > $(ERR)
        WOMP    /fp setcom.obj
        $(LIB)  setcom.obj

diagnodi.obj:       $(CSRC)\$(WORK)\diagnodi.c
        $(CL)   $(CSRC)\$(WORK)\diagnodi.c > $(ERR)
        WOMP    /fp diagnodi.obj
        $(LIB)  diagnodi.obj

coman.obj:       $(CSRC)\$(WORK)\coman.c
	$(CL)   $(CSRC)\$(WORK)\coman.c > $(ERR)
        WOMP    /fp coman.obj
        $(LIB)  coman.obj

invao.obj:       $(CSRC)\$(WORK)\invao.c
	$(CL)   $(CSRC)\$(WORK)\invao.c > $(ERR)
        WOMP    /fp invao.obj
        $(LIB)  invao.obj

gesarm.obj:       $(CSRC)\$(WORK)\gesarm.c
	$(CL)   $(CSRC)\$(WORK)\gesarm.c > $(ERR)
        WOMP    /fp gesarm.obj
        $(LIB)  gesarm.obj

setdata.obj:       $(CSRC)\$(WORK)\setdata.c
	$(CL)   $(CSRC)\$(WORK)\setdata.c > $(ERR)
        WOMP    /fp setdata.obj
        $(LIB)  setdata.obj

inetmast.obj:       $(CSRC)\$(WORK)\inetmast.c
	$(CL)   $(CSRC)\$(WORK)\inetmast.c > $(ERR)
        WOMP    /fp inetmast.obj
        $(LIB)  inetmast.obj






