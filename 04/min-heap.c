#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} MinHeap;

// Function declarations
MinHeap *createMinHeap(int capacity);
void insert(MinHeap *heap, int element);
int extractMin(MinHeap *heap);
bool isEmpty(MinHeap *heap);
void siftUp(MinHeap *heap, int index);
void siftDown(MinHeap *heap, int index);
void destroyMinHeap(MinHeap *heap);
void convertArrayToMinHeap(MinHeap *heap, int *elements, int size);
void decreaseKey(MinHeap *heap, int index, int newValue);
void clearInputBuffer();

// Function implementations

MinHeap *createMinHeap(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->array = malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert(MinHeap *heap, int element) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->array = realloc(heap->array, sizeof(int) * heap->capacity);
    }

    heap->array[heap->size++] = element;
    siftUp(heap, heap->size - 1);
}

int extractMin(MinHeap *heap) {
    if (heap->size == 0) {
        return -1;
    }

    int min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    siftDown(heap, 0);
    return min;
}

bool isEmpty(MinHeap *heap) {
    return heap->size == 0;
}

void siftUp(MinHeap *heap, int index) {
    // Implementation of siftUp
}

void siftDown(MinHeap *heap, int index) {
    // Implementation of siftDown
}

void destroyMinHeap(MinHeap *heap) {
    free(heap->array);
    free(heap);
}

void convertArrayToMinHeap(MinHeap *heap, int *elements, int size) {
    // Implementation of converting an array to a min-heap
}

void decreaseKey(MinHeap *heap, int index, int newValue) {
    // Implementation of decreasing a key
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int capacity;
    printf("Enter the initial capacity of the MinHeap: ");
    scanf("%d", &capacity);
    clearInputBuffer();

    MinHeap *heap = createMinHeap(capacity);

    int choice, element, size;
    int *elements;

    while (1) {
        printf("\nMin Heap Operations:\n");
        printf("1. Insert element\n");
        printf("2. Extract minimum\n");
        printf("3. Check if the heap is empty\n");
        printf("4. Convert array to min-heap\n");
        printf("5. Decrease key\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please try again.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                clearInputBuffer();
                insert(heap, element);
                printf("Element %d inserted.\n", element);
                break;

            case 2:
                if (!isEmpty(heap)) {
                    int min = extractMin(heap);
                    printf("Minimum element: %d\n", min);
                } else {
                    printf("The heap is empty.\n");
                }
                break;

            case 3:
                if (isEmpty(heap)) {
                    printf("The heap is empty.\n");
                } else {
                    printf("The heap is not empty.\n");
                }
                break;

            case 4:
                printf("Enter the size of the array: ");
                scanf("%d", &size);
                clearInputBuffer();
                elements = (int *)malloc(sizeof(int) * size);
                printf("Enter %d elements: ", size);
                for (int i = 0; i < size; i++) {
                    scanf("%d", &elements[i]);
                }
                convertArrayToMinHeap(heap, elements, size);
                free(elements);
                printf("Array converted to a min-heap.\n");
                break;

            case 5:
                printf("Enter the index and new value (space-separated): ");
                int index, newValue;
                scanf("%d %d", &index, &newValue);
                clearInputBuffer();
                decreaseKey(heap, index, newValue);
                break;

            case 6:
                destroyMinHeap(heap);
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

