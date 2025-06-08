#include "stack_frames.h"
#include "classloader.h"
#include "runtime_attribute.h"
#include "runtime_class_util.h"
#include "string.h"

int
init_operand_stack (struct operand_stack *opstack, uint16_t max_stack)
{
  opstack->stack = my_alloc_array (struct jvariable, max_stack);
  if (opstack->stack == NULL)
    {
      prerr ("Can not allocate memory for operand stack");
      return ENOMEM;
    }
  opstack->max_stack = max_stack;
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
  locals->max_locals = size;
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

  // TODO
  if ((method->access_flags & ACC_NATIVE) && method->code_attr == NULL)
    {
      frame->code_length = 0;
      frame->code = NULL;

      // безопасные значения
      frame->local_vars = my_alloc (struct local_variables);
      init_local_vars (frame->local_vars, 10); // безопасный дефолт

      frame->operand_stack = my_alloc (struct operand_stack);
      init_operand_stack (frame->operand_stack, 10); // безопасный дефолт

      frame->pc = 0;
      frame->error = 0;
      return frame;
    }

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
                            method->code_attr->max_stack);
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

// ---- OPSTACK OPERATIONS ----

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
opstack_peek_nth (struct operand_stack *stack, int n, jvariable *out)
{
  if (!stack || !out || n < 0)
    {
      prerr ("opstack_peek_nth: stack or variable are null | n is 0");
      return EINVAL;
    }
  printf ("opstack size : %d\n", stack->top);

  if (stack->top < n)
    {
      prerr ("opstack_peek_nth: Opstack underflow");
      return EINVAL; // недостаточно элементов в стеке
    }

  if (opstack_is_empty (stack))
    {
      prerr ("OPSTACK is empty");
      return EINVAL;
    }
  *out = stack->stack[stack->top - n];
  return 0;
}

void
debug_print_operand_stack (struct operand_stack *opstack)
{
  printf ("  >> Operand Stack: size = %d\n", opstack->top + 1);

  for (int i = opstack->top; i >= 0; i--)
    {
      jvariable var = opstack->stack[i];
      printf ("    [%d] ", opstack->top - i); // индекс сверху вниз

      switch (var.type)
        {
        case JBOOLEAN:
          printf ("JBOOLEAN = %s\n", var.value._bool ? "true" : "false");
          break;
        case JBYTE:
          printf ("JBYTE = %d\n", var.value._byte);
          break;
        case JCHAR:
          printf ("JCHAR = '%c' (0x%04x)\n", var.value._char, var.value._char);
          break;
        case JSHORT:
          printf ("JSHORT = %d\n", var.value._short);
          break;
        case JINT:
          printf ("JINT = %d\n", var.value._int);
          break;
        case JLONG:
          printf ("JLONG = %lld\n", (long long)var.value._long);
          break;
        case JFLOAT:
          printf ("JFLOAT = %f\n", var.value._float);
          break;
        case JDOUBLE:
          printf ("JDOUBLE = %f\n", var.value._double);
          break;
        case JOBJECT:
          printf ("JOBJECT = %p\n", (void *)var.value._object);
          break;
        default:
          printf ("UNKNOWN TYPE (%d)\n", var.type);
        }
    }

  printf ("\n");
}

// ---- LOCAL VARIABLES ----

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

// ---- CALL STACK OPERATIONS

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

int
count_arguments_in_descriptor (const char *descriptor)
{
  if (!descriptor || *descriptor != '(')
    return -1;

  int count = 0;
  const char *p = descriptor + 1;

  while (*p && *p != ')')
    {
      while (*p == '[') // массивы
        p++;

      if (*p == 'L')
        { // объектный тип
          while (*p && *p != ';')
            p++;
          if (*p == ';')
            p++;
          else
            return -1;
        }
      else if (strchr ("BCDFIJSZ", *p))
        {
          count++;
          p++;
        }
      else
        {
          return -1; // ошибка
        }

      count++;
    }

  if (*p != ')')
    return -1;

  return count;
}

