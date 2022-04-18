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
mpirun --bind-to none -n ${process_sum} singularity exec --env OPAL_PREFIX=,OMPI_MCA_pml=,PMIX_HOME=,OSHMEM_HOME=,SHMEM_HOME=,OMPI_MCA_btl=,OMPI_MCA_btl_openib_allow_ib=,UCX_NET_DEVICES=,OMPI_MCA_coll_hcoll_np=,OMPI_MCA_btl_openib_warn_default_gid_prefix=,OMPI_MCA_coll_hcoll_enable=,UCX_IB_PCOMPI_PREFIX=/opt/opmi --rocm /path/sc.sif /opt/rely/espreso_m/espreso_m/build/espreso -c espreso.ecf
