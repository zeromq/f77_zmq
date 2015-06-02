#!/bin/bash
#
# Tests the build distribution


ZMQ_TGZ="zeromq-4.1.1.tar.gz"

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
./configure || exit 1
make || exit 1
#cp src/.libs/libzmq.a ../lib
cp src/.libs/libzmq.so ../lib/libzmq.so.4
cp include/{zmq.h,zmq_utils.h} ../lib
popd
pushd lib
ln -s libzmq.so.4 libzmq.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export LIBRARY_PATH=$LIBRARY_PATH:$PWD
export ZMQ_H=$PWD/zmq.h
popd

