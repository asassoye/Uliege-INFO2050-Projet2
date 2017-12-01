#include <stdlib.h>
#include "UnionFind.h"


typedef struct node_t Node;

struct node_t {
    size_t key;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
};

struct union_find_t {
    Node **vector;
    size_t size;
};


UnionFind *ufCreate(size_t n_items) {
    UnionFind *unionFind = malloc(sizeof(*unionFind));

    Node **vector = malloc(n_items * sizeof(Node *));

    Node *actual = NULL;

    for (unsigned int i = 0; i < n_items; i++) {
        actual = malloc(sizeof(Node));

        actual->key = i;
        actual->parent = NULL;
        actual->rightChild = NULL;
        actual->leftChild = NULL;

        vector[i] = actual;
    }

    unionFind->vector = vector;
    unionFind->size = n_items;

    return unionFind;

}

void ufFree(UnionFind *union_find) {
    for (unsigned int i = 0; i < union_find->size; i++) {
        free(union_find->vector[i]);
    }
    free(union_find->vector);
    free(union_find);
}


ufStatus ufUnion(UnionFind *union_find, size_t item1, size_t item2) {
    if (item1 > union_find->size || item2 > union_find->size) {
        return UF_ERROR;
    }

    Node *element1 = union_find->vector[ufFind(union_find, item1)];
    Node *element2 = union_find->vector[ufFind(union_find, item2)];

    if (element1 == element2) {
        return UF_SAME;
    }

    Node *y = NULL;
    Node *x = element1;
    Node *z = element2;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->leftChild;
        } else {
            x = x->rightChild;
        }
    }
    z->parent = y;

    if (y == NULL) {
        *element1 = *z;
    } else if (z->key < y->key) {
        y->leftChild = z;
    } else {
        y->rightChild = z;
    }

    return UF_MERGED;

}


size_t ufFind(const UnionFind *union_find, size_t item) {
    Node *element = union_find->vector[item];

    while (element->parent != NULL) {
        element = element->parent;
    }

    return element->key;
}

size_t ufComponentsCount(const UnionFind *union_find) {
    Node **vector = union_find->vector;

    size_t count = 0;

    for (unsigned int i = 0; i < union_find->size; i++) {
        if (vector[i]->parent == NULL) {
            count++;
        }
    }

    return count;

}
