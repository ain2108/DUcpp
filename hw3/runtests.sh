#!/bin/sh

MAX=250
COUNTER=5
echo "" > data.txt
for ((n=1;n<50;n++)); 
do
	C=$(($n*5));
	printf "$C," >> data.txt
	./a.out $C >> data.txt
done



