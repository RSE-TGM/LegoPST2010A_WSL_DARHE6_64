#
#	Makefile Header:               Makefile
#       Subsystem:              28
#       Description:
#       %created_by:    zanna %
#       %date_created:  Mon Jun 17 11:53:36 1996 %
FFLAGS= $(F_FLAGS) 
SORGENTI_FOR= $(LEGOCAD_USER)/legocad/libut_reg/libreg/modrvar.f \
	      $(LEGOCAD_USER)/legocad/libut_reg/libreg/modrdat.f
OGGETTI_FOR= modrvar.o  \
	     modrdat.o
SORGENTI_C= $(LEGOCAD)/regoserver/regoserver.c 
$(LEGOCAD_USER)/legocad/libut_reg/libreg/regoserver: $(OGGETTI_FOR) $(SORGENTI_C)
	$(CC) $(SORGENTI_C) modrvar.o modrdat.o \
              $(LEGOCAD_USER)/legocad/libut_reg/libreg/reglib.a \
              $(LEGO_LIB)/legolib.a \
	      $(LEGO_LIB)/vapo.a -lm $(LIBOTS) $(FC_LIBS) -o $@

modrvar.o :  $(LEGOCAD_USER)/legocad/libut_reg/libreg/modrvar.f
	$(FC) $(F_FLAGS) -c $(LEGOCAD_USER)/legocad/libut_reg/libreg/modrvar.f
modrdat.o : $(LEGOCAD_USER)/legocad/libut_reg/libreg/modrdat.f
	$(FC) $(F_FLAGS) -c $(LEGOCAD_USER)/legocad/libut_reg/libreg/modrdat.f
