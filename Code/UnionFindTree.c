#include "UnionFind.h"
#include <stdbool.h>
#include <MacTypes.h>
#include <stdlib.h>


typedef struct node_t Node;

struct node_t {
    int key;
    int rang;
    Node *parent;
};

struct union_find_t{
    Node vector[];
    size_t size;
};


UnionFind *ufCreate(size_t n_items){
    UnionFind *unionFind = malloc(sizeof(*unionFind));

    Node *vector = malloc(n_items * sizeof(int));

    for(int i = 0; i < n_items; i++){
        vector[i].key = i;
        vector[i].parent = NULL;
        vector[i].rang = 1;
    }

    unionFind->vector = vector;
    unionFind->size = n_items;

    return unionFind;

}

void ufFree(UnionFind *union_find){
    for(int i = 0; i < union_find->size; i++){
        free(&union_find->vector[i]);
    }
    free(union_find->vector);
    free(union_find);
}


ufStatus ufUnion(UnionFind *union_find, size_t item1, size_t item2){
    return NULL;
}


size_t ufFind(const UnionFind *union_find, size_t item){
    return 0;
}

size_t ufComponentsCount(const UnionFind *union_find){
    return 0;
}

