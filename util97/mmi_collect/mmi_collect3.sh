#!/bin/ksh
#
#  Script:			mmi_collect3.sh
#  Instance:		1
#  %version:		2 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Thu Mar 11 11:03:53 2004 %

#@(#)mmi_collect3	Rifacimento mmi_collect				1997-07-09

#	Convenzione sui nomi delle variabili:
#	xbn  : basename	(prodotto da basename ... SENZA .suffix)
#	xfn  : filename (completo)
#	xdn  : dirname  (prodotto da dirname ...)
#	xcn  : corename	(prodotto da basename ... CON   .suffix)

#=======================================================================
#		ROUTINE

#-----------------------------------------------------------------------
# Richiamare cosi' :	Default  Variab  Val
# Se e` definita la variabile di ambiente Variab ritorna, 
# altrimenti le assegna il valore Val .

Default()
{
	D "Default $1 $2 ..."
	eval "EnvVar=\$$1"
	if [ -z "$EnvVar" ]; then
		D "Variabile $1 NON definita ! [ >> $2 ]"
		eval "$1=$2"
	else
		D "Variabile $1     definita ! [ << $EnvVar ]"
		return
	fi
}					# Default()

#-----------------------------------------------------------------------
Help()
{
	cat << EOT

Raccolta di tutti gli schemi di regolazione di un simulatore in una sola directory.
Rilocazione dei puntatori rispetto allo spazio occupato da ogni task in shared memory.

Uso:
	mmi_collect3  [ -dhvx -g glob-dir -w win-dir ] xxxxx
  -d		Visualizzazioni per debugging        (: ....)
  -g glob-dir	Dichiara glob-dir come directory globale
  -h		Questo testo di help
  -v		Visualizzazione fasi di elaborazione (# ....)
  -V		Stampa la versione
  -w win-dir	Dichiara win-dir  come directory ...
  -x		Visualizzazione comandi eseguiti     (+ ....)

EOT
	exit	$1
}					# Help()

#-----------------------------------------------------------------------
Version()
{
	echo	"mmi_collect3  -  Versione 1.1  1997-07-02"
	exit	$1
}					# Version()

#-----------------------------------------------------------------------
ProcessTask()
{

#.......................................................................
#	Estrae posizione e offset della task da variabili.edf

	grep "^NOME MODELLO.* $task " $vfn | read f1 f2 f3 f4 f5
## echo "ProcessTask() vfn:$vfn task:$task f3:$f3"
## grep "^NOME MODELLO.* $task " $vfn 
	if [ -z "$f3" ]; then
		echo "Task $task non presente in $vfn" >> $efn
		return
	fi

	let position=f3-1
#+	offset=`al_punt_mod $s02 $position | grep '^OFFSET=' | cut -f2 -d=`
	offset=`al_punt_mod . $position | grep '^OFFSET=' | cut -f2 -d=`
	D "postion=$position offset=$offset"
  
#.......................................................................
#	Costruzione dello script per il programma 'pagmod'

	cat << EOT > $scr
#MMI.scr 	`date`
#................................
anywidget=
	compiled8has=1,1
	value=0
	compiled8add=1,1
	value=$position
	compiled8add=1,2
	value=$offset
#................................
anywidget=
	compiled8has=2,1
	value=0
	compiled8add=2,1
	value=$position
	compiled8add=2,2
	value=$offset
#................................
anywidget=
	compiled8has=3,1
	value=0
	compiled8add=3,1
	value=$position
	compiled8add=3,2
	value=$offset
#................................
anywidget=
	compiled8has=4,1
	value=0
	compiled8add=4,1
	value=$position
	compiled8add=4,2
	value=$offset
EOT

#.......................................................................
#	Page (?!) loop

ls -1 $tdn/$path/$spec.rtf 2>> $efn | while read rfn; do
#.......................................................................
#	Controllo preliminare che oltre all' .rtf esista anche il .bkg
#	(se manca rimuove anche l' .rtf).

	ddd=`dirname $rfn`
	ccc=`basename $rfn .rtf`
	bkg=$ddd/$ccc.bkg
#+	echo "$ss `ls -g $bkg` $rr"
	if [ -f $bkg ]; then
		D "Riloca $rfn ...."
		Riloca $rfn
	else
		X "/bin/rm -f $rfn $bkg"
		/bin/rm -f $rfn $bkg
#+		sleep 2
	fi

done

}					# ProcessTask()

#-----------------------------------------------------------------------
Link_rtf()
{
#.......................................................................
#	Il ../ nella riga seguente "recupera" il fatto che la targetdirectory
#	del comando 'ln' e` un livello sotto la directory corrente
	dir=../`dirname $1`		# <<< ../ !!
#...	sdn='source directory name' (per il comando: ln)
	sdn=$dir			# A regime: a monte di Link_rtf
	lcn=`basename $1 .rtf`

#.......................................................................
	X "ln -sf $sdn/$lcn.rtf $gdn"
	X "ln -sf $sdn/$lcn.bkg $gdn"
	X "ln -sf $sdn/$lcn.rtf $gdn/$lcn.pag"
	ln -sf $sdn/$lcn.rtf $gdn 2>> $efn
	ln -sf $sdn/$lcn.bkg $gdn 2>> $efn
	ln -sf $sdn/$lcn.rtf $gdn/$lcn.pag 2>> $efn
	let page_num=page_num+1
	page_list="$page_list $lcn"
	D "[$page_list]"

}					# Link_rtf()

#-----------------------------------------------------------------------
Riloca()
{
#.......................................................................
#//	echo "+++ chgcompiled posizione offset < file > savepwd/GLBPAGES/file"
	rbn=`basename $rfn`
	rcn=`basename $rfn .rtf`
	rdn=`dirname $rfn`
	mfn=$gdn/$rbn
	pfn="$gdn/`basename $rfn .rtf`.pag"
	kfn=../$rdn/`basename $rfn .rtf`.bkg
	qfn="$gdn/`basename $rfn .rtf`.bkg"

#+	[ -n "$x" ] && echo "+ $pagmod -s $scr -i < $rfn > $mfn"
	X "$pagmod -s $scr -i < $rfn > $mfn"
	$pagmod -s $scr -i < $rfn > $mfn
#++	[ -n "$x" ] && echo	"+ ln -sf $mfn $pfn ..."
#++	ln -sf $mfn $pfn
#+	[ -n "$x" ] && echo	"+ ln -sf $rbn $pfn ..."
	X "ln -sf $rbn $pfn"
	ln -sf $rbn $pfn
#+	[ -n "$x" ] && echo	"+ ln -sf $kfn $qfn ..."
	X "ln -sf $kfn $qfn"
	ln -sf $kfn $qfn
	let page_num=page_num+1
	page_list="$page_list $rcn"
	D "[$page_list]"

}					# Riloca()

#-----------------------------------------------------------------------
#	Visualizzazione condizionata all' opzione: -d
D()
{
	[ -n "$d" ] && echo ": $*"
}					# D()

#-----------------------------------------------------------------------
#	Visualizzazione condizionata all' opzione: -v
V()
{
	[ -n "$v" ] && echo "# $*"
}					# V()

#-----------------------------------------------------------------------
#	Visualizzazione condizionata all' opzione: -x
X()
{
	[ -n "$x" ] && echo "+ $* ..."
}					# X()

#=======================================================================
#		MAIN

#+ echo "\nPrima:  \$#: $# : $*"

#-----------------------------------------------------------------------
#	INIZIALIZZAZIONI

ss=`tput smso`
rr=`tput rmso`
v=

Default	ARGMIN			0			# DEBUG
Default	MMI_GLBDIR		globpages
Default	MMI_WINDIR		o_win
Default	BASEPATH		../../legocad		# Cfr.: al_sim.conf
Default	MMI_LSTFIL		al_sim.conf		# Input
Default	MMI_VARFIL		variabili.edf		# Input
Default	MMI_CTXFIL		Context.ctx		# Output
Default	MMI_HOSTNAME		puerto4			# ..........
Default	MMI_HOSTNAME_SCADA	puerto4			# ..........
scr=mmi_collect3.scr				# Output

direxe=~/legocad/libut_bin                      # Direttorio eseguibili

egrep1=mmi_collect3.egrep			# Utilizzato dalla egrep
pagmod=`which pagmod`				# Eseguibile
page_num=0					# Risorsa: *pag_num   / Context.ctx
page_list=""					# Risorsa: *page_list / Context.ctx
pwd=`pwd`
s02=$pwd/S02_OSF1
t2=mmi_collect3.t2				# F. temporaneo (anti: arg too long)

#-----------------------------------------------------------------------
#	Verifica esistenza di file o programmi indispensabili

if [ ! -r $pagmod -o ! -x $pagmod ]; then
	echo "Programma: $pagmod non eseguibile"
	exit	6
fi

if [ ! -r $s02 ]; then
	echo "Programma: $s02 non leggibile"
	exit	6
fi

#-----------------------------------------------------------------------
cat > $egrep1 << EOT
^\*tagPag:
^\*top_descrizione:
^\*schemeInUse:
^\*gerarchia:
^\*refresh_freq:
^\*top_tipo:
EOT

#-----------------------------------------------------------------------
#	ACQUISIZIONE ARGOMENTI

set -- `getopt dg:hvVw:x $*`
if [ $? != 0 ]; then
	Help	2
fi

while [ $1 != -- ]
do
	case $1 in
	-d)     		# Debug
		d=Yes;;
	-g)     		# Global directory
		ARG_GLBDIR=$2
