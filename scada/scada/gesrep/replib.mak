#############################################################
#
#  06 Maggio 1995
#  ---------------	
#	
#	RepLib.mak
#	
#	makefile moduli per gestione linea reperibili
#
#############################################################

# -- modello di default

!include \pscs32\cflag.inc

# -- parametri necessari al < ASM >

DREP=   \pscs32\scada\gesrep
DMARTE= \pscs32\marte
DINCL=  \pscs32\incl
DTNT=   \TNT\INCLUDE

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(DINCL) -I$(DTNT) -I$(DMARTE)
!ELSE
ML = $(ASM) -I$(DINCL) -I$(DTNT) -I$(DMARTE)
!ENDIF

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D) -I$(DINCL)
!ELSE
CL= $(CC) -I$(DINCL)
!ENDIF

ERR= file.err
FLIB= LIBREP.lib  # nome della libreria
LIB = 386lib $(FLIB) -REPLACE

ALL:   repdrv.obj reptask.obj inviogdc.obj repinit.obj gesrep.obj gdcdia.obj\
       gdcalld.obj gdcalls.obj

repdrv.obj:	$(DREP)\repdrv.asm 
        $(ML)   $(DREP)\$*.asm >$(ERR)
 	$(LIB)  $*.obj 


reptask.obj:	$(DREP)\reptask.c $(DREP)\gesrep.h $(DREP)\repgdc.h
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

inviogdc.obj:	$(DREP)\inviogdc.c $(DREP)\gesrep.h $(DREP)\repgdc.h
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

repinit.obj:	$(DREP)\repinit.c $(DREP)\gesrep.h 
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

gesrep.obj:	$(DREP)\gesrep.c $(DREP)\gesrep.h 
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

gdcdia.obj:	$(DREP)\gdcdia.c $(DREP)\repgdc.h 
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

gdcalld.obj:	$(DREP)\gdcalld.c $(DREP)\repgdc.h 
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

gdcalls.obj:	$(DREP)\gdcalls.c $(DREP)\repgdc.h 
         $(CL)  $(DREP)\$*.c > file.err
         WOMP   /fp $*.obj
         $(LIB) $*.obj

