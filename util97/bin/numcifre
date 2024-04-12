#############################################################################
#
#############################################################################
#
# Prepara lo script di sostituzione
#
echo widgetclass=Indic > limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=8 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-99999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=99999999 >> limiti.scr
echo widgetclass=Indic >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=7 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-9999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=9999999 >> limiti.scr
echo widgetclass=Indic >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=6 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=999999 >> limiti.scr
echo widgetclass=Indic >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=5 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-99999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=99999 >> limiti.scr
echo widgetclass=Indic >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=4 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-9999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=9999 >> limiti.scr
echo widgetclass=Indic >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=3 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=8 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-99999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=99999999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=8 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-99999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=99999999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=7 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-9999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=9999999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=6 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-999999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=999999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=5 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-99999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=99999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=4 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-9999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=9999 >> limiti.scr
echo widgetclass=IndicTelep >> limiti.scr
echo hasattrib=tipoInd >> limiti.scr
echo value=4 >> limiti.scr
echo hasattrib=numeroInt >> limiti.scr
echo value=3 >> limiti.scr
echo attrib=valoreMinimo >> limiti.scr
echo value=-999 >> limiti.scr
echo attrib=valoreMassimo >> limiti.scr
echo value=999 >> limiti.scr
ls M_S*.pag | while read plantd
do
  cp ${plantd} ${plantd}.old
  pagmod.1.4 -g -p ${plantd} -s limiti.scr
  mv ${plantd}.mod ${plantd}
done
