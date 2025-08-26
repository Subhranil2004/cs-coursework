#include <stdio.h>
#include <stdlib.h>

typedef struct bnode
{
    int data;
    struct bnode *left, *right;
} bnode;

bnode *insertBST(bnode *root, int num)
{
    if (root == NULL)
    {
        root = malloc(sizeof(bnode));
        root->data = num;
        root->left = root->right = NULL;
    }
    else if (num < root->data)
        root->left = insertBST(root->left, num);
    else
        root->right = insertBST(root->right, num);
    return root;
}

void inOrder(bnode *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void preOrder(bnode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(bnode *root)
{
    if (root == NULL)
        return;

    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

bnode *insertCBT(int arr[500], int idx, int size)
{
    bnode *bn = NULL;
    if (idx < size)
    {
        bn = malloc(sizeof(bnode));
        bn->data = arr[idx];
        bn->left = insertCBT(arr, 2 * idx + 1, size);
        bn->right = insertCBT(arr, 2 * idx + 2, size);
    }
    return bn;
}

int main()
{
    int n, i, num;
    bnode *rootCBT, *rootBST;
    int arr[500];
    rootBST = NULL;
    rootCBT = NULL;
    printf("Enter the number of integers: ");
    scanf("%d", &n);
    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
        rootBST = insertBST(rootBST, num);
    }
    printf("\nBinary Search Tree generated.\n");
    printf("In-order traversal: ");
    inOrder(rootBST);
    printf("\nPre-order traversal: ");
    preOrder(rootBST);
    printf("\nPost-order traversal: ");
    postOrder(rootBST);

    rootCBT = insertCBT(arr, 0, n);
    printf("\n\nComplete Binary Tree generated.\n");
    printf("In-order traversal: ");
    inOrder(rootCBT);
    printf("\nPre-order traversal: ");
    preOrder(rootCBT);
    printf("\nPost-order traversal: ");
    postOrder(rootCBT);
    printf("\n");
}
