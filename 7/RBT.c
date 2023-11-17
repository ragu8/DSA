#include <stdio.h>
#include <stdlib.h>

// Define colors for nodes
#define RED 0
#define BLACK 1

// Node structure for the Red-Black Tree
struct Node {
    int data;
    int color;  // Color of the node
    struct Node *left, *right, *parent;
};

// Function prototypes
struct Node *createNode(int data);
void insert(struct Node **root, int data);
void fixInsert(struct Node **root, struct Node *newNode);
void deleteNode(struct Node **root, int key);
void fixDelete(struct Node **root, struct Node *x);
struct Node *search(struct Node *root, int key);
struct Node *minimum(struct Node *root);
struct Node *maximum(struct Node *root);
void inOrderTraversal(struct Node *root);
void leftRotate(struct Node **root, struct Node *x);
void rightRotate(struct Node **root, struct Node *x);

// Helper function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct Node **root, struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Function to insert a node into the Red-Black Tree
void insert(struct Node **root, int data) {
    struct Node *newNode = createNode(data);
    struct Node *parent = NULL;
    struct Node *current = *root;

    // Traverse the tree to find the appropriate position for the new node
    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // Set the parent of the new node
    newNode->parent = parent;

    // Insert the new node into the tree
    if (parent == NULL)
        *root = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Fix any violations of the Red-Black Tree properties
    fixInsert(root, newNode);
}

// Fix the Red-Black Tree properties after insertion
void fixInsert(struct Node **root, struct Node *newNode) {
    while (newNode->parent != NULL && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->left) {
            struct Node *uncle = newNode->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    leftRotate(root, newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rightRotate(root, newNode->parent->parent);
            }
        } else {
            struct Node *uncle = newNode->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rightRotate(root, newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                leftRotate(root, newNode->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

// Function to delete a node from the Red-Black Tree
void deleteNode(struct Node **root, int key) {
    struct Node *z = search(*root, key);
    if (z == NULL) {
        printf("Node with key %d not found in the tree.\n", key);
        return;
    }

    struct Node *y = z;
    int yOriginalColor = y->color;
    struct Node *x;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL)
                x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == BLACK)
        fixDelete(root, x);
}

// Fix the Red-Black Tree properties after deletion
void fixDelete(struct Node **root, struct Node *x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            struct Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL)
                    w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL)
                    w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}

// Transplant function for deletion
void transplant(struct Node **root, struct Node *u, struct Node *v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// Function to search for a node with a given key
struct Node *search(struct Node *root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Function to find the node with the minimum key in the tree
struct Node *minimum(struct Node *root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to find the node with the maximum key in the tree
struct Node *maximum(struct Node *root) {
    while (root->right != NULL)
        root = root->right;
    return root;
}

// Function to perform in-order traversal of the Red-Black Tree
void inOrderTraversal(struct Node *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

int main() {
    struct Node *root = NULL;

    // Insertion
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);

    printf("In-order Traversal after insertion: ");
    inOrderTraversal(root);
    printf("\n");

    // Deletion
    deleteNode(&root, 20);

    printf("In-order Traversal after deletion: ");
    inOrderTraversal(root);
    printf("\n");

    // Minimum and Maximum
    struct Node *minNode = minimum(root);
    struct Node *maxNode = maximum(root);
    printf("Minimum: %d\n", minNode->data);
    printf("Maximum: %d\n", maxNode->data);

    return 0;
}

