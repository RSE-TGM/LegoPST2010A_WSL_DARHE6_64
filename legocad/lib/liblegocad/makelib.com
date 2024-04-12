$!******************************************************************************
$! modulo makelib.com
$! tipo 
$! release 1.3
$! data 96/04/05
$! reserver @(#)makelib.com	1.3
$!******************************************************************************
$!
$ on error THEN GOTO ABORT
$ linkexe = "link/nodebug/nomap"
$ nomelib := 'p1'
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
$    delete/nolog/noconf  'obj';*
$  else
$    goto ciclo
$  endif
$!
$faiogg:
$  write sys$output " "
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
$  pu/nolog LEGOMMI_LIB:'nomelib'.olb
$  purge/nolog *.obj
$  del/nolog/noconf lista_file.dat;
$  exit
$!
$finecomp:
$  messaggio="creazione della libreria ''nomelib' con ''numero' oggetti ..."
$  write sys$output messaggio
$  messaggio= "FASE DI CREAZIONE DELLA LIBRERIA  ''nomelib' !!!! "
$  purge/nolog *.obj
$  lib/create LEGOCAD_LIB:'nomelib'  *.obj
$  goto end
