//Смещение адреса возврата в необходимую область (изменение адреса возврата на машинную инструкцию в кадре функции)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsPassOk(void);

int main(void)
{
    int PwStatus;
    printf("\nMain = %p  IsPassOk = %p\n", main, IsPassOk);
    puts("Enter password:");
    PwStatus = IsPassOk();

    if (PwStatus == 0)
    {
        printf("Bad password!\n");
        exit(1);
    }
    else
    {
        printf("Access granted!\n");
    }

    return 0;
}

int IsPassOk(void)
{
    char Pass[12];

    gets(Pass);

    return 0 == strcmp(Pass, "test");
}
