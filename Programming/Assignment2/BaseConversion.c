// Conversion to other bases
#include <stdio.h>
#include <string.h>

long int convert_bin(int);
int convert_oct(int);
void convert_hex(int, char *);
int main()
{
    int ch, dec;
    char hex[15];
    printf("Enter the decimal number : ");
    scanf("%d", &dec);
    printf("1. Convert to Binary\n");
    printf("2. Convert to Octal\n");
    printf("3. Convert to Hexadecimal\n");
    printf("Enter your choice no. : ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        printf("The Binary equivalent of %d is %ld\n", dec, convert_bin(dec));
        break;
    case 2:
        printf("The Octal equivalent of %d is %d\n", dec, convert_oct(dec));
        break;
    case 3:
        convert_hex(dec, hex);
        printf("The Hexadecimal equivalent of %d is %s\n", dec, hex);
        break;
    default:
        printf("Wrong choice.Exiting...\n");
    }

    return 0;
}
long int convert_bin(int dec)
{
    long int bin = 0;
    int pos = 1;
    while (dec != 0)
    {
        bin = (dec % 2) * pos + bin;
        pos *= 10;
        dec /= 2;
    }
    return bin;
}

int convert_oct(int dec)
{
    int oct = 0;
    int pos = 1;
    while (dec != 0)
    {
        oct = (dec % 8) * pos + oct;
        pos *= 10;
        dec /= 8;
    }
    return oct;
}

void convert_hex(int dec, char *hex)
{
    int rem, i = 0;
    while (dec != 0)
    {
        rem = dec % 16;
        if (rem < 10)
            hex[i] = rem + 48;
        else
            hex[i] = 'A' + (rem % 10);
        i++;
        dec /= 16;
    }
    hex[i] = '\0';
    // Reversing the digits
    char c;
    for (i = 0; i < strlen(hex) / 2; i++)
    {
        c = hex[i];
        hex[i] = hex[strlen(hex) - i - 1];
        hex[strlen(hex) - i - 1] = c;
    }
}