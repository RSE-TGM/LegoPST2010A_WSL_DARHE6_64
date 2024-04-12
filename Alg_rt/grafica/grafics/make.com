$!   make.com
$!   
$!   1.6
$!   96/03/19
$!   @(#)make.com	1.6
$!
$
$ linkexe = "link/nodebug/nomap"
$ numero=0
$
$ delete/nolog/noconf *.obj;
$ on error THEN GOTO ABORT
$if F$SEARCH("lista_file.dat").nes. "" then delete/nolog/NOCONF lista_file.dat;*
$DIR/nohea/notrai/vers=1/out=lista_file.dat/col=1 *.c
$open/read infile lista_file.dat
$ciclo:
$read/end_of_file=finecomp infile riga
$nomef=F$ELEMENT(1,"]",riga)
$ceobj=F$ELEMENT(0,".",nomef)
$ data_c=F$FILE_ATTRIBUTES(nomef,"RDT")
$ data_o=F$FILE_ATTRIBUTES("''ceobj'.obj","RDT")
$ time_1=f$CVTIME(data_c)
$ time_2=f$CVTIME(data_o)
$ numero=numero+1
$if time_1 .GTS. time_2
$then
$ canc="''ceobj'.obj;*"
$ delete/nolog/noconf 'canc'
$endif
$if F$SEARCH("''ceobj'.obj").eqs."")
$then
$  write sys$output "compilazione ''nomef'"
$messaggio= "COMPILAZIONE DI ''nomef'!!!! "
$'compile' 'nomef'
$endif
$goto ciclo
$ABORT:
$  write sys$output " "
$  write sys$output " "
$  write sys$output " "
$  write sys$output " "
$  write sys$output "ERRORE IN ''messaggio'"
$  write sys$output "PROCEDURA ABORTITA ..............................."
$  write sys$output " "
$  write sys$output " "
$  write sys$output " "
$end:
$close infile
$ pu/nolog LEGORT_BIN:cgrafics.exe
$ purge/nolog *.obj
$ exit
$finecomp:
$  write sys$output "Crea file uid"
$messaggio= "CREAZIONE FILE UID!!!! "
$uil/motif/out=LEGORT_UID:grafics.uid grafics.uil'MOTIF_VER'
$  messaggio="Linking ''numero' oggetti ..."
$  write sys$output messaggio
$messaggio= "FASE DI LINK !!!! "
$ 'linkexe/exe=LEGORT_BIN:cgrafics grafics.obj,-
                grsfio.obj,-
        	LEGOROOT_LIB:libutilx/lib,-
		LEGORT_LIB:libsim/lib,-
	        LEGORT_LIB:libcom/lib,-
		LEGOROOT_LIB:libutil/lib,-
        	sys$input/opt
        	sys$share:decw$xlibshr/share
        	sys$share:decw$xtlibshrr5/share
        	sys$share:decw$xmlibshr12/share
        	sys$share:decw$mrmlibshr12/share
        	sys$share:decw$dxmlibshr12/share
$ goto end
