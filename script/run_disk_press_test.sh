#!/bin/bash

# disk performace tool, 
# include:  sequence read/write, random read/write


# dd only support sequence r/w, the result should use iostat -x to evaluation
dd_seq_read_cmd() {
    /usr/bin/time dd if=/tmp/foo of=/dev/null iflag=direct bs=1k count=100k
    /usr/bin/time dd if=/tmp/foo of=/dev/null iflag=direct bs=8k count=100k
    /usr/bin/time dd if=/tmp/foo of=/dev/null iflag=direct bs=1M count=10k
    /usr/bin/time dd if=/tmp/foo of=/dev/null iflag=direct bs=8M count=2k
}
dd_seq_write_cmd() {
    /usr/bin/time dd if=/dev/zero of=/tmp/foo conv=fsync oflag=direct bs=1k count=100k
    /usr/bin/time dd if=/dev/zero of=/tmp/foo conv=fsync oflag=direct bs=8k count=100k
    /usr/bin/time dd if=/dev/zero of=/tmp/foo conv=fsync oflag=direct bs=1M count=10k
    /usr/bin/time dd if=/dev/zero of=/tmp/foo conv=fsync oflag=direct bs=8M count=2k
}

# fio: a powful tool
# install： ubuntu12.04LTS    apt-get install fio

fio_ran_read_cmd(){
    fio -filename=/dev/sdb1 -direct=1 -iodepth 1 -thread -rw=randread -ioengine=psync -bs=16k -size=200G -numjobs=10 -runtime=1000 -group_reporting -name=mytest
}
fio_ran_write_cmd(){
    fio -filename=/dev/sdb1 -direct=1 -iodepth 1 -thread -rw=randwrite -ioengine=psync -bs=16k -size=200G -numjobs=30 -runtime=1000 -group_reporting -name=mytest 
}
fio_seq_read_cmd() {
    fio -filename=/dev/sdb1 -direct=1 -iodepth 1 -thread -rw=read -ioengine=psync -bs=16k -size=200G -numjobs=30 -runtime=1000 -group_reporting -name=mytest 
}
fio_seq_write_cmd() {
    fio -filename=/dev/sdb1 -direct=1 -iodepth 1 -thread -rw=write -ioengine=psync -bs=16k -size=200G -numjobs=30 -runtime=1000 -group_reporting -name=mytest 
}
fio_ran_rw_cmd() {
    fio -filename=/dev/sdb1 -direct=1 -iodepth 1 -thread -rw=randrw -rwmixread=70 -ioengine=psync -bs=16k -size=200G -numjobs=30 -runtime=100 -group_reporting -name=mytest -ioscheduler=noop 
}

