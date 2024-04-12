#
actualdir=`pwd`
workdir=$actualdir
if [ "$1" = "" ]
then
echo "usage: mkdtw basename"
exit 1
else
nomelist=`echo $1 | sed s/win/dtw/g`
fi
#
if [ ! -f $HOME/legocad/libut_mmi/${nomelist}.templ ]
then
echo "error: file $HOME/legocad/libut_mmi/${nomelist}.templ not found"
exit 1
fi
#
if [ ! -f $HOME/legocad/libut_mmi/${nomelist}.tebkg ]
then
echo "error: file $HOME/legocad/libut_mmi/${nomelist}.tebkg not found"
exit 1
fi
#
first=1
cat $1.list |sed "s/\([[A-Za-z0-9]\{4,\}\)-\([[A-Za-z0-9]\{4,\}\)-\([[A-Za-z0-9]\{3,\}\)/\1\&\2\&\3/g" | while read cont0 cont1 cont2 cont3 cont4 cont5 cont6 cont7 cont8 cont9 cont10 cont11 cont12 cont13 cont14 cont15 cont16 cont17 cont18 cont19 cont20 cont21 cont22
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
var20=$cont20
var21=$cont21
var22=$cont22
first=0
else
cont0=`echo $cont0 | tr '&' ' '`
cont1=`echo $cont1 | tr '&' ' '`
cont2=`echo $cont2 | tr '&' ' '`
cont3=`echo $cont3 | tr '&' ' '`
cont4=`echo $cont4 | tr '&' ' '`
cont5=`echo $cont5 | tr '&' ' '`
cont6=`echo $cont6 | tr '&' ' '`
cont7=`echo $cont7 | tr '&' ' '`
cont8=`echo $cont8 | tr '&' ' '`
cont9=`echo $cont9 | tr '&' ' '`
cont10=`echo $cont10 | tr '&' ' '`
cont11=`echo $cont11 | tr '&' ' '`
cont12=`echo $cont12 | tr '&' ' '`
cont13=`echo $cont13 | tr '&' ' '`
cont14=`echo $cont14 | tr '&' ' '`
cont15=`echo $cont15 | tr '&' ' '`
cont16=`echo $cont16 | tr '&' ' '`
cont17=`echo $cont17 | tr '&' ' '`
cont18=`echo $cont18 | tr '&' ' '`
cont19=`echo $cont19 | tr '&' ' '`
cont20=`echo $cont20 | tr '&' ' '`
cont21=`echo $cont21 | tr '&' ' '`
cont22=`echo $cont22 | tr '&' ' '`
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
    -e "1,$ s/${var20}/${cont20}/g" \
    -e "1,$ s/${var21}/${cont21}/g" \
    -e "1,$ s/${var22}/${cont22}/g" \
    $HOME/legocad/libut_mmi/${nomelist}.templ > ${cont0}_DTW.pag
cp  $HOME/legocad/libut_mmi/${nomelist}.tebkg ${cont0}_DTW.bkg
fi
done
