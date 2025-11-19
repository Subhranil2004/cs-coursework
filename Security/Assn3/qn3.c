#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200
void extended_euclidean_algo(int a, int b, int *t, int *gcd)
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

char *affine_decrypt(char arr[], int k1, int k2)
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
            cipher[i] = (char)(('A' + (((arr[i] - 'A' + 26) - k2) * k1) % 26));
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

    char arr[SIZE];
    printf("Cipher text: ");
    fgets(arr, SIZE - 1, stdin);
    // printf("\n%s\n", arr);
    printf("Possible Plain texts:\n");
    for (int k1 = 1; k1 < 26; k1++)
    {
        for (int k2 = 0; k2 < 26; k2++)
        {
            extended_euclidean_algo(26, k1, &t, &gcd);
            if (gcd == 1)
            {
                t = t < 0 ? (26 + t) % 26 : t;
                printf("Key [%d, %d]:\t%s", t, k2, affine_decrypt(arr, t, k2));
            }
        }
    }
}

// Key [15, 11]:   THEEXTRALABOFTODAYSTARTSATTWOPM