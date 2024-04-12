if [ `ls *.tab | wc -l` -ge 1 ]
then
echo "\n${star}\npunt2canc.sh\n${star}"
ls *.tab | cut -f1 -d. | while read file
do
echo "Elaborating ${file}"
cat ${file}.tab | sed  "s/@\./@#/g" | tr -d '\015' > ${file}.list
done
echo "\n"
fi
