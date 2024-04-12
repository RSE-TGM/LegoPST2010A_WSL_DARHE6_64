#
#       Makefile Header:               %name%
#       Subsystem:              %subsystem%
#       Description:
#       %created_by:    %
#       %date_created:  %

#
FFLAGS= $(F_FLAGS) 
SORGENTI_FOR= $(LEGOCAD_USER)/legocad/libut/modi.f \
	      $(LEGOCAD_USER)/legocad/libut/forausbase.f 
OGGETTI_FOR= $(LEGOCAD_USER)/legocad/libut/modi.o \
	      $(LEGOCAD_USER)/legocad/libut/forausbase.o
SORGENTI_C= $(LEGOCAD)/legoserver/legoserver.c 
$(LEGOCAD_USER)/legocad/libut/legoserver: $(OGGETTI_FOR) $(SORGENTI_C)
	$(CC) $(SORGENTI_C) modi.o forausbase.o \
              $(LEGOCAD_USER)/legocad/libut/modulilib.a \
              $(CAD_LEGO_LIB)/clegolib.a \
	      $(LEGO_LIB)/vapo.a -lm $(LIBOTS) $(FC_LIBS) -o $@
