#!/bin/bash

mkdir -p build
cd build
rm -rf ./*

if [ $# -eq 1 ] && ([ $1 == "-h" ] || [ $2 == "--help" ])
then
    echo "Usage :"
    echo "$0"
    echo "$0 -c <clang|gnu>"
elif [ $# -eq 2 ] && [ $1 == "-c" ]
then
    if [ $2 == "gnu" ]
    then
        export CC=/usr/bin/gcc
        export CXX=/usr/bin/g++

        cmake ..
    elif [ $2 == "clang" ]
    then
        export CC=/usr/bin/clang-5.0
        export CXX=/usr/bin/clang++-5.0

        cmake ..
    fi
else
	cmake ..
fi

make
