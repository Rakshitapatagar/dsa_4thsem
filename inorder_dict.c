 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    char name[50];
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to create a new node
struct TreeNode* newTreeNode(const char* name) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform in-order traversal and print the contents
void inOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    inOrderTraversal(root->left);
    printf("%s\n", root->name);
    inOrderTraversal(root->right);
}

// Function to insert a new node into the BST
struct TreeNode* insertNode(struct TreeNode* root, const char* name) {
    if (root == NULL) {
        return newTreeNode(name);
    }

    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = insertNode(root->left, name);
    } else if (cmp > 0) {
        root->right = insertNode(root->right, name);
    } else {
        // Handle duplicates (if required)
    }

    return root;
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

int main() {
    struct TreeNode* root = NULL;
    char name[50];

    // Take user inputs for constructing the binary search tree
    printf("Enter folder or file names (Enter 'exit' to stop):\n");
    while (1) {
        printf("> ");
        scanf("%s", name);
        if (strcmp(name, "exit") == 0) {
            break;
        }
        root = insertNode(root, name);
    }

    // Perform in-order traversal to print the contents in sorted order
    printf("Contents of the directories in sorted order:\n");
    inOrderTraversal(root);

    // Free the memory of the tree
    freeTree(root);

    return 0;
}




The program implements a binary search tree (BST) to store and print a list of folder or file names in sorted order entered by the user.
