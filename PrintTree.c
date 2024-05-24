#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// Definition of the tree node
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to calculate the height of the tree
int treeHeight(struct Node *root)
{
    if (root == NULL)
        return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return fmax(leftHeight, rightHeight) + 1;
}

// Helper function to fill the 3D array with tree nodes
void fillArray(struct Node *root, char ***arr, int row, int col, int width, int arrBegining)
{
    if (root == NULL)
        return;

    // Place the current node
    sprintf(arr[row][col + arrBegining], "%.5d", root->data);

    // Fill left and right subtrees
    fillArray(root->left, arr, row + 1, width / 4, width / 2, arrBegining);
    fillArray(root->right, arr, row + 1, width / 4, width / 2, col + arrBegining + 1);
}

// Function to print the 3D array representing the tree
void printTree(struct Node *root)
{
    if (root == NULL)
        return;

    int height = treeHeight(root);
    int width = pow(2, height) - 1;

    // Allocate memory for the 3D array
    char ***arr = (char ***)malloc(height * sizeof(char **));
    for (int i = 0; i < height; i++)
    {
        arr[i] = (char **)malloc((width + 1) * sizeof(char *)); // Include space for null-terminating character
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = (char *)malloc(6 * sizeof(char)); // Allocate space for up to 5 characters and a null-terminating character
            strcpy(arr[i][j], "     ");                   // Initialize with spaces
        }
    }

    // Fill the array with tree nodes
    fillArray(root, arr, 0, width / 2, width, 0);

    // Print the 3D array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%s", arr[i][j]);
        }
        printf("\n");

        // Print '|' under all numbers and '-' to link the pips
        if (i < height - 1)
        {
            bool isUnderscor = false;
            for (int j = 0; j < width; j++)
            {
                if (!isUnderscor && arr[i + 1][j][2] != ' ')
                {
                    isUnderscor = true;
                    printf("  ---");
                }
                else if (isUnderscor && arr[i + 1][j][2] != ' ')
                {
                    printf("---  ");
                    isUnderscor = false;
                }
                else if (arr[i][j][2] != ' ')
                {
                    printf("  |  ");
                }
                else if (isUnderscor)
                {
                    printf("-----");
                }
                else
                {
                    printf("     ");
                }
            }
            printf("\n");
        }
    }

    // Free the allocated memory
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
}

int main()
{
    // Creating a sample tree
    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    root->left->left->left = createNode(8);
    root->left->left->right = createNode(9);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(11);
    root->right->left->left = createNode(12);
    root->right->left->right = createNode(13);
    root->right->right->left = createNode(14);
    root->right->right->right = createNode(15);

    // Printing the tree
    printTree(root);

    getchar();

    return 0;
}