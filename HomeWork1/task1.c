//Вывести квадратную матрицу по заданному N.
#include <stdio.h>

#define N 10

void main()
{
    int matrix [N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = N * i + j + 1;
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("\n");
        for (int j = 0; j < N; j++)
        {
            printf("%3i ",matrix[i][j]);
        }
    }
    printf("\n");
}