#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 200

void build_matrix(char keyM[5][5], int pos[26][2])
{
    char *key = "HELLOWORLD";
    int vis[26] = {0};

    int i = 0, j = 0;
    for (int k = 0; k < strlen(key); k++)
    {
        if (key[k] == 'J')
            key[k] = 'I'; // Replace J with I
        if (isalpha(key[k]) && !vis[key[k] - 'A'])
        {
            vis[key[k] - 'A'] = 1;
            keyM[i][j] = key[k];
            pos[key[k] - 'A'][0] = i;
            pos[key[k] - 'A'][1] = j;
            j++;
            if (j == 5)
            {
                j = 0;
                i++;
            }
        }
    }

    vis['J' - 'A'] = 1; // J is omitted
    int ch = 0;
    for (; i < 5; i++)
    {
        for (; j < 5; j++)
        {
            while (vis[ch] == 1)
                ch++; // find next unvisited character
            keyM[i][j] = 'A' + ch;
            pos[ch][0] = i;
            pos[ch][1] = j;
            vis[ch] = 1;
        }
        j = 0;
    }
    pos['J' - 'A'][0] = pos['I' - 'A'][0];
    pos['J' - 'A'][1] = pos['I' - 'A'][1];

    printf("Key Matrix:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            printf("%c ", keyM[i][j]);
        printf("\n");
    }
}

char *generate_digraphs(char arr[])
{
    int len = strlen(arr);
    char *temp = malloc(sizeof(char) * (2 * len + 1));
    int idx = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(arr[i]))
        {
            arr[i] = toupper(arr[i]);
            if (arr[i] == 'J')
            {
                temp[idx++] = 'I'; // Replace J with I
            }
            else
            {
                temp[idx++] = arr[i];
            }
        }
    }
    temp[idx] = '\0';

    char *digraphs = malloc(sizeof(char) * (2 * idx + 1));
    int digraph_idx = 0;
    for (int i = 0; i < idx; i++)
    {
        digraphs[digraph_idx++] = temp[i];
        if (i + 1 < idx && temp[i] == temp[i + 1])
        {
            digraphs[digraph_idx++] = 'X'; // Insert X between same letters
        }
        else if (i + 1 < idx)
        {
            digraphs[digraph_idx++] = temp[++i];
        }
        else
        {
            digraphs[digraph_idx++] = 'X'; // Padding if single letter left
        }
    }
    digraphs[digraph_idx] = '\0';
    free(temp);

    // Uncomment below line to print the digraphs
    printf("Digraphs: ");
    for (int i = 0; i < digraph_idx; i += 2)
    {
        printf("%c%c ", digraphs[i], digraphs[i + 1]);
    }
    printf("\n");
    return digraphs;
}

char *playfair_decrypt(char arr[])
{
    char keyM[5][5];
    int pos[26][2];
    build_matrix(keyM, pos);

    char *digraphs = generate_digraphs(arr);
    int len = strlen(digraphs);

    char *cipher = malloc(sizeof(char) * len + 1);
    int i = 0;
    for (; digraphs[i] != '\0'; i += 2)
    {
        int row1 = pos[digraphs[i] - 'A'][0];
        int col1 = pos[digraphs[i] - 'A'][1];
        int row2 = pos[digraphs[i + 1] - 'A'][0];
        int col2 = pos[digraphs[i + 1] - 'A'][1];

        if (row1 == row2)
        {
            cipher[i] = keyM[row1][(col1 + 4) % 5];
            cipher[i + 1] = keyM[row2][(col2 + 4) % 5];
        }
        else if (col1 == col2)
        {
            cipher[i] = keyM[(row1 + 4) % 5][col1];
            cipher[i + 1] = keyM[(row2 + 4) % 5][col2];
        }
        else
        {
            cipher[i] = keyM[row1][col2];
            cipher[i + 1] = keyM[row2][col1];
        }
    }
    cipher[i] = '\0';
    return cipher;
}

int main()
{
    int n = 26;

    char cipher[SIZE] = "LFGDNWDPWOCV";
    printf("Cipher Text: %s\n", cipher);

    char *decipher = playfair_decrypt(cipher);
    printf("Deciphered Text: %s\n", decipher);
    free(decipher);

    return 0;
}