#+ [ -n "$d" ] && echo "g) ARG_GLBDIR: $ARG_GLBDIR"
		D "g) ARG_GLBDIR: $ARG_GLBDIR"
		shift;;
	-h)     		# Help
		Help	0;;
	-v)     		# Verbose
		v=Yes;;
	-V)     		# Versione
		Version;;
	-w)     		# Win directory
		ARG_WINDIR=$2
#+ [ -n "$d" ] && echo "g) ARG_WINDIR: $ARG_WINDIR"
		D "g) ARG_WINDIR: $ARG_WINDIR"
		shift;;
	-x)     		# X
		x=Yes;;
	esac
	shift   # next flag
done
shift				# skip double dash
#+ echo "Dopo:   \$#: $# : $*\n"

if [ $# -lt $ARGMIN ]; then
	Help	1
fi

#-----------------------------------------------------------------------
#	Verifica esistenza del file di lista (al_sim.conf)

if [ ! -r $MMI_LSTFIL ]; then
	echo "File: $MMI_LSTFIL non leggibile"
	exit	6
fi

#-----------------------------------------------------------------------
#	LETTURA al_sim.conf - (1) Acquisizione variabili di ambiente

grep '^MMI.*=' $MMI_LSTFIL | while read line
do
#+	echo "\nline: |$line|"
	var=`echo $line | sed -e 's/=.*//'`
	val=`echo $line | sed -e 's/.*=//'`
#+	echo "$var=\"$val\" ...."
	eval "$var=\"$val\""
	[ -n "$d" ] && eval "echo : $var: \$$var"
done

#.......................................................................
#	Preparazione lista dei display (keyword: MMI_DISPLAY_LIST)

dl_str=`grep 'MMI_DISPLAY_LIST=' $MMI_LSTFIL | sed -e 's/MMI_DISPLAY_LIST=//'`
dl_cnt=`echo $dl_str | awk '{ print NF }'`
#+ echo "dl_str: {$dl_str}"
#+ echo "dl_cnt: {$dl_cnt}"
#+ exit

#-----------------------------------------------------------------------
#	MODIFICA DIRECTORY SE FORNITE DALLA RIGA DI COMANDO

if [ -n "$ARG_GLBDIR" ]; then
	MMI_GLBDIR=$ARG_GLBDIR
fi

if [ -n "$ARG_WINDIR" ]; then
	MMI_WINDIR=$ARG_WINDIR
fi

#-----------------------------------------------------------------------
#	CONTROLLI

#+ [ -n "$v" ] && echo "# Controlli accessibilita' directory ..."
V "Controlli accessibilita' directory e file ..."
if [ ! -d $MMI_GLBDIR ]; then
	mkdir  $MMI_GLBDIR
fi
if [ ! -d $MMI_GLBDIR -o ! -x $MMI_GLBDIR -o ! -w $MMI_GLBDIR ]; then
	echo "Creazione directory: $MMI_GLBDIR fallita"
	exit	5
fi

if [ ! -d $MMI_WINDIR -o ! -x $MMI_WINDIR ]; then
	echo "Directory: $MMI_WINDIR non accessibile"
#!	exit	5		# Questo errore non e' bloccante.
fi

if [ ! -f $MMI_LSTFIL -o ! -r $MMI_LSTFIL ]; then
	echo "File: $MMI_LSTFIL non accessibile"
	exit	5
fi

if [ ! -f $MMI_VARFIL -o ! -r $MMI_VARFIL ]; then
	echo "File: $MMI_VARFIL non accessibile"
	exit	5
fi

V "... controlli OK"

#.......................................................................
gdn=$MMI_GLBDIR
tdn=$BASEPATH				# Cfr.: al_sim.conf
wdn=$MMI_WINDIR
vfn=$MMI_VARFIL
lst=$MMI_LSTFIL
ctx=$MMI_GLBDIR/$MMI_CTXFIL
efn=mmi_collect3.err			# Log degli errori

date '+mmi_collect3 - Inizio %y-%m-%d %T' > $efn

#-----------------------------------------------------------------------
#	PULIZIA DIRECTORY globpages

#+ [ -n "$x" ] && echo "+ /bin/rm -f $gdn/*.bkg $gdn/*.pag $gdn/*.rtf ..."
#+X	"+ /bin/rm -f $gdn/*.bkg $gdn/*.pag $gdn/*.rtf ..."
X "/bin/rm -fr $gdn"
sleep 1
/bin/rm -fr $gdn
mkdir $gdn

#-----------------------------------------------------------------------
#	GENERAZIONE PARTE INIZIALE Context.ctx

V "Generazione $ctx / 1 ..."
#Generazione della prima parte del file Context.ctx
#
##++*numTagPag:	0
##++*project:	$PWD
cat >$ctx <<!EOF
*hostName:	$MMI_HOSTNAME
*hostNameS:	$MMI_HOSTNAME_SCADA
*iconlib_list:	\\ 
*displayList:	$dl_str
*numDisplay:	$dl_cnt
*iconlib_num:	0
*description:	
*iconlib_label:	\\ 
*nextTagPag:	01
*simulator:	$PWD
*pages:	$PWD/$gdn
*objectLibraries:	$PWD
*animatedIconLibraries:	$PWD/../../legocad/libut_reg/libreg
!EOF

#-----------------------------------------------------------------------
#	LETTURA al_sim.conf - (2) Individuazione dei modelli

#.......................................................................
#	Task loop

#+ [ -n "$v" ] && echo "# Task loop ..."
V "Task loop ..."
grep '^R[[:space:]]' $lst | while read f1 f2 f3 f4 f5 ; do
	task=$f2
	path=$f3
	spec=$f4

	D "$task $path $spec"
	ProcessTask ;
done


#-----------------------------------------------------------------------
#	LINK LOOP

#+ [ -n "$v" ] && echo "# Link loop ..."
V "Link loop ..."

# ............ (da verificare) ........

#...	sdn=......
ls -1 $wdn | grep ^O_ | grep rtf | grep -v err 2>> $efn | while read lfn; do
	lfn=$wdn/$lfn
	D "Link_rtf $lfn ....."
	Link_rtf $lfn
done

ls -1 $wdn | grep ^F_ | grep rtf | grep -v err 2>> $efn | while read lfn; do
	lfn=$wdn/$lfn
	D "Link_rtf $lfn ....."
	Link_rtf $lfn
done

ls -1 $wdn | grep ^M_ | grep rtf | grep -v err 2>> $efn | while read lfn; do
	lfn=$wdn/$lfn
	D "Link_rtf $lfn ....."
	Link_rtf $lfn
done


#-----------------------------------------------------------------------
#	GENERAZIONE PARTE CENTRALE Context.ctx

V "Generazione $ctx / 2 ..."

#% ls -1 $gdn/*.rtf 2>> $efn | while read rfn; do
find $gdn -name '*.rtf' > $t2
exec 5< $t2
while [ 1 ]
do
	read -u5 rfn
	rc=$?
	if [ $rc -ne 0 ]; then
		break;
	fi
	tsk=`basename $rfn .rtf`
	X "egrep -f mmi_collect3.egrep $rfn | sed -e \"s/./*$tsk./\" >> $ctx"
	egrep -f mmi_collect3.egrep $rfn | sed -e "s/./*$tsk./" >> $ctx
done

#-----------------------------------------------------------------------
#	GENERAZIONE PARTE FINALE Context.ctx

V "Generazione $ctx / 3 ..."
X "echo \"*pag_num:\t$page_num\" >> $ctx"
echo "*pag_num:\t$page_num" >> $ctx
X "echo \"*page_list:\t$page_num\" >> $ctx"
echo "*page_list:\t\\$page_list" >> $ctx			# <<< ATTENZIONE ai blank !

X "/usr/bin/rm -f $egrep1 $t2 $scr"
/usr/bin/rm -f $egrep1 $t2 $scr

date '+mmi_collect3 - Fine   %y-%m-%d %T' >> $efn

