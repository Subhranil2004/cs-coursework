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
        key = key == 0 ? 25 : key - 1;
    }
    cipher[i] = '\0';
    return cipher;
}

char *encrypt(char arr[], int key)
{
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
        key++;
    }
    cipher[i] = '\0';
    return cipher;
}

int main()
{
    char plain[SIZE];
    int key;
    printf("Plain text: ");
    scanf("%[^\n]%*c", plain);
    printf("Key: ");
    scanf("%d", &key);

    // printf("Plain text: %s\n", plain);
    char *cipher = encrypt(plain, key);
    printf("\nCipher text: %s\n", cipher);
    printf("\nDecrypted Plain text: %s\n", decrypt(cipher, key));
}