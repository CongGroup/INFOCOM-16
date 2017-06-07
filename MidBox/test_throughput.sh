#!/bin/bash

if [ ! $# == 2 ]; then

echo "Usage : ./test_throughput.sh [RULE_PATH] [PACKET_PATH]"
exit

fi

RULE_PATH=$1

PACKET_PATH=$2

CURTIME=`date +%s`

CURTIME=$(($CURTIME+600))

echo $CURTIME


for i in {1..1500}
do
echo ./ThroughputTest $i $CURTIME $TIME $RULE_PATH $PACKET_PATH

./ThroughputTest $i $CURTIME $RULE_PATH $PACKET_PATH >> res &

done

