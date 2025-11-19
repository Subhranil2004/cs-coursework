#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000

char *decrypt(char arr[], int key)
{
    key = -key;
    if (key < 0)
    {
        key += 26;
    }

    char *cipher = malloc(sizeof(char) * SIZE);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        if (isalpha(arr[i]))
        {
            if (islower(arr[i]))
            {
                cipher[i] = (char)('a' + ((arr[i] - 'a' + key) % 26));
            }
            else
            {
                cipher[i] = (char)('A' + ((arr[i] - 'A' + key) % 26));
            }
        }
        else
        {
            cipher[i] = arr[i];
        }
    }
    cipher[i] = '\0';
    return cipher;
}

int main()
{
    char cipher[SIZE];
    printf("Cipher text: ");
    scanf("%[^\n]%*c", cipher);

    printf("Cipher text: %s\n", cipher);
    printf("Decoded texts\n");
    for (int key = -25; key <= 25; key++)
    {
        printf("Key=%d : %s\n", key, decrypt(cipher, key));
    }
}