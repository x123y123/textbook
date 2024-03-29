/* Passing multi-dim array */

#include <stdio.h>

/* 

we can use: 
    
    method_1: 
        void display_2d_arr(int arr[][5], int rows) {}
    
    method_2:
        void display_2d_arr(int (*arr)[5], int rows) {}
*/

void display_2d_arr(int arr[][5], int rows)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void display_2d_arr_size_unknown(int *arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            printf("%d ", *(arr + (i*cols) + j));
        }
        printf("\n");
    }
}

void display_3d_arr(int (*arr)[2][5], int rows)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 2; j++) {
            printf("{");
            for (int k = 0; k < 4; k++) {
                printf("%d ", arr[i][j][k]);
            }
            printf("}");
        }
        printf("\n");
    }
}

int main()
{
    int matrix_2d[2][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10}
    };

    int matrix_3d[3][2][5] = {
        {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}},
        {{11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}},
        {{21, 22, 23, 24, 25}, {26, 27, 28, 29, 30}},
    };

    display_2d_arr(matrix_2d, 2);
    display_2d_arr_size_unknown(*matrix_2d, 2, 5);
    display_3d_arr(matrix_3d, 3);

    return 0;
}
