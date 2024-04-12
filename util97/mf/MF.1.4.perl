#!/bin/sh
eval 'exec $UTIL97/prebuilt_bin/perl -S -x $0 "$@"'
    if 0;
# La riga seguente e' necessaria ed e' collegata allo switch -x della riga precedente
#!perl

#=======================================================================
#@(#)MF	Costruzione di file Y_*.scr da file *.MF	1998-01-27
#	
#	Costruisce un file *.scr in base
#	alle informazioni contenute nei file:
#	- tipo_comp_malf.mf                    ( "Classi" )
#	  ( Ogni riga da' luogo ad un *.scr  )
#	- malf_set.mf                          ( "Malfunzioni" )
#	- component.mf                         ( "Istanze" )
#	- direttive.mf
#	  ( (introdotto per definire parametri geometrici)

#------------------------------------------------------------------------
#	Use & Require

use	Fcntl;
use	AnyDBM_File;

require	'getopts.pl';
require	'stat.pl';

#------------------------------------------------------------------------
#	Variabili relative alle opzioni

$Opts	= 'cdDhilmp:qQSsTuVx' ;

$Help	= "\
Uso:  MF  [ -cdDhilmqQsSTux ] [ -p xxx ]  argomento-qualsiasi\
\
Opzioni:\
 -c	Stampa il contenuto della tabella delle Classi\
 -d	Stampa il contenuto della tabella delle Direttive\
 -D	Centra le eventuali label di descrizione\n
 -h	Questo testo di help\
 -i	Stampa il contenuto della tabella delle Istanze\
 -l	Ricerca i file: *.dflt nella directory locale\
 -m	Stampa il contenuto della tabella delle Malfunzioni\
 -p xxx	Lancia la creazione delle pagine con le opzioni xxx (racchiudere tra apici)\
	Esempio di uso:  -p '-S -w'\
	Se non sono richieste opzione usare l'opzione nulla: -p N\
 -q	quiet mode - stampa solo il numero di linee utili lette nei file\
 -Q	Quiet mode - stampa solo gli errori\
 -s	Stampa i nomi degli script prodotti\
 -S	Stampa le variabili secondarie\
 -T	Centra la label del titolo\
 -u	Ricerca i file: *.mf e *.dir nella directory sovrastante\
 -V	Stampa la versione\
 -x	Stampa informazioni sulle malfunzioni\
";

$Ver	= "MF - Versione: 1.4 1998-01-27";

#========================================================================
#	SUBROUTINE


#-----------------------------------------------------------------------
#	Costruisce un blocco:   Icon  Bottone (SENZA lamp)  Label

sub	bld_malfunzione()
{
local( $nnn )	= @_;
local( $cflbc );

		if( $nnn == 1 )
		{
			$cflbc	= $verde;
		}
		else
		{
			$cflbc	= $giallo;
		}
#.......................................................................
		$Ycrnt	+= $Y_INCR;
		$Ico	= 'Icon';
		$Ico	= 'IconM0' if( $m == 0 );
		printf	PFH "\nPLACE $Ico     M%dic\n", $m;	#! M... Icon
		printf	PFH "	varInputCambioColore1=%s NOP 1.0$codaIn\n", $ResVp;
		printf	PFH "	valoreBassissimo1=%.2f\n", $m-0.5;
		printf	PFH "	valoreBassissimoBasso1=%.2f\n", $m+0.5;
		printf	PFH "	coloreBassissimo1=%s\n", $COLOR_BG;
		printf	PFH "	coloreBassissimoBasso1=%s\n", $cflbc;
		printf	PFH "	coloreBassoAlto1=%s\n", $COLOR_BG;
		printf	PFH "	coloreAltoAltissimo1=%s\n", $COLOR_BG;
		$x	= $MARG_SX + 10;		# Icon/Malfunzione
		$x	= $MARG_SX + 0;		# Icon/Malfunzione
		printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
		printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt+4, $Ycrnt+4;
		printf	PFH "ENDPLACE\n";

#.......................................................................
		printf	PFH "\nPLACE Bottone  M%dbo\n", $m;	#! M... Bottone
		printf	PFH "	varOutput=%s PERT_MALFUNCTION %.1f$codaOu\n", $ResVp, $m;
		$x	= $MARG_SX + 30;		# Bottone/Malfunzione
		$x	= $MARG_SX + 20;		# Bottone/Malfunzione
		printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
		printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
		printf	PFH "ENDPLACE\n";

#.......................................................................
		$MfDe	= $TMfDe{ $c }{ $m };
		printf	PFH "\nPLACE Label    M%dla\n", $m;	#! M... Label
		printf	PFH "	labelText=$MfDe\n";
		printf	PFH "	normalFont=%s\n", $FONT_LA if( $FONT_LA ne '' );
		printf	PFH "	normFg=%s\n", $COLOR_LA if( $COLOR_LA ne '' );
		$x	= $MARG_SX + 58;		# Label/Malfunzione
		$x	= $MARG_SX + 48;		# Label/Malfunzione
		do updateWcrnt( $x, $MfDe, $PPC_LA );
		printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
		printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt+2, $Ycrnt+2;
		printf	PFH "ENDPLACE\n";
}					# bld_malfunzione()


#-----------------------------------------------------------------------
#	Costruisce un blocco:   [ Icon ]  [ Bottone ]  [ Label ]

