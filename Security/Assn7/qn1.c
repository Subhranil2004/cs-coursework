#include <stdio.h>

/* AES affine matrix as bits (rows x cols) */
static const unsigned char AFFINE[8][8] = {
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 1, 1}};

#define AFFINE_CONST 0x63 /* 0x63 = 0110 0011 in AES */

/* Multiply two bytes in GF(2^8) with AES polynomial reduction 0x11B */
static unsigned char gf_mul(unsigned char a, unsigned char b)
{
    unsigned char res = 0;
    while (b)
    {
        if (b & 1)
            res ^= a;
        unsigned char hi = a & 0x80;
        a <<= 1;
        if (hi)
            a ^= 0x1B; /* reduction polynomial */
        b >>= 1;
    }
    return res;
}

/* Fast exponentiation a^e in GF(2^8) using gf_mul */
static unsigned char gf_pow(unsigned char a, unsigned int e)
{
    unsigned char result = 1;
    unsigned char base = a;
    while (e)
    {
        if (e & 1)
            result = gf_mul(result, base);
        base = gf_mul(base, base);
        e >>= 1;
    }
    return result;
}

/* Multiplicative inverse in GF(2^8): x^(254) for x != 0; by convention inverse(0)=0 */
static unsigned char gf_inv(unsigned char x)
{
    if (x == 0)
        return 0;
    return gf_pow(x, 254); /* 2^8 - 2 = 254 */
}

/* Apply AES affine transform (A * x) XOR constant */
static unsigned char affine_transform(unsigned char x)
{
    unsigned char out = 0;
    int row, col;
    for (row = 0; row < 8; ++row)
    {
        int bit = 0;
        for (col = 0; col < 8; ++col)
        {
            if (AFFINE[row][col])
                bit ^= ((x >> col) & 1);
        }
        bit ^= ((AFFINE_CONST >> row) & 1);
        out |= (unsigned char)(bit << row);
    }
    return out;
}

/* Build S-box and inverse S-box tables */
static void build_sboxes(unsigned char sbox[256], unsigned char invsbox[256])
{
    int i;
    for (i = 0; i < 256; ++i)
    {
        unsigned char inv = gf_inv((unsigned char)i);
        sbox[i] = affine_transform(inv);
    }
    for (i = 0; i < 256; ++i)
        invsbox[i] = 0;
    for (i = 0; i < 256; ++i)
        invsbox[sbox[i]] = (unsigned char)i;
}

/* SubBytes: apply sbox to each of 16 state bytes */
static void sub_bytes(unsigned char state[16], const unsigned char sbox[256])
{
    int i;
    for (i = 0; i < 16; ++i)
        state[i] = sbox[state[i]];
}

/* InvSubBytes: apply inverse sbox */
static void inv_sub_bytes(unsigned char state[16], const unsigned char invsbox[256])
{
    int i;
    for (i = 0; i < 16; ++i)
        state[i] = invsbox[state[i]];
}

/* Print state */
static void print_state(const char *label, unsigned char state[16])
{
    int i;
    printf("%s", label);
    for (i = 0; i < 16; ++i)
        printf("%02X ", state[i]);
    printf("\n");
}

int main(void)
{
    unsigned char S[256], InvS[256];
    build_sboxes(S, InvS);

    /* example 16-byte AES state (order doesn't matter for SubBytes) */
    unsigned char state[16] = {
        0x32, 0x88, 0x31, 0xE0,
        0x43, 0x5A, 0x31, 0x37,
        0xF6, 0x30, 0x98, 0x07,
        0xA8, 0x8D, 0xA2, 0x34};

    print_state("Original:\t\t", state);

    /* Do SubBytes once (as a round operation) */
    sub_bytes(state, S);
    print_state("After SubBytes:\t\t", state);
    /* Undo with InvSubBytes to get the original state back */
    inv_sub_bytes(state, InvS);
    print_state("After InvSubBytes:\t", state);

    return 0;
}