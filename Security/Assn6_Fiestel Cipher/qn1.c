#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 400

unsigned char circular_left_shift(unsigned char key)
{
    return (key << 1) | (key >> 7);
}

int sbox(int input)
{
    switch (input)
    {
    case 0:
        return 2;
    case 1:
        return 3;
    case 2:
        return 0;
    case 3:
        return 1;
    default:
        return -1;
    }
}

unsigned char apply_sbox(unsigned char input)
{
    unsigned char output = 0;
    for (int i = 0; i < 4; i++)
    {
        int two_bits = (input >> (6 - 2 * i)) & 0x3;
        int substituted = sbox(two_bits);
        output |= (substituted << (6 - 2 * i));
    }
    return output;
}

unsigned char apply_pbox(unsigned char input, int inverse)
{
    int pbox[8] = {5, 0, 2, 6, 7, 4, 3, 1}; // pbox[i]th bit of input goes to ith bit of output
    int inv_pbox[8] = {1, 7, 2, 6, 5, 0, 3, 4};
    unsigned char output = 0;

    for (int i = 0; i < 8; i++)
    {
        int bit;
        if (inverse)
        {
            bit = (input >> (7 - inv_pbox[i])) & 1;
        }
        else
        {
            bit = (input >> (7 - pbox[i])) & 1;
        }
        output |= (bit << (7 - i));
    }

    return output;
}

char *spn_decrypt(unsigned char input[SIZE], unsigned char key)
{
    char *plain = (char *)malloc(SIZE * sizeof(char));

    unsigned char round1_key = key;
    unsigned char round2_key = circular_left_shift(key);

    for (int i = 0; i < strlen(input); i++)
    {
        unsigned char block = input[i];

        // round 1
        block = apply_pbox(block, 1);
        block = apply_sbox(block); // Inverse S-box is the same as S-box here
        block ^= round2_key;

        // round 2
        block = apply_pbox(block, 1);
        block = apply_sbox(block); // Inverse S-box is the same as S-box here
        block ^= round1_key;

        plain[i] = block;
    }
    // plain[strlen(input)] = '\0';

    return plain;
}

char *spn_encrypt(unsigned char input[SIZE], unsigned char key)
{
    char *cipher = (char *)malloc(SIZE * sizeof(char));

    unsigned char round1_key = key;
    unsigned char round2_key = circular_left_shift(key);

    for (int i = 0; i < strlen(input); i++)
    {
        unsigned char block = input[i];

        // round 1
        block ^= round1_key;
        block = apply_sbox(block);
        block = apply_pbox(block, 0);

        // round 2
        block ^= round2_key;
        block = apply_sbox(block);
        block = apply_pbox(block, 0);

        cipher[i] = block;
    }

    return cipher;
}

int main()
{
    char input[SIZE];
    unsigned char key;

    printf("Input string: ");
    scanf("%[^\n]%*c", input);
    // modify_input(&input);

    printf("Input: %s\n", input);

    printf("Key (0-255): ");
    scanf("%hhu", &key);

    char *cipher = spn_encrypt((unsigned char *)input, key);

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < strlen(input); i++)
    {
        printf("%02X ", (unsigned char)cipher[i]);
    }

    printf("\nCiphertext (in dec): ");
    for (int i = 0; i < strlen(input); i++)
    {
        printf("%d ", (unsigned char)cipher[i]);
    }
    char *plain = spn_decrypt((unsigned char *)cipher, key);
    plain[strlen(input)] = '\0';
    // printf("len: %d", (int)strlen(input));

    printf("\nDecrypted text: %s", plain);
}