int
copy_arguments (struct stack_frame *caller, struct stack_frame *callee,
                const char *descriptor, int has_this)
{
  const char *p = descriptor;
  int err;
  int local_index = has_this ? 1 : 0;

  // 1. Validate descriptor
  if ((err = validate_descriptor (p)))
    return err;
  p++; // Пропускаем '('

  // 2. Пропарсим все аргументы в массив типов
  typedef struct
  {
    java_value_type type;
    int is_wide;
  } arg_info;

  arg_info args[MAX_ARG_COUNT];
  int arg_count = 0;

  while (*p != ')')
    {
      int array_depth, is_wide;
      char base_type;
      java_value_type expected_type;

      if ((err = parse_arg_type (&p, &array_depth, &base_type)))
        return err;

      determine_expected_type (base_type, array_depth, &expected_type,
                               &is_wide);

      if (arg_count >= MAX_ARG_COUNT)
        {
          prerr ("Too many method arguments");
          return E2BIG;
        }

      args[arg_count].type = expected_type;
      args[arg_count].is_wide = is_wide;
      arg_count++;
    }
  printf ("ARG_COUNT = %d\n\n", arg_count);

  // 3. Копируем аргументы в локальные переменные в обратном порядке
  for (int i = arg_count - 1; i >= 0; i--)
    {
      jvariable arg;
      if (opstack_pop (caller->operand_stack, &arg))
        {
          prerr ("Stack underflow while copying argument %d", i);
          return EINVAL;
        }

      if (arg.type != args[i].type)
        {
          prerr ("Type mismatch in argument %d (expected %d, got %d)", i,
                 args[i].type, arg.type);
          return EINVAL;
        }

      if ((err = store_local_var (callee->local_vars, arg, local_index)))
        return err;

      local_index += args[i].is_wide ? 2 : 1;
    }

  // 3. Начинаем с this-объекта, если метод нестатический
  if (has_this)
    {
      jvariable this_ref;
      if (opstack_pop (caller->operand_stack, &this_ref))
        {
          prerr ("Stack underflow while copying 'this'");
          return EINVAL;
        }
      if (this_ref.type != JOBJECT)
        {
          prerr ("'this' is not an object reference");
          return EINVAL;
        }
      if ((err = store_local_var (callee->local_vars, this_ref, 0)))
        return err;
      local_index++;
    }

  return 0;
}

int
execute_frame (struct jvm *jvm, struct stack_frame *frame)
{
  call_stack_push (jvm->call_stack, frame);

  while (!call_stack_is_empty (jvm->call_stack))
    {
      struct stack_frame *current_frame = call_stack_peek (jvm->call_stack);

      if (current_frame->pc >= current_frame->code_length)
        {
          call_stack_pop (jvm->call_stack);
          continue;
        }

      struct runtime_opcode op = current_frame->code[current_frame->pc];
      uint32_t old_pc = current_frame->pc;

      printf ("[%s.%s%s] PC=%u: %s\n", current_frame->class->this_class,
              current_frame->method->name, current_frame->method->descriptor,
              current_frame->pc, op.name);

      op.handler (current_frame);

      debug_print_operand_stack (current_frame->operand_stack);

      if (current_frame->pc == old_pc)
        {
          current_frame->pc++;
        }

      if (current_frame->error)
        {
          // if (!handle_exception(current_frame)) {
          prerr ("Unhandled exception in method %s",
                 current_frame->method->name);
          return -1;
          // }
        }
    }

  return 0;
}

int
ensure_class_initialized (struct jvm *jvm, struct jclass *cls)
{
  int err;
  if (cls->initialized)
    return 0; // уже всё сделано

  if (cls->being_initialized)
    return 0; // предотвращаем рекурсию (спецификация это разрешает)

  cls->being_initialized = true;

  struct rt_method *clinit_method = NULL;
  if (!find_method_in_current_class (cls, &clinit_method, "<clinit>", "()V"))
    {
      // IT IS VERY BAD, NEED CHANGE. TODO
      struct jvm *clinit_jvm = new_jvm ();
      clinit_jvm->classloader = jvm->classloader;
      heap_destroy (clinit_jvm->heap);
      clinit_jvm->heap = jvm->heap;

      if (new_call_stack (&clinit_jvm->call_stack))
        {
          prerr ("Call stack creation failed");
          return -1;
        }

      struct stack_frame *clinit_frame
          = init_stack_frame (cls, clinit_method, clinit_jvm);
      if (!clinit_frame)
        return -1;

      err = execute_frame (clinit_jvm, clinit_frame);
      if (err)
        {
          prerr ("ensure_class_initialized: error");
          // free_frame(clinit_frame);
          return -1;
        }
      // free_frame(clinit_frame);
    }

  cls->being_initialized = false;
  cls->initialized = true;

  return 0;
}

int
find_method_in_hierarchy (struct jvm *jvm, struct jclass *start,
                          struct rt_method **out_method, const char *name,
                          const char *descriptor)
{
  struct jclass *cls = start;

  while (cls)
    {
      for (int i = 0; i < cls->methods_data.methods_count; i++)
        {
          struct rt_method *m = &cls->methods_data.methods[i];

          if (strcmp (m->name, name) == 0
              && strcmp (m->descriptor, descriptor) == 0)
            {
              *out_method = m;
              return 0;
            }
        }

      // Переход к суперклассу
      if (!cls->super_class)
        break;

      struct jclass *super;
      if (classloader_load_class (jvm->classloader, jvm->heap,
                                  cls->super_class, &super))
        return ENOENT;

      cls = super;
    }

  return ENOENT;
}
