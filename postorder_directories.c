



 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    char name[50];
    int size; // File size in KB or MB
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to create a new node
struct TreeNode* newTreeNode(const char* name, int size) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(newNode->name, name);
    newNode->size = size;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform post-order traversal and calculate the total size
int postOrderSize(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // Calculate the size of left and right subtrees
    int leftSize = postOrderSize(root->left);
    int rightSize = postOrderSize(root->right);

    // Calculate the total size including the current node's size
    int totalSize = leftSize + rightSize + root->size;

    return totalSize;
}

// Function to free the memory of the tree
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Function to construct the directory structure using user inputs
struct TreeNode* constructDirectoryStructure() {
    char name[50];
    int size;

    printf("Enter the name of the directory: ");
    scanf("%s", name);
    printf("Enter the size of the directory (in KB): ");
    scanf("%d", &size);

    struct TreeNode* root = newTreeNode(name, size);

    char choice;
    printf("Does the directory have any subdirectories or files? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        root->left = constructDirectoryStructure();
    }

    printf("Does the directory have any files? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        root->right = constructDirectoryStructure();
    }

    return root;
}

int main() {

    printf("Enter the root directory details:\n");
    struct TreeNode* root = constructDirectoryStructure();

    // Calculate the total size using post-order traversal
    int totalSize = postOrderSize(root);

    printf("Total size of all files in the directory structure: %d KB\n", totalSize);

    // Free the memory of the tree
    freeTree(root);

    return 0;
}

