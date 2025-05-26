
#f77   tradFORf22.for
gfortran  $(F_FLAGS) tradFORf22.for -o tradFORf22.exe

copy  tradFORf22.exe %target%\bin\lego
REM WIN XP
REM copy /Y tradFORf22.exe %target%\bin\lego

