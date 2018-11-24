/**
 * \file
 * \author Matthias P. Nowak
 * \date 2018-04-19
 */
#include "queue.h"
#include <stdlib.h>
#ifdef DEVMODE
#include <error.h>
#include <errno.h>
#endif


void init(queue_t* q) {
	/**
	 * \fn init
	 * \brief Initializes the queue - size must contain desired value.
	 * This function initializes the queue and checks the desired size.
	 * In case of errors, the size is set to 0.
	 * \param q a pointer to the structure with the member \e size set accordingly.
	 */
	if (q->size <= 0) {
#ifdef DEVMODE
		error(1, EDOM, "size of queue is not positive!");
#endif
		q->size = 0;
	}
	q->posOut = 0;
	q->count = 0;
	if (q->size > 0)
	q->buffer = (int *) calloc(q->size, sizeof(int));
	else
		q->buffer = NULL;
	if (q->buffer == NULL) {
#ifdef DEVMODE
		error(1, ENOBUFS, "no buffer for queue allocated");
#endif
		q->size = 0; // queue will be full from start
	}
}


bool is_empty(queue_t* q) {
	/**
	 * \fn is_empty
	 * \brief test if queue is empty
	 * \return true if the queue is empty
	 * \param q an initialized queue
	 */
	return q->count <= 0;
}

int enqueue(queue_t* q, int val) {
	/**
	 * \fn enqueue
	 * \brief Puts a new entry into this fifo-like queue.
	 * \param q a pointer to an initialized queue
	 * \param val the integer to be stored
	 * \return QUEUE_IS_FULL when there is no more space
	 */
	if (q->count >= q->size)
		return QUEUE_IS_FULL;
	// coming here means q was initialized and got a buffer
	// some say that % isn't fast enough
	// int posIn=(q->posOut+q->count+1) % q->size;
	int posIn = q->posOut + q->count;
	if (posIn >= q->size)
		posIn -= q->size;
	//
	q->buffer[posIn] = val;
	++q->count;
	return QUEUE_NO_ERROR;
}

int dequeue(queue_t* q, int* val) {
	/**
	 * \fn dequeue
	 * \brief Pops a earliest entry from the fifo-like queue
	 * \param q a pointer to an initialized queue
	 * \param val pointer to where the retrieved value is stored at
	 * \return QUEUE_IS_EMPTY when trying to fetch from an empty queue
	 */
	if (q->count <= 0)
		return QUEUE_IS_EMPTY;
	--q->count;
	*val = q->buffer[q->posOut];
	if (++q->posOut >= q->size)
		q->posOut = 0;
	return QUEUE_NO_ERROR;
}
