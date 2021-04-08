#!/bin/sh

incorrect="input 1 (of 5)? ***************************************
*********** ALARM TRIGGERED ***********
***************************************"

correct="!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         !!!!!!!!!!! SAFE OPENED !!!!!!!!!!!
         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

for i in {100..200};
do	
output=$(./s1 <<< i)

	if [ "$output" = "$incorrect" ]; then
    	echo $i;
	else
    	echo "safe opened";
	fi;
done

#echo "${incorrect}"
#echo "${output}"
