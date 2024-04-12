# ******* Telelogic expanded section *******

# make_macros from project "Alg_legopc-2007A1_RHE4_lomgr
#CFLAGS = -g -Wall
F_FLAGS=-fno-second-underscore -g -fno-automatic -finit-local-zero
CFLAGS = -Wall -DLinux
CC = gcc
TARGETBIN = ../../bin
LIBS =  -lm 
INCLUDES =
OBJS = readconn.o
SRCS = i32i5.c pag2f01.c  readconn.c 
HDRS = i32i5.h pag2f01.h  


all: ${TARGETBIN}/i32i5 ${TARGETBIN}/pag2f01

# The variable $@ has the value of the target. 
${TARGETBIN}/i32i5: i32i5.c ${OBJS} ${HDRS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ i32i5.c ${OBJS} ${LIBS}

${TARGETBIN}/pag2f01: pag2f01.o ${OBJS} pag2f01.h
	${CC} ${CFLAGS} -o $@ pag2f01.c ${OBJS} ${LIBS}

.c.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<


clean:
	rm *.o core *~


