#!/usr/bin/env bash

if [ ! -d build ]; then
    mkdir build
fi
cd build &&
cmake .. &&
make &&
cd bin
./cdna-node-core
#./boot
#./shell-terminal