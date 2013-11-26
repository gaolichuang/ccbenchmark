#ifndef CCBENCHMARK_DISK_H_
#define CCBENCHMARK_DISK_H_

#define RAM_READ_FILE "/tmp/foo"
#define RAM_WRITE_FILE "/tmp/foo"
#define SEQ_READ_FILE "/tmp/foo"
#define SEQ_WRITE_FILE "/tmp/foo"

void* diskRanRead(void* _para);
void* diskRanWrite(void* _para);
void* diskSeqWrite(void* _para);
void* diskSeqRead(void* _para);

#endif  // CCBENCHMARK_DISK_H_
