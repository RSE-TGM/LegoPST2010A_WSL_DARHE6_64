#!/bin/sh
eval 'exec perl -S -x $0 "$@"'
    if 0;
# La riga seguente e' necessaria ed e' collegata allo switch -x della riga precedente
#!perl

#=======================================================================
#@(#)PLACE	Posiziona ogg. in un pag da uno script 	1998-01-27

# Convenzioni:
#	Gli identificativi delle risorse di tipo "Input"  sono DISPARI
#	Gli identificativi delle risorse di tipo "Output" sono    PARI
#

#------------------------------------------------------------------------
#	Use & Require

use	Fcntl;
use	AnyDBM_File;

require	'getopts.pl';
require	'stat.pl';

#------------------------------------------------------------------------
#	Variabili relative alle opzioni

$Opts	= 'AaDhIkmPrSsVwX' ;

$Help	= "\
Uso:  PLACE  [ -AaDhIkPrSsVX ]  script-name.scr\
\
Opzioni:\
  -a	Stampa (nel doppio loop) tutti gli attributi del widget testati\
  -A	Stampa (nel doppio loop) solo  gli attributi del widget modificati rispetto al default\
  -D	Stampe di visualizzazione della letture/scritture nel DB (place.db)\
  -h	Questo testo di help\
  -I	Stampe di visualizzazione della elaborazione degli INCLUDE\
  -D	Stampe di visualizzazione delle scritture nel file *.pag\
  -k	Non cancella lo script al termine dell'elaborazione\
  -m	Stampa le righe prodotte dalla modify_PAGE\
  -P	Stampa le righe scritte nel file pagine prodotto\
  -r	Stampa le righe lette dallo script\
  -s	Stampa l' ingresso nelle subroutine e gli argomenti\
  -S	Stampa l' intestazione delle diverse Sezioni del programma\
  -V	Stampa la versione\
  -w	Stampa il nome simbolico e il nome attribuito ad un widget\
  -X	Stampe di visualizzazione nel DB (place.xx)\
\
Il risultato dell'elaborazione e` su un file di nome: script-name.pag\
";

$Ver	= "PLACE - Versione: 1.3 1998-01-27";

#========================================================================
#	SUBROUTINE

#-----------------------------------------------------------------------
sub	do_PAGE()
{

	$k	= 0;
	for( sort keys %place_db )
	{
		$k++;
		$Rvl	= $place_db{$_};
		chop	$Rvl;
#++		( $Rty, $Wid, $Cid, $Rnm )	= split( '/', $_ );
		( $Rty, $Cid, $Rnm )	= split( '/', $_ );
		next if( $Rty ne 'PAGE' );
		next if( $Rnm eq 'WIDGET_TYPE' );
		next if( $Rnm eq 'nomePag' );
		next if( $Rnm eq 'num_widget' );

		printf '>'.$Pfmt, $Rnm, $Rvl if( $opt_P );
		printf PFH $Pfmt, $Rnm, $Rvl;
	}
	printf '>'.$Pfmt, 'nomePag', $Pbn if( $opt_P );
	printf PFH $Pfmt, 'nomePag', $Pbn;
	printf '>'.$Pfmt, 'num_widget', $WDGK if( $opt_P );
	printf PFH $Pfmt, 'num_widget', $WDGK;
	printf '>'."$elenco\n" if( $opt_P );
	printf PFH "$elenco\n";

}					# do_PAGE()


#-----------------------------------------------------------------------
sub	do_script()
{
my ( $Sfn )	= @_;

	open( SFH, $Sfn );
	$state	= $IDLE;
	while( <SFH> )
	{
		chop;
		$line	= $_;
		$line	=~ s/^[\t\s]*//;
printf	".: %04d) [%d] $_\n", $., $state if( $opt_r );
		if( $state == $IDLE )
		{
			&idle();
			next;
		}
		if( $state == $PLACE )
		{
			&place();
			next;
		}
		if( $state == $MODIFY )
		{
			&modify_PAGE();
			next;
		}
	}
	close( SFH );
}					# do_script()



