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

# Debugging
Use gdb to debug your application. You can run mpirun with xterm and gdb to debug MPI programs:
```sh
mpirun -np <num_procs> xterm -e gdb --args ./your_program
```

Employ valgrind to detect memory leaks and errors:
```sh
mpirun -np <num_procs> valgrind ./your_program
```

X11 Errors:
If you're running this in an environment where you're interacting with X11 windows, make sure your display variable is set correctly:
```sh
echo $DISPLAY
```
If it's not set or you're running on a headless server without an X server, you'll need to address the X11 issue separately.