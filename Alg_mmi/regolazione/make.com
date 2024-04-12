$!******************************************************************************
$! modulo make.com
$! tipo 
$! release 5.1
$! data 96/03/22
$! reserver @(#)make.com	5.1
$!******************************************************************************
$!###########################################################################
$! MP 30/5/94
$! FILE DI MAKE PER GENERARE TUTTI GLI ESEGUIBILI DEL DIRETTORIO
$! [LEGOROOT.LEGOMMI.REGOLAZIONE] 
$! SI COMPILA E LINKA SE L'ESEGUIBILE E' ASSENTE O E' PIU' VECCHIO DEL 
$! SORGENTE.
$! SI LANCIA DAL DIRETTORIO DEI SORGENTI:
$!
$! IN CASO DI UNRESOLVED EXTERNAL IL LINKER GENERA COMUNQUE UN ESEGUIBILE 
$! ED EMETTE UN WARNING CHE INTERROMPE IL MAKE E CHIEDE SE SI VUOL 
$! CANCELLARE L'ESEGUIBILE SCORRETTO.
$! PER AGGIUNGERE FILE AGGIUNGERE LE RIGHE:
$!
$! MODULO := <NOME_MODULO>
$! GOSUB LINK<TIPO_DI_MAKE>
$!
$! PER CAMBIARE I PARAMETRI DI CC,FORTRAN E LINK AGGIUNGERE SUBROUTINE DEL TIPO 
$! LINK<TIPO_DI_MAKE> COPIANDO UNA DELLE ESISTENTI E PERSONALIZZANDOLA
$!
$!###########################################################################
$
$ cdebug := "NODEBUG"
$ fdebug := "NODEBUG"
$ wr := write sys$output
$ on warning  then GOTO WARN 
$
$! linkc2   compilazione in c con FAMX LIBSKEDC
$! linkf   compilazione in fortran con LIBSKED
$
$
$ modulo := GEN_F01TASK
$ gosub linkc2
$
$ modulo := GEN_F14TASK
$ gosub linkc2
$
$ modulo := GEN_F14
$ gosub linkc2
$
$ modulo := GEN_MACROMOD
$ gosub linkc2
$
$ modulo := GEN_TOPOLOGIA
$ gosub linkc2
$
$ modulo := gen_sche_vms
$ gosub linkf
$
$ wr "  "
$ wr "  FINE MAKE "
$ wr "  "
$
$fine:
$exit
$!
$!
$!
$!
$!
$linkc2:
$
$  src :='modulo'.c
$  exe :=LEGOMMI_BIN:'modulo'.exe
$
$  wr "  Modulo ''src'  "
$
$  if (F$SEARCH("''exe'") .eqs."") 
$  then 
$      goto exec2
$  endif
$  tc=f$CVTIME(F$FILE_ATTRIBUTES("''src'","RDT"))
$  te=f$CVTIME(F$FILE_ATTRIBUTES("''exe'","RDT"))
$  if tc .GTS. te
$  then
$        goto exec2
$  else
$	 goto noexec1
$  endif
$exec2:
$        wr " "
$        wr "  *****************************************************  "
$        wr "  Compilazione e Link del modulo ''src'    "
$        wr "  *****************************************************  "
$        CC/decc/standard=vaxc/define=(XGRAF,ENEL_CRA,ON_PAGEDDIT,XLIB_ILLEGAL_ACCESS)/optimize/include_directory=(LEGOROOT_INCLUDE,LEGORT_INCLUDE,[],LEGORT_INCLUDE_WIDGET,LEGOMMI_LIB,LEGOMMI_INCLUDE)-
		      /OBJ=SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.OBJ -
                      SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.C
$        LINK/EXE=legommi_bin:'modulo'.EXE -
                      SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.OBJ, -
                      LEGOMMI_LIB:libcs.opt/options,-
                      LEGOMMI_LIB:libol.opt/options,-
                      LEGOMMI_LIB:libxd.opt/options,-
                      LEGOMMI_LIB:libxl.opt/options, -
                      LEGOROOT_LIB:libutilx/lib,-
                      LEGOROOT_LIB:libutil/lib, -
                      LEGORT_LIB:libsim/lib, LEGORT_LIB:libipc/lib, -
                      LEGORT_LIB:libnet/lib, LEGORT_LIB:libcom/lib, -
                      sys$input/opt
                      SYS$LIBRARY:VAXCRTL/share
                      sys$share:decw$xlibshr/share
                      sys$share:decw$mrmlibshr12/share
$	
$  PURGE/nolog   LEGOMMI_BIN:'modulo'.EXE
$  DEL/nolog/noconf   SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.OBJ;*
$  return
$noexec1:
$  return
$ exit
$!*********************************************
$linkf:
$!
$  src :='modulo'.for
$  exe :=LEGOMMI_BIN:'modulo'.exe
$
$  wr "  Modulo ''src'  "
$
$  if (F$SEARCH("''exe'") .eqs."") 
$  then 
$      goto exef1
$  endif
$  tc=f$CVTIME(F$FILE_ATTRIBUTES("''src'","RDT"))
$  te=f$CVTIME(F$FILE_ATTRIBUTES("''exe'","RDT"))
$  if tc .GTS. te
$  then
$        goto exef1
$  else
$	 goto noexef1
$  endif
$exef1:
$  wr " "
$  wr "  *****************************************************  "
$  wr "  Compilazione e Link del modulo ''src'    "
$  wr "  *****************************************************  "
$ FOR/WARN=(NOUNUSED)/OBJ=SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.OBJ -
          SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.FOR
$ LINK/EXE=legommi_bin:'modulo'.EXE -
          SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.OBJ, -
          LEGOROOT_LIB:libutil/lib, -
          LEGORT_LIB:libsim/lib, LEGORT_LIB:libipc/lib, -
          LEGORT_LIB:libnet/lib, LEGORT_LIB:libcom/lib, -
          sys$input/opt
          SYS$LIBRARY:VAXCRTL/share
          sys$share:decw$xlibshr/share
          sys$share:decw$mrmlibshr12/share
$
$ PURGE/nolog/noconf   legommi_bin:'modulo'.EXE
$ DEL/nolog/noconf  SYS$SYSDEVICE:[LEGOROOT.LEGOMMI.REGOLAZIONE]'modulo'.OBJ;*
$  return
$noexef1:
$  return
$
############################################################################
$! GESTIONE WARNING:
$!
$WARN:
$ wr " WARNING "
$ SERCE = F$SEARCH("''EXE'")
$ IF SERCE .EQS. "" THEN EXIT
$ DEL/CONF 'EXE';*
$EXIT
