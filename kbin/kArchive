#!/bin/ksh
#
clear
${KBIN}/kTest
KTEST=`cat $KSTATUS/kTest.status`
echo "kTest result : $KTEST"
if [ ! "$KTEST" = "OK" ]
then
echo "Environement test not succesful\a"
banner "NOK"
exit
fi
kpresentation
if [ -f $KLOG/kArchive.log ]
then
mv $KLOG/kArchive.log $KLOG/kArchive.log.kold
fi
echo ${star}
echo ${star} >> $KLOG/kArchive.log
kAddScreen kArchive Start
kAddLog kArchive Start
Type=$1
#
if [ "$Type" = "Save" ]
then
	KREV=`cat $KINFO/Simulator_Revision.info`
	if [ ! -d $KARCHIVE/$KREV ]
	then
	mkdir $KARCHIVE/$KREV
	mkdir $KARCHIVE/$KREV/.info
	cp $KSIM/al_sim.conf $KARCHIVE/$KREV/al_sim.conf
	cp $KSIM/pd.list $KARCHIVE/$KREV/pd.list
	cp $KSIM/kMmi.cfg $KARCHIVE/$KREV/kMmi.cfg
	cp $KSIM/f22_fgraf.edf $KARCHIVE/$KREV/f22_fgraf.edf
	cp $KSIM/page_mandb.dat $KARCHIVE/$KREV/page_mandb.dat
	cp $KSIM/recorder.edf $KARCHIVE/$KREV/recorder.edf
	cp $KSIM/LeeF22.in $KARCHIVE/$KREV/LeeF22.in
	cd $KARCHIVE/$KREV/.info
	cp $KINFO/*.info .
	cp -R $KINFOTAG .
	chmod -R 777 $KARCHIVE/$KREV
	else
	echo "\nSorry, the simulator $KREV is already archived\n\a"
	fi
elif  [ "$Type" = "Load" ]
then
	echo "\n$star8"
	CONFIRM=""
	echo "Please confirm the NEW simulator directory is $KSIM."
	echo "(If not, please update KSIMNAME ressource in .profile and execute it)."
	echo "\nPress y to confirm"
	read CONFIRM
	if [ ! "${CONFIRM}" = "y" ]
	then
	echo "\nSorry ...\a\n"
	echo "$star8"
	exit
	fi
	echo "$star8"
	echo "\nThe available simulators are the following :\n"
	$KBIN/kArchiveDisponibility
	echo "\nPlease enter the simulator name you want to load :"
	read KREVOLD
	if [ -d $KARCHIVE/$KREVOLD ]
	then
	echo "\n$star4"
	echo "Please confirm updating of following files"
	echo "in $KSIM directory.\n"
	cd $KARCHIVE/$KREVOLD
	ls -C1
	CONFIRM=""
	echo "\nPress  y to confirm"
	read CONFIRM
	if [ ! "${CONFIRM}" = "y" ]
	then
	echo "\nSorry ...\a\n"
	echo "$star4"
	exit
	fi
	echo "$star4"
	if [ -f $KSIM/al_sim.conf ]
	then
	mv $KSIM/al_sim.conf $KSIM/al_sim.conf.kold
	fi
	if [ -f $KSIM/f22_fgraf.edf ]
	then
	mv $KSIM/f22_fgraf.edf $KSIM/f22_fgraf.edf.kold
	fi
	if [ -f $KSIM/page_mandb.dat ]
	then
	mv $KSIM/page_mandb.dat $KSIM/page_mandb.dat.kold
	fi
	if [ -f $KSIM/pd.list ]
	then
	mv  $KSIM/pd.list $KSIM/pd.list.kold
	fi
	if [ -f $KSIM/kMmi.cfg ]
	then
	mv  $KSIM/kMmi.cfg $KSIM/kMmi.cfg.kold
	fi
	cp $KARCHIVE/$KREVOLD/* $KSIM
	kAddInfo Original_Revision `echo "$KREVOLD"`
	echo "\nPlease update the al_sim.conf (simulator name), pd.list, kMmi.cfg and "
	echo "LeeF22.in files using an editor and EXIT THE SESSION."
	echo "(It is possible to remove the recorder.edf file if it is not necessary).\n\a\a"
	banner "EXIT"
	else
	echo "Sorry, the simulator $KREVOLD does not exist\a"
	fi
else
	echo "\n\tCorrect Use :  kArchive  [ Load / Save ]\n\a"
	exit
fi
#
kAddScreen kArchive End
kAddLog kArchive End
echo "Log File :\t$KLOG/kArchive.log"
echo "$star"
echo "$star" >> $KLOG/kArchive.log

