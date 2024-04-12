find . -name 'image*.gif' | while read var
do
echo `echo $var | sed  "s/image/Image/g"`
mv $var `echo $var | sed  "s/image/Image/g"`
done 

