$!   make.com
$!   
$!   5.1
$!   96/03/18
$!   @(#)make.com	5.1
$!
$! ************ template per preparazione di eseguibili  **************
$! istruzioni: inserire in nomeexe il nome dell' eseguibile che si vuole
$! creare e mettere questa procedura nella directory dei sorgenti ed
$! aggiungere l'elenco degli oggetti
$!
$ on error THEN GOTO ABORT
$ linkexe = "link/nodebug/nomap"
$ nomeexe := net_compi
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
$  write sys$output "PROCEDURA ABORTITA ................................."
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
$  for co_read_
$  numero=numero+1
$  messaggio="link di ''nomeexe' con ''numero' oggetti ..."
$  write sys$output messaggio
$  messaggio= "FASE DI LINK DI   ''nomeexe' !!!! "
$ 'linkexe/exe=LEGORT_BIN:'nomeexe'  co_main,-
	check_i, check_m, check_o, check_dt,-
	co_legge, co_len04, co_varlego,-
	co_n04_s,co_sep_s, f04_s04, co_read_, -
	tabella,tabelle_net, co_snap,-
        LEGOROOT_LIB:libutilx/lib, -
        LEGOROOT_LIB:libutil/lib, -
        LEGORT_LIB:libsim/lib, -
        LEGORT_LIB:libipc/lib, -
        LEGORT_LIB:libnet/lib, -
        LEGORT_LIB:libcom/lib
$!
$!
$  goto end
