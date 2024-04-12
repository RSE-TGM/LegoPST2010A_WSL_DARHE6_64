rem @echo off
rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE
set PATH=%INSTDIR%\SharedIDE\bin;%PATH%
%INSTDIR%\Vc\bin\cl /c -nologo *.c
%INSTDIR%\VC\bin\lib *.obj /OUT:Blaslib.lib

copy  Blaslib.lib    %target%\bin\lego
REM WIN XP
REM copy /Y Blaslib.lib    %target%\bin\lego
