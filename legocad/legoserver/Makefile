#
#       Makefile Header:               Makefile
#       Subsystem:              27
#       Description:
#       %created_by:    lomgr %
#       %date_created:  Wed Jan 10 13:00:58 2001 %

#
FFLAGS= $(F_FLAGS) 
SORGENTI_FOR= $(LEGOCAD_USER)/legocad/libut/modi.f \
	      $(LEGOCAD_USER)/legocad/libut/forausbase.f 
OGGETTI_FOR= modi.o \
	     forausbase.o
SORGENTI_C= $(LEGOCAD)/legoserver/legoserver.c
$(LEGOCAD_USER)/legocad/libut/legoserver: $(OGGETTI_FOR) $(SORGENTI_C)
	$(CC) $(SORGENTI_C)  $(OGGETTI_FOR) \
              $(LEGOCAD_USER)/legocad/libut/modulilib.a \
               $(LEGOCAD_USER)/legocad/libut/auxlegolib.a $(LEGO_LIB)/clegolib.a \
	      $(LEGO_LIB)/vapo.a -lm $(LIBOTS) $(FC_LIBS) -o $@
forausbase.o : $(LEGOCAD_USER)/legocad/libut/forausbase.f
	$(FC) $(F_FLAGS) -c  $(LEGOCAD_USER)/legocad/libut/forausbase.f
modi.o : $(LEGOCAD_USER)/legocad/libut/modi.f
	$(FC) $(F_FLAGS) -c $(LEGOCAD_USER)/legocad/libut/modi.f
