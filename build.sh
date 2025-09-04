#!/bin/sh

#========================================================
# This installs the SAT-Solver CaDiCal (version) 2.1.3
# and builds the InitialSetSolver from sources.
#
# Please make sure, that Cmake (min v. 3.13) and the 
# Boost C++ Librairies are installed on your system.
#========================================================

cd lib/cadical-rel-2.1.3
./configure && make
cd ../..
cmake -B build
cmake --build build