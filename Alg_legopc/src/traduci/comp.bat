
acc -c -windefs iof22bin.c
f77 -f -N3 traduci.for iof22bin.obj

copy  traduci.exe %target%\bin\grafics

REM WIN XP
REM copy /Y traduci.exe %target%\bin\grafics

