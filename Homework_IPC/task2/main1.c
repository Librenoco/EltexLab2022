//отправка сообщения с помощью FIFO (pipe) (сервер)
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
  int fd = 0;
  int errorWrite = 0;
  int result = 0;
  int errorMkfifo = 0;
  int errorUnlink = 0;
  char name[]="test.fifo";
  char buff[60];
  for (int i = 0; i < 60; i++) {
    buff[i] = '\0';
  }

  signal(SIGPIPE, SIG_IGN);
  unlink(name);

  errorMkfifo = mkfifo(name, S_IRWXO | S_IRWXG | S_IRWXU);
  if(errorMkfifo < 0) {
    printf("Can\'t create FIFO\n");
    exit(EXIT_FAILURE);
  }
  printf("%s is created\n", name);

  fd = open(name, O_WRONLY);
  if(fd < 0) {
    printf("Can\'t open FIFO for writing\n");
    exit(EXIT_FAILURE);
  }
  printf("%s is opened\n", name);

  fgets(buff, 60, stdin);
  errorWrite = write(fd, buff, 60);
  if(errorWrite != 60) {
    printf("Can\'t write all string to FIFO\n");
    exit(EXIT_FAILURE);
  }
  printf("%s is closed\n", name);

  unlink(name);
  close(fd);
  return EXIT_SUCCESS;
}