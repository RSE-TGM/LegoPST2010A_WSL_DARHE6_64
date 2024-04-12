$!   make.com
$!   
$!   1.5
$!   96/03/18
$!   @(#)make.com	1.5
$!
$! ************ template per preparazione di eseguibili  **************
$! istruzioni: inserire in nomeexe il nome dell' eseguibile che si vuole 
$! creare e mettere questa procedura nella directory dei sorgenti ed 
$! aggiungere l'elenco degli oggetti
$!
$ on error THEN GOTO ABORT
$ linkexe = "link/nodebug/nomap"
$ nomeexe := xaing
$ numero  =0
$!
$  if (f$trnlnm("infile").nes."") then close infile
$  if F$SEARCH("lista_file.dat").nes. "" then dele/nolog/noconf lista_file.dat;*
$  DIR/nohea/notrai/vers=1/out=lista_file.dat/col=1 *.c
$  open/read infile lista_file.dat
$!
$ciclo:
$  read/end_of_file=finecomp infile riga
$  numero=numero+1
$  nomef=F$ELEMENT(1,"]",riga)
$  obj=(F$ELEMENT(0,".",nomef)+".obj")
$  write sys$output obj
$  if ((F$SEARCH(obj)).eqs."") then goto faiogg
$  time_c=f$CVTIME(F$FILE_ATTRIBUTES(nomef,"RDT"))
$  time_o=f$CVTIME(F$FILE_ATTRIBUTES(obj,"RDT"))
$  if time_c .GTS. time_o
$  then
$    delete/nolog/noconf 'obj';*
$  else
$    goto ciclo
$  endif
$!
$faiogg:
$  write sys$output "compilazione ''nomef'"
$  messaggio= "COMPILAZIONE DI ''nomef'!!!! "
$  'compile' 'nomef'
$goto ciclo
$!
$ABORT:
$  write sys$output " "
$  write sys$output " "
$  write sys$output " "
$  write sys$output " "
$  write sys$output "ERRORE IN ''messaggio'"
$  write sys$output "PROCEDURA ABORTITA .................................. "
$  write sys$output " "
$  write sys$output " "
$  write sys$output " "
$!
$end:
$  close infile
$  pu/nolog LEGORT_BIN:'nomeexe'.exe
$  purge/nolog *.obj
$  del/nolog/noconf lista_file.dat;
$  exit
$!
$finecomp:
$  messaggio="link di ''nomeexe' con ''numero' oggetti ..."
$  write sys$output messaggio
$  messaggio= "FASE DI LINK DI   ''nomeexe' !!!! "
$ 'linkexe/exe=LEGORT_BIN:'nomeexe'  'nomeexe',-
	LEGOROOT_LIB:libutilx/lib, -
	LEGOROOT_LIB:libutil/lib, -
	LEGORT_LIB:libsim/lib, -
	LEGORT_LIB:libipc/lib, -
	LEGORT_LIB:libnet/lib, -
	LEGORT_LIB:libcom/lib, -
        sys$input/opt
        sys$share:decw$xlibshr/share
        sys$share:decw$xtlibshrr5/share
        sys$share:decw$xmlibshr12/share
        sys$share:decw$mrmlibshr12/share
        sys$share:decw$dxmlibshr12/share
$!
$  goto end
