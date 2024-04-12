#******************************************************************************
# modulo mkstaz
# tipo        
# release 1.4         
# data 98/09/01
# reserver @(#)mkstaz.sh	1.5        
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
cat $1.list |sed "s/\([[A-Za-z0-9]\{4,\}\)-\([[A-Za-z0-9]\{4,\}\)-\([[A-Za-z0-9]\{3,\}\)/\1\&\2\&\3/g" | \
while read cont0 cont1 cont2 cont3 cont4 cont5 cont6 cont7 cont8 cont9 cont10 cont11 cont12 cont13 cont14 cont15 cont16 cont17 cont18 cont19 cont20 cont21 cont22 cont23 cont24 cont25 cont26 cont27 cont28 cont29 cont30 cont31 cont32 cont33 cont34 cont35 cont36 cont37 cont38 cont39 cont40 cont41 cont42 cont43 cont44 cont45 cont46 cont47 cont48 cont49 cont50 cont51 cont52 cont53 cont54 cont55 cont56 cont57 cont58 cont59 cont60 cont61 cont62 cont63 cont64 cont65 cont66 cont67 cont68 cont69 cont70 cont71 cont72 cont73 cont74 cont75 cont76 cont77 cont78 cont79 cont80 cont81 cont82 cont83 cont84 cont85 cont86 cont87 cont88 cont89 cont90 cont91 cont92 cont93 cont94 cont95 cont96 cont97 cont98 cont99 cont100 cont101 cont102 cont103 cont104 cont105 cont106 cont107 cont108 cont109 cont110 cont111 cont112 cont113 cont114 cont115 cont116 cont117 cont118 cont119 cont120 cont121 cont122 cont123 cont124 cont125 cont126 cont127 cont128 cont129
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
var23=$cont23
var24=$cont24
var25=$cont25
var26=$cont26
var27=$cont27
var28=$cont28
var29=$cont29
var30=$cont30
var31=$cont31
var32=$cont32
var33=$cont33
var34=$cont34
var35=$cont35
var36=$cont36
var37=$cont37
var38=$cont38
var39=$cont39
var40=$cont40
var41=$cont41
var42=$cont42
var43=$cont43
var44=$cont44
var45=$cont45
var46=$cont46
var47=$cont47
var48=$cont48
var49=$cont49
var50=$cont50
var51=$cont51
var52=$cont52
var53=$cont53
var54=$cont54
var55=$cont55
var56=$cont56
var57=$cont57
var58=$cont58
var59=$cont59
var60=$cont60
var61=$cont61
var62=$cont62
var63=$cont63
var64=$cont64
var65=$cont65
var66=$cont66
var67=$cont67
var68=$cont68
var69=$cont69
var70=$cont70
var71=$cont71
var72=$cont72
var73=$cont73
var74=$cont74
var75=$cont75
var76=$cont76
var77=$cont77
var78=$cont78
var79=$cont79
var80=$cont80
var81=$cont81
var82=$cont82
var83=$cont83
var84=$cont84
var85=$cont85
var86=$cont86
var87=$cont87
var88=$cont88
var89=$cont89
var90=$cont90
var91=$cont91
var92=$cont92
var93=$cont93
var94=$cont94
var95=$cont95
var96=$cont96
var97=$cont97
var98=$cont98
var99=$cont99
var100=$cont100
var101=$cont101
var102=$cont102
var103=$cont103
var104=$cont104
var105=$cont105
var106=$cont106
var107=$cont107
var108=$cont108
var109=$cont109
var110=$cont110
var111=$cont111
var112=$cont112
var113=$cont113
var114=$cont114
var115=$cont115
var116=$cont116
var117=$cont117
var118=$cont118
var119=$cont119
var120=$cont120
var121=$cont121
var122=$cont122
var123=$cont123
var124=$cont124
var125=$cont125
var126=$cont126
var127=$cont127
var128=$cont128
var129=$cont129
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
cont23=`echo $cont23 | tr '&' ' '`
cont24=`echo $cont24 | tr '&' ' '`
cont25=`echo $cont25 | tr '&' ' '`
cont26=`echo $cont26 | tr '&' ' '`
cont27=`echo $cont27 | tr '&' ' '`
cont28=`echo $cont28 | tr '&' ' '`
cont29=`echo $cont29 | tr '&' ' '`
cont30=`echo $cont30 | tr '&' ' '`
cont31=`echo $cont31 | tr '&' ' '`
cont32=`echo $cont32 | tr '&' ' '`
cont33=`echo $cont33 | tr '&' ' '`
cont34=`echo $cont34 | tr '&' ' '`
cont35=`echo $cont35 | tr '&' ' '`
cont36=`echo $cont36 | tr '&' ' '`
cont37=`echo $cont37 | tr '&' ' '`
cont38=`echo $cont38 | tr '&' ' '`
cont39=`echo $cont39 | tr '&' ' '`
cont40=`echo $cont40 | tr '&' ' '`
cont41=`echo $cont41 | tr '&' ' '`
cont42=`echo $cont42 | tr '&' ' '`
cont43=`echo $cont43 | tr '&' ' '`
cont44=`echo $cont44 | tr '&' ' '`
cont45=`echo $cont45 | tr '&' ' '`
cont46=`echo $cont46 | tr '&' ' '`
cont47=`echo $cont47 | tr '&' ' '`
cont48=`echo $cont48 | tr '&' ' '`
cont49=`echo $cont49 | tr '&' ' '`
cont50=`echo $cont50 | tr '&' ' '`
cont51=`echo $cont51 | tr '&' ' '`
cont52=`echo $cont52 | tr '&' ' '`
cont53=`echo $cont53 | tr '&' ' '`
cont54=`echo $cont54 | tr '&' ' '`
cont55=`echo $cont55 | tr '&' ' '`
cont56=`echo $cont56 | tr '&' ' '`
cont57=`echo $cont57 | tr '&' ' '`
cont58=`echo $cont58 | tr '&' ' '`
cont59=`echo $cont59 | tr '&' ' '`
cont60=`echo $cont60 | tr '&' ' '`
cont61=`echo $cont61 | tr '&' ' '`
cont62=`echo $cont62 | tr '&' ' '`
cont63=`echo $cont63 | tr '&' ' '`
cont64=`echo $cont64 | tr '&' ' '`
cont65=`echo $cont65 | tr '&' ' '`
cont66=`echo $cont66 | tr '&' ' '`
cont67=`echo $cont67 | tr '&' ' '`
cont68=`echo $cont68 | tr '&' ' '`
cont69=`echo $cont69 | tr '&' ' '`
cont70=`echo $cont70 | tr '&' ' '`
cont71=`echo $cont71 | tr '&' ' '`
cont72=`echo $cont72 | tr '&' ' '`
cont73=`echo $cont73 | tr '&' ' '`
cont74=`echo $cont74 | tr '&' ' '`
cont75=`echo $cont75 | tr '&' ' '`
cont76=`echo $cont76 | tr '&' ' '`
cont77=`echo $cont77 | tr '&' ' '`
cont78=`echo $cont78 | tr '&' ' '`
cont79=`echo $cont79 | tr '&' ' '`
cont80=`echo $cont80 | tr '&' ' '`
cont81=`echo $cont81 | tr '&' ' '`
cont82=`echo $cont82 | tr '&' ' '`
cont83=`echo $cont83 | tr '&' ' '`
cont84=`echo $cont84 | tr '&' ' '`
cont85=`echo $cont85 | tr '&' ' '`
cont86=`echo $cont86 | tr '&' ' '`
cont87=`echo $cont87 | tr '&' ' '`
cont88=`echo $cont88 | tr '&' ' '`
cont89=`echo $cont89 | tr '&' ' '`
cont90=`echo $cont90 | tr '&' ' '`
cont91=`echo $cont91 | tr '&' ' '`
cont92=`echo $cont92 | tr '&' ' '`
cont93=`echo $cont93 | tr '&' ' '`
cont94=`echo $cont94 | tr '&' ' '`
cont95=`echo $cont95 | tr '&' ' '`
cont96=`echo $cont96 | tr '&' ' '`
cont97=`echo $cont97 | tr '&' ' '`
cont98=`echo $cont98 | tr '&' ' '`
cont99=`echo $cont99 | tr '&' ' '`
cont100=`echo $cont100 | tr '&' ' '`
cont101=`echo $cont101 | tr '&' ' '`
cont102=`echo $cont102 | tr '&' ' '`
cont103=`echo $cont103 | tr '&' ' '`
cont104=`echo $cont104 | tr '&' ' '`
cont105=`echo $cont105 | tr '&' ' '`
cont106=`echo $cont106 | tr '&' ' '`
cont107=`echo $cont107 | tr '&' ' '`
cont108=`echo $cont108 | tr '&' ' '`
cont109=`echo $cont109 | tr '&' ' '`
cont110=`echo $cont110 | tr '&' ' '`
cont111=`echo $cont111 | tr '&' ' '`
cont112=`echo $cont112 | tr '&' ' '`
cont113=`echo $cont113 | tr '&' ' '`
cont114=`echo $cont114 | tr '&' ' '`
cont115=`echo $cont115 | tr '&' ' '`
cont116=`echo $cont116 | tr '&' ' '`
cont117=`echo $cont117 | tr '&' ' '`
cont118=`echo $cont118 | tr '&' ' '`
cont119=`echo $cont119 | tr '&' ' '`
cont120=`echo $cont120 | tr '&' ' '`
cont121=`echo $cont121 | tr '&' ' '`
cont122=`echo $cont122 | tr '&' ' '`
cont123=`echo $cont123 | tr '&' ' '`
cont124=`echo $cont124 | tr '&' ' '`
cont125=`echo $cont125 | tr '&' ' '`
cont126=`echo $cont126 | tr '&' ' '`
cont127=`echo $cont127 | tr '&' ' '`
cont128=`echo $cont128 | tr '&' ' '`
cont129=`echo $cont129 | tr '&' ' '`
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
    -e "1,$ s/${var23}/${cont23}/g" \
    -e "1,$ s/${var24}/${cont24}/g" \
    -e "1,$ s/${var25}/${cont25}/g" \
    -e "1,$ s/${var26}/${cont26}/g" \
    -e "1,$ s/${var27}/${cont27}/g" \
    -e "1,$ s/${var28}/${cont28}/g" \
    -e "1,$ s/${var29}/${cont29}/g" \
    -e "1,$ s/${var30}/${cont30}/g" \
    -e "1,$ s/${var31}/${cont31}/g" \
    -e "1,$ s/${var32}/${cont32}/g" \
    -e "1,$ s/${var33}/${cont33}/g" \
    -e "1,$ s/${var34}/${cont34}/g" \
    -e "1,$ s/${var35}/${cont35}/g" \
    -e "1,$ s/${var36}/${cont36}/g" \
    -e "1,$ s/${var37}/${cont37}/g" \
    -e "1,$ s/${var38}/${cont38}/g" \
    -e "1,$ s/${var39}/${cont39}/g" \
    -e "1,$ s/${var40}/${cont40}/g" \
    -e "1,$ s/${var41}/${cont41}/g" \
    -e "1,$ s/${var42}/${cont42}/g" \
    -e "1,$ s/${var43}/${cont43}/g" \
    -e "1,$ s/${var44}/${cont44}/g" \
    -e "1,$ s/${var45}/${cont45}/g" \
    -e "1,$ s/${var46}/${cont46}/g" \
    -e "1,$ s/${var47}/${cont47}/g" \
    -e "1,$ s/${var48}/${cont48}/g" \
    -e "1,$ s/${var49}/${cont49}/g" \
    -e "1,$ s/${var50}/${cont50}/g" \
    -e "1,$ s/${var51}/${cont51}/g" \
    -e "1,$ s/${var52}/${cont52}/g" \
    -e "1,$ s/${var53}/${cont53}/g" \
    -e "1,$ s/${var54}/${cont54}/g" \
    -e "1,$ s/${var55}/${cont55}/g" \
    -e "1,$ s/${var56}/${cont56}/g" \
    -e "1,$ s/${var57}/${cont57}/g" \
    -e "1,$ s/${var58}/${cont58}/g" \
    -e "1,$ s/${var59}/${cont59}/g" \
    -e "1,$ s/${var60}/${cont60}/g" \
    -e "1,$ s/${var61}/${cont61}/g" \
    -e "1,$ s/${var62}/${cont62}/g" \
    -e "1,$ s/${var63}/${cont63}/g" \
    -e "1,$ s/${var64}/${cont64}/g" \
    -e "1,$ s/${var65}/${cont65}/g" \
    -e "1,$ s/${var66}/${cont66}/g" \
    -e "1,$ s/${var67}/${cont67}/g" \
    -e "1,$ s/${var68}/${cont68}/g" \
    -e "1,$ s/${var69}/${cont69}/g" \
    -e "1,$ s/${var70}/${cont70}/g" \
    -e "1,$ s/${var71}/${cont71}/g" \
    -e "1,$ s/${var72}/${cont72}/g" \
    -e "1,$ s/${var73}/${cont73}/g" \
    -e "1,$ s/${var74}/${cont74}/g" \
    -e "1,$ s/${var75}/${cont75}/g" \
    -e "1,$ s/${var76}/${cont76}/g" \
    -e "1,$ s/${var77}/${cont77}/g" \
    -e "1,$ s/${var78}/${cont78}/g" \
    -e "1,$ s/${var79}/${cont79}/g" \
    -e "1,$ s/${var80}/${cont80}/g" \
    -e "1,$ s/${var81}/${cont81}/g" \
    -e "1,$ s/${var82}/${cont82}/g" \
    -e "1,$ s/${var83}/${cont83}/g" \
    -e "1,$ s/${var84}/${cont84}/g" \
    -e "1,$ s/${var85}/${cont85}/g" \
    -e "1,$ s/${var86}/${cont86}/g" \
    -e "1,$ s/${var87}/${cont87}/g" \
    -e "1,$ s/${var88}/${cont88}/g" \
    -e "1,$ s/${var89}/${cont89}/g" \
    -e "1,$ s/${var90}/${cont90}/g" \
    -e "1,$ s/${var91}/${cont91}/g" \
    -e "1,$ s/${var92}/${cont92}/g" \
    -e "1,$ s/${var93}/${cont93}/g" \
    -e "1,$ s/${var94}/${cont94}/g" \
    -e "1,$ s/${var95}/${cont95}/g" \
    -e "1,$ s/${var96}/${cont96}/g" \
    -e "1,$ s/${var97}/${cont97}/g" \
    -e "1,$ s/${var98}/${cont98}/g" \
    -e "1,$ s/${var99}/${cont99}/g" \
    -e "1,$ s/${var100}/${cont100}/g" \
    -e "1,$ s/${var101}/${cont101}/g" \
    -e "1,$ s/${var102}/${cont102}/g" \
    -e "1,$ s/${var103}/${cont103}/g" \
    -e "1,$ s/${var104}/${cont104}/g" \
    -e "1,$ s/${var105}/${cont105}/g" \
    -e "1,$ s/${var106}/${cont106}/g" \
    -e "1,$ s/${var107}/${cont107}/g" \
    -e "1,$ s/${var108}/${cont108}/g" \
    -e "1,$ s/${var109}/${cont109}/g" \
    -e "1,$ s/${var110}/${cont110}/g" \
    -e "1,$ s/${var111}/${cont111}/g" \
    -e "1,$ s/${var112}/${cont112}/g" \
    -e "1,$ s/${var113}/${cont113}/g" \
    -e "1,$ s/${var114}/${cont114}/g" \
    -e "1,$ s/${var115}/${cont115}/g" \
    -e "1,$ s/${var116}/${cont116}/g" \
    -e "1,$ s/${var117}/${cont117}/g" \
    -e "1,$ s/${var118}/${cont118}/g" \
    -e "1,$ s/${var119}/${cont119}/g" \
    -e "1,$ s/${var120}/${cont120}/g" \
    -e "1,$ s/${var121}/${cont121}/g" \
    -e "1,$ s/${var122}/${cont122}/g" \
    -e "1,$ s/${var123}/${cont123}/g" \
    -e "1,$ s/${var124}/${cont124}/g" \
    -e "1,$ s/${var125}/${cont125}/g" \
    -e "1,$ s/${var126}/${cont126}/g" \
    -e "1,$ s/${var127}/${cont127}/g" \
    -e "1,$ s/${var128}/${cont128}/g" \
    -e "1,$ s/${var129}/${cont129}/g" \
    $HOME/legocad/libut_mmi/$1.templ > ${cont0}.pag
cp  $HOME/legocad/libut_mmi/$1.tebkg ${cont0}.bkg
fi
done
