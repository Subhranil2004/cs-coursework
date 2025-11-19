#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200
int extended_euclidean_algo(int a, int b, int *t, int *gcd)
{
    int r1 = a, r2 = b;
    int t1 = 0, t2 = 1;

    while (r2 > 0)
    {
        int q = r1 / r2;
        // updating r's
        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        // updating t's
        *t = t1 - q * t2;
        t1 = t2;
        t2 = *t;
    }
    *gcd = r1;
    *t = t1;
}

char *affine_encrypt(char arr[], int k1, int k2)
{
    if (k1 < 0)
    {
        k1 = 26 + k1;
    }

    char *cipher = malloc(sizeof(char) * SIZE);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        if (isalpha(arr[i]))
        {
            if (islower(arr[i]))
            {
                cipher[i] = (char)('a' + (((arr[i] - 'a') * k1 + k2) % 26));
            }
            else
            {
                cipher[i] = (char)('A' + (((arr[i] - 'A') * k1 + k2) % 26));
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
    int k1, k2, t, gcd;
    printf("Affine Cipher (k1 * c + k2)\n");
    printf("k1: ");
    scanf("%d", &k1);
    printf("k2: ");
    scanf("%d", &k2);

    getchar();

    extended_euclidean_algo(26, k1, &t, &gcd);
    if (gcd != 1)
    {
        printf("k1 entered doesn't have an inverse");
        return 1;
    }
    char arr[SIZE];
    printf("Plain text: ");
    fgets(arr, SIZE - 1, stdin);
    // printf("\n%s\n", arr);
    printf("Cipher text: %s", affine_encrypt(arr, k1, k2));
}