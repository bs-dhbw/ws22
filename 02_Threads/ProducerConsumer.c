#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* Color codes */
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KRST "\x1B[0m"

#define MAX_NR_PRODUCER 1
#define MAX_NR_CONSUMER 1
#define MAX_NR_ELEMENTS 10

pthread_t producerIds[MAX_NR_PRODUCER];
pthread_t consumerlds[MAX_NR_CONSUMER];
bool runProducer = false;
bool runConsumer = false;

typedef struct {
  uint16_t a;
  uint16_t b;
  uint32_t sum;
} DataElement_t;

typedef struct {
  size_t DataCnt;
  DataElement_t DataElement[MAX_NR_ELEMENTS];
} Data_t;

Data_t SharedData;
uint8_t GenRnd() { return rand() % 255; }

void ConsumerCalcSum(DataElement_t *DataElementPtr) {
  DataElementPtr->sum = (DataElementPtr->a + DataElementPtr->b);
}

void *Producer(void *arg) {
  printf("Start Producer[%lu]\n", pthread_self());

  while (runProducer) {
    sleep(rand() % 3); /* Producing takes some time */
    /* Produce new data element */
    if (SharedData.DataCnt < MAX_NR_ELEMENTS) {
      SharedData.DataElement[SharedData.DataCnt].a = GenRnd();
      SharedData.DataElement[SharedData.DataCnt].b = GenRnd();
      SharedData.DataCnt++;

    } else {
      /* DataCnt >= MAX_NR_ELEMENTS - Producer can not produce anymore :( */
      printf(KRED "Producer[%lu] chrashed - Buffer is full\n" KRST,
             pthread_self());
      return (void *)-1;
    }
  }

  printf("Stop Producer[%lu]\n", pthread_self());
  return 0;
}

void *Consumer(void *arg) {
  printf("Start Consumer[%lu]\n", pthread_self());

  while (runConsumer) {
    sleep(rand() % 3); /* Consuming takes some time */
    if (SharedData.DataCnt != 0) {

      /* Get the next element, which should be consumed */
      DataElement_t *nextDataElementPtr =
          &SharedData.DataElement[SharedData.DataCnt];

      ConsumerCalcSum(nextDataElementPtr);
      SharedData.DataCnt--;

    } else {
      /* DataCnt is empty -> Consumer can not consume anymore :( */
      printf(KRED "Consumer[%lu] chrashed - No data to consume\n " KRST,
             pthread_self());
      return (void *)-1;
    }
  }

  printf("Stop Consumer[%lu]\n", pthread_self());
  return 0;
}

void PrintSharedData(size_t Cnt) {
  printf(KGRN "\tSharedData.DataCnt: %zu\n" KRST, SharedData.DataCnt);
  for (size_t i = 0; i < Cnt; i++) {
    printf(KGRN "\ta: %i b: %i sum: %i\n" KRST, SharedData.DataElement[i].a,
           SharedData.DataElement[i].b, SharedData.DataElement[i].sum);
  }
}

void StartProducer() {
  runProducer = true;
  for (size_t i = 0; i < MAX_NR_PRODUCER; i++) {
    pthread_create(&producerIds[i], NULL, Producer, NULL);
  }
}

void WaitProducer() {
  runProducer = false;
  for (size_t i = 0; i < MAX_NR_PRODUCER; i++) {
    pthread_join(producerIds[i], NULL);
  }
}

void PreProduce(size_t PreproduceCnt) {
  printf("PreProduce %zu elements\n", PreproduceCnt);
  if (PreproduceCnt <= MAX_NR_ELEMENTS) {
    for (size_t i = 0; i < PreproduceCnt; i++) {

      SharedData.DataElement[SharedData.DataCnt].a = GenRnd();
      SharedData.DataElement[SharedData.DataCnt].b = GenRnd();
      SharedData.DataCnt++;
    }
  }
}

void StartConsumer() {
  runConsumer = true;
  for (size_t i = 0; i < MAX_NR_CONSUMER; i++) {
    pthread_create(&consumerlds[i], NULL, Consumer, NULL);
  }
}

void WaitConsumer() {
  runConsumer = false;
  for (size_t i = 0; i < MAX_NR_CONSUMER; i++) {
    pthread_join(consumerlds[i], NULL);
  }
}

void InitSharedData(void) {
  srand(time(NULL));

  SharedData.DataCnt = 0;
  for (size_t i = 0; i < MAX_NR_ELEMENTS; i++) {
    SharedData.DataElement[i].a = 0;
    SharedData.DataElement[i].b = 0;
    SharedData.DataElement[i].sum = 0;
  }
}

int main(void) {
  size_t mainCnt = 10;
  InitSharedData();

  PrintSharedData(10);
  // PreProduce(10);
  // PrintSharedData(10);

  StartProducer();
  StartConsumer();

  while (mainCnt != 0) {
    printf("Main is running...\n");
    mainCnt--;
    sleep(1);
  }

  PrintSharedData(10);
  WaitProducer();
  WaitConsumer();

  exit(0);
}