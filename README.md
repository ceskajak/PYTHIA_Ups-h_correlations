# PYTHIA_Ups-h_correlations
A (for now) skeleton code to study Upsilon-hadron correlations in PYTHIA (FNSPE CTU sunrise cluster dependent)

# How to work with the code
Load all libraries: `./load_PYTHIA.sh`

Compile code (needed after changing source file Bottom.cc): `./compile.sh`

## Submit jobs
`qsub Bottom.sh`

## Check job status
For all jobs: `qstat`
For particular job: `qstat $JOBID`
For job array: `qstat -t $JOBID[]`