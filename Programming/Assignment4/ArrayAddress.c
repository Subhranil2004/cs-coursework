// Display array elements with their addresses
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i;
    int *arr;
    printf("Enter the size of array = ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));
    printf("Enter %d elements : ", n);
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    printf("The array elements with their corresponding addresses :\n");
    for (i = 0; i < n; i++)
        printf("Element : %d\tAddress : %p\n", arr[i], arr + i);
    return 0;
}
