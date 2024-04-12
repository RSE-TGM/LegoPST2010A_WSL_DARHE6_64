@echo off
set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE
set PATH=%INSTDIR%\SharedIDE\bin;%PATH%
REM %INSTDIR%\Vc\bin\cl lmf.c snmpmac.cpp snmpapi.cpp ws2_32.lib
%INSTDIR%\Vc\bin\cl lmf.c ws2_32.lib ..\source\LIBS_DIR\legolib\legolib.lib

REM con absoft acc -windefs lmf.c Wsock32.lib ..\source\LIBS_DIR\legolib\legolib.lib

del *.obj

REM lmf.exe è locale