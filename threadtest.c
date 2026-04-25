#include "types.h"
#include "stat.h"
#include "user.h"

void
thread_func(void *arg1, void *arg2)
{
  int val1 = (int)arg1;
  int val2 = (int)arg2;
  printf(1, "Thread started with args: %d, %d\n", val1, val2);
  exit();
}

int
main(int argc, char *argv[])
{
  void *stack = malloc(4096);
  if(stack == 0){
    printf(1, "malloc failed\n");
    exit();
  }

  printf(1, "Thread test starting\n");

  int pid = clone(thread_func, (void*)100, (void*)200, stack);
  if(pid < 0){
    printf(1, "clone failed\n");
    exit();
  }

  printf(1, "Parent waiting for thread %d\n", pid);
  void *stack_out;
  int joined_pid = join(&stack_out);
  
  printf(1, "Thread %d joined\n", joined_pid);

  free(stack);
  printf(1, "Thread test finished\n");
  exit();
}
