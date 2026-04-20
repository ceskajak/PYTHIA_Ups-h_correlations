#!/bin/zsh

if [[ -n "$1" ]]; then
    FILES="$1"
else
    FILES=./*.cc
fi

g++ ./*.cc -o RunPythia `pythia8-config --cxxflags --ldflags` `root-config --cflags --glibs` -lGenVector