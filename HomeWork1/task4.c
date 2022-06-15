#include <stdio.h>

#define N 13

void main()
{
    int matrix[N][N];

    int evenNumber = (N % 2 == 0) ? 0 : 1;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = -1;
        }
    }

    for (int j = 0; j < N / 2 + evenNumber; j++)
    {
        // right >
        for (int i = 0; i < N - (j * 2); i++)
        {
            if (j > 0)
            {
                matrix[j][i + j] = matrix[j][j - 1] + i + 1;
            }
            else
            {
                matrix[j][i] = i + 1;
            }
        }
        // down >
        for (int i = 0; i < N - (j * 2); i++)
        {
            if (j > 0)
            {
                matrix[i + j][N - 1 - j] = matrix[j][N - 1 - j] + i;
            }
            else
            {
                matrix[i][N - 1] = matrix[0][N - 1] + i;
            }
        }
        // left >
        for (int i = 0; i < N - (j * 2); i++)
        {
            if (j > 0)
            {
                matrix[N - 1 - j][N - 1 - j - i] = matrix[N - 1 - j][N - 1 - j] + i;
            }
            else
            {
                matrix[N - 1][N - 1 - i] = matrix[N - 1][N - 1] + i;
            }
        }
        // up >
        for (int i = 0; i < N - 1 - (j * 2); i++)
        {
            if (j > 0)
            {
                matrix[N - 1 - j - i][j] = matrix[N - 1 - j][j] + i;
            }
            else
            {
                matrix[N - 1 - i][0] = matrix[N - 1][0] + i;
            }
        }
        // center
        if (j == 0)
        {
            matrix[N / 2 + evenNumber - 1][N / 2 + evenNumber - 1] = N * N;
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("\n");
        for (int j = 0; j < N; j++)
        {
            printf("%3i ", matrix[i][j]);
        }
    }
    printf("\n");
}
