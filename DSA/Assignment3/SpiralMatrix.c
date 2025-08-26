// Spiral matrix
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>

void zig_zag(int arr[SIZE][SIZE], int, int);
void spiral(int arr[SIZE][SIZE], char, int, int);
void display(int arr[SIZE][SIZE], int, int);
int main()
{
    int row, col, i, j, ch;
    int arr[SIZE][SIZE];
    printf("Options for traversing : \n");
    printf("1. Spiral clockwise\n2. Spiral anticlockwise\n3. Zig-zag\n");
    printf("Enter your choice : ");
    scanf("%d", &ch);

    printf("Enter the no. of rows and columns of a square matrix respectively: ");
    scanf("%d %d", &row, &col);
    printf("Enter %d elements for the matrix : ", row * col);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            scanf("%d", &arr[i][j]);
    }

    printf("The original matrix:\n");
    display(arr, row, col);
    switch (ch)
    {
    case 1:
        spiral(arr, 'c', row, col);
        break;
    case 2:
        spiral(arr, 'a', row, col);
        break;
    case 3:
        zig_zag(arr, row, col);
        break;
    default:
        printf("Wrong choice");
        exit(0);
    }

    return 0;
}

void zig_zag(int arr[SIZE][SIZE], int row, int col)
{
    int i, j;
    printf("Traversal in zig-zag pattern : \n");
    for (i = 0; i < row; i++)
    {
        if (i % 2 != 0)
        {
            for (j = col - 1; j >= 0; j--)
                printf("%d  ", arr[i][j]);
        }
        else
        {
            for (j = 0; j < col; j++)
                printf("%d  ", arr[i][j]);
        }
    }

    printf("\n");
}

void spiral(int arr[SIZE][SIZE], char c, int row, int col)
{
    int top, right, bottom, left;
    int i;
    top = 0;
    bottom = row - 1;
    left = 0;
    right = col - 1;

    if (c == 'c')
    {
        printf("Traversal in Clockwise spiral pattern : \n");
        while (top <= bottom && left <= right)
        {
            for (i = left; i <= right; i++)
            {
                printf("%d  ", arr[top][i]);
            }

            top++;
            for (i = top; i <= bottom; i++)
            {
                printf("%d  ", arr[i][right]);
            }

            right--;
            if (top <= bottom) // Both conditions not reqd.
            {
                for (i = right; i >= left; i--)
                {
                    printf("%d  ", arr[bottom][i]);
                }

                bottom--;
            }

            if (left <= right) // Same
            {
                for (i = bottom; i >= top; i--)
                {
                    printf("%d  ", arr[i][left]);
                }

                left++;
            }
        }
    }
    else
    {
        printf("Traversal in Anti-clockwise spiral pattern : \n");
        while (top <= bottom && left <= right)
        {
            for (i = top; i <= bottom; i++)
            {
                printf("%d  ", arr[i][left]);
            }

            left++;
            for (i = left; i <= right; i++)
            {
                printf("%d  ", arr[bottom][i]);
            }

            bottom--;
            if (left <= right) // Same
            {
                for (i = bottom; i >= top; i--)
                {
                    printf("%d  ", arr[i][right]);
                }

                right--;
            }

            if (top <= bottom) // Same
            {
                for (i = right; i >= left; i--)
                {
                    printf("%d  ", arr[top][i]);
                }

                top++;
            }
        }
    }

    printf("\n");
}

void display(int arr[SIZE][SIZE], int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            printf("%d\t", arr[i][j]);
        printf("\n");
    }
}
