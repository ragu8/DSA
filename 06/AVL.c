#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the AVL tree
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function prototypes
struct Node* insert(struct Node* root, int key);
struct Node* deleteNode(struct Node* root, int key);
int isAVL(struct Node* root);
int findHeight(struct Node* root);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
int max(int a, int b);

// Function to get the height of a node
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node with a given key
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // New node is initially at height 1
    return node;
}

// Function to perform a right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return the new root
    return x;
}

// Function to perform a left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return the new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a key into the AVL tree
struct Node* insert(struct Node* root, int key) {
    // Perform standard BST insert
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;  // Duplicate keys are not allowed

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // No rotation needed
    return root;
}

// Function to find the node with the minimum key value in a tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with a given key from the AVL tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else  // One child case
                *root = *temp;  // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to check if a tree is AVL
int isAVL(struct Node* root) {
    if (root == NULL)
        return 1;

    int balance = getBalance(root);

    if (balance > 1 || balance < -1)
        return 0;

    return isAVL(root->left) && isAVL(root->right);
}

// Function to find the height of an AVL tree
int findHeight(struct Node* root) {
    if (root == NULL)
        return 0;

    return root->height;
}

// Function to create a balanced AVL tree from a sorted array
struct Node* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = newNode(arr[mid]);

    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}

// Function to count the number of nodes at a given level in an AVL tree
int countNodesAtLevel(struct Node* root, int level) {
    if (root == NULL)
        return 0;

    if (level == 1)
        return 1;

    return countNodesAtLevel(root->left, level - 1) + countNodesAtLevel(root->right, level - 1);
}

// Function to perform AVL tree operations based on user input
void performOperations() {
    struct Node* root = NULL;
    int choice, key;

    do {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Check if tree is AVL\n");
        printf("4. Find the height of the tree\n");
        printf("5. Convert a sorted array to AVL tree\n");
        printf("6. Count nodes at a given level\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;

            case 3:
                if (isAVL(root))
                    printf("The tree is AVL.\n");
                else
                    printf("The tree is not AVL.\n");
                break;

            case 4:
                printf("The height of the tree is: %d\n", findHeight(root));
                break;

            case 5:
                {
                    int n, i;
                    printf("Enter the size of the sorted array: ");
                    scanf("%d", &n);
                    int arr[n];
                    printf("Enter the sorted array elements:\n");
                    for (i = 0; i < n; i++)
                        scanf("%d", &arr[i]);
                    root = sortedArrayToBST(arr, 0, n - 1);
                    printf("Sorted array converted to AVL tree.\n");
                }
                break;

            case 6:
                {
                    int level;
                    printf("Enter the level to count nodes: ");
                    scanf("%d", &level);
                    printf("Number of nodes at level %d: %d\n", level, countNodesAtLevel(root, level));
                }
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 7);
}

// Main function
int main() {
    performOperations();
    return 0;
}

