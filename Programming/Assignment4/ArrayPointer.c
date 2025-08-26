// Store addresses of different elements of an array using an array of pointers
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr;
    int **ptr;
    int n, i;
    printf("Enter the size of array : ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));
    ptr = malloc(n * sizeof(int *));

    printf("Enter %d elements : ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
        ptr[i] = arr + i;
    }
    printf("Elements with their addresses :\n");
    for (i = 0; i < n; i++)
        printf("Element : %d\tAddress : %p\n", arr[i], ptr[i]);
    return 0;
}
