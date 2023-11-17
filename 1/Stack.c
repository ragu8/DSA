#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

int top = -1, array[SIZE];


void push()
{
    int x;

    if (top >= SIZE - 1)
    {
        printf("\n Stack is Overflow!!");
    }
    else
    {
        printf("\nEnter the element to be Push: ");
        scanf("%d", &x);
        top ++;
        array[top] = x;
    }
}

void pop()
{
    if (top <= -1)
    {
        printf("\n Stack is Underflow!!");
    }
    else
    {
        printf("\nPopped element: %d", array[top]);
        top --;
    }
}

void show()
{
    if (top == -1)
    {
        printf("\n Stack is Empty");
    }
    else
    {
        printf("\nElements present in the stack: \n");
        for (int i = top; i >= 0; --i)
            printf("%d\n", array[i]);
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\nPerform operations on the stack:");
        printf("\n1.Push the element\n2.Pop the element\n3.Show\n4.End");
        printf("\n\nEnter the choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;
            
        case 2:
            pop();
            break;
            
        case 3:
            show();
            break;
            
        case 4:
            exit(0);
            break;

        default:
            printf("\nInvalid choice!!");
        }
    }
}