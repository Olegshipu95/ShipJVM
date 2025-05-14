#include "stack_frames.h"

int
init_operand_stack (struct operand_stack *opstack, uint16_t max_stack)
{
  opstack->stack = my_alloc_array (struct jvariable, max_stack);
  if (opstack->stack == NULL)
    {
      prerr ("Can not allocate memory for operand stack");
      return ENOMEM;
    }

  opstack->top = -1;
  return 0;
}

int
init_local_vars (struct local_variables *locals, uint16_t size)
{
  locals->vars = my_alloc_array (struct jvariable, size);
  if (locals->vars == NULL)
    {
      prerr ("Can not allocate memory for local vars");
      return ENOMEM;
    }
  return 0;
}

struct stack_frame *
init_stack_frame (struct jclass *class, struct rt_method *method,
                  struct jvm *jvm)
{
  int err = 0;
  if (!class || !method || !jvm)
    {
      prerr ("Stack frame: class|method|jvm is null");
      return NULL;
    }
  struct stack_frame *frame = my_alloc (struct stack_frame);
  frame->jvm_runtime = jvm;
  frame->class = class;
  frame->method = method;
  frame->caller = NULL;

  frame->local_vars = my_alloc (struct local_variables);
  if (frame->local_vars == NULL)
    {
      prerr ("can not allocate memory for local_vars in stack frame");
      return NULL;
    }
  err = init_local_vars (frame->local_vars, method->code_attr->max_locals);
  if (err)
    {
      prerr ("init_local_vars return error - %d", err);
      return NULL;
    }

  frame->operand_stack = my_alloc (struct operand_stack);
  if (frame->operand_stack == NULL)
    {
      prerr ("can not allocate memory for local_vars in stack frame");
      return NULL;
    }
  err = init_operand_stack (frame->operand_stack,
                            method->code_attr->max_locals);
  if (err)
    {
      prerr ("init_operand_stack return error - %d", err);
      return NULL;
    }

  frame->code_length = method->code_attr->code_length;
  frame->code = method->code_attr->code;

  frame->pc = 0;
  frame->error = 0;
  return frame;
}

int
opstack_is_full (struct operand_stack *opstack)
{
  return opstack->top == (opstack->max_stack - 1);
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
  if (index >= locals->max_locals)
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
  if (index >= locals->max_locals)
    {
      prerr ("Illegal index in get_local_var");
      return EINVAL;
    }

  locals->vars[index] = value;
  return 0;
}

int
new_call_stack (struct call_stack **stack)
{
  struct call_stack *new = my_alloc (struct call_stack);
  if (new == NULL)
    {
      prerr ("Can not allocate memory for call_stack");
      return ENOMEM;
    }
  new->frames = my_alloc_array (struct stack_frame *, CALL_STACK_CAPACITY);
  new->size = 0;
  *stack = new;
  return 0;
}

int
call_stack_push (struct call_stack *stack, struct stack_frame *frame)
{
  if (stack->size >= CALL_STACK_CAPACITY)
    {
      prerr ("size >= CALL_STACK_CAPACITY");
      return -1;
    }
  stack->frames[stack->size++] = frame;
  return 0;
}

struct stack_frame *
call_stack_pop (struct call_stack *stack)
{
  if (stack->size == 0)
    return NULL;
  return stack->frames[--stack->size];
}

struct stack_frame *
call_stack_peek (struct call_stack *stack)
{
  if (stack->size == 0)
    return NULL;
  return stack->frames[stack->size - 1];
}

int
call_stack_is_empty (struct call_stack *stack)
{
  return stack->size == 0;
}

// ---- Invoke operations

int
validate_descriptor (const char *descriptor)
{
  if (descriptor == NULL || *descriptor != '(')
    {
      prerr ("Invalid method descriptor: %s",
             descriptor ? descriptor : "NULL");
      return EINVAL;
    }
  return 0;
}

int
parse_arg_type (const char **p, int *array_depth, char *base_type)
{
  *array_depth = 0;
  while (**p == '[')
    {
      (*array_depth)++;
      (*p)++;
    }

  switch (**p)
    {
    case 'B':
    case 'C':
    case 'D':
    case 'F':
    case 'I':
    case 'J':
    case 'S':
    case 'Z':
      *base_type = **p;
      (*p)++;
      return 0;

    case 'L':
      while (**p != ';' && **p != '\0')
        (*p)++;
      if (**p != ';')
        {
          prerr ("Malformed object type in descriptor");
          return EINVAL;
        }
      *base_type = 'L';
      (*p)++;
      return 0;

    default:
      prerr ("Unknown type in descriptor: %c", **p);
      return EINVAL;
    }
}

void
determine_expected_type (char base_type, int array_depth,
                         java_value_type *expected_type, int *is_wide)
{
  *is_wide = 0;

  if (array_depth > 0)
    {
      *expected_type = JOBJECT;
    }
  else
    {
      switch (base_type)
        {
        case 'D':
          *expected_type = JDOUBLE;
          *is_wide = 1;
          break;
        case 'J':
          *expected_type = JLONG;
          *is_wide = 1;
          break;
        case 'F':
          *expected_type = JFLOAT;
          break;
        case 'L':
          *expected_type = JOBJECT;
          break;
        default:
          *expected_type = JINT;
          break;
        }
    }
}

int
copy_single_arg (struct stack_frame *caller, struct stack_frame *callee,
                 int local_index, java_value_type expected_type)
{
  jvariable arg;

  if (opstack_pop (caller->operand_stack, &arg))
    {
      prerr ("Stack underflow while copying arguments");
      return EINVAL;
    }

  if (arg.type != expected_type)
    {
      prerr ("Type mismatch in argument %d", local_index);
      return EINVAL;
    }

  if (store_local_var (callee->local_vars, arg, local_index))
    {
      prerr ("Failed to store argument %d", local_index);
      return EINVAL;
    }

  return 0;
}

/**
 * Копирует аргументы из стека вызывающего фрейма в локальные переменные
 * вызываемого фрейма
 * @param caller Фрейм вызывающего метода
 * @param callee Фрейм вызываемого метода
 * @param descriptor Дескриптор метода (формата (Аргументы)ВозвращаемыйТип)
 * @return 0 при успехе, код ошибки при неудаче
 */
int
copy_arguments (struct stack_frame *caller, struct stack_frame *callee,
                const char *descriptor)
{
  const char *p = descriptor;
  int local_index = 0;
  int err;

  // 1. Validate descriptor
  if ((err = validate_descriptor (p)))
    return err;
  p++;

  // 2. Parse arguments
  while (*p != ')')
    {
      int array_depth, is_wide;
      char base_type;
      java_value_type expected_type;

      // Parse type
      if ((err = parse_arg_type (&p, &array_depth, &base_type)))
        return err;

      // Determine expected type
      determine_expected_type (base_type, array_depth, &expected_type,
                               &is_wide);

      // Copy argument
      if ((err = copy_single_arg (caller, callee, local_index, expected_type)))
        {
          return err;
        }

      // Wide types take two slots
      local_index += is_wide ? 2 : 1;
    }

  // 3. Skip return type
  p++;

  // 4. Verify stack is empty
  if (!opstack_is_empty (caller->operand_stack))
    {
      prerr ("Extra arguments on stack after parsing descriptor");
      return EINVAL;
    }

  return 0;
}