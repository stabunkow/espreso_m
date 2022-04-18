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
