#include <queues.h>

struct STRSEMAPHORE {
	int count;
	QUEUE queue;
};

typedef struct STRSEMAPHORE * SEMAPHORE;

SEMAPHORE semaphore_get(int val);
void semaphore_destroy(SEMAPHORE s);
void semaphore_wait(SEMAPHORE s);
void semaphore_signal(SEMAPHORE s);
