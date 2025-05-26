f77 -s -N109 H2O_tab.for %LG_LEGO%\vapo.lib unix.lib -aliases:UNICODE.ALS
REM solo Windows

copy  H2O_tab.exe   %target%\bin\tables

REM WIN XP
REM copy /Y H2O_tab.exe   %target%\bin\tables