rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE;%INSTDIR%\Vc\mfc\include
set PATH=%INSTDIR%\SharedIDE\bin;%INSTDIR%\Vc\bin;%PATH%
nmake -f f01totom.mak


copy Release\f01totom.exe %target%\bin\Tools
REM WIN XP
REM copy /Y release\f01totom.exe %target%\bin\Tools