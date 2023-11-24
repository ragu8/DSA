#include <stdio.h>
#include <stdlib.h>

// Node structure for the leftist heap
struct Node {
    int key;
    int npl; // Null Path Length
    struct Node *left;
    struct Node *right;
};

typedef struct Node Node;

// Function prototypes
Node* merge(Node *h1, Node *h2);
Node* insert(Node *heap, int key);
Node* deleteMin(Node *heap);
void inorderTraversal(Node *heap);

// Function to create a new node
Node* createNode(int key) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->npl = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Merge two leftist heaps
Node* merge(Node *h1, Node *h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    // Make sure h1 has a smaller root
    if (h1->key > h2->key) {
        Node *temp = h1;
        h1 = h2;
        h2 = temp;
    }

    // Merge the right subtree of h1 with h2
    h1->right = merge(h1->right, h2);

    // Update null path length
    if (h1->left == NULL || (h1->right != NULL && h1->left->npl < h1->right->npl)) {
        Node *temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }

    if (h1->right == NULL) {
        h1->npl = 0;
    } else {
        h1->npl = h1->right->npl + 1;
    }

    return h1;
}

// Insert into a leftist heap
Node* insert(Node *heap, int key) {
    Node *newNode = createNode(key);
    return merge(heap, newNode);
}

// Delete minimum element from a leftist heap
Node* deleteMin(Node *heap) {
    if (heap == NULL) {
        printf("Heap is empty\n");
        return NULL;
    }

    Node *left = heap->left;
    Node *right = heap->right;
    free(heap);

    return merge(left, right);
}

// In-order traversal for testing
void inorderTraversal(Node *heap) {
    if (heap != NULL) {
        inorderTraversal(heap->left);
        printf("%d ", heap->key);
        inorderTraversal(heap->right);
    }
}

int main() {
    Node *heap = NULL;

    // Insertion
    heap = insert(heap, 3);
    heap = insert(heap, 5);
    heap = insert(heap, 7);
    heap = insert(heap, 2);
    heap = insert(heap, 8);

    printf("Leftist Heap after insertion: ");
    inorderTraversal(heap);
    printf("\n");

    // Deletion
    heap = deleteMin(heap);

    printf("Leftist Heap after deletion: ");
    inorderTraversal(heap);
    printf("\n");

    return 0;
}

