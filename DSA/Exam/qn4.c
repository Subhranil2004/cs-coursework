#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left, *right;
} node;

// typedef struct record
// {
//     int turns;
//     int length;
//     int *arr;
// }record;
node *insertBST(int item, node *root)
{
    if (root == NULL)
    {
        node *new = (node *)malloc(sizeof(node));
        new->data = item;
        new->left = new->right = NULL;
        return new;
    }
    else if (item < root->data)
    {
        root->left = insertBST(item, root->left);
    }
    else
    {
        root->right = insertBST(item, root->right);
    }
    return root;
}

// Function to find the length of the path with maximum turns
int findMaxTurnsPath(node *root)
{
    if (root == NULL)
        return 0;

    // Recursively find the lengths of the left and right subtrees
    int leftPath = findMaxTurnsPath(root->left);
    int rightPath = findMaxTurnsPath(root->right);

    // Calculate the maximum between the left and right subtrees
    int maxPath = 1 + (leftPath > rightPath ? leftPath : rightPath);

    return maxPath;
}

int main()
{
    int n;
    int item;
    node *root = NULL;
    printf("Enter the no. of terms: ");
    scanf("%d", &n);
    printf("Enter the preorder traversal of BST: ");
    scanf("%d", &item);
    // node *root = (node *)malloc(sizeof(node));
    // root->data = item;
    // root->left = root->right = NULL;
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &item);
        root = insertBST(item, root);
    }

    int maxTurnsPath = findMaxTurnsPath(root);
    printf("Length of the path with maximum turns: %d\n", maxTurnsPath - 1);

    return 0;
}