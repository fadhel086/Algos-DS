#ifndef STACK_H
#define STACK_H

#define STACK_NOT_FULL 0
#define STACK_NOT_EMPTY 0
#define STACK_EMPTY 1
#define STACK_FULL 1
#define SUCCESS 0


struct stack {
    int top;
    int capacity;
    int member_size;
    void *array;
};

struct stack* create_stack(unsigned size, unsigned member_size);
void remove_stack(struct stack *s);
int is_empty(struct stack *s);
int is_full(struct stack *s);
int push(struct stack *s, void *data);
int pop(struct stack *s, void *data);
int peek(struct stack *s, void *data);

#endif
