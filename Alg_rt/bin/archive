DATEFILE=`date +%b_%d_%T`
SUM1=`sum variabili.edf | cut -f1 -d " "`
if [ "$OS" = "OSF1" ]
then
	SUM2=`sum S02_OSF1 | cut -f1 -d " "`
fi
if [ "$OS" = "AIX" ]
then
	SUM2=`sum S02_AIX | cut -f1 -d " "`
fi
SUM3=`sum Simulator | cut -f1 -d " "`
STRING=${DATEFILE}_${SUM1}_${SUM2}_${SUM3}
echo $STRING
