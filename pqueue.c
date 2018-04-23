//
// Created by Robert Hartings and Lars .... . Version 1.0
//
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "pqueue.h"

typedef struct pqentry{
    float priority;
    char* string;
    int id; //Unique ID for an entry.
    struct pqentry *prev;
    struct pqentry *next;
}pqentry_t;

typedef struct priorityqueue{
    int size;
    int idCounter;
    pqentry_t *head;
    pqentry_t *tail;
}priorityqueue_t;

priorityqueue_t *pqueueCreate() {
    priorityqueue_t *pqueue = (priorityqueue_t *) malloc(sizeof(priorityqueue_t));
    if (pqueue == NULL) {
        printf("Error 1: Program couldn't allocate memory for priority queue.\n");
    } else {
        pqueue->idCounter = 0;
        pqueue->size = 0;
        pqueue->tail = NULL;
        pqueue->head = NULL;
    }
    return pqueue;
}
void pqueueInsert(priorityqueue_t *priorityqueue, char* value, float priority) {
    pqentry_t *newElement = (pqentry_t *) malloc(sizeof(pqentry_t));
    pqentry_t *tempElement;
    if (!newElement) {
        printf("Error 2: Program couldn't allocate memory for a new entry.\n");
        return;
    }
    newElement->string = value;
    newElement->priority = priority;
    newElement->id = priorityqueue->idCounter;

    if (priorityqueue->size == 0) { // New element is the first and last element in the empty queue
        priorityqueue->head = newElement;
        priorityqueue->tail = newElement;
        newElement->next = NULL;
        newElement->prev = NULL;
    } else if (priority <= priorityqueue->head->priority) { // New element has the highest priority
        newElement->next = priorityqueue->head;
        newElement->prev = NULL;
        priorityqueue->head->prev = newElement;
        priorityqueue->head = newElement;
    } else if(priorityqueue->tail->priority <= priority) { // New element has the lowest priority
        newElement->next = NULL;
        newElement->prev = priorityqueue->tail;
        priorityqueue->tail->next = newElement;
        priorityqueue->tail = newElement;
    } else { // New element is inserted in "the middle"
        tempElement = priorityqueue->head;
        while (tempElement->priority < priority) {
            tempElement = tempElement->next;

        }
        newElement->next = tempElement;
        newElement->prev = tempElement->prev;
        tempElement->prev->next = newElement;
        tempElement->prev = newElement;
    }
    priorityqueue->size += 1;
    priorityqueue->idCounter += 1;
}

char* pqueueExtractMin(priorityqueue_t *priorityqueue) {
    char *rtrnValue;
    if(priorityqueue->size) {
        rtrnValue = priorityqueue->head->string;
    } else {
        printf("Error 3: Priority queue has no entries or wrong priority queue specified.\n");
        rtrnValue = "Error";
    }
    return rtrnValue;
}

void pqueueRemove(priorityqueue_t *priorityqueue, char* value) {
    if (priorityqueue->size == 0) { // Queue is empty
        printf("Error 4: Priority queue is emtpy.\n");
        return;
    } else if (priorityqueue->size == 1) { // Queue only has one element
        if(strcmp(priorityqueue->head->string, value) == 0) { // strcmp returns 0, if both strings are identical
            free(priorityqueue->head);
            priorityqueue->size = 0;
            priorityqueue->head = NULL;
            priorityqueue->tail = NULL;
        } else { // The only element wasn't searched for
            printf("Error 5: Specified value not found.\n");
        }
        return;
    }
    if (strcmp(priorityqueue->head->string,value) == 0) {// The first element was searched for.
        priorityqueue->head = priorityqueue->head->next;
        free(priorityqueue->head->prev);
        priorityqueue->head->prev = NULL;
    } else if (strcmp(priorityqueue->tail->string,value) == 0) {// The last element was searched for.
        priorityqueue->tail = priorityqueue->tail->prev;
        free(priorityqueue->tail->next);
        priorityqueue->tail->next = NULL;
    } else { // T
        pqentry_t *tempEntry = priorityqueue->head;
        while (tempEntry->next != NULL && strcmp(tempEntry->string, value) != 0) {
            tempEntry = tempEntry->next;
        }
        if (tempEntry->next == NULL) {
            printf("Error 6: The element you were looking for wasn't found.\n");
        }
        tempEntry->prev->next = tempEntry->next;
        tempEntry->next->prev = tempEntry->prev;
    }
    priorityqueue->size -= 1;
}

void pqueueDecreaseKey(priorityqueue_t *priorityqueue, char* value, float priority) { //Instead of a shift, the element is deleted and inserted again with the new priority.
    pqueueRemove(priorityqueue, value);
    pqueueInsert(priorityqueue, value, priority);
}

void pqueueDestroy(priorityqueue_t *priorityqueue) {
    if (priorityqueue != NULL) {
        pqentry_t *tempEntry;
        while (priorityqueue->head != NULL) { // Before the queue is deleted, all elements in it are deleted.
            tempEntry = priorityqueue->head->next;
            free(priorityqueue->head);
            priorityqueue->head = tempEntry;
        }
        free(priorityqueue);
    } else {
        printf("Error 7: No queue is specified.\n");
    }
}