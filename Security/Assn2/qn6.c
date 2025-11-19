#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200
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

int main()
{
    int n = 26;

    int s, t, gcd;
    int count = 0;
    char cipher[SIZE]; // = "WE ARE LEARNING MULTIPLICATIVE CIPHER";
    printf("Cipher text: ");
    scanf("%[^\n]%*c", cipher);
    printf("Plain Texts:\n");
    for (int key = 1; key < n; key++)
    {
        extended_euclidean_algo(n, key, &s, &t, &gcd);
        if (gcd == 1)
        {
            if (t < 0)
                t = (n + t) % n;
            printf("key = %d,\tinverse = %d:\t", key, t);
            char *ct;
            printf("%s\n", (ct = multiplicative_cipher(cipher, t)));
            // printf("%s\n", multiplicative_cipher(ct, t));

            count++;
        }
    }
    printf("\n#keys found through brute force = %d\n", count);
}