#!/bin/sh

cd lib/cadical-rel-2.1.3
./configure && make
cd ../..
cmake -B build
cmake --build build