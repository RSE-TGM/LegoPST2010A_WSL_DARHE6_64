set SER=%LG_BIN%\LegoSim
set LEGO=%LG_LEGO%
set LIBUT=%LG_LIBUT%

set LIBS=unix.lib absRT0.lib kernel32.lib fio.lib fmath.lib comdlg32.lib libac.lib Wsock32.lib user32.lib 

lnk -out:lgser.exe %SER%\legoser.obj %LEGO%\legolib.lib %LIBUT%\moduli.lib %LEGO%\blaslib.lib %LEGO%\vapo.lib foraus.obj %LIBUT%\foraus_b.lib proc\ltm.obj %LIBS% -aliases:UNICODE.ALS
