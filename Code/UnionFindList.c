#include <stdlib.h>
#include "UnionFind.h"


typedef struct cell_t cell;

struct cell_t {
    int key;
    cell *next;
    UnionFind *set;
};

struct union_find_t {
    cell *head;
    cell *tail;
};


UnionFind *ufCreate(size_t n_items) {
    UnionFind *unionFind = malloc(sizeof(*unionFind));
    cell *new = malloc(sizeof(cell));;
    cell *current = new;
    unionFind->head = current;
    for (size_t i = 0; i < n_items; ++i) {
        current->key = (int) i;
        current->set = unionFind;
        current->next = NULL;
        printf("%d ", current->key); //test

        if (i < n_items - 1) {
            new = malloc(sizeof(cell));
            current->next = new;
            current = current->next;
        }
    }
    unionFind->tail = current;
    //tests
    current = unionFind->head;
    printf("\nHead : %d ", current->key);
    current = unionFind->tail;
    printf("Tail : %d \n", current->key);

    return unionFind;
}

void ufFree(UnionFind *union_find) {
    cell *current = union_find->head;
    cell *next;
    while (current != NULL) {
        next = current->next;
        printf("bla");
        free(current);
        current = next;
        if (current != NULL)
            next = current->next;
    }
    free(union_find);
}

