rem set INSTDIR=D:\Programmi\DevStudio
REM set LIB=%INSTDIR%\Vc\LIB
REMset INCLUDE=%INSTDIR%\Vc\INCLUDE
REM set PATH=%INSTDIR%\SharedIDE\bin;%PATH%
REM %INSTDIR%\Vc\bin\cl Tradf22.c
REM del *.obj


REM acc Tradf22.c User32.lib Wsock32.lib 

acc -windefs Tradf22.c User32.lib

REM del *.obj

copy  Tradf22.exe      %target%\bin\lego

REM WIN XP
REM copy /Y i32i5.exe      %target%\bin\tools
REM copy /Y pag2f01.exe    %target%\bin\tools