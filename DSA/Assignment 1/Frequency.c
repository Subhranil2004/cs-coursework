// Find the frequency of a character in a file

#include <stdio.h>
#include <stdlib.h>
int frequency(FILE *, char);
void print_contents(FILE *);
int main()
{
    FILE *fptr;
    char fpath[100];
    char ch;
    printf("Enter the relative filepath : "); 
    // For testing with the sample provided just type "Sample.txt" without quotes.
    scanf("%s", fpath);
    fptr = fopen(fpath, "r");
    if (fptr == NULL)
    {
        printf("File can't be opened. Exiting...");
        exit(0);
    }

    printf("Contents of the file :\n");
    print_contents(fptr);
    rewind(fptr); 
    // rewind() is used to move the file pointer to the beginning of the file stream.
    // fseek(fptr, 0L, SEEK_SET); performs the same task.
    printf("\nEnter the character : ");
    ch = getchar();
    while (ch == ' ' || ch == '\n' || ch == '\t')
        ch = getchar();
    printf("The frequency of character \'%c\' = %d.\n", ch, frequency(fptr, ch));
    fclose(fptr);
    return 0;
}
void print_contents(FILE *fp)
{
    char readch;
    readch = fgetc(fp);
    while(readch != EOF)
    {
        printf("%c", readch);
        readch = fgetc(fp);
    }
}
int frequency(FILE *fp, char ch)
{
    char readch;
    int freq = 0;
    readch = fgetc(fp);
    while (readch != EOF)
    {
        if (ch == readch)
            freq++;
        readch = fgetc(fp);
    }
    return freq;
}
