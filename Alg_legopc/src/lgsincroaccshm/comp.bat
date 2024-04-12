rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE;%INSTDIR%\Vc\mfc\include
set PATH=%INSTDIR%\SharedIDE\bin;%INSTDIR%\Vc\bin;%PATH%
nmake -f LgSincroAccShM.mak

copy  release\LgSincroAccShM.exe %target%\bin\legosim

REM WIN XP
REM copy /Y release\LgSincroAccShM.exe %target%\bin\legosim