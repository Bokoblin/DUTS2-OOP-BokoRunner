#!/bin/bash

mkdir -p build
cd build
rm -rf ./*

if [[ $# -eq 1 ]] && { [[ $1 == "-h" ]] || [[ $2 == "--help" ]]; }

then
    echo "Usage :"
    echo "$0"
    echo "$0 -c <clang|gnu>"
elif [[ $# -eq 2 ]] && [[ $1 == "-c" ]]
then
    if [[ $2 == "gnu" ]]
    then
        export CC=/usr/bin/gcc
        export CXX=/usr/bin/g++

        cmake ..
    elif [[ $2 == "clang" ]]
    then
        export CC=/usr/bin/clang
        export CXX=/usr/bin/clang++

        cmake ..
    fi
else
	cmake ..
fi

core_number=$(grep ^cpu\\scores /proc/cpuinfo | uniq |  awk '{print $4}')
jobs_number=$(awk "BEGIN {print 1.5 * $core_number}")
make -j ${jobs_number}
