//Пример работы (потоков) магазина с покупателем(потребность в товаре магазина) и грузчиком(привозит новый товар в магазин). Необходимо привести потребность покупателей в 0.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_STORES 5
#define NUMBER_BUYERS 3
#define NUMBER_LOADERS 1

typedef struct {
  pthread_mutex_t mutex;
  int id;
  int product;
} store;

typedef struct {
  int id;
  int loadNeedProduct;
} loader;

typedef struct {
  int id;
  int numberNeedProduct;
} buyer;

//Структура данных для передачи информации в поточную функцию (покупка товаров в магазине)
typedef struct {
  store *arrayStore;
  buyer *arrayBuer;
} pthreadArgBuy;

//Структура данных для передачи информации в поточную функцию (загрузка товаров в магазин)
typedef struct {
  store *arrayStore;
  loader *arrayLoader;
} pthreadArgLoad;

//Поточная функция для покупателей в магазине
void *threadBuy(void *args) {
  pthreadArgBuy *arg = (pthreadArgBuy*) args;
  int isLock = 0;
  printf("\nКлиент %d пришёл в магазин со следующей потребностью: %d\n",
         arg->arrayBuer->id,
         arg->arrayBuer->numberNeedProduct);

  while (arg->arrayBuer->numberNeedProduct > 0) {
    for (int i = rand() % NUMBER_STORES; i < NUMBER_STORES; i++) {
      isLock = pthread_mutex_trylock(&(arg->arrayStore[i].mutex));
      if (isLock == 0) {
        if (arg->arrayStore[i].product > 0) {
          printf("Клиент %d зашёл в магазин под номером: %d. В магазине на полках есть %d товаров\n",
               arg->arrayBuer->id,
               arg->arrayStore[i].id, arg->arrayStore[i].product);
          }
        if (arg->arrayStore[i].product > 0) {
          arg->arrayBuer->numberNeedProduct -= arg->arrayStore[i].product;
          if (arg->arrayBuer->numberNeedProduct < 0) {
            arg->arrayStore[i].product = arg->arrayBuer->numberNeedProduct;
            arg->arrayStore[i].product *= -1;
            arg->arrayBuer->numberNeedProduct = 0;
          } else {
            arg->arrayStore[i].product = 0;
          }
          printf("Клиент %d купил в магазине %d и теперь в магазине %d товаров, а потребность клиента состовляет %d\n",
                 arg->arrayBuer->id,
                 arg->arrayStore[i].id,
                 arg->arrayStore[i].product,
                 arg->arrayBuer->numberNeedProduct);
          pthread_mutex_unlock(&(arg->arrayStore[i].mutex));
          break;
        } else {
          printf("Клиент %d вышел из магазина под номером: %d (не покупая) и его потребность состовляет %d\n",
                arg->arrayBuer->id,
                arg->arrayStore[i].id,
                arg->arrayBuer->numberNeedProduct);
                pthread_mutex_unlock(&(arg->arrayStore[i].mutex));
        }
      }
    }
  }
  printf("\nКлиент %d устал (отдых 5 секунд)\n",
         arg->arrayBuer->id);
  sleep(5);
}

//Поточная функция для пополнения магазинов
void *threadLoad(void *args) {
  pthreadArgLoad *argL = (pthreadArgLoad*) args;
  int isLock = 0;
  while (1) {
    for (int i = rand() % NUMBER_STORES; i < NUMBER_STORES; i++) {
      isLock = pthread_mutex_trylock(&(argL->arrayStore[i].mutex));
      if (isLock == 0) {
        printf("\n%d Грузчик приехал в магазин %d\n",
               argL->arrayLoader->id,
               argL->arrayStore[i].id);
        argL->arrayStore[i].product += argL->arrayLoader->loadNeedProduct;
        printf("%d Грузчик привёз %d товаров в магазин %d и теперь в магазине есть %d товаров\n",
               argL->arrayLoader->id,
               argL->arrayLoader->loadNeedProduct,
               argL->arrayStore[i].id,
               argL->arrayStore[i].product);
        pthread_mutex_unlock(&(argL->arrayStore[i].mutex));
        break;
      }
    }
    printf("%d Грузчик отдыхает\n",
           argL->arrayLoader->id);
    sleep(1);
  }
}

int main() {
  pthread_t threadBuyer[NUMBER_BUYERS];
  pthread_t threadLoader[NUMBER_LOADERS];
  store stores[NUMBER_STORES];
  buyer buyers[NUMBER_BUYERS];
  loader loaders[NUMBER_LOADERS];
  pthreadArgBuy arg[NUMBER_BUYERS];
  pthreadArgLoad argL[NUMBER_LOADERS];
  srand(time(NULL));
//Заполнение структур начальными значениями
  for (int i = 0; i < NUMBER_STORES; ++i) {
    stores[i].id = (i + 1);
    stores[i].product = 1000 + (rand() % 501);
    pthread_mutex_init(&(stores[i].mutex), NULL);
  }

  for (int i = 0; i < NUMBER_LOADERS; ++i) {
    loaders[i].id = (i + 1);
    loaders[i].loadNeedProduct = 350 + (rand() % 351);
  }

  for (int i = 0; i < NUMBER_BUYERS; ++i) {
    buyers[i].id = (i + 1);
    buyers[i].numberNeedProduct = 1200 + (rand() % 901);
  }
//
//Запуск потоков покупателей и грузчиков
  for (int i = 0; i < NUMBER_BUYERS; ++i) {
    arg[i].arrayBuer = &(buyers[i]);
    arg[i].arrayStore = stores;
    pthread_create(&(threadBuyer[i]),NULL, threadBuy, &(arg[i]));
  }

  for (int i = 0; i < NUMBER_LOADERS; ++i) {
    argL[i].arrayLoader = &(loaders[i]);
    argL[i].arrayStore = stores;
    pthread_create(&(threadLoader[i]),NULL, threadLoad, &(argL[i]));
    pthread_detach(threadLoader[i]);
  }
//
  for (int i = 0; i < NUMBER_BUYERS; ++i) {
    pthread_join(threadBuyer[i], NULL);
  }
}
