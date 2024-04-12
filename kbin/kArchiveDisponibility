#!/bin/ksh
#
cd $KARCHIVE
rm -f $TMPDIR/kArchiveDisponibility.*
ls -d -C1 * | while read VERSION_DIR
do
cd $VERSION_DIR/.info
if [ -f Original_Revision.info ]
then
OldRevision=`cat Original_Revision.info`
NewRevision=`cat Simulator_Revision.info`
echo "${OldRevision} -> ${NewRevision}" >> $TMPDIR/kArchiveDisponibility.WithFather
else
NewRevision=`cat Simulator_Revision.info`
echo "${NewRevision}" >> $TMPDIR/kArchiveDisponibility.WithOutFather
fi
cd $KARCHIVE
done
cat $TMPDIR/kArchiveDisponibility.WithFather > $TMPDIR/kArchiveDisponibility.mix
cat $TMPDIR/kArchiveDisponibility.WithOutFather >> $TMPDIR/kArchiveDisponibility.mix
sort -o $TMPDIR/kArchiveDisponibility.mix $TMPDIR/kArchiveDisponibility.mix
cat $TMPDIR/kArchiveDisponibility.mix
rm -f $TMPDIR/kArchiveDisponibility.*
