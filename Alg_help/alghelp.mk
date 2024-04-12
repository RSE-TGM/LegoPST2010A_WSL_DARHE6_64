SORG_LG=legohelp.hpj
PROD_LG= $(ALG_HELP_BIN)/legohelp.hlp
SORG_GL=gloshelp.hpj
PROD_GL=$(ALG_HELP_BIN)/gloshelp.hlp
SORG_MMI=lmmihelp.hpj
PROD_MMI=$(ALG_HELP_BIN)/lmmihelp.hlp
SORG_SIMUL=simuhelp.hpj
PROD_SIMUL=$(ALG_HELP_BIN)/simuhelp.hlp
all: $(PROD_LG) $(PROD_GL) $(PROD_MMI) $(PROD_SIMUL)
$(PROD_LG): $(SORG_LG)
	echo $@ $< $*
	$(HYPER_BIN)/rtfhhc -v legohelp.hpj
	mv legohelp.hlp $@
$(PROD_GL): $(SORG_GL)
	$(HYPER_BIN)/rtfhhc -v gloshelp.hpj
	mv gloshelp.hlp $@
$(PROD_MMI): $(SORG_MMI)
	$(HYPER_BIN)/rtfhhc -v lmmihelp.hpj
	mv lmmihelp.hlp $@
$(PROD_SIMUL): $(SORG_SIMUL)
	$(HYPER_BIN)/rtfhhc -v simuhelp.hpj
	mv simuhelp.hlp $@

#	$(HYPER_BIN)/rtfhhc -v legohelp.hpj
#	mv legohelp.hlp $(ALG_HELP_BIN)
#	$(HYPER_BIN)/rtfhhc -v gloshelp.hpj
#	mv gloshelp.hlp $(ALG_HELP_BIN)
#	$(HYPER_BIN)/rtfhhc -v lmmihelp.hpj
#	mv lmmihelp.hlp $(ALG_HELP_BIN)
#	$(HYPER_BIN)/rtfhhc -v simuhelp.hpj
#	mv simuhelp.hlp $(ALG_HELP_BIN)

