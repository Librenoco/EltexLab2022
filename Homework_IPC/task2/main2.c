//приём сообщения с помощью FIFO (pipe) (клиент)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
  int fd = 0;
  int errorRead = 0;
  int result = 0;
  int errorMknod = 0;
  char name[]="test.fifo";
  char buff[60];
  for (int i = 0; i < 60; i++) {
    buff[i] = '\0';
  }

  fd = open(name, O_RDONLY);
  if(fd < 0) {
    printf("Can\'t open FIFO for reading\n");
    exit(EXIT_FAILURE);
  }

  errorRead = read(fd, buff, 60);
  if(errorRead < 0) {
    printf("Can\'t read string\n");
    exit(EXIT_FAILURE);
  }
  printf("%s", buff);

  close(fd);
  return EXIT_SUCCESS;
}
