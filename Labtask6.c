#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 50
typedef char MatrixName[MAX_STRING_LEN];

/*---------------------------------------------------------------------------*/
double* input_matrix(int* numRows, int* numCols, MatrixName descriptor){

    double *matrixData; 
    int i, j;

    printf("Input number of rows for %s: ", descriptor);
    scanf("%d", numRows);
    printf("Input number of columns for %s: ", descriptor);
    scanf("%d", numCols);
    
    matrixData = (double*)malloc((*numRows) * (*numCols) * sizeof(double));
    if (!matrixData)
        return NULL;
    
    for(i = 0; i < *numRows; i++){
        for(j = 0; j < *numCols; j++){
            printf("Input value %d (Row Major Sequence): ", 
                    i * (*numCols) + j + 1);
            scanf("%lf", &matrixData[i * (*numCols) + j]); 	
        }
    }
    return matrixData;
}

/*---------------------------------------------------------------------------*/
int matrix_multiply(double* matrixA, int rowsA, int colsA, double* matrixB, int rowsB, int colsB, double* resultMatrix){
    int x, y, z;

    if(colsA != rowsB){
        return 0;
    }

    for(x = 0; x < rowsA; x++){
        for(y = 0; y < colsB; y++){
            resultMatrix[x * colsB + y] = 0;
            for(z = 0; z < colsA; z++){
                resultMatrix[x * colsB + y] += matrixA[x * colsA + z] * matrixB[z * colsB + y];
            }
        }
    }

    return 1; 
}
/*---------------------------------------------------------------------------*/

void output_matrix(double* data, int r, int c){
    int i, j;
    for (i = 0; i < r; i++){
        for(j = 0; j < c; j++){
            printf("%.2lf ", data[i * c + j]);
        }
        printf("\n");
    }
}
/*---------------------------------------------------------------------------*/
int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}