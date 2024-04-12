$!******************************************************************************
$! modulo make.com
$! tipo 
$! release 2.3
$! data 96/04/05
$! reserver @(#)make.com	2.3
$!******************************************************************************
$!furlani 23/11/92
$!
$ on error then go to abort
$ sd [.libicofile]
$ write sys$output "creazione libreria libicofile "
$ @ [--]makecadlib libicofile
$!
$ write sys$output "************  LEGOCAD TUTTO OK  ******************** "
$!
$fine:
$ sd [-]
$ exit
$abort
$ write sys$output " "
$ write sys$output " "
$ write sys$output "PROCEDURA ABORTITA  !! "
$ write sys$output " "
$ write sys$output " "
$ go to fine
