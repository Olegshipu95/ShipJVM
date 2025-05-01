#include "util.h"


void stack_char_push(struct stack_char *restrict stack, char letter) {
    stack->data[stack->size] = letter;
    stack->size++;
}

void stack_int_push(struct stack_int *restrict stack, int letter) {
    stack->data[stack->size] = letter;
    stack->size++;
}

int stack_int_pop(struct stack_int *restrict stack) {
    if (stack->size == 0) {
        exit(OutOfBoundariesStack);
    }
    stack->size--;
    return stack->data[stack->size];
}

char stack_char_pop(struct stack_char *restrict stack) {
    if (stack->size == 0) {
        exit(OutOfBoundariesStack);
    }
    stack->size--;
    return stack->data[stack->size];
}

char stack_char_peek(struct stack_char *restrict stack) {
    if (stack->size == 0) {
        exit(OutOfBoundariesStack);
    }
    return stack->data[stack->size - 1];
}

int stack_int_peek(struct stack_int *restrict stack) {
    if (stack->size == 0) {
        exit(OutOfBoundariesStack);
    }
    return stack->data[stack->size - 1];
}