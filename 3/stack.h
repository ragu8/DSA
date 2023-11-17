#ifndef STACK_H
#define STACK_H

// Define the maximum size of the stack
#define MAX_SIZE 100

// Define the data type of elements in the stack
typedef int StackType; // Change this to the desired data type

// Define the stack structure
typedef struct {
    StackType data[MAX_SIZE];
    int top;
} Stack;

// Function prototypes
void initialize(Stack* stack);
int isEmpty(const Stack* stack);
int isFull(const Stack* stack);
int push(Stack* stack, StackType item);
int pop(Stack* stack, StackType* item);
int peek(const Stack* stack, StackType* item);

#endif // STACK_H

