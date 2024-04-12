#Shell per depurare i file *.i dalla linea con SCCS Id
#Utilizzato per migrare i file *.i sotto C.M. Continuus
for file in `find . -name '*.i' -print`
do 
	chmod +w $file
	echo $file
	sed "/SccsID/d" $file > pippo 
	cp pippo $file
	rm pippo
	chmod -w $file
done
