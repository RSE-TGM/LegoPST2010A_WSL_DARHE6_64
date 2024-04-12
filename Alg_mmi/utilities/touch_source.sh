#Shell per toccare i sorgenti *.c a partire dal dir da cui la 
#Shell e' lanciata.
for file in `find . -name '*.c' -print`
do 
	echo $file
	touch $file
done
