#############################################################################
#
# Sostituzione dei flagOffset per i pictograph elencati nei *.pag e *.rtf
# di Operating Window e Plant Displays
#
# Dragoni M. 14/11/97
#
#############################################################################
#
#############################################################################
# Operazioni preliminari 
#############################################################################
#
export pagina
export flag
export picto
export riga
#
#############################################################################
# Creazione del file temporaneo di lavoro
#############################################################################
#
rm -f modoff.scr modoff.out
cat > modoff.tmp << EOT
aso 1_4
br 1_6
br 2_6
gc 1_6
gc 2_6
sgc 1_6
sgc 2_6
motor 1_4
switch_little 1_4
switch_little 2_4
switch_little 3_4
switch_big 1_4
switch_big 2_4
switch_big 3_4
compr_big_vert 1_4
compr_big_ori 1_4
compr_little_vert 1_4
compr_little_ori 1_4
pump_big_vert 1_4
pump_big_ori 1_4
pump_little_vert 1_4
pump_little_ori 1_4
pump_big 1_4
compr_big 1_4
switch_big 1_4
switch_big 2_4
switch_big 3_4
motor_big_OW 1_4
aso_big 1_4
motor_big_aso 1_4
sgc_big 1_6
sgc_big 2_6
gc_big 1_6
gc_big 2_6
sgc_dgs 1_6
sgc_dgs 2_6
EOT
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per Pictograph
#----------------------------------------------------------------------------
#
cat modoff.tmp | while read riga
do
  picto=`echo ${riga} | cut -d ' ' -f 1`
  flag=`echo ${riga} | cut -d ' ' -f 2`
  echo "widgetclass=Pictograph" >> modoff.scr
  echo "hasattrib=nomeFile" >> modoff.scr
  echo "value=${picto}" >> modoff.scr
  echo "attrib=flagOffset${flag}" >> modoff.scr
  echo "value=1" >> modoff.scr
done
rm -f modoff.tmp
#
#############################################################################
# Loop sulle pagine
#############################################################################
#
ls M_S_*.pag | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modoff.out
  pagmod.1.4 -g -G -p ${pagina} -s modoff.scr 2>> modoff.out
  mv ${pagina}.mod ${pagina}
done
ls M_S_*.rtf | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modoff.out
  pagmod.1.4 -g -G -p ${pagina} -s modoff.scr 2>> modoff.out
  mv ${pagina}.mod ${pagina}
done
ls O_*.pag | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modoff.out
  pagmod.1.4 -g -G -p ${pagina} -s modoff.scr 2>> modoff.out
  mv ${pagina}.mod ${pagina}
done
ls O_*.rtf | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modoff.out
  pagmod.1.4 -g -G -p ${pagina} -s modoff.scr 2>> modoff.out
  mv ${pagina}.mod ${pagina}
done
rm -f modoff.scr
