#include <stdio.h>
#include <stdlib.h>

void create_output_file(int message){
    FILE *file;
    file = fopen("sudoku_laaan.out", "w");
    
    if (message == 0) fputs("SUCCESS", file);
    else fputs("FAIL", file);
}