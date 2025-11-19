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

    // printf("Sequence: ");
    // for (int i = 0; i < PERMLEN; i++)
    // {
    //     printf("%f ", seq[i]);
    // }
    // printf("\n");

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

char *decipher_text(int padded_len, int *perm, char padded[padded_len + 1], char deciphered[padded_len + 1])
{
    char rows[PERMLEN][padded_len / PERMLEN + 1];
    for (int i = 0; i < PERMLEN; i++)
    {
        strncpy(rows[perm[i]], &padded[i * (padded_len / PERMLEN)], padded_len / PERMLEN);
        rows[perm[i]][padded_len / PERMLEN] = '\0';
    }

    int idx = 0;
    for (int j = 0; j < padded_len / PERMLEN; j++)
    {
        for (int i = 0; i < PERMLEN; i++)
        {
            deciphered[idx++] = rows[i][j];
        }
    }
    deciphered[idx] = '\0';

    return deciphered;
}

int main()
{
    char cipher[] = " wieen ty hnyu  t tspemeeies cphudedngcds ia Cl Iptttgeeiw nenesnt l banufeglPkee i oirerilieigai nrenl fen hre dratddte dineottiaa ies svec lt S oti n,oc eunisraaaotfterieolD c  cpEgaein euC Seg  gCh get stwawiet e nneot aenune il oCnsaoc Iusowargshten sedopyPy gi n  usnnood lisop nane Er  hlietiotti nedr r o rtgpfb t fneo n f Egtd  hsieBioeoo hwthenecneierternhWr ccgdCnaarie tlu bi snelh sicei u el. eiqo ne rmhltltvesPhirrHet TorhlEg rhterdnesycbmh hmanrrietoEBien nsngwd a ";
    printf("len: %d\n", (int)strlen(cipher));

    int len = strlen(cipher);
    int padded_len = len + (PERMLEN - (len % PERMLEN)) % PERMLEN;

    char padded[padded_len + 1];
    char deciphered[padded_len + 1];

    // Copy the original string and pad with spaces
    strcpy(padded, cipher);
    for (int i = len; i < padded_len; i++)
    {
        padded[i] = ' ';
    }
    padded[padded_len] = '\0';
    printf("Deciphered texts (Brute Force with different values of r and x_n):\n");

    // Keeping x_n fixed, varying r
    double x_n = 0.748;
    double r_values[] = {3.740, 3.74104, 3.730999, 3.741};

    for (int i = 0; i < sizeof(r_values) / sizeof(r_values[0]); i++)
    {
        int *perm = get_permutation(r_values[i], x_n);
        printf("[x_n=%.3f, r=%.5f]:\t'%s'\n", x_n, r_values[i], decipher_text(padded_len, perm, padded, deciphered));
        free(perm);
    }

    // Keeping r fixed, varying x_n
    double r = 3.741;
    double x_n_values[] = {0.747, 0.7469, 0.7470078};
    for (int i = 0; i < sizeof(x_n_values) / sizeof(x_n_values[0]); i++)
    {
        int *perm = get_permutation(r, x_n_values[i]);
        printf("[x_n=%.3f, r=%.5f]:\t'%s'\n", x_n_values[i], r, decipher_text(padded_len, perm, padded, deciphered));
        free(perm);
    }

    // Varying both r and x_n
    for (int i = 0; i < sizeof(r_values) / sizeof(r_values[0]); i++)
    {
        for (int j = 0; j < sizeof(x_n_values) / sizeof(x_n_values[0]); j++)
        {
            int *perm = get_permutation(r_values[i], x_n_values[j]);
            printf("[x_n=%.3f, r=%.5f]:\t'%s'\n", x_n_values[j], r_values[i], decipher_text(padded_len, perm, padded, deciphered));
            free(perm);
        }
    }
    return 0;
}