espreso modified.

## Dependencies

Download Math Lib: 

- [Intel MKL](https://software.intel.com/en-us/intel-mkl)

MKL install config: slient.cfg

Download Graph partitioners:

- [ParMetis](http://glaros.dtc.umn.edu/gkhome/metis/parmetis/overview)
- [Metis](http://glaros.dtc.umn.edu/gkhome/metis/metis/overview)

Metis config: metis.h (For 64 bits)

Download ROCM（For device usage)：

- [ROCM](https://github.com/RadeonOpenCompute/ROCm)
- [rocBlas](https://github.com/ROCmSoftwarePlatform/rocBLAS)

## Install

Install MKL:

```shell
$  tar zxvf l_mkl_2019.5.281.tgz 
$  l_mkl_2019.5.281/install.sh -s silent.cfg            # install mkl
$  /home/root/install/intel/bin/compilervars.sh intel64 # configure mkl
```

Install Metis:

```shell
$ tar zxvf metis-5.1.0.tar.gz
$ cp metis.h metis-5.1.0/include/
$ make config prefix=~/install-path
$ make 
$ make install
```

Install ParMetis:

```shell
$ tar zxvf parmetis-4.0.3.tar.gz
$ cp metis.h parmetis-4.0.3/metis/include/
$ make config prefix=~/install-path
$ make 
$ make install
```

Install espreso

```bash
$ ./waf configure --intwidth=64 --metis=metis-install-path --parmetis=parmetis-install-path
$ ./waf $(nproc)
```

For device usage， follow the guide bellows:

[ROCm Installation documentation](https://rocmdocs.amd.com/en/latest/Installation_Guide/Installation-Guide.html)

[rocBLAS documentation](https://rocblas.readthedocs.io/en/rocm-5.1.1/Linux_Install_Guide.html#installing-pre-built-packages)

Build espreso wtih rocm/rocblas lib at build last step：

```shell
$ /usr/bin/mpic++ -fopenmp -L/opt/rocm/lib  src/app/espreso.cpp.37.o -L/opt/rocm/rocblas/lib -o/home/root/espreso_m/build/espreso -Wl,-Bstatic,--start-group -Wl,--end-group -Wl,-Bdynamic -Wl,--no-as-needed -L. -L/home/root/install/metis/lib -L/home/root/install/parmetis/lib -lnbesinfo -lnbconfig -lnbbasis -lnbwmpi -lnbmesh -lnbinput -lnboutput -lnbwpthread -lnbwcatalyst -lnbwhdf5 -lnbwgmsh -lnbwnglib -lnbwmetis -lnbwparmetis -lnbwscotch -lnbwptscotch -lnbwkahip -lnbphysics -lnbdevel -lnbmath -lnbautoopt -lnbwmkl -lnbwcuda -lnbwhypre -lnbwmklpdss -lnbwpardiso -lnbwsuperlu -lnbwwsmp -lnbwcsparse -lnbwbem -lnbwnvtx -lnbfeti -lparmetis -lmetis -lmkl_intel_ilp64 -lmkl_core -lmkl_gnu_thread -lmkl_blacs_intelmpi_ilp64 -lrocblas
```

All install steps can refer to Dockerfile or Dockerfile_device.

Or you can pull image：

```shell
$ docker pull stabunkow/espreso_m:v1 # for cpu compile
$ docker pull stabunkow/espreso_m:v2 # for device compile version
```

## Case file

Fuel rod small case are provided.

small case: rlzj_small

Set up at 1 node, 4 mpi processes, each mpi process set 1 core.  Node memory larger than 8GB.

```shell
$ ./run_0.sh        # for default strategy run
$ ./run_coarse.sh   # for coarse load-balance run
$ ./run_fine.sh     # for fine load-balance run
```

normal case: rlzj，[download](https://drive.google.com/file/d/1qrc-skigwrdSfAGDBqLrzImRSY0E8cHS/view?usp=sharing)

At slurm workload manager，modify espreso.slurm to run.

```slurm
#!/bin/bash
#SBATCH -J %j
#SBATCH -p normal
#SBATCH -t 03:00:00             # work time
#SBATCH --mem=100G              # node mem limit
#SBATCH -n 8                    # mpi processes num
#SBATCH --ntasks-per-node=1     # mpi processes num at each node
#SBATCH --ntasks-per-socket=1   
#SBATCH --cpus-per-task=32      # cpu num at each mpi process
#SBATCH -o slurmlog/espreso.%j.log
#SBATCH -e slurmlog/espreso.%j.log
##SBATCH --gres=dcu:4           # special device node with device count

cpu_per_task=8
process_sum=${SLURM_NTASKS}
if [ -n "${SLURM_CPUS_PER_TASK}" ]; then
        cpu_per_task=$SLURM_CPUS_PER_TASK
fi
export OMP_NUM_THREADS=${cpu_per_task}

source ~/espreso_m/build/env/threading.default ${cpu_per_task}                                              
mpirun --bind-to none -n ${process_sum} espreso -c espreso.ecf
```

Set up at 8 nodes, 8 mpi processes, each mpi process set 32 cores.  Each node memory larger than 50GB.

```shell
$ mpirun -n 8 espreso -c espreso.ecf 0 0 0   # for default strategy run
$ mpirun -n 8 espreso -c espreso.ecf 1 0 0   # for coarse load-balance run
$ mpirun -n 8 espreso -c espreso.ecf 1 1 0   # for fine load-balance run
$ mpirun -n 8 espreso -c espreso.ecf 1 1 1   # for device run
```

espreso configure file information：

```ecf
INPUT {
  loaddomain [ARG0];                 # set coarse load-balance, must with loaddomain.dat file
  use_mpi_balance [ARG1];            # set fine load-balance
  use_device [ARG2];                 # set device usage
  device_count 4;                    # set device count
  use_device_async 1;                # set device usage async
  device_stream_count 8;             # set device stream count
  FORMAT             VTK_LEGACY;
  PATH               vtk/rlzj.*.vtk; # set model path
  DECOMPOSITION {
    PARALLEL_DECOMPOSER   PARMETIS;
    SEQUENTIAL_DECOMPOSER METIS;
    DOMAINS    256;
  }
}
...
```

## Reference

[espreso](https://github.com/It4innovations/espreso)