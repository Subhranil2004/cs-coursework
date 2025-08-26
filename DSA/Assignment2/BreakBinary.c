#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
int main()
{
    FILE *fptr;
    char fpath[100];
    char ch;
    int i, j, k, cnt, n;
    char str[SIZE];
    char substrings[SIZE][5];
    char sub[5];
    int freq;
    short flag[SIZE];
    char abc[SIZE];
    printf("Enter the relative filepath : ");
    // For testing with the sample provided just type "Sample.txt" without quotes.
    scanf("%s", fpath);
    while (fpath == " " || fpath == "\n")
        scanf("%s", fpath);
    fptr = fopen(fpath, "r");
    if (fptr == NULL)
    {
        printf("File can't be opened. Exiting...");
        exit(0);
    }
    fscanf(fptr, "%s", str);
    printf("The first binary array in the file :\n%s\n", str);
    fclose(fptr); // Closing the Sample.txt file as its contents are now stored in str.

    printf("\nEnter the value of n = ");
    scanf("%d", &n);
    k = 0; // Initializing the index of the String array : 'substrings' as 0.
    for (i = 0; i < strlen(str); k++)
    {
        // cnt --> Counts the characters in a substring
        for (cnt = 0; i < strlen(str) && cnt < n; i++)
        {

            if (str[i] == '0' && (cnt == 0 || sub[cnt - 1] == '0'))
            {
                sub[cnt] = '0';
                cnt++;
            }
            else if (str[i] == '1')
            {
                if (cnt != 0 && sub[cnt - 1] == '0')
                {
                    sub[cnt] = '1';
                    cnt++;
                    i++;
                    break;
                }
                else // Condition when '1' is found at the 1st position of substring
                {
                    sub[cnt] = '1';
                    cnt++;
                    i++; // see
                    for (j = 1; j < n && (i + j - 1) < strlen(str); j++)
                        if (str[i + j - 1] == '0')
                            break;
                    if (j == n) // For n consecitive '1's
                    {
                        for (j = 1; j < n; j++)
                        {
                            sub[j] = str[i + j - 1];
                            cnt++;
                        }
                        i += n - 2;
                    }
                    else
                        break;
                }
            }
        }
        sub[cnt] = '\0';
        strcpy(substrings[k], sub);
    }
    k -= 1; // k now stores the no. of substrings generated

    sub[0] = substrings[k][0]; // Check if '0's need to be appended at the end
    cnt = strlen(substrings[k]);
    for (i = 1; i < cnt; i++)
        if (substrings[k][i] != sub[0])
            break;

    if (i == cnt && cnt != n)
    {
        printf("%d 0(s) is/are appended at the end of last substring.\n", n - cnt);
        while (cnt != n)
        {
            substrings[k][cnt] = sub[0];
            cnt++;
        }
        substrings[k][cnt] = '\0';
    }

    printf("The %d valid substrings generated are :\n", k + 1);
    for (i = 0; i <= k; i++)
    {
        printf("%s ", substrings[i]);

        flag[i] = 0; // Initializing flag[] for frequency calculation

        // Writing in abc[] the corresponding character simultaneously
        if (!strcmp(substrings[i], "1"))
            abc[i] = 'A';
        else if (!strcmp(substrings[i], "01"))
            abc[i] = 'B';
        else if (!strcmp(substrings[i], "001"))
            abc[i] = 'C';
        else if (!strcmp(substrings[i], "0001"))
            abc[i] = 'D';
        else if (!strcmp(substrings[i], "0000") || !strcmp(substrings[i], "000") || !strcmp(substrings[i], "00"))
            abc[i] = 'E';
        else
            abc[i] = 'F';
    }
    abc[i] = '\0';

    printf("\n\nThe frequency of each of the substrings :\n");
    for (i = 0; i <= k; i++)
    {
        if (flag[i] == 1)
            continue;
        freq = 1;
        for (j = i + 1; j <= k; j++)
        {
            if (strcmp(substrings[j], substrings[i]) == 0)
            {
                freq++;
                flag[j] = 1; // Flipping flag[i] to denote that the substring is already checked.
            }
        }
        printf("%4s : %hi\n", substrings[i], freq);
    }
    printf("\nThe Character array so formed after replacing each substring : %s\n", abc);

    strcpy(fpath, "Alphabets.txt"); // Setting file path to store the Character array
    fptr = fopen(fpath, "w");
    fprintf(fptr, "%s", abc);
    fclose(fptr);
    printf("Successfully written in %s file.\n", fpath);
    
    printf("\nThe length of Binary array : %d\nThe length of Character array : %d\n", strlen(str), strlen(abc));
    printf("Thus, the %% reduction of length = %f %%.\n", 100 * (1 - (float)strlen(abc) / strlen(str)));
    return 0;
}
