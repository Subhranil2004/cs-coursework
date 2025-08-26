// Store sparse matrices efficiently in triplet form
// Sparsity should be > (2/3) for efficiency.

#include <stdio.h>
#define VALUES 50

void addition(int mat1[3][VALUES], int mat2[3][VALUES], int add[3][VALUES], int, int, int);
void subtraction(int mat1[3][VALUES], int mat2[3][VALUES], int add[3][VALUES], int, int, int);
void display(int mat[3][VALUES], int);
int input(int mat[3][VALUES], int);
int main()
{
    int mat1[3][VALUES];
    int mat2[3][VALUES];
    int add[3][VALUES];
    int sub[3][VALUES];
    // mat[0] --> row_indexes, mat[1] --> col_indexes, mat[2] --> non-zero values
    int n, i, j, num, k, max1, max2, max_op;
    printf("Enter the side length (n) of the two square matrices : ");
    scanf("%d", &n);

    // Input 2 matrices
    printf("Enter the elements of (%d * %d) matrix 1(Row major order):\n", n, n);
    max1 = input(mat1, n);
    printf("Enter the elements of (%d * %d) matrix 2(Row major order):\n", n, n);
    max2 = input(mat2, n);
    // Display 2 matrices
    printf("Matrix 1:\n");
    display(mat1, n);
    printf("Matrix 2:\n");
    display(mat2, n);
    // Add 2 matrices and display 'add' matrix
    addition(mat1, mat2, add, max1, max2, n);
    printf("Addition result :\n");
    display(add, n);
    // Subtract 2 matrices and display 'sub' matrix
    subtraction(mat1, mat2, sub, max1, max2, n);
    printf("Subtraction result :\n");
    display(sub, n);
    return 0;
}
int input(int mat[3][VALUES], int n)
{
    // Stores the non-zero values in mat[0]
    int k, i, j, num;
    k = 0; // IMP!
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
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

    return k - 1;
}
void display(int mat[3][VALUES], int n)
{
    // Prints the non-zero values present in mat[0] and fills the rest with 0s in matrix form.
    int i, j, k = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
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
}

void addition(int mat1[3][VALUES], int mat2[3][VALUES], int add[3][VALUES], int max1, int max2, int n)
{
    // Performs the operation : add = mat1 + mat2
    int i, j, k1, k2, k_add, num1, num2;
    k1 = k2 = k_add = 0; // !
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < n; j++)
        {
            num1 = 0;
            num2 = 0;
            if (k1 <= max1 && mat1[0][k1] == i && mat1[1][k1] == j)
            {
                num1 = mat1[2][k1];
                k1++;
            }
            if (k2 <= max2 && mat2[0][k2] == i && mat2[1][k2] == j)
            {
                num2 = mat2[2][k2];
                k2++;
            }
            if (num1 != 0 || num2 != 0)
            {
                add[0][k_add] = i;
                add[1][k_add] = j;
                add[2][k_add] = num1 + num2;
                k_add++;
            }
        }
    }
}

void subtraction(int mat1[3][VALUES], int mat2[3][VALUES], int sub[3][VALUES], int max1, int max2, int n)
{
    // Performs the operation : sub = mat1 - mat2
    int i, j, k1, k2, k_sub, num1, num2;
    k1 = k2 = k_sub = 0; // !
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < n; j++)
        {
            num1 = 0;
            num2 = 0;
            if (k1 <= max1 && mat1[0][k1] == i && mat1[1][k1] == j)
            {
                num1 = mat1[2][k1];
                k1++;
            }
            if (k2 <= max2 && mat2[0][k2] == i && mat2[1][k2] == j)
            {
                num2 = mat2[2][k2];
                k2++;
            }
            if (num1 != 0 || num2 != 0)
            {
                sub[0][k_sub] = i;
                sub[1][k_sub] = j;
                sub[2][k_sub] = num1 - num2;
                k_sub++;
            }
        }
    }
}
