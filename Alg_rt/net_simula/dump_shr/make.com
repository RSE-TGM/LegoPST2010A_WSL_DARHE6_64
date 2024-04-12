$!******************************************************************************
$! modulo make.com
$! tipo 
$! release 5.1
$! data 96/04/04
$! reserver @(#)make.com	5.1
$!******************************************************************************
$!******************************************************************************
$! modulo make.com
$! tipo 
$! release 5.1
$! data 96/04/04
$! reserver @(#)make.com	5.1
$!******************************************************************************
$! Furl 21-10-92 nome del file:make.com per net_demone
$! ************ template per preparazione di eseguibili  **************
$! istruzioni: inserire in nomeexe il nome dell' eseguibile che si vuole 
$! creare e mettere questa procedura nella directory dei sorgenti ed 
$! aggiungere l'elenco degli oggetti
$!
$ on error THEN GOTO ABORT
$ linkexe = "link/nodebug/nomap"
$ nomeexe := dump_shr
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
	LEGORT_LIB:libsim/lib,-
	LEGORT_LIB:libipc/lib, -
	LEGORT_LIB:libnet/lib,-
	LEGOROOT_LIB:libutil/lib,-
	SYS$LIBRARY:UCX$IPC/LIB,-
        SYS$INPUT/OPTIONS
        SYS$SHARE:VAXCRTL.EXE/SHARE
$!
$  goto end
