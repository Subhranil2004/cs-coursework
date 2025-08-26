// Calculates power produced by a dam
#include <stdio.h>
int main()
{
    float vol, h;
    printf("Enter the dam's height(in m) : ");
    scanf("%f", &h);
    printf("Enter the water flow(in m^3/s) : ");
    scanf("%f", &vol);
    printf("Power produced : %.4f MW\n", 0.9 * vol * 9.81 * h);
    return 0;
}