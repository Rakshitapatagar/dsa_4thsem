#include <stdio.h>
#include <stdlib.h>

// Structure for AVL tree node
struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the height of a node
int getHeight(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to create a new AVL tree node
struct AVLNode* createNode(int data) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform a right rotation
struct AVLNode* rotateRight(struct AVLNode* y, FILE* output) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    fprintf(output, "Performing RR Rotation at node %d\n", y->data);
    fprintf(output, "Old Root: %d\n", y->data);
    fprintf(output, "New Root after RR Rotation: %d\n", x->data);

    return x;
}

// Function to perform a left rotation
struct AVLNode* rotateLeft(struct AVLNode* x, FILE* output) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    fprintf(output, "Performing LL Rotation at node %d\n", x->data);
    fprintf(output, "Old Root: %d\n", x->data);
    fprintf(output, "New Root after LL Rotation: %d\n", y->data);

    return y;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into the AVL tree
struct AVLNode* insertNode(struct AVLNode* node, int data, FILE* output) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data, output);
    else if (data > node->data)
        node->right = insertNode(node->right, data, output);
    else
        return node;  // Duplicate keys are not allowed in AVL tree

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && data < node->left->data)
        return rotateRight(node, output);

    // Right Right Case
    if (balanceFactor < -1 && data > node->right->data)
        return rotateLeft(node, output);

    // Left Right Case
    if (balanceFactor > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left, output);
        return rotateRight(node, output);
    }

    // Right Left Case
    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rotateRight(node->right, output);
        return rotateLeft(node, output);
    }

    return node;
}

// Function to find the node with the minimum value in the AVL tree
struct AVLNode* findMinValueNode(struct AVLNode* node) {
    struct AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
struct AVLNode* deleteNode(struct AVLNode* root, int data, FILE* output) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data, output);
    else if (data > root->data)
        root->right = deleteNode(root->right, data, output);
    else {
        // Node to be deleted found
        if (root->left == NULL || root->right == NULL) {
            struct AVLNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            struct AVLNode* temp = findMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data, output);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balanceFactor = getBalanceFactor(root);

    // Left Left Case
    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root, output);

    // Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left, output);
        return rotateRight(root, output);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root, output);

    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right, output);
        return rotateLeft(root, output);
    }

    return root;
}

// Function to perform inorder traversal of the AVL tree
void inorderTraversal(struct AVLNode* root, FILE* output) {
    if (root != NULL) {
        inorderTraversal(root->left, output);
        fprintf(output, "%d ", root->data);
        inorderTraversal(root->right, output);
    }
}

// Function to perform preorder traversal of the AVL tree
void preorderTraversal(struct AVLNode* root, FILE* output) {
    if (root != NULL) {
        fprintf(output, "%d ", root->data);
        preorderTraversal(root->left, output);
        preorderTraversal(root->right, output);
    }
}

// Function to perform postorder traversal of the AVL tree
void postorderTraversal(struct AVLNode* root, FILE* output) {
    if (root != NULL) {
        postorderTraversal(root->left, output);
        postorderTraversal(root->right, output);
        fprintf(output, "%d ", root->data);
    }
}

// Function to search for a node in the AVL tree and delete if found
struct AVLNode* searchAndDelete(struct AVLNode* root, int data, FILE* output) {
    if (root == NULL) {
        fprintf(output, "%d not found in the AVL tree!\n", data);
        return root;
    }

    if (data < root->data)
        root->left = searchAndDelete(root->left, data, output);
    else if (data > root->data)
        root->right = searchAndDelete(root->right, data, output);
    else {
        fprintf(output, "%d found and deleted from the AVL tree!\n", data);
        root = deleteNode(root, data, output);
    }

    return root;
}

// Function to calculate the depth of a node in the AVL tree
int getNodeDepth(struct AVLNode* root, int data, int depth) {
    if (root == NULL)
        return 0;

    if (data < root->data)
        return getNodeDepth(root->left, data, depth + 1);
    else if (data > root->data)
        return getNodeDepth(root->right, data, depth + 1);
    else
        return depth;
}

int main() {
    int minRange, maxRange;
    printf("Enter the minimum range for random number generation: ");
    scanf("%d", &minRange);
    printf("Enter the maximum range for random number generation: ");
    scanf("%d", &maxRange);

    FILE* inputFile = fopen("input.txt", "w");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Generate and write random numbers to the input file
    int i, num;
    for (i = 0; i < 4; i++) {
        num = minRange + rand() % (maxRange - minRange + 1);
        fprintf(inputFile, "%d \t", num);
    }
    //fprintf(inputFile,"/n");
    fclose(inputFile);

    // Read the input file and construct the AVL tree
    FILE* inputFileRead = fopen("input.txt", "r");
    if (inputFileRead == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    struct AVLNode* root = NULL;
    while (fscanf(inputFileRead, "%d", &num) != EOF) {
        root = insertNode(root, num, NULL);
    }
    fclose(inputFileRead);

    FILE* outputFile = fopen("avl_eval_final.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    // Display the generated random numbers
    printf("Generated Random Numbers: ");
    inputFileRead = fopen("input.txt", "r");
    while (fscanf(inputFileRead, "%d", &num) != EOF) {
        printf("%d ", num);
    }
    printf("\n\n");
    fclose(inputFileRead);

    // Perform AVL tree operations and write the output to the file
    fprintf(outputFile, "Inorder Traversal: ");
    inorderTraversal(root, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "Preorder Traversal: ");
    preorderTraversal(root, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "Postorder Traversal: ");
    postorderTraversal(root, outputFile);
    fprintf(outputFile, "\n");

    int searchData;
    printf("Enter a number to search and delete from the AVL tree: ");
    scanf("%d", &searchData);

    struct AVLNode* oldRoot = root;
    root = searchAndDelete(root, searchData, outputFile);

    // Print height, depth, balancing factor, old root, and alternate solutions
    int height = getHeight(root);
    int depth = getNodeDepth(root, root->data, 1);
    int balanceFactor = getBalanceFactor(root);

    fprintf(outputFile, "\nHeight of the AVL tree: %d\n", height);
    fprintf(outputFile, "Depth of the root node: %d\n", depth);
    fprintf(outputFile, "Balancing Factor of the root node: %d\n", balanceFactor);
    fprintf(outputFile, "Old Root: %d\n", oldRoot->data);
    fprintf(outputFile, "Number after RR rotation: %d\n", oldRoot->right ? oldRoot->right->data : -1);
    fprintf(outputFile, "Number after RL rotation: %d\n", oldRoot->left ? oldRoot->left->data : -1);
    fprintf(outputFile, "Number after LL rotation: %d\n", root->left ? root->left->data : -1);
    fprintf(outputFile, "Number after LR rotation: %d\n", root->right ? root->right->data : -1);

    fclose(outputFile);

    printf("AVL tree operations completed successfully. Check 'avl_eval.txt' for the output.\n");

    return 0;
}
