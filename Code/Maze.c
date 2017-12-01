#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "Maze.h"
#include "UnionFind.h"

struct maze_t {
    size_t size;
    Coord **coord;
};


static bool isNeighbour(size_t size, size_t cell1, size_t cell2) {
    if ((cell2 == cell1 + 1 && cell2 % size + 1 != size) ||
        (cell2 == cell1 - 1 || cell2 == cell1 - size
         || cell2 == cell1 + size))
        return true;
    return false;
}


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


Maze *mzCreate(size_t size) {
    size_t vecSize = size * size;
    srand(time(NULL));
    Maze *maze = malloc(sizeof(Maze));
    maze->size = size;
    maze->coord = malloc(vecSize * sizeof(Coord));
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
    size_t rand1;
    size_t rand2 = INT_MAX;
    size_t tab[4] = {INT_MAX};
    while (ufComponentsCount(unionFind) != 1) {
        rand1 = rand() % (size * size);
        getNeighbours(tab, rand1, size);
        while (rand2 == INT_MAX)
            rand2 = tab[rand() % (4)];
        //mzSetWall(maze,maze->coord[rand1], maze->coord[rand2], false);
        ufUnion(unionFind, rand1, rand2);
    }
    ufFree(unionFind);
    return maze;
}


void mzFree(Maze *maze) {
    for (size_t i = 0; i < (maze->size * maze->size); ++i) {
        free(maze->coord[i]);
    }
    free(maze->coord);
    free(maze);
}
