//
// Copied from the template and slightly added. Version 1.0
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pqueue.h"

#define MAX 1000
#define TestC 10

char* randomString(int size) {
    char *str = (char *) malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; i++) {
        str[i] = (char) ((rand() % 26) + 'A');
    }
    str[size] = '\0';
    return str;
}

void testFunction() {
    int i;
    srand(time(NULL));
    priorityqueue_t *pqTest, *pq = pqueueCreate();
    // Test 1: Kein Element in der Wartschlange
    pqueueExtractMin(pq);
    // Test 2: Element removen was nicht vorhanden ist.
    pqueueRemove(pq, "Hello");
    // Test 3:
    pqueueDecreaseKey(pq, "Hello", 20);
    // Test 4:
    pqueueDestroy(pqTest);

}

int main() {
    testFunction();
    int i;
    char *strings[MAX];
    clock_t tic, toc;

    srand(time(NULL));
    for (i = 0; i < MAX; i++) {
        strings[i] = randomString(8);
    }
    priorityqueue_t *pq = pqueueCreate();
    tic = clock();
    for (i = 0; i < MAX; i++) {
        pqueueInsert(pq, strings[i], rand() % 100);
    }
    toc = clock();

    printf("Insertion time: %.10f\n",(float)(toc-tic)/CLOCKS_PER_SEC);
    printf("Debugger: Tic: %f - Toc: %f\n", (float) tic / CLOCKS_PER_SEC, (float) toc / CLOCKS_PER_SEC); //Added for debugging reasons

    tic = clock();
    for (i = 0; i < MAX; i++) {
        pqueueExtractMin(pq);
    }
    toc = clock();

    printf("Extract time: %.10f\n", (float)(toc-tic) / CLOCKS_PER_SEC);
    printf("Debugger: Tic: %f - Toc: %f\n", (float) tic / CLOCKS_PER_SEC, (float) toc / CLOCKS_PER_SEC); //Added for debugging reasons
    pqueueDestroy(pq);
    for (i = 0; i < MAX; i++) {
        free(strings[i]);
    }

    return 0;
}