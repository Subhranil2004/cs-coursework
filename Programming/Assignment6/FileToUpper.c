// Lowercase -> Uppercase
#include<stdio.h>
#include<stdlib.h>
void display(char file[])
{
    char ch;
    FILE *fptr = fopen(file, "r");
    while(fscanf(fptr, "%c", &ch) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");
}
int main()
{
    FILE *fp1, *fp2;
    char file1[20], file2[20];
    char ch;
    printf("Enter the name of file to copy: ");
    scanf("%s", file1);
    fp1 = fopen(file1, "r");
    if(fp1 == NULL)
    {
        printf("That file doesn't exist in current directory. Exiting...");
        exit(0);
    }
    printf("Enter the name of file where to copy: ");
    scanf("%s", file2);

    
    fp2 = fopen(file2, "w");

    while((ch = fgetc(fp1))!= EOF)
    {
        if(ch>='a' && ch<='z')
            ch-=32;
        fputc(ch, fp2);
    }
    printf("Copied!\n");
    fclose(fp1);
    fclose(fp2);
    printf("Contents of resultant file:\n");
    display(file2);
    return 0;
}
