#!/bin/bash
#
# Tests the build distribution

set -e
set -i 

export C_INCLUDE_PATH=${C_INCLUDE_PATH}:./

pushd lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export LIBRARY_PATH=$LIBRARY_PATH:$PWD
export ZMQ_H=$PWD/zmq.h
popd
cd ..

# Build library and examples
# ==========================

make || (ls ; exit 1)
pushd examples
FC="gfortran -g -O2 -fopenmp"
make || (ls ; exit 1)


# Run tests
# =========

cat << EOF > ref1 
 msg_copy_from/to
 Received :Hello!
 msg_copy
 msg_new/destroy_data
 Received :Hello!
 msg_copy_from/to
 Received :Hello!
 msg_copy
 msg_new/destroy_data
 Received :Hello!
 msg_copy_from/to
 Received :Hello!
 msg_copy
 msg_new/destroy_data
 Received :Hello!
 msg_copy_from/to
 Received :Hello!
EOF

cat << EOF > ref2
           1 Received :World
           2 Received :Hello!
           3 Received :world
           4 Received :World
           5 Received :Hello!
           6 Received :world
           7 Received :World
           8 Received :Hello!
           9 Received :world
          10 Received :World
EOF

./hwserver_msg > hwserver_msg.out &
./hwclient_msg > hwclient_msg.out ;
wait

diff hwserver_msg.out ref1 || exit 1 
diff hwclient_msg.out ref2 || exit 1
