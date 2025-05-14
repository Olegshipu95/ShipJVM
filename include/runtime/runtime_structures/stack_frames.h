#ifndef SHIP_JVM_STACK_FRAMES_H
#define SHIP_JVM_STACK_FRAMES_H

#define MAX_ARG_COUNT 64
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include<unistd.h>


#include "java_types.h"
#include "runtime.h"
#include "runtime_class.h"
#include "util.h"

#define LOCAL_VARS_SIZE 100
#define MAX_OPERAND_STACK 100
#define CALL_STACK_CAPACITY 30

// ERROR TYPES
#define JVM_INVALID_BYTECODE 1001
#define JVM_STACK_OVERFLOW 1002
#define JVM_ILLEGAL_LOCAL_INDEX 1003
#define JVM_ILLEGAL_BRANCH_JUMP 1004
#define JVM_NULL_POINTER 1005

struct jvm;

struct operand_stack
{
  uint16_t max_stack;
  jvariable *stack; // size of MAX_OPERAND_STACK
  // Index of the top element in the stack
  jsize top;
};

struct local_variables
{
  uint16_t max_locals;
  jvariable *vars; // size of LOCAL_VARS_SIZE
};

struct stack_frame
{
  struct jvm *jvm_runtime;
  struct jclass *class;       // current class
  struct rt_method *method;   // current method
  struct stack_frame *caller; // The frame that called this (NULL for main)
  struct local_variables *local_vars;  // Local variables
  struct operand_stack *operand_stack; // Operand stack
  uint32_t code_length;
  struct runtime_opcode *code;
  uint32_t pc; // Program counter (index in code[])
  int error;
};

struct call_stack
{
  struct stack_frame **frames; // array of pointers on stack_frames
  size_t size;
};

int init_operand_stack (struct operand_stack *, uint16_t);
int init_local_vars (struct local_variables *, uint16_t);

struct stack_frame *init_stack_frame (struct jclass *jclass,
                                      struct rt_method *method,
                                      struct jvm *jvm);

int opstack_push (struct operand_stack *opstack, jvariable value);

int opstack_pop (struct operand_stack *opstack, jvariable *value);

int opstack_peek (struct operand_stack *opstack, jvariable *value);

int
opstack_peek_nth(struct operand_stack *stack, int n, jvariable *out);

int opstack_is_full (struct operand_stack *opstack);

int opstack_is_empty (struct operand_stack *opstack);

int get_local_var (struct local_variables *, jvariable *value, uint32_t index);

int store_local_var (struct local_variables *, jvariable value,
                     uint32_t index);

int new_call_stack (struct call_stack **stack);
int call_stack_push (struct call_stack *stack, struct stack_frame *frame);
struct stack_frame *call_stack_pop (struct call_stack *stack);
struct stack_frame *call_stack_peek (struct call_stack *stack);
int call_stack_is_empty (struct call_stack *stack);

int count_arguments_in_descriptor(const char *descriptor);

int
copy_arguments(struct stack_frame *caller,
               struct stack_frame *callee,
               const char *descriptor,
               int has_this);

int execute_frame (struct jvm *jvm, struct stack_frame *frame);

int ensure_class_initialized (struct jvm *jvm, struct jclass *cls);

int find_method_in_hierarchy(struct jvm* jvm, struct jclass *start,
                             struct rt_method **out_method,
                             const char *name,
                             const char *descriptor);


#endif