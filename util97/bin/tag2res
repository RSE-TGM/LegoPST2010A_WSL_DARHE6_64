#@(#)TAG2RES	Interfaccia tra un file *.tag e il comando 'pagmod'	1997-07-10

#=======================================================================
#	ROUTINE

#-----------------------------------------------------------------------
build_awk()
{
	cat << EOT > $afn
#@(#)TAG2RES.awk	Richiamato dalla shell TAG2RES		1997-07-09

#-----------------------------------------------------------------------
#	Trasforma un file *.tag del tipo:

#:#	Riga di commento - Sono ammesse righe vuote - Placeholder: '^'
#:
#:objectTag	valoreMinimo	valoreMassimo	scalamento	varInputBlink
#:
#:tag1		-777		777		77		QUALSIASI
#:tag2		-888		888		^		QUALSIVOGLIA
#:blink		-999		999		99		ABCD1234~C77777CS~CSREG0~NOT~1.0~0.0~---

#	Nel seguente script (per il programma 'pagmod') :

#:#TAG2RES.scr - Script ottenuto dal file: T1.tag
#:
#:anywidget=
#:	hasattrib=objectTag
#:	value=tag1
#:	attrib=valoreMinimo
#:	value=-777
#:	attrib=valoreMassimo
#:	value=777
#:	attrib=scalamento
#:	value=77
#:	attrib=varInputBlink
#:	value=QUALSIASI
#:
#:anywidget=
#:	hasattrib=objectTag
#:	value=tag2
#:	attrib=valoreMinimo
#:	value=-888
#:	attrib=valoreMassimo
#:	value=888
#:	attrib=scalamento
#:	value=QUALSIVOGLIA
#:anywidget=
#:	hasattrib=objectTag
#:	value=blink
#:	attrib=valoreMinimo
#:	value=-999
#:	attrib=valoreMassimo
#:	value=999
#:	attrib=scalamento
#:	value=99
#:	attrib=varInputBlink
#:	value=ABCD1234 C77777CS CSREG0 NOT 1.0 0.0 ---

#	NOTA BENE:
#(1) E' possibile inserire nel file tag righe vuote o commenti (iniziano con #)
#(2) La suddivisione di una linea in campi avviene secondo le regole dell' awk
#(3) Tutte le righe utili devono avere lo stesso numero di campi della prima
#(4) La prima riga utile del file tag deve iniziare con la risorsa 'objectTag'
#(5) Attualmente il numero massimo di colonne interpretate nel file tag e' 20
#(6) E' possibile specificare campi contenenti spazi utilizzando invece dello
#    spazio il carattere ~(tilde) che viene convertito in spazio dopo
#    l' esecuzione dell' awk
#-----------------------------------------------------------------------

#=======================================================================
BEGIN {
	ln_flg	= 1;			# .........
	nf_max	= 20;			# Numero massimo di colonne riconosciute
	tagkw	= "objectTag";		# keyword che identifica le tag
	plchld	= "^";			# carattere placeholder nel file tag

	printf( "#TAG2RES.scr - Script ottenuto dal file: %s\n", FILENAME );
}

#-----------------------------------------------------------------------
{
	if( length( \$0 ) < 1 ) next;
	if( substr( \$1, 1, 1 ) == "#" ) next;

	if( ln_flg )
	{
#-----------------------------------------------------------------------
#	Riga attributi
		if( \$1 != tagkw )
		{
			printf( "La riga attributi deve iniziare con la keyword: %s\n", tagkw );
			exit;
		}
		nf	= NF;		# No. campi che devono comparire in ogni riga
		if( nf > 20 )
		{
			printf( "Il file tag puo' avere al piu' %d colonne\n", nfmax );
			exit;
		}
		ln_flg	= 0;
#.......................................................................
		att[1]	=  \$1;
		att[2]	=  \$2;
		att[3]	=  \$3;
		att[4]	=  \$4;
		att[5]	=  \$5;
		att[6]	=  \$6;
		att[7]	=  \$7;
		att[8]	=  \$8;
		att[9]	=  \$9;
		att[10]	= \$10;
		att[11]	= \$11;
		att[12]	= \$12;
		att[13]	= \$13;
		att[14]	= \$14;
		att[15]	= \$15;
		att[16]	= \$16;
		att[17]	= \$17;
		att[18]	= \$18;
		att[19]	= \$19;
		att[20]	= \$20;
	}
	else
	{
#-----------------------------------------------------------------------
#	Riga valori
		if( NF != nf )
		{
			printf( "Riga % 3d - Numero valori diverso dal numero attributi [%d]\n", NR, nf );
			exit;
		}
#.......................................................................
		val[1]	=  \$1;
		val[2]	=  \$2;
		val[3]	=  \$3;
		val[4]	=  \$4;
		val[5]	=  \$5;
		val[6]	=  \$6;
		val[7]	=  \$7;
		val[8]	=  \$8;
		val[9]	=  \$9;
		val[10]	= \$10;
		val[11]	= \$11;
		val[12]	= \$12;
		val[13]	= \$13;
		val[14]	= \$14;
		val[15]	= \$15;
		val[16]	= \$16;
		val[17]	= \$17;
		val[18]	= \$18;
		val[19]	= \$19;
		val[20]	= \$20;
#.......................................................................
		printf( "\nanywidget=\n" );
		printf( "\thasattrib=%s\n", att[1] );
		printf( "\tvalue=%s\n", val[1] );
		for( j = 2; j <= nf; j++ )
		{
			if( val[j] == plchld ) continue;
			printf( "\tattrib=%s\n", att[j] );
			printf( "\tvalue=%s\n", val[j] );
		}
	}
}
EOT

}					# build_awk()


