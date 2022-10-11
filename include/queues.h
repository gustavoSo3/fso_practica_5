// #ifndef QUEUES_H

#include <pthread.h>

#define QUEUESIZE 10

struct STRQUEUE {
	pthread_t threads[QUEUESIZE];
	int first,last;
};

typedef struct STRQUEUE * QUEUE;

QUEUE queue_create();
void queue_destroy(QUEUE q);
void queue_offer(QUEUE q,pthread_t t);
pthread_t queue_poll(QUEUE q);
int queue_is_empty(QUEUE q);

// #endif