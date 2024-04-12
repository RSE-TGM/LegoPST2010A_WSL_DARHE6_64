#@(#)rgb1.pl

while( <> )
{
#+	printf	"$_";
	chop;
	$col	= substr( $_,  0, 24 );
	$w	= substr( $_, 24, 88 );
	(@ttt)	= split( / /, $w );
#+	printf	"ttt: @ttt\n";
	$sum	= 0;
	for( $j = 0; $j < 3; $j++ )
	{
		$sum	+= $ttt[$j] * $ttt[$j];
#+		printf	"$j : $ttt[$j] * $ttt[$j] = $sum\n";
	}
	$rad	= sqrt( $sum );
	printf	"% 6ld. = sqrt(% 7.f) %-24s@ttt\n", $rad, $sum, $col;
}
