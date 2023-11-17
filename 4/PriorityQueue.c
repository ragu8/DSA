#include <stdio.h>
#include <stdlib.h>

struct PQElement {
    int key;
};

struct PriorityQueue {
    struct PQElement* heap;
    int capacity;
    int size;
};

void swap(struct PQElement* a, struct PQElement* b) {
    struct PQElement temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(struct PriorityQueue* pq, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->heap[left].key > pq->heap[largest].key) {
        largest = left;
    }
    if (right < pq->size && pq->heap[right].key > pq->heap[largest].key) {
        largest = right;
    }

    if (largest != idx) {
        swap(&pq->heap[idx], &pq->heap[largest]);
        maxHeapify(pq, largest);
    }
}

void insert(struct PriorityQueue* pq, int key) {
    if (pq->size == pq->capacity) {
        printf("Priority Queue is full, can't insert.\n");
        return;
    }

    struct PQElement newElement;
    newElement.key = key;

    int i = pq->size;
    pq->heap[i] = newElement;
    pq->size++;

    while (i > 0 && pq->heap[(i - 1) / 2].key < pq->heap[i].key) {
        swap(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteMax(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty, can't delete.\n");
        return;
    }

    if (pq->size == 1) {
        pq->size--;
        return;
    }

    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    maxHeapify(pq, 0);
}

int peekMax(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty.\n");
        return -1;
    }
    return pq->heap[0].key;
}

struct PriorityQueue* createPriorityQueue(int capacity) {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->heap = (struct PQElement*)malloc(capacity * sizeof(struct PQElement));
    return pq;
}

int main() {
    struct PriorityQueue* pq = createPriorityQueue(10);

    int choice, key;

    do {
        printf("Choose an operation:\n");
        printf("1. Insert\n");
        printf("2. Delete Max\n");
        printf("3. Peek Max\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(pq, key);
                break;
            case 2:
                deleteMax(pq);
                break;
            case 3:
                printf("Max priority element: %d\n", peekMax(pq));
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    free(pq->heap);
    free(pq);

    return 0;
}

