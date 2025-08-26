// WAP to add the contents of one file at the end of another.
#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fp1, *fp2;
    char file1[20], file2[20];
    char ch;
    printf("Enter the name of file where to append: ");
    scanf("%s", file1);
    printf("Enter the name of file whose contents are to be appended: ");
    scanf("%s", file2);

    fp1 = fopen(file1, "a");
    fp2 = fopen(file2, "r");
    if(fp2 == NULL)
    {
        printf("That file doesn't exist in current directory. Exiting...");
        exit(0);
    }
    while((ch = fgetc(fp2))!= EOF)
    {
        fputc(ch, fp1);
    }
    printf("Appended.\n");
    fclose(fp1);
    fclose(fp2);
    return 0;
}
