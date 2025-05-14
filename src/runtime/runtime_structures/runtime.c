#include "runtime.h"

struct jvm *
new_jvm ()
{
  struct jvm *new_jvm = my_alloc (struct jvm);
  new_jvm->main_class = NULL;
  new_jvm->classloader = NULL;
  return new_jvm;
}

int
run_jvm (struct jvm *jvm)
{
  int err;
  struct rt_method *main_method = NULL;
  err = find_method_in_current_class (jvm->main_class, &main_method, "main",
                                      "([Ljava/lang/String;)V");
  if (err)
    {
      prerr ("Can not find Main method");
      return -1;
    }
  err = new_call_stack (&jvm->call_stack);
  if (err)
    {
      prerr ("Can not create call stack for jvm");
      return -1;
    }

  struct stack_frame *main_frame
      = init_stack_frame (jvm->main_class, main_method, jvm);
  if (!main_frame)
    {
      prerr ("Can not create main_frame");
      return -1;
    }

  call_stack_push (jvm->call_stack, main_frame);

  // while (!call_stack_is_empty(jvm->call_stack)) {
  //   struct stack_frame *current_frame = call_stack_peek(jvm->call_stack);

  //   if (current_frame->pc >= current_frame->code_length) {
  //       call_stack_pop(jvm->call_stack);
  //       continue;
  //   }

  //   struct runtime_opcode op = current_frame->code[current_frame->pc];
  //   uint32_t old_pc;

  //   printf("[%s.%s%s] PC=%u: %s\n",
  //          current_frame->class->this_class,
  //          current_frame->method->name,
  //          current_frame->method->descriptor,
  //          current_frame->pc, op.name);

  // Execute the instruction
  // op.handler(current_frame);

  // Increment PC if the instruction did not change it (jump, return, etc.)
  // if (current_frame->pc == old_pc) {
  //     current_frame->pc++;
  // }

  // if (check_exceptions(current_frame)) {
  //     handle_exception(current_frame);
  // }
  // }

  printf ("Execution completed successfully\n");
  return 0;
}