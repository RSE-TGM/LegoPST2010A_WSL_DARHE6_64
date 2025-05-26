
REM solo Windows
f77    -s -N109 -N3 edi14.for
f77    -s -N109 -N3 lg1.for ..\libs_dir\legolib\legolib.lib
f77 -c -s -N109 -N3 lg2.for
f77 -c -s -N109 -N3 lg3.for
f77    -s -N109 -N3 lg4.for ..\libs_dir\legolib\legolib.lib
f77 -c -s -N109 -N3 lg5.for

copy  edi14.exe  %target%\bin\lego
copy  lg1.exe    %target%\bin\lego
copy  lg2.obj    %target%\bin\lego
copy  lg3.obj    %target%\bin\lego
copy  lg4.exe    %target%\bin\lego\lg4_exe,exe
copy  lg5.obj    %target%\bin\lego

REM WIN XP
REM copy /Y edi14.exe  %target%\bin\lego
REM copy /Y lg1.exe    %target%\bin\lego
REM copy /Y lg2.obj    %target%\bin\lego
REM copy /Y lg3.obj    %target%\bin\lego
REM copy /Y lg4.exe    %target%\bin\lego\lg4_exe.exe
REM copy /Y lg5.obj    %target%\bin\lego