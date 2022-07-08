// Создание процесса с помощью fork и вывод основной информации pid and ppid
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(void) {
  pid_t pid = 0;
  int rv = 2;
  int *pRv = &rv;

  switch(pid = fork()) {
    case -1: {
      perror("fork");
      exit(1);
    }
    case 0: {
      printf("  CHILD\n");
      printf("  CHILD PID: %d\n", getpid());
      printf("  CHILD PPID: %d\n", getppid());
      printf("  CHILD EXIT\n");
      *pRv = 0;
      exit(*pRv);
    }
    default: {
      printf("PARENT\n");
      printf("PARENT PID: %d\n", getpid());
      printf("PARENT PPID: %d\n", getppid());
      printf("PARENT CHILD_PID: %d\n", pid);
      printf("PARENT WAIT EXIT CHILD\n");
      wait(pRv);
      printf("PARENT CHILD_RETURN_CODE: %d\n", *pRv);
      printf("PARENT EXIT\n");
    }
  }

  exit(EXIT_SUCCESS);
}