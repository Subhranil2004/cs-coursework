#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200
char alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ' ', ',', '.'};

int len_alphabet = sizeof(alphabet) / sizeof(alphabet[0]);

int get_code(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (int)c - 65;
    }
    else if (c >= 'a' && c <= 'z')
    {
        return 26 + (int)c - 97;
    }
    else if (c >= '0' && c <= '9')
    {
        return 52 + (int)c - 48;
    }
    else if (c == ' ')
    {
        return 62;
    }
    else if (c == ',')
    {
        return 63;
    }
    else if (c == '.')
    {
        return 64;
    }
    return -1;
}

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

        int code = get_code(arr[i]);
        cipher[i] = code != -1 ? alphabet[(code * k1 + k2) % len_alphabet] : arr[i];
        // if char is not in alphabet, then that char itself is returned as encryption
    }
    cipher[i] = '\0';
    return cipher;
}

int main()
{
    int n = len_alphabet;

    int k1, k2, t, gcd;
    printf("Affine Cipher (k1 * c + k2)\n");

    printf("Use default values? ");
    if (getchar() == 'y')
    {
        k1 = len_alphabet - 5 + 1; // fifth last
        k2 = 56;
    }
    else
    {
        printf("k1: ");
        scanf("%d", &k1);
        printf("k2: ");
        scanf("%d", &k2);
    }

    getchar();

    extended_euclidean_algo(n, k1, &t, &gcd);
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