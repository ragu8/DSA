#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int arrayIndex;
    int elementIndex;
} HeapNode;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HeapNode* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].value < heap[smallest].value)
        smallest = left;

    if (right < size && heap[right].value < heap[smallest].value)
        smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

int* mergeSortedArrays(int** arrays, int* sizes, int k, int* resultSize) {
    HeapNode* minHeap = (HeapNode*)malloc(k * sizeof(HeapNode));
    int i;
    for (i = 0; i < k; i++) {
        minHeap[i].value = arrays[i][0];
        minHeap[i].arrayIndex = i;
        minHeap[i].elementIndex = 0;
    }

    for (i = k / 2 - 1; i >= 0; i--) {
        minHeapify(minHeap, k, i);
    }

    int* result = (int*)malloc(sizeof(int) * k * sizes[0]);
    int currentIndex = 0;

    while (currentIndex < k * sizes[0]) {
        HeapNode root = minHeap[0];
        result[currentIndex++] = root.value;

        int nextElementIndex = root.elementIndex + 1;
        if (nextElementIndex < sizes[root.arrayIndex]) {
            minHeap[0] = (HeapNode){arrays[root.arrayIndex][nextElementIndex], root.arrayIndex, nextElementIndex};
        } else {
            minHeap[0] = (HeapNode){INT_MAX, root.arrayIndex, nextElementIndex};
        }
        
        minHeapify(minHeap, k, 0);
    }

    *resultSize = k * sizes[0];
    free(minHeap);

    return result;
}

int main() {
    int arr1[] = {1, 10, 11, 15};
    int arr2[] = {2, 4, 9, 14};
    int arr3[] = {5, 6, 8, 16};
    int arr4[] = {3, 7, 12, 13};
    
    int* arrays[] = {arr1, arr2, arr3, arr4};
    int sizes[] = {4, 4, 4, 4};
    int k = 4;
    int resultSize;

    int* mergedArray = mergeSortedArrays(arrays, sizes, k, &resultSize);
    printf("\n");
    for (int i = 0; i < resultSize; i++) {
        
        printf("%d ", mergedArray[i]);
    }
    printf("\n");

    free(mergedArray);

    return 0;
}

