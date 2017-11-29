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


UnionFind *ufCreate(size_t n_items){
    UnionFind *unionFind = malloc(sizeof(*unionFind));
    cell *current = malloc(sizeof(cell));
    unionFind->head = current;
    for (size_t i = 0; i < n_items; ++i) {
        current->key = (int) i;
        current->set = unionFind;
        printf("%d ",current->key); //test

        if (i < n_items - 1) {
            current = current->next;
            current = malloc(sizeof(cell));
        }
    }
    unionFind->tail = current;

    //tests
    current = unionFind->head;
    printf("\nHead : %d ",current->key);
    current = unionFind->tail;
    printf("Tail : %d \n",current->key);
    
    return unionFind;
}


