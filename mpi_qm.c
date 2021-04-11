//
// Created by jean morelli on 02/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "qm.h"
#include <mpi.h>

#define return_data_tag 2002


////////////////////////////////////////////////////////////////////////////////////
////////////// MAIN
////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
        int side;
        int side_thirds;
        int **matrix;

        //Open file
        char *filename = argv[1];
        FILE *file = fopen(filename, "r");

        //Get size
        int size = 0;
        sscanf(filename, "%*[^0-9]%d", &size);

        //Allocate mem
        int *a = ints_new(size * size);
        int n = ints_to_array_from_file(file, a);
        fclose(file);

        //Fill Matrix
        side = (int) sqrt(n);
        side_thirds = side / 3;
        matrix = ints2_new(side, side);
        fill_matrix(a, matrix, side);

        MPI_Status status;
        long int sum, partial_sum, diag2, diag1;
        int ierr, num_procs, my_id, sender;


        ierr = MPI_Init(&argc, &argv);

        ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
        ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

        if(my_id == 0) //root process
        {
            printf("Approach : MPI \n");
            long int sum_lines;
            ierr = MPI_Recv( &sum_lines, 1, MPI_LONG, 1, return_data_tag, MPI_COMM_WORLD, &status);
            long int sum_columns;
            ierr = MPI_Recv( &sum_columns, 1, MPI_LONG, 2, return_data_tag, MPI_COMM_WORLD, &status);
            long int sum_diag;
            ierr = MPI_Recv( &sum_diag, 1, MPI_LONG, 3, return_data_tag, MPI_COMM_WORLD, &status);

            //Print result
            printf("Result : ");
            if (sum_lines == sum_columns && sum_lines == sum_diag) {
                printf("Mágico\n");
            } else if (sum_lines == sum_columns && sum_lines != -1) {
                printf("Imperfeito\n");
            } else {
                printf("Não é mágico\n");
            }

        } else //slaves
        {
            switch (my_id)
            {
                case 1:
                    partial_sum = check_lines(side, matrix);
                    ierr = MPI_Send(&partial_sum, 1, MPI_LONG, 0, return_data_tag, MPI_COMM_WORLD);
                    break;
                case 2:
                    partial_sum = check_columns(side, matrix);
                    ierr = MPI_Send(&partial_sum, 1, MPI_LONG, 0, return_data_tag, MPI_COMM_WORLD);
                    break;
                case 3:
                    diag1 = check_diagonal_top_left(side, matrix);
                    diag2 = check_diagonal_top_right(side, matrix);
                    partial_sum = diag1 == diag2 ? diag1 : -1;
                    ierr = MPI_Send(&partial_sum, 1, MPI_LONG, 0, return_data_tag, MPI_COMM_WORLD);
                    break;
                default:
                    break;
            }
        }
        ierr = MPI_Finalize();

    return 0;
}
