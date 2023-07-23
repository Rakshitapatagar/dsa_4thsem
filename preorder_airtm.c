 
The program takes an arithmetic expression in prefix notation as input, constructs an expression tree, evaluates the expression using pre-order traversal, and prints the result.


#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to create a new node
struct TreeNode* newTreeNode(char val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform pre-order traversal and evaluate the expression
int evaluateExpression(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }


    if (root->val >= '0' && root->val <= '9') {
        return root->val - '0';
    }


    int leftVal = evaluateExpression(root->left);
    int rightVal = evaluateExpression(root->right);


    if (root->val == '+') {
        return leftVal + rightVal;
    } else if (root->val == '-') {
        return leftVal - rightVal;
    } else if (root->val == '*') {
        return leftVal * rightVal;
    } else if (root->val == '/') {
        return leftVal / rightVal;
    }

    return 0;
}

// Function to construct the expression tree from prefix notation input
struct TreeNode* constructExpressionTree() {
    char ch;
    scanf(" %c", &ch);

    if (ch >= '0' && ch <= '9') {
        return newTreeNode(ch);
    }

    struct TreeNode* root = newTreeNode(ch);
    root->left = constructExpressionTree();
    root->right = constructExpressionTree();
    return root;
}

// Function to free the memory of the expression tree
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {

    printf("Enter the arithmetic expression in prefix notation: ");
    struct TreeNode* root = constructExpressionTree();

    // Evaluate the expression using pre-order traversal
    int result = evaluateExpression(root);

    printf("Result of the expression: %d\n", result);

    // Free the memory of the expression tree
    freeTree(root);

    return 0;
}
