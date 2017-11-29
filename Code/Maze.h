/* ========================================================================= *
 * Maze interface:
 * ========================================================================= */

#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdbool.h>
#include <stdio.h>

/* Opaque structure */
typedef struct maze_t Maze;

/* Coordinate structure */
typedef struct coord_t {
    size_t row, col;
} Coord;

/* ------------------------------------------------------------------------- *
 * Create a random square maze.
 *
 * PARAMETERS
 * size         The number of cells on a side of the maze
 *
 * NOTE
 * The returned structure should be cleaned with $mazeFree$ after
 * usage.
 *
 * RETURN
 * maze         The created maze.
 * ------------------------------------------------------------------------- */
Maze* mzCreate(size_t size);

/* ------------------------------------------------------------------------- *
 * Free the memory allocated for the maze structure.
 *
 * PARAMETERS
 * maze         The maze to free
 * ------------------------------------------------------------------------- */
void mzFree(Maze* maze);

/* ------------------------------------------------------------------------- *
 * Return the size of the Maze $maze$. If the size is N, the maze is
 * composed N*N cells.
 *
 * PARAMETERS
 * maze         A maze
 *
 * RETURN
 * size         The size of $maze$
 * ------------------------------------------------------------------------- */
size_t mzSize(const Maze* maze);

/* ------------------------------------------------------------------------- *
 * Check whether a maze wall between two neighbour cells $cell1$ and $cell2$
 * is opened or closed.
 *
 * PARAMETERS
 * maze         The maze
 * cell1        A cell
 * cell2        A neibhoring cell of $cell1$
 *
 * RETURN
 * opened       True if the wall is opened, false otherwise
 * ------------------------------------------------------------------------- */
bool mzIsWallClosed(const Maze *maze, Coord cell1, Coord cell2);


/* ------------------------------------------------------------------------- *
 * Close or open a wall between  two neighbour cells $cell1$ and $cell2$
 *
 * PARAMETERS
 * maze         The maze
 * cell1        A cell
 * cell2        A neighboring celle pf $cell1$
 * ------------------------------------------------------------------------- */
void mzSetWall(Maze* maze, Coord cell1, Coord cell2, bool close);


/* ------------------------------------------------------------------------- *
 * Check whether the Maze $maze$ is valid (in the sense that there is exactly
 * one path between any two pairs of cells)
 *
 * PARAMETERS
 * maze         The Maze to check
 *
 * RETURN
 * isValid      Whether the maze is valid.
 * ------------------------------------------------------------------------- */
bool mzIsValid(const Maze* maze);

/* ------------------------------------------------------------------------- *
 * Print the maze.
 *
 * PARAMETERS
 * maze         The Maze structure
 * out          File descriptor where to write the maze.
 * ------------------------------------------------------------------------- */
void mzPrint(const Maze* maze, FILE* out);

#endif // _MAZE_H_
