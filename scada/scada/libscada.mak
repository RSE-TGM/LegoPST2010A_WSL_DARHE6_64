#############################################################
#
#  9-09-1993
#  ----------	
#	SCDLIB.MAK
#	
#	makefile moduli per SCADA
#
#############################################################

UT=
DEB=

PROT=CF1		# tipo di protezione scheda MATROX

!include \PSCS32\cflag.inc

# -- parametri necessari al < ASM >

ASMSRC=   \pscs32\scada

ASMINC=   \pscs32\marte
ASMSW=    \pscs32\incl

!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
ML = $(ASM) $(AFLAGS_D) -I$(ASMINC) -I$(ASMSW)
!ELSE
ML = $(ASM) -I$(ASMINC) -I$(ASMSW)
!ENDIF

# -- parametri necessari al < C >

DPROT= \pscs32\prot
DHASP= \pscs32\hasp

CSRC = \pscs32\scada	        		# directory sorgenti C 	scada
INCTCP=   \pscs32\tcp
CINCC= \pscs32\incl	               	    	# include C


!IF ("$(DEBUG)"=="D" || "$(DEBUG)"=="d")
CL= $(CC) $(CFLAGS_D)  -I$(CINCC) -I$(INCTCP) -I$(CSRC)\$(WORK) 
!ELSE
CL= $(CC)  -I$(CINCC)  -I$(INCTCP) -I$(CSRC)\$(WORK)
!ENDIF

# -- parametri necessari per la gestione files errori

ERR= file.err
FLIB= \PSCS32\LIB\LIBSCADA.LIB                # nome della libreria
LIB = 386lib  $(FLIB) -REPLACE



ALL:  wrdb.obj rdpb.obj get_key.obj scan_arg.obj cmostime.obj biosdate.obj\
      riderr.obj init.obj\
      stamal.obj printal.obj printar.obj printele.obj stampe.obj intesta.obj\
      testlbg.obj\
      timeor.obj  initor.obj calcor.obj asinct.obj inibiz.obj calcdi.obj\
      calcort.obj calcdit.obj calcau.obj printalt.obj verifalt.obj stamalt.obj\
      verifall.obj exall.obj exfa.obj rtdebug.obj\
      vsoglia.obj gesele.obj descriz.obj descrizw.obj modpun.obj hostfio.obj msoglia.obj\
      fsoglia.obj taggcfg.obj diagnet.obj tcpmaste.obj dsioc.obj hostfiow.obj rwritewi.obj hcwin.obj\
      thcwin.obj mmidbl.obj tabfound.obj trfile.obj haspinit.obj haspqry.obj haspwc.obj hasp32b.obj



# -------------------------------------------------
# -- generazione oggetti WRDB
# -------------------------------------------------

WORK=.

wrdb.obj:	$(CSRC)\wrdb.c $(CINCC)\dconf.inc
	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -------------------------------------------------
# -- generazione oggetti utility 
# -------------------------------------------------

rdpb.obj:	$(CSRC)\rdpb.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

get_key.obj:	$(CSRC)\get_key.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -------------------------------------------------
# -- generazione oggetti riguardandi funzioni SCADA
# -------------------------------------------------

scan_arg.obj:	$(CSRC)\scan_arg.c
	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

#  $(FLIB)::	$(CSRC)\set_tdos.c
#    	$(CL)   $(CSRC)\set_tdos  > $(ERR)
#            !@womp /fp set_tdos.obj
#    	$(LIB)  set_tdos.obj
#    	del     set_tdos.obj

cmostime.obj:       $(CSRC)\cmostime.asm
	$(ML)   $(CSRC)\$*.asm  > $(ERR)
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

biosdate.obj:       $(CSRC)\biosdate.asm
	$(ML)   $(CSRC)\$*.asm  > $(ERR)
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

#$(FLIB)::	$(CSRC)\PSCSWD.C
#	$(CL)   $(CSRC)\PSCSWD  > $(ERR)
#        !@womp /fp PSCSWD.obj
#	$(LIB)  PSCSWD.obj
#	del     PSCSWD.obj

riderr.obj:	$(CSRC)\riderr.asm
	$(ML)   $(CSRC)\$*.asm 
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

