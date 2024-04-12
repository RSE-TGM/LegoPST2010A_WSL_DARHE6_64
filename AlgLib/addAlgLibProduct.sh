#!/bin/sh
#
#  Script:                      addAlgLibProduct.sh
#  Subsystem:           1
#  %version:            7 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Fri Oct 21 12:20:11 2005 %
#
VERSION=$1
ALGLIB=AlgLib-${VERSION}
QUERYKO="Objects not found"
#Trova la dir lib
	if [ $ALGLIB ]
	then
		ccm query -f "%objectname"  "is_member_of('$ALGLIB') and (type='relocatable_obj' or type='executable' or type='library')"
		ccm use @
#Trova sim_param.h
		cd ./libinclude
		SIMPARAM=`ccm query -f "%objectname" -u  "is_member_of('$ALGLIB') and type='incl' and name='sim_param.h'"`
		if [ "$SIMPARAM" != "$QUERYKO" ]
		then
			ccm use $SIMPARAM
		else 
			echo "sim_param.h not found"
		fi
		cd ..
		
	fi

#Trova la dir dcethreads_include
	DCETHEADS_INCLUDE=`ccm query -f "%objectname" -u "is_member_of('$ALGLIB') and name='dcethreads_include' and type='dir'"`
	echo ELABORO: $DCETHEADS_INCLUDE

	if [ $DCETHEADS_INCLUDE ]
	then
		ccm use  $DCETHEADS_INCLUDE
		ccm query -f "%objectname"  "is_child_of('$DCETHEADS_INCLUDE','$ALGLIB') "
                cd ./dcethreads_include
                ccm use @
                cd ..
        fi

#Trova la dir dcethreads_lib
	DCETHEADS_LIB=`ccm query -f "%objectname" -u "is_member_of('$ALGLIB') and name='dcethreads_lib' and type='dir'"`
	echo ELABORO: $DCETHEADS_LIB

	if [ $DCETHEADS_LIB ]
	then
		ccm use  $DCETHEADS_LIB
		ccm query -f "%objectname"  "is_child_of('$DCETHEADS_LIB','$ALGLIB') "
                cd ./dcethreads_lib
                ccm use @
                cd ..
        fi

#Trova la dir sqlite_lib
	SQLITE_LIB=`ccm query -f "%objectname" -u "is_member_of('$ALGLIB') and name='sqlite_lib' and type='dir'"`
	echo ELABORO: $SQLITE_LIB
	if [ $SQLITE_LIB ]
	then
		ccm use $SQLITE_LIB
		ccm query -f "%objectname"  "is_child_of('$SQLITE_LIB','$ALGLIB') "
                cd ./sqlite_lib
                ccm use @
                cd ..
        fi

#Trova la dir sqlite_include
	SQLITE_INCLUDE=`ccm query -f "%objectname" -u "is_member_of('$ALGLIB') and name='sqlite_include' and type='dir'"`
	echo ELABORO: $SQLITE_INCLUDE

	if [ $SQLITE_INCLUDE ]
	then
		ccm use $SQLITE_INCLUDE
		ccm query -f "%objectname"  "is_child_of('$SQLITE_INCLUDE','$ALGLIB') "
                cd ./sqlite_include
                ccm use @
                cd ..
        fi

#Trova la dir sqlite_bin
	SQLITE_BIN=`ccm query -f "%objectname" -u "is_member_of('$ALGLIB') and name='sqlite_bin' and type='dir'"`
	echo ELABORO: $SQLITE_BIN

	if [ $SQLITE_BIN ]
	then
		ccm use $SQLITE_BIN
		ccm query -f "%objectname"  "is_child_of('$SQLITE_BIN','$ALGLIB') "
                cd ./sqlite_bin
                ccm use @
                cd ..
        fi

SINCRON=1
echo ""
echo "***   Allineamento progetto ALGLIB eseguito ***"
echo ""


