@echo off
f77 -c -s -N109 -N3 *.for
f77 -c -s -N3 wgsab.for
rem acc -c  snmpapi.cpp snmpmac.cpp 
acc -c -windefs LManager.c prep_f22.c

REM REM set INSTDIR=C:\Programmi\DevStudio
REM set LIB=%INSTDIR%\Vc\LIB
REM set INCLUDE=%INSTDIR%\Vc\INCLUDE
REM set PATH=%INSTDIR%\SharedIDE\bin;%PATH%
REM %INSTDIR%\Vc\bin\cl -c snmpmac.cpp snmpapi.cpp

acc -c   -windefs snmpapi.cpp snmpmac.cpp 

lb /out:legolib.lib *.obj
del *.obj
