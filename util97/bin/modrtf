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
if [ "$1" = "" ]
then
  echo "\n uso: modrtf parametro \n\a"
  echo "parametro: sim = cambia attributo nomeProgram dei Pictograph aggiungendo _sim"
  echo "           sca = cambia attributo nomeProgram dei Pictograph togliendo _sim"
  exit
elif [ "$1" = "sim" ]
then
  label1=""
  label2="_sim"
elif [ "$1" = "sca" ]
then
  label1="_sim"
  label2=""
else
  echo "\n PARAMETRO ERRATO! Fine procedura \n\a"
  exit
fi
#
#############################################################################
# Creazione del file temporaneo di lavoro
#############################################################################
#
rm -f modrtf.scr modrtf.out
cat > modrtf.tmp << EOT
aso
br
gc
master_controller
pos_valvdamp_Blue
pos_valvdamp_DBlue
pos_valvdamp_DGrey
pos_valvdamp_DRed
pos_valvdamp_DYellow
pos_valvdamp_Green
pos_valvdamp_LBlue
pos_valvdamp_LGreen
pos_valvdamp_LGrey
pos_valvdamp_LRed
pos_valvdamp_LYellow
pos_valvdamp_Lilac
pos_valvdamp_Ochre
pos_valvdamp_Orange
pos_valvdamp_Violet
pos_valvdamp_Yellow
pumpcompr_Blue
pumpcompr_DBlue
pumpcompr_DGrey
pumpcompr_DRed
pumpcompr_DYellow
pumpcompr_Green
pumpcompr_LBlue
pumpcompr_LGreen
pumpcompr_LGrey
pumpcompr_LRed
pumpcompr_LYellow
pumpcompr_Lilac
pumpcompr_Ochre
pumpcompr_Orange
pumpcompr_Violet
pumpcompr_Yellow
sgc
sol_valvdamp_Blue
sol_valvdamp_DBlue
sol_valvdamp_DGrey
sol_valvdamp_DRed
sol_valvdamp_DYellow
sol_valvdamp_Green
sol_valvdamp_LBlue
sol_valvdamp_LGreen
sol_valvdamp_LGrey
sol_valvdamp_LRed
sol_valvdamp_LYellow
sol_valvdamp_Lilac
sol_valvdamp_Ochre
sol_valvdamp_Orange
sol_valvdamp_Violet
sol_valvdamp_Yellow
step_controller
switch_Blue
switch_DBlue
switch_DGrey
switch_DRed
switch_DYellow
switch_Green
switch_LBlue
switch_LGreen
switch_LGrey
switch_LRed
switch_LYellow
switch_Lilac
switch_Ochre
switch_Orange
switch_Violet
switch_Yellow
EOT
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per Pictograph
#----------------------------------------------------------------------------
#
cat modrtf.tmp | while read riga
do
  echo "widgetclass=Pictograph" >> modrtf.scr
  echo "hasattrib=nomeProgram" >> modrtf.scr
  echo "value=${riga}${label1}" >> modrtf.scr
  echo "attrib=nomeProgram" >> modrtf.scr
  echo "value=${riga}${label2}" >> modrtf.scr
done
rm -f modrtf.tmp
#
#############################################################################
# Loop sulle pagine
#############################################################################
#
ls | grep ^M_S_ | grep .rtf | grep -v err | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modrtf.out
  pagmod.1.4 -g -G -p ${pagina} -s modrtf.scr 2>> modrtf.out
  mv ${pagina}.mod ${pagina}
done
ls | grep ^O_ | grep .rtf | grep -v err | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modrtf.out
  pagmod.1.4 -g -G -p ${pagina} -s modrtf.scr 2>> modrtf.out
  mv ${pagina}.mod ${pagina}
done
