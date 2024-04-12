#!/bin/sh
#
#  Script:                      addLegocadProduct.sh
#  Subsystem:           1
#  %version:            4 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Mon Jul 13 13:47:52 1998 %
#

VERSION=$1
LEGOCAD=legocad-${VERSION}


#Trova la dir lib
	LEGOCAD_LIB=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='lib' and type='dir'"`
	echo $LEGOCAD_LIB
	if [ $LEGOCAD_LIB ]
	then
		ccm query -f "%objectname"  "is_child_of('$LEGOCAD_LIB','$LEGOCAD')  and (type='relocatable_obj' or type='executable' or type='library')" 
		cd ./lib
		ccm use @
		cd ..
	fi
#Trova la dir bin
	LEGOCAD_BIN=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='bin' and type='dir'"`
	echo $LEGOCAD_BIN
	if [ $LEGOCAD_BIN ]
	then
		ccm query -f "%objectname"  "is_child_of('$LEGOCAD_BIN','$LEGOCAD') and (type='relocatable_obj' or type='executable' or type='library')" 
		cd ./bin
		ccm use @
		cd ..
	fi
#Trova la dir risorse
        LEGOCAD_RISORSE=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='risorse' and type='dir'"`
        echo $LEGOCAD_RISORSE
        if [ $LEGOCAD_RISORSE ]
        then
                ccm query -f "%objectname"  "is_child_of('$LEGOCAD_RISORSE','$LEGOCAD') and (type='ascii' or type='bitmap' )"
                cd ./risorse
                ccm use @
                cd ..
        fi

#Trova la dir icons
        LEGOCAD_ICONS=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='icons' and type='dir'"`
        echo $LEGOCAD_ICONS
        if [ $LEGOCAD_ICONS ]
        then
                ccm query -f "%objectname"  "is_child_of('$LEGOCAD_ICONS','$LEGOCAD') and (type='ascii' or type='bmp' )"
                cd ./icons
                ccm use @
                cd ..
        fi
#Trova la dir uid
        LEGOCAD_UID=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='uid' and type='dir'"`
        echo $LEGOCAD_UID
        if [ $LEGOCAD_UID ]
        then
                ccm query -f "%objectname"  "is_child_of('$LEGOCAD_UID','$LEGOCAD') and (type='uid' )"
                cd ./uid
                ccm use @
                cd ..
        fi
#Trova la dir legoserver
	LEGOCAD_LEGOSERVER=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='legoserver' and type='dir'"`
	echo $LEGOCAD_LEGOSERVER
	if [ $LEGOCAD_LEGOSERVER ]
	then
		ccm query -f "%objectname"  "is_child_of('$LEGOCAD_LEGOSERVER','$LEGOCAD') and ((type='makefile' and name ='Makefile') or type='csrc')"
		cd ./legoserver
		ccm use @
		cd ..
		fi
#Trova la dir regoserver
	LEGOCAD_REGOSERVER=`ccm query -f "%objectname" -u "is_member_of('$LEGOCAD') and name='regoserver' and type='dir'"`
	echo $LEGOCAD_REGOSERVER
	if [ $LEGOCAD_REGOSERVER ]
	then
		ccm query -f "%objectname"  "is_child_of('$LEGOCAD_REGOSERVER','$LEGOCAD') and ((type='makefile' and name ='Makefile') or type='csrc') "
		cd ./regoserver
		ccm use @
		cd ..
		fi
SINCRON=1
echo ""
echo "***   Allineamento progetto LEGOCAD eseguito ***"
echo ""

