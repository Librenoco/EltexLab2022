//Заполнить верхний треугольник матрицы 1, а нижний 0.
#include <stdio.h>

#define N 3

void main()
{
    int matrix [N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            matrix[(N - 1) - i][j] = 0;
            matrix[(N - 1) - j][i] = 1;
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
