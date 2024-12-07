#!/bin/bash

min=-10
max=10
random_number=$((min+RANDOM%(max-min+1)))

while true; 
do
	read -p "Put your number: " number
	
	if ! [[ "$number" =~ ^-?[0-9]+$ ]];
	then
		echo "That's not number, try again"
		continue
	fi
	
	if [ $number -eq $random_number ];
	then
		echo "Congratulations! The number was $random_number"
		break
	else
		echo "It's wrong, try again"
	fi
done

exit 0
