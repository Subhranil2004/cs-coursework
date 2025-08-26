// Sorts the names into alphabetical order. Format (Title, Name Age). 
#include<stdio.h>
#include<string.h>
#include<ctype.h>
void sortNames(char names[][50], int *ages, int n);
int compare(char *name1, char *name2);
void display(char names[][50], int *ages, int n);
int main()
{
    int n;
    char name[50];
    
    printf("Enter the no. of names: ");
    scanf("%d", &n);
    char names[100][50];
    int ages[100];
    for(int i=0;i<n;i++)
    {
        printf("Name %d: ", i+1);
        scanf("%s %s", name, names[i]);// Storing the last name first and first name in another var.
        strcat(names[i], ", ");
        strcat(names[i], name);

        printf("Age: ");
        scanf("%d", &ages[i]);
    }
    printf("Original list\n");
    printf("-------------\n");
    display(names, ages, n);
    sortNames(names, ages, n);
    printf("\nAlphabetized list\n");
    printf("-----------------\n");
    display(names, ages, n);
    return 0;
}
void sortNames(char names[][50], int *ages, int n)
{
    // Insertion sort implementation
    int i, j;
    char nkey[50];
    int akey; // !Always use keys in this sort
    for(i=1;i<n;i++)
    {
        strcpy(nkey, names[i]);
        akey = ages[i];
        for(j=i-1;j>=0 && compare(nkey, names[j]) == -1;j--)
        {
                strcpy(names[j+1], names[j]);
                ages[j+1] = ages[j];
        }
        strcpy(names[j+1], nkey);
        ages[j+1] = akey;
    }
}
int compare(char *name1, char *name2)
{
    int i,j;
    if(name1 == name2)
        return 0;
    for(i=0, j=0;;i++, j++)
    {
        if(name1[i] == ',')
        {
            i+=2;
        }
        if(name2[j] == ',')
        {
            j+=2;
        }
        if(toupper(name1[i])< toupper(name2[j]))
            return -1;
        else if(toupper(name1[i])> toupper(name2[j]))
            return 1;
    }
    // return 0;
}
void display(char names[][50], int *ages, int n)
{
    for(int i=0;i<n;i++)
        printf("%s %d\n", names[i], ages[i]);
}
