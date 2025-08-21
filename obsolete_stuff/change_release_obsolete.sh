#!/bin/sh
#
#  Script:                      change_release.sh
#  Instance:            1
#  %version:            3 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Mon Apr 27 16:38:09 1998 %

################################################
#	Shell utilizzabile da ogni utente 
#	  per cambiare release a oggetti 
#	  in working nell' ambiente develop.
################################################
RELEASEOLD=$1
RELEASENEW=$2
USERNAME=$3
CONFIRM=
QUERYKO="Objects not found"
export QUERYKO CONFIRM RELEASENEW RELEASEOLD USERNAME

if [  ! "${RELEASEOLD}" -o ! "${RELEASENEW}" -o ! "${USERNAME}" ]
then
        echo "Syntax: sh change_release.sh <oldRelease_name> <newRelease_name> <userName>"
        exit
fi

echo "Old Version: " ${RELEASEOLD} "New Version: " ${RELEASENEW} "Username " ${USERNAME}
echo " Confirm (y/n) "
read CONFIRM
if [ "${CONFIRM}" != "y" ]
then
        echo "Exiting from Shell"
        exit
fi
ccm query -f "%objectname %release" -u "owner='$USERNAME' and ( status='working' or status='prep' ) and is_bound() and release='${RELEASEOLD}'" > obj_list



CONFIRM=""
export CONFIRM
echo "Objects whose release is to be changed:"
cat obj_list
echo "Do you confirm ? (y)"
read CONFIRM
if [ ${CONFIRM} != "y" ]
then
        echo "Exiting from Shell"
        exit
fi
rm obj_list
echo ""

echo "Changing release; new Release =$RELEASENEW"
ccm attr -m release -v $RELEASENEW @

echo " Alg_global release attribute  must be set by you!!!"

