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
    size_t **convert;

};


struct neighbour_t {
    size_t cell1;
    size_t cell2;
    bool wall;
};


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
    maze->convert = malloc(size * sizeof(size_t));

    size_t count = 0;
    for (int i = 0; i < size; ++i) {
        maze->convert[i] = malloc(size * sizeof(size_t));
        for (int j = 0; j < size; ++j) {
            maze->convert[i][j] = count;
            count++;
        }
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

            if (ufUnion(unionFind, maze->neighbours[rand1]->cell1, maze->neighbours[rand1]->cell2)
                == UF_MERGED)
                maze->neighbours[rand1]->wall = false;
        }
    }
    ufPrint(unionFind);
    ufFree(unionFind);
    FILE *stream = fopen("test.txt", "w");
    if (stream != NULL)
        mzPrint(maze, stream);
    fclose(stream);
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

bool mzIsWallClosed(const Maze *maze, Coord cell1, Coord cell2) {
    size_t coord1 = maze->convert[cell1.row][cell1.col];
    size_t coord2 = maze->convert[cell2.row][cell2.col];
    for (int i = 0; i < (maze->size * (maze->size - 1) * 2); ++i) {
        if ((maze->neighbours[i]->cell1 == coord1 && maze->neighbours[i]->cell2 == coord2) ||
            (maze->neighbours[i]->cell1 == coord2 && maze->neighbours[i]->cell2 == coord1)) {
            return maze->neighbours[i]->wall;
        }
    }
    return true;
}

void mzPrint(const Maze *maze, FILE *out) {
    Coord coord1;
    Coord coord2;
    fprintf(out, "+");
    for (int i = 0; i < maze->size; ++i) {
        fprintf(out, "--+");
    }
    fprintf(out, "\n");
    for (size_t i = 0; i < maze->size; ++i) {
        if (i == 0)
            fprintf(out, " ");
        else
            fprintf(out, "|");
        coord1.row = i;
        for (size_t j = 0; j < maze->size - 1; ++j) {
            coord1.col = j;
            coord2.row = i;
            coord2.col = j + 1;
            fprintf(out, "  ");
            if (!mzIsWallClosed(maze, coord1, coord2))
                fprintf(out, " ");
            else
                fprintf(out, "|");
        }
        fprintf(out, "  ");
        if (i == maze->size - 1)
            fprintf(out, " ");
        else
            fprintf(out, "|");
        fprintf(out, "\n+");
        for (size_t j = 0; j < maze->size; ++j) {
            coord1.col = j;
            coord2.row = i + 1;
            coord2.col = j;
            if (coord2.row < maze->size && !mzIsWallClosed(maze, coord1, coord2))
                fprintf(out, "  ");
            else
                fprintf(out, "--");
            fprintf(out, "+");
        }
        fprintf(out, "\n");
    }
}
