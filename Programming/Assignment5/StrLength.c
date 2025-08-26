// find the length of a given string, including and excluding the spaces
#include<stdio.h>
#include<stdlib.h>
int main()
{
    char *p = calloc(100, 1);
    int len, lenExcl;
    len=0;
    lenExcl=0;
    printf("Enter the string: ");
    scanf("%[^\n]", p);
    printf("Received string = '%s'\n", p);
    
    while(*p != '\0')
    {
        if(*p != ' ')
            lenExcl++;
        len++;
        p++;
    }
    printf("Length of string including spaces: %d\n", len);
    printf("Length of string excluding spaces: %d\n", lenExcl);
    return 0;
}
