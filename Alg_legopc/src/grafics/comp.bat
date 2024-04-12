rem set INSTDIR=C:\Programmi\DevStudio
set LIB=%INSTDIR%\Vc\LIB
set INCLUDE=%INSTDIR%\Vc\INCLUDE;%INSTDIR%\Vc\mfc\include
set PATH=%INSTDIR%\SharedIDE\bin;%INSTDIR%\Vc\bin;%PATH%
nmake -f grafics.mak


copy bin\grafics.exe %target%\bin\grafics
REM WIN XP
REM copy /Y bin\grafics.exe %target%\bin\grafics