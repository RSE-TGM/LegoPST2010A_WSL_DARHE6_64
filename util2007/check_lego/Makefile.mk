# ******* Telelogic expanded section *******
all: ../bin/check_lego

../bin/check_lego: check_lego.sh
	cp $? $@
	chmod a+x $@
