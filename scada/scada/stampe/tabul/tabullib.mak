#############################################################
#
#  29-09-1993
#  ----------	
#	TABULATI.MAK
#	
#	makefile moduli per STOP_PC:
#
#############################################################

# -- modello di default

!include \pscs32\cflag.inc

# -- parametri necessari al < ASM >

CSRC = \pscs32\scada			  # directory sorgenti C scada
CINCC= \pscs32\incl
INCSIM= \pscs32\incl\sim


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D)  -I$(CINCC) -I$(CSRC)\$(WORK) 
CL1= $(CC) $(CFLAGS_D)  -I$(CINCC) -I$(CSRC)\$(WORK) -I$(INCSIM)
!ELSE
CL= $(CC)  -I$(CINCC) -I$(CSRC)\$(WORK)
CL1= $(CC)  -I$(CINCC) -I$(CSRC)\$(WORK) -I$(INCSIM)
!ENDIF

# -- parametri necessari al < ASM >

ASMSRC=   \pscs32\scada
ASMINC=   \pscs32\marte
ASMSW=    \pscs32\incl


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(ASMINC) -I$(ASMSW) -I$(ASMSRC)\$(WORK) 
!ELSE
ML = $(ASM) -I$(ASMINC) -I$(ASMSW) -I$(ASMSRC)\$(WORK) 
!ENDIF


FLIB= \PSCS32\LIB\LIBTABUL.LIB           # nome della libreria
LIB = 386LIB $(FLIB) -REPLACE
ERR= file.err


ALL : tabper.obj readtab.obj racdbs.obj tabul.obj cprint.obj lantab.obj stfile.obj\
      wildric.obj  trasfile.obj

# -- generazione oggetti <tabulati>
# ------------------------------

WORK=stampe\tabul

tabper.obj:	$(CSRC)\$(WORK)\tabper.c\
                $(CINCC)\tabulati.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

readtab.obj:	$(CSRC)\$(WORK)\readtab.c\
                $(CINCC)\tabulati.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

racdbs.obj:	$(CSRC)\$(WORK)\racdbs.c\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

tabul.obj:	$(CSRC)\$(WORK)\tabul.c\
                $(CINCC)\tabulati.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

cprint.obj:	$(CSRC)\$(WORK)\cprint.c\
                $(CSRC)\$(WORK)\cprint.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL1)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

lantab.obj:	$(CSRC)\$(WORK)\lantab.c\
                $(CINCC)\tabulati.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

stfile.obj:	$(CSRC)\$(WORK)\stfile.c
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

wildric.obj:	$(CSRC)\$(WORK)\wildric.c $(CINCC)\mesprocv.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj

# -- generazione oggetti <trasfile>
# ------------------------------


trasfile.obj:	$(ASMSRC)\$(WORK)\trasfile.c
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        WOMP    /fp $*.obj
	$(LIB)  $*.obj




