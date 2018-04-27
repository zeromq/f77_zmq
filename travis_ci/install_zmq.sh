#!/bin/bash -x
#
# Tests the build distribution


VERSION=4.2.5
ZMQ_TGZ="zeromq-${VERSION}.tar.gz"

export C_INCLUDE_PATH=${C_INCLUDE_PATH}:./

# Download ZeroMQ library
# =======================

if [[ ! -f ${ZMQ_TGZ} ]]
then
   wget --no-check-certificate "https://github.com/zeromq/libzmq/releases/download/v${VERSION}/${ZMQ_TGZ}"
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
cp .libs/libzmq.a ../lib
cp .libs/libzmq.so ../lib/libzmq.so.5
cp include/{zmq.h,zmq_utils.h} ../lib
popd
pushd lib
ln -s libzmq.so.5 libzmq.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export LIBRARY_PATH=$LIBRARY_PATH:$PWD
export ZMQ_H=$PWD/zmq.h
popd

