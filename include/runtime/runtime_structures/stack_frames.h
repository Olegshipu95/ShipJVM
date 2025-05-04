#ifndef SHIP_JVM_STACK_FRAMES_H
#define SHIP_JVM_STACK_FRAMES_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>

#include "java_types.h"
#include "util.h"

#define LOCAL_VARS_SIZE 100
#define MAX_OPERAND_STACK 100

struct operand_stack
{
  jvariable *stack; // size of MAX_OPERAND_STACK
  // Index of the top element in the stack
  jsize top;
};

struct local_variables
{
  jvariable *vars; // size of LOCAL_VARS_SIZE
};

struct stack_frame
{
  struct local_variables *local_vars;
  struct operand_stack *operand_stack;
  uint32_t pc;
};

int init_operand_stack (struct operand_stack *);
int init_local_vars (struct local_variables *);
int init_stack_frame (struct stack_frame *);

int opstack_push (struct operand_stack *opstack, jvariable value);

int opstack_pop (struct operand_stack *opstack, jvariable *value);

int opstack_peek (struct operand_stack *opstack, jvariable *value);

int opstack_is_full (struct operand_stack *opstack);

int opstack_is_empty (struct operand_stack *opstack);

int get_local_var (struct local_variables *, jvariable *value, uint32_t index);

int store_local_var (struct local_variables *, jvariable value,
                     uint32_t index);

#endif