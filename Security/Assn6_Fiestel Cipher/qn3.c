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

int main()
{
    char message[SIZE];
    unsigned char key;

    printf("Enter the message to be encrypted: ");
    scanf("%[^\n]%*c", message); // Read string with spaces and consume newline

    printf("Enter 8-bit key (0-255): ");
    scanf("%hhu", &key);

    size_t len = strlen(message);

    unsigned char encrypted[SIZE];
    unsigned char decrypted[SIZE];

    encrypt((unsigned char *)message, len, key, encrypted);

    printf("\nEncrypted bytes (hex): ");
    for (size_t i = 0; i < len; i++)
        printf("%02X ", encrypted[i]);
    printf("\n");

    printf("\nEncrypted bytes (dec): ");
    for (size_t i = 0; i < len; i++)
        printf("%d ", encrypted[i]);
    printf("\n");

    decrypt(encrypted, len, key, decrypted);
    decrypted[len] = '\0';

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}

/*
Unused functions

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