sub	bld_bool_blk_0()
{

	if( $j == 1 )
	{
	printf	PFH "\nPLACE IconS1   S%dic\n", $j;	#! S... Debug Icon
	}
	else
	{
	printf	PFH "\nPLACE Icon     S%dic\n", $j;	#! S... Debug Icon
	}
	$x	= $MARG_SX + 10;			# Icon/blocco-0
	printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
	printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt+4, $Ycrnt+4;
	printf	PFH "varInputCambioColore1=%s NOP 1.0$codaIn\n", $ResVs;
	printf	PFH "ENDPLACE\n";
#.......................................................................
	printf	PFH "\nPLACE Bottone  S%dbo\n", $j;	#! S... Debug Bottone
	printf	PFH "varOutput=%s $VsPt 0.0$codaOu\n", $ResVs;
	$x	= $MARG_SX + 30;			# Bottone/blocco-0
	printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
	printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
	printf	PFH "ENDPLACE\n";
#.......................................................................
	printf	PFH "\nPLACE Label    S%dla\n", $j;	#! S... Debug Label
	printf	PFH "	labelText=$VsDe\n";
	printf	PFH "	normalFont=%s\n", $FONT_LA if( $FONT_LA ne '' );
	printf	PFH "	normFg=%s\n", $COLOR_LA if( $COLOR_LA ne '' );
	$x	= $MARG_SX + 58;			# Label/blocco-0
	do updateWcrnt( $x, $VsDe, $PPC_LA );
	printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
	printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt+2, $Ycrnt+2;
	printf	PFH "ENDPLACE\n";
}					# bld_bool_blk_0()


#-----------------------------------------------------------------------
#	Costruisce un blocco:   [ Bottone with Lamp ]  [ Label ]

sub	bld_bool_blk_1()
{

#.......................................................................
	printf	PFH "\nPLACE BottoneLamp  S%dbo\n", $j;	#! S... Debug Bottone
	printf	PFH "	varInputColore=%s NOP 1.0$codaIn\n", $ResVs;
	printf	PFH "	varInputBlink=%s NOP 1.0$codaIn\n", $ResVs;
	printf	PFH "	varOutput=%s $VsPt $VsVa$codaOu\n", $ResVs;
	printf	PFH "	tipoBt=1\n";
	printf	PFH "	actFg=%s\n", $red;
	printf	PFH "	normBg=%s\n", $grigio;
	printf	PFH "	colorLamp=%s\n", $red;
	printf	PFH "	colorBlink=%s\n", $grigio;
	$x	= $MARG_SX + 30;			# Bottone-w-Lamp/blocco-1
	$x	= $MARG_SX + 20;			# Bottone-w-Lamp/blocco-1
	printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
	printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
	printf	PFH "ENDPLACE\n";
#.......................................................................
	printf	PFH "\nPLACE Label    S%dla\n", $j;	#! S... Debug Label
	printf	PFH "	labelText=$VsDe\n";
	printf	PFH "	normalFont=%s\n", $FONT_LA if( $FONT_LA ne '' );
	printf	PFH "	normFg=%s\n", $COLOR_LA if( $COLOR_LA ne '' );
	$x	= $MARG_SX + 58;			# Label/blocco-1
	$x	= $MARG_SX + 48;			# Label/blocco-1
	do updateWcrnt( $x, $VsDe, $PPC_LA );
	printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
	printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt+2, $Ycrnt+2;
	printf	PFH "ENDPLACE\n";
}					# bld_bool_blk_1()


#-----------------------------------------------------------------------
#	Costruisce gli script per il programma PLACE
#	(uno per ogni riga del file: "Istanze" )
#
# Struttura delle stazioni generate:
#
#	      [	TIla ]
#	      [	D1la ]
#	      [	D2la ]
#	      [	NSla ]
#	      [	DCla ]
#	M0ic	M0bo	M0la
#	M1ic	M1bo	M1la
#	M2ic	M2bo	M2la
#	....	....	....
#	S1ic	S1bo	S1la
#	S2ic	S2bo	S2la
#	....	....	....
#
# Variabili utilizzate per controllare la geometria:
#	$Y_INCR	incremento coordinata Y
#

