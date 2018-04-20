//
// Created by hartings on 19.04.18.
//

#ifndef OOA_PQUEUE_H
#define OOA_PQUEUE_H

typedef struct priorityqueue priorityqueue_t;

priorityqueue_t* pqueueCreate();
void pqueueInsert(priorityqueue_t *priorityqueue, char* value, float priority);
char* pqueueExtractMin(priorityqueue_t *priorityqueue);
void pqueueDecreaseKey(priorityqueue_t *priorityqueue, char* value, float priority);
void pqueueRemove(priorityqueue_t *priorityqueue, char* value);
void pqueueDestroy(priorityqueue_t *priorityqueue);

#endif //OOA_PQUEUE_H
