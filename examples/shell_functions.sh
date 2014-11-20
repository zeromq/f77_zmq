#!/bin/bash

function run_dialog()
{
  make $SERVER $CLIENT
  TMPDIR=$(mktemp -d)
  resize > $TMPDIR/size
  source $TMPDIR/size

  declare -i H
  H=$LINES-2

  declare -i W
  W=$COLUMNS/2-2

  OUT1=$TMPDIR/out1
  OUT2=$TMPDIR/out2
  touch $OUT1 $OUT2

  (echo "SERVER" >  $OUT1 ;\ 
   echo "======" >> $OUT1 ;\
   $SERVER &>> $OUT1 ) &
  (echo "CLIENT" >  $OUT2 ;\
   echo "======" >> $OUT2 ;\
   $CLIENT &>> $OUT2 ) &

  dialog \
    --begin 1 1 \
    --tailboxbg $OUT2 $H $W \
    --and-widget \
    --begin 1 $(echo 2+$W | bc -l) \
    --tailboxbg $OUT1 $(echo $H-7 | bc -l) $W \
    --and-widget \
    --begin $(echo $H-5 |bc -l) $(echo 2+$W | bc -l) \
    --yesno "close?" 5 $W

  ps x | grep $SERVER | cut -d ' ' -f 1 | xargs kill 2> /dev/null
  ps x | grep $CLIENT | cut -d ' ' -f 1 | xargs kill 2> /dev/null

  rm -rf $TMPDIR
}

function run_nodialog()
{
  make $SERVER $CLIENT
  TMPDIR=$(mktemp -d)
  resize > $TMPDIR/size
  source $TMPDIR/size

  OUT1=$TMPDIR/out1
  OUT2=$TMPDIR/out2
  touch $OUT1 $OUT2

  (echo "SERVER" >  $OUT1 ;\ 
   echo "======" >> $OUT1 ;\
   $SERVER &>> $OUT1 ) &
  (echo "CLIENT" >  $OUT2 ;\
   echo "======" >> $OUT2 ;\
   $CLIENT &>> $OUT2 ) &

  tail -f $OUT1 $OUT2 &

#  ps x | grep $SERVER | cut -d ' ' -f 1 | xargs kill 2> /dev/null
#  ps x | grep $CLIENT | cut -d ' ' -f 1 | xargs kill 2> /dev/null

  wait %1
  wait %2
  kill -9 %3
  rm -rf $TMPDIR
}


which dialog &>/dev/null 
if [[ $? -eq 0 ]]
then
  function run()
  {
    run_dialog $@
  }
else
  function run()
  {
    run_nodialog $@
  }
fi

