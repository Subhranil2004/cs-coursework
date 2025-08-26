// WAP to find the size of a text file without traversing it character by character.
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char file[20];
    printf("Enter the filename: ");
    scanf("%s", file);
    FILE *fptr = fopen(file, "r");
    fseek(fptr, 0, SEEK_END);
    printf("File size = %ld bytes.\n", ftell(fptr));
    return 0;
}
