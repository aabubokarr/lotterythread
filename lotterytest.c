#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;
  int pid;
  int tickets[] = {10, 20, 30};

  printf(1, "Lottery test starting\n");

  for(i = 0; i < 3; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "fork failed\n");
      exit();
    }
    if(pid == 0){
      // Child
      settickets(tickets[i]);
      printf(1, "Child %d started with %d tickets\n", i, tickets[i]);
      
      // Do some work
      double x = 0;
      for(int j = 0; j < 100000000; j++){
        x += 1.1;
      }
      printf(1, "Child %d finished (x=%d)\n", i, (int)x);
      exit();
    }
  }

  for(i = 0; i < 3; i++){
    wait();
  }

  printf(1, "Lottery test finished\n");
  exit();
}
