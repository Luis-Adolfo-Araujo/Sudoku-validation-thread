#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 12

typedef struct
{
    int grid_length;
    int **grid;
} threads_args;

int checkRepetition(int number, int *grid, int length)
{
    int counter = 0;
    for (int i = 0; i < length; i++)
    {
        if (number == grid[i])
        {
            counter++;
        }
    }
    if (counter > 1)
        return 1;
    else
        return 0;
}

void *verifyRows(void *arg)
{
    threads_args *threads_arg = (threads_args *)arg;
    for (int i = 0; i < threads_arg->grid_length; i++)
    {
        int tmp_array[threads_arg->grid_length];
        for (int j = 0; j < threads_arg->grid_length; j++)
        {
            tmp_array[j] = threads_arg->grid[i][j];
            int v = checkRepetition(threads_arg->grid[i][j], tmp_array, j + 1);
            if (v == 1)
            {
                create_output_file(v);
                exit(1);
            }
        }
    }
    pthread_exit(NULL);
}

void *verifyColumns(void *arg)
{
    threads_args *threads_arg = (threads_args *)arg;
    int j = 0;
    int tmp_array[threads_arg->grid_length];

    for (int i = 0; i < threads_arg->grid_length; i++)
    {
        tmp_array[i] = threads_arg->grid[i][j];
        int v = checkRepetition(threads_arg->grid[i][j], tmp_array, i + 1);
        if (v == 1)
        {
            create_output_file(v);
            exit(1);
        }
        if (i + 1 == threads_arg->grid_length && j + 1 == threads_arg->grid_length)
        {
            break;
        }
        else if (i + 1 == threads_arg->grid_length)
        {
            j++;
            i = -1;
        }
    }
    pthread_exit(NULL);
}

void *verifySubgrid(void *arg)
{
    threads_args *threads_arg = (threads_args *)arg;
    int array_length = subgrid_row * subgrid_column;
    int tmp_array[array_length];
    int row_start = 0, col_start = 0;

    for (int i = row_start; i < row_start + subgrid_row; i++)
    {
        for (int j = col_start; j < col_start + subgrid_column; j++)
        {
            int cell_value = threads_arg->grid[i][j];
            if (tmp_array[cell_value - 1])
            {
                create_output_file(1);
                exit(1);
            }
            else
            {
                tmp_array[cell_value - 1] = 1;
            }
        }
    }
    pthread_exit(NULL);
}

int verifyVeracity(int grid_length, int **grid)
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int result;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        threads_args *threads_arg = (threads_args *)malloc(sizeof(threads_args));
        threads_arg->grid_length = grid_length;
        threads_arg->grid = grid;
        if (i % 3 == 0)
        {
            result = pthread_create(&threads[i], NULL, verifyRows, threads_arg);
            if (result != 0)
            {
                perror("Thread creation failed");
                exit(EXIT_FAILURE);
            }
        }
        else if (i % 3 == 1)
        {
            result = pthread_create(&threads[i], NULL, verifyColumns, threads_arg);
            if (result != 0)
            {
                perror("Thread creation failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            result = pthread_create(&threads[i], NULL, verifySubgrid, threads_arg);
            if (result != 0)
            {
                perror("Thread creation failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    int veracity = 0;
    create_output_file(veracity);
    return 0;
}
