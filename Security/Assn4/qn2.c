#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200

char *vigenere_encrypt(char arr[], char key[])
{
    char *cipher = malloc(sizeof(char) * SIZE);
    int key_len = strlen(key);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        cipher[i] = (char)('A' + ((arr[i] - 'A' + key[i % key_len] - 'A') % 26));
    }
    cipher[i] = '\0';
    return cipher;
}

int main()
{
    int n = 26;

    char plain[SIZE] = "ATHIRDEYEISOBSERVINGBEALERT";
    printf("Plain Text: %s\n", plain);
    char key[SIZE] = "SECURE";
    char *cipher = vigenere_encrypt(plain, key);
    printf("Cipher Text (Key = %s): %s\n", key, cipher);
    free(cipher);

    return 0;
}