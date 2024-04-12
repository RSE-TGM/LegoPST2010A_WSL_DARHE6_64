#Uso:  untab rgb.txt | perl rgb.pl | sort +0.24 > rgb.col
#

while( <> )
{
	chop;
	$rgb	= " ".substr( $_,  0, 13 );
	$rgb	=~ s/[ ]+/ /g;
	(@ccc)	= split( / /, $rgb );
	$r	= $ccc[1];
	$g	= $ccc[2];
	$b	= $ccc[3];
	$col	= substr( $_, 24, 99 );
#+	printf	"ccc: <@ccc> {$col}\n";
	printf	"%-23s %03d %03d %03d \n", $col, $r, $g, $b;
#+	printf	"%-23s$rgb\n", $col;
}
