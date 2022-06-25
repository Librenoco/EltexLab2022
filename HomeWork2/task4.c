//Телефонный справочник (функции и динамическая память)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define N 3
#define SIZE 12

struct telephoneUser
{
    long number;
    char firstName[SIZE];
    char lastName[SIZE];
};
enum menuItem
{
    START,
    ADD_NEW_USER,
    OUTPUT_USER_LIST,
    USER_SEARCH,
    USER_DELETE,
    EXIT
};

typedef struct telephoneUser telephoneUser;
typedef enum menuItem menuItem;

void phoneBookMenu();
void phoneBookDeleteUser(struct telephoneUser *);
void phoneBookAddUser(struct telephoneUser *);
void phoneBookSearchUser(struct telephoneUser *);
void phoneBookOutputUserList(struct telephoneUser *);

void main()
{
    phoneBookMenu();
}

void phoneBookMenu()
{
    menuItem menuItems = START;

    telephoneUser *pUsers = calloc(N, sizeof(telephoneUser));
    if (pUsers == NULL)
    {
        printf("ERROR");
        exit(-1);
    }

    system("clear");

    while (menuItems != EXIT)
    {
        printf("1. Добавить нового пользователя\n");
        printf("2. Вывести список пользователей\n");
        printf("3. Найти пользователя по имени\n");
        printf("4. Удалить пользователя\n");
        printf("5. Выход\n\n");
        printf("Выберите пункт в меню: ");

        scanf("%u", &menuItems);

        switch (menuItems)
        {
        case ADD_NEW_USER:
        {
            phoneBookAddUser(pUsers);
            menuItems = START;
            break;
        }

        case OUTPUT_USER_LIST:
        {
            phoneBookOutputUserList(pUsers);
            menuItems = START;
            break;
        }

        case USER_SEARCH:
        {
            phoneBookSearchUser(pUsers);
            menuItems = START;
            break;
        }

        case USER_DELETE:
        {
            phoneBookDeleteUser(pUsers);
            menuItems = START;
            break;
        }

        case EXIT:
        {
            system("clear");
            break;
        }

        default:
            system("clear");
            printf("Ошибка: введено некорректное значение пункта (повторите попытку)\n");
            menuItems = START;
            break;
        }
    }
    free(pUsers);
}

void phoneBookDeleteUser(struct telephoneUser *pUsers)
{
    system("clear");
    printf("Удаление пользователя\n\n");
    printf("Введите порядковый номер пользователя: ");

    int recordNumber = 0;
    scanf("%i", &recordNumber);

    pUsers[recordNumber - 1].number = 0;
    pUsers[recordNumber - 1].firstName[0] = '\0';
    pUsers[recordNumber - 1].lastName[0] = '\0';

    printf("\nПользователь удалён\n\n");
}

void phoneBookAddUser(struct telephoneUser *pUsers)
{
    system("clear");
    printf("Добавление нового пользователя\n\n");

    for (int i = 0; i < N; i++)
    {
        printf("Запись под номером %i: ", i + 1);
        if ((pUsers[i].number == 0) && (pUsers[i].firstName[0] == '\0') && (pUsers[i].lastName[0] == '\0'))
        {
            printf("Свободная\n");
        }
        else
        {
            printf("Занята\n");
        }
    }

    printf("\nДля добавления нового пользователя необходимо выбрать свободную запись\n");
    printf("\nВведите номер записи: ");

    int recordNumber = 0;
    scanf("%i", &recordNumber);

    if ((pUsers[recordNumber - 1].number != 0) && (pUsers[recordNumber - 1].firstName[0] != '-') && (pUsers[recordNumber - 1].lastName[0] != '-'))
    {
        system("clear");
        printf("Запись под номером %i занята\n\n", recordNumber);
    }
    else
    {
        printf("\nНомер пользователя: ");
        scanf("%ld", &pUsers[recordNumber - 1].number);
        printf("Имя пользователя: ");
        scanf("%s", pUsers[recordNumber - 1].firstName);
        printf("Фамилия пользователя: ");
        scanf("%s", pUsers[recordNumber - 1].lastName);
        system("clear");
    }
}

void phoneBookSearchUser(struct telephoneUser *pUsers)
{
    system("clear");
    printf("Поиск пользователя по имени\n\n");
    printf("Введите имя пользователя: ");

    char userName[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        userName[i] = '\0';
    }

    scanf("%s", userName);
    printf("\n");
    printf("Найденные записи:\n\n");

    for (int i = 0; i < N; i++)
    {
        if (strcmp(pUsers[i].firstName, userName) == 0)
        {
            printf("User №%i", i + 1);
            printf("\nНомер пользователя: %ld ", pUsers[i].number);
            printf("\nИмя пользователя: %s ", pUsers[i].firstName);
            printf("\nФамилия пользователя: %s \n\n", pUsers[i].lastName);
        }
    }

    printf("\n");
}

void phoneBookOutputUserList(struct telephoneUser *pUsers)
{
    system("clear");

    for (int i = 0; i < N; i++)
    {
        printf("\nUser №%i", i + 1);
        printf("\nНомер пользователя: %ld ", pUsers[i].number);
        printf("\nИмя пользователя: %s ", pUsers[i].firstName);
        printf("\nФамилия пользователя: %s \n", pUsers[i].lastName);
    }

    printf("\n");
}