#############################################################################
#
# Ripulisce tutti i file *.pag dai resti dei widget cancellati
#
#############################################################################
#
#############################################################################
# Operazioni preliminari 
#############################################################################
#
export pagina
rm -f modoff.out
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca
#----------------------------------------------------------------------------
#
echo "anywidget=" > modoff.scr
echo "attrib=nome" >> modoff.scr
echo "samevalue=" >> modoff.scr
#
#############################################################################
# Loop sulle pagine
#############################################################################
#
ls ????.pag | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> modoff.out
  pagmod.1.4 -p ${pagina} -s modoff.scr 2>> modoff.out
done
rm -f modoff.scr
