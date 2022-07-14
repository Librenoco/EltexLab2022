//Текстовый редактор на базе библиотеки curses (нет функции добавить строки)
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <malloc.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

WINDOW *create_newwin(int, int, int, int);
int loadFile(void **, char **);
int cursesMainWidnow(void **, char *);
int forwardReadFile(int, void **);
int representationFileTextInLines(void ***, void **);
int saveCursesWindowTextToFile(char *, char **, int);
int editTextForFile(char **, int, char);
int muve_cursor(WINDOW *, int, int);
int printLineInWindow(WINDOW *, int, char *);
void destroy_win(WINDOW *);
void sig_winch(int);

int main(int argc, char **argv) {
  if (argc == 2) {
    char *nameFile = NULL;
    void *textFile = NULL;
    nameFile = argv[1] ;
    loadFile(&textFile, &nameFile);
    cursesMainWidnow(textFile, nameFile);
    free(textFile);
  }

  return EXIT_SUCCESS;
}

int printLineInWindow(WINDOW *win, int line, char *text) {
  int x, y;
  int len = strlen(text);
  wmove(win, line, 0);

  for(int i = 0; i < len; ++i) {
    waddch(win, text[i]);
  }

  wrefresh(win);
  return EXIT_SUCCESS;
}

int cursorMovement(WINDOW *wnd, int moveX, int moveY) {
  int x = 0;
  int y = 0;
  int newLine = 0;
  int maxWinY = getmaxy(wnd);

  getyx(wnd, y, x);
  x += moveX;
  y += moveY;

  if (y > (maxWinY - 1)) {
    wscrl(wnd, 1);
    newLine = 1;
  } else if (y < 0) {
    wscrl(wnd, -1);
    newLine = 1;
  } else {
    wmove(wnd, y, x);
  }

  wrefresh(wnd);
  return newLine;
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  wrefresh(local_win);

  return local_win;
}

void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
}

void destroy_win(WINDOW *local_win) {
  wrefresh(local_win);
  delwin(local_win);
}

int representationTextInLines(char ***lineArray, void **fullText) {
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
    if (((char *)fullText)[i] == '\n') {
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

int cursesMainWidnow(void **textFile, char *nameFile) {
  WINDOW *wnd;
  char **lineText = NULL;
  int x = 0;
  int y = 0;
  int totalLine = 0;
  int currentLine = 0;
  int ch = 0;
  const char * textFromDisplay = (const char *)textFile;
  totalLine = representationTextInLines(&lineText, textFile);

  initscr();
  signal(SIGWINCH, sig_winch);
  curs_set(TRUE);
  refresh();
  wnd = create_newwin(0, 0, 0, 0);
  int maxSizeWindowY = getmaxy(wnd);
  idlok(wnd, TRUE);
  keypad(wnd, TRUE);
  scrollok(wnd, TRUE);

  for(int i = 0; (i < maxSizeWindowY) && (i < totalLine); i++) {
    printLineInWindow(wnd, i, lineText[i]);
  }

  wmove(wnd, x, y);
  wrefresh(wnd);

  while((ch = wgetch(wnd)) != KEY_F(1)) {
    switch(ch) {
      case KEY_LEFT: {
          if (x > 0) {
            x--;
            cursorMovement(wnd, -1, 0);
          }
        break;
      }
      case KEY_RIGHT: {
        x++;
        cursorMovement(wnd, 1, 0);
        break;
      }
      case KEY_UP: {
        y--;
        currentLine--;
          if (y < 0) {
            y++;
          } else if (cursorMovement(wnd, 0, -1)) {
            currentLine = 0;
            printLineInWindow(wnd, currentLine, lineText[y]);
            wmove(wnd, currentLine, x);
          }
        break;
      }
      case KEY_DOWN: {
        y++;
        currentLine++;
        if (y > (totalLine - 1)) {
          y--;
        } else if (cursorMovement(wnd, 0, 1)) {
          currentLine = maxSizeWindowY - 1;
          printLineInWindow(wnd, currentLine, lineText[y]);
          wmove(wnd, currentLine, x);
        }
        break;
      }
      case KEY_F(2): {
        saveCursesWindowTextToFile(nameFile, lineText, totalLine);
        free(lineText);
        destroy_win(wnd);
        refresh();
        endwin();
        exit(EXIT_SUCCESS);
        break;
      }
      case '\n': {
        y++;
        x = 0;
        currentLine++;
        if (y > (totalLine - 1)) {
          y--;
        } else if (cursorMovement(wnd, 0, 1)) {
          currentLine = maxSizeWindowY - 1;
          printLineInWindow(wnd, currentLine, lineText[y]);
          wmove(wnd, currentLine, x);
        }
        break;
      }
      default: {
        if ((ch > 0) && (ch < 255)) {
          editTextForFile(&(lineText[y]), x, ch);
          x++;
        }
        wmove(wnd, currentLine, x);
        break;
      }
    }
  }

  free(lineText);
  destroy_win(wnd);
  refresh();
  endwin();
  exit(EXIT_SUCCESS);
}

int saveCursesWindowTextToFile(char *nameFile, char **text, int countLine) {
  int fd;

  fd = open(nameFile, O_RDWR | O_TRUNC | O_CREAT, S_IREAD | S_IWRITE);
  if (fd < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < countLine; i++) {
    int sizeString = strlen(text[i]);

    write(fd, text[i], sizeString);
    if (i != countLine -1) {
      write(fd, "\n", sizeof(char));
    }
  }

  return EXIT_SUCCESS;
}

int editTextForFile(char **string, int position, char charToInsert) {
  int sizeString = strlen(*string);

  if (position < sizeString) {
    (*string)[position] = charToInsert;
  } else {
    *string = realloc(*string, sizeof(**string) * (position + 2));
    for (int i = sizeString; i < position; i++) {
      (*string)[i] = ' ';
    }
    (*string)[position] = charToInsert;
    (*string)[position + 1] = '\0';

    int size = strlen(*string);
    return size;
  }
}

int forwardReadFile(int fd, void **textFile) {
  void *buffer = NULL;
  off_t fileSize = 0;
  off_t errorLseek = 0;
  size_t errorRead = 0;

  fileSize = lseek(fd, 0, SEEK_END);
  if (fileSize < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  errorLseek = lseek(fd, 0, SEEK_SET);
  if (errorLseek < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  buffer = malloc(fileSize + 1);
  ((char*)buffer)[fileSize] = '\0';

  errorRead = read(fd, buffer, fileSize);
  if (errorRead < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  *textFile = buffer;
  return EXIT_SUCCESS;
}

int loadFile(void **textFile, char **nameFile) {
  int fd = 0;
  int errorClose = 0;
  ssize_t errorWrite = 0;
  ssize_t errorRead = 0;

  fd = open(*nameFile, O_RDONLY, S_IREAD);
  if (fd < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  forwardReadFile(fd, textFile);

  errorClose = close(fd);
  if (errorClose < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}