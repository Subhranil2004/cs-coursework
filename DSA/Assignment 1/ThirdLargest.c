// Find the 3rd largest integer without sorting

#include <stdio.h>
#define SIZE 50
int find_min(int *, int);
int find_max(int *, int);
int main()
{
        int n, i, min, max, index;
        int arr[SIZE];
        printf("Enter the number of integers : ");
        scanf("%d", &n);
        printf("Enter %d integers : ", n);
        for (i = 0; i < n; i++)
                scanf("%d", &arr[i]);
        min = find_min(arr, n);
        for (i = 1; i <= 3; i++)
        {
                index = find_max(arr, n);
                if (i != 3)
                        arr[index] = min;
        }
        printf("The third largest integer is = %d.\n", arr[index]);
        return 0;
}
int find_min(int brr[], int num)
{
        int i;
        int min = brr[0];
        for (i = 1; i < num; i++)
        {
                if (brr[i] < min)
                        min = brr[i];
        }
        return min;
}
int find_max(int brr[], int num)
{
        int i;
        int index = 0;
        for (i = 1; i < num; i++)
        {
                if (brr[i] > brr[index])
                        index = i;
        }
        return index;
}