#-----------------------------------------------------------------------
do_pagmod()
{
	`test -n "$opt_v"` && echo "$ss pagmod -s $sfn -p $pfn ...$rr"
	pagmod -s $sfn -p $pfn
}					# do_pagmod()

#-----------------------------------------------------------------------
help()
{
	cat << EOT

Interpreta un file *.tag , produce uno script per il programma 'pagmod'
e lo utilizza per modificare i file *.pag specificati.
Carattere placeholder (attributo da non modificare)	: ^
Carattere sostitutivo dello spazio			: ~

Uso:      TAG2RES  [ -hkV ] -t file.tag  file.pag  [ file2.pag .... ]
  oppure
          TAG2RES  [ -hkV ] -t file.tag  -l page-list

 -h		Questo testo di help
 -k		Non cancella i file creati (TAG2RES.awk e TAG2RES.scr)
 -l page-list	Specifica un file contenente la lista dei file pagine da modificare
 -t file.tag	Specifica il tag file
 -v		Premette l' indicazione dei file pagine elaborati
 -V		Stampa la versione

EOT
	exit	1
}					# help()


#=======================================================================
#	MAIN

#-----------------------------------------------------------------------
#	Inizializzazioni

afn=TAG2RES.awk				# Programma awk (creato e cancellato)
sfn=TAG2RES.scr				# Script filename (output)
optstr='hkl:t:Vv'
rr=`tput rmso`
ss=`tput smso`

#-----------------------------------------------------------------------
#	Acquisizione e controllo argomenti

if [ $# -lt 1 ]; then
	help
fi

set -- `getopt $optstr $*`
if [ $? != 0 ]; then
       help
fi

#.......................................................................
while [ $1 != --	]
do
       case $1 in
	-h)     help ;;			## help
	-k)     k_opt=k ;;		## Keep option
	-l)	lfn=$2			## List file
		shift;;
	-t)	tfn=$2			## Tag file
		shift;;
	-V)     echo "TAG2RES Versione 1.0 1997-09-10"
		exit;;
	-v)     opt_v=opt_v ;;		## echo $pfn
       esac
       shift   # next flag
done
shift   # skip double dash

#.......................................................................
if [ -z "$tfn" ]; then
	help
	echo "Errore *** Occorre specificare il tag file."
	exit	1
fi
if [ ! -r $tfn ]; then
	echo "File (tag) non accessibile: $tfn"
	exit	1
fi

if [ -n "$lfn" ]; then
	if [ ! -r "$lfn" ]; then
		echo "File (list) non accessibile: $lfn"
		exit	1
	fi
fi

#.......................................................................
#+ echo "No. arg. residui: $# ($*)"
if [ $# -lt 1 -a -z "$lfn" ]; then
	help
	echo "Manca specificazione file pagine"
	exit	1
fi

#-----------------------------------------------------------------------
#	Elaborazione

#.......................................................................
#	Creazione del file .awk

build_awk
if [ ! -r "$afn" ]; then
	echo "Creazione del file $afn fallita"
	exit	1
fi

#.......................................................................
#	Creazione dello script (e trasformazione di '~' in blank)

awk -f TAG2RES.awk $tfn | tr "~" " " > $sfn

#.......................................................................
#	Controllo preliminare della corretta dello script

pagmod -s $sfn -cq > /dev/null 2> /dev/null
rc=$?
#+ echo "rc: <$rc>"
if [ "`expr $rc`" -ne 0 ]; then
	echo "Script $sfn errato - Verificare script e tag-file $tfn"
	exit	5
fi

#.......................................................................
#	Esecuzione dello script

if [ -z "$lfn" ]; then
	for pfn in $*
	do
		do_pagmod
	done
else
	cat $lfn | while read pfn
	do
		do_pagmod
	done

fi

#.......................................................................
#	Eventuale cancellazione di .scr e .awk

if [ -z "$k_opt" ]; then
	rm -f $afn $sfn
fi
