#Utilizzato per Inserire gli Header file di CM nei file *.c
for file in `find . -name '*.c' -print`
do 
	chmod +w $file
	echo $file
	cat headerCm $file > pippo
	cp pippo $file
	rm pippo
	chmod -w $file
done
