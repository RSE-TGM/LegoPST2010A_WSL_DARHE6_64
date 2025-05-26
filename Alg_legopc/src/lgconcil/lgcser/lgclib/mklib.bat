@echo off
set CINCLUDE=C:\Programmi\Absoft70\CINCLUDE
rem solo Windows
f77 -c -N109 -N3 *.for
f77 -c -N3 wgsab.for
acc -c -I"%CINCLUDE%" -D_WIN32 -D_X86_ auxfuns.c
lb /out:LgCLib.lib *.obj
del *.obj
