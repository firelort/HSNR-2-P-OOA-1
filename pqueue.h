//
// Created by hartings on 19.04.18.
//

#ifndef OOA_PQUEUE_H
#define OOA_PQUEUE_H
static typedef struct pqentry{
    float priority; // Definiert die Priorität eines Eintrages
    char* string;
    int id; //Gibt die Unique ID eines Eintrages an.
    struct pqentry *last;
    struct pqentry *next;
}pqentry_t;

typedef struct priorityqueue{
    int size;


}priorityqueue_t;



priorityqueue_t* pqueue_create() {

}
void pqueue_insert(priorityqueue_t *priorityqueue, char* value, float priority);
char* pqueue_extractMin(priorityqueue_t *priorityqueue);
void pqueue_decreaseKey(priorityqueue_t *priorityqueue, char* value, float priority);
void pqueue_remove(priorityqueue_t *priorityqueue, char* value);
void pqueue_destroy(priorityqueue_t *priorityqueue);

#endif //OOA_PQUEUE_H
