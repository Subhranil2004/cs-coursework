#include <stdio.h>

int main()
{
    int yrs;
    char ch;
    printf("Enter the no. of year(s) : ");
    scanf("%d", &yrs);
    printf("Enter M for converting to months\n");
    printf("Enter d for converting to days\n");
    printf("Enter h for converting to hours\n");
    printf("Enter m for converting to minutes\n");
    printf("Enter s for converting to seconds\n");
    printf("Enter your choice : ");
    ch = getchar();
    while (ch == ' ' || ch == '\n')
        ch = getchar();
    switch (ch)
    {
    case 'M':
        printf("%d year(s) is equivalent to %d months.\n", yrs, 12 * yrs);
        break;
    case 'd': // Assuming non-leap years
        printf("%d year(s) is equivalent to %d days.\n", yrs, 365 * yrs);
        break;
    case 'h':
        printf("%d year(s) is equivalent to %d hours.\n", yrs, 24 * 365 * yrs);
        break;
    case 'm':
        printf("%d year(s) is equivalent to %ld minutes.\n", yrs, 60 * 24 * 365 * yrs);
        break;
    case 's':
        printf("%d year(s) is equivalent to %ld seconds.\n", yrs, 60 * 60 * 24 * 365 * yrs);
        break;
    default:
        printf("Wrong choice.Exiting...");
    }
    return 0;
}
