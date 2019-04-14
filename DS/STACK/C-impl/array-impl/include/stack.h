#ifndef STACK_H
#define STACK_H

struct stack {
    int top;
    int capacity;
    int member_size;
    void *array;
};

struct stack* create_stack(int size, int member_size);
void remove_stack(struct stack *s);
int is_empty(struct stack *s);
int is_full(struct stack *s);
int push(struct stack *s, void *data);
int pop(struct stack *s, void *data);
int peek(struct stack *s, void *data);

#endif
