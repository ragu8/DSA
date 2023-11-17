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
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);

// Function to perform a right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + ((y->left != NULL) ? y->left->height : 0) + ((y->right != NULL) ? y->right->height : 0);
    x->height = 1 + ((x->left != NULL) ? x->left->height : 0) + ((x->right != NULL) ? x->right->height : 0);

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
    x->height = 1 + ((x->left != NULL) ? x->left->height : 0) + ((x->right != NULL) ? x->right->height : 0);
    y->height = 1 + ((y->left != NULL) ? y->left->height : 0) + ((y->right != NULL) ? y->right->height : 0);

    // Return the new root
    return y;
}

// Function to display the menu and perform AVL tree rotations
void performRotations() {
    struct Node* root = NULL;
    int choice;

    do {
        printf("\nAVL Tree Rotation Functions:\n");
        printf("1. Right Rotate\n");
        printf("2. Left Rotate\n");
        printf("3. Display Tree\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = rightRotate(root);
                printf("Right Rotation performed.\n");
                break;

            case 2:
                root = leftRotate(root);
                printf("Left Rotation performed.\n");
                break;

            case 3:
                // Add a function to display the AVL tree (if needed)
                printf("Display Tree Function Placeholder.\n");
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
}

// Main function
int main() {
    performRotations();
    return 0;
}

