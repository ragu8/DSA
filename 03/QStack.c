#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Queue {
    int data[MAX_SIZE];
    int front, rear;
};

void initializeQueue(struct Queue* queue) {
    queue->front = queue->rear = -1;
}

int isQueueEmpty(struct Queue* queue) {
    return (queue->front == -1);
}

int isQueueFull(struct Queue* queue) {
    return (queue->rear == MAX_SIZE - 1);
}

void enqueue(struct Queue* queue, int value) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        exit(EXIT_FAILURE);
    }

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear++;
    }

    queue->data[queue->rear] = value;
}

int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        exit(EXIT_FAILURE);
    }

    int value = queue->data[queue->front];
    
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }

    return value;
}

struct QStack {
    struct Queue q1;
    struct Queue q2;
};

void initializeQStack(struct QStack* stack) {
    initializeQueue(&stack->q1);
    initializeQueue(&stack->q2);
}

int isQStackEmpty(struct QStack* stack) {
    return (isQueueEmpty(&stack->q1) && isQueueEmpty(&stack->q2));
}

int getQStackSize(struct QStack* stack) {
    int size = 0;
    if (!isQueueEmpty(&stack->q1)) {
        size += (stack->q1.rear - stack->q1.front) + 1;
    }
    if (!isQueueEmpty(&stack->q2)) {
        size += (stack->q2.rear - stack->q2.front) + 1;
    }
    return size;
}

void clearQStack(struct QStack* stack) {
    initializeQueue(&stack->q1);
    initializeQueue(&stack->q2);
}

void push(struct QStack* stack, int value) {
    if (!isQueueEmpty(&stack->q1)) {
        enqueue(&stack->q1, value);
    } else {
        enqueue(&stack->q2, value);
    }
}

int pop(struct QStack* stack) {
    int value = -1;

    if (!isQueueEmpty(&stack->q1)) {
        while (!isQueueEmpty(&stack->q1)) {
            value = dequeue(&stack->q1);
            if (!isQueueEmpty(&stack->q1)) {
                enqueue(&stack->q2, value);
            }
        }
    } else if (!isQueueEmpty(&stack->q2)) {
        while (!isQueueEmpty(&stack->q2)) {
            value = dequeue(&stack->q2);
            if (!isQueueEmpty(&stack->q2)) {
                enqueue(&stack->q1, value);
            }
        }
    }

    return value;
}

int top(struct QStack* stack) {
    int value = -1;

    if (!isQueueEmpty(&stack->q1)) {
        while (!isQueueEmpty(&stack->q1)) {
            value = dequeue(&stack->q1);
            enqueue(&stack->q2, value);
        }
    } else if (!isQueueEmpty(&stack->q2)) {
        while (!isQueueEmpty(&stack->q2)) {
            value = dequeue(&stack->q2);
            enqueue(&stack->q1, value);
        }
    }

    return value;
}

int main() {
    struct QStack stack;
    initializeQStack(&stack);

    int choice;
    int data;

    while (1) {
        printf("\nQStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Is Empty\n");
        printf("5. Get Size\n");
        printf("6. Clear\n");
        printf("7. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(&stack, data);
                break;
            case 2:
                if (!isQueueEmpty(&stack.q1) || !isQueueEmpty(&stack.q2)) {
                    int poppedItem = pop(&stack);
                    printf("Popped item: %d\n", poppedItem);
                } else {
                    printf("QStack is empty. Cannot pop.\n");
                }
                break;
            case 3:
                if (!isQueueEmpty(&stack.q1) || !isQueueEmpty(&stack.q2)) {
                    int topItem = top(&stack);
                    printf("Top item: %d\n", topItem);
                } else {
                    printf("QStack is empty. Cannot retrieve top.\n");
                }
                break;
            case 4:
                if (isQStackEmpty(&stack)) {
                    printf("QStack is empty.\n");
                } else {
                    printf("QStack is not empty.\n");
                }
                break;
            case 5:
                printf("QStack Size: %d\n", getQStackSize(&stack));
                break;
            case 6:
                clearQStack(&stack);
                printf("QStack cleared.\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

