//Телефонный справочник
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
#define SIZE 12

struct telephoneSubscriber
{
    char firstName[SIZE];
    char lastName[SIZE];
    long number;
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

typedef struct telephoneSubscriber telephoneSubscriber;
typedef enum menuItem menuItem;

void main()
{
    menuItem menuItems = START;
    telephoneSubscriber users[N];

    for (int i = 0; i < N; i++)
    {
        users[i].number = 0;
        users[i].firstName[0] = '-';
        users[i].lastName[0] = '-';
        for (int j = 1; j < SIZE; j++)
        {
            users[i].firstName[j] = '\0';
            users[i].lastName[j] = '\0';
        }
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
                system("clear");
                printf("Добавление нового пользователя\n\n");

                for (int i = 0; i < N; i++)
                {
                    printf("Запись под номером %i: ", i + 1);
                    if ((users[i].number == 0) && (users[i].firstName[0] == '-') && (users[i].lastName[0] == '-'))
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

                if ((users[recordNumber - 1].number != 0) && (users[recordNumber - 1].firstName[0] != '-') && (users[recordNumber - 1].lastName[0] != '-'))
                {
                    system("clear");
                    printf("Запись под номером %i занята\n\n", recordNumber);
                }
                else
                {
                    printf("\nНомер пользователя: ");
                    scanf("%ld", &users[recordNumber - 1].number);
                    printf("Имя пользователя: ");
                    scanf("%s", users[recordNumber - 1].firstName);
                    printf("Фамилия пользователя: ");
                    scanf("%s", users[recordNumber - 1].lastName);
                    system("clear");
                }

                menuItems = START;
                break;
            }

            case OUTPUT_USER_LIST:
            {
                system("clear");

                for (int i = 0; i < N; i++)
                {
                    printf("\nUser №%i", i + 1);
                    printf("\nНомер пользователя: %ld ", users[i].number);
                    printf("\nИмя пользователя: %s ", users[i].firstName);
                    printf("\nФамилия пользователя: %s \n", users[i].lastName);
                }

                printf("\n");
                menuItems = START;
                break;
            }

            case USER_SEARCH:
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
                    if (strcmp(users[i].firstName, userName) == 0)
                    {
                        printf("User №%i", i + 1);
                        printf("\nНомер пользователя: %ld ", users[i].number);
                        printf("\nИмя пользователя: %s ", users[i].firstName);
                        printf("\nФамилия пользователя: %s \n\n", users[i].lastName);
                    }
                }

                printf("\n");
                menuItems = START;
                break;
            }

            case USER_DELETE:
            {
                system("clear");
                printf("Удаление пользователя\n\n");
                printf("Введите порядковый номер пользователя: ");

                int recordNumber = 0;
                scanf("%i", &recordNumber);

                users[recordNumber - 1].number = 0;
                users[recordNumber - 1].firstName[0] = '-';
                users[recordNumber - 1].lastName[0] = '-';

                for (int i = 1; i < SIZE; i++)
                {
                    users[recordNumber - 1].firstName[i] = '\0';
                    users[recordNumber - 1].lastName[i] = '\0';
                }

                printf("\nПользователь удалён\n");
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
}