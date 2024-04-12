rem set CCINCLUDE=C:\Programmi\Absoft70\CINCLUDE
acc -c -I"%CCINCLUDE%" -D_WIN32 -D_X86_ LgCSer.c


copy   LgCSer.obj %target%\bin\LgConcil

REM WIN XP
REM copy  /Y LgCSer.obj %target%\bin\LgConcil