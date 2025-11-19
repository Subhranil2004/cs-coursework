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

void get_top_2_chars(int hist[26], int *max1, int *max2)
{
    *max1 = -1;
    *max2 = -1;
    for (int i = 0; i < 26; i++)
    {
        if (*max1 == -1 || hist[i] > hist[*max1])
        {
            *max2 = *max1;
            *max1 = i;
        }
        else if (*max2 == -1 || hist[i] > hist[*max2])
        {
            *max2 = i;
        }
    }
}

char *affine_decrypt(char arr[], int k1, int k2)
{
    int k1_inv, t, gcd;
    extended_euclidean_algo(k1, 26, &k1_inv, &t, &gcd);
    if (gcd != 1)
    {
        printf("k1 (%d) has no inverse. Decryption failed.\n", k1);
        return NULL;
    }
    k1_inv = (k1_inv + 26) % 26;

    char *cipher = malloc(sizeof(char) * SIZE);
    int i = 0;
    for (; arr[i] != '\0'; i++)
    {
        if (isalpha(arr[i]))
        {
            cipher[i] = (char)(('A' + (((arr[i] - 'A' + 26 - k2) * k1_inv) % 26)));
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

    int max1, max2;
    get_top_2_chars(hist, &max1, &max2);

    for (int i = 0; i < 26; i++)
    {
        printf("%d, ", hist[i]);
    }
    printf("\n");

    // printf("Cipher text: %s\n", cipher);
    char most_freq[] = {'E', 'T'};
    int key;
    printf("Most frequent letters: %c, %c\n", most_freq[0], most_freq[1]);
    printf("Most freq chars in text: %c and %c\n", 'A' + max1, 'A' + max2);

    printf("\nDecoded texts\n");

    // int inverses[26] = {0};
    // for (int key = 1; key < 26; key++)
    // {
    //     extended_euclidean_algo(26, key, &s, &t, &gcd);
    //     if (gcd == 1)
    //     {
    //         if (t < 0)
    //             t = (26 + t) % 26;
    //         inverses[count++] = t;
    //     }
    // }

    // max1 = k1 * 'E' + k2
    // max2 = k1 * 'T' + k2

    // int s, t, gcd, count = 0;
    // int diff = (26 + most_freq[0]-most_freq[1]) % 26;
    // extended_euclidean_algo(26, diff, &s, &t, &gcd);
    // if(gcd != 1) return 1;
    // t = (t+26) % 26;
    // int k1 = ((max1 - max2 + 26) * t) % 26;
    // int k2 = (26 + max1 - k1 * ('E' - 'A')) % 26;

    int c1 = max1; // index of most freq letter in cipher
    int c2 = max2;
    int p1 = most_freq[0] - 'A'; // 'E' = 4
    int p2 = most_freq[1] - 'A'; // 'T' = 19

    int delta_p = (p1 - p2 + 26) % 26;
    int delta_c = (c1 - c2 + 26) % 26;

    // Get modular inverse of delta_p
    int s, t, gcd;
    extended_euclidean_algo(delta_p, 26, &s, &t, &gcd);
    if (gcd != 1)
    {
        printf("No modular inverse exists. Decryption failed.\n");
        return 1;
    }
    int inv_delta_p = (s + 26) % 26;

    // Now get k1 and k2
    int k1 = (delta_c * inv_delta_p) % 26;
    int k2 = (c1 - k1 * p1 + 26 * 26) % 26; // Avoid negative

    printf("k1 = %d, k2 = %d. Decrypted text: %s\n", k1, k2, affine_decrypt(cipher, k1, k2));
}