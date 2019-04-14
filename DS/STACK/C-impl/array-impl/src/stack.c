#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "stack.h"

struct stack* create_stack(int stack_size, int member_size)
{
    struct stack *s = malloc(sizeof(struct stack));
    if (!s) {
        printf("Stack error: Insufficient memory.\n");
        return s;
    }
    s->top = -1;
    s->capacity = stack_size;
    s->member_size = member_size;
    s->array = malloc(sizeof(member_size) * s->capacity);
    if (!s->array) {
            printf("Stack error:Cannot initialize memory for stack.\n");
            return (struct stack *)s->array;
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

int push(struct stack *s, void *data)
{
    void *location;

    if (is_full(s)) {
        printf("Stack error: Stack Overflow.\n");
        return 1;
    }

    s->top++;
    /* place to write the data */
    location = (char  *)s->array + (s->top * s->member_size);
    memcpy(location, data, s->member_size);
    return 0;
}

int pop(struct stack *s, void *data)
{
    void *data_src;

    if (is_empty(s)) {
        printf("Stack error: Stack Underflow.\n");
        return -1;
    }

    data_src = (char *)s->array + (s->top * s->member_size);
    memcpy(data, data_src, s->member_size);
    s->top--;
    return 0;
}

int peek(struct stack *s, void *data)
{
    void *data_src;

    if (is_empty(s)) {
        printf("Stack error: Stack is empty.\n");
        return -1;
    }
    data_src = s->array + (s->top * s->member_size);
    memcpy(data, data_src, s->member_size);
    return 0;
}

void remove_stack(struct stack *s)
{
    free(s->array);
    free(s);
}
