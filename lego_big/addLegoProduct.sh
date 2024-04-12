
VERSION=$1
LEGO=lego-${VERSION}


#########################
#Trova la dir lib
#########################
	LEGO_LIB=`ccm query -f "%objectname" -u "is_member_of('$LEGO') and name='lib' and type='dir'"`
	echo $LEGO_LIB
	if [ "$LEGO_LIB" ]
	then
		ccm query -f "%objectname"  "is_child_of('$LEGO_LIB','$LEGO')" 
		cd ./lib
		ccm use @
		cd ..
	fi
#########################
#Trova la dir bin
#########################
	LEGO_BIN=`ccm query -f "%objectname" -u "is_member_of('$LEGO') and name='bin' and type='dir'"`
	echo $LEGO_BIN
	if [ "$LEGO_BIN" ]
	then
		ccm query -f "%objectname"  "is_child_of('$LEGO_BIN','$LEGO') and (type='relocatable_obj' or type='executable' or type='library')" 
		cd ./bin
		ccm use @
		cd ..
	fi
########################
#Trova la dir main
########################
	LEGO_MAIN=`ccm query -f "%objectname" -u "is_member_of('$LEGO') and name='main' and type='dir'"`
	echo $LEGO_MAIN
	if [ "$LEGO_MAIN" ]
	then 
		ccm query -f "%objectname"  "is_child_of('$LEGO_MAIN','$LEGO') and (type='relocatable_obj' or type='executable' or type='library')"
		cd ./sorglego/main
		ccm use @
		cd ../..
	fi
#########################
#Trova la dir procedure
#########################

        LEGO_PROCEDURE=`ccm query -f "%objectname" -u "is_member_of('$LEGO') and name='procedure' and type='dir'"`
        echo $LEGO_PROCEDURE
        if [ "$LEGO_PROCEDURE" ]
        then
                ccm query -f "%objectname"  "is_child_of('$LEGO_PROCEDURE','$LEGO') and (type='templ')" 
                cd ./procedure
                ccm use @
                cd ..
        fi
SINCRON=1
echo ""
echo "***   Allineamento progetto LEGO eseguito ***"
echo ""

