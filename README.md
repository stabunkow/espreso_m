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

Or you can pull image：

```shell
$ docker pull stabunkow/espreso_m:v1 # for cpu compile
$ docker pull stabunkow/espreso_m:v2 # for device compile version
```

## Case file

Fuel rod small case are provided, normal case are located at espreso_m:v2 image.

### Run case

small case: rlzj_small

Set up at 1 node, 4 mpi processes, each mpi process set 1 core.  Node memory larger than 8GB.

```shell
$ ./run_0.sh        # for default strategy run
$ ./run_coarse.sh   # for coarse load-balance run
$ ./run_fine.sh     # for fine load-balance run
```

normal case: rlzj

Set up at 8 nodes, 8 mpi processes, each mpi process set 32 cores.  Each node memory larger than 50GB.

```shell
$ ./run_0.sh      # for default strategy run
$ ./run_coarse.sh # for coarse load-balance run
$ ./run_fine.sh   # for fine load-balance run
$ ./run_device.sh # for device run
```

## Reference

[espreso](https://github.com/It4innovations/espreso)