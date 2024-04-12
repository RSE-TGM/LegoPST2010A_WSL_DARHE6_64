ls *.mod | cut -f1,2 -d. | while read var
do
mv ${var}.mod ${var}
done
