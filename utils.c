int subgrid_row;
int subgrid_column;

#include "out.c"
#include "input.c"
#include "processing.c"


FILE *openFile(char *filename);
int getGridLength(char *filename);
void getSubgridLength(char *filename, int n);
int **getSudoku(char *filename);

void *verifyRows(void *arg);
void *verifyColumns(void *arg);
void *verifySubgrid(void *arg);
int verifyVeracity(int grid_length, int **grid);

void create_output_file(int message);