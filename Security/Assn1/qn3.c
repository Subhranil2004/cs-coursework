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
    char cipher[SIZE];
    printf("Cipher text: ");
    scanf("%[^\n]%*c", cipher);

    int hist[26] = {0};

    for (int i = 0; i < strlen(cipher); i++)
    {
        hist[cipher[i] - 'A']++;
    }
    int max_freq = 0;
    int max = 0;
    for (int i = 0; i < 26; i++)
    {
        if (hist[i] > max_freq)
        {
            max = i;
            max_freq = hist[i];
        }
    }

    printf("Letter frequencies:\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c: %d, ", (char)(i + 'A'), hist[i]);
    }
    printf("\n");

    // printf("Cipher text: %s\n", cipher);
    printf("\nMost frequent letter: '%c' with frequency %d\n", (char)(max + 'A'), max_freq);
    printf("\nDecoded texts\n");
    char most_freq[] = {'E', 'T', 'A'};
    int key;
    for (int i = 0; i < 3; i++)
    {
        key = max - (most_freq[i] - 'A');
        // printf("max = %d, key = %d\n", max, key);
        printf("Replacing with '%c' : %s\n\n", most_freq[i], decrypt(cipher, key));
    }
}