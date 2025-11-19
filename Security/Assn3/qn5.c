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

char *c1_encrypt(char arr[], int b1, int a, int b2)
{
    if (a < 0)
    {
        a = 26 + a;
    }

    char *cipher = malloc(sizeof(char) * SIZE);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        if (isalpha(arr[i]))
        {
            if (islower(arr[i]))
            {
                cipher[i] = (char)('a' + ((((arr[i] - 'a') + b1) * a + b2) % 26));
            }
            else
            {
                cipher[i] = (char)('A' + ((((arr[i] - 'A') + b1) * a + b2) % 26));
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

char *c2_encrypt(char arr[], int a1, int b)
{

    char *cipher = malloc(sizeof(char) * SIZE);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        if (isalpha(arr[i]))
        {
            if (islower(arr[i]))
            {
                cipher[i] = (char)('a' + ((((arr[i] - 'a') * a1) + b) * a1) % 26);
            }
            else
            {
                cipher[i] = (char)('A' + ((((arr[i] - 'A') * a1) + b) * a1) % 26);
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
    int a, b1, b2, t, gcd;
    printf("a: ");
    scanf("%d", &a);
    printf("k1: ");
    scanf("%d", &b1);
    printf("k2: ");
    scanf("%d", &b2);

    getchar();

    // extended_euclidean_algo(26, k1, &t, &gcd);
    // if(gcd != 1) {
    //     printf("k1 entered doesn't have an inverse");
    //     return 1;
    // }

    char arr[SIZE];
    printf("Plain text: ");
    fgets(arr, SIZE - 1, stdin);
    // printf("\n%s\n", arr);
    printf("C1 cipher: C1 = [(P + b1)*a + b2] mod 26\n");
    printf("Cipher text 1: %s", c1_encrypt(arr, b1, a, b2));

    int a1, b;
    printf("a1: ");
    scanf("%d", &a1);
    printf("b: ");
    scanf("%d", &b);
    printf("C2 =   [(P *a1 + b)*a1] mod 26");
    printf("\nCipher text 2: %s", c2_encrypt(arr, a1, b));
}