sub	bld_place_script()
{

#+	$codaOu	= '.0 0.0 1.0 0.0 ---';			98-01-27
#+	$codaIn	= '.0 0.0 ---';				98-01-27
	$codaOu	= ' 0.0 1.0 0.0 ---';
	$codaIn	= ' 0.0 ---';

	open( EFH, ">$Elfn" );		# File elenco
	printf	EFH ":\n#File: $Elfn - Prodotto da MF -  $dataora\n\n";

#-----------------------------------------------------------------------
#	Loop su tutte le istanze del file "Istanze"

	for( $i = 1; $i <= $IsNo; $i++ )
	{
		&init_dirett_var();

		$c	= $TIsCl[$i];				# classe
#+printf	"Classe dell'istanza (\$c): $c\n";
		$Ybn	= $F_.$TIsKk[$i];
		$Yfn	= $F_.$TIsKk[$i].'.scr';
		printf	"[Classe:% 2d] $Yfn\n", $c if( $opt_s );
		open( PFH, ">$Yfn" );		# File .pag corrente
		($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
		$dataora	= sprintf( "%02d-%02d-%02d %02d:%02d:%02d",
					$year, $mon+1, $mday, $hour, $min, $sec );
		printf	PFH "#File: %-40s - Prodotto da MF -  Classe: $c - $dataora\n\n", $Yfn;
		printf	EFH "PLACE \$1	$Yfn\n";		# aggiunge all'elenco

		printf	PFH "INCLUDE	${dfDIR}PAGE.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}Bottone.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}BottoneLamp.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}Icon.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}IconM0.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}IconS1.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}Label.dflt\n";
		printf	PFH "INCLUDE	${dfDIR}SetValore.dflt\n";

		$ResVp	= $TVpPx[$c].$TIsVp[$i];		#+ 1998-01-21
		$ResVp	=~ s/-/ /g;

#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#		INTESTAZIONI

#		TITOLO
		unless( $LABEL_TI eq '' )
		{
			$Ycrnt	= $MARG_SUP;
			printf	PFH "\nPLACE Label    TIla\n";			#! TItolo
			printf	PFH "	labelText=$LABEL_TI\n";
			printf	PFH "	normalFont=%s\n", $FONT_TI if( $FONT_TI ne '' );
			printf	PFH "	normFg=%s\n", $COLOR_TI if( $COLOR_TI ne '' );
			$x	= $MARG_SX;			# Label/Titolo
			$x	= centra( "$LABEL_TI" ) if( $opt_T );
			do updateWcrnt( $x, "$LABEL_TI", $PPC_TI );
			printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
			printf	PFH "ENDPLACE\n";
		}

#.......................................................................
#		DESCRIZIONE 1
		if( $LABEL_D1 && $TClD1[$c] ne '' )
		{
			$Ycrnt	+= $Y_INCR;
			printf	PFH "\nPLACE Label    D1la\n";			#! Descrizione 1
			printf	PFH "	labelText=$TClD1[$c]\n";
			printf	PFH "	normalFont=%s\n", $FONT_LA if( $FONT_LA ne '' );
			printf	PFH "	normFg=%s\n", $COLOR_TI if( $COLOR_TI ne '' );
			$x	= $MARG_SX;
			$x	= centra( $TClD1[$c] ) if( $opt_T );
			do updateWcrnt( $x, $TClD1[$c], $PPC_LA );
			printf	PFH "	x=%s\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
			printf	PFH "ENDPLACE\n";
		}

#.......................................................................
#		DESCRIZIONE 2
		if( $LABEL_D2 && $TClD2[$c] ne '' )
		{
			$Ycrnt	+= $Y_INCR;
			printf	PFH "\nPLACE Label    D2la\n";			#! Descrizione 2
			printf	PFH "	labelText=$TClD2[$c]\n";
			printf	PFH "	normalFont=%s\n", $FONT_LA if( $FONT_LA ne '' );
			printf	PFH "	normFg=%s\n", $COLOR_TI if( $COLOR_TI ne '' );
			$x	= $MARG_SX;
			$x	= centra( $TClD2[$c] ) if( $opt_D );
			do updateWcrnt( $x, $TClD2[$c], $PPC_LA );
			printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
			printf	PFH "ENDPLACE\n";
		}

#.......................................................................
#		NOME STAZIONE
		if( $LABEL_NS )
		{
			$Ycrnt	+= $Y_INCR;
			printf	PFH "\nPLACE Label    NSla\n";			#! Nome Stazione
			printf	PFH "	labelText=$TIsKk[$i]\n";
			printf	PFH "	normalFont=%s\n", $FONT_TI if( $FONT_TI ne '' );
			printf	PFH "	normFg=%s\n", $COLOR_TI if( $COLOR_TI ne '' );
			$x	= $MARG_SX + 10;		# Label/Nome Stazione
			$x	= $MARG_SX +  0;		# Label/Nome Stazione
			$x	= centra( "$TIsKk[$i]" ) if( $opt_D );
			do updateWcrnt( $x, $TIsKk[$i], $PPC_TI );
			printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
			printf	PFH "ENDPLACE\n";
		}

#.......................................................................
#		DESCRIZIONE CLASSE
		if( $LABEL_DC )
		{
			$Ycrnt	+= $Y_INCR;
			printf	PFH "\nPLACE Label    DCla\n";			#! Descrizione Classe
			printf	PFH "	labelText=$TIsDe[$i]\n";
			printf	PFH "	normalFont=%s\n", $FONT_TI if( $FONT_TI ne '' );
			printf	PFH "	normFg=%s\n", $COLOR_TI if( $COLOR_TI ne '' );
			$x	= $MARG_SX + 10;		# Label/Descrizione classe
			$x	= $MARG_SX +  0;		# Label/Descrizione classe
			$x	= centra( "$TIsDe[$i]" ) if( $opt_D );
			do updateWcrnt( $x, $TIsDe[$i], $PPC_TI );
			printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
			printf	PFH "ENDPLACE\n";
		}

#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#		MALFUNZIONI
#+971114	for( $m = 0; $m < $MfNo; $m++ )
		@mmm	= split( $ss, $liMf[$c] );
		for( $k = 1; $k <= $#mmm; $k++ )
		{
			$m	= $mmm[$k];			# malfunzione
			&bld_malfunzione( $k );
		}


#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#		VARIABILI SECONDARIE
#+printf	"{$TVsPx1[$c]} {$TVsPx2[$c]} {$TVsPx3[$c]} {$TVsPx4[$c]}\n";
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
#	Salva la coordinata Y in cui porre la linea di separazione

		$Yln		= 0;				# No. di linee nel background
#+		@TYl		= ();
		for( $q = 0; $q < 10; $q++ ) { $TYl[$q] = 0; };
		$Ycrnt	+= $Y_SPACE;
VS_LOOP:
		for( $j = 1; $j <= 4; $j++ )		# Per ogni V. secondaria definita
		{
			eval	"\$VsPx = \$TVsPx$j\[$c];";
#+			printf	"La Var. Sec. #$j / Cl.$c     e` definita ? (\$TVsPx$j\[$c]=$VsPx)\n";
			last VS_LOOP if( $VsPx eq '' );

			$Ycrnt	+= $Y_INCR;	# Incremento per la linea di separazione
			$TYl[$Yln]	= $Ycrnt;
			$Yln++;
#+			printf	"Yln: $Yln - $Ycrnt: $Ycrnt\n";
			$Ycrnt	-= $Y_INCR;
			$Ycrnt	+= $Y_SPACE;


			eval	"\$VsPt = \$TVsPt$j\[$c];";
			eval	"\$VsVa = \$TVsVa$j\[$c];";
#+	printf	"c:$c j:$j VsVa:$VsVa\n";
			eval	"\$VsDe = \$TVsDe$j\[$c];";
#%			$ResVs	= $VsPx.$TIsVp[$i];				  98-01-21
			eval	"\$ResVs	= \$VsPx.\$TIsV$j\[\$i];";	# 98-01-21
			eval	"\$IsVx		= \$TIsV$j\[\$i];";		# 98-01-21
			$ResVs	=~ s/-/ /g;
#+ 			printf	"j:$j i:$i VsPx: {$VsPx} IsVx: {$IsVx} ResVs: {$ResVs}\n";
#+			printf	"La Var. Sec. #$j / Cl.$c     e` definita - Prefix: <$VsPx>\n" if( $opt_S );
#+			if( substr( $VsPx, 0, 1 ) eq 'J' )	98-01-23
			$VS_1	= substr( $VsPx, 0, 1 );
			if( $VS_1 eq 'J' || $VS_1 eq 'V' )
			{
#.......................................................................
#			BLOCCO PER VARIABILE SECONDARIA DIGITALE

				$Ycrnt	+= $Y_INCR;
				do bld_bool_blk_1();
			}
			else				# else: I o U
			{
#.......................................................................
#			BLOCCO PER VARIABILE SECONDARIA ANALOGICA

			$Ycrnt	+= $Y_INCR;
			printf	PFH "\nPLACE SetValore     S%dic\n", $j;	#! S... SetValore
			$x	= $MARG_SX + 10;	# SetValore/Var. Secondaria
			$x	= $MARG_SX +  0;	# SetValore/Var. Secondaria
			printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
#+			printf	PFH "	varInput=%s NOP 1.0$codaIn\n", $ResVs;
#+			printf	PFH "	varOutput=%s $VsPt 0.0$codaOu\n", $ResVs;
			printf	PFH "	varInput=%s NOP 1.0$codaIn\n", $ResVs;
			printf	PFH "	varOutput=%s $VsPt $VsVa$codaOu\n", $ResVs;
			printf	PFH "ENDPLACE\n";
#.......................................................................
			printf	PFH "\nPLACE Label    S%dla\n", $j;		#! S... SetValore Label
#+			printf	PFH "	labelText=%s\n", '%';
#++			printf	PFH "	labelText=%s\n", ' % '.$VsDe;
#			$VsDe	= ' % '.$VsDe;
			printf	PFH "	labelText=%s\n", $VsDe;
			printf	PFH "	normalFont=%s\n", $FONT_LA if( $FONT_LA ne '' );
			printf	PFH "	normFg=%s\n", $COLOR_LA if( $COLOR_LA ne '' );
			$x	= $MARG_SX + 115;	# Label/Var. Secondaria
			$x	= $MARG_SX + 105;	# Label/Var. Secondaria
			$Ycrnt	+= 10;	# SetValore e' piu' alto / messo qui abbassa il '%'
			do updateWcrnt( $x, $VsDe, $PPC_LA );	# aggiungere il % !!
			printf	PFH "	x=%d\n	x0=%d\n", $x, $x;
			printf	PFH "	y=%d\n	y0=%d\n", $Ycrnt, $Ycrnt;
			printf	PFH "ENDPLACE\n";
			}
		}

#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#		PAGE
		printf	PFH "\nMODIFY PAGE\n";				#! PAGE
#+		printf	PFH "	top_descrizione=$Ybn (MF)\n";
#+		printf	PFH "	top_descrizione=$TIsDe[$i]\n";		1997-11-27
		printf	PFH "	top_descrizione=($TClNm[$c]) $TIsDe[$i]\n";
#+		printf	"Ycrnt: $Ycrnt \@ Y_INCR: $Y_INCR \@ MARG_INF: $MARG_INF\n";
		$Ycrnt	+= $MARG_INF;			# Il MARG_INF 
		printf	PFH "	drawing_background=%s\n", $COLOR_BG;
		printf	PFH "	drawing_height=%d\n", $Ycrnt;
		$w	= $W_MIN if( $W_MIN ne '' );
		$w	= $Wcrnt;
#		....
#		$w	= $W_MAX if( $W_MAX ne '' );
		$Wcrnt	+= $MARG_DX;
		printf	PFH "	drawing_width=%d\n", $Wcrnt;
		printf	PFH "	top_width=%d\n", $Wcrnt + 4;
		printf	PFH "	top_height=%d\n", $Ycrnt + 4;
		printf	PFH "ENDMODIFY\n";
		close( PFH );

#+		do bkg_line( 0, $Yline1, $Wcrnt, $Yline1 );
		do bkg_line( $Yln, $Wcrnt );		# 98-01-23
	}
	close( EFH );
}					# bld_place_script()


#-----------------------------------------------------------------------
#	Verificare funzionalita' ed effetto estetico

sub	centra()
{
local( $lab ) = @_;
my( $labl, $lwpx, $lmpx );

	if( $FONT_TI ne '' )
	{
		printf	PFH "	normalFont=%s\n", $FONT_TI;
#....		$cwpx	= ...			# Character Width (Pixels)
		$cwpx	= 9.2;			# (anche con cifre decimali)
	}
	$labl	= length( "$lab" );
	$lwpx	= $labl * $cwpx;
	printf	PFH "# No. car. * cwpx = % 3d *% 4.1f = $lwpx\n", $labl, $cwpx;
	$lmpx	= int(($W_MIN-$lwpx)/2);	# Left Margin (Pixel)
	$lmpx	= 0 if( $lmpx < 0 );		# Sanity check
#+	printf	"<>centra()<> W_MIN:$W_MIN - lwpx:$lwpx - lmpx:$lmpx  |$lab|\n";
	printf	PFH "# La label: {$lab} e`stata centrata - x = (% 4d-% 3d)/2 = $lmpx\n", $W_MIN, $lwpx;
	return	$lmpx;
}					# centra()


#-----------------------------------------------------------------------
#	Crea un file *.bkg avente lo stesso basename della pagina in corso
#	di generazione e contenente tante linee quanti sono gli elementi
#	dell'array $TYl (Tabella coordinate Y delle linee).
#.......................................................................
#	Esempio di file *.bkg contenente 3 linee orizzontali
#//	x_min_d -1
#//	y_min_d 35
#//	x_max_d 249
#//	y_max_d 269
#//	num_d 3
#//	...........................
#//	wi_c 3
#//	st_c 0
#//	fg_c #000000000000
#//	bg_c #ffffffffffff
#//	fg_f #ffffffffffff
#//	fill 1
#//	line 0 268 248 268
#//	...........................
#//	wi_c 3
#//	st_c 0
#//	fg_c #ffff00000000
#//	bg_c #ffffffffffff
#//	fg_f #ffffffffffff
#//	fill 1
#//	line 0 148 248 148
#//	...........................
#//	wi_c 3
#//	st_c 0
#//	fg_c #ffffffffffff
#//	bg_c #ffffffffffff
#//	fg_f #ffffffffffff
#//	fill 1
#//	line 0 36 248 36
#.......................................................................

sub	bkg_line()
{
#+ local( $x1, $y1, $x2, $y2 )	= @_;
#+ local( $W, $Y1, $Y2 )	= @_;			!! 98-01-23
local( $N, $W )	= @_;
local( $headfmt, $linefmt, $x1, $x2, $YlineN );

#.......................................................................
$headfmt	= "x_min_d -1\
y_min_d 35\
x_max_d 249\
y_max_d 269\
num_d %d\n";

$linefmt	= "wi_c 3\
st_c 0\
fg_c #ffffffffffff\
bg_c #ffffffffffff\
fg_f #ffffffffffff\
fill 1\
line %d %d %d %d\n";
#.......................................................................

	$Bfn	= $Ybn.'.bkg';
	open( BFH, ">$Bfn" );		# File .bkg corrente
#+	printf	BFH "$headfmt", ( $Y2 > $Y1 ) ? 2 : 1;		98-01-23
	printf	BFH "$headfmt", $N;
	for( $q = 0; $q < $Yln; $q++ )
	{
#+	printf	BFH "$linefmt", 0, $Y1, $W, $Y1 if( $N > 0 );
#+	printf	BFH "$linefmt", 0, $Y2, $W, $Y2 if( $N > 1 );
		printf	BFH "$linefmt", 0, $TYl[$q], $W, $TYl[$q];
	}
	close( BFH );

}					# bkg_line()


#-----------------------------------------------------------------------
#	Premette al base-name dei file in gioco la directory in cui vanno
#	ricercati in base alle opzioni eventualmente specificate.
#	Le regole di costruzione rispecchiano la seguente tabella di verita':
#
# +---------------------------------------------------------------------------+
# | OPZIONI |                          DIRECTORIES                            |
# |---------+-------------------+----------------------+----------------------|
# |         | Var.int.: $mfDIR  | Var.int.: $dfDIR     | Var.int.: $diDIR     |
# |---------+-------------------+----------------------+----------------------|
# |    |    | tipo_comp_malf.mf |                      |                      |
# | -u | -l | malf_set.mf       |        *.dflt        |    direttive.mf      |
# |    |    | component.mf      |                      |                      |
# +----+----+-------------------+----------------------+----------------------+
# | No | No |        .          | .../libut_reg/libreg | .../libut_reg/libreg |
# | No | Si |        .          |        .             |        .             |
# | Si | No |       ..          | .../libut_reg/libreg | .../libut_reg/libreg |
# | Si | Si |       ..          |        .             |       ..             |
# +---------------------------------------------------------------------------+

sub	build_filenames()
{
#.......................................................................
#		Basenames
	$Clbn	= 'tipo_comp_malf.mf';			# "Classi"
	$Mfbn	= 'malf_set.mf';			# "Malfunzioni"
	$Isbn	= 'component.mf';			# "Istanze"
	$Dibn	= 'direttive.mf';			# "Direttive" per l'MF
	$Elfn	= 'ELENCO.MF';				# Elenco file *.scr prodotti

#.......................................................................
#		Directories
	$root	= $ENV{'LEGOCAD_USER'};
	if( length( $root ) < 1 )
	{
		die	"Non e' definita la variabile di ambiente: \$LEGOCAD_USER\n";
	}
	$CRTDIR	= './';
	$UPRDIR	= '../';
	$LIBDIR	= $root.'/legocad/libut_reg/libreg/';
	$mfDIR	= $CRTDIR;				# Default: directory locale
	$dfDIR	= $LIBDIR;				# Default: directory comune
	$diDIR	= $LIBDIR;				# Default: directory comune

	$mfDIR	= $UPRDIR if( $opt_u );
	if( $opt_l )
	{
		$dfDIR	= $CRTDIR;
		$diDIR	= $CRTDIR;
		$diDIR	= $UPRDIR if( $opt_u );
	}

#.......................................................................
#		Filenames
	$Clfn	= $mfDIR.$Clbn;
	$Mffn	= $mfDIR.$Mfbn;
	$Isfn	= $mfDIR.$Isbn;
	$Difn	= $diDIR.$Dibn;
}					# build_filenames()


#-----------------------------------------------------------------------
#	Controllo che i file di input siano accessibili

sub	check_files()
{
	die "Errore - Il file $Clfn non esiste.\n" unless( -e $Clfn );
	die "Errore - Il file $Clfn non e\` leggibile.\n" unless( -r $Clfn );
	die "Errore - Il file $Mffn non esiste.\n" unless( -e $Mffn );
	die "Errore - Il file $Mffn non e\` leggibile.\n" unless( -r $Mffn );
	die "Errore - Il file $Isfn non esiste.\n" unless( -e $Isfn );
	die "Errore - Il file $Isfn non e\` leggibile.\n" unless( -r $Isfn );
	die "Errore - Il file $Difn non esiste.\n" unless( -e $Difn );
	die "Errore - Il file $Difn non e\` leggibile.\n" unless( -r $Difn );
	die "Errore - Il file $dfDIR non e\` leggibile.\n" unless( -r $dfDIR );
}					# check_files()


#-----------------------------------------------------------------------
#	Inizializzazione delle variabili lette dal file 'direttive'

sub	init_dirett_var()
{
	$COLOR_BG	= $Di{ 'COLOR_BG' };
	$COLOR_FG	= $Di{ 'COLOR_FG' };
	$COLOR_LA	= $Di{ 'COLOR_LA' };
	$COLOR_TI	= $Di{ 'COLOR_TI' };
	$F_		= $Di{ 'F_' };
	$FONT_LA	= $Di{ 'FONT_LA' };
	$FONT_TI	= $Di{ 'FONT_TI' };
	$H_MAX		= $Di{ 'H_MAX' };
	$H_MIN		= $Di{ 'H_MIN' };
	$LABEL_TI	= $Di{ 'LABEL_TI' };
	$LABEL_D1	= $Di{ 'LABEL_D1' };
	$LABEL_D2	= $Di{ 'LABEL_D2' };
	$LABEL_NS	= $Di{ 'LABEL_NS' };
	$LABEL_DC	= $Di{ 'LABEL_DC' };
	$MARG_INF	= $Di{ 'MARG_INF' };
	$MARG_SUP	= $Di{ 'MARG_SUP' };
	$MARG_DX	= $Di{ 'MARG_DX' };
	$MARG_SX	= $Di{ 'MARG_SX' };
	$PPC_LA		= $Di{ 'PPC_LA' };
	$PPC_TI		= $Di{ 'PPC_TI' };
	$W_MAX		= $Di{ 'W_MAX' };
	$W_MIN		= $Di{ 'W_MIN' };
	$Y_INCR		= $Di{ 'Y_INCR' };
	$Y_SPACE	= $Di{ 'Y_SPACE' };
	$FONT_LA	= 'fixed' if( $FONT_LA eq '' );
	$FONT_TI	= 'fixed' if( $FONT_TI eq '' );

	$F_	= 'Y_' if( $F_ eq '' );	# Default
	$Wcrnt	= $W_MIN;
#+printf	"(1) {$LABEL_TI}	{$LABEL_D1}	{$LABEL_D2}	{$LABEL_NS}	{$LABEL_DC}\n";
	$LABEL_D1	= ( $LABEL_D1 =~ /no/i ) ? 0 : 1;
	$LABEL_D2	= ( $LABEL_D2 =~ /no/i ) ? 0 : 1;
	$LABEL_NS	= ( $LABEL_NS =~ /no/i ) ? 0 : 1;
	$LABEL_DC	= ( $LABEL_DC =~ /no/i ) ? 0 : 1;
#+printf	"(2) {$LABEL_TI}	{$LABEL_D1}	{$LABEL_D2}	{$LABEL_NS}	{$LABEL_DC}\n";

}					# init_dirett_var()


#-----------------------------------------------------------------------
sub	read_CLASSI()
{
	open( IFH, $Clfn );
	while( <IFH> )
	{
		chop;
#	I campi iniziano da 1 e anche quelli vuoti sono rilevati
		s/
$//;
		$line	= $RS.$_.$RS.$EOR;

#.......................................................................
#	Estrazione dei campi
		@ttt	= split( $RS, $line );
		for( $j = 0; $j <= $#ttt; $j++ )
		{
			last if( $ttt[$j] eq $EOR );
#+			printf	"% 3d) {$ttt[$j]}\n";
		}
		$ClId	= $ttt[1];		# Classi - Identificativo
		$ClNm	= $ttt[2];		# Classi - Nome della Classe
		$ClD1	= $ttt[3];		# Classi - Descrizione 1
		$ClD2	= $ttt[4];		# Classi - Descrizione 2
		$RegM	= $ttt[5];		# Classi - Modulo di Regolazione
		$VpPx	= $ttt[6];		# Classi - Var. Primaria  / Prefisso
		$VsPx1	= $ttt[7];		# Classi - Var. Secondaria/ Prefisso
		$VsDe1	= $ttt[8];		# Classi - Var. Secondaria/ Descrizione
		$VsPt1	= $ttt[9];		# Classi - Var. Secondaria/ Perturbazione
		$VsVa1	= $ttt[10];		# Classi - Var. Secondaria/ Valore
		$VsPx2	= $ttt[11];
		$VsDe2	= $ttt[12];
		$VsPt2	= $ttt[13];
		$VsVa2	= $ttt[14];
		$VsPx3	= $ttt[15];
		$VsDe3	= $ttt[16];
		$VsPt3	= $ttt[17];
		$VsVa3	= $ttt[18];
		$VsPx4	= $ttt[19];
		$VsDe4	= $ttt[20];
		$VsPt4	= $ttt[21];
		$VsVa4	= $ttt[22];
		if( $opt_x )
		{
printf	"\n{$ClId} {$ClNm} {$ClD1} {$ClD2} {$RegM} {$VpPx}\n";
printf	"Vs/1: {$VsPx1} {$VsDe1} {$VsPt1} {$VsVa1}\n";
printf	"Vs/2: {$VsPx2} {$VsDe2} {$VsPt2} {$VsVa2}\n";
printf	"Vs/3: {$VsPx3} {$VsDe3} {$VsPt3} {$VsVa3}\n";
printf	"Vs/4: {$VsPx4} {$VsDe4} {$VsPt4} {$VsVa4}\n";
		}
		$TClNm[$ClId]	= $ClNm;
		$TClD1[$ClId]	= $ClD1;
		$TClD2[$ClId]	= $ClD2;
		$TVpPx[$ClId]	= $VpPx;
		$TVsPx1[$ClId]	= $VsPx1;
		$TVsDe1[$ClId]	= $VsDe1;
		$TVsPt1[$ClId]	= $VsPt1;
		$TVsVa1[$ClId]	= $VsVa1;
		$TVsPx2[$ClId]	= $VsPx2;
		$TVsDe2[$ClId]	= $VsDe2;
		$TVsPt2[$ClId]	= $VsPt2;
		$TVsVa2[$ClId]	= $VsVa2;
		$TVsPx3[$ClId]	= $VsPx3;
		$TVsDe3[$ClId]	= $VsDe3;
		$TVsPt3[$ClId]	= $VsPt3;
		$TVsVa3[$ClId]	= $VsVa3;
		$TVsPx4[$ClId]	= $VsPx4;
		$TVsDe4[$ClId]	= $VsDe4;
		$TVsPt4[$ClId]	= $VsPt4;
		$TVsVa4[$ClId]	= $VsVa4;
		$ClNo	= $ClId if( $ClId > $ClNo );
	}
	printf	"%-40s - No. Classi      : $ClNo\n", $Clfn unless( $opt_Q );
	if( $opt_c )
	{
		printf	"            Classe     No. elementi\n";
		for( $j = 0; $j <= $ClNo; $j++ )
		{
			printf	":TClNm[%02d]: $TClNm[$j]\n", $j;
		}
		printf	"\n";
	}
	close( IFH );
}					# read_CLASSI()

#-----------------------------------------------------------------------
# Elabora un file contenente righe del tipo:
#			0.0;4;NORMAL WORKING 0.0
#			1.0;4;OPEN VOLTAGE CIRCUIT 1.0
#			2.0;4;CLOSED VOLTAGE CIRCUIT 2.0
#			3.0;4;NOISE WORKING 3.0
# avendo presente che gli identificativi delle classi e delle malfunzioni
# non sono necessariamente consecutivi.
# Allo scopo utilizza la variabile:
#	- $liCl		che concatena tutti gli ID Classe
# e per ogni ID Classe la variabile:
#	- $liMf[...]	che concatena tutti gli ID Malfunzione

sub	read_MALFUN()
{
	open( IFH, $Mffn );
	while( <IFH> )
	{
		chop;
		s/
$//;
		printf	"% 4d *** $_\n", $. unless( $opt_q || $opt_Q );
# NOTA: I campi iniziano da 1 e anche quelli vuoti sono rilevati
		$line	= $RS.$_.$RS.$EOR;

#.......................................................................
#	Estrazione dei campi
		@ttt	= split( $RS, $line );
		for( $j = 0; $j <= $#ttt; $j++ )
		{
			last if( $ttt[$j] eq $EOR );
		}
		$MfId	= int( $ttt[1] );	# Malfunzioni - Id Malfunzione
#+		$MfId	=~ s/\..*//;		# elimina il decimale
		$ClId	= $ttt[2];		# Malfunzioni - Id Classe
		$MfDe	= $ttt[3];		# Malfunzioni - Descrizione

		if( $liCl !~ /$ss$ClId$ss/ )
		{
			$liCl	.= "$ClId$ss";		# concatena la nuova classe
		}
		$liMf[$ClId]	= $ss if( length($liMf[$ClId]) == 0 );	# inizializza
		$liMf[$ClId]	.= "$MfId$ss";				# concatena
		$TMfDe{ $ClId }{ $MfId }	= $MfDe;
		printf	"+TMfDe[%02d][%02d]: $TMfDe{ $ClId }{ $MfId }\n", $ClId, $MfId if( $opt_x );
		$ClNo	= $ClId if( $ClId > $ClNo );
	}
	@ccc	= split( $ss, $liCl );
	$MfNo	= $#ccc;
	printf	"%-40s - No. Malfunzioni : $MfNo\n", $Mffn unless( $opt_Q );
	for( $j = 1; $j <= $#ccc; $j++ )
	{
		printf	"% 3d)    *** $ccc[$j] ***\n", $j unless( $opt_q || $opt_Q );
	}

	if( $opt_m )
	{
		printf	"       Cl  Mf   Malfunzione\n";
		for( $j = 1; $j <= $#ccc; $j++ )
		{
			$c	= $ccc[$j];
			@mmm	= split( $ss, $liMf[$c] );
			for( $k = 1; $k <= $#mmm; $k++ )
			{
				$m	= $mmm[$k];
				printf	":TMfDe[%02d][%02d]: $TMfDe{ $c }{ $m }\n", $c, $m;
			}
		}
		printf	"\n";
	}
	close( IFH );
}					# read_MALFUN()


#-----------------------------------------------------------------------

sub	read_ISTANZ()
{
	open( IFH, $Isfn );
	$IsNo	= 0;			# No. entry Istanz
	while( <IFH> )
	{
		$IsNo++;
		chop;
		s/
$//;
#	I campi iniziano da 1 e anche quelli vuoti sono rilevati
		$line	= $RS.$_.$RS.$EOR;

#.......................................................................
#	Estrazione dei campi
		@ttt	= split( $RS, $line );
		for( $j = 0; $j <= $#ttt; $j++ )
		{
			last if( $ttt[$j] eq $EOR );
#+			printf	"% 3d) {$ttt[$j]}\n";
		}
		$ClId	= $ttt[1];
		$IsDe	= $ttt[2];
		$IsKk	= $ttt[3];
		$IsVp	= $ttt[4];
		$IsV1	= $ttt[5];
		$IsV2	= $ttt[6];
		$IsV3	= $ttt[7];
		$IsV4	= $ttt[8];
		$TIsCl[$IsNo]	= $ClId;	# Istanze - Classe
		$TIsDe[$IsNo]	= $IsDe;	# Istanze - Descrizione
		$TIsKk[$IsNo]	= $IsKk;	# Istanze - KKS
		$TIsVp[$IsNo]	= $IsVp;	# Istanze - cod. reg. Var. Principale
		$TIsV1[$IsNo]	= $IsV1;	# Istanze - cod. reg. Var. 1
		$TIsV2[$IsNo]	= $IsV2;	# Istanze - cod. reg. Var. 2
		$TIsV3[$IsNo]	= $IsV3;	# Istanze - cod. reg. Var. 3
		$TIsV4[$IsNo]	= $IsV4;	# Istanze - cod. reg. Var. 4
	}
	printf	"%-40s - No. Istanze     : $IsNo\n", $Isfn unless( $opt_Q );
	if( $opt_i )
	{
		printf	"            Istanza\n";
		for( $j = 1; $j <= $IsNo; $j++ )
		{
			printf	":TIsKk[%02d]: $TIsKk[$j]\n", $j;
		}
		printf	"\n";
	}
	close( IFH );
}					# read_ISTANZ()


#-----------------------------------------------------------------------

sub	read_DIRETT()
{
	$DiKeyword	= '#';
	$DiKeyword	.= 'COLOR_BG#COLOR_FG#COLOR_LA#COLOR_TI#';
	$DiKeyword	.= 'F_#';
	$DiKeyword	.= 'FONT_TI#FONT_LA#PPC_LA#PPC_TI#';
	$DiKeyword	.= 'H_MIN#H_MAX#W_MIN#W_MAX#';
	$DiKeyword	.= 'LABEL_TI#LABEL_D1#LABEL_D2#LABEL_NS#LABEL_DC#';
	$DiKeyword	.= 'MARG_SUP#MARG_INF#MARG_SX#MARG_DX#';
	$DiKeyword	.= 'Y_INCR#Y_SPACE#';

	open( IFH, $Difn );
	$DiNo	= 0;			# No. entry
	while( <IFH> )
	{
		chop;
		$line	= $_;
#//		$line	=~ s/^[\t\s]*//;
		next if( $line eq '' || substr( $line, 0, 1 ) eq '#' );
		if( $line =~ /=/ )
		{
			$k	= $`;
			$v	= $';
			$k	=~ s/[\t\s]//g;
			$k	=~ tr/[a-z]/[A-Z]/;
			if( $DiKeyword =~ /#$k#/ )
			{
				$DiNo++;
				$Di{ $k }	= $v;
			}
			else
			{
				printf	"Keyword non riconosciuta: <$k>\n";
			}
		}
		else
		{
			printf	"% 4d. - Manca il carattere: '=' |$line|\n", $.;
		}
	}

	printf	"%-40s - No. Direttive   : $DiNo\n", $Difn unless( $opt_Q );
	if( $opt_d )
	{
		foreach $key ( sort keys %Di )
		{
			$value	= $Di{$key};
			printf	"%-16s	%s\n", $key, $value;
		}
	}
	close( IFH );
}					# read_DIRETT()


#-----------------------------------------------------------------------

sub	updateWcrnt()
{
# updateWcrnt( $x, $MfDe, $PPC_LA );
local( $xc, $txt, $ppc )	= @_;
local( $lll, $www );

	$lll	= length( $txt );
	$ppp	= $lll * $ppc;
	$www	= $x + int($ppp);
	printf	PFH "# [$Wcrnt]  $lll * $ppc = $ppp /// $x + int($ppp) = $www\n";
	if( $www > $Wcrnt )
	{
		printf	"Wcrnt: % 4d >>==>> % 4d\n", $Wcrnt, $www if( $opt_x );
		$Wcrnt	= $www;
	}
}					# updateWcrnt()


#=======================================================================
#	MAIN

#-----------------------------------------------------------------------
#	Inizializzazioni

$RS	= ';';
$EOR	= '<><>';

$ss	= '#';				# Separatore Standard
$liCl	= $ss;				# Ini variabile: lista-classi

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .-
#	Colori (trasferire nel file DIRETT.MF)
$red	= '#ffff00000000';
$giallo	= '#ffffffff0000';
$verde	= '#0000ffff0000';
$grigio	= '#a3a3babad4d4';

#-----------------------------------------------------------------------
#	Acquisizione e controllo di opzioni e argomenti

$argc1	= $#ARGV;
#+printf	"[ $argc1 ]	{@ARGV} <$ARGV[0]>\n";
Getopts( $Opts );
$argc2	= $#ARGV;
#+printf	"[ $argc2 ]	{@ARGV} <$ARGV[0]>\n";

if( $opt_V )
{
	printf	"$Ver\n";
	exit;			# -V
}

do build_filenames();

#+ if( $opt_h || $#ARGV < 0 ) : Con lo switch -x (?!) e' inefficace, quindi: trucco.
if( $opt_h || $argc2 < 0 || ($argc1 == 0 && $argc2 == 0 && $ARGV[0] eq '') )
{
	printf	"$Help\n";
	printf	"File classi      : %-60s %s\n", $Clfn , (-r $Clfn)  ? '( OK)':'(NOK)';
	printf	"File malfunzioni : %-60s %s\n", $Mffn , (-r $Mffn)  ? '( OK)':'(NOK)';
	printf	"File istanze     : %-60s %s\n", $Isfn , (-r $Isfn)  ? '( OK)':'(NOK)';
	printf	"Directory *.dflt : %-60s %s\n", $dfDIR, (-r $dfDIR) ? '( OK)':'(NOK)';
	printf	"File direttive   : %-60s %s\n", $Difn , (-r $Difn)  ? '( OK)':'(NOK)';
	exit;			# -h / arg. insuff.
}

do check_files();

#-----------------------------------------------------------------------
#	Elaborazione

printf	"\
MF - Costruisce gli script Y_*.scr dai file: $Clfn , $Mffn , $Isfn\
     e in base ai parametri del file       : $Difn\n\n" unless( $opt_q || $opt_Q );

do read_CLASSI();
do read_MALFUN();
do read_ISTANZ();

do read_DIRETT();

do bld_place_script();

#-----------------------------------------------------------------------
#	Lancio della shell di creazione pagine

system( "chmod a+rx $Elfn" );
#+ system( "pg $Elfn" );

if( "$opt_p" ne '' )
{
#+	printf	"opt_p: |$opt_p|\n";
	$opt_p	= '' if( $opt_p eq 'N' );
	printf	"$Elfn $opt_p\n";
	system( "$Elfn \"$opt_p\" " );
}

