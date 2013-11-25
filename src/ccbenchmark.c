
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "function.h"

//********************* memory ********************//
/* use for memory random access
  input: memory size for access and how many times to run
 */
void* memRandomAccess(void* _para) {
    unsigned long m = 1024ul * 1024ul * 100ul; // 100M
    CCParams * para = (CCParams *)_para;
    int size = para->params_1;
    int loops = para->params_2; //number of loops
    char * des = (char *)malloc(m*sizeof(char)); //destination memory
    char * src = (char *)malloc(loops*size*sizeof(char)); //source memory
    int j = 0;
    for (j = 0; j < loops; j++) {
        int idx =  rand()%(m - size - 1); //random index
        int idx2 = rand()%(loops*size - size - 1); //random index
        memcpy(des+idx, src+idx2, size);
    }
    free(des);
    free(src);
    return NULL;
}
/*
   hold memory for pressure test
*/
void* memHold(void* _para) {
    CCParams * para = (CCParams *)_para;
    int max_size = para->params_1;  // size of memory(M)
    int malloc_time = para->params_2; // how many times
    int size = max_size / malloc_time + 1;
    for (int i = 0;i < malloc_time;i++) {
      int char_size = size*1024*1024;
      char* mem = (char*)malloc(char_size*sizeof(char));
      printf("allocate memory:%dM\n", size);
      for (int j = 0;j < char_size;j++) {
        mem[j] = rand()%255;
      }
      sleep(1);
    }
    int allocate_size = size * (malloc_time + 1);
    printf("Finish allocate memory:%dM\n", allocate_size);
    while(1) {
      sleep(10);
      printf(".");
    }
    return NULL;
}

//********************* calculate ********************//
#define N 7200
void pi(int long_size) {
  int M = long_size;
  int B = long_size;
  int const L=4;
  // Machin公式 计算pi到一万位
  int s[M/L];
  int r1[N]={0},r2[N]={0},d1[N]={0},d2;
  int r3[N]={0},r4[N]={0},d3[N]={0},d4;
  int i,k,t,p=0,mp=M/L/20;

  r1[0]=1;  r1[1]=3;  r3[0]=4;
  for(k=0;k<M/L;++k){
    t=r1[0]*B;
    d1[0]=t/0x5;
    r1[0]=t%0x5;
    t=r3[0]*B;
    d3[0]=t/0xEF;
    r3[0]=t%0xEF;
    s[k]=d1[0]-d3[0];
    int tag=0;
    for(i=1;i<N;++i){
      t=r1[i]*B+d1[i-1];
      d1[i]=t/0x19;
      r1[i]=t%0x19;
      t=r2[i]*B+d1[i];
      d2=t/(2*i+1);
      r2[i]=t%(2*i+1);
      t=r3[i]*B+d3[i-1];
      d3[i]=t/0xDF21;
      r3[i]=t%0xDF21;
      t=r4[i]*B+d3[i];
      d4=t/(2*i+1);
      r4[i]=t%(2*i+1);
      if(tag){
        s[k]+=(d2-d4);
        tag=0;
      } else {
        s[k]+=(d4-d2);
        tag=1;
      }
    }
    if(p==mp) {
      //printf(">");
      p=0;
    } else
       p++;
    }
    for(i=M/L-1;i>=0;i--) {
      while(s[i]>=B) {
        s[i-1]++;
        s[i]-=B;
      }
      while(s[i]<0) {
        s[i-1]--;
        s[i]+=B;
      }
    }
/*    printf("\npi=3.\n");
    for(i=0;i<M/L;++i)
      printf("%04d",s[i]);
      */
}

void* computePi(void* _para) {
    CCParams * para = (CCParams *)_para;
    int times = para->params_1;
    int long_size = para->params_2; //number of loops
    for (int i = 0;i < times;i++) {
      pi(long_size);
    }
    return NULL;
}
