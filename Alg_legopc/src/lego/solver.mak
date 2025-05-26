lg3: proc\nssls.exe

lg5: proc\lg5.exe

proc\nssls.exe: proc\ltm.obj foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib
	gfortran  $(LG_LEGO)\lg3.obj  proc\ltm.obj $(LG_LEGO)\legolib.lib\
		foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib \
		$(LG_LEGO)\vapo.lib $(LG_LEGO)\libsbtk.lib $(LG_LEGO)\blaslib.lib \
		Wsock32.lib User32.lib unix.lib -aliases:UNICODE.ALS -o lg3.exe
	copy lg3.exe proc\nssls.exe
	del lg3.exe
#	f77 -s -N109 -N3  $(LG_LEGO)\lg3.obj  proc\ltm.obj $(LG_LEGO)\legolib.lib\
#		foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib \
#		$(LG_LEGO)\vapo.lib $(LG_LEGO)\libsbtk.lib $(LG_LEGO)\blaslib.lib \
#		Wsock32.lib User32.lib unix.lib -aliases:UNICODE.ALS

proc\lg5.exe: proc\ltm.obj foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib
	f77 -s -N109 -N3 $(LG_LEGO)\lg5.obj $(LG_LEGO)\legolib.lib proc\ltm.obj \
		foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib \
		$(LG_LEGO)\vapo.lib $(LG_LEGO)\blaslib.lib \
		Wsock32.lib User32.lib unix.lib -aliases:UNICODE.ALS
	copy lg5.exe proc\lg5.exe
	del lg5.exe
# f77 -s -N109 -N3 $(LG_LEGO)\lg5.obj $(LG_LEGO)\legolib.lib proc\ltm.obj \
# 	foraus.obj $(LG_LIBUT)\moduli.lib $(LG_LIBUT)\foraus_b.lib \
# 	$(LG_LEGO)\vapo.lib $(LG_LEGO)\blaslib.lib \
# 	Wsock32.lib User32.lib unix.lib -aliases:UNICODE.ALS
