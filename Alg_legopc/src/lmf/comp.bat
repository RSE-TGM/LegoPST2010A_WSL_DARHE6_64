@echo off

acc -windefs lmf.c Wsock32.lib ..\source\LIBS_DIR\legolib\legolib.lib

del *.obj

REM lmf.exe è locale