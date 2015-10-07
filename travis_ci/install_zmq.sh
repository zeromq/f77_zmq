#!/bin/bash
#
# Tests the build distribution


ZMQ_TGZ="zeromq-4.1.3.tar.gz"

export C_INCLUDE_PATH=${C_INCLUDE_PATH}:./

# Download ZeroMQ library
# =======================

if [[ ! -f ${ZMQ_TGZ} ]]
then
   wget "http://download.zeromq.org/"${ZMQ_TGZ}
   if [[ $? -ne 0 ]]
   then
      echo "Unable to download ${ZMQ_TGZ}"
      exit 1
   fi
fi

# Install ZeroMQ library
# ======================

mkdir lib

tar -zxf ${ZMQ_TGZ}
pushd ${ZMQ_TGZ%.tar.gz}
./configure --with-libsodium=no || exit 1
make -j 8 || exit 1
cp .libs/libzmq.so.5.0.0 ../lib/
cp include/{zmq.h,zmq_utils.h} ../lib
popd
pushd lib
ln -s ibzmq.so.5.0.0 libzmq.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export LIBRARY_PATH=$LIBRARY_PATH:$PWD
export ZMQ_H=$PWD/zmq.h
popd

