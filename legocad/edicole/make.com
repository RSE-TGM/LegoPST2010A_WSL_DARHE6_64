$!************************************************************************
$! modulo make.com
$! tipo 
$! release 1.3
$! data 96/04/05
$! reserver @(#)make.com	1.3
$!************************************************************************
$
$ compile = "cc/optimize/define=MAIN/include_directory=(LEGOCAD_INCLUDE,LEGOROOT_INCLUDE,LEGORT_INCLUDE)"
$ linkexe = "link/nodebug/nomap"
$ numero=0
$
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
$ pu/nolog LEGOROOT_BIN:edicole.exe
$ purge/nolog *.obj
$ exit
$finecomp:
$  write sys$output "Crea file uid"
$messaggio= "CREAZIONE FILE UID!!!! "
$uil/motif/out=LEGOCAD_UID:edicole.uid edicole.uil
$  messaggio="Linking ''numero' oggetti ..."
$  write sys$output messaggio
$messaggio= "FASE DI LINK !!!! "
$ linkexe/exe=LEGOROOT_BIN:edicole edicole.obj, -
		LEGOROOT_LIB:libutil/lib,-
        	LEGOROOT_LIB:libutilx/lib,-
		LEGOCAD_LIB:libicofile/lib,-
                sys$input/opt
                sys$share:decw$dxmlibshr/share
                sys$share:decw$xlibshr/share
$ goto end
