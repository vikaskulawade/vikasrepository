#!/bin/bash
var1="/usr/include/bits/typesizes.h"
var2="/usr/include/linux/posix_types.h"
var14="/home/http/FCGI_ADSERVER/Install/Apache2/conf/extra/httpd-default.conf"


var3=$(cat $var1 |grep "__FD_SETSIZE"|cut -d'_' -f4|tr -s [\\t] ' ' | cut -d' ' -f2)
#var3=$(cat $var1 | grep __FD_SETSIZE | tr -s '\t' ' ' |tr -s ' ' ' ' |  cat -T | cut -d' ' -f3)
#echo var3= $var3 

var4=$(cat $var2 |grep " __FD_SETSIZE" | grep "#define"| cut -d'_' -f4| tr -s [\\t] ' '|cut -d' ' -f2)
#echo var4= $var4

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
#echo $var5

var6=$(ulimit -a | grep "stack size"|cut -d')' -f2)
#echo $var6
size=20480
if [ $var5 = "unlimited" -a $var6 -eq $size ]
then
        echo "Both Value Matches to each other"
else
        echo "Expected value === $ulimit and Unexpected value === $var3"
fi


var7=$( free -g|sed '3,4d' | sed 1d|cut -d':' -f2 |awk '{print $1}' )
echo $var7

var8="/etc/adserver.properties"
var9=$(cat $var8 | grep "adserver.thread.count"|cut -d'=' -f2)
echo $var9
ExpectedValue=0
if [ $var7 -eq 7 ]
then
        ExpectedValue=150
else
        ExpectedValue=400
fi

if [ $var9 -eq $ExpectedValue ]
then
        echo "OK"
else
        echo "Expected value === $ExpectedValue and Unexpected value === $var9"
fi


var10=$(grep '[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}' /etc/*.properties )
#echo $var10


var11=$( ifconfig -a | sed '1d' |sed '2,17d'|cut -d':' -f2|awk '{print $1}'|cut -c1-6)




var12=$(echo "$var10" | grep -v "$var11"|xargs -n 1 )
#var13=$(echo $var12 |xargs -n 1)
#echo $var13

if [ "$var12" ]
then
        echo "\n  UnExpected =$var12"
else
       echo" Expected    =$var12"
fi



var15=$(cat $var14 |grep "Timeout 300"|cut -d' ' -f2 )
echo $var15

var16=$(cat $var14 |grep "KeepAlive Off"|cut -d' ' -f2 )
echo $var16


var17=$( echo stats | nc 172.16.4.15 11211 | grep curr_conn)
echo $var17



























































































