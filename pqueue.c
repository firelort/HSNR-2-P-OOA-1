//
// Created by hartings on 19.04.18.
// TODO: Error Codes überprüfen und Kommentare schreiben
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "pqueue.h"

typedef struct pqentry{
    float priority; // Definiert die Priorität eines Eintrages
    char* string;
    int id; //Gibt die Unique ID eines Eintrages an.
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
    if (!pqueue) {
        printf("Error 1: Program couldn't allocate memory for priority queue.");
    }
    pqueue->idCounter = 0;
    pqueue->size = 0;
    pqueue->tail = NULL;
    pqueue->head = NULL;
    printf("DEBUGGER 2.1\n");
    return pqueue;
}
void pqueueInsert(priorityqueue_t *priorityqueue, char* value, float priority) {
    pqentry_t *newElement = (pqentry_t *) malloc(sizeof(pqentry_t));
    pqentry_t *tempElement, *tempSElement;
    if (!newElement) {
        printf("Error 2: Program couldn't allocate memory for a new entry.");
        return;
    }
    newElement->string = value;
    newElement->priority = priority;
    newElement->id = priorityqueue->idCounter;
    printf("SPAM\n");

    if (priorityqueue->size == 0) { // QUEUE ist leer
        priorityqueue->head = newElement;
        priorityqueue->tail = newElement;
        newElement->next = NULL;
        newElement->prev = NULL;
    } else if (priority <= priorityqueue->head->priority) { // Erstes Element
        newElement->next = priorityqueue->head;
        newElement->prev = NULL;
        priorityqueue->head->prev = newElement;
        priorityqueue->head = newElement;
    } else if(priorityqueue->tail->priority <= priority) { // Letztes Element
        newElement->next = NULL;
        newElement->prev = priorityqueue->tail;
        priorityqueue->tail->next = newElement;
        priorityqueue->tail = newElement;
    } else {
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

char* pqueueExtractMin(priorityqueue_t *priorityqueue) { //TODO: Error Ausgabe, sowie überprüfen ob richtig abgefangen.
    char *rtrnValue;
    if(priorityqueue->size) {
        rtrnValue = priorityqueue->head->string;
    } else {
        printf("PQ no entry. or wrong PQ");
        rtrnValue = "Error";
    }
    return rtrnValue;
}

void pqueueRemove(priorityqueue_t *priorityqueue, char* value) {//TODO: Fehlermeldung
    if (priorityqueue->size == 0) {
        printf("Error: X Warteschlange leer");
        return;
    } else if (priorityqueue->size == 1) {
        if(!strcmp(priorityqueue->head->string, value)) { // Wenn Strings gleich sind kommt 0 raus also mit !
            free(priorityqueue->head);
            priorityqueue->size = 0;
            priorityqueue->head = NULL;
            priorityqueue->tail = NULL;
        } else {
            printf("Error: Angegebnes Value nicht gefunden.");
        }
        return;
    }
    if (!strcmp(priorityqueue->head->string,value)) {
        priorityqueue->head = priorityqueue->head->next;
        free(priorityqueue->head->prev);
        priorityqueue->head->prev = NULL;
    } else if (!strcmp(priorityqueue->tail->string,value)) {
        priorityqueue->tail = priorityqueue->tail->prev;
        free(priorityqueue->tail->next);
        priorityqueue->tail->next = NULL;
    } else {
        pqentry_t *tempEntry = priorityqueue->head;
        while (strcmp(tempEntry->string, value) != 0) {
            tempEntry = tempEntry->next;
        }
        tempEntry->prev->next = tempEntry->next;
        tempEntry->next->prev = tempEntry->prev;
    }
    priorityqueue->size -= 1;
}

void pqueueDecreaseKey(priorityqueue_t *priorityqueue, char* value, float priority) {
    pqueueRemove(priorityqueue, value);
    pqueueInsert(priorityqueue, value, priority);
}

void pqueueDestroy(priorityqueue_t *priorityqueue) {
    pqentry_t *tempEntry = priorityqueue->head;
    while (tempEntry->next != NULL) {
        priorityqueue->head = tempEntry->next;
        free(tempEntry);
        tempEntry = priorityqueue->head;
    }
    free(tempEntry);
    free(priorityqueue);
}