init.obj:	$(CSRC)\init.c $(CINCC)\allstr.inc\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		$(CINCC)\messcada.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\tipal.inc $(CINCC)\ttipal.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

#$(FLIB)::	$(CSRC)\initdb.c $(CINCC)\allstr.inc\
#		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
#		$(CINCC)\messcada.inc $(CINCC)\comunic.inc\
#		$(CINCC)\fileop.inc $(CINCC)\tipal.inc $(CINCC)\ttipal.inc\
#		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
#		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
#	$(CL)   $(CSRC)\initdb  > $(ERR)
#        !@womp /fp initdb.obj
#	$(LIB)  initdb.obj
#	del     initdb.obj

#$(FLIB)::	$(CSRC)\pscsini.c $(CINCC)\allstr.inc\
#		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
#		$(CINCC)\messcada.inc $(CINCC)\comunic.inc\
#		$(CINCC)\fileop.inc $(CINCC)\tipal.inc $(CINCC)\ttipal.inc\
#		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
#		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
#	$(CL)   $(CSRC)\pscsini  > $(ERR)
#        !@womp /fp pscsini.obj
#	$(LIB)  pscsini.obj
#	del     pscsini.obj

# -- generazione oggetti <STAMPE>
# -------------------------------

WORK= stampe

stamal.obj:	$(CSRC)\$(WORK)\stamal.c $(CINCC)\allstr.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

printal.obj:	$(CSRC)\$(WORK)\printal.c $(CINCC)\allstr.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

printar.obj:	$(CSRC)\$(WORK)\printar.c $(CINCC)\allstr.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

printele.obj:	$(CSRC)\$(WORK)\printele.c $(CINCC)\allstr.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

stampe.obj:	$(CSRC)\$(WORK)\stampe.c $(CINCC)\allstr.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

intesta.obj:	$(CSRC)\$(WORK)\intesta.c $(CINCC)\allstr.inc\
		$(CSRC)\$(WORK)\intesta.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

testlbg.obj:	$(CSRC)\$(WORK)\testlbg.c\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

printalt.obj:	$(CSRC)\$(WORK)\printalt.c $(CINCC)\allstr.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

stamalt.obj:	$(CSRC)\$(WORK)\stamalt.c $(CINCC)\allstr.inc\
		$(CINCC)\g2comdb.inc $(CINCC)\dconf.inc\
		$(CINCC)\mestampe.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CINCC)\print.inc\
		$(CINCC)\allar.inc $(CINCC)\diagnodi.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL)   $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB


# -- generazione oggetti <ATTIPER>
# --------------------------------

WORK= attiper

timeor.obj:	$(CSRC)\$(WORK)\timeor.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g1tipdb.inc
	$(CL) -I$(CSRC)\$(WORK)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

#$(FLIB)::	$(CSRC)\$(WORK)\attiper.c\
#		$(CINCC)\g2comdb.inc\
#		$(CINCC)\g1tipdb.inc $(CCFGSW)\pscs.cfg 
#	$(CL)   -I$(CSRC)\$(WORK) $(CSRC)\$(WORK)\attiper  > $(ERR)
#        !@womp  /fp attiper.obj
#	$(LIB)  attiper.obj
#	del     attiper.obj

initor.obj:	$(CSRC)\$(WORK)\initor.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g1tipdb.inc
	$(CL) -I$(CSRC)\$(WORK)  $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetti <DIGOR>
# ------------------------------

WORK= digor

calcor.obj:    $(CSRC)\$(WORK)\calcor.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

asinct.obj:	$(CSRC)\$(WORK)\asinct.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

inibiz.obj:	$(CSRC)\$(WORK)\inibiz.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

calcdi.obj:	$(CSRC)\$(WORK)\calcdi.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

calcort.obj:	$(CSRC)\$(WORK)\calcort.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) -I$(CSRC)\attiper $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB
calcdit.obj:	$(CSRC)\$(WORK)\calcdit.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

calcau.obj:	$(CSRC)\$(WORK)\calcau.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetti <ACQUI>
# ------------------------------

WORK= acqui

verifall.obj:	$(CSRC)\$(WORK)\verifall.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

