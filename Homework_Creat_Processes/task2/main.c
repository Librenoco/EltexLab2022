// Создание процессов с помощью fork в определённом виде и вывод pid and ppid:
/*
          1 -процесс
         / \
        |   |
        2   4 - процессы
       /   / \
      |   |   |
      3   5   6 - процессы
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(void) {
  pid_t pids[5];

  pids[0] = fork();
  if (pids[0] == 0) {
    printf("2 CHILD PID: %d\n", getpid());
    printf("2 CHILD PPID: %d\n\n", getppid());
    pids[1] = fork();
    if (pids[1] == 0) {
      printf("3 CHILD PID: %d\n", getpid());
      printf("3 CHILD PPID: %d\n\n", getppid());
      // end 3
      exit(EXIT_SUCCESS);
    } else {
      // wait 3
      waitpid(pids[1], 0, 0);
      // end 2
      exit(EXIT_SUCCESS);
    }
  } else {
    printf("1 PARENT PID: %d\n", getpid());
    printf("1 PARENT PPID: %d\n\n", getppid());
    pids[2] = fork();
    if ( pids[2] == 0) {
      printf("4 CHILD PID: %d\n", getpid());
      printf("4 CHILD PPID: %d\n\n", getppid());
      pids[3] = fork();
      if (pids[3] == 0) {
        printf("5 CHILD PID: %d\n", getpid());
        printf("5 CHILD PPID: %d\n\n", getppid());
        // end 5
        exit(EXIT_SUCCESS);
      } else {
        pids[4] = fork();
        if (pids[4] == 0) {
          printf("6 CHILD PID: %d\n", getpid());
          printf("6 CHILD PPID: %d\n\n", getppid());
          // end 6
          exit(EXIT_SUCCESS);
        } else {
          // wait 5
          waitpid(pids[3], 0, 0);
          // wait 6
          waitpid(pids[4], 0, 0);
          // end 4
          exit(EXIT_SUCCESS);
        }
      }
    } else {
      // wait 4
      waitpid(pids[2], 0, 0);
      // wait 2
      waitpid(pids[0], 0, 0);
      // end parent
      exit(EXIT_SUCCESS);
    }
  }
}