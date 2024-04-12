#!/bin/ksh
#
#  Script:                      cad_marcotask.sh
#  Subsystem:           1
#  %version:            6 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Mar 23 15:37:54 2005 %

# Makefile per la nuova attivita (regolazione semplificata) LG1 del codice LEGO.
# DECFFLAGS= -fpe3
# IBMFFLAGS= -O -qextname

FFLAGS= $(F_FLAGS)

#######################################
# Sezione  S K E D   R G 5 
#######################################
rg5sk: proc/first proc/rg5sk

proc/rg5sk : proc/f04.dat
	$(FC) $(FFLAGS) $(LEGO)/sorglego/main/main_rg5sk.o \
	$(REGO_LIB)/rg5sim.o proc/ltm.o \
        proc/schemi_reg.a ../libut_reg/libreg/reglib.a $(REGO_LIB)/regonew.a \
        $(LEGORT_LIB)/libsim.a $(LEGORT_LIB)/libipc.a $(LEGORT_LIB)/libnet.a\
        $(LEGOROOT_LIB)/libutil.a $(LEGOROOT_LIB)/libRt.a \
	$(LEGORT_LIB)/libsim.a  $(LEGO_LIB)/vapo.a $(ALG_FPE_OBJ) -o  proc/lg5sk
#	rm -f rg5sk.o ltm.o
	cat $(LEGO)/procedure/S01.tpl | sed  "s/LEGOCAD/`cad_curdir R`/g" \
	| sed  "s/ALG_TASK_TYPE_FLAG/R/g" > S01
	chmod a+w S01
	net_compi

#######################################
# Sezione regime
#######################################
proc/f04.dat: proc/pslego3 f14.dat
	proc/pslego3 f01.dat f14.dat
	mv ./F04.dat proc/f04.dat
	mv ./n04.dat proc/n04.dat


proc/pslego3: proc/ltm.o proc/schemi_reg.a ../libut_reg/libreg/reglib.a
	$(CC) $(CFLAGS) -o proc/pslego3  $(REGO_LIB)/pslego3.o proc/ltm.o \
	proc/schemi_reg.a ../libut_reg/libreg/reglib.a $(REGO_LIB)/regonew.a \
	$(LEGO_LIB)/vapo.a $(FC_LIBS)  $(ALG_FPE_OBJ)


proc/ltm.o: proc/ltm.f
	$(FC) $(FFLAGS) -c proc/ltm.f
	mv ltm.o proc/ltm.o


proc/ltm.f: f01.dat
	crealtm
	mv ltm.f proc/ltm.f
	rm crealtm.dat
