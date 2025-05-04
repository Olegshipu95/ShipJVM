#include "stack_frames.h"

int
init_operand_stack (struct operand_stack *opstack)
{
  opstack->stack = my_alloc_array (struct jvariable, MAX_OPERAND_STACK);
  if (opstack->stack == NULL)
    {
      prerr ("Can not allocate memory for operand stack");
      return ENOMEM;
    }

  opstack->top = -1;
  return 0;
}

int
init_local_vars (struct local_variables *locals)
{
  locals->vars = my_alloc_array (struct jvariable, LOCAL_VARS_SIZE);
  if (locals->vars == NULL)
    {
      prerr ("Can not allocate memory for local vars");
      return ENOMEM;
    }
  return 0;
}

int
init_stack_frame (struct stack_frame *frame)
{
  int err = 0;

  frame->local_vars = my_alloc (struct local_variables);
  if (frame->local_vars == NULL)
    {
      prerr ("can not allocate memory for local_vars in stack frame");
      return ENOMEM;
    }
  err = init_local_vars (frame->local_vars);
  if (err)
    {
      prerr ("init_local_vars return error - %d", err);
      return err;
    }

  frame->operand_stack = my_alloc (struct operand_stack);
  if (frame->operand_stack == NULL)
    {
      prerr ("can not allocate memory for local_vars in stack frame");
      return ENOMEM;
    }
  err = init_operand_stack (frame->operand_stack);
  if (err)
    {
      prerr ("init_operand_stack return error - %d", err);
      return err;
    }

  frame->pc = 0;
  return 0;
}

int
opstack_is_full (struct operand_stack *opstack)
{
  return opstack->top == (MAX_OPERAND_STACK - 1);
}

int
opstack_is_empty (struct operand_stack *opstack)
{
  return opstack->top == -1;
}

int
opstack_push (struct operand_stack *opstack, jvariable value)
{
  if (opstack_is_full (opstack))
    {
      prerr ("Operand stack overflow");
      return -1;
    }
  opstack->stack[++(opstack->top)] = value;
  return 0;
}

int
opstack_pop (struct operand_stack *opstack, jvariable *value)
{
  if (opstack_is_empty (opstack))
    {
      prerr ("Stack underflow");
      return -1;
    }

  if (value == NULL)
    {
      prerr ("Pointer on value is NULL");
      return EINVAL;
    }
  // Return the top value
  jvariable popped = opstack->stack[opstack->top];
  --(opstack->top);
  *value = popped;

  return 0;
}

int
opstack_peek (struct operand_stack *opstack, jvariable *value)
{
  if (opstack_is_empty (opstack))
    {
      prerr ("Stack underflow");
      return -1;
    }

  if (value == NULL)
    {
      prerr ("Pointer on value is NULL");
      return EINVAL;
    }

  jvariable popped = opstack->stack[opstack->top];
  *value = popped;
  return 0;
}

int
get_local_var (struct local_variables *locals, jvariable *value,
               uint32_t index)
{
  if (index >= LOCAL_VARS_SIZE)
    {
      prerr ("Illegal index in get_local_var");
      return EINVAL;
    }

  if (value == NULL)
    {
      prerr ("Illegal pointer on value in get_local_var");
      return EINVAL;
    }

  *value = locals->vars[index];
  return 0;
}

int
store_local_var (struct local_variables *locals, jvariable value,
                 uint32_t index)
{
  if (index >= LOCAL_VARS_SIZE)
    {
      prerr ("Illegal index in get_local_var");
      return EINVAL;
    }

  locals->vars[index] = value;
  return 0;
}