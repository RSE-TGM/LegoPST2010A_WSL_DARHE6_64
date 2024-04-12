@echo off

if not "%1"=="" goto oknome

      echo The name of the model to make is needed!
	echo Correct usage is:  DOLG1LG2 modelname
	goto exit

:oknome
        cd %1
	if exist lg1_done.out del lg1_done.out
	if exist lg2_done.out del lg2_done.out
	amake -f %LG_LEGO%\dopag2f01.mak LGTOPNAME=%2
	amake -f %LG_LEGO%\dolg1lg2_ridotto.mak
        cd 

:exit
	
