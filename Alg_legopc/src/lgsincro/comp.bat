rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE;%INSTDIR%\Vc\mfc\include
set PATH=%INSTDIR%\SharedIDE\bin;%INSTDIR%\Vc\bin;%PATH%

nmake -f LgSincro.mak

copy  release\LgSincro.exe %target%\bin\legosim

REM WIN XP
REM copy /Y release\LgSincro.exe %target%\bin\legosim