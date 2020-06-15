#!/bin/bash
if [[ ! -d /usr/local/include/ctdd ]]
then
	sudo mkdir /usr/local/include/ctdd
fi
sudo cp ctdd.h /usr/local/include/ctdd/
