#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200

char *autokey_decipher(char arr[], int key)
{

    if (key < 0)
    {
        key = 26 + key;
    }

    char *plain = malloc(sizeof(char) * SIZE);
    plain[0] = (char)('A' + ((arr[0] - 'A' + 26 - key) % 26));
    int i = 1;
    for (; arr[i] != '\0'; i++)
    {
        plain[i] = (char)('A' + ((arr[i] - 'A' + 26 - (plain[i - 1] - 'A')) % 26));
    }
    plain[i] = '\0';
    return plain;
}

int main()
{
    int n = 26;

    char cipher[SIZE] = "OJLETXVNETWMFGCUANA";
    printf("Cipher Text: %s\n", cipher);
    printf("Plain Texts:\n");
    for (int key = 1; key < n; key++)
    {
        char *plain = autokey_decipher(cipher, key);
        printf("Key = %d:\t%s\n", key, plain);
        free(plain);
    }
    return 0;
}