#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>


#define MAX_SIZE_MATRIX    (400000000) //20 000 x 20 000 matrix


// Author:  Professor Pedro Guerreiro
int *ints_new(int n)
{
    //  return (int *) calloc(n, sizeof (int));
    return (int *) malloc (n * sizeof(int));
}

// Author:  Professor Pedro Guerreiro
int **ints2_new(int rows, int cols) {
    int **result = (int **) malloc(rows * sizeof(int *));
    int *p = ints_new(rows * cols);
    for (int i = 0; i < rows; i++, p+= cols) {
        result[i] = p;
    }
    return result;
}

//Read from file to array "a"
int ints_to_array_from_file(FILE *file, int *a) {
    int result = 0;
    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        a[result++] = num;
    }
    return result;
}

//Convert a vector to a 2-D matrix
void fill_matrix(const int *a, int **matrix, int sides) {
    int current = 0;
    for (int i = 0; i < sides; ++i) {
        for (int j = 0; j < sides; ++j) {
            matrix[i][j] = a[current];
            current++;
        }
    }
}

//Print matrix on console with the row X column format
void toString(int n, int **a) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%i ", a[i][j]);
        }
        printf("\n");
    }
}

//Check to see if all lines has the sum up to the same value
//Return -> -1 if false, otherwise return the value of the sum of one row
int check_lines(int n, int **matrix) {

    int sum = 0;
    int sumLine = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum += matrix[i][j];
        }

        //Set what the sumLine is mean to be. It will always compare the others lines with the first one
        if(i == 0) sumLine = sum;

        if(i >= 1 && sum != sumLine) {
            return -1;
        }

        sum = 0;
    }

    return sumLine;
}

//Check to see if all lines has the sum up to the same value
//Return -> -1 if false, otherwise return the value of the sum of one column
int check_columns(int n, int **matrix) {
    int sum = 0;
    int sumColumn = 0;
    for (int j = 0; j < n; ++j) {

        for (int i = 0; i < n;  ++i) {
            sum += matrix[i][j];
        }

        //Set what the sumColumn is mean to be. It will always compare the others columns with the first one
        if(j == 0) sumColumn = sum;

        //In case the sum is different it returns "false"
        if(j >= 1 && sum != sumColumn) {
            return -1;
        }


        sum = 0;
    }

    return sumColumn;
}

//Check to see if all lines has the sum up to the same value
//Return -> -1 if false, otherwise return the value of the sum of one column
int check_columns_arg(int l, int n, int side, int **matrix) {
    int sum = 0;
    int sumColumn = 0;
    for (int j = l; j < n; ++j) {

        for (int i = 0; i < side;  ++i) {
            sum += matrix[i][j];
        }

        //Set what the sumColumn is mean to be. It will always compare the others columns with the first one
        if(j == l) sumColumn = sum;

        //In case the sum is different it returns "false"
        if(j >= 1 && sum != sumColumn) {
            return -1;
        }


        sum = 0;
    }

    return sumColumn;
}

//Returns the sum of the diagonal (top left to bottom right)
int check_diagonal_top_left(int n,  int **matrix) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += matrix[i][i];
    }


    return sum;
}

//Returns the sum of the diagonal (top right to bottom left)
int check_diagonal_top_right(int n, int **matrix) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += matrix[i][n-i-1];
    }

    return sum;
}

//Total time in seconds
float total_time(struct timeval i, struct timeval e) {
    return  ((float)(e.tv_sec - i.tv_sec) * 1000.0f + (float) (e.tv_usec - i.tv_usec) / 1000.0f) / 1000.0f;
}