verifalt.obj:	$(CSRC)\$(WORK)\verifalt.c\
		$(CINCC)\g2comdb.inc $(CINCC)\messcada.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetti debugger RT
# ----------------------------------

rtdebug.obj:	$(CSRC)\rtdebug.c
	$(CL) $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetti <PROCV>
# ------------------------------

WORK= procv

vsoglia.obj:	$(CSRC)\$(WORK)\vsoglia.c\
		$(CINCC)\g2comdb.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB


gesele.obj:	$(CSRC)\$(WORK)\GESELE.c $(CINCC)\allstr.inc\
		$(CINCC)\ALLAR.inc\
		$(CINCC)\MESTAMPE.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

descriz.obj:	$(CSRC)\$(WORK)\descriz.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

descrizw.obj:	$(CSRC)\$(WORK)\descrizw.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

mmidbl.obj:	$(CSRC)\$(WORK)\mmidbl.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

modpun.obj:	$(CSRC)\$(WORK)\modpun.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

trfile.obj:	$(CSRC)\$(WORK)\trfile.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

tabfound.obj:	$(CSRC)\$(WORK)\tabfound.c
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

rwritewi.obj:	$(CSRC)\$(WORK)\rwritewi.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

hostfio.obj:	$(CSRC)\$(WORK)\hostfio.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

hostfiow.obj:	$(CSRC)\$(WORK)\hostfiow.c\
		$(CINCC)\g2comdb.inc $(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

hcwin.obj:	$(CSRC)\$(WORK)\hcwin.c\
		$(CINCC)\mesprocv.inc\
		$(CINCC)\g1tipdb.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

thcwin.obj:	$(CSRC)\$(WORK)\thcwin.c\
		$(CINCC)\mesprocv.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

msoglia.obj:	$(CSRC)\$(WORK)\msoglia.c $(CINCC)\allstr.inc\
		$(CINCC)\mesprocv.inc $(CINCC)\tipal.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

fsoglia.obj:	$(CSRC)\$(WORK)\fsoglia.c\
		$(CINCC)\mesprocv.inc $(CINCC)\tipal.inc
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

exall.obj:	$(CSRC)\$(WORK)\exall.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

exfa.obj:	$(CSRC)\$(WORK)\exfa.c\
		$(CINCC)\g2comdb.inc $(CINCC)\g1tipdb.inc 
	$(CL) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetti <AGGCFG>
# --------------------------------
WORK= aggcfg\

taggcfg.obj:	$(CSRC)\$(WORK)\taggcfg.c\
		$(CINCC)\dconf.inc $(CINCC)\g2comdb.inc\
		$(CINCC)\messcada.inc $(CINCC)\comunic.inc\
		$(CINCC)\fileop.inc $(CSRC)\$(WORK)\aggcfg.inc\
             	$(CINCC)\diagnodi.inc $(CINCC)\g1tipdb.inc
        $(CL)   -I$(CSRC)\$(WORK) $(CSRC)\$(WORK)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetto <diagnet>
# --------------------------------
WORK=.

diagnet.obj:	$(CSRC)\diagnet.c  $(INCTCP)\netmsg.h
	$(CL) $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

tcpmaste.obj:	$(CSRC)\tcpmaste.c 
	$(CL) $(CSRC)\$*.c  > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

# -- generazione oggetti <prot>
# ------------------------------

dsioc.obj:	$(DPROT)\dsioc.asm
        $(ML)   $(DPROT)\$*.asm > $(ERR)
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB


# -- generazione oggetti <hasp>
# ------------------------------

haspinit.obj:	$(DHASP)\haspinit.c
        $(CL)   $(DHASP)\$*.c > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

haspqry.obj:	$(DHASP)\haspqry.c
        $(CL)   $(DHASP)\$*.c > $(ERR)
        !@womp /fp $*.obj
	$(LIB)  $*.obj
        del .\LIBSCADA.LIB

haspwc.obj:	
	$(LIB)  $(DHASP)\haspwc.obj
        del .\LIBSCADA.LIB

hasp32b.obj:	
	$(LIB)  $(DHASP)\hasp32b.obj
        del .\LIBSCADA.LIB

