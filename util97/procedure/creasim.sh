###############################################################
#
# Prepara l'ambiente per la generazione di un simulatore
#
###############################################################
#
if [ "$1" = "" ]
then
  echo "\n uso: creasim directory_simulatore \n\a"
  exit
fi
cd $HOME
if [ ! -f $HOME/legocad/libut_bin/al_sim.conf ]
then
  echo "Non esiste il file al_sim.conf !! Fine procedura \a"
else 
cp $HOME/legocad/libut_bin/al_sim.conf .
fi
if [ ! -d sked ]
then
  mkdir sked
fi
cd sked
if [ ! -d $1 ]
then
  mkdir $1
else
  echo "Il simulatore $1 e' gia' esistente !! Fine procedura.\a"
  exit
fi
cd $1
mkdir plant_display
