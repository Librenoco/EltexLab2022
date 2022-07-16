//Интерпретатор командной строки (исполняемый файл с аргументами)
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *getStingWar(void);
int representationTextInArrayLines(char ***lineArray, char *fullText);

int main(int argc, char **argV) {
  system("clear");
  while (1) {
    pid_t pid = 0;
    int argC = 0;
    char **argv = NULL;
    char *enterCommand = NULL;
    printf("\nmyBash > ");
    enterCommand = getStingWar();
    argC = representationTextInArrayLines(&argv, enterCommand);

    switch(pid = fork()) {
      case -1: {
        perror("fork");
        exit(EXIT_FAILURE);
      }
      case 0: {
        int errorExecv = execv(argv[0], argv);
        if (errorExecv < 0){
          perror("Error");
          exit(EXIT_FAILURE);
        }
      }
      default: {
        int fExitCode;
        wait(&fExitCode);
        free(argv);
        free(enterCommand);
      }
    }
  }
}

char *getStingWar(void){
  char *string = malloc(sizeof(*string));
  int size = 0;

  while (1) {
    string[size] = getchar();
    size++;
    if (string[size - 1] == '\n') {
      string[size - 1] = '\0';
      break;
    }
    string = realloc(string, sizeof(*string) * (size + 1));
  }

  return string;
}

int representationTextInArrayLines(char ***lineArray, char *fullText) {
  if (fullText == NULL) {
    return EXIT_FAILURE;
  }

  int sizeString = strlen((char *)fullText);
  int countLineString = 1;
  int countLenString = 1;
  (*lineArray) = malloc(sizeof(char *) * countLineString);
  (*lineArray)[countLineString - 1] = malloc(sizeof(char) * countLineString);
  (*lineArray)[countLineString - 1][countLenString - 1] = '\0';

  for (int i = 0; i < sizeString; i++) {
    if (((char *)fullText)[i] == ' ') {
      (*lineArray)[countLineString - 1][countLenString - 1] = '\0';

      countLineString++;
      (*lineArray) = realloc(*lineArray, sizeof(char *) * countLineString);

      countLenString = 1;
      (*lineArray)[countLineString - 1] = malloc(sizeof(char) * countLenString);
      (*lineArray)[countLineString - 1][countLenString - 1] = '\0';
    } else {
      countLenString++;
      (*lineArray)[countLineString - 1] = realloc((*lineArray)[countLineString - 1], sizeof(char) * countLenString);
      (*lineArray)[countLineString - 1][countLenString - 2] = ((char *)fullText)[i];
    }
  }
  (*lineArray) = realloc(*lineArray, sizeof(char *) * (countLineString + 1));
  (*lineArray)[countLineString] = (char *)NULL;

  return countLineString;
}
