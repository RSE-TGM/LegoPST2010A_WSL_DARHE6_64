$!   make.com
$!   
$!   5.1
$!   96/04/03
$!   @(#)make.com	5.1
$!
$! aggiungere l'elenco degli oggetti
$!
$ on error THEN GOTO ABORT
$ linkexe = "link/nodebug/nomap"
$ nomeexe := draw
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
$    delete 'obj';*
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
$  pu/nolog LEGOMMI_BIN:'nomeexe'.exe
$  purge/nolog *.obj
$  del/nolog/noconf lista_file.dat;
$  exit
$!
$finecomp:
$  messaggio="link di ''nomeexe' con ''numero' oggetti ..."
$  write sys$output messaggio
$  messaggio= "FASE DI LINK DI   ''nomeexe' !!!! "
$ 'linkexe/exe=LEGOMMI_BIN:'nomeexe' draw ,-
   drawShell, applicationShell1, line_width_dialog, snap_width_dialog, -
   MessageBox, SaveSelection, UxXt, graphics, ColorViewer, ColorEditor, -
   ColorMapViewer, UtilRes, draw_wid, draw_other,-
	LEGOMMI_LIB:libcs.opt/options,-
	LEGOMMI_LIB:libol.opt/options,-
	LEGOMMI_LIB:libxd.opt/options,-
	LEGOMMI_LIB:libxl.opt/options, -
	LEGOROOT_LIB:libutilx/lib,-
	LEGOROOT_LIB:libutil/lib, - 
        LEGORT_LIB:libsim/lib, LEGORT_LIB:libipc/lib, -
        LEGORT_LIB:libnet/lib, LEGORT_LIB:libcom/lib, -
	sys$input/opt
        sys$share:decw$xlibshr/share
        sys$share:decw$xtlibshrr5/share
        sys$share:decw$xmlibshr12/share
        sys$share:decw$mrmlibshr12/share
        sys$share:decw$dxmlibshr12/share
$!
$  goto end
