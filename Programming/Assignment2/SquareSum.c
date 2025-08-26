// Print sum of squares of nos. with LSD = 5
#include <stdio.h>

int main()
{
    int a, b, i, sum = 0;
    printf("Enter the starting and stopping integers : ");
    scanf("%d %d", &a, &b);

    printf("The numbers(LSD = 5) with their corresponding squares :\n");
    for (i = a + 1; i < b; i++)
    {
        if (i % 10 == 5)
        {
            printf("%d --- %d\n", i, i * i);
            sum += i * i;
        }
    }
    printf("The sum of their squares = %d\n", sum);
    return 0;
}