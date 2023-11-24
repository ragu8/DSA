#include <stdio.h>
#include "stack.h"

// Define the SQueue structure and initialize it
typedef struct {
    Stack enqueueStack; // Stack for enqueueing elements
    Stack dequeueStack; // Stack for dequeueing elements
} SQueue;

void initializeSQueue(SQueue* queue) {
    initialize(&queue->enqueueStack);
    initialize(&queue->dequeueStack);
}

// Enqueue an element into the SQueue
int enqueue(SQueue* queue, StackType item) {
    // Push the item onto the enqueue stack
    return push(&queue->enqueueStack, item);
}

// Dequeue an element from the SQueue
int dequeue(SQueue* queue, StackType* item) {
    // If the dequeue stack is empty, transfer elements from the enqueue stack
    if (isEmpty(&queue->dequeueStack)) {
        if (isEmpty(&queue->enqueueStack)) {
            // Both stacks are empty; the queue is empty
            return 0;
        }
        while (!isEmpty(&queue->enqueueStack)) {
            StackType temp;
            pop(&queue->enqueueStack, &temp);
            push(&queue->dequeueStack, temp);
        }
    }

    // Pop the item from the dequeue stack
    return pop(&queue->dequeueStack, item);
}

// Get the size of the SQueue
int size(const SQueue* queue) {
    return (queue->enqueueStack.top - (-1)) + (queue->dequeueStack.top - (-1));
}

// Display the contents of the SQueue
void display(const SQueue* queue) {
    printf("SQueue Contents: ");
    
    // Display elements in the enqueue stack
    for (int i = 0; i <= queue->enqueueStack.top; i++) {
        printf("%d ", queue->enqueueStack.data[i]);
    }
    
    // Display elements in the dequeue stack in reverse order
    for (int i = queue->dequeueStack.top; i >= 0; i--) {
        printf("%d ", queue->dequeueStack.data[i]);
    }
    
    printf("\n");
}

int main() {
    SQueue queue;
    initializeSQueue(&queue);
    int choice;
    StackType item;

    do {
        printf("SQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Get Size\n");
        printf("4. Display Contents\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &item);
                if (enqueue(&queue, item)) {
                    printf("%d enqueued successfully.\n", item);
                } else {
                    printf("Queue is full. Enqueue operation failed.\n");
                }
                break;
            case 2:
                if (dequeue(&queue, &item)) {
                    printf("Dequeued element: %d\n", item);
                } else {
                    printf("Queue is empty. Dequeue operation failed.\n");
                }
                break;
            case 3:
                printf("Size of the queue: %d\n", size(&queue));
                break;
            case 4:
                display(&queue);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

