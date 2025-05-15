# ******* Telelogic expanded section *******

# make_macros from project "Alg_legopc-2007A1_RHE4_lomgr
#CFLAGS = -g -Wall
#F_FLAGS=-fno-second-underscore -g -fno-automatic -finit-local-zero
CFLAGS = -Wall -DLinux
CC = gcc
#CCM_MAKE_LOCAL=cp

PREFIXBIN= ../../bin/


SHELLFILES= rerunlg2.bat rerunlg2.mak

SHELLBIN=$(PREFIXBIN)rerunlg2.bat $(PREFIXBIN)rerunlg2.mak


all: $(SHELLBIN) Makefile.mk

debug:
	echo $(SHELLFILES)
	echo $(SHELLBIN)


#$(PREFIXBIN)%.tix: %.tix
#	cp %.tix $(PREFIXBIN)


$(PREFIXBIN)rerunlg2.bat         : rerunlg2.bat
	cp $? $(PREFIXBIN)
$(PREFIXBIN)rerunlg2.mak         : rerunlg2.mak
	cp $? $(PREFIXBIN)
