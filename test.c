#include <stdio.h>
#include <stdbool.h>

bool verify_subgrid(int sudoku[9][9], int row_start, int col_start) {
    // Create an array to store the values in the subgrid
    int subgrid[9] = {0};

    // Loop over the cells in the subgrid
    for (int i = row_start; i < row_start + 3; i++) {
        for (int j = col_start; j < col_start + 3; j++) {
            // Check if the cell value is already in the array
            int cell_value = sudoku[i][j];
            if (subgrid[cell_value-1]) {
                return false;
            } else {
                subgrid[cell_value-1] = 1;
            }
        }
    }

    // If we get to the end of the loop without returning false, the subgrid is valid
    return true;
}