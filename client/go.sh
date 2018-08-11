#!bin/sh

INC="0"
while [ $INC -lt $3 ]
do
	# ./execlient 10.114.12.13 8888 &
	./execlient $1 $2 &
	INC=$[$INC + 1]
done
