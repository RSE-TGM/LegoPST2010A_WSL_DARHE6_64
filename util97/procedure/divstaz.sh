#############################################################################
#
#############################################################################
#
# controllo dei parametri passati
#
if [ "$1" = "" -o "$2" = "" ]
then 
   echo "\n uso: divstaz nome_task nome_sim\n\a"
   exit
fi
dirtask=~/legocad/$1
dirstaz=~/sked/$2/o_win
if [ ! -d ${dirstaz} ]
then
   echo "\n Non esiste il direttorio ${dirstaz}\n\a"
   exit
fi
if [ ! -d ${dirtask} ]
then
   echo "\n Non esiste il direttorio ${dirtask}\n\a"
   exit
fi
echo $1 | cut -d_ -f 2 | read direc
cd ${dirstaz}
ls N_win*.list | while read var
do
   grep -c -q -i -w ${direc} ${var} &&
{
   echo ${dirtask}/${var}
   grep TITLE ${var} > ${dirtask}/${var}
   grep -i -w ${direc} ${var} >> ${dirtask}/${var}
}
done
ls mal*.list | while read var
do
   grep -c -q -i -w ${direc} ${var} &&
{
   echo ${dirtask}/${var}
   grep TITLE ${var} > ${dirtask}/${var}
   grep -i -w ${direc} ${var} >> ${dirtask}/${var}
}
done
