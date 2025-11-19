#include <stdio.h>
#include <string.h>

#define SIZE 1000

unsigned char circular_left_shift(unsigned char key)
{
    return (key << 1) | (key >> 7);
}

unsigned char des_function(unsigned char right4, unsigned char round_key)
{
    // unsigned char expanded = expansion_pbox(right4);     // 4 → 8 bits
    // unsigned char xored = expanded ^ round_key;          // XOR with key
    // unsigned char compressed = compression_sbox(xored);  // 8 → 4 bits
    // unsigned char result4 = straight_pbox_4(compressed); // permute

    return (right4 ^ round_key) & 0x0F;
}

unsigned char extract_and_square(unsigned char key)
{
    int extracted = key & 0x81;
    extracted = (extracted >> 6) | (extracted & 0x01); // extract first and last bit
    // printf("Extracted key component: %d and %hhu\n", key, extracted);
    int squared = extracted * extracted;
    // printf("Squared key component: %d and %hhu\n", squared, squared);
    return squared;
}

void encrypt(unsigned char *message, size_t len, unsigned char key, unsigned char *encrypted)
{
    unsigned char round1_key = key;
    round1_key = circular_left_shift(round1_key);
    round1_key = circular_left_shift(round1_key);
    unsigned char round2_key = circular_left_shift(round1_key);

    round1_key = extract_and_square(round1_key);
    round2_key = extract_and_square(round2_key);

    for (size_t i = 0; i < len; i++)
    {
        unsigned char block = message[i];
        unsigned char left = (block >> 4) & 0x0F;
        unsigned char right = block & 0x0F;

        unsigned char f_out1 = des_function(right, round1_key);
        unsigned char new_left = right;
        unsigned char new_right = left ^ f_out1;

        unsigned char f_out2 = des_function(new_right, round2_key);
        unsigned char final_left = new_right;
        unsigned char final_right = new_left ^ f_out2;

        encrypted[i] = (final_left << 4) | (final_right & 0x0F);
    }
}

void decrypt(unsigned char *encrypted, size_t len, unsigned char key, unsigned char *decrypted)
{
    // unsigned char round1_key = circular_left_shift(key);
    // round1_key = circular_left_shift(key);
    // unsigned char round2_key = circular_left_shift(round1_key);
    unsigned char round1_key = key;
    round1_key = circular_left_shift(round1_key);
    round1_key = circular_left_shift(round1_key);
    unsigned char round2_key = circular_left_shift(round1_key);

    round1_key = extract_and_square(round1_key);
    round2_key = extract_and_square(round2_key);

    for (size_t i = 0; i < len; i++)
    {
        unsigned char block = encrypted[i];
        unsigned char left2 = (block >> 4) & 0x0F;
        unsigned char right2 = block & 0x0F;

        unsigned char right1 = left2;
        unsigned char f2 = des_function(right1, round2_key);
        unsigned char left1 = right2 ^ f2;

        unsigned char right0 = left1;
        unsigned char f1 = des_function(right0, round1_key);
        unsigned char left0 = right1 ^ f1;

        decrypted[i] = (left0 << 4) | (right0 & 0x0F);
    }
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
    size_t len = strlen(input);

    printf("Input: %s\n", input);

    printf("Key (0-255): ");
    scanf("%hhu", &key);

    unsigned char cipher1[SIZE];
    unsigned char cipher2[SIZE];
    unsigned char cipher3[SIZE];
    unsigned char plain[SIZE];

    encrypt((unsigned char *)input, len, key, cipher1);

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < strlen(input); i++)
    {
        printf("%02X ", (unsigned char)cipher1[i]);
    }

    printf("\nCiphertext (in dec): ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", (unsigned char)cipher1[i]);
    }
    decrypt(cipher1, len, key, plain);
    plain[len] = '\0';

    printf("\nDecrypted text: %s", plain);

    // flip the first bit of the first byte of ciphertext
    char input2[SIZE];
    strcpy(input2, input);
    input2[0] ^= 0x80;

    printf("\n\nAfter flipping the first bit of the first byte of input text:\n");
    printf("Modified Input: %s\n", input2);

    encrypt((unsigned char *)input2, len, key, cipher2);

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < len; i++)
    {
        printf("%02X ", (unsigned char)cipher2[i]);
    }

    printf("\nCiphertext (in dec): ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", (unsigned char)cipher2[i]);
    }
    decrypt(cipher2, len, key, plain);
    plain[len] = '\0';
    printf("\nDecrypted text: %s", plain);

    float percent_changed = nbcr((unsigned char *)cipher1, (unsigned char *)cipher2, len) * 100.0f;
    printf("\nFor 1 bit flip in input text, %% of bits changed in cipher text: %f%%\n", percent_changed);

    // Small change in key
    printf("\n\nAfter flipping the first bit of key:\n");
    unsigned char key2 = key;
    key2 ^= 0x80;

    printf("Input: %s\n", input);
    printf("Key (0-255): %d\n", key2);
    encrypt((unsigned char *)input, len, key2, cipher3);

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < len; i++)
    {
        printf("%02X ", (unsigned char)cipher3[i]);
    }

    printf("\nCiphertext (in dec): ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", (unsigned char)cipher3[i]);
    }
    decrypt((unsigned char *)cipher3, len, key2, plain);
    plain[len] = '\0';

    printf("\nDecrypted text: %s", plain);

    percent_changed = nbcr((unsigned char *)cipher1, (unsigned char *)cipher3, len) * 100.0f;

    printf("\nFor 1 bit flip in key, %% of bits changed in cipher text: %f%%\n", percent_changed);
    return 0;
}

/*
Unused functions
Use these to see a percentage change in bits for 1 bit flip in key. otherwise the change is 0% for the current keygen method.

unsigned char expansion_pbox(unsigned char input)
{
    int ebox[8] = {3, 0, 1, 2, 1, 2, 3, 0};
    unsigned char output = 0;
    for (int i = 0; i < 8; i++)
    {
        int bit = (input >> (3 - ebox[i])) & 1;
        output |= (bit << (7 - i));
    }
    return output;
}

unsigned char compression_sbox(unsigned char input)
{
    int sbox_table[16] = {2, 0, 3, 1, 3, 2, 1, 0, 1, 3, 0, 2, 0, 1, 2, 3};

    unsigned char left4 = (input >> 4) & 0x0F;
    unsigned char right4 = input & 0x0F;

    unsigned char left2 = sbox_table[left4] & 0x03;
    unsigned char right2 = sbox_table[right4] & 0x03;

    unsigned char combined = (left2 << 2) | right2;
    return combined & 0x0F;
}

unsigned char straight_pbox_4(unsigned char input)
{
    int pbox[4] = {2, 0, 3, 1};
    unsigned char output = 0;
    for (int i = 0; i < 4; i++)
    {
        int bit = (input >> (3 - pbox[i])) & 1;
        output |= (bit << (3 - i));
    }
    return output & 0x0F;
}

*/