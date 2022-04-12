espreso modified.

## Pull

```shell
$ docker pull stabunkow/espreso_m:v1 # for cpu compile
$ docker pull stabunkow/espreso_m:v2 # for device compile version
```

## Run

rlzj small case: /home/root/rlzj_small
```shell
$ ./run_0.sh
$ ./run_coarse.sh
$ ./run_fine.sh
```

rlzj case: /home/root/rlzj
```shell
$ ./run_0.sh
$ ./run_coarse.sh
$ ./run_fine.sh
$ ./run_device.sh
```

## Reference

[espreso](https://github.com/It4innovations/espreso)