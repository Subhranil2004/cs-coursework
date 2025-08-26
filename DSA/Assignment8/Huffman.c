// Huffman Coding in C

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_TREE_HT 50

struct MinHNode
{
    char item;
    unsigned freq;
    struct MinHNode *left, *right;
};

struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHNode **array;
};

typedef struct record
{
    char ch;
    int freq;
    char code[100];//????
} record;
// Create nodes
struct MinHNode *newNode(char item, unsigned freq)
{
    struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;

    return temp;
}

// Create min heap
struct MinHeap *createMinH(unsigned capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
    return minHeap;
}

// Function to swap
void swapMinHNode(struct MinHNode **a, struct MinHNode **b)
{
    struct MinHNode *t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size if 1
int checkSizeOne(struct MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

// Extract min
struct MinHNode *extractMin(struct MinHeap *minHeap)
{
    struct MinHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// Insertion function
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(struct MinHNode *root)
{
    return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(record table[], int size)
{
    struct MinHeap *minHeap = createMinH(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(table[i].ch, table[i].freq);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

struct MinHNode *buildHuffmanTree(record table[], int size)
{
    struct MinHNode *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(table, size);

    while (!checkSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void insertCodeInTable(char ch, char code[], record table[], int size)
{
    for(int i=0;i<size;i++)
    {
        if(table[i].ch == ch)
        {
            strcpy(table[i].code, code);
            return;
        }
    }
}
void generateHCodes(struct MinHNode *root, char *code, record table[], int size)
{
    if (root->left)
    {
        
        char reset[100];
        strcpy(reset, code);
        
        strcat(code, "0");
        
        
        generateHCodes(root->left, code, table, size);
        strcpy(code, reset);
        
    }
    if (root->right)
    {
        char reset[100];
        strcpy(reset, code);
        strcat(code, "1");
        
        
        generateHCodes(root->right, code, table, size);
        strcpy(code, reset);
        
    }
    if (isLeaf(root))
    {
        insertCodeInTable(root->item, code, table, size);
    }
}

// Wrapper function
void HuffmanCodes(record table[], int size)
{
    struct MinHNode *root = buildHuffmanTree(table, size);

    int arr[MAX_TREE_HT], top = 0;

    generateHCodes(root, (char *)calloc(100, sizeof(char)), table, size);
}
int generateFrequency(char file[], record table[])
{
    FILE *fp;
    char ch;
    int count = 0;
    int idx;
    if ((fp = fopen(file, "r")) == NULL)
    {
        printf("File couldn't be opened.Exiting...\n");
        exit(0);
    }
    while (fscanf(fp, "%c", &ch) != EOF)
    {
        idx = count;
        for (int i = 0; i < count; i++)
        {
            if (table[i].ch == ch)
            {
                idx = i;
                break;
            }
        }
        table[idx].freq++;
        if (idx == count)
        {
            table[idx].ch = ch;
            count++;
        }
    }
    fclose(fp);
    return count;
}
void printTable(record table[], int size)
{
    printf("Char\tFrequency\tHuffman_Code\n");
    printf("----\t---------\t------------\n");
    for(int i=0;i<size;i++)
    {
        printf(" '%c'\t   %d\t\t%s\n", table[i].ch, table[i].freq, table[i].code);
    }
}
int main()
{
    char text[800], file[20], *coded = "coded.txt";
    int size = 0;
    int origSize = 0, codedSize=0;
    printf("Text file: ");
    scanf("%s", file);
	printf("\n[NOTE: Characters with same frequencies might have swapped codes in different implementations.]\n");
    record *table = calloc(50, sizeof(record));
    size = generateFrequency(file, table);
    // realloc?
    HuffmanCodes(table, size);
    printTable(table, size);

    for(int i=0;i<size;i++)
    {
        codedSize += table[i].freq*strlen(table[i].code);
        origSize += table[i].freq;
    }
    printf("\nNo. of characters in original text file: %d\n", origSize);
    printf("No. of characters in coded text file: %d", codedSize);
    origSize*=8;
    printf("\nOriginal file size: %d bits.\n", origSize);
    printf("Coded file size: %d bits.\n", codedSize);
    printf("Reduction %% of file size: %f%%", (1 - (float)codedSize/origSize)*100.0);
    return 0;
}
