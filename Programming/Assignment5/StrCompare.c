// Compare strings character by character
#include<stdio.h>
int len(char *str)
{
    int len=0;
    while(*str != '\0')
    {
        len++;
        str++;
    }
    return len;
}
int main()
{
    char str1[100];
    char str2[100];
    int same=0, diff=0;
    printf("Enter String 1: ");
    scanf("%[^\n]", str1);
    getchar();
    printf("Enter String 2: ");
    scanf("%[^\n]", str2);

    printf("Received strings:\n");
    printf("'%s' and '%s'\n", str1, str2);
    printf("Similar characters found in both strings are as follows:\n");
    int min = len(str1)<len(str2)?len(str1):len(str2);
    int max = len(str1)>len(str2)?len(str1):len(str2);
    int i = 0;
    for(i=0;i<min;i++)
    {
        if(str1[i] == str2[i])
        {
            printf("%c ", str1[i]);
            same++;
        }    
    }
    diff=max-same;
    printf("\nThe strings are different at %d places.\n", diff);
    printf("The strings are similar at %d places.\n", same);
    return 0;
}
