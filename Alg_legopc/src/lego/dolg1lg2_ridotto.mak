all: lg1_done.out

lg1_done.out: proc\f14.dat
	type nul: > lg1_done.out

proc\f14.dat: proc\lg2.exe
	proc\lg2.exe > lg2.out

proc\lg2.exe: proc\ltm.obj foraus.obj
	f77 -s -N109 -N3 $(LG_LEGO)\lg2.obj $(LG_LEGO)\legolib.lib proc\ltm.obj foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib $(LG_LEGO)\vapo.lib unix.lib -aliases:UNICODE.ALS
	if exist "proc\lg2.exe" del "proc\lg2.exe"
	copy lg2.exe proc\lg2.exe
        del lg2.exe

proc\ltm.obj: proc\ltm.for
	f77 -c -s -N109 -N3 proc\ltm.for
	if exist "proc\ltm.obj" del "proc\ltm.obj"
	copy ltm.obj proc\ltm.obj
        del ltm.obj

foraus.obj: foraus.for
	f77 -c -s -N109 -N3 foraus.for

foraus.for:
	if not exist "foraus.for" copy "$(LG_LIBUT)\foraus.for" "foraus.for"

proc\ltm.for: f01.dat
	$(LG_LEGO)\lg1.exe > lg1.out
	if exist "proc\ltm.for" del "proc\ltm.for"
	copy proc\ltm.f proc\ltm.for
        del proc\ltm.f
