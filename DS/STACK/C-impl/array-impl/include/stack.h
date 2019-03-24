#ifndef STACK_H
#define STACK_H

struct stack {
    int top;
    int capacity;
    char *array;
};

struct stack* create_stack(int size);
void remove_stack(struct stack *s);
int is_empty(struct stack *s);
int is_full(struct stack *s);
void push(struct stack *s, char data);
char pop(struct stack *s);
char peek(struct stack *s);

#endif
