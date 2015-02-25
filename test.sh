#!/bin/bash
#sed -n 's/REQ_END/REQ_END/p' error_log_1 | cut -d':' -f5 | grep -v '^[a-zA-Z ]'|grep -v "REQ_END"  |sort -n >error1.txt
#sort -nu error1.txt>error2.txt
while read line1
do
	count=0
	if [ $line1 -le 300 ]
	then
		while read line2
		do
			if [ $line1 -eq $line2 ]
			then	
				count=$(($count+1));
			fi
		done<error1.txt
		echo $line1  "Presents " $count "Times"
	fi
done<error2.txt






