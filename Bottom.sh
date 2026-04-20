#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -J 1-100
#PBS -V
#PBS -N PYTHIA_Ups-h_corr
#PBS -e /home/ceskajak/PYTHIA_Ups-h_correlations/output/stderr/PYTHIA_Ups.^array_index^.err
#PBS -o /home/ceskajak/PYTHIA_Ups-h_correlations/output/stdout/PYTHIA_Ups.^array_index^.out

source /cvmfs/sft.cern.ch/lcg/views/setupViews.sh LCG_106 x86_64-el9-gcc13-opt

export PATH=/home/ceskajak/pythia8313/bin:$PATH
export LD_LIBRARY_PATH=/home/ceskajak/pythia8313/lib:/home/ceskajak/pythia8313/include:$LD_LIBRARY_PATH
export PYTHIA8DATA=/home/ceskajak/pythia8313/share/Pythia8/xmldoc

cd /home/ceskajak/PYTHIA_Ups-h_correlations

./RunPythia ${PBS_ARRAY_INDEX}
