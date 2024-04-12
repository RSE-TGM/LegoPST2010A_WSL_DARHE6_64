#for( $j = 0; $j < 100; $j++ )
#{
#	printf	"touch M%02d.o\n", $j;
#}

for( $j = 0; $j < 10; $j++ )
{
	printf	"L$j.a:	";
	for( $k = 0; $k < 10; $k++ )
	{
		printf	"M$j$k.o ";
	}
	printf	"\n";

	printf	"	ar -ru L$j.a";
	for( $k = 0; $k < 10; $k++ )
	{
		printf	" M$j$k.o";
	}
	printf	"\n";
}

