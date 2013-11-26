#!/bin/bash

WAIT_SECS=10
BIN_NAME=ccbenchmark
LOG_FILE=log.txt
cmd=./$BIN_NAME

job_array=(
      "diskRanRead:10240:100000000"
       )

#"memHold:1024:100,computePi:1000:100000"
#"memHold:1024:100,computePi:10:1000"
#"computePi:1000:100000"
#"memRandomAccess:512:1000"


usage() {
  echo "bash run_benchmark.sh (start|stop)"
}
start() {
  echo $cmd
  ulimit -c unlimited
  rm $LOG_FILE
  for job in ${job_array[@]};do
# eval $cmd -t \"$job\" 2>>$LOG_FILE 1>>$LOG_FILE &
    eval $cmd -t \"$job\"
    echo "eval $cmd -t \"$job\" 2>>$LOG_FILE 1>>$LOG_FILE &"
  done

  time_left=$WAIT_SECS
  while [ $time_left -gt 0 ]; do
    cnt=$(ps aux | grep -v grep | grep -c $BIN_NAME )
    if [ $cnt != 0 ]; then
      return 0
    fi  
    sleep 1
    time_left=$(($time_left-1))
  done
  return 1
}
stop() {
  killall $BIN_NAME
  time_left=$WAIT_SECS
  while [ 1 ]; do
    pid=$(ps aux | grep $BIN_NAME| grep -v grep | awk '{print $2}')
    if [ "$pid" == "" ]; then
      break
    fi
    sleep 1
    time_left=$(($time_left-1))
  done
  echo "ccbenchmark be killed."
}

if [ $# -ne 1 ];then
  usage
elif [ $1 == "start" ];then
  start
elif [ $1 == "stop" ];then
  stop
else
  usage
fi
