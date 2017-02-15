#!/bin/sh

MAX=250
COUNTER=5
echo "" > data.txt
for ((n=1;n<100;n++)); 
do
	C=$((5000 + $n*5000));
	printf "$C," >> data.txt;
	./a.out $C >> data.txt;
	printf "done for n=$C\n";
done



