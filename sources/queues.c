#include <queues.h>

void queue_offer(QUEUE q,pthread_t t)
{
	q->threads[q->first]=t;
	q->first++;
	q->first%=QUEUESIZE;
}

pthread_t queue_poll(QUEUE q)
{
	pthread_t ret=q->threads[q->last];
	q->last++;
	q->last%=QUEUESIZE;
	return(ret);
}

QUEUE queue_create()
{
	QUEUE q = malloc(sizeof(struct STRQUEUE));
	q->first=0;
	q->last=0;
	return q;
}

void queue_destroy(QUEUE q)
{
	free(q);
}

int queue_is_empty(QUEUE q)
{
	return q->first == q->last;
}