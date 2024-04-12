rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE;%INSTDIR%\Vc\mfc\include
set PATH=%INSTDIR%\SharedIDE\bin;%INSTDIR%\Vc\bin;%PATH%
nmake -f inhoud.mak

copy  debug\inhoud.exe %target%\bin\tools

REM WIN XP
REM copy /Y debug\inhoud.exe %target%\bin\tools