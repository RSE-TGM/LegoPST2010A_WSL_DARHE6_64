cmd /x /c crea_obj.bat

copy  legoser.obj %target%\bin\legosim
copy  dolgser.bat %target%\bin\legosim

REM WIN XP
REM copy /Y legoser.obj %target%\bin\legosim
REM copy /Y dolgser.bat %target%\bin\legosim