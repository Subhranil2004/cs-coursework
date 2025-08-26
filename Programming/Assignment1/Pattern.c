#include <stdio.h>
void fullscreen();
void halfscreen();
void top_3_lines();
void bottom_3_lines();
void right_triangle();
void isosceles_triangle();
void circle();
void diamond_blank();
int rows = 24;
int cols = 80;
int main()
{
    int ch;
    printf("1.... ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        fullscreen();
        break;
    case 2:
        halfscreen();
        break;
    case 3:
        top_3_lines();
        break;
    case 4:
        bottom_3_lines();
        break;
    case 5:
        right_triangle();
        break;
    case 6:
        isosceles_triangle();
        break;
    case 7:
        circle();
        break;
    case 8:
        diamond_blank();
        break;
    default:
        printf("Wrong choice.Exiting...");
    }
    return 0;
}
void fullscreen()
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void halfscreen()
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols / 2; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}
void top_3_lines()
{
    int i, j;
    for (i = 0; i < rows - 1; i++)
    {
        if (i >= 3)
        {
            printf("\n");
            continue;
        }
        for (j = 0; j < cols; j++)
            printf("*");
        printf("\n");
    }
}

void bottom_3_lines()
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        if (i < rows - 3)
        {
            printf("\n");
            continue;
        }
        for (j = 0; j < cols; j++)
            printf("*");
        printf("\n");
    }
}
void right_triangle()
{
    int i, j;
    for (i = 1; i < rows; i++)
    {
        for (j = 1; j <= 8; j++)
            printf(" ");
        for (j = 1; j <= rows; j++)
        {
            if (j <= rows - i)
                printf("   ");
            else
                printf("***");
        }
        printf("\n");
    }
}

void isosceles_triangle()
{
    int k = 1, i, j;
    for (i = 1; i < rows; i++)
    {
        for (j = 1; j <= 16; j++)
            printf(" ");
        for (j = 1; j <= rows - i; j++)
            printf(" ");
        for (j = 1; j <= k; j++)
            printf("*");
        printf("\n");
        k += 2;
    }
}

void circle()
{
    int i, j;
    int rad = rows / 2 - 1;
    for (i = -rad; i <= rad; i++)
    {
        for (j = 1; j <= 15; j++)
            printf(" ");
        for (j = rad; j >= -rad; j--)
        {
            // if(i*i + j*j <= rad*rad+16 && i*i + j*j >= rad*rad-16) // For Hollow circle
            if (i * i + j * j <= rad * rad)
                printf("**");
            else
                printf("  ");
        }
        printf("\n");
    }
}

void diamond_blank()
{
    int k = 1, i, j;
    for (i = 1; i <= rows / 2 - 1; i++)
    {
        for (j = 1; j <= rows - i + 16; j++)
            printf("*");
        for (j = 1; j <= k; j++)
            printf(" ");
        for (j = 1; j <= rows - i + 17; j++)
            printf("*");
        printf("\n");
        k += 2;
    }
    k = 1;
    for (i = rows / 2; i >= 1; i--)
    {
        for (j = 1; j <= rows - i + 16; j++)
            printf("*");
        for (j = 1; j <= rows - k; j++)
            printf(" ");
        for (j = 1; j <= rows - i + 17; j++)

            printf("*");
        printf("\n");
        k += 2;
    }
}
