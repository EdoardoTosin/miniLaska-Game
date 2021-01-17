#!/bin/sh

set -o errexit

rm -rf build
mkdir build
cd build

#Generate build folder
cmake ../.
#make, execute compile command
make
