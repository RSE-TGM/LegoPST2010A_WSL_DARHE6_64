#############################################################################
#
# Prepara i file .rtf per lo SCADA
#
# Dragoni M. 11/11/97
#
#############################################################################
#
#############################################################################
# Operazioni preliminari 
#############################################################################
#
export label
export pagina
export riga
#
if [ "$1" != "" ]
then
  echo "\n uso: $0  \n\a"
  exit 1
fi
#
#############################################################################
# Creazione del file temporaneo di lavoro
#############################################################################
#
rm -f chpg2newpg.scr chpg2newpg.out
cat > chpg2newpg.tmp << EOT
rel86
hand_op_dev_nc
hand_op_dev_no
pipe_burst
trasformer
generator
motor
malf_meas
analog_remote_par
flow_contr_branch
rem_subgrcontr
EOT
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per Pictograph
#----------------------------------------------------------------------------
#
cat chpg2newpg.tmp | while read riga
do
  echo "widgetclass=ChangePage" >> chpg2newpg.scr
  echo "hasattrib=bitmapName" >> chpg2newpg.scr
  echo "value=${riga}" >> chpg2newpg.scr
  echo "attrib=changeType" >> chpg2newpg.scr
  echo "value=1" >> chpg2newpg.scr
done
rm -f chpg2newpg.tmp
#
#############################################################################
# Loop sulle pagine
#############################################################################
#
ls M_S_*.pag | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> chpg2newpg.out
  pagmod.1.4 -g -G -p ${pagina} -s chpg2newpg.scr 2>> chpg2newpg.out
  mv ${pagina}.mod ${pagina}
done
