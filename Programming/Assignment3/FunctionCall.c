// Call by value and call by reference 
#include<stdio.h>
void swap_by_value(int ,int);
void swap_by_reference(int *,int *);
int main()
{
	int a,b;
	printf("Enter values of a and b : ");
	scanf("%d %d", &a, &b);
	printf("In main():\ta = %d, b = %d.\n\n", a, b);

	printf("Using call by value...\n");
	swap_by_value(a, b);
	printf("Back in main():\ta = %d, b = %d.(Actual argument remains same)\n", a, b);
	printf("\nUsing call by reference...\n");
	swap_by_reference(&a, &b);
	printf("Back in main():\ta = %d, b = %d.(Actual argument changes)\n", a, b);
	return 0;
}

void swap_by_value(int a,int b)
{
	//Swapping values...
	int temp = a;
	a = b;
	b = temp;
	printf("In swap_by_value():\ta = %d, b = %d.\n", a, b);
}
void swap_by_reference(int *a, int *b)
{
	//Swapping values...
	int temp = *a;
	*a = *b;
	*b = temp;
	printf("In swap_by_reference():\ta = %d, b = %d.\n", *a, *b);
}
