$!******************************************************************************
$! modulo make.com
$! tipo 
$! release 1.6
$! data 96/03/18
$! reserver @(#)make.com	1.6
$!******************************************************************************
$! Furl 27-10-92 nome del file:make.com per xstaz
$! ************ template per preparazione di eseguibili  **************
$! istruzioni: inserire in nomeexe il nome dell' eseguibile che si vuole 
$! creare e mettere questa procedura nella directory dei sorgenti ed 
$! aggiungere l'elenco degli oggetti
$!
$ on error THEN GOTO ABORT
$ linkexe = "link/nodebug/nomap"
$ nomeexe := xstaz
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
$  purge/nolog *.olb
$  del/nolog/noconf lista_file.dat;
$  exit
$!
$finecomp:
$  write sys$output "Crea libreria libstaz_r"
$messaggio= "CREAZIONE DELLA LIBRERIA!!!! "
$ lib/create libstaz_r am1_r, am2_r, am3_r, amd_r, -
                       id1_r, -
                       tr1_r, sp1_r, spd_r, br1_r, sd1_r, -
                       sa1_r, mr1_r, lu1_r, stazgenr
$!
$  messaggio="link di ''nomeexe' con ''numero' oggetti ..."
$  write sys$output messaggio
$  messaggio= "FASE DI LINK DI   ''nomeexe' !!!! "
$ 'linkexe/exe=LEGORT_BIN:'nomeexe'  'nomeexe', -
        cnewstaz, gled, gstringa, glampada, gpulsluce, -
        gpulsante, gselet, gdisplay, gdisplayscal, gindic,-
        gluce, gtasto, gsetval, gsincro, -
        libstaz_r/lib, -
        LEGORT_LIB:libsim/lib, -
        LEGORT_LIB:libcom/lib,-
        LEGORT_LIB:libipc/lib,-
        LEGORT_LIB:libwidget/lib/include=(led,bottone,selettore),-
        LEGOROOT_LIB:libutilx/lib,-
        LEGOROOT_LIB:libutil/lib,-
        sys$input/opt
        sys$share:decw$xlibshr/share
        sys$share:decw$xtlibshrr5/share
        sys$share:decw$xmlibshr12/share
        sys$share:decw$mrmlibshr12/share
        sys$share:decw$dxmlibshr12/share
$ goto end
