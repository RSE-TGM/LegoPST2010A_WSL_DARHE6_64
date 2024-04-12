default: all

all: lg2_done.out

lg2_done.out: proc/f03.dat
	touch lg2_done.out

proc/f03.dat: proc/f02.dat
	proc/lg2 > lg2.out

proc/f02.dat: f01.dat
	$(LEGOCAD_BIN)/lg1 > lg1.out
	rm -f proc/ltm.f