#ifndef FUNCTION_H_
#define FUNCTION_H_

typedef struct {
  int params_1;
  int params_2;
} CCParams;

typedef void* (*func_t)(void* _p);

typedef struct {
  func_t func;
  CCParams* _p;
  char show_info[512];
} CCJobParam;

typedef struct CCJobParamNode {
  CCJobParam job;
  struct CCJobParamNode* next;
} CCJobParamNode, *CCJobParamList;

typedef struct {
  const char* name;
  func_t func;
} benchmark_jobs_t;

void* CCWrapper(void* jpara);

func_t getJob(char* name);
#endif  // FUNCTION_H_
