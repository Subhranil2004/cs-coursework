// Encrypt/decrypt a file using offset/substitution cipher
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void offsetCipher(char src[30], char trg[30], int action, int offset)
{
    if (action == 2)
        offset = -offset;
    // printf("Offset: %d", offset);
    FILE *srcptr = fopen(src, "r");
    FILE *trgptr = fopen(trg, "w");
    char ch = fgetc(srcptr);
    while (ch != EOF)
    {
        fputc(ch + offset, trgptr);
        ch = fgetc(srcptr);
    }
    fclose(trgptr);
    fclose(srcptr);
}

int getIdx(char ch, char domain[53])
{
    for(int i=0;i<53;i++)
    {
        if(ch == domain[i])
            return i;
    }
    return -1;
}
void substitutionCipher(char src[30], char trg[30], int action, char domain[53], char codomain[53])
{
    if (action == 2)
    {
        // Swap domain and codomain
        char temp[53];
        strcpy(temp, domain);
        strcpy(domain, codomain);
        strcpy(codomain, temp);
    }
    FILE *srcptr = fopen(src, "r");
    FILE *trgptr = fopen(trg, "w");
    int idx;
    char ch = fgetc(srcptr);
    while (ch != EOF)
    {
        idx = getIdx(ch, domain);
        if (idx == -1)
            fputc(ch, trgptr);
        else
            fputc(codomain[idx], trgptr);
        ch = fgetc(srcptr);
    }
    fclose(srcptr);
    fclose(trgptr);
}
// void printFiles(char src[30], char trg[30])
// {
//     FILE *srcptr = fopen(src, "r");
//     FILE *trgptr = fopen(trg, "r");
//     printf("Printing contents:\n");
//     printf("Source file:\n");
//     while(!feof(srcptr))
//     {
//         printf("%c", fgetc(srcptr));
//     }
//     printf("\nTarget file:\n");
//     while(!feof(trgptr))
//     {
//         printf("%c", fgetc(trgptr));
//     }
// }
void printFiles(char src[30], char trg[30])
{
    FILE *srcptr = fopen(src, "r");
    FILE *trgptr = fopen(trg, "r");
    char ch;
    printf("Printing contents:\n");
    printf("Source file:\n");
    ch = fgetc(srcptr);
    while(ch!= EOF)
    {
        printf("%c", ch);
        ch = fgetc(srcptr);
    }
    printf("\nTarget file:\n");
    //fseek(trgptr, 0, SEEK_SET);
    
    while(fscanf(trgptr,"%c",&ch)!=EOF)
      printf("%c",ch); 

    printf("\n");
    fclose(srcptr);
    fclose(trgptr);
    
    // while(ch!= EOF)
    // {
    //     printf("%c", ch);
    //     ch = fgetc(trgptr);
        
    // }
}
int main()
{
    int action, cipher;
    char src[30], trg[30];
    // Mapping for substitution cipher.
    char domain[] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i',
                     'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's',
                     'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', '\0'};
    char codomain[] = {'!', '7', 'K', 'c', '3', 'L', '1', 'R', 'o', 'U', 'j', 'A', '5', 'g', 'W', 's', 'q',
                       'X', 'z', '8', '6', '9', 'B', 't', 'v', 'y', 'V', 'x', 'N', 'P', 'p', '2', 'Z', 'S', 'Y', '0', 'D',
                       'i', 'b', 'n', 'l', 'Q', 'T', 'a', 'u', 'I', 'w', 'F', 'H', '4', 'm', '\0'};

    printf("\n1. Encrypt\t2. Decrypt\n");
    printf("Choice: ");
    do
    {
        scanf("%d", &action);
    } while (action != 1 && action != 2);
    printf("\n1. Offset cipher\t2. Substitution cipher\n");
    printf("Choice: ");
    do
    {
        scanf("%d", &cipher);
    } while (cipher != 1 && cipher != 2);
    printf("Source file: ");
    scanf("%s", src);
    printf("Target file: ");
    scanf("%s", trg);

    switch (cipher)
    {
    case 1:
        offsetCipher(src, trg, action, 4);
        break;
    case 2:
        substitutionCipher(src, trg, action, domain, codomain);
        break;
    default:
        printf("Wrong choice.\n");
    }
    if (action == 1)
        printf("File encrypted!\n");
    else
        printf("File decrypted!\n");
    printFiles(src, trg);
    return 0;
}
