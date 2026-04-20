#!/bin/bash

source /cvmfs/sft.cern.ch/lcg/views/setupViews.sh LCG_106 x86_64-el9-gcc13-opt

export PATH=/home/ceskajak/pythia8313/bin:$PATH
export LD_LIBRARY_PATH=/home/ceskajak/pythia8313/lib:/home/ceskajak/pythia8313/include:$LD_LIBRARY_PATH
export PYTHIA8DATA=/home/ceskajak/pythia8313/share/Pythia8/xmldoc

exec bash