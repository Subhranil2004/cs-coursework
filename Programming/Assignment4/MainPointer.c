// Call main() using pointer to main() function.
#include <stdio.h>

int counter = 6;
int main()
{
    int (*p_main)(void);
    p_main = &main;
    printf("Inside main()\n");
    while (--counter > 0)
        (*p_main)();
    return counter;
}
