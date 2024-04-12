#!/bin/ksh
#
#############################################################################
# sostituisci l'attributo Sinottico con Teleperm
#############################################################################
#
ls M_S_*.pag | while read plantd
do
  echo Elaboration plant display ${plantd}
  sed s/Teleperm/Sinottico/ ${plantd} > ${plantd}.Tel
  mv ${plantd}.Tel ${plantd}
done
if [ -f Context.ctx ]
then
  echo Elaboration file Context.ctx
  sed s/Teleperm/Sinottico/ Context.ctx > Context.ctx.Tel
  mv Context.ctx.Tel Context.ctx
fi
