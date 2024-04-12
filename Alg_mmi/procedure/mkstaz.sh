#******************************************************************************
# modulo mkstaz.sh
# tipo        
# release 1.3         
# data 96/04/04
# reserver @(#)mkstaz.sh	1.3        
#******************************************************************************
#
# Utility per la generazione di pagine legommi a partire da un template
# presente in $HOME/legocad/libut_mmi e da una lista presente nella directory
# di lavoro ottenendo in quest'ultima le pagine elaborate.
#
if [ "$1" = "" ]
then
echo "usage: mkstaz basename"
exit 1
fi
#
if [ ! -f $HOME/legocad/libut_mmi/$1.templ ]
then
echo "error: file $HOME/legocad/libut_mmi/$1.templ not found"
exit 1
fi
#
if [ ! -f $HOME/legocad/libut_mmi/$1.tebkg ]
then
echo "error: file $HOME/legocad/libut_mmi/$1.tebkg not found"
exit 1
fi
#
first=1
cat $1.list |  while read cont0 cont1 cont2 cont3 cont4 cont5 cont6 cont7 cont8 cont9 cont10 cont11 cont12 cont13 cont14 cont15 cont16 cont17 cont18 cont19
do
if [ $first -eq 1 ]
then
var0=$cont0
var1=$cont1
var2=$cont2
var3=$cont3
var4=$cont4
var5=$cont5
var6=$cont6
var7=$cont7
var8=$cont8
var9=$cont9
var10=$cont10
var11=$cont11
var12=$cont12
var13=$cont13
var14=$cont14
var15=$cont15
var16=$cont16
var17=$cont17
var18=$cont18
var19=$cont19
first=0
else
#echo $var0 $var1 $var2 $var3 $var4 $var5 $var6 $var7 $var8 $var9 
cont0=`echo $cont0 | tr '-' ' '`
cont1=`echo $cont1 | tr '-' ' '`
cont2=`echo $cont2 | tr '-' ' '`
cont3=`echo $cont3 | tr '-' ' '`
cont4=`echo $cont4 | tr '-' ' '`
cont5=`echo $cont5 | tr '-' ' '`
cont6=`echo $cont6 | tr '-' ' '`
cont7=`echo $cont7 | tr '-' ' '`
cont8=`echo $cont8 | tr '-' ' '`
cont9=`echo $cont9 | tr '-' ' '`
cont10=`echo $cont10 | tr '-' ' '`
cont11=`echo $cont11 | tr '-' ' '`
cont12=`echo $cont12 | tr '-' ' '`
cont13=`echo $cont13 | tr '-' ' '`
cont14=`echo $cont14 | tr '-' ' '`
cont15=`echo $cont15 | tr '-' ' '`
cont16=`echo $cont16 | tr '-' ' '`
cont17=`echo $cont17 | tr '-' ' '`
cont18=`echo $cont18 | tr '-' ' '`
cont19=`echo $cont19 | tr '-' ' '`
#echo $cont0 $cont1 $cont2 $cont3 $cont4 $cont5 $cont6 $cont7 $cont8 $cont9
sed -e "1,$ s/${var0}/${cont0}/g" \
    -e "1,$ s/${var1}/${cont1}/g" \
    -e "1,$ s/${var2}/${cont2}/g" \
    -e "1,$ s/${var3}/${cont3}/g" \
    -e "1,$ s/${var4}/${cont4}/g" \
    -e "1,$ s/${var5}/${cont5}/g" \
    -e "1,$ s/${var6}/${cont6}/g" \
    -e "1,$ s/${var7}/${cont7}/g" \
    -e "1,$ s/${var8}/${cont8}/g" \
    -e "1,$ s/${var9}/${cont9}/g" \
    -e "1,$ s/${var10}/${cont10}/g" \
    -e "1,$ s/${var11}/${cont11}/g" \
    -e "1,$ s/${var12}/${cont12}/g" \
    -e "1,$ s/${var13}/${cont13}/g" \
    -e "1,$ s/${var14}/${cont14}/g" \
    -e "1,$ s/${var15}/${cont15}/g" \
    -e "1,$ s/${var16}/${cont16}/g" \
    -e "1,$ s/${var17}/${cont17}/g" \
    -e "1,$ s/${var18}/${cont18}/g" \
    -e "1,$ s/${var19}/${cont19}/g" \
    $HOME/legocad/libut_mmi/$1.templ > ${cont0}.pag
cp  $HOME/legocad/libut_mmi/$1.tebkg ${cont0}.bkg
fi
done
