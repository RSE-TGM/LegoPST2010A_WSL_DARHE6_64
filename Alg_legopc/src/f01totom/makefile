# ******* Telelogic expanded section *******

# make_macros from project "Alg_legopc-2007A1_RHE4_lomgr
#CFLAGS = -g -Wall
F_FLAGS=-fno-second-underscore -g -fno-automatic -finit-local-zero
CFLAGS = -Wall -DLinux
CC = gcc
TARGETBIN = ../../bin
LIBS =  -lm
INCLUDES =
SRCS = f01totom.c

all: ${TARGETBIN}/f01totom

# The variable $@ has the value of the target.
${TARGETBIN}/f01totom: f01totom.c
	${CC} ${CFLAGS} ${INCLUDES} -g -o $@ $? ${LIBS}


clean:
	rm *.o core *~
