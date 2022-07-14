//Текстовый редактор на базе библиотеки curses
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

int loadFile(void **, char **);
int cursesMainWidnow(void **);
int forwardReadFile(int, void **);
void sig_winch(int);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char ** argv) {
  if (argc == 2) {
    char *nameFile = NULL;
    void *textFromFile = NULL;
    nameFile = argv[1] ;
    loadFile(&textFromFile, &nameFile);
    cursesMainWidnow(textFromFile);
    free(textFromFile);
  }

  return EXIT_SUCCESS;
}

// Изменение размера окна динамически
void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
}

// Создание окна
WINDOW *create_newwin(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  wrefresh(local_win);

  return local_win;
}

// Уничтожение окна
void destroy_win(WINDOW *local_win) {
  wrefresh(local_win);
  delwin(local_win);
}

int cursesMainWidnow(void **textFromFile) {
  WINDOW *wnd;
  int startx = 0;
  int starty = 0;
  int width = 0;
  int height = 0;
  int x = 0;
  int y = 0;
  int new_line = 0;
  int ch = 0;
  const char * textFromDisplay = (const char *)textFromFile;
  initscr();
  //cbreak(); //управление клавой с возможностью считывания прерываний (CTR + C)
  keypad(wnd, TRUE); //Работа с клавишами F1 F2 F...
  signal(SIGWINCH, sig_winch);
  curs_set(TRUE); //отображение курсора
  //start_color();// инициализирует управление цветом ncurses
  refresh();//обновление экрана
  //init_pair(1, COLOR_YELLOW, COLOR_BLUE); // задание цвета окна
  //wnd = newwin(0, 0, 0, 0); // создание окна old
  wnd = create_newwin(height, width, starty, startx); // создание окна new
  //wbkgd(wnd, COLOR_PAIR(1)); // цвет окна
  //wattron(wnd, A_BOLD);// вид текста

  wprintw(wnd, "%s", textFromDisplay); // от = 0;ображение текста на экране
  wmove(wnd, 0, 0); // курсор в начало
  //wprintw(wnd, "Enter your = 0; name...\n");
  //wgetnstr(wnd, name, = 0; MAX_NAME_LEN);
  //name[MAX_NAME_LEN] = 0;
  //wprintw(wnd, "%s", test); // отображение текста на экране
  wrefresh(wnd);// обновление окна

  while((ch = wgetch(wnd)) != KEY_F(1)) {
    switch(ch) {
      case KEY_LEFT: {
        getyx(wnd, y, x);
        wmove(wnd, y, x - 1);
        wrefresh(wnd);

        //destroy_win(my_win);
        //my_win = create_newwin(height, width, starty,--startx);
        break;
      }
      case KEY_RIGHT: {
        getyx(wnd, y, x);
        wmove(wnd, y, x + 1);//destroy_win(my_win);
        wrefresh(wnd);
        //my_win = create_newwin(height, width, starty,++startx);
        break;
      }
      case KEY_UP: {
        getyx(wnd, y, x);
        wmove(wnd, y + 1, x);//destroy_win(my_win);
        wrefresh(wnd);
        //my_win = create_newwin(height, width, --starty,startx);
        break;
      }
      case KEY_DOWN: {
        getyx(wnd, y, x);
        wmove(wnd, y - 1, x);//destroy_win(my_win);
        wrefresh(wnd);
        //my_win = create_newwin(height, width, ++starty,startx);
        break;
      }
    }
  }

  destroy_win(wnd);
  //move(8, 4); // перемещение курсора
  refresh();//обновление экрана
  //getch();// ожидание ввода (для выхода в данном случае)
  endwin();//восстанавливает то состояние, в котором терминал находился до инициализации ncurses
  exit(EXIT_SUCCESS);
}

int forwardReadFile(int fd, void **textFromFile) {
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

  *textFromFile = buffer;
  return EXIT_SUCCESS;
}

int loadFile(void **textFromFile, char **nameFile) {
  int fd = 0;
  int errorClose = 0;
  ssize_t errorWrite = 0;
  ssize_t errorRead = 0;

  fd = open(*nameFile, O_RDONLY, S_IREAD);
  if (fd < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  forwardReadFile(fd, textFromFile);

  errorClose = close(fd);
  if (errorClose < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}