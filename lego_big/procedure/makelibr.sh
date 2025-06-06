#!/bin/ksh
#
#  Script:                      makelibr.sh
#  Subsystem:           1
#  %version:            6 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Tue Apr  6 16:07:57 2004 %

.SUFFIXES:  .pf .o .f .c .sh .h .a
FFLAGS=$(F_FLAGS) 
CFLAGS=$(C_FLAGS) 
CFLIBS=$(FC_LIBS) 
ARFLAGS = rv

all: $(LIBRERIA)
	@echo "la lista  $(LISTA)"

$(LIBRERIA): $(LISTA)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@


.pf.f:
	/lib/cpp -P $(CPP_FLAGS) $(PREPROCESSOR_OPTIONS) $< >> $*.f
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
.f.o:
	$(FC) -c $(FFLAGS) $< -o $@	

.f.a:
	$(FC) $(FFLAGS) -c $< -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o
	ranlib $@  # Corretto: opera sul target corrente $@
	rm -f $*.o # Buona pratica: rimuovere l'oggetto intermedio se non serve più


