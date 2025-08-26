// Find the sum of an array's elements
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, sum;
    int *arr;
    sum = 0;
    printf("Enter the size of array = ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));
    printf("Enter %d elements : ", n);
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);

    for (i = 0; i < n; i++)
        sum += arr[i];
    printf("The sum of array elements = %d\n", sum);
    return 0;
}
