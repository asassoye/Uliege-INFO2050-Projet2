#include <stdlib.h>
#include "UnionFind.h"
#include <assert.h>


typedef struct cell_t Cell;
typedef struct set_t Set;
typedef struct node_t Node;

static void setFree(Set *set);

struct cell_t {
    size_t key;
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

        printf("%zu", current_node->set->head->key);

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

void ufFree(UnionFind *union_find) {
    Node *actual = union_find->first;

    Node *next = actual->next;

    while (next != NULL) {
        setFree(actual->set);
        free(actual);
        actual = next;
        next = actual->next;
    }

    setFree(actual->set);
    free(actual);

    free(union_find);

}

static void setFree(Set *set) {
    assert(set != NULL);

    Cell *actual = set->head;

    Cell *next = actual->next;

    while (set->size > 1) {
        free(actual);
        actual = next;

        next = actual->next;

        set->size--;
    }

    free(actual);
    free(set);
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

//temporary function to print uf
void ufPrint(UnionFind *unionFind) {
    Node *node = unionFind->first;
    Cell *cell;
    while (node != NULL) {
        printf("(");
        cell = node->set->head;
        while (cell != NULL) {
            printf("%zu", cell->key);
            cell = cell->next;
        }
        printf(")");
        node = node->next;
    }
    printf("\n");
}