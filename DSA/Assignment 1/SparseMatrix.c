// Store sparse matrices efficiently in triplet form
// Sparsity should be > (2/3) for efficiency.

#include <stdio.h>
int main()
{
    int mat[3][30];
    // mat[0] --> row_indexes, mat[1] --> col_indexes, mat[2] --> non-zero values
    int rows, cols, i, j, num, k, max;
    printf("Enter the no. of rows and columns of matrix : ");
    scanf("%d %d", &rows, &cols);
    printf("Enter the (%d * %d) matrix (Row major order): ", rows, cols);
    k = 0; // IMP!
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &num);
            if (num != 0)
            {
                mat[0][k] = i;
                mat[1][k] = j;
                mat[2][k] = num;
                k++;
            }
        }
    }
    max = --k;
    k = 0;
    printf("The matrix :\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (i == mat[0][k] && j == mat[1][k])
            {
                printf("%d\t", mat[2][k]);
                k++;
            }
            else
            {
                printf("0\t");
            }
        }
        printf("\n");
    }
    return 0;
}