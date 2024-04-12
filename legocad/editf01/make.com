$!************************************************************************
$! modulo make.com
$! tipo 
$! release 1.2
$! data 96/04/05
$! reserved @(#)make.com	1.2
$!************************************************************************
$ !
$ ! Make sure that the prerequisite files and logicals exist.  This command
$ ! procedure requires that the DECwindows programming be installed.
$ !
$ if f$search("sys$system:decw$uilcompiler.exe") .nes. "" then goto startupok
$ write sys$output "DECwindows programming environment not installed."
$ write sys$output "DECwindows example program build aborted."
$ exit
$startupok:
$ if f$search("sys$system:vaxc.exe") .eqs. "" then goto do_pascal
$ !
$ ! Define the logical names for the C language include files and libraries
$ !
$ define/nolog c$include decw$examples,decw$include,sys$library,LEGOCAD_INCLUDE,LEGOMMI_INCLUDE,LEGOROOT_INCLUDE
$ define/nolog vaxc$include c$include
$ !
$ ! Define logical names for UIL compiler
$ !
$ define/nolog uil$include decw$include
$ !
$ define/nolog X11 decw$include
$ define/nolog sys sys$library
$ cc edit_f01
$ cc applicationshell1
$ cc UxXt.c 
$ link edit_f01,applicationshell1,uxxt,-
        LEGOROOT_LIB:libutilx/lib,-
        LEGOROOT_LIB:libutil/lib,-
        LEGOCAD_LIB:liblegocad/lib,-
        sys$input/opt
        SYS$LIBRARY:VAXCRTL/share
        SYS$LIBRARY:UCX$IPC_SHR/share
        SYS$LIBRARY:RPC$LIBUCX/lib
        SYS$LIBRARY:UCX$IPC/lib
        sys$share:decw$dxmlibshr/share
        sys$share:decw$xlibshr/share
$end:
$ exit
