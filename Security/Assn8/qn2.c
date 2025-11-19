/* rsa_signature_with_hash_demo.c
   Educational RSA signature demo that:
    - creates a small RSA keypair (demo primes)
    - computes a simple message hash (toy hash)
    - signs the hash with the private key: s = (hash mod N)^d mod N
    - verifies by computing v = s^e mod N and comparing v to (hash mod N)

   NOTE: This code is for teaching only. Do NOT use this in production.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Basic helpers ---------- */

/* gcd */
unsigned long gcd_ul(unsigned long a, unsigned long b)
{
    while (b != 0)
    {
        unsigned long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/* extended gcd: iterative */
unsigned long extended_gcd(unsigned long a, unsigned long b, long *x, long *y)
{
    long x0 = 1, y0 = 0;
    long x1 = 0, y1 = 1;
    unsigned long aa = a, bb = b;

    while (bb != 0)
    {
        unsigned long q = aa / bb;
        unsigned long r = aa % bb;

        aa = bb;
        bb = r;

        long tmpx = x0 - (long)q * x1;
        x0 = x1;
        x1 = tmpx;

        long tmpy = y0 - (long)q * y1;
        y0 = y1;
        y1 = tmpy;
    }

    if (x)
        *x = x0;
    if (y)
        *y = y0;
    return aa; /* gcd */
}

/* modular inverse using extended gcd; returns 0 if inverse does not exist */
unsigned long modinv(unsigned long a, unsigned long m)
{
    long x, y;
    unsigned long g = extended_gcd(a, m, &x, &y);
    if (g != 1)
        return 0;
    long inv = x % (long)m;
    if (inv < 0)
        inv += m;
    return (unsigned long)inv;
}

/* safe modular multiplication (avoid overflow) using addition-and-doubling */
unsigned long mod_mul(unsigned long a, unsigned long b, unsigned long mod)
{
    a %= mod;
    unsigned long result = 0;
    while (b > 0)
    {
        if (b & 1UL)
        {
            result += a;
            if (result >= mod)
                result -= mod;
        }
        /* double a */
        a <<= 1;
        if (a >= mod)
            a -= mod;
        b >>= 1;
    }
    return result % mod;
}

/* modular exponentiation using mod_mul */
unsigned long mod_pow(unsigned long base, unsigned long exp, unsigned long mod)
{
    unsigned long result = 1 % mod;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1UL)
            result = mod_mul(result, base, mod);
        base = mod_mul(base, base, mod);
        exp >>= 1;
    }
    return result;
}

/* ---------- Simple (toy) message hash ----------
   We implement a tiny, deterministic non-cryptographic hash (djb2-like).
   Returns an unsigned long hash value. For real systems use SHA-256.
*/
unsigned long simple_hash(const char *msg)
{
    unsigned long h = 5381UL;
    for (size_t i = 0; msg[i] != '\0'; ++i)
    {
        /* h = h * 33 + c  (djb2 style) */
        h = (h * 33UL) + (unsigned char)msg[i];
    }
    return h;
}

int main()
{
    /* small demo primes (toy only) */
    unsigned long p = 263UL;
    unsigned long q = 271UL;
    unsigned long N = p * q;
    unsigned long phi = (p - 1UL) * (q - 1UL);

    printf("Demo primes: p=%lu, q=%lu\n", p, q);
    printf("Modulus N = %lu\n", N);
    printf("phi(N)  = %lu\n\n", phi);

    /* choose public exponent e */
    unsigned long e = 65537UL;
    if (gcd_ul(e, phi) != 1UL)
    {
        unsigned long cand[] = {3UL, 5UL, 17UL, 257UL};
        int found = 0;
        for (int i = 0; i < 4; ++i)
        {
            if (gcd_ul(cand[i], phi) == 1UL)
            {
                e = cand[i];
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("No suitable e found. Exiting demo.\n");
            return;
        }
    }
    printf("Public exponent e = %lu\n", e);

    /* compute d = e^{-1} mod phi */
    unsigned long d = modinv(e, phi);
    if (d == 0UL)
    {
        printf("Could not compute modular inverse of e. Exiting.\n");
        return;
    }
    printf("Private exponent d = %lu\n\n", d);

    /* Read message from user (single line) */
    char message[1024];
    printf("Enter a message to sign (one line):\n> ");
    if (!fgets(message, sizeof(message), stdin))
    {
        printf("Error reading message. Exiting.\n");
        return;
    }
    /* strip newline */
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n')
        message[len - 1] = '\0';

    /* compute hash of the message (toy hash) */
    unsigned long h = simple_hash(message);
    printf("\nToy hash (unsigned long)   = %lu\n", h);

    /* reduce hash modulo N so it fits the textbook RSA domain */
    unsigned long h_mod = h % N;
    printf("Hash reduced modulo N     = %lu\n\n", h_mod);

    /* ---------- Signing (private key operation) ----------
       Signature s = (h_mod)^d mod N
       This is equivalent to "encrypting the hash with the sender's private key".
    */
    unsigned long signature = mod_pow(h_mod, d, N);
    printf("Signature (decimal) s (private key encrypted hash) = %lu\n", signature);

    /* ---------- Verification (public key operation) ----------
       Verify by computing v = s^e mod N; if v == h_mod, signature is valid.
       This is like "decrypting the signature with the sender's public key".
    */
    unsigned long recovered = mod_pow(signature, e, N);
    printf("Decrypted signature (s^e mod N) = %lu\n", recovered);

    if (recovered == h_mod)
    {
        printf("\nSignature VERIFIED: recovered hash matches original hash modulo N.\n");
    }
    else
    {
        printf("\nSignature FAILED: recovered hash does NOT match original hash modulo N.\n");
    }
}
