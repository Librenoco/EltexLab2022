//Калькулятор с динамической библиотекой
#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

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
                    "(Пример: Введите a и b: 2 3 \nРезультат: 5)", addition);
                menuItems = START;
                break;
            }

            case SUBTRACTION:
            {
               arithmeticOperations("Вычитание",
                    "(Пример: Введите a и b: 2 3 \nРезультат: -1)", subtraction);
                menuItems = START;
                break;
            }

            case DIVISION:
            {
                arithmeticOperations("Деление",
                    "(Пример: Введите a и b: 3 2 \nРезультат: 1)", division);
                menuItems = START;
                break;
            }

            case MULTIPLICATION:
            {
                arithmeticOperations("Умножение",
                    "(Пример: Введите a и b: 2 3 \nРезультат: 6)", multiplication);
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
}
