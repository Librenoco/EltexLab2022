#include <stdio.h>
#include <stdlib.h>

int division (int firstNumber, int secondNamber)
{
    int result;

    if (secondNamber != 0)
    {
        result = firstNumber / secondNamber;
    }
    else
    {
        printf("\nError: division by 0\n\n");
        exit(-1);
    }

    return result;
}