#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PERMLEN 10
// #define SIZE 1000

int *get_permutation(double r, double x1)
{
    int *perm = (int *)malloc(PERMLEN * sizeof(int));
    double seq[10] = {0};
    double x_n_1 = x1;
    int idx = 0;
    for (int i = 1; i < 100; i++)
    {
        double x_n = r * x_n_1 * (1 - x_n_1);
        x_n_1 = x_n;
        if (i >= 90)
        {
            seq[idx++] = x_n;
        }
    }

    printf("Sequence: ");
    for (int i = 0; i < PERMLEN; i++)
    {
        printf("%f ", seq[i]);
    }
    printf("\n");

    // perform argsort with stable insertion sorting
    typedef struct
    {
        double value;
        int index;
    } Pair;

    Pair pairs[PERMLEN];
    for (int i = 0; i < PERMLEN; ++i)
    {
        pairs[i].value = seq[i];
        pairs[i].index = i;
    }

    for (int i = 1; i < PERMLEN; ++i)
    {
        Pair key = pairs[i];
        int j = i - 1;
        while (j >= 0 &&
               (pairs[j].value > key.value ||
                (pairs[j].value == key.value && pairs[j].index > key.index)))
        {
            pairs[j + 1] = pairs[j];
            --j;
        }
        pairs[j + 1] = key;
    }

    for (int i = 0; i < PERMLEN; ++i)
    {
        perm[i] = pairs[i].index;
    }

    printf("Permutation: ");
    for (int i = 0; i < PERMLEN; i++)
    {
        printf("%d ", perm[i]);
    }
    printf("\n");
    return perm;
}

int main()
{
    int *perm = get_permutation(3.741, 0.748);
    char plain[] = "IIEST Shibpur owes its origin to the erstwhile Bengal Engineering College, the history of which goes to the nineteenth century when industries in the sense we understand today were practically absent. Prompted by the idea of meeting the requirement of trained engineering personnel for the Public Works Department the then council of Education Bengal decided to open Civil Engineering classes and a Professorship in Civil Engineering was created at Hindu College Calcutta";

    int len = strlen(plain);
    int padded_len = len + (PERMLEN - (len % PERMLEN)) % PERMLEN;

    char padded[padded_len + 1];
    char cipher[padded_len + 1];

    // Copy the original string and pad with spaces
    strcpy(padded, plain);
    for (int i = len; i < padded_len; i++)
    {
        padded[i] = ' ';
    }
    padded[padded_len] = '\0';

    int idx = 0;
    for (int i = 0; i < PERMLEN; i++)
    {
        for (int j = 0; j < padded_len / PERMLEN; j++)
        {
            cipher[idx++] = padded[j * PERMLEN + perm[i]];
        }
    }
    cipher[idx] = '\0';
    printf("\nPadded text: '%s'\n", padded);
    printf("\nCipher text: '%s'\n", cipher);
    free(perm);
    return 0;
}