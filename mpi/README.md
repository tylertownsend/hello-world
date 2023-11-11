# MPI Setup Instructions on Ubuntu

To begin MPI programming on an Ubuntu machine, follow these steps to install the necessary tools and libraries.

## Update Your Package List

Ensure your package list is up-to-date:

```bash
sudo apt update
```
## Install the C++ Compiler
Install g++ if it's not already on your system:
```bash
sudo apt install build-essential
```

## Install MPI
Install OpenMPI, a popular MPI implementation:
```bash
sudo apt install openmpi-bin openmpi-common libopenmpi-dev
```
## Verify the Installation
Check the MPI installation:
For OpenMPI:

``` bash
ompi_info
```
# Compile Your MPI Program
Use mpic++ to compile MPI programs:
```bash
mpic++ -o your_program your_program.cpp
```
# Run Your MPI Program
Execute your MPI program with mpirun:
```bash
mpirun -np <number_of_processes> ./your_program
```
Replace <number_of_processes> with the desired number of processes.