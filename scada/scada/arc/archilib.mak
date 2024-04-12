##############################################################
#
#  29-09-1993
#  ----------	
#	ARCHlib.MAK
#	
#	makefile moduli per archiviazione 
#       
#       NB non sono aggiornati per la versione AC_SIMULATORE
#
# i moduli arcwai.c arcfind.c e arcfile.c sono compilati con la condizione
# #ifdef AC_SIMULATORE. E' stato tolto il riferimento da PSCS.CFG per cui
# per generare una versione per il simulatore e' necessario definire tale
# valore in attivazione : nmake SIM=-DAC_SIMULATORE archlib.mak
#
#############################################################

!include \PSCS32\cflag.inc


# -- parametri necessari al < C >


CSRC = \pscs32\scada	        		# directory sorgenti C 	scada
INCTCP=   \pscs32\tcp
CINCC= \pscs32\incl	               	    	# include C
CINCSIM= \pscs32\incl\sim


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D) -I$(CINCC) -I$(CSRC)\$(WORK) 
CL1=$(CC) $(CFLAGS_D) -I$(CINCC) -I$(CINCSIM) -I$(CSRC)\$(WORK) $(SIM)
!ELSE
CL= $(CC) -I$(CINCC) -I$(CSRC)\$(WORK)
CL1=$(CC) -I$(CINCC) -I$(CINCSIM) -I$(CSRC)\$(WORK) $(SIM)
!ENDIF


# -- parametri necessari per la gestione files errori

ERR= file.err

FLIB= \PSCS32\LIB\LIBARCHI.LIB   # nome della libreria
LIB =386LIB $(FLIB) -REPLACE

ALL : arcopen.obj arcwai.obj arcwr.obj arcfnom.obj arcfile.obj arclen.obj arcrac.obj\
      arcana.obj arcdig.obj arcave.obj arctrig.obj arcread.obj arcfind.obj arctabin.obj\
      arctab.obj arcind.obj arcpar.obj arcvis.obj arctrend.obj arcdia.obj arcflop.obj arctrc.obj\
      arcsec.obj


# -- generazione oggetti <archivi>
# ------------------------------
WORK= arc

arcopen.obj:	$(CSRC)\$(WORK)\arcopen.c $(CSRC)\$(WORK)\arc.inc\
                $(CINCC)\dconf.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcwai.obj:	$(CSRC)\$(WORK)\arcwai.c $(CSRC)\$(WORK)\arc.inc\
                $(CSRC)\$(WORK)\arctab.inc  $(CINCC)\diagnoan.inc
	$(CL1)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcwr.obj:	$(CSRC)\$(WORK)\arcwr.c $(CSRC)\$(WORK)\arc.inc\
                $(CINCC)\dconf.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcfnom.obj:	$(CSRC)\$(WORK)\arcfnom.c $(CSRC)\$(WORK)\arc.inc\
                $(CINCC)\dconf.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcfile.obj:	$(CSRC)\$(WORK)\arcfile.c $(CSRC)\$(WORK)\arc.inc\
                $(CINCC)\g2comdb.inc\
                $(CINCC)\diagnoan.inc  $(CINCC)\dconf.inc
	$(CL1)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arclen.obj:	$(CSRC)\$(WORK)\arclen.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcrac.obj:	$(CSRC)\$(WORK)\arcrac.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcana.obj:	$(CSRC)\$(WORK)\arcana.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcdig.obj:	$(CSRC)\$(WORK)\arcdig.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcave.obj:	$(CSRC)\$(WORK)\arcave.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arctrig.obj:	$(CSRC)\$(WORK)\arctrig.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcread.obj:	$(CSRC)\$(WORK)\arcread.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcfind.obj:	$(CSRC)\$(WORK)\arcfind.c $(CSRC)\$(WORK)\arc.inc
	$(CL1)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arctabin.obj:	$(CSRC)\$(WORK)\arctabin.c $(CSRC)\$(WORK)\arc.inc\
                $(CSRC)\$(WORK)\arctab.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arctab.obj:	$(CSRC)\$(WORK)\arctab.c $(CSRC)\$(WORK)\arc.inc\
                $(CSRC)\$(WORK)\arctab.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcind.obj:	$(CSRC)\$(WORK)\arcind.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcpar.obj:	$(CSRC)\$(WORK)\arcpar.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcvis.obj:	$(CSRC)\$(WORK)\arcvis.c $(CSRC)\$(WORK)\arc.inc\
                $(CSRC)\$(WORK)\arcvis.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arctrend.obj:	$(CSRC)\$(WORK)\arctrend.c $(CSRC)\$(WORK)\arc.inc\
                $(CSRC)\$(WORK)\arcvis.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcdia.obj:	$(CSRC)\$(WORK)\arcdia.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcflop.obj:	$(CSRC)\$(WORK)\arcflop.c $(CSRC)\$(WORK)\arcvis.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arctrc.obj:	$(CSRC)\$(WORK)\arctrc.c $(CSRC)\$(WORK)\arcvis.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj

arcsec.obj:	$(CSRC)\$(WORK)\arcsec.c $(CSRC)\$(WORK)\arc.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
	!@womp    /fp	$*.obj
	$(LIB)  $*.obj




