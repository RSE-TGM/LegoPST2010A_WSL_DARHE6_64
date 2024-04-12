ls N_win*.list | while read file 
do 
  cp $file $file.bak
  echo "Elaborazione file $file"
  echo $file | sed "s/\.list//" | read file
  tab2sem.sh $file
done
rm N_winDFGK_S.listdb
