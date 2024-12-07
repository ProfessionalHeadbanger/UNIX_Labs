#!/bin/bash

if [ ! "$#" -eq 3 ];
then 
	echo "Incorrect arguments, right usage is <file> <pattern> <replaceable pattern>"
	exit 1
fi

if [ ! -f $1 ];
then 
	echo "File doesn't exist"
	exit 1
fi

file=$1
pattern=$2
replaceable=$3

initial_count_lines=$(sed -n '$=' $file)
echo "Number of lines in $file before all actions: $initial_count_lines"

sed -i '/^[[:space:]]*$/d' $file &> /dev/null
sed -i "s/$pattern/$replaceable/g" $file &> /dev/null
sed -i 'n;d' $file &> /dev/null

count_lines=$(sed -n '$=' $file)
echo "Number of lines in $file after all actions: $count_lines"

exit 0
