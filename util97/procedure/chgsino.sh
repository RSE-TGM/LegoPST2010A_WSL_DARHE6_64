###############################################################
#
# Sostituisce nei file .pag .rtf e Context.ctx l'attributo
# del plant display da Sinottico e Teleperm
#
###############################################################
#
export plantd
#ls M_S_*.pag | while read plantd
#do
#  sed s/Teleperm/Sinottico/ ${plantd} > ${plantd}.Tel
#  mv ${plantd}.Tel ${plantd}
#done
#ls M_S_*.rtf | while read plantd
#do
#  sed s/Teleperm/Sinottico/ ${plantd} > ${plantd}.Tel
#  mv ${plantd}.Tel ${plantd}
#done
if [ -f Context.ctx ]
then
  sed s/Sinottico/Teleperm/ Context.ctx > Context.ctx.Tel
  mv Context.ctx.Tel Context.ctx
fi
