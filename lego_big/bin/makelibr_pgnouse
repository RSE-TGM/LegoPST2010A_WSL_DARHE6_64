#!/bin/ksh
#
#  Script:                      makelibr_pgnouse.sh
#  Subsystem:           1
#  %version:            4 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Tue Mar 25 16:30:46 1997 %

# Compila il file fortran prodotto dallo schema senza
# inserirlo in libreria.
.SUFFIXES:  .pf .o .f .c .sh .h .a
FFLAGS=$(F_FLAGS) 
all: $(LISTA)

.f.a:
	$(FC) -c $(FFLAGS) $<

