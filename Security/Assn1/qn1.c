#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

char *encrypt(char arr[], int key)
{
    if (key < 0)
    {
        key = 26 + key;
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
    char plain[SIZE];
    int key;
    printf("Plain text: ");
    scanf("%[^\n]%*c", plain);
    printf("Key: ");
    scanf("%d", &key);

    printf("Plain text: %s\n", plain);
    printf("Cipher text: %s\n", encrypt(plain, key));
    printf("Cipher text (reverse shifting): %s\n", encrypt(plain, -key));
}