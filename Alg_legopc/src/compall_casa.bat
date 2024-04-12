
REM---------------------------------------------------------------------------------------------
REM ------------ Procedura di compilazione di LegoPC -------------------------------------------
REM mettere a punto le definizioni delle variabili di ambiente legate i path dei compilatori! 
REM---------------------------------------------------------------------------------------------
REM Path base dei sorgenti da compilare
set base=H:\legopak\private\source

REM Path del kit LegoPC da aggiornare
set target=H:\legopak\public\legopc

REM Path del compilatore visual c++ 5
set INSTDIR=H:\Programmi\DevStudio

REM Path file di include del compilatore Absoft
set CCINCLUDE=H:\Absoft70\CINCLUDE 
REM----------------------------------------------------------------------------------------------

cd ..\lmf
cmd /x /c comp.bat
chdir
if errorlevel 1 goto enderrore
cd %base%


cd f22toascii\tradf22
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd Grafics
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd Inhoud
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd LegoSim\lgser
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd lgconcil
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd lgconcil\lgcser\lgclib
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd lgconcil\lgcser\main
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd lgSincro
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd libs_dir\blaslib
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd libs_dir\legolib
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd libs_dir\libsbtk
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd libs_dir\vapo
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd main_lego
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd newmod 
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd tables
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%


cd traduci
cmd /x /c comp.bat
chdir
rem pause
if errorlevel 1 goto enderrore 
cd %base%

cd C_files
cmd /x /c comp.bat
chdir
if errorlevel 1 goto enderrore 
cd %base%


goto end

:enderrore
chdir
echo ERRORE DI COMPILAZIONE

:end
echo  FINE REGOLARE