#-----------------------------------------------------------------------
sub	do_wgt_resources()
{
my ( $n, $t )	= @_;			# wgt-name , wgt-type
my ( $tR );				# wgt-REAL-type

	$tR	= read_db( $t, '', 'WIDGET_TYPE' );
	$WDGK++;
	$WDGN	+= 10;
	$Cid	= '';				# in prima istanza caso semplice
	$FatId	= sprintf( "%dw", $WDGN );	# Costruisce il FID
#%!	$elenco	.= ' '.$FatId.' '.$t;
	$elenco	.= ' '.$FatId.' '.$tR;		# Accoda all'elenco il FID ...
#+printf	"ATTENZIONE: |$FatId.' '.$t| <-?!?!-> |$FatId.' '.$t|\n";
	$WgtId	= $FatId.$Cid;
	$k	= 0;
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#	Innanzitutto "battezza" il widget
	$res	= $WgtId.'.nome';
	$Val	= $WgtId;
	printf '>'.$Pfmt, $res, $Val if( $opt_P );
	printf PFH $Pfmt, $res, $Val;

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#	Per tutti gli attributi del widget corrente ....
	for( sort keys %place_db )
	{
		$Val	= $place_db{ $_ };
		chop	$Val;
		( $Wnm, $Cid, $Att )	= split( "/", $_ );
		next unless( $Wnm eq $t );
		next if( $Att eq 'WIDGET_TYPE' );
		printf	"--- $_\n" if( $opt_a );
		$r_flg	= 0;
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#	.... verifica se vanno modificati in base allo script ....
DWR_X:
		for( sort keys %place_xx )
		{
			$val	= $place_xx{ $_ };
			chop	$val;
			( $wnm, $cnm, $att )	= split( "/", $_ );
			next unless( $wnm eq $n );
			next unless( $cid eq $Cid );	# Altrimenti i figli ereditano dal padre
			if( $att eq $Att )
			{
				$r_flg	= 1;
				printf	"@@@ $_\n" if( $opt_A );
				$Val	= $val;		# MODIFICA SPECIFICA DEL WDGT !
				last DWR_X;
			}
		}
		$WgtId	= $FatId.$Cid;
		$Val	=~ s/!!!/$FatId/g if( $Att eq 'listChildren' );	# <><><>
		$res	= $WgtId.'.'.$Att;
		printf '>'.$Pfmt, $res, $Val if( $opt_P );
		printf PFH $Pfmt, $res, $Val;

		$k++;
	}
	return	$WgtId;

}					# do_wgt_resources()


#-----------------------------------------------------------------------
sub	idle()
{
		printf	"\@ % 4d) {%-16s} %s\n", $., "idle", $line if( $opt_s );

#.......................................................................
#		Parsing della linea
#+		printf	"(0) |$line|\n";
#+...		$line	=~ s/^[\t\s]*//;
		return if( $line eq '' || substr( $line, 0, 1 ) eq '#' );
#+		printf	"(1) |$line|\n";
		@ttt	= split( /[\s\t]+/, ' '.$line );
#+		printf	"(2) [%02d] |@ttt|\n", $#ttt;
		$kwd	= $ttt[1];
		$wty	= $ttt[2];
#+		$wid	= $ttt[3];
		$wnm	= $ttt[3];
#+ printf	"<$kwd> <$wty> <$wnm>\n";
#.......................................................................
#		Controllo keyword
		if( $kwd eq 'INCLUDE' )
		{
			&include( $wty );
		}
		elsif( $kwd eq 'PLACE' )
		{
			$parse_flg	= 0;
			$state	= $PLACE;	# Default/potra' essere modificato dalla parse_PLACE()
			&parse_PLACE();
		}
		elsif( $kwd eq 'MODIFY' )
		{
			$modify_flg	= 0;
			$state	= $MODIFY;	# Default/potra' essere modificato dalla modify_PAGE()
			&modify_PAGE();
		}
		else
		{
			printf	"KEYWORD: %-30s Sconosciuta  - Linea ignorata\n", $kwd;
		}
}					# idle()


