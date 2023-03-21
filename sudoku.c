#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "utils.c"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("invalid number of parameters\n");
        exit(1);
    }

    char *filename = argv[1];
    int **grid_sudoku = getSudoku(filename);
    if (grid_sudoku == NULL)
    {
        printf("Error to read file");
        exit(1);
    }

    int gridLength = getGridLength(filename);
    getSubgridLength(filename, gridLength);
    verifyVeracity(gridLength, grid_sudoku);

    return 0;
}
