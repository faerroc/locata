#!/bin/bash

./clean.sh

DIR=$PWD
FILE=locata-1.0
cd ..
rm -f $FILE.tar.gz
tar -zcvf $FILE.tar.gz src/
cd $DIR