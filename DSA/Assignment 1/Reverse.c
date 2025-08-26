// Reverse an array without using another array

#include <stdio.h>
#define SIZE 50

void display(int *, int);
void reverse(int *, int);

int main()
{
	int n, i, arr[SIZE];
	printf("Enter no. of elements = ");
	scanf("%d", &n);
	printf("Enter %d elements : ", n);
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	printf("Original array :\n");
	display(arr, n);
	reverse(arr, n);
	printf("Array after reversing :\n");
	display(arr, n);
	return 0;
}
void display(int brr[], int num)
{
	int i;
	for (i = 0; i < num; i++)
		printf("%d\t", brr[i]);
	printf("\n");
}
void reverse(int *brr, int num)
{
	int i, temp;
	for (i = 0; i < num / 2; i++)
	{
		temp = brr[i];
		brr[i] = brr[num - i - 1];
		brr[num - i - 1] = temp;
	}
}
