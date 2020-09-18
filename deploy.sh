#!/bin/bash
DEVICE_IP=192.168.0.18
USER_NAME=root
MODULE=locata

rsync -avr $MODULE $MODULE.conf libwifi-scan.so run.sh $USER_NAME@$DEVICE_IP:/home/$USER_NAME/$MODULE/
