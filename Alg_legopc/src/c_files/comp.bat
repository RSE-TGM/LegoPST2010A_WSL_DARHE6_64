REM @echo off

acc -windefs pag2f01.c  readconn.c User32.lib Wsock32.lib User32.lib ..\LIBS_DIR\legolib\legolib.lib
acc i32i5.c    readconn.c 

REM del *.obj

copy  i32i5.exe      %target%\bin\tools
copy  pag2f01.exe    %target%\bin\tools
REM WIN XP
REM copy /Y i32i5.exe      %target%\bin\tools
REM copy /Y pag2f01.exe    %target%\bin\tools