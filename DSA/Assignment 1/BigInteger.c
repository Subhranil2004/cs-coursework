#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 101 // Taking the max no. of digits to be 100 (+1) for storing '\0'
char *addition(char *, char *);
int compare(char *, char *);
char *subtraction(char *, char *);
void remove_zeroes(char *);
char add[MAX + 1], subt[MAX]; // Global variables

// initial 0 remove!! FUNCTION

int main()
{
    char num1[MAX], num2[MAX];
    printf("Enter two integers having atleast 10 digits each :\n");
    // Using gets() instead of fgets() as fgets() stores the newline at the end of string
    printf("1st integer : ");
    gets(num1);
    while (num1 == NULL || num1 == "\n" || num1 == " " || num1 == "\t")
        gets(num1);
    printf("2nd integer : ");
    gets(num2);
    while (num2 == NULL || num2 == "\n" || num2 == " " || num2 == "\t")
        gets(num2);

    remove_zeroes(num1);
    remove_zeroes(num2);
    printf("num1 = %s\nnum2 = %s\n", num1, num2);
    printf("Addition result : %s", addition(num1, num2));
    printf("\nSubtraction result : %s\n", subtraction(num1, num2));
    return 0;
}
char *addition(char *num1, char *num2)
{
    char carry[MAX];
    int i;
    char temp[MAX + 1];
    int res = 0;
    int diff;

    diff = strlen(num1) - strlen(num2);
    if (diff != 0)
    {
        for (i = 0; i < abs(diff); i++)
            temp[i] = '0';
        temp[i] = '\0';
    }

    for (i = 0; i < sizeof(carry) - 1; i++)
        carry[i] = '0';
    carry[i] = '\0'; //!

    // Padding the smaller no. with zeroes at the left
    if (diff > 0)
    {
        strcat(temp, num2);
        num2 = temp;
    }
    else if (diff < 0)
    {
        strcat(temp, num1);
        num1 = temp;
    }

    for (i = strlen(num1) - 1; i >= 0; i--)
    {
        // +- 48
        carry[i] = res + 48;
        res = (int)(carry[i]) - 48 + (int)(num1[i]) - 48 + (int)(num2[i]) - 48;
        add[i] = (res % 10) + 48;
        res /= 10;
    }
    add[strlen(num1)] = '\0'; //!
    // carry at end
    if (res != 0)
    {
        temp[0] = res + 48;
        temp[1] = '\0'; //!
        strcat(temp, add);
        strcpy(add, temp);
    }

    return add;
}
int compare(char *num1, char *num2)
{
    int i;
    if (strlen(num1) > strlen(num2))
        return 0;
    else if (strlen(num1) < strlen(num2))
        return 1;
    for (i = 0; i < strlen(num1); i++)
    {
        if ((int)num2[i] - 48 > (int)num1[i] - 48)
            return 1;
    }
    return 0;
}
char *subtraction(char *num1, char *num2)
{
    char temp[MAX];
    int i;
    int flag;
    int res = 0;
    int diff;
    int dig1, dig2;
    flag = compare(num1, num2);
    if (flag)
    {
        // Swapping num1 and num2
        strcpy(temp, num1);
        strcpy(num1, num2);
        strcpy(num2, temp);
    }
    diff = strlen(num1) - strlen(num2);
    if (diff != 0)
    {
        for (i = 0; i < diff; i++)
            temp[i] = '0';
        temp[i] = '\0';
    }

    // Padding the smaller no. with zeroes at the left
    if (diff > 0)
    {
        strcat(temp, num2);
        strcpy(num2, temp);
    }

    for (i = strlen(num1) - 1; i >= 0; i--)
    {
        dig1 = num1[i] - 48;
        dig2 = num2[i] - 48;
        if (dig1 < dig2)
        {
            dig1 += 10;
            num2[i - 1] += 1; // If 9+1=10 then character wont be 10 but res will be correct
        }
        res = dig1 - dig2;
        subt[i] = res + 48;
    }
    subt[strlen(num1)] = '\0';
    remove_zeroes(subt);
    if (flag)
    {
        strcpy(temp, "-");
        strcat(temp, subt);
        strcpy(subt, temp);
    }

    return subt;
}
void remove_zeroes(char *str) // char *type not reqd as array addresses are passed on in C
{

    int i = 0, index = 0;

    while (str[i] == '0' && str[i] != '\0')
        i++;

    if (str[i] == '\0')
    {

        str[0] = '0';
        str[1] = '\0';
        return; // Return early when the result is 0 otherwise it will continue to next if()!
    }

    if (i != 0)
    {
        while (str[i] != '\0')
        {
            str[index] = str[i];
            index++;
            i++;
        }
        str[index] = '\0';
    }
}