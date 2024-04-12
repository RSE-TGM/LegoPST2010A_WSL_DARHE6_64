RITORNO=${PWD}
echo ${RITORNO}
cd ${HOME}/legocad/libut_mmi
LISTA=`ls mal*.templ`
echo ${LISTA}
cd ${RITORNO}
mkListaMalf ${LISTA}
sort -o malf_set.mf malf_set.mf
