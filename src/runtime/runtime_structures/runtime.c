#include "runtime.h"

jvariable
create_empty_args_variable ()
{
  jvariable var;
  var.type = JOBJECT;

  var.value._object = NULL;

  return var;
}

int
run_jvm (struct jvm *jvm)
{
  if (new_call_stack (&jvm->call_stack))
    {
      prerr ("Call stack creation failed");
      return -1;
    }

  struct rt_method *main_method = NULL;
  if (find_method_in_current_class (jvm->main_class, &main_method, "main",
                                    "([Ljava/lang/String;)V"))
    {
      prerr ("Main method not found");
      return -1;
    }

  if (ensure_class_initialized (jvm, jvm->main_class))
    {
      prerr ("Failed to initialize main class (<clinit> failed)");
      return -1;
    }

  struct stack_frame *main_frame
      = init_stack_frame (jvm->main_class, main_method, jvm);
  if (!main_frame)
    {
      prerr ("Failed to initialize main frame");
      return -1;
    }

  // Устанавливаем пустой args
  main_frame->local_vars->vars[0] = create_empty_args_variable ();

  printf ("\n\n\n START EXECUTION MAIN\n\n\n\n");

  int result = execute_frame (jvm, main_frame);

  printf ("Execution completed %s\n",
          result == 0 ? "successfully" : "with errors");

  return result;
}
