//Калькулятор (плагины)
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <malloc.h>
#include <string.h>

#define N 2

int loadLibrary(void);
int closeLibrary(void **);
int loadMenuLibrary(void **);
int arithmeticOperations(char *, int (*)(int, int));

int main(void) {
    loadLibrary();

    return 0;
}

int loadMenu(void **pluginLibrary) {
    char *DescriptionMenu = NULL;
    char *functionName = NULL;
    void *functionExecution = NULL;
    int menuItem = 0;

    printf("\nВведите номер меню\n");
    while (menuItem != (N + 1)) {
        for (int i = 0; i < N; i++) {
            printf("%i: ", i);
            DescriptionMenu = (char *)(dlsym(pluginLibrary[i], "functionDescriptionMenu"));
            printf("%s\n", DescriptionMenu);
        }
        printf("Для выхода введите %d\n", (N + 1));
        printf("Ввод: ");
        scanf("%d", &menuItem);
        system("clear");
        if ((menuItem >= 0) && (menuItem < N)) {
            DescriptionMenu = (char *)(dlsym(pluginLibrary[menuItem], "functionDescription"));
            functionName = (char *)(dlsym(pluginLibrary[menuItem], "functionName"));
            functionExecution = dlsym(pluginLibrary[menuItem], functionName);
            arithmeticOperations(DescriptionMenu, functionExecution);
        }

    }

    return 0;
}

int loadLibrary(void) {
    char libraryPath[30];
    libraryPath[0] = '\0';

    void **pluginLibrary = malloc(sizeof(void *) * N);
    if (pluginLibrary == NULL) {
        printf("ERROR");
        exit(-1);
    }

    for (int i = 0; i < N; i++) {
        printf("\nВведите путь к %d библиотеке: ", i + 1);
        scanf("%s", libraryPath);
        pluginLibrary[i] = dlopen(libraryPath, RTLD_LAZY);
        if (!(pluginLibrary[i])) {
            fprintf(stderr, "dlopen() error: %s\n", dlerror());
            exit(-1);
        };
    }

    loadMenu(pluginLibrary);

    closeLibrary(pluginLibrary);

    return 0;
}

int closeLibrary(void **pluginLibrary) {
    for (int i = 0; i < N; i++) {
        dlclose(pluginLibrary[i]);
    }

    free(pluginLibrary);

    return 0;
}

int arithmeticOperations(char *example, int (*operation)(int, int)) {
    int firstNumber;
    int secondNumber;
    int result;

    system("clear");
    printf("\n%s\n", example);
    printf("\nВведите a и b: ");
    scanf("%d %d", &firstNumber, &secondNumber );
    result = operation(firstNumber, secondNumber);
    printf("\nРезультат: %d\n\n", result);

    return 0;
}