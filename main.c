#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pqueue.h"

#define MAX 1000

char* randomString(int size) {
    char *str = (char *) malloc((size + 1)*sizeof(char));
    for (int i = 0; i < size; i++) {
        str[i] = (rand() % 26) + 'A';
    }
    str[size] = '\0';
}

int main() {
    int i;
    char *strings[MAX];
    clock_t tic, toc;

    srand(time(NULL));
    printf("DEBUG\n");
    for (i = 0; i < MAX; i++) {
        strings[i] = randomString(8);
    }
    printf("DEBUG 1.1\n");
    priorityqueue_t *pq = pqueueCreate();
    tic = clock();
    for (int i = 0; i < MAX; i++) {
        pqueueInsert(pq, strings[i], rand() % 100);
    }
    toc = clock();

    printf("Insertion time: %.2f\n",(float)(tic-toc)/CLOCKS_PER_SEC);

    tic = clock();
    for (i = 0; i < MAX; i++) {
        pqueueExtractMin(pq);
    }
    toc = clock();

    printf("Extract time: %2.f\n", (float)(tic-toc) / CLOCKS_PER_SEC);

    for (i = 0; i < MAX; i++) {
        free(strings[i]);
    }
    pqueueDestroy(pq);
    return 0;
}