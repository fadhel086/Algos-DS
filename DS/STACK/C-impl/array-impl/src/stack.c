#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct stack* create_stack(int size)
{
    struct stack *s = malloc(sizeof(struct stack));
    if (!s) {
        printf("Stack error: Insufficient memory.\n");
        return s;
    }
    s->top = -1;
    s->capacity = size;
    s->array = malloc(sizeof(char) * size);
    if (!s->array) {
            printf("Stack error:Cannot initialize memory for stack.\n");
            return s;
        }
    return s;
}

int is_full(struct stack *s)
{
    if (s->top == (s->capacity - 1)){
        return 1;
    }
    return 0;
}

int is_empty(struct stack *s)
{
    if (s->top == -1){
        return 1;
    }
    return 0;
}

void push(struct stack *s, char data)
{
    if (is_full(s)) {
        printf("Stack error: Stack Overflow.\n");
        return;
    }
    s->top++;
    s->array[s->top] = data;
}

char pop(struct stack *s)
{
    if (is_empty(s)) {
        printf("Stack error: Stack Underflow.\n");
        return -1;
    }
    return s->array[s->top--];
}

char peek(struct stack *s)
{
    if (is_empty(s)) {
        printf("Stack error: Stack is empty.\n");
        return -1;
    }
    return s->array[s->top];
}

void remove_stack(struct stack *s)
{
    free(s->array);
    free(s);
}
