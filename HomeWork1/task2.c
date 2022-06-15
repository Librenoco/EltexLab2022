#include <stdio.h>

#define N 10

void main()
{
    int array [N];

    for (int i = 0; i < N; i++)
    {
        array[i] = i + 1;
    }

    printf("Ввод->  ");
    for (int i = 0; i < N; i++)
    {
       printf("%3i", array[i]);
    }
    printf("\n");

    int temp = 0;

    for (int i = 0; i < N / 2; i++)
    {
        temp = array[i];
        array[i] = array[N - i - 1];
        array[N - i - 1] = temp;
    }

    printf("Вывод-> ");
    for (int i = 0; i < N; i++)
    {
       printf("%3i", array[i]);
    }
    printf("\n");
}