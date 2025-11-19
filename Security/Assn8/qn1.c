/* cyclic_rsa_simple.c
   Iteratively applies f(x) = x^e mod N starting from ciphertext.
   Detects when a value repeats (cycle detection).
*/

#include <stdio.h>
#include <stdlib.h>

#define E 13
#define N 68681
#define START_CIPHERTEXT 56210

/* Simple modular exponentiation using long long only */
long long mod_exp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;

    while (exp > 0)
    {
        if (exp % 2 == 1) // if exponent is odd
            result = (result * base) % mod;

        base = (base * base) % mod; // square base
        exp /= 2;
    }
    return result;
}

int main(void)
{
    long long current = START_CIPHERTEXT;

    printf("Iterating f(x) = x^%d mod %d\n", E, N);
    printf("Starting with ciphertext = %d\n\n", START_CIPHERTEXT);

    long long round = 0;

    while (1)
    {
        round++;

        long long next_value = mod_exp(current, E, N);

        /* Check if this result appeared before */
        if (next_value == START_CIPHERTEXT)
        {
            printf("Round %lld: %lld\n", round, next_value);

            printf("\nCycle detected!\n");
            printf("Cycle length = %d\n", round);
            printf("Plaintext recovered = %lld for ciphertext %lld\n", current, START_CIPHERTEXT);

            break;
        }

        printf("Round %lld: %lld\n", round, next_value);

        current = next_value; // continue iterating
    }

    return 0;
}