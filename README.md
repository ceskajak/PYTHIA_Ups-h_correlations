# PYTHIA_Ups-h_correlations
A (for now) skeleton code to study Upsilon-hadron correlations in PYTHIA (FNSPE CTU sunrise cluster dependent)

## Prerequisites
In order to run the code successfully, please adjust your paths in `Bottom.sh` (lines 6, 7, 15.)

## How to work with the code
### Setup
Load all libraries: `./load_PYTHIA.sh`

Compile code (needed after changing source file Bottom.cc): `./compile.sh`

Execute PYTHIA interactively: `./RunPythia $ID`

### Submit jobs
`qsub Bottom.sh`

### Check job status
For all jobs: `qstat`

For particular job: `qstat $JOBID`

For job array: `qstat -t $JOBID[]`

### Cleanup
To remove all files from submitted jobs (contents of all subdirectories of the `output` directory): `./clear.sh`

## Useful Resources
PYTHIA documentation regarding particles: [Particle Properties](https://pythia.org/latest-manual/ParticleProperties.html)

PYTHIA documentation regarding Onia processes: [Onia Processes](https://pythia.org/latest-manual/OniaProcesses.html)

PDG MC numbering scheme: [Monte Carlo Particle Numbering Scheme](https://pdg.lbl.gov/2025/reviews/rpp2025-rev-monte-carlo-numbering.pdf)