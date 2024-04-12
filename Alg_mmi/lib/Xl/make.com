$!******************************************************************************
$! modulo make.com
$! tipo 
$! release 5.1
$! data 96/04/03
$! reserver @(#)make.com	5.1
$!******************************************************************************
$ @makelib libxl
$ set def [.SourceGrafica]
$ @makelib libxl
$ sd [-]
