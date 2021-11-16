#!/bin/bash
#
set -x
echo "Build dir: $abs_builddir"

if [[ -n ${abs_builddir} ]] ; then
  cd ${abs_builddir}/examples
fi

function cleanall ()
{
  rm ref3 vent_thread.out hwserver_msg.out ref1 ref2 hwclient_msg.out 
}
trap cleanall EXIT


# Run tests
# =========

cat << EOF > ref1 
              msg_copy_from/to
          Received :              Hello!
                      msg_copy
          msg_new/destroy_data
          Received :              Hello!
              msg_copy_from/to
          Received :              Hello!
                      msg_copy
          msg_new/destroy_data
          Received :              Hello!
              msg_copy_from/to
          Received :              Hello!
                      msg_copy
          msg_new/destroy_data
          Received :              Hello!
              msg_copy_from/to
          Received :              Hello!
EOF

cat << EOF > ref2
   1          Received :               World
   2          Received :              Hello!
   3          Received :               world
   4          Received :               World
   5          Received :              Hello!
   6          Received :               world
   7          Received :               World
   8          Received :              Hello!
   9          Received :               world
  10          Received :               World
EOF

cat << EOF > ref3
   Joined    1
   Joined    2
   Joined    3
   Joined    4
   Joined    5
EOF

./hwserver_msg > hwserver_msg.out &
./hwclient_msg > hwclient_msg.out ;
./vent_thread | tail -5 > vent_thread.out ;
wait

diff hwserver_msg.out ref1 || exit 1 && echo server OK
diff hwclient_msg.out ref2 || exit 1 && echo client OK
diff vent_thread.out  ref3 || exit 1 && echo vent_thread OK

