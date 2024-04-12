# ******* Telelogic expanded section *******

# make_macros from project "Alg_global-2007A1_RHE4_lomgr
#
#       Makefile Header:               Makefile.mk
#       Subsystem:              146
#       Description:
#       %created_by:    lomgr %
#       %date_created:  Mon Feb 19 16:09:30 2007 %
all:
	cd ./kprocedure; $(MAKE) -f Makefile.mk
	cd ./kutil; $(MAKE) -f Makefile.mk
	cd ./Alg_mmi/AlgLib; $(MAKE) -f Makefile.mk
	cd ./Alg_mmi; $(MAKE) -f Makefile.mk
	cd ./Alg_rt; $(MAKE) -f Makefile.mk
	cd ./legocad/lego_big; $(MAKE) -f Makefile.mk
	cd ./legocad; $(MAKE) -f Makefile.mk
	cd ./scada; $(MAKE) -f Makefile.mk
	cd ./util97; $(MAKE) -f Makefile.mk
	cd ./Alg_legopc; $(MAKE) -f Makefile.mk
	cd ./util2007; $(MAKE) -f Makefile.mk