#-----------------------------------------------------------------------
sub	include()
{
my ( $Ifn )	= @_;
my ( $ln, $wt, $wn, $wi, $fi, $ci, $at, $va );

	$wn	= $Ifn;
	$wn	=~ s/\.dflt//;
	$wn	=~ s/.*\///;
	printf	"<<< include: <$Ifn>  wn=<$wn>\n" if( $opt_I );
	open( IFH, $Ifn );
	while( <IFH> )
	{
		chop;
		printf	"%04d) $_\n", $. if( $opt_I );
		if( $. == 1 )
		{
			$wt	= $wn;		# Default: Wty == Wnm
			if( $_ =~ /^WIDGET_TYPE=/ )
			{
				$wt	= $_;
				$wt	=~ s/WIDGET_TYPE=//;
				printf	"Keyword WIDGET_TYPE !! ($wt)\n" if( $opt_I );
			}
#......................................................................-
#+ ?/!			$avWty	.= $wt.'#';	# registra nuovo Wty
			$avWty	.= $wn.'#';	# registra nuovo Wty
			printf	"avWty: <$avWty>\n" if( $opt_I );
			&write_db( $wn, '', 'WIDGET_TYPE', $wt );	# include
			next	if( $_ =~ /^WIDGET_TYPE=/ );
		}
		$wi	= $_;
		$wi	=~ s/^\*//;		# Elimina * iniziale
		$wi	=~ s/:.*//;		# Elimina :....
		if( $wi =~ /\./ )		# Se c'e` WID estrae FID e CID
		{
			$fi	= $`;
			$ci	= $fi;
			if( $ci =~ /c/ )
			{
				$ci	=~ s/.*w//;	# A regime: cn !
			}
			else
			{
				$ci	= '';
			}
		}
		else
		{
			$fi	= '';
			$ci	= '';
		}
		$at	= $wi;
		$at	=~ s/.*\.//;		# Elimina eventuale widget-id
		next	if( $at eq 'nome' );	# Scarta l'attributo: 'nome'
		$va	= $_;
		$va	=~ s/.*:\t//;
		$va	=~ s/$fi/!!!/g if( $at eq 'listChildren' );	# <><><>
		printf	"Wty:%-20s Wnm:%-20s Fid:%-20s Cid:%-20s Att:%-20s Val:%-20s\n",
				"{$wt}", "{$wn}", "{$fi}", "{$ci}", "{$at}", "{$va}" if( $opt_I );
		&write_db( $wn, $ci, $at, $va );			# include
	}
	close( IFH );
	printf	"%-20s : #$.\n", $Ifn if( $opt_I );

}					# include()



#-----------------------------------------------------------------------
#	Parse della linea di tipo: "PLACE WidgetType WidgetName"
#
#	Salva ogni WidgetName nella variabile: usWnm

sub	modify_PAGE()
{
printf	"\@ % 4d) {%-16s} %s\n", $., "modify_PAGE/$modify_flg", $line if( $opt_s );

	if( $modify_flg++ == 0 )
	{
#.......................................................................
#	Controllo esistenza widget-type e unicita' widget-name

		if( $avWty =~ /#$wty#/ )
		{
#+			printf "....  WIDGET_TYPE: %-30s Riconosciuto - ($wnm)\n", $wty;

# La riga seguente per ricordare il widget-type del widget.
#+			&write_xx( $wnm, '@@@', '@@@', $wty );		# place
		}
		else
		{
			printf	"****  WIDGET_TYPE: %-30s Sconosciuto  - Line ignorata\n", $wty;
			$state	= $IDLE;
			return;
		}
	}
	else
	{
#.......................................................................
#	Se ENDMODIFY: cambia stato e ritorna

		if( /ENDMODIFY/ )
		{
#+			printf	"ENDMODIFY detected !\n";
			$state	= $IDLE;
			return;
		}
#.......................................................................
#	Analisi ed esecuzione della linea corrente
#
# Sintassi:	Attribute=Value
#		normFg=#00000000ffff

		if( $line !~ /=/ )
		{
			printf	"Manca il segno di '=' - Linea errata: ignorata:\n";
			printf	"%04d) $line\n", $.;
			return;
		}
		$Att	= $`;
		$Val	= $';
		printf	"modify_PAGE: |$Att| |$Val|\n" if( $opt_m );
		&write_db( 'PAGE', '', $Att, $Val );				# place
	}

}					# modify_PAGE()


#-----------------------------------------------------------------------
#	Parse della linea di tipo: "PLACE WidgetType WidgetName"
#
#	Salva ogni WidgetName nella variabile: usWnm

sub	parse_PLACE()
{
printf	"\@ % 4d) {%-16s} %s\n", $., "parse_PLACE/$parse_flg", $line if( $opt_s );

#.......................................................................
#	Controllo esistenza widget-type e unicita' widget-name

		if( $avWty =~ /#$wty#/ )
		{
#+			printf "....  WIDGET_TYPE: %-30s Riconosciuto - ($wnm)\n", $wty;

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ..
#	Se e`un XlComposite estrae la lista dei figli
			if( $wty eq 'XlComposite' )
			{
#+				$key	= join( '/', $wty, '', '', 'listChildren' );
#+				$lll	= $place_db{$key};
				$lll	= read_db( $wty, '', 'listChildren' );
				@ccc	= split( '\s', $lll );
				for ( $j = 0; $j <= $#ccc; $j += 2 )
				{
					$k	= ($j+1)/2;
					eval "\$C$k = \$ccc[$j+1];";
					eval "\$CX = \$ccc[$j];";
					$CX	=~ s/!!!//;
					printf	"<%d> $CX %s\n", $j+1, $ccc[$j+1];
				}
			}
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ..
#+ printf	"usWnm: <$usWnm> ... $wnm ?\n";
			if( $usWnm !~ /#$wnm#/ )
			{
				$usWnm	.= $wnm.'#';	# registra nuovo Wnm
			}
			else
			{
				printf	"****  WDGTNAME: %-30s Gia' utilizzato - Linea ignorata\n", $wnm;
				$state	= $IDLE;	# Widget-name in uso !
				return;
			}
#+			$state	= $PLACE;
# La riga seguente per ricordare il widget-type del widget.
			&write_xx( $wnm, '@@@', '@@@', $wty );		# place
		}
		else
		{
			printf	"****  WIDGET_TYPE: %-30s Sconosciuto  - Line ignorata\n", $wty;
			$state	= $IDLE;		# Widget-type sconosciuto !
			return;
		}

}					# parse_PLACE()


#-----------------------------------------------------------------------
#		Elaborazione risorsa

sub	place()
{
printf	"\@ % 4d) {%-16s} %s\n", $., "place", $line if( $opt_s );

#.......................................................................
#	Se ENDPLACE: cambia stato e ritorna

	if( /ENDPLACE/ )
	{
#+		printf	"ENDPLACE detected !\n";
		$state	= $IDLE;
		return;
	}

#.......................................................................
#	Analisi ed esecuzione della linea corrente
#
# Sintassi:	[Cid.]resource=value
# Sintassi:	[Cid.]Attribute=Value
#		8c.normFg=#00000000ffff
# N.B.:		Provvisoriamente il Cid dovra' corrispondere a quello
#		utilizzato nel file *.dflt

	if( $line !~ /=/ )
	{
		printf	"Manca il segno di '=' - Linea errata: ignorata:\n";
		printf	"%04d) $line\n", $.;
		return;
	}
	$Att	= $`;
	$Val	= $';
	$Cid	= $Att;
	if( $Cid =~ /\./ )
	{
		$Cid	=~ s/\..*//;
	}
	else
	{
		$Cid	= '';
	}
	$Att	=~ s/.*\.//;
	$Wid	= $wid;
#+	$key	= join( "/", $rty, $Wid, $Cid, $Rnm );
#/	delete $place_db{ $key };		# Cancella dal DB

#***	&write_db( $Wnm, $Cnm, $Att, $Val );				# place
	&write_xx( $wnm, $Cid, $Att, $Val );				# place

}					# place()


#-----------------------------------------------------------------------
#		Lettura dal DB place_db

sub	read_db()
{
my ( $w, $c, $a )	= @_;

	$readsw	= 1;				# 1:  OK
	$k	= join( "/", $w, $c, $a );
	$v	= $place_db{"$k"};
	$readsw	= 0 if( length($v) < 1 );	# 0: NOK
	chop	$v;
#+ printf	"{$w} {$c} {$a}\n";
#+ printf	"{$k} <::< {$v}\n";
	return	$v;

}					# read_db()


#-----------------------------------------------------------------------
#		Scrittura nel DB place_db

sub	write_db()
{
my ( $w, $c, $a, $v )	= @_;

	$k	= join( "/", $w, $c, $a );
	printf	"{$k} >::> {$v}\n" if( $opt_D );
	delete $place_db{ $k };		# Cancella dal DB
	$place_db{"$k"}	= $v.$TAV;

}					# write_db()

#-----------------------------------------------------------------------
#		Scrittura nel AA place_xx

sub	write_xx()
{
my ( $w, $c, $a, $v )	= @_;

	$k	= join( "/", $w, $c, $a );
	printf	"{$k} >@@> {$v}\n" if( $opt_D );
#	delete $place_xx{ $k };		# Cancella dal DB
	$place_xx{"$k"}	= $v.$TAV;

}					# write_xx()


#=======================================================================
#	MAIN

#-----------------------------------------------------------------------
#	Inizializzazioni

$TAV	= '{';			# Tappo Anti-Vuoto
$TAV	= '@';			# Tappo Anti-Vuoto
$HASH	= '#';

$IDLE	= 0;			# Stato interno
$PARSE	= 1;			# Stato interno
$PLACE	= 2;			# Stato interno
$MODIFY	= 3;			# Stato interno

$Pfn	= 'PLACE.pag';		# Default Output filename
$Pbn	= 'PLACE';		# Default Output basename
$Sfn	= 'PLACE.scr';		# Default Script filename

$Pfmt	= "*%s:\t%s\n";		# Page output format

$avWty	= '#';			# Available Widget Types
$usWnm	= '#';			# Used      Widget Names
$KWDG	= 0;			# Contatore widget (father)
$elenco	= '*elenco_wid0:	\\';		# Inizializza l'elenco

#-----------------------------------------------------------------------
#	Acquisizione e controllo di opzioni e argomenti

Getopts( $Opts );

if( $opt_V )
{
	printf	"$Ver\n";
	exit;
}

if( $opt_h || $#ARGV < 0 )
{
	printf	"$Help\n";
	exit;
}

$Sfn	= $ARGV[0];
unless( -e $Sfn )
{
	printf	"Lo script: $Sfn non esiste\n";
	exit;
}

unless( -r $Sfn )
{
	printf	"Lo script: $Sfn non e` accessibile\n";
	exit;
}

unless( $Sfn =~ /\.scr$/ )
{
	printf	"Il nome dello script DEVE avere l'extension: .scr\n";
	exit;
}

$Pfn	= $Sfn;
$Pfn	=~ s/\.scr$/.pag/;
$Pbn	= $Pfn;
$Pbn	=~ s/\.pag$//;
#+ printf	"<$Sfn> <$Pfn> <$Pbn>\n";

($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
$dataora	= sprintf( "%02d-%02d-%02d %02d:%02d:%02d", $year, $mon+1, $mday, $hour, $min, $sec );
printf	"\n$Ver *** Inizio *** $dataora \@\@\@ $Pbn\n";

#-----------------------------------------------------------------------
#	"Tie" dei database
#	Con le opzioni seguenti ricostruisce ogni volta il DB !

tie( %place_db, AnyDBM_File, "place.db", O_CREAT|O_TRUNC|O_RDWR, 0644 )  || die( "Sorry" );
tie( %place_xx, AnyDBM_File, "place.xx", O_CREAT|O_TRUNC|O_RDWR, 0644 )  || die( "Sorry" );

#-----------------------------------------------------------------------
#	Lettura degli 'include"

#	printf	"S: LETTURA DEGLI INCLUDE\n" if( $opt_S );
#	&include( 'MyWid.dflt' );
#	&include( 'PAGE.dflt' );
#	&include( 'Bottone.dflt' );
#	&include( 'Icon.dflt' );
#	&include( 'Label.dflt' );
#	&include( 'XlComposite.dflt' );

#-----------------------------------------------------------------------
#	Apertura file *.pag

open( PFH, ">$Pfn" );
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
$dataora	= sprintf( "%02d-%02d-%02d %02d:%02d:%02d", $year, $mon+1, $mday, $hour, $min, $sec );

printf '>'."#File:$Pfn - Prodotto da PLACE / Script: $Sfn - $dataora\n" if( $opt_P );
printf PFH "#File:$Pfn - Prodotto da PLACE / Script: $Sfn - $dataora\n";

#-----------------------------------------------------------------------
#	Lettura dello script

printf	"S: LETTURA DELLO SCRIPT\n" if( $opt_S );
&do_script( $Sfn );

#-----------------------------------------------------------------------
#	"Pop" dei widget-name richiesti

printf	"S: LOOP DI OUTPUT DEI WIDGET RICHIESTI\n" if( $opt_S );
$KWDG	= 0;			# Contatore widget (father)
@aWnm	= split( '#', $usWnm );
#+ printf	"aWnm: @aWnm\n";
for( $j = 1; $j <= $#aWnm; $j++ )
{
	$wtype	= $place_xx{ $aWnm[$j].'/@@@/@@@' };
	chop	$wtype;					# TAV
	$wname	= $aWnm[$j];
#+	printf	"% 3d./do_wgt_resources( |%-16s| |%s| )\n", $j, $wtype,  $wname;
	$wgt_id	= &do_wgt_resources( $wname, $wtype );
	printf	"% 3d./do_wgt_resources: %-16s %-6s >-> %9s\n", $j, $wtype,  $wname, $wgt_id if( $opt_w );
}

printf	"S: OUTPUT DELLE RISORSE DI PAGINA\n" if( $opt_S );
&do_PAGE();

#-----------------------------------------------------------------------
#	Chiusura

if( $opt_X )
{
	foreach $key ( keys %place_xx )
	{
		$value	= $place_xx{$key};
		printf	"place_xx: {$key} {$value}\n";
	}
}

close( PFH );
untie( %place_db );
untie( %place_xx );

system( "/bin/rm -f $Sfn" ) unless( $opt_k );
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
$dataora	= sprintf( "%02d-%02d-%02d %02d:%02d:%02d", $year, $mon+1, $mday, $hour, $min, $sec );
printf	"$Ver *** Fine   *** $dataora \@\@\@ $Pbn\n";

