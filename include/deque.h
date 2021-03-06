#ifndef SNAKE_H_DEQUE
#define SNAKE_H_DEQUE

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int y, x;
} data;

struct _deqnode;
typedef struct _deqnode *dnptr;

typedef struct _deqnode
{
    data *d;
    dnptr next;
} deqnode;

typedef struct
{
    dnptr head;
    dnptr tail;
} deque;

deque *initDeque(void)
{
    deque *ret = malloc(sizeof(deque));
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

void prepend(deque *dq, data d)
{
    dnptr new = malloc(sizeof(deqnode));
    new->d = malloc(sizeof(data));
    new->d->y = d.y;
    new->d->x = d.x;
    
    new->next = dq->head;
    if (!(dq->head))
    {
	dq->tail = new;
    }
    dq->head = new;    
}

void append(deque *dq, data d)
{
    dnptr new = malloc(sizeof(deqnode));
    new->d = malloc(sizeof(data));
    new->d->y = d.y;
    new->d->x = d.x;
    new->next = NULL;
    
    if (dq->tail)
    {
	(dq->tail)->next = new;
    }
    else
    {
	dq->head = new;
    }

    dq->tail = new;
}

data *popHead(deque *dq)
{
    if (!(dq->head)) return NULL;

    data *ret = malloc(sizeof(data));

    ret->y = dq->head->d->y;
    ret->x = dq->head->d->x;

    free(dq->head->d);
    dnptr newhead = dq->head->next;
    free(dq->head);
    dq->head = newhead;
    if (!(dq->head)) dq->tail = dq->head;

    return ret;
}

data *popTail(deque *dq)
{
    if (!(dq->tail)) return NULL;

    data *ret = malloc(sizeof(data));

    ret->y = dq->tail->d->y;
    ret->x = dq->tail->d->x;

    free(dq->tail->d);
    dnptr newtail = dq->head;
    while(newtail && newtail->next != dq->tail)
	newtail = newtail->next;

    free(dq->tail);
    dq->tail = newtail;
    if (dq->tail) dq->tail->next = NULL;

    return ret;
}

void printDeqPtr(deque dq)
{
    printf("deq head: %p, tail: %p\n", dq.head, dq.tail);
    for (dnptr node = dq.head; node; node = node->next)
    {
	printf("{%u %u}, %p %p\n",node->d->y, node->d->x, node, node->next);
    }
}

void killDeque(deque *dq)
{
    data *dp;
    while (dp = popHead(dq)) free(dp);
    free(dq);
}
#endif
