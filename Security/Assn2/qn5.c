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
        key = len_alphabet + key;
    }

    char *cipher = malloc(sizeof(char) * SIZE);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        int code = get_code(arr[i]);
        cipher[i] = code != -1 ? alphabet[(code * key) % len_alphabet] : arr[i];
        // if char is not in alphabet, then that char itself is returned as encryption
    }
    cipher[i] = '\0';
    return cipher;
}

int main()
{
    int n = len_alphabet;

    int s, t, gcd;
    char str[SIZE];
    printf("Plain text: ");
    scanf("%[^\n]%*c", str);

    int key = 29;
    printf("Cipher Text:\n");
    extended_euclidean_algo(n, key, &s, &t, &gcd);
    if (gcd == 1)
    {
        if (t < 0)
        {
            t = (n + t) % n;
        }
        printf("key = %d: ", key);
        char *ct;
        printf("%s\n", (ct = multiplicative_cipher(str, key)));
        printf("Deciphered Text: %s\n", multiplicative_cipher(ct, t));
    }
    else
    {
        printf("Key = %d is not valid for decryption.\n", key);
    }
}