@echo off
rem set CCINCLUDE=C:\Programmi\Absoft70\CINCLUDE
f77 -c -N109 -N3 *.for
f77 -c -N3 wgsab.for
acc -c -I"%CCINCLUDE%" -D_WIN32 -D_X86_ auxfuns.c
lb /out:LgCLib.lib *.obj
del *.obj

copy   LgCLib.lib %target%\bin\LgConcil

REM WIN XP
REM copy  /Y LgCLib.lib %target%\bin\LgConcil