# ******* Telelogic expanded section *******

# make_macros from makefile "Makefile.mk-1"
all: ../bin/banner

../bin/banner: banner.c  config.h  letters.h
	$(CC) $(CFLAGS) -o $@ $? 
