#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 500
int extended_euclidean_algo(int a, int b, int *s, int *t, int *gcd)
{
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    while (r2 > 0)
    {
        int q = r1 / r2;
        // updating r's
        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        // updating s's
        *s = s1 - q * s2;
        s1 = s2;
        s2 = *s;

        // updating t's
        *t = t1 - q * t2;
        t1 = t2;
        t2 = *t;
    }
    *gcd = r1;
    *s = s1;
    *t = t1;
}

char *multiplicative_cipher(char arr[], int key)
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
                cipher[i] = (char)('a' + (((arr[i] - 'a') * key) % 26));
            }
            else
            {
                cipher[i] = (char)('A' + (((arr[i] - 'A') * key) % 26));
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

char *additive_decrypt(char arr[], int key)
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

    for (int i = 0; i < 26; i++)
    {
        printf("%d, ", hist[i]);
    }
    printf("\n");

    // printf("Cipher text: %s\n", cipher);
    char most_freq[] = {'E', 'T', 'A'};
    int key;
    printf("Most frequent letters: %c, %c, %c\n", most_freq[0], most_freq[1], most_freq[2]);
    printf("Most freq char in text: %c\n", 'A' + max);

    printf("\nDecoded texts\n");
    printf("\nConsidering Additive Cipher\n");
    for (int i = 0; i < 3; i++)
    {
        key = max - (most_freq[i] - 'A');
        // printf("max = %d, key = %d\n", max, key);
        printf("Replacing most freq char with '%c' : %s\n\n", most_freq[i], additive_decrypt(cipher, key));
    }

    printf("\nConsidering Multiplicative Cipher\n");

    int s, t, gcd, count = 0;
    int inverses[26] = {0};
    for (int key = 1; key < 26; key++)
    {
        extended_euclidean_algo(26, key, &s, &t, &gcd);
        if (gcd == 1)
        {
            if (t < 0)
                t = (26 + t) % 26;
            inverses[count++] = t;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        char repl = most_freq[i];
        int inv = -1;
        for (int j = 0; j < count; j++)
        {
            if ((char)('A' + (((cipher[i] - 'A') * inverses[j]) % 26)) == repl)
            {
                inv = inverses[j];
                break;
            }
        }
        if (inv == -1)
        {
            printf("No valid key found for replacing with '%c'\n\n", repl);
            continue;
        }
        // printf("max = %d, key = %d\n", max, key);
        printf("Inverse %d \n", inv);
        printf("Replacing most freq char with '%c' : %s\n\n", most_freq[i], multiplicative_cipher(cipher, inv));
    }
}