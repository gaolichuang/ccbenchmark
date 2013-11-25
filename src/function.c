
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#include "function.h"
#include "ccbenchmark.h"

/*
   -t memRandomAccess:512:100000,XXX:X:X
    callfunction:param_1:params_2
    memRandomAccess:mem_size:loop_num
    memHold:mem_hold_size:allocate_time
example:
    memHold:1024:10 : use 10 times to allocate 1024M memory
    computePi:run_times:result_size
example:
    computePi:1000:100000  : compute 1000 times pi which result size 100000
 */

benchmark_jobs_t jobs[] = {
    {"memRandomAccess", memRandomAccess},
    {"memHold", memHold},
    {"computePi", computePi},
};


void* CCWrapper(void* _jpara) {
  CCJobParam* jpara = (CCJobParam*)_jpara;
  void* (* func)(void* p) = jpara->func;
  CCParams* para = jpara->_p;
  struct timeval start, end;
  char* info = jpara->show_info;
  gettimeofday(&start, NULL);
  printf("====== get into %s ======\n", info);
  func(para);
  gettimeofday(&end, NULL);
  double exec_t = (1000.0*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000.0);
  printf("====== finish %s , time used  %f ms======\n", info, exec_t);
  return NULL;
}

CCJobParamList job_list = NULL;
int list_size = 0;

func_t getJob(char* name) {
  int job_num = sizeof(jobs) / sizeof(benchmark_jobs_t);
  for (int i = 0;i < job_num;i++) {
    if (strcmp(jobs[i].name, name) == 0) {
      return jobs[i].func;
    }
  }
  return NULL;
}
void parseOneJob(char* job) {
  const char* splitstr = ":";
  char* job_name = strtok(job, splitstr);
  char* param_1 = strtok(NULL, splitstr);
  char* param_2 = strtok(NULL, splitstr);
  assert(NULL == strtok(NULL,splitstr));

  CCJobParamNode* node = new CCJobParamNode;
  node->job.func = getJob(job_name);
  assert(NULL != node->job.func);
  CCParams* p = new CCParams;
  p->params_1 = atoi(param_1);
  p->params_2 = atoi(param_2);
  node->job._p = p;
  strcpy(node->job.show_info, job_name);
  node->next = job_list;
  job_list = node;
  list_size++;
  printf("Add one job name:%s params1:%s params2:%s\n",job_name, param_1, param_2);
}
void parseJobs(char* joblist) {
  char* pchar = joblist;
  char onejob[512] = {'\0'};
  int id = 0;
  while(*pchar != '\0') {
    if (*pchar == ',') {
      onejob[id] = '\0';
      id = 0;
      parseOneJob(onejob);
      pchar++;
    }
    onejob[id++] = *pchar;
    pchar++;
  }
  onejob[id] = '\0';
  parseOneJob(onejob);
}
void parseOpt(int argc, char **argv) {
  /** Parsing options **/
  int c;
  opterr=0;
  while ((c = getopt(argc, argv, "ht:")) != -1) {
    switch (c) {
      case 't':
        parseJobs(optarg);
        break;
      default:
        break;
    }
  }
}
void startJobs() {
  pthread_t * threads = (pthread_t* )malloc(list_size * sizeof(pthread_t));
  CCJobParamList plist = job_list;
  int i = 0;
  while (plist != NULL) {
    assert(pthread_create(&threads[i], NULL, CCWrapper, (void*)(&(plist->job))) == 0);
    plist = plist->next;
  }
  /** Join **/
  for( i = 0; i < list_size; i++) {
      pthread_join(threads[i], NULL);
  }
}
void Release() {
  CCJobParamList plist = job_list;
  while (plist != NULL) {
    free(plist->job._p);
    CCJobParamList tmp = plist;
    plist = plist->next;
    free(tmp);
  }
}
int main(int argc, char **argv) {
  parseOpt(argc, argv);
  assert(list_size != 0);
  startJobs();
  Release();
  return 0;
}
