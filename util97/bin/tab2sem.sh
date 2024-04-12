#******************************************************************************
# modulo tab2sem.sh
# tipo        
# release 1.0         
# data 98/01/26
# reserver @(#)tab2sem.sh	1.0        
#******************************************************************************
#
# Utility per la traduzione di campi separati da TABS e/o BLANKS
# in equivalenti separati da ;
#
if [ "$1" = "" ]
then
echo "usage: tab2sem basename"
exit 1
fi
#
cat /dev/null> $1.listdb
cat $1.list | while read cont0 cont1 cont2 cont3 cont4 cont5 cont6 cont7 cont8 cont9 cont10 cont11 cont12 cont13 cont14 cont15 cont16 cont17 cont18 cont19 cont20 cont21 cont22
do
echo ${cont0}";"\
${cont1}";"\
${cont2}";"\
${cont3}";"\
${cont4}";"\
${cont5}";"\
${cont6}";"\
${cont7}";"\
${cont8}";"\
${cont9}";"\
${cont10}";"\
${cont11}";"\
${cont12}";"\
${cont13}";"\
${cont14}";"\
${cont15}";"\
${cont16}";"\
${cont17}";"\
${cont18}";"\
${cont19}";"\
${cont20}";"\
${cont21}";"\
${cont22}
done >> $1.listdb
