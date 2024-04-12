@echo off

if not "%1"=="" goto oknome

      echo The name of the file is needed!
	echo Correct usage is:  EDITA filename
	goto exit

:oknome
	if exist %LG_TEXTEDITOR% goto esiste 
        notepad %1
	goto exit
:esiste 
	%LG_TEXTEDITOR% %1
:exit
	
