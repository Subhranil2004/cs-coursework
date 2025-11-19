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
    int pbox[8] = {5, 0, 2, 6, 7, 4, 3, 1};
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

float nbcr(unsigned char *enc1, unsigned char *enc2, int length)
{
    int total_bits = length * 8;
    int diff_bits = 0;

    for (int i = 0; i < length; i++)
    {
        unsigned char xor_result = enc1[i] ^ enc2[i];
        // Count bits set to 1 in xor_result
        for (int bit = 0; bit < 8; bit++)
        {
            if (xor_result & (1 << bit))
            {
                diff_bits++;
            }
        }
    }

    return (diff_bits / (float)total_bits) * 1.0f; // percentage of differing bits
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

    printf("\nDecrypted text: %s", plain);

    // flip the first bit of the first byte of ciphertext
    char input2[SIZE];
    strcpy(input2, input);
    input2[0] ^= 0x80;

    printf("\n\nAfter flipping the first bit of the first byte of input text:\n");
    printf("Modified Input: %s\n", input2);

    char *cipher2 = spn_encrypt((unsigned char *)input2, key);

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < strlen(input2); i++)
    {
        printf("%02X ", (unsigned char)cipher2[i]);
    }

    printf("\nCiphertext (in dec): ");
    for (int i = 0; i < strlen(input2); i++)
    {
        printf("%d ", (unsigned char)cipher2[i]);
    }
    plain = spn_decrypt((unsigned char *)cipher2, key);
    plain[strlen(input2)] = '\0';

    printf("\nDecrypted text: %s", plain);

    float percent_changed = nbcr((unsigned char *)cipher, (unsigned char *)cipher2, strlen(cipher)) * 100.0f;
    printf("\nFor 1 bit flip in input text, %% of bits changed in cipher text: %f%%\n", percent_changed);

    // Small change in key
    printf("\n\nAfter flipping the first bit of key:\n");
    unsigned char key2 = key;
    key2 ^= 0x80;

    printf("Input: %s\n", input);
    char *cipher3 = spn_encrypt((unsigned char *)input, key2);
    printf("Key (0-255): %d\n", key2);

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < strlen(input); i++)
    {
        printf("%02X ", (unsigned char)cipher2[i]);
    }

    printf("\nCiphertext (in dec): ");
    for (int i = 0; i < strlen(input); i++)
    {
        printf("%d ", (unsigned char)cipher2[i]);
    }
    plain = spn_decrypt((unsigned char *)cipher3, key2);
    plain[strlen(input)] = '\0';

    printf("\nDecrypted text: %s", plain);

    percent_changed = nbcr((unsigned char *)cipher, (unsigned char *)cipher3, strlen(cipher)) * 100.0f;

    printf("\nFor 1 bit flip in key, %% of bits changed in cipher text: %f%%\n", percent_changed);
    return 0;
}