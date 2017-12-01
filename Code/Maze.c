#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "Maze.h"
#include "UnionFind.h"

typedef struct neighbour_t Neighbour;

struct maze_t {
    size_t size;
    Coord **coord;
    Neighbour **neighbours;

};


struct neighbour_t {
    size_t cell1;
    size_t cell2;
    bool wall;
};

static void getNeighbours(size_t *tab, size_t x, size_t size) {
    if (x > size)
        tab[0] = x + size;
    if (x < (size * size) - size)
        tab[1] = x - size;
    if (x % size != 0)
        tab[2] = x - 1;
    if (x - 1 % size != 0)
        tab[3] = x + 1;
}


static void setNeighbours(Neighbour **neighbours, size_t size) {
    int count = 0;
    for (size_t i = 0; i < (size * size); i++) {
        if ((i + size) < (size * size)) {
            neighbours[count] = malloc(sizeof(Neighbour));
            neighbours[count]->cell1 = i;
            neighbours[count]->cell2 = i + size;
            neighbours[count]->wall = true;
            count++;
        }
        if ((i + 1) % size != 0) {
            neighbours[count] = malloc(sizeof(Neighbour));
            neighbours[count]->cell1 = i;
            neighbours[count]->cell2 = i + 1;
            neighbours[count]->wall = true;
            count++;
        }
    }
}


Maze *mzCreate(size_t size) {
    size_t vecSize = size * size;
    srand(time(NULL));
    Maze *maze = malloc(sizeof(Maze));
    maze->size = size;
    maze->coord = malloc(vecSize * sizeof(Coord));
    maze->neighbours = malloc(size * (size - 1) * 2 * sizeof(Neighbour));
    setNeighbours(maze->neighbours, size);
    for (size_t i = 0; i < (maze->size * (maze->size - 1) * 2); ++i) {
        printf("%zu,%zu ", maze->neighbours[i]->cell1, maze->neighbours[i]->cell2);
    }

    int t = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            maze->coord[t] = malloc(sizeof(Coord));
            maze->coord[t]->row = i;
            maze->coord[t]->col = j;
            t++;
        }
    }
    UnionFind *unionFind = ufCreate(vecSize);
    ufPrint(unionFind);
    size_t rand1;
    while (ufComponentsCount(unionFind) != 1) {
        rand1 = rand() % (size * (size - 1) * 2);
        if (maze->neighbours[rand1]->wall == true) {
            ufUnion(unionFind, maze->neighbours[rand1]->cell1, maze->neighbours[rand1]->cell2);
            maze->neighbours[rand1]->wall = false;
        }
    }
    ufPrint(unionFind);
    ufFree(unionFind);
    return maze;
}


void mzFree(Maze *maze) {
    for (size_t i = 0; i < (maze->size * maze->size); ++i) {
        free(maze->coord[i]);
    }
    for (size_t i = 0; i < (maze->size * (maze->size - 1) * 2); ++i) {
        free(maze->neighbours[i]);
    }
    free(maze->neighbours);
    free(maze->coord);
    free(maze);
}
