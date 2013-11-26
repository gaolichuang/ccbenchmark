
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "function.h"
#include "ccbenchmark_disk.h"


//********************* disk ********************//
/*
  disk random read
  param1: block size
  param2: read times
 */
void* diskRanRead(void* _para) {
    CCParams * para = (CCParams *)_para;
    int buf_size = para->params_1;
    int loops = para->params_2; //number of loops
    FILE *fp = fopen(RAM_READ_FILE, "r");
    assert(fp != NULL);
    fseek(fp, 0L, SEEK_END);
    unsigned long filesize = ftell(fp);
    unsigned long pos = 0;
    char* buffer = (char *)malloc(buf_size*sizeof(char)); //buffer
    for (int i = 0; i < loops; i++) {
        pos = rand() % (filesize - buf_size); //randomly find a position
        fseek(fp, pos, SEEK_SET);
        fread(buffer, buf_size, 1, fp); //read one block from disk
    }
    fclose(fp);
    free(buffer);
    return NULL;
}
/*
  disk random write
  param1: block size
  param2: write times
 */
void* diskRanWrite(void* _para) {
    CCParams * para = (CCParams *)_para;
    int buf_size = para->params_1;
    int loops = para->params_2; //number of loops
    FILE *fp = fopen(RAM_WRITE_FILE, "r+");
    assert(fp != NULL);
    fseek(fp, 0L, SEEK_END);
    unsigned long filesize = ftell(fp);
    unsigned long pos = 0;
    char* buffer = (char *)malloc(buf_size*sizeof(char)); //buffer
    for (int i = 0; i < loops; i++) {
        pos = rand() % (filesize - buf_size); //randomly find a position
        fseek(fp, pos, SEEK_SET);
        fwrite(buffer, buf_size, 1, fp); //read one block from disk
    }
    fclose(fp);
    free(buffer);
    return NULL;
}
/*
  disk sequence read
  param1: block size
  param2: read times
 */
void* diskSeqRead(void* _para) {
    CCParams * para = (CCParams *)_para;
    int buf_size = para->params_1;
    int loops = para->params_2; //number of loops

    FILE *fp = fopen(SEQ_READ_FILE, "r");
    char *buffer = (char *)malloc(buf_size*sizeof(char));
    int pos = rand(); //randomly find a position to read first
    fseek(fp, pos, SEEK_SET);
    for (int i = 0; i < loops; i++)
      fread(buffer, buf_size, 1, fp); //read one block multiple times
    fclose(fp);
    free(buffer);
    return NULL;
}
/*
  disk sequence write
  param1: block size
  param2: write times
 */
void* diskSeqWrite(void* _para) {
    CCParams * para = (CCParams *)_para;
    int buf_size = para->params_1;
    int loops = para->params_2; //number of loops

    FILE *fp = fopen(SEQ_WRITE_FILE, "r");
    char *buffer = (char *)malloc(buf_size*sizeof(char));
    int pos = rand(); //randomly find a position to read first
    fseek(fp, pos, SEEK_SET);
    for (int i = 0; i < loops; i++)
      fwrite(buffer, buf_size, 1, fp); //read one block multiple times
    fclose(fp);
    free(buffer);
    return NULL;
}
