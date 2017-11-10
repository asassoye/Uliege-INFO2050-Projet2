/* ------------------------------------------------------------------------- *\
 * NOM
 *      maze
 * SYNOPSIS
 *      maze [-s size] [-r random_seed] [-f file]
 * DESCRIPTION
 *      Build a random maze
 *      -s size     The size of the maze (the number of cells on a
 *                  side of the maze). Default: 10.
 *      -r          The random seed. If not provided, the generator will be set
 *                  by the current time.
 *      -f          The file in which to print the maze. If not provided, the
 *                  maze will be printed on stdstream.
 \* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Maze.h"


/* ------------------------------------------------------------------------- *
 * Close the file pointer $file$.
 *
 * PARAMETERS
 * file         A file pointer
 *
 * NOTE
 * if the file pointer is stdout or stderr, nothing happens
 *
 * RETURN
 * code         0 in case of success.
 * ------------------------------------------------------------------------- */

 static inline int closeFile(FILE* file)
 {
    if(file != NULL && file != stdout && file !=stderr)
        return fclose(file);
    return 0;
 }




int main(int argc, char** argv)
{
    //--------------------------- PARSE COMMAND LINE -------------------------
    unsigned seed = (unsigned) time(NULL);
    FILE* stream = stdout;
    char* fpath = NULL;
    size_t size = 10;
    int argi = 1; // Ideally this should be a size_t (historical reasons)
    while(argi < argc)
    {
        if(strcmp(argv[argi], "-s") == 0)
        {
            size_t inputSize;
            if(sscanf (argv[++argi], "%zu", &inputSize) != 1)
            {
                fprintf(stderr, "%s\n", "Aborting; size should be an unsigned "
                                        "integer.");
                exit(EXIT_FAILURE);
            }
            size = inputSize;
        } else if(strcmp(argv[argi], "-r") == 0) {
            unsigned inputSeed;
            if(sscanf (argv[++argi], "%u", &inputSeed) != 1)
            {
                fprintf(stderr, "%s\n", "Aborting; the random seed should be an "
                                        "unsigned integer.");
                exit(EXIT_FAILURE);
            }
            seed = inputSeed;
        } else if(strcmp(argv[argi], "-f") == 0) {
            fpath = argv[++argi];
        } else {
            fprintf(stderr, "%s '%s'\n", "Aborting; unknown parameter",
                    argv[argi]);
            fprintf(stderr, "%s %s %s\n", "Usage:", argv[0], "[-s size] "
                    "[-r random_seed] [-f file]");
            exit(EXIT_FAILURE);
        }
        argi++;
    }

    //---------------------------- INITIATE PROGRAM --------------------------
    if(fpath != NULL)
    {
        stream = fopen(fpath, "w");
        if(!stream)
        {
            fprintf(stderr, "%s '%s'\n", "Could not open the file", fpath);
            exit(EXIT_FAILURE);
       }
    }
    srand(seed);

    //------------------------ BUILD MAZE AND PRINT IT -----------------------

    Maze* maze = mzCreate(size);
    if(!maze)
    {
        fprintf(stderr, "%s\n", "Error while creating the maze.");
        closeFile(stream);
        exit(EXIT_FAILURE);
    }

    mzPrint((const Maze*)maze, stream);

    //----------------------- TERMINATE THE PROGRAM NICELY -------------------
    mzFree(maze);
    closeFile(stream);
    exit(EXIT_SUCCESS);
}
