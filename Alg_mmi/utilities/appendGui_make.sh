#Appende alla fine del makefile la parte sulla chiamata per AIC
#la parte di comando si trova nel file end_make
for file in `find . -name Makefile -print`
do 
	chmod +w $file
	echo $file
	cat $file end_make > pippo
	cp pippo $file
	rm pippo
	chmod -w $file
done
