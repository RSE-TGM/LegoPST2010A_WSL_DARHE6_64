########################################################################
#  modulo lego_back.sh
#  tipo 
#  release 1.10
#  data 5/13/96
#  reserved @(#)lego_back.sh	1.10
########################################################################
#
if [ "$LEGO_BACK" != "" ] 
then
cd $HOME
if [ "$LEGO_REMOTE_LIB" = "YES" ]
then
find . \( -name '*.sav' -o -name macroblocks.dat -o -name descr.dat \
       -o -name '*.f' -o -name '*.c' -o -name f01.dat -o -name f14.dat \
       -o -name '*.pag' -o -name '*.ico' -o -name '*.lib' \
       -o -name '*.templ' -o -name '*.tebkg' -o -name '*.list' \
       -o -name '*.doc' -o -name '*.bkg' -o -name S01 \
       -o -name Context.ctx -o -name Connessioni.reg \
       -o -name recorder.edf -o -name r01.dat \
       -o -name FileColoriDefault -o -name FileFontsDefault \
       -o -name SubSystem.edf -o -name Component.edf \
       -o -name foraus.for -o -name '*.mdb' \) -print | \
       grep -v libut | grep -v forausbase.f > legoback.lis
else
find . \( -name '*.sav' -o -name macroblocks.dat -o -name descr.dat \
       -o -name '*.f' -o -name '*.c' -o -name f01.dat -o -name f14.dat \
       -o -name '*.pag' -o -name '*.ico' -o -name '*.lib' \
       -o -name '*.templ' -o -name '*.tebkg' -o -name '*.list' \
       -o -name '*.doc' -o -name '*.bkg' -o -name S01 \
       -o -name Context.ctx -o -name Connessioni.reg \
       -o -name recorder.edf -o -name r01.dat \
       -o -name FileColoriDefault -o -name FileFontsDefault \
       -o -name SubSystem.edf -o -name Component.edf \
       -o -name foraus.for -o -name '*.mdb' \) -print | \
                grep -v forausbase.f > legoback.lis
fi
FILE_BACK=$LEGO_BACK/"`hostname`_`whoami`_`date  +"%d%h%y"`.tar.Z"
if [ "$OS" = "AIX" ]
then
tar -cvFf- -Llegoback.lis | compress > ${FILE_BACK} 
elif [ "$OS" = "OSF1" ]
then
tar -cvFf- -Rlegoback.lis | compress > ${FILE_BACK} 
elif [ "$OS" = "Linux" ]
then
tar -cvFf- -Tlegoback.lis | compress > ${FILE_BACK} 
else
echo "lego_back: non implementato per il sistema $OS"
fi
else
echo "lego_back: definire la variabile d'ambiente LEGO_BACK"
fi
