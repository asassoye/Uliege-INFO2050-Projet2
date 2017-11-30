#include <stdlib.h>
#include "UnionFind.h"


typedef struct cell_t Cell;
typedef struct set_t Set;
typedef struct node_t Node;

static void setFree(Set *set);

struct cell_t {
    int key;
    Cell *next;
    Set *set;
};

struct set_t {
    Cell *head;
    Cell *tail;
    size_t size;
};

struct node_t {
    Set *set;
    Node *next;
};

struct union_find_t {
    Node *first;
    Node *last;
};


UnionFind *ufCreate(size_t n_items) {
    UnionFind *unionFind = malloc(sizeof(*unionFind));
    Set *current_set = malloc(sizeof(*current_set));;
    Cell *current_cel;
    Node *current_node = malloc(sizeof(*current_node));;
    unionFind->first = current_node;
    for (size_t i = 0; i < n_items; ++i) {

        current_cel = malloc(sizeof(*current_cel));
        current_cel->key = (int) i;
        current_cel->set = current_set;
        current_cel->next = NULL;

        current_set->head = current_cel;
        current_set->tail = current_cel;
        current_set->size = 1;

        current_node->set = current_set;

        printf("%d", current_node->set->head->key);

        if (i < n_items - 1) {
            current_node->next = malloc(sizeof(*current_node));
            current_node = current_node->next;
            current_set = current_node->set;
            current_set = malloc(sizeof(*current_set));
            current_cel = current_set->head;
        }
    }
    unionFind->last = current_node;
    current_node->next = NULL;

    return unionFind;
}


size_t ufComponentsCount(const UnionFind *union_find) {
    Node *node = union_find->first;
    size_t count = 0;
    while (node != NULL) {
        count += node->set->size;
        node = node->next;
    }
    return count;
}

void ufFree(UnionFind *union_find){
    Node *actual = union_find->first;

    Node *next = actual->next;

    while(next != NULL){
        setFree(actual->set);
        actual = next;
        next = actual->next;
    }

    setFree(actual->set);

    free(union_find);

}

static void setFree(Set *set){
    Cell *actual = set->head;

    Cell *next = actual->next;

    while(set->size > 0){
        free(actual);
        actual = next;
        next = actual->next;
        set->size--;
    }

    set->head = NULL;
    set->tail = NULL;
}
