#!/bin/sh
#
#  Script:                      addAlg_rtProduct.sh
#  Subsystem:           1
#  %version:            6 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Fri Jun  9 12:21:21 2006 %
#
VERSION=$1
ALG_RT=Alg_rt-${VERSION}
#Trova la dir bin
	ALGRT_BIN=`ccm query -f "%objectname" -u "is_member_of('$ALG_RT') and name='bin' and type='dir'"`        
	echo $ALGRT_BIN
	if [ "$ALGRT_BIN" ]
	then
		ccm query -f "%objectname" "is_child_of('$ALGRT_BIN','$ALG_RT') and (type='relocatable_obj' or type='executable' or type='library' or type='sql')"
		cd ./bin
		ccm use @
		cd ..
	fi
#Trova la dir uid
        ALGRT_UID=`ccm query -f "%objectname" -u "is_member_of('$ALG_RT') and name='uid' and type='dir'"`
        echo $ALGRT_UID
        if [ "$ALGRT_UID" ]
        then
                ccm query -f "%objectname" "is_child_of('$ALGRT_UID','$ALG_RT') and (type='uid')"
                cd ./uid
                ccm use @
                cd ..
        fi
#Trova la dir compstaz
	ALGRT_COMPSTAZ=`ccm query -f "%objectname" -u "is_member_of('$ALG_RT') and name='compstaz' and type='dir'"`
	echo $ALGRT_COMPSTAZ
	if [ "$ALGRT_COMPSTAZ" ]
	then 
		ccm query -f "%objectname" "is_child_of('$ALGRT_COMPSTAZ','$ALG_RT') and (type='library')"
		cd ./grafica/compstaz
		ccm use @
		cd ../..
	fi
#Trova la dir xstaz
	ALGRT_XSTAZ=`ccm query -f "%objectname" -u "is_member_of('$ALG_RT') and name='xstaz' and type='dir'"`
	echo $ALGRT_XSTAZ
	if [ "$ALGRT_XSTAZ" ]
	then 
		ccm query -f "%objectname" "is_child_of('$ALGRT_XSTAZ','$ALG_RT') and (type='library')"
		cd ./grafica/xstaz
		ccm use @
		cd ../..
	fi
#Trova la dir uid
        ALGRT_MONIT=`ccm query -f "%objectname" -u "is_member_of('$ALG_RT') and name='net_monit' and type='dir'"`
        echo $ALGRT_MONIT
        if [ "$ALGRT_MONIT" ]
        then
                ccm query -f "%objectname" "is_child_of('$ALGRT_MONIT','$ALG_RT') and (type='ascii' or type='bmp')"
                cd ./net_simula/net_monit
                ccm use @
                cd ../..
        fi

SINCRON=1
echo ""
echo "***   Allineamento progetto ALG_RT eseguito ***"
echo ""
