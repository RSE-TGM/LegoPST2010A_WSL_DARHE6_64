#!/bin/ksh
#
#  Script:                      cad_environment.sh
#  Subsystem:           1
#  %version:            3 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 16:58:40 1997 %

#
# cad_environment : crea l'ambiente per un nuovo utente legocad.
#
#
DIR_LEGOCAD= $(LEGOCAD_USER)/legocad $(LEGOCAD_USER)/legocad/libut \
          $(LEGOCAD_USER)/legocad/libut_reg \
          $(LEGOCAD_USER)/legocad/libut_reg/libreg
crea_libut:
	cd $(LEGOCAD_USER)/legocad/libut; cad_crealibut
crea_libreg:
	cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; cad_crealibreg
crea_libut_reg:
	cd $(LEGOCAD_USER)/legocad/libut_reg; crealibut_reg 
copia_all: $(DIR_LEGOCAD)
	cp $(PROCLIB)/general/*.f $(LEGOCAD_USER)/legocad/libut
	cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.f
	cp $(PROCLIB)/general/*.bmp $(LEGOCAD_USER)/legocad/libut
	-cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.bmp
	cp $(PROCLIB)/general/*.dat $(LEGOCAD_USER)/legocad/libut
	cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.dat
	cp $(PROCLIB)/base/*.f $(LEGOCAD_USER)/legocad/libut
	cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.f
	-cp $(PROCLIB)/base/*.doc $(LEGOCAD_USER)/legocad/libut
	-cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.doc
	-cp $(PROCLIB)/base/*.bmp $(LEGOCAD_USER)/legocad/libut
	-cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.bmp
	cp $(PROCLIB)/base/*.dat $(LEGOCAD_USER)/legocad/libut
	cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.dat
	cp $(REGOLIB)/regola/*.f $(LEGOCAD_USER)/legocad/libut_reg/libreg
	cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; chmod +w *.f
	-cp $(REGOLIB)/regola/*.doc $(LEGOCAD_USER)/legocad/libut_reg/libreg
	-cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; chmod +w *.doc
	cp $(REGOLIB)/regola/lista_moduli_reg.dat \
           $(LEGOCAD_USER)/legocad/libut_reg/libreg
	cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; chmod +w lista_moduli_reg.dat
	@echo 'Done'
copia_libut:
	cp $(PROCLIB)/base/*.f $(LEGOCAD_USER)/legocad/libut
	cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.f
	-cp $(PROCLIB)/base/*.doc $(LEGOCAD_USER)/legocad/libut
	-cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.doc
	-cp $(PROCLIB)/base/*.bmp $(LEGOCAD_USER)/legocad/libut
	-cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.bmp
	cp $(PROCLIB)/base/*.dat $(LEGOCAD_USER)/legocad/libut
	cd $(LEGOCAD_USER)/legocad/libut; chmod +w *.dat
	@echo 'Done'
copia_libreg:
	cp $(REGOLIB)/regola/*.f $(LEGOCAD_USER)/legocad/libut_reg/libreg
	cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; chmod +w *.f
	-cp $(REGOLIB)/regola/*.doc $(LEGOCAD_USER)/legocad/libut_reg/libreg
	-cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; chmod +w *.doc
	cp $(REGOLIB)/regola/lista_moduli_reg.dat \
           $(LEGOCAD_USER)/legocad/libut_reg/libreg
	cd $(LEGOCAD_USER)/legocad/libut_reg/libreg; chmod +w lista_moduli_reg.dat
	@echo 'Done'
#
# crea le directory necessarie all'ambiente legocad e 
# crea ifile di lista vuoti
#
crea_dir: $(DIR_LEGOCAD)
$(LEGOCAD_USER)/legocad:
	touch $(LEGOCAD_USER)/filtri.edf
	mkdir $(LEGOCAD_USER)/legocad
$(LEGOCAD_USER)/legocad/libut:
	touch $(LEGOCAD_USER)/filtri.edf
	mkdir $(LEGOCAD_USER)/legocad/libut
	cp $(PROCLIB)/general/*.f $(LEGOCAD_USER)/legocad/libut
	touch $(LEGOCAD_USER)/legocad/libut/lista_moduli.dat
	touch $(LEGOCAD_USER)/legocad/libut/icon_list.dat
	chmod +w  $(LEGOCAD_USER)/legocad/libut/*.f
	cp $(PROCLIB)/general/*.dat $(LEGOCAD_USER)/legocad/libut
	cp $(PROCLIB)/general/*.bmp $(LEGOCAD_USER)/legocad/libut
	chmod +w $(LEGOCAD_USER)/legocad/libut/*.dat
	chmod +w $(LEGOCAD_USER)/legocad/libut/*.bmp
$(LEGOCAD_USER)/legocad/libut_reg:
	mkdir $(LEGOCAD_USER)/legocad/libut_reg
	touch $(LEGOCAD_USER)/legocad/libut_reg/lista_schemi.dat
$(LEGOCAD_USER)/legocad/libut_reg/libreg:
	mkdir $(LEGOCAD_USER)/legocad/libut_reg/libreg
	touch $(LEGOCAD_USER)/legocad/libut_reg/libreg/lista_moduli_reg.dat
	chmod +w $(LEGOCAD_USER)/legocad/libut_reg/libreg/lista_moduli_reg.dat
	@echo 'Done'
#
# copia di un modello
#
# le touch servono per verificare 
# la accessibilita ai direttori dest e sorg
#
copy_model:  $(DIR_SOURCE_MODEL)/..  $(DIR_DEST_MODEL)/..
	@echo 'Copy Model'
	cp $(DIR_SOURCE_MODEL)/f01.dat $(DIR_DEST_MODEL)
	cp $(DIR_SOURCE_MODEL)/f14.dat $(DIR_DEST_MODEL)
	cp $(DIR_SOURCE_MODEL)/macroblocks.dat $(DIR_DEST_MODEL)
	cp $(DIR_SOURCE_MODEL)/foraus.for $(DIR_DEST_MODEL)
	cp $(DIR_SOURCE_MODEL)/foraus.f $(DIR_DEST_MODEL)
	cp $(DIR_SOURCE_MODEL)/forausbase.f $(DIR_DEST_MODEL)
	cp $(DIR_SOURCE_MODEL)/descr.dat $(DIR_DEST_MODEL)
	@echo 'Done'
