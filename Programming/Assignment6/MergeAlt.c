// merges lines alternatively from two files
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp1, *fp2, *mergedFile;
    char line1[1000], line2[1000];
    char file1[20], file2[20];
    printf("File1: ");
    scanf("%s", file1);
    fp1 = fopen(file1, "r");
    if (fp1 == NULL) {
        printf("Failed to open file for reading.\n");
        return 1;
    }

    printf("File2: ");
    scanf("%s", file2);
    fp2 = fopen(file2, "r");
    if (fp2 == NULL) {
        fclose(fp1);
        printf("Failed to open file for reading.\n");
        return 1;
    }

    mergedFile = fopen("mergedFile.txt", "w");
    // if (mergedFile == NULL) {
    //     fclose(fp1);
    //     fclose(fp2);
    //     printf("Failed to open mergedFile.txt for writing.\n");
    //     return 1;
    // }

    while (1) {
        if (fgets(line1, sizeof(line1), fp1) != NULL) {
            fputs(line1, mergedFile);
            // fputc('\n',mergedFile);
        }

        if (fgets(line2, sizeof(line2), fp2) != NULL) {
            fputs(line2, mergedFile);
            //   fputc('\n',mergedFile);
        }

        if (feof(fp1) && feof(fp2)) {
            break;
        }
    }

    printf("Merging completed and saved to mergeFile.txt.\n");

    fclose(fp1);
    fclose(fp2);
    fclose(mergedFile);

    return 0;
}
