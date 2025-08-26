// Remove the leading and trailing blanks of a string.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *trim_blanks(char *);
int main()
{
    char str[100];
    printf("Enter a string : ");
    scanf("%[^\n]", str);
    printf("The original string : '%s'\n", str);
    printf("The string with blanks trimmed : '%s'\n", trim_blanks(str));
    return 0;
}

char *trim_blanks(char *to_trim)
{
    char *trim;
    int start = 0, end = strlen(to_trim)-1;
    while(to_trim[start] == ' ')
        start++;
    while(to_trim[end] == ' ')
        end--;
    printf("\nstart = %d, end = %d\n", start, end);
    trim = malloc((end-start+2)*sizeof(char));
    strncpy(trim, to_trim+start, end-start+1);
    trim[end-start+1] = '\0';
    return trim;
}
