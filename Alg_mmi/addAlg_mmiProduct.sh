#!/bin/sh
#
#  Script:                      addAlg_mmiProduct.sh
#  Subsystem:           1
#  %version:            5 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Mon Jul 13 13:18:39 1998 %
#



VERSION=$1
ALG_MMI=Alg_mmi-${VERSION}

#Trova la dir bin
        ALG_MMI_BIN=`ccm query -f "%objectname" -u "is_member_of('$ALG_MMI') and name='bin' and type='dir'"`
        echo $ALG_MMI_BIN
        if [ "$ALG_MMI_BIN" ]
        then
		 ccm query -f "%objectname"  "is_child_of('$ALG_MMI_BIN','$ALG_MMI')  and (type='relocatable_obj' or type='executable' or type='library')"
		cd ./bin
		ccm use @
		cd ..
	fi
#Trova la dir lib
	ALG_MMI_LIB=`ccm query -f "%objectname" -u "is_member_of('$ALG_MMI')
 and name='lib' and type='dir'"`
	echo $ALG_MMI_LIB
	if [ "$ALG_MMI_LIB" ]
	then
		ccm query -f "%objectname"  "is_child_of('$ALG_MMI_LIB','$ALG_MMI')  and (type='relocatable_obj' or type='executable' or type='library')"
		cd ./lib
		ccm use @
		cd ..
	fi

SINCRON=1
echo ""
echo "***   Allineamento progetto ALG_MMI eseguito ***"
echo ""
