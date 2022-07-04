//Калькулятор с подключаемой библиотекой во время работы программы <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

enum menuItem
{
    START,
    ADDITION,
    SUBTRACTION,
    DIVISION,
    MULTIPLICATION,
    EXIT
};

typedef enum menuItem menuItem;

void calculatorMenu();
void arithmeticOperations(char *, char *, int (*)(int, int));

void main()
{
    calculatorMenu();
}

void arithmeticOperations(char *operationName, char *example, int (*operation)(int, int))
{
    int firstNumber;
    int secondNumber;
    int result;

    system("clear");
    printf("%s\n", operationName);
    printf("\n%s\n", example);
    printf("\nВведите a и b: ");
    scanf("%d %d", &firstNumber, &secondNumber );
    result = operation(firstNumber, secondNumber);
    printf("\nРезультат: %d\n\n", result);
}

void calculatorMenu()
{
    menuItem menuItems = START;
    void *ext_library;

	ext_library = dlopen("./Calculator/libcalculator.so", RTLD_LAZY);
	if (!ext_library)
    {
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		exit(-1);
	};

    system("clear");

    while (menuItems != EXIT)
    {
        printf("1. Сложение (a + b)\n");
        printf("2. Вычитание (a - b)\n");
        printf("3. Деление (a / b)\n");
        printf("4. Умножение (a * b)\n");
        printf("5. Выход\n\n");
        printf("Выберите пункт в меню: ");

        scanf("%u", &menuItems);

        switch (menuItems)
        {
            case ADDITION:
            {
                arithmeticOperations("Сложение",
                    "(Пример: Введите a и b: 2 3 \nРезультат: 5)",
                    dlsym(ext_library, "addition"));
                menuItems = START;
                break;
            }

            case SUBTRACTION:
            {
                arithmeticOperations("Вычитание",
                    "(Пример: Введите a и b: 2 3 \nРезультат: -1)",
                    dlsym(ext_library, "subtraction"));
                menuItems = START;
                break;
            }

            case DIVISION:
            {
                arithmeticOperations("Деление",
                    "(Пример: Введите a и b: 3 2 \nРезультат: 1)",
                    dlsym(ext_library, "division"));
                menuItems = START;
                break;
            }

            case MULTIPLICATION:
            {
                arithmeticOperations("Умножение",
                    "(Пример: Введите a и b: 2 3 \nРезультат: 6)",
                    dlsym(ext_library, "multiplication"));
                menuItems = START;
                break;
            }

            case EXIT:
            {
                system("clear");
                break;
            }

            default:
            {
                system("clear");
                printf("Ошибка: введено некорректное значение пункта (повторите попытку)\n");
                menuItems = START;
                break;
            }
        }
    }
	dlclose(ext_library);
}