////////////////////////////////////////////////////////////////////////////////////
////////////// UNIT TEST
////////////////////////////////////////////////////////////////////////////////////
//void unit_test_check_lines() {
//    int *a = ints_new(MAX_SIZE_MATRIX);
//    FILE *file = fopen("test_lines_1.txt", "r");
//    int n = ints_to_array_from_file(file, a);
//    fclose(file);
//
//
//    int side = (int) sqrt(n);
//    int **matrix = ints2_new(side, side);
//    fill_matrix(a, matrix, side);
//    free(a);
//
//
//    int result = check_lines(side,matrix);
//    assert(result == 10);
//
//    //Check to see if it will return -1 in case the matrix have different sum of values for the rows.
//    int *a2 = ints_new(MAX_SIZE_MATRIX);
//    FILE *file2 = fopen("test_lines_2.txt", "r");
//    int n2 = ints_to_array_from_file(file2, a2);
//    fclose(file2);
//
//
//    int side2 = (int) sqrt(n2);
//    int **matrix2 = ints2_new(side2, side2);
//    fill_matrix(a2, matrix2, side2);
//    free(a2);
//
//    result = check_lines(side2,matrix2);
//    assert(result == -1);
//
//}
//
//
//void unit_test_check_columns() {
//    int *a = ints_new(MAX_SIZE_MATRIX);
//    FILE *file = fopen("test_columns_1.txt", "r");
//    int n = ints_to_array_from_file(file, a);
//    fclose(file);
//
//
//    int side = (int) sqrt(n);
//    int **matrix = ints2_new(side, side);
//    fill_matrix(a, matrix, side);
//    free(a);
//
//
//    int result = check_columns(side,matrix);
//    assert(result == 16);
//
//    //Check to see if it will return -1 in case the matrix have different sum of values for the columns.
//    int *a2 = ints_new(MAX_SIZE_MATRIX);
//    FILE *file2 = fopen("test_columns_2.txt", "r");
//    int n2 = ints_to_array_from_file(file2, a2);
//    fclose(file2);
//
//
//    int side2 = (int) sqrt(n2);
//    int **matrix2 = ints2_new(side2, side2);
//    fill_matrix(a2, matrix2, side2);
//    free(a2);
//
//    result = check_columns(side2,matrix2);
//    assert(result == -1);
//
//}
//
//void unit_test_check_diagonal_top_left() {
//    int *a = ints_new(MAX_SIZE_MATRIX);
//    FILE *file = fopen("test_columns_1.txt", "r");
//    int n = ints_to_array_from_file(file, a);
//    fclose(file);
//
//
//    int side = (int) sqrt(n);
//    int **matrix = ints2_new(side, side);
//    fill_matrix(a, matrix, side);
//    free(a);
//
//
//    int result = check_diagonal_top_left(side,matrix);
//    assert(result == 15);
//
//    //Check to see if it will return -1 in case the matrix have different sum of values for the rows.
//    int *a2 = ints_new(MAX_SIZE_MATRIX);
//    FILE *file2 = fopen("test_lines_1.txt", "r");
//    int n2 = ints_to_array_from_file(file2, a2);
//    fclose(file2);
//
//
//    int side2 = (int) sqrt(n2);
//    int **matrix2 = ints2_new(side2, side2);
//    fill_matrix(a2, matrix2, side2);
//    free(a2);
//
//    result = check_diagonal_top_left(side2,matrix2);
//    assert(result == 10);
//}
//
//void unit_test_check_diagonal_top_right() {
//    int *a = ints_new(MAX_SIZE_MATRIX);
//    FILE *file = fopen("test_columns_1.txt", "r");
//    int n = ints_to_array_from_file(file, a);
//    fclose(file);
//
//
//    int side = (int) sqrt(n);
//    int **matrix = ints2_new(side, side);
//    fill_matrix(a, matrix, side);
//    free(a);
//
//
//    int result = check_diagonal_top_right(side,matrix);
//    assert(result == 17);
//
//    //Check to see if it will return -1 in case the matrix have different sum of values for the rows.
//    int *a2 = ints_new(MAX_SIZE_MATRIX);
//    FILE *file2 = fopen("test_lines_1.txt", "r");
//    int n2 = ints_to_array_from_file(file2, a2);
//    fclose(file2);
//
//
//    int side2 = (int) sqrt(n2);
//    int **matrix2 = ints2_new(side2, side2);
//    fill_matrix(a2, matrix2, side2);
//    free(a2);
//
//    result = check_diagonal_top_right(side2,matrix2);
//    assert(result == 10);
//}
//
//void unit_test_p() {
//    //Test with 2001x2001 matrix
//    int *a = ints_new(MAX_SIZE_MATRIX);
//    FILE *file = fopen("p2001.txt", "r");
//    int n = ints_to_array_from_file(file, a);
//    fclose(file);
//
//
//    int side = (int) sqrt(n);
//    int **matrix = ints2_new(side, side);
//    fill_matrix(a, matrix, side);
//    free(a);
//
//
//    //Sum Lines
//    int sum_lines = check_lines(side, matrix);
//    //Sum Columns
//    int sum_columns = check_columns(side, matrix);
//    //Sum Diagonal (Top Left to Bottom Right)
//    int sum_diag_top_left = check_diagonal_top_left(side, matrix);
//    //Sum Diagonal (Top Right to Bottom Left);
//    int sum_diag_top_right = check_diagonal_top_right(side, matrix);
//    int lines_columns = sum_lines == sum_columns;
//    int diagonals = sum_diag_top_left == sum_diag_top_right;
//    int sides_diagonals = sum_lines == sum_diag_top_right;
//    assert(lines_columns == diagonals == sides_diagonals == 1);
//
////    Test with 4001x4001 matrix
//    int *a2 = ints_new(MAX_SIZE_MATRIX);
//    FILE *file2 = fopen("p4001.txt", "r");
//    int n2 = ints_to_array_from_file(file2, a2);
//    fclose(file2);
//
//
//    int side2 = (int) sqrt(n2);
//    int **matrix2 = ints2_new(side2, side2);
//    fill_matrix(a2, matrix2, side2);
//    free(a2);
//
//
//    //Sum Lines
//    int sum_lines2 = check_lines(side, matrix);
//    //Sum Columns
//    int sum_columns2 = check_columns(side, matrix);
//    //Sum Diagonal (Top Left to Bottom Right)
//    int sum_diag_top_left2 = check_diagonal_top_left(side, matrix);
//    //Sum Diagonal (Top Right to Bottom Left);
//    int sum_diag_top_right2 = check_diagonal_top_right(side, matrix);
//    int lines_columns2 = sum_lines2 == sum_columns2;
//    int diagonals2 = sum_diag_top_left2 == sum_diag_top_right2;
//    int sides_diagonals2 = sum_lines2 == sum_diag_top_right2;
//    assert(lines_columns2 == diagonals2 == sides_diagonals2 == 1);
//
//}
//
//void run_tests() {
//    unit_test_check_lines();
//    unit_test_check_columns();
//    unit_test_check_diagonal_top_left();
//    unit_test_check_diagonal_top_right();
//
//    //Tests to check Perfeito, Imperfeito e Nao Magico
//    unit_test_p();
//}