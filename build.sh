#!/bin/bash

LIB_DIR=libs
OPENSSL_DIR=openssl
OPENSSL_FILE=openssl_1_1_1.tar
HOME_DIR=`git rev-parse --show-cdup; pwd`

echo "*** Start build of ants ***"

command="cd ${LIB_DIR}"

eval ${command}
if [ ! -d "$OPENSSL_DIR" ]
then
	tar -xvf $OPENSSL_FILE
	cd $OPENSSL_DIR
	./config
	./make
else
	echo "openssl directory was existing...";
fi;

cmake .
make










