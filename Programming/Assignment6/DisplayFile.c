// WAP to read a file and display its contents with its line numbers.
#include<stdio.h>
#include<stdlib.h>
int main()
{
    char file[20];
    char line[200];
    int i=1;
    printf("Enter the filename: ");
    scanf("%s", file);
    FILE *fptr = fopen(file, "r");
    if(fptr == NULL)
    {
        printf("No such file exists in current directory.Exiting...\n");
        exit(0);
    }
    printf("The contents of the file:\n");
    while (fgets(line, 200, fptr) != NULL) 
    {
        printf("%d. %s", i, line);
        i++;
    }
    printf("\n");
    return 0;
}
