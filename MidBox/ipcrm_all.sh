#!/bin/bash

ipcs -m|grep -v key|grep -v -|awk {'print "ipcrm -m " $2";"'}|grep -v " ;"|bash
