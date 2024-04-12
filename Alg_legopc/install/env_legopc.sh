#!/bin/sh
alias tix='/usr/bin/tixwish8.1.8.3'
alias tix1='/usr/bin/tixwish8.1.8.3.1'
#export PATH=%PATH%;$LG_BASE%\bin\Util;$LG_BASE%\bin\LegoSim

if [ $OS == "Linux" ]; then

export LG_BASE=$HOME/legopc_pak
export LG_ENTRY=$HOME/legocad_pc
export LG_BIN=$LG_BASE/bin

export LG_PREINST=$LG_BIN/preinst
export LG_INSTALL=$LG_BIN/install

export LG_LIBGRAPH=$LG_ENTRY/libgraph
export LG_LIBUT=$LG_ENTRY/libut
export LG_MODELS=$LG_ENTRY

export LG_GRAF=$LG_BIN/grafics
export LG_LEGO=$LG_BIN/lego
export LG_PIXMAPS=$LG_LIBGRAPH/pixmaps
export LG_TIX=$LG_BIN/tix
export LG_TOOLS=$LG_BIN/tools
export LG_TABLES=$LG_BIN/tables
export LG_NEWMOD=$LG_BIN/newmod
export LG_POSTPROC=$LG_BIN/postproc
export LG_LIBRARIAN=$LG_BIN/libraria

export LG_FILESI5=$LG_LIBGRAPH/files_i5
export LG_HELP=$LG_LIBGRAPH/help
export LG_LIBRARIES=$LG_LIBGRAPH/libraries
export LG_XBM=$LG_LIBGRAPH/xbm

export LG_CONCIL=$LG_BIN%/lgconcil

export LG_SIMULATORS=$LG_ENTRY

export LG_BROWSER=/usr/bin/mozilla

export LG_HTML=$LG_BIN/help

#export LG_ICOEDITOR=C:/PROGRA~1/JASC~1/PAINT~1/PSP.EXE
export LG_TEXTEDITOR=kwrite

else

export LG_BASE=$HOME/legopc
export LG_ENTRY=$LG_BASE/user
export LG_BIN=$LG_BASE/bin

export LG_PREINST=$LG_BIN/preinst
export LG_INSTALL=$LG_BASE/Install

export LG_LIBGRAPH=$LG_ENTRY/libgraph
export LG_LIBUT=$LG_ENTRY/libut
export LG_MODELS=$LG_ENTRY/models

export LG_GRAF=$LG_BIN/grafics
export LG_LEGO=$LG_BIN/lego
export LG_PIXMAPS=$LG_LIBGRAPH/pixmaps
export LG_TIX=$LG_BIN/tix
export LG_TOOLS=$LG_BIN/tools
export LG_TABLES=$LG_BIN/tables
export LG_NEWMOD=$LG_BIN/newmod
export LG_POSTPROC=$LG_BIN/postproc
export LG_LIBRARIAN=$LG_BIN/libraria

export LG_FILESI5=$LG_LIBGRAPH/files_i5
export LG_HELP=$LG_LIBGRAPH/help
export LG_LIBRARIES=$LG_LIBGRAPH/libraries
export LG_XBM=$LG_LIBGRAPH/xbm

export LG_CONCIL=$LG_BIN%/lgconcil

export LG_SIMULATORS=$LG_ENTRY/simulators

export LG_BROWSER=mozilla
export LG_HTML=$LG_BASE/help

#export LG_ICOEDITOR=C:/PROGRA~1/JASC~1/PAINT~1/PSP.EXE
export LG_TEXTEDITOR=kwrite

fi



