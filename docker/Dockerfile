FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install cpio -y
RUN apt-get install mpich -y
RUN apt-get install python -y
RUN apt-get install make -y
RUN apt-get install cmake -y
RUN apt-get install git -y

# install mkl
WORKDIR /home/root
COPY l_mkl_2019.5.281.tgz .
RUN tar zxvf l_mkl_2019.5.281.tgz 
COPY silent.cfg l_mkl_2019.5.281/
RUN mkdir -p /home/root/install/intel
RUN l_mkl_2019.5.281/install.sh -s l_mkl_2019.5.281/silent.cfg

# install metis
WORKDIR /home/root
COPY metis-5.1.0.tar.gz .
RUN tar zxvf metis-5.1.0.tar.gz
COPY metis.h metis-5.1.0/include/
RUN mkdir -p /home/root/install/metis
WORKDIR /home/root/metis-5.1.0
RUN make config prefix=/home/root/install/metis \
    && make \
    && make install

# install parmetis
WORKDIR /home/root/
COPY parmetis-4.0.3.tar.gz .
RUN tar zxvf parmetis-4.0.3.tar.gz
COPY metis.h parmetis-4.0.3/metis/include/
WORKDIR /home/root/parmetis-4.0.3
RUN mkdir -p /home/root/install/parmetis
RUN make config prefix=/home/root/install/parmetis \
    && make \
    && make install

# install espreso
WORKDIR /home/root/
COPY espreso.tar.gz .
RUN tar zxvf espreso.tar.gz

WORKDIR /home/root/espreso_m
RUN chmod 755 waf
ENV CPATH="/home/root/install/metis/include:/home/root/install/parmetis/include:$CPATH"
ENV LD_LIBRARY_PATH="/home/root/install/metis/lib:/home/root/install/parmetis/lib:$LD_LIBRARY_PATH"
ENV CPATH="/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/mkl/include:$CPATH"
ENV LD_LIBRARY_PATH="/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/compiler/lib/intel64_lin:/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/tbb/lib/intel64_lin/gcc4.7:/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/compiler/lib/intel64_lin:/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/mkl/lib/intel64_lin:$LD_LIBRARY_PATH"
ENV MKLROOT=/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/mkl
ENV LIBRARY_PATH=/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/tbb/lib/intel64_lin/gcc4.7:/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/compiler/lib/intel64_lin:/home/root/install/intel/compilers_and_libraries_2019.5.281/linux/mkl/lib/intel64_lin
RUN echo ". /home/root/install/intel/bin/compilervars.sh intel64" >> /etc/bash.bashrc
RUN ./waf configure --intwidth=64 --metis=/home/root/install/metis --parmetis=/home/root/install/parmetis
RUN ./waf -j2
RUN sed -i -e 's/\r$//' /home/root/espreso_m/env/threading.default
RUN chmod 755 /home/root/espreso_m/env/threading.default
ENV PATH="/home/root/espreso_m/build:$PATH"
ENV LD_LIBRARY_PATH="/home/root/espreso_m/build:$LD_LIBRARY_PATH"

# copy case file
WORKDIR /home/root/
COPY rlzj_small.tar.gz .
RUN tar zxvf rlzj_small.tar.gz
WORKDIR /home/root/rlzj_small
RUN chmod 755 *.sh
WORKDIR /home/root/
COPY rlzj.tar.gz .
RUN tar zxvf rlzj.tar.gz
WORKDIR /home/root/rlzj
RUN chmod 755 *.sh
