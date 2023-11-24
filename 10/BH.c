#include <stdio.h>
#include <stdlib.h>

// Node structure for binomial heap
struct Node {
    int key;
    int degree;
    struct Node *parent, *child, *sibling;
};

// Function to create a new node
struct Node *createNode(int key) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}

// Function to link two binomial trees of the same degree
void link(struct Node *root1, struct Node *root2) {
    root1->parent = root2;
    root1->sibling = root2->child;
    root2->child = root1;
    root2->degree++;
}

// Function to merge two binomial heaps
struct Node *unionBinomialHeaps(struct Node *h1, struct Node *h2) {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    struct Node *carry = NULL;
    struct Node *temp1 = h1;
    struct Node *temp2 = h2;

    while (temp1 != NULL || temp2 != NULL || carry != NULL) {
        struct Node *node = createNode(0);

        if (temp1 != NULL) {
            node = temp1;
            temp1 = temp1->sibling;
        }

        if (temp2 != NULL) {
            node = temp2;
            temp2 = temp2->sibling;
        }

        if (carry != NULL) {
            node = carry;
            carry = NULL;
        }

        if (head == NULL) {
            head = tail = node;
        } else {
            tail->sibling = node;
            tail = node;
        }

        struct Node *next = node->sibling;
        node->sibling = NULL;

        while (next != NULL && next->degree == node->degree) {
            struct Node *temp;
            if (next->key < node->key) {
                temp = next;
                next = node;
                node = temp;
            }

            if (node->child == NULL) {
                node->child = next;
                next->parent = node;
                next->sibling = NULL;
            } else {
                link(next, node->child);
                node->child = next;
            }

            next = next->sibling;
            node->degree++;
        }

        if (node->degree > 0) {
            carry = node;
        }
    }

    return head;
}

// Function to insert a key into the binomial heap
struct Node *insert(struct Node *heap, int key) {
    struct Node *newNode = createNode(key);
    return unionBinomialHeaps(heap, newNode);
}

// Function to extract the minimum key from the binomial heap
struct Node *extractMin(struct Node *heap) {
    if (heap == NULL) {
        return NULL;
    }

    struct Node *prev = NULL;
    struct Node *minNode = heap;
    struct Node *minPrev = NULL;
    struct Node *temp = heap->sibling;

    while (temp != NULL) {
        if (temp->key < minNode->key) {
            minNode = temp;
            minPrev = prev;
        }

        prev = temp;
        temp = temp->sibling;
    }

    if (minPrev == NULL) {
        heap = minNode->sibling;
    } else {
        minPrev->sibling = minNode->sibling;
    }

    struct Node *child = minNode->child;
    struct Node *childPrev = NULL;

    while (child != NULL) {
        childPrev = child;
        child = child->sibling;
        childPrev->sibling = NULL;
        heap = unionBinomialHeaps(heap, childPrev);
    }

    free(minNode);
    return heap;
}

// Function to decrease the key of a node in the binomial heap
struct Node *decreaseKey(struct Node *heap, int oldKey, int newKey) {
    // Not implemented in this example
    // You may need to search for the node with the old key and then decrease its key
    return heap;
}

// Function to search for a key in the binomial heap
struct Node *search(struct Node *heap, int key) {
    // Not implemented in this example
    // You may need to traverse the heap to search for the key
    return heap;
}

// Function to display the binomial heap
void display(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->key);
        display(node->child);
        node = node->sibling;
    }
}

int main() {
    struct Node *heap = NULL;

    int choice, key, oldKey, newKey;

    do {
        printf("\n1. Insert\n2. Extract Min\n3. Decrease Key\n4. Search\n5. Display\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                heap = insert(heap, key);
                break;

            case 2:
                heap = extractMin(heap);
                break;

            case 3:
                printf("Enter the old key: ");
                scanf("%d", &oldKey);
                printf("Enter the new key: ");
                scanf("%d", &newKey);
                heap = decreaseKey(heap, oldKey, newKey);
                break;

            case 4:
                printf("Enter key to search: ");
                scanf("%d", &key);
                struct Node *result = search(heap, key);
                if (result != NULL) {
                    printf("Key found in the heap.\n");
                } else {
                    printf("Key not found in the heap.\n");
                }
                break;

            case 5:
                printf("Binomial Heap: ");
                display(heap);
                printf("\n");
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

