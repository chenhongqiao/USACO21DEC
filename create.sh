#!/bin/zsh

name=($1)

if [ -z $name ]
then
	echo "Error: not all parameters are supplied."
	exit -1
fi
	

if [ ! -d $name ] 
then
	mkdir -p $name
	src_path=($name/$name.cpp)
	touch $src_path
	code $src_path
	echo "Solution folder created."
else
	echo "Error: problem exists."
fi