// Replace the words "a" "the", and "an" with " ".
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void display(char file[20])
{
    FILE *fptr = fopen(file, "r");
    char ch;
    
    while(fscanf(fptr, "%c", &ch) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");
    fclose(fptr);
}
int main()
{
    char file[20];
    char *mod = "modified.txt";
    FILE *srcptr, *modptr;
    printf("Filename: ");
    scanf("%s", file);
    srcptr = fopen(file, "r");
    if(srcptr == NULL)
    {
        printf("File not found in current directory.Exiting\n");
        exit(0);
    }
    printf("Contents of the '%s' file:\n", file);
    display(file);
    // rewind(srcptr); // IMP!
    modptr = fopen(mod, "w");// "w+" first write then read...
    char str[15];
    
    while(fscanf(srcptr, "%s", str) != EOF)// EOF
    {
        // printf("Str: '%s'\n", str);
        if (strcmp(str, "a") == 0 || strcmp(str, "an") == 0 || strcmp(str, "the") == 0)
        {
            fprintf(modptr, " ");
        }
        else
            fprintf(modptr, "%s", str);
        fprintf(modptr, " ");
    }
    fclose(modptr);
    printf("New file 'modified.txt' created.\nContents:\n");
    // rewind(modptr); // IMP!
    display(mod);
    return 0;
}
