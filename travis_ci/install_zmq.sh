#!/bin/bash
#
# Tests the build distribution


VERSION=4.1.3
ZMQ_TGZ="zeromq-${VERSION}.tar.gz"

export C_INCLUDE_PATH=${C_INCLUDE_PATH}:./

# Download ZeroMQ library
# =======================

if [[ ! -f ${ZMQ_TGZ} ]]
then
   wget "http://download.zeromq.org/zeromq-${VERSION}.tar.gz"
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
./configure --without-libsodium || exit 1
make -j 8 || exit 1
cp src/.libs/libzmq.a ../lib
cp src/.libs/libzmq.so ../lib/libzmq.so.5
cp include/{zmq.h,zmq_utils.h} ../lib
popd
pushd lib
ln -s libzmq.so.5 libzmq.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export LIBRARY_PATH=$LIBRARY_PATH:$PWD
export ZMQ_H=$PWD/zmq.h
popd

