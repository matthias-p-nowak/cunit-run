#ifndef QUEUE_API
#define QUEUE_API

#include <stdbool.h>

/** \def QUEUE_NO_ERROR no errors during operation */
#define QUEUE_NO_ERROR 0
/** \def QUEUE_IS_EMPTY error when assuming that there are entries left in the queue */
#define QUEUE_IS_EMPTY 1
/** \def QUEUE_IS_FULL error when assuming that queue has space for more entries */
#define QUEUE_IS_FULL 2

/**
 * \struct queue
 * A circular buffer
 */
struct queue {
	/** specifies the size of the buffer */
	int size;
	/** \private position for next item to be taken out */
	int posOut;
	/** \private numbers of elements stored in the buffer */
	int count;
	/** \private the buffer, which is allocated in \e init */
	int *buffer;
};

/**
 * \typedef queue_t
 * Type definition for the struct \e queue
 */
typedef struct queue queue_t;

void init(queue_t* q);
int enqueue(queue_t* q, int val);
int dequeue(queue_t* q, int* val);
bool is_empty(queue_t* q);

#endif
