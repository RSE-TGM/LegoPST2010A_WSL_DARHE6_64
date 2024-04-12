rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE;%INSTDIR%\Vc\mfc\include
set PATH=%INSTDIR%\SharedIDE\bin;%INSTDIR%\Vc\bin;%PATH%
nmake -f LgConcil.mak

copy  release\LgConcil.exe %target%\bin\LgConcil

REM WIN XP
REM copy /Y release\LgConcil.exe %target%\bin\LgConcil