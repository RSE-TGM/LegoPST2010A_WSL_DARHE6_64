echo "widgetclass=CaiVar" >> listacai.scr
echo "attrib=objectTag" >> listacai.scr
echo "samevalue=" >> listacai.scr
ls M_S*.pag | while read pagina
do
  echo ${pagina}
  echo ${pagina} >> listacai.out
  pagmod.1.4 -g -n -p ${pagina} -s listacai.scr 2>> listacai.out
done
rm -f listacai.scr
