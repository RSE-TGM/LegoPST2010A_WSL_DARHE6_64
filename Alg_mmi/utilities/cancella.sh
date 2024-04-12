#Questa e ' una prova
export savedir=`pwd`
find . -type d -print | while read directory
do
cd $directory
ls *.i | cut -f1 -d. | while read file
do
rm -f ${file}.c
done
cd $savedir
done

