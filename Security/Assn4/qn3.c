#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_CIPHER 2000
#define MAX_KEY 30
#define TOP_KEY_CANDIDATES 8 /* how many key lengths to show */

const double english_freq[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074};

/* remove non-letters and uppercase */
void preprocess(const char *in, char *out)
{
    int j = 0;
    for (int i = 0; in[i] && j < MAX_CIPHER - 1; i++)
    {
        if (isalpha((unsigned char)in[i]))
        {
            out[j++] = toupper((unsigned char)in[i]);
        }
    }
    out[j] = '\0';
}

/* compute Index of Coincidence for a text block */
double index_of_coincidence(const char *s)
{
    int n = strlen(s);
    if (n <= 1)
        return 0.0;
    int counts[26] = {0};
    for (int i = 0; s[i]; i++)
        counts[s[i] - 'A']++;
    double sum = 0.0;
    for (int i = 0; i < 26; i++)
        sum += counts[i] * (counts[i] - 1);
    double ic = sum / ((double)n * (n - 1));
    return ic;
}

/* split ciphertext into keylen columns and compute average IC */
double avg_ic_for_keylen(const char *ctext, int keylen)
{
    int n = strlen(ctext);
    double total = 0.0;
    for (int k = 0; k < keylen; k++)
    {
        char column[MAX_CIPHER];
        int p = 0;
        for (int i = k; i < n; i += keylen)
        {
            column[p++] = ctext[i];
        }
        column[p] = '\0';
        total += index_of_coincidence(column);
    }
    return total / keylen;
}

/* compute chi-squared statistic for a candidate shift on a column */
double chi_squared_for_shift(const char *col, int shift)
{
    int counts[26] = {0};
    int n = strlen(col);
    if (n == 0)
        return 1e9;
    for (int i = 0; i < n; i++)
    {
        int val = (col[i] - 'A' - shift + 26) % 26; /* shift back */
        counts[val]++;
    }
    double chi2 = 0.0;
    for (int i = 0; i < 26; i++)
    {
        double observed = counts[i];
        double expected = english_freq[i] * n;
        double diff = observed - expected;
        chi2 += (diff * diff) / (expected + 1e-9);
    }
    return chi2;
}

/* find best shift (0..25) for given column */
int best_shift_for_column(const char *col)
{
    double bestChi = 1e18;
    int bestShift = 0;
    for (int s = 0; s < 26; s++)
    {
        double ch = chi_squared_for_shift(col, s);
        if (ch < bestChi)
        {
            bestChi = ch;
            bestShift = s;
        }
    }
    return bestShift;
}

/* derive key for a given keylen using frequency analysis */
void derive_key_for_len(const char *ctext, int keylen, char *out_key)
{
    int n = strlen(ctext);
    for (int k = 0; k < keylen; k++)
    {
        char column[MAX_CIPHER];
        int p = 0;
        for (int i = k; i < n; i += keylen)
        {
            column[p++] = ctext[i];
        }
        column[p] = '\0';
        int shift = best_shift_for_column(column);
        out_key[k] = 'A' + shift; /* shift means key letter with numeric value shift */
    }
    out_key[keylen] = '\0';
}

/* decrypt with given key */
void decrypt_with_key(const char *ctext, const char *key, char *out_plain)
{
    int n = strlen(ctext);
    int klen = strlen(key);
    for (int i = 0; i < n; i++)
    {
        int c = ctext[i] - 'A';
        int k = key[i % klen] - 'A';
        int p = (c - k + 26) % 26;
        out_plain[i] = 'A' + p;
    }
    out_plain[n] = '\0';
}

/* quick helper to print top keylength candidates by IC */
typedef struct
{
    int keylen;
    double ic;
} ic_rec;
int cmp_ic_rec(const void *a, const void *b)
{
    double da = ((ic_rec *)a)->ic;
    double db = ((ic_rec *)b)->ic;
    if (da < db)
        return 1;
    if (da > db)
        return -1;
    return 0;
}

int main(void)
{
    /* Paste your ciphertext here (can contain non-letters; they will be removed) */
    const char raw_cipher[] = "OIFZZGWRJGUIZGYUFQLPUHIJDGNVRWHYNGQRWGQYNQBZXBINWSZVWFYUYCUJHOYJFFWZUVYINHCJFBUUIWNZASWZUVYIBWNYYVYBJMMVYHIKMFYVJOWYHVUIFQNVWWMKMSJCFWHKJLNZXGBZKHYUYVLVJQBRWOWKJFMKTQLVFHYTNDBVWHYOY";

    char ctext[MAX_CIPHER];
    preprocess(raw_cipher, ctext);
    int n = strlen(ctext);
    if (n == 0)
    {
        printf("No letters in ciphertext.\n");
        return 0;
    }

    printf("Ciphertext (sanitized, N=%d):\n%s\n\n", n, ctext);

    /* compute avg IC for key lengths 1..MAX_KEY */
    ic_rec ics[MAX_KEY];
    for (int L = 1; L <= MAX_KEY; L++)
    {
        double avgic = avg_ic_for_keylen(ctext, L);
        ics[L - 1].keylen = L;
        ics[L - 1].ic = avgic;
    }
    qsort(ics, MAX_KEY, sizeof(ic_rec), cmp_ic_rec);

    printf("Top %d key-length candidates by average IC:\n", TOP_KEY_CANDIDATES);
    for (int i = 0; i < TOP_KEY_CANDIDATES && i < MAX_KEY; i++)
    {
        printf("  len=%2d  avgIC=%.5f\n", ics[i].keylen, ics[i].ic);
    }
    printf("\n");

    /* For each of the top candidates, derive key and decrypt */
    for (int idx = 0; idx < TOP_KEY_CANDIDATES && idx < MAX_KEY; idx++)
    {
        int L = ics[idx].keylen;
        char key[MAX_KEY + 1];
        derive_key_for_len(ctext, L, key);

        /* Note: key currently contains numeric shifts as letters (A=0 shift). Real key letter = 'A'+shift.
           Some people prefer to print key as A..Z where A means shift 0 (i.e., key letter 'A' would do shift 0).
        */

        char plaintext[MAX_CIPHER];
        decrypt_with_key(ctext, key, plaintext);

        printf("Candidate (keylen=%2d): key(as shift letters) = %s\n", L, key);
        /* convert key from shift-letter to printable key like 'A'..'Z' (already is) */
        printf("Decrypted text (first 400 chars):\n");
        for (int i = 0; i < (int)strlen(plaintext); i++)
        {
            putchar(plaintext[i]);
            if ((i + 1) % 80 == 0)
                putchar('\n');
        }
        putchar('\n');
        printf("----\n\n");
    }

    printf("Note: The program guesses key letters as shifts (A=shift0, B=shift1, ...).\n");
    printf("If the recovered key looks odd, try interpreting/rotating those letters\n");
    printf("or try more key lengths (increase MAX_KEY), or use Kasiski analysis for repeating sequences.\n");
    return 0;
}