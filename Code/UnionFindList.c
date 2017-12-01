#include <stdlib.h>
#include "UnionFind.h"


typedef struct cell_t Cell;
typedef struct set_t Set;
typedef struct node_t Node;


struct union_find_t {
    Node *first;
};

struct node_t {
    Set *set;
    Node *next;
};

struct set_t {
    Cell *head;
    Cell *tail;
    size_t size;
};

struct cell_t {
    size_t key;
    Cell *next;
    Set *set;
};


UnionFind *ufCreate(size_t n_items) {
    UnionFind *unionFind = malloc(sizeof(*unionFind));
    Set *current_set;
    Cell *current_cel;
    Node *current_node;
    unionFind->first = malloc(sizeof(*current_node));;
    current_node = unionFind->first;
    current_node->set = malloc(sizeof(*current_set));
    current_set = current_node->set;
    current_set->head = malloc(sizeof(*current_cel));
    current_cel = current_set->head;

    for (size_t i = 0; i < n_items; ++i) {
        current_cel->key = (int) i;
        current_cel->set = current_set;
        current_cel->next = NULL;

        current_set->tail = current_cel;
        current_set->size = 1;

        current_node->next = NULL;

        if (i < n_items - 1) {
            current_node->next = malloc(sizeof(*current_node));
            current_node = current_node->next;
            current_node->set = malloc(sizeof(*current_set));

            current_set = current_node->set;
            current_set->head = malloc(sizeof(*current_cel));

            current_cel = current_set->head;
        }
    }
    return unionFind;
}


void ufFree(UnionFind *union_find) {
    Node *node = union_find->first;
    Node *next_node;
    Set *set;
    Cell *cell;
    Cell *next_cell;
    while (node != NULL) {
        set = node->set;
        cell = set->head;

        while (cell != NULL) {
            next_cell = cell->next;
            free(cell);
            cell = next_cell;
        }
        free(set);
        next_node = node->next;
        free(node);
        node = next_node;
    }
    free(union_find);
}


static ufStatus Union(UnionFind *unionFind, Set *set1, Set *set2) {
    Cell *tmp;
    set1->size += set2->size; //update the size of the set

    //update the tail and head pointers
    tmp = set1->tail;
    set1->tail = set2->tail;
    tmp->next = set2->head;

    //update the set pointer in each element of the second set
    tmp = set2->head;
    while (tmp != NULL) {
        tmp->set = set1;
        tmp = tmp->next;
    }

    //update the linked list of sets
    Node *node = unionFind->first;
    Node *prev = node;
    while (node != NULL) {
        if (node->set == set2) {
            if (node == unionFind->first) {
                unionFind->first = node->next;
            } else {
                prev->next = node->next;
            }
            free(set2);
            free(node);
            return UF_MERGED;
        }
        prev = node;
        node = node->next;
    }
    return UF_ERROR;
}


ufStatus ufUnion(UnionFind *union_find, size_t item1, size_t item2) {
    size_t it1 = ufFind(union_find, item1);
    size_t it2 = ufFind(union_find, item2);
    if (it1 == it2)
        return UF_SAME;
    Set *set1 = NULL;
    Set *set2 = NULL;
    Node *node = union_find->first;
    while (node != NULL) {
        if (node->set->head->key == it1) {
            set1 = node->set;
        }
        if (node->set->head->key == it2) {
            set2 = node->set;
        }
        if (set1 != NULL && set2 != NULL)
            break;
        node = node->next;
    }
    if (set1 == NULL || set2 == NULL)
        return UF_ERROR;

    //concatenate the two sets, puts the smaller one after the bigger one to reduce cost
    if (set1->size >= set2->size)
        return Union(union_find, set1, set2);
    else
        return Union(union_find, set2, set1);
}


size_t ufFind(const UnionFind *union_find, size_t item) {
    Node *node = union_find->first;
    Set *set;
    Cell *cell;
    while (node != NULL) {
        set = node->set;
        cell = set->head;
        while (cell != NULL) {
            if (cell->key == item)
                return cell->set->head->key;
            cell = cell->next;
        }
        node = node->next;
    }
    return (size_t) -1;
}


size_t ufComponentsCount(const UnionFind *union_find) {
    Node *node = union_find->first;
    size_t count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}
