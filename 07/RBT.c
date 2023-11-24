#include <stdio.h>
#include <stdlib.h>

// Node structure for the Red-Black Tree
struct Node {
    int key;
    enum { RED, BLACK } color;
    struct Node *left, *right, *parent;
};

typedef struct Node Node;

// Sentinel node to represent NIL
Node NIL_NODE = {0, BLACK, NULL, NULL, NULL};
Node *NIL = &NIL_NODE;

// Function prototypes
Node* createNode(int key);
void leftRotate(Node **root, Node *x);
void rightRotate(Node **root, Node *y);
void insert(Node **root, int key);
void insertFixup(Node **root, Node *z);
void deleteNode(Node **root, Node *z);
void deleteFixup(Node **root, Node *x);
void transplant(Node **root, Node *u, Node *v);
Node* search(Node *root, int key);
Node* minimum(Node *root);
Node* maximum(Node *root);
void inOrderTraversal(Node *root);

// Function to create a new node
Node* createNode(int key) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;
    return newNode;
}

// Left rotation
void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    
    if (y->left != NIL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

// Right rotation
void rightRotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    
    if (x->right != NIL)
        x->right->parent = y;
    
    x->parent = y->parent;
    
    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

// Insertion operation
void insert(Node **root, int key) {
    Node *z = createNode(key);
    Node *y = NIL;
    Node *x = *root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NIL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = NIL;
    z->right = NIL;
    z->color = RED;
    insertFixup(root, z);
}

// Fixup after insertion
void insertFixup(Node **root, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Deletion operation
void deleteNode(Node **root, Node *z) {
    Node *y = z;
    Node *x;
    int yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK)
        deleteFixup(root, x);
    free(z);
}

// Fixup after deletion
void deleteFixup(Node **root, Node *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Transplant function for deletion
void transplant(Node **root, Node *u, Node *v) {
    if (u->parent == NIL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

// Search operation
Node* search(Node *root, int key) {
    if (root == NIL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Minimum key
Node* minimum(Node *root) {
    while (root->left != NIL)
        root = root->left;
    return root;
}

// Maximum key
Node* maximum(Node *root) {
    while (root->right != NIL)
        root = root->right;
    return root;
}

// In-order traversal
void inOrderTraversal(Node *root) {
    if (root != NIL) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

int main() {
    Node *root = NIL;

    // Insertion and validation
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);

    printf("In-order traversal after insertion: ");
    inOrderTraversal(root);
    printf("\n");

    // Deletion and validation
    Node *toDelete = search(root, 20);
    if (toDelete != NIL) {
        deleteNode(&root, toDelete);
        printf("In-order traversal after deletion of 20: ");
        inOrderTraversal(root);
        printf("\n");
    }

    // Search, minimum, and maximum operations
    Node *searchResult = search(root, 12);
    if (searchResult != NIL)
        printf("Search result for key 12: Found\n");
    else
        printf("Search result for key 12: Not Found\n");

    Node *minNode = minimum(root);
    printf("Minimum key in the tree: %d\n", minNode->key);

    Node *maxNode = maximum(root);
    printf("Maximum key in the tree: %d\n", maxNode->key);

    return 0;
}

