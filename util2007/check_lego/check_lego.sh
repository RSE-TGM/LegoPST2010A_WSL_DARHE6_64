clear
clean
echo '#################################################'
echo '#                                               #'
echo '#    ROUTINE DI CHECK INSTALLAZIONE SUITE       #'
echo '#                   ALTERLEGO                   #'   
echo '#                                               #'
echo '#################################################'
echo ''
echo ''
echo 'STATO LICENZA LEGOCAD:'
check_license alglc
lc=$?
echo ''

echo ''
echo ''
echo 'STATO LICENZA CONFIG:'
check_license algcf
cf=$?
echo ''

echo ''
echo ''
echo 'STATO LICENZA MMI:'
check_license algmm
mm=$?
echo ''

echo ''
echo ''
echo 'STATO LICENZA SCADA:'
check_license algsc
sc=$?
echo ''

echo ''
echo ''
echo 'STATO LICENZA RUN TIME:'
check_license algrt
rt=$?
echo ''

if  [ $lc = 0 ] && [ $cf = 0 ] && [ $mm = 0 ] && [ $sc = 0 ] && [ $rt = 0 ]
then
 banner "LEGO OK!"
else
 echo ""
 echo ""
 banner "LEGO NOK"
 echo "#################################################"
 echo "#                                               #"
 echo "#      RISCONTRATO PROBLEMA CON LE LICENZE      #"
 echo "#                                               #"
 echo "#################################################"
 echo ""
fi



