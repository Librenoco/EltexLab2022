// Передача строки от родительского процесса в дочерний с помощью pipe
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

void main(int argc, char **argV) {
  if (argc < 2) {
    exit(EXIT_FAILURE);
  }

  pid_t pid = 0;
  int errorPipe = 0;
  char buf = '1';
  int pipefd[2];

  errorPipe = pipe(pipefd);
  if (errorPipe == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {
    case -1: {
      perror("fork");
      exit(1);
    }
    case 0: {
      close(pipefd[1]);
      while (read(pipefd[0], &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
      }
      write(STDOUT_FILENO, "\n", 1);
      close(pipefd[0]);

      exit(EXIT_SUCCESS);
    }
    default: {
      close(pipefd[0]);
      write(pipefd[1], argV[1], strlen(argV[1]));
      close(pipefd[1]);
      wait(NULL);

      exit(EXIT_SUCCESS);
    }
  }
}