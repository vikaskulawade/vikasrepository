#!/bin/bash
var1="/usr/include/bits/typesizes.h"
var2="/usr/include/linux/posix_types.h"
var3=$(cat $var1 |grep "__FD_SETSIZE"|cut -d'_' -f4|tr -s [\\t] ' ' | cut -d' ' -f2)
#var3=$(cat $var1 | grep __FD_SETSIZE | tr -s '\t' ' ' |tr -s ' ' ' ' |  cat -T | cut -d' ' -f3)
#echo var3= $var3 

var4=$(cat $var2 |grep " __FD_SETSIZE" | grep "#define"| cut -d'_' -f4| tr -s [\\t] ' '|cut -d' ' -f2)
echo var4= $var4

ulimit=128000

#echo $ulimit
if [ $var3 -eq $ulimit -a $var4 -eq $ulimit ] 
then
	echo "OK"
else
	echo "Expected value === $ulimit and Unexpected value === $var3"
fi

#task2
var5=$(ulimit -a | grep "core file size"| cut -d')' -f2)
echo $var5

var6=$(ulimit -a | grep "stack size"|cut -d')' -f2)
echo $var6
size=20480
if [ $var5 = "unlimited" -a $var6 -eq $size ]
then
        echo "OK"
else
        echo "Expected value === $ulimit and Unexpected value === $var3"
fi



