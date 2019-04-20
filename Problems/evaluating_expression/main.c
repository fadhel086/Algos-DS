#include <stdio.h>
#include <stack.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define EXPR_SIZE 256
#define DIGITS 6

int precedence(char operator)
{
    switch(operator)
    {
        case '/':
            return 3;
        case '*':
            return 3;
        case '+':
            return 2;
        case '-':
            return 2;
        default:
        // Assumed '('
            return 1;
    }
}

int is_operator(char c)
{
   if ( (c == '/') || (c == '*') ||
        (c == '+') || (c == '-') ||
        (c == '(') || (c == ')') )
   {
           return 1;
   }
   return 0;
}

unsigned do_math(unsigned num1, unsigned num2, char operator)
{
    switch(operator)
    {
        case '/':
            return num1 / num2;
        case '*':
            return num1 * num2;
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        default:
            return num1;
    }
}

unsigned eval_expr(char *buf)
{
    struct stack *operand_stack = NULL;
    char operand_word[DIGITS] = {0};
    unsigned i, num, num1, num2, result, digits = 0;

    operand_stack = create_stack(sizeof(buf), sizeof(int));
    if (!operand_stack) {
        printf("Stack cretion failed\n");
        exit(1);
    }

    for (i = 0; i < strlen(buf); ++i) {
        if (isspace(buf[i])) {
            if (operand_word[0]) {
                num = (unsigned)atoi(operand_word);
                push(operand_stack, &num);
                memset(operand_word, '\0', sizeof(char) * DIGITS);
                digits = 0;
            }
        } else if (is_operator(buf[i])) {
            if (operand_word[0]) {
                num = (unsigned)atoi(operand_word);
                push(operand_stack, &num);
                memset(operand_word, '\0', sizeof(char) * DIGITS);
                digits = 0;
            }
            // pop previous operands from stack and do_math
            pop(operand_stack, &num2);
            pop(operand_stack, &num1);
            result = do_math(num1, num2, buf[i]);
            push(operand_stack, &result);
        } else {
            // Add to operand_word[] the individual chars
            operand_word[digits++] = buf[i];
        }
    }
    pop(operand_stack, &result);
    return result;
}

void infix_to_postfix(char *infix, char *postfix)
{
    unsigned int i,j = 0;
    struct stack *operator_stack = NULL;
    char stack_data;

    if (!infix) {
        printf("Enter a valid infix_expression.\n");
        exit(1);
    }

    operator_stack = create_stack(strlen(infix), sizeof(char));

    for (i = 0; i < strlen(infix); ++i) {
        if (isspace(infix[i])) {
            postfix[j++] = ' ';
            continue;
        }
        // if It's numerical character.
        // Append to post_fix expression.
        if (!is_operator(infix[i])) {
            postfix[j++] = infix[i];
            continue;
        }

        //It's an operator
        if (peek(operator_stack, &stack_data) == STACK_EMPTY) {
            push(operator_stack, &infix[i]);
        } else {
           if (precedence(infix[i]) >= precedence(stack_data)) {
                push(operator_stack, &infix[i]);
            } else {
                while(pop(operator_stack, &stack_data) != STACK_EMPTY) {
                    postfix[j++] = stack_data;
                    postfix[j++] = ' ';
                }
                push(operator_stack, &infix[i]);
            }
        }
    } // End of for

    // pop all the operators in stack.
    while(pop(operator_stack, &stack_data) != STACK_EMPTY) {
        postfix[j++] = stack_data;
        postfix[j++] = ' ';
    }
}

int main()
{
    char buf[EXPR_SIZE] = {0};
    char postfix_expr[EXPR_SIZE] = {0};
    unsigned result;

    /* Get user input */
    printf("User direction:\nIndividual numbers, operators are sperated by spaces.\n"
           "Example:\n"
           "\t111 + 222 * 333 / 64.\n"
           "\tEnter valid expression. Invalid expression will result in spurious answers.\n");
    printf("Enter the post-fix expr:");
    fgets(buf, EXPR_SIZE, stdin);
    infix_to_postfix(buf, postfix_expr);
    printf("pexpr is %s\n", postfix_expr);
    result = eval_expr(postfix_expr);
    printf("result:%d\n", result);
    return 0;
}
