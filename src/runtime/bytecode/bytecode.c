#include "bytecodes.h"

void
_common_store (struct stack_frame *frame, java_value_type type, uint32_t index)
{
  int err;
  jvariable var;

  if (opstack_pop (frame->operand_stack, &var))
    {
      prerr ("Failed to pop from stack");
      frame->error = ENOMEM;
      return;
    }

  if (check_var_type (&var, type))
    {
      prerr ("Type mismatch in store: expected %d", type);
      frame->error = ENOMEM;
      return;
    }

  err = store_local_var (frame->local_vars, var, index);
  if (err)
    {
      prerr ("STORE: can not store local var");
      frame->error = ENOMEM;
      return;
    }
}

void
_common_load (struct stack_frame *frame, java_value_type type, uint32_t index)
{
  jvariable var;
  get_local_var (frame->local_vars, &var, index);

  if (var.type != type)
    {
      prerr ("Type mismatch in load: expected %d", type);
      frame->error = EINVAL;
      return;
    }

  if (opstack_push (frame->operand_stack, var))
    {
      prerr ("Failed to push variable to stack");
      frame->error = EINVAL;
      return;
    }
}

// TODO
void
opcode_aaload (struct stack_frame *)
{
}

// TODO
void
opcode_aastore (struct stack_frame *)
{
}

void
opcode_aconst_null (struct stack_frame *frame)
{
  jvariable result = create_variable (JOBJECT);
  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in ACONST_NULL");
      frame->error = EINVAL;
      return;
    }
};

// TODO
void
opcode_aload (struct stack_frame *)
{
}

void
opcode_aload_0 (struct stack_frame *frame)
{
  _common_load (frame, JOBJECT, 0);
}

void
opcode_aload_1 (struct stack_frame *frame)
{
  _common_load (frame, JOBJECT, 1);
}

void
opcode_aload_2 (struct stack_frame *frame)
{
  _common_load (frame, JOBJECT, 2);
}

void
opcode_aload_3 (struct stack_frame *frame)
{
  _common_load (frame, JOBJECT, 3);
}

// TODO
void
opcode_anewarray (struct stack_frame *)
{
}
// TODO
void
opcode_areturn (struct stack_frame *)
{
}

// TODO
void
opcode_arraylength (struct stack_frame *)
{
}

void
_common_astore (struct stack_frame *frame, uint32_t index)
{
  jvariable var;
  opstack_pop (frame->operand_stack, &var);

  store_local_var (frame->local_vars, var, index);
}
// TODO
void
opcode_astore (struct stack_frame *)
{
}

void
opcode_astore_0 (struct stack_frame *frame)
{
  _common_store (frame, JOBJECT, 0);
}

void
opcode_astore_1 (struct stack_frame *frame)
{
  _common_store (frame, JOBJECT, 1);
}

void
opcode_astore_2 (struct stack_frame *frame)
{
  _common_store (frame, JOBJECT, 2);
}

void
opcode_astore_3 (struct stack_frame *frame)
{
  _common_store (frame, JOBJECT, 3);
}
// TODO
void
opcode_athrow (struct stack_frame *)
{
}
// TODO
void
opcode_baload (struct stack_frame *)
{
}
// TODO
void
opcode_bastore (struct stack_frame *)
{
}

void
opcode_bipush (struct stack_frame *frame)
{
  ++frame->pc;
  if (frame->pc >= frame->code_length)
    {
      prerr ("Truncated bytecode in bipush: missing byte operand");
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }
  uint8_t byte_value = frame->code[frame->pc].raw_byte;
  jvariable push_value = create_variable (JINT);
  push_value.value._int = byte_value;

  if (opstack_push (frame->operand_stack, push_value))
    {
      prerr ("Stack overflow in bipush");
      frame->error = JVM_STACK_OVERFLOW;
      return;
    }
  frame->pc++;
}

// TODO
void
opcode_caload (struct stack_frame *)
{
}

// TODO
void
opcode_castore (struct stack_frame *)
{
}

// TODO
void
opcode_checkcast (struct stack_frame *)
{
}

void
opcode_d2f (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in D2F");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JDOUBLE))
    {
      prerr ("Type mismatch in D2F: expected double");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = (jfloat)op1.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in D2F");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_d2i (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in D2I");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JDOUBLE))
    {
      prerr ("Type mismatch in D2I: expected double");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);

  if (op1.value._double != op1.value._double)
    {
      result.value._int = 0;
    }
  else if (op1.value._double >= INT32_MAX)
    {
      result.value._int = INT32_MAX;
    }
  else if (op1.value._double <= INT32_MIN)
    {
      result.value._int = INT32_MIN;
    }
  else
    {
      result.value._int = (jint)op1.value._double;
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in D2I");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_d2l (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in D2L");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JDOUBLE))
    {
      prerr ("Type mismatch in D2L: expected double");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);

  if (op1.value._double != op1.value._double)
    {
      result.value._long = 0;
    }
  else if (op1.value._double >= INT64_MAX)
    {
      result.value._long = INT64_MAX;
    }
  else if (op1.value._double <= INT64_MIN)
    {
      result.value._long = INT64_MIN;
    }
  else
    {
      result.value._long = (jlong)op1.value._double;
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in D2L");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_dadd (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= check_var_type (&op1, JDOUBLE);
  err |= check_var_type (&op2, JDOUBLE);
  if (err != 0)
    {
      prerr ("Take incorrect data from opstack in dadd");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JDOUBLE);
  result.value._double = op1.value._double + op2.value._double;
  opstack_push (frame->operand_stack, result);
}

void
opcode_daload (struct stack_frame *)
{
}

// TODO
void
opcode_dastore (struct stack_frame *)
{
}

// TODO
void
opcode_dcmpg (struct stack_frame *)
{
}

// TODO
void
opcode_dcmpl (struct stack_frame *)
{
}

void
_common_dconst (struct stack_frame *frame, jdouble value)
{
  jvariable var = create_variable (JDOUBLE);
  var.value._double = value;
  opstack_push (frame->operand_stack, var);
}

void
opcode_dconst_0 (struct stack_frame *frame)
{
  _common_dconst (frame, 0.0);
}

void
opcode_dconst_1 (struct stack_frame *frame)
{
  _common_dconst (frame, 1.0);
}

// TODO
void
opcode_ddiv (struct stack_frame *)
{
}

// TODO
void
opcode_dload (struct stack_frame *)
{
}

void
opcode_dload_0 (struct stack_frame *frame)
{
  _common_load (frame, JDOUBLE, 0);
}

void
opcode_dload_1 (struct stack_frame *frame)
{
  _common_load (frame, JDOUBLE, 1);
}

void
opcode_dload_2 (struct stack_frame *frame)
{
  _common_load (frame, JDOUBLE, 2);
}

void
opcode_dload_3 (struct stack_frame *frame)
{
  _common_load (frame, JDOUBLE, 3);
}

void
opcode_dmul (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in DMUL");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JDOUBLE) || check_var_type (&op2, JDOUBLE))
    {
      prerr ("Type mismatch in DMUL: expected double");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = op1.value._double * op2.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DMUL");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_dneg (struct stack_frame *frame)
{
  jvariable val;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &val);
  err |= check_var_type (&val, JDOUBLE);

  if (err)
    {
      prerr ("DNEG operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = -val.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DNEG");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_drem (struct stack_frame *frame)
{
  jvariable value1, value2;

  if (opstack_pop (frame->operand_stack, &value2)
      || opstack_pop (frame->operand_stack, &value1))
    {
      prerr ("Stack underflow in DREM");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&value1, JDOUBLE) || check_var_type (&value2, JDOUBLE))
    {
      prerr ("Type mismatch in DREM: expected double");
      frame->error = EINVAL;
      return;
    }

  if (value2.value._double == 0)
    {
      prerr ("ArithmeticException: division by zero in DREM"); // EXCEPTION
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double
      = value1.value._double
        - (value1.value._double / value2.value._double) * value2.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DREM");
      frame->error = EINVAL;
      return;
    }
};

// TODO
void
opcode_dreturn (struct stack_frame *)
{
}

// TODO
void
opcode_dstore (struct stack_frame *)
{
}

void
opcode_dstore_0 (struct stack_frame *frame)
{
  _common_store (frame, JDOUBLE, 0);
}

void
opcode_dstore_1 (struct stack_frame *frame)
{
  _common_store (frame, JDOUBLE, 1);
}

void
opcode_dstore_2 (struct stack_frame *frame)
{
  _common_store (frame, JDOUBLE, 2);
}

void
opcode_dstore_3 (struct stack_frame *frame)
{
  _common_store (frame, JDOUBLE, 3);
}

void
opcode_dsub (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in DSUB");
      frame->error = EINVAL;
      return;
    }

  // Type checking
  if (check_var_type (&op1, JDOUBLE) || check_var_type (&op2, JDOUBLE))
    {
      prerr ("Type mismatch in DSUB: expected double");
      frame->error = EINVAL;
      return;
    }

  // Perform subtraction
  jvariable result = create_variable (JDOUBLE);
  result.value._double = op1.value._double - op2.value._double;

  // Push result
  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DSUB");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_dup (struct stack_frame *frame)
{
  jvariable op1;
  if (opstack_peek (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in DUP");
      frame->error = EINVAL;
      return;
    }

  if (opstack_push (frame->operand_stack, op1))
    {
      prerr ("Stack overflow in DUP");
      frame->error = EINVAL;
      return;
    }
};

void
opcode_dup_x1 (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op1)
      || opstack_pop (frame->operand_stack, &op2))
    {
      prerr ("Stack underflow in DUP_X1");
      frame->error = EINVAL;
      return;
    }

  if (var_computation_type (&op1) == 1 || var_computation_type (&op2) == 1)
    {
      prerr ("Args are not category 1 computational type in DUP_X1");
      frame->error = EINVAL;
      return;
    }

  if (opstack_push (frame->operand_stack, op1)
      || opstack_push (frame->operand_stack, op2)
      || opstack_push (frame->operand_stack, op1))
    {
      prerr ("Stack overflow in DUP_X1");
      frame->error = EINVAL;
      return;
    }
};

void
opcode_dup_x2 (struct stack_frame *frame)
{
  jvariable op1, op2, op3;
  int computation_type;

  if (opstack_pop (frame->operand_stack, &op1)
      || opstack_pop (frame->operand_stack, &op2))
    {
      prerr ("Stack underflow in DUP_X2");
      frame->error = EINVAL;
      return;
    }

  if (var_computation_type (&op1) != 1)
    {
      prerr ("Value1 must be 1 computational type in DUP_X2");
      frame->error = EINVAL;
      return;
    }

  computation_type = var_computation_type (&op2);

  if (computation_type == 1)
    {
      if (opstack_pop (frame->operand_stack, &op3))
        {
          prerr ("Stack underflow in DUP_X2");
          frame->error = EINVAL;
          return;
        }
      if (var_computation_type (&op3) == 1)
        {
          if (opstack_push (frame->operand_stack, op1)
              || opstack_push (frame->operand_stack, op3)
              || opstack_push (frame->operand_stack, op2)
              || opstack_push (frame->operand_stack, op1))
            {
              prerr ("Stack overflow in DUP_X2");
              frame->error = EINVAL;
              return;
            }
        }
      else
        {
          prerr ("Value3 must be 1 computational type in DUP_X2");
          frame->error = EINVAL;
          return;
        }
    }
  else if (computation_type == 2)
    {
      if (opstack_push (frame->operand_stack, op1)
          || opstack_push (frame->operand_stack, op2)
          || opstack_push (frame->operand_stack, op1))
        {
          prerr ("Stack overflow in DUP_X2");
          frame->error = EINVAL;
          return;
        }
    }
  else
    {
      prerr ("Value2 undefined computational type in DUP_X2");
      frame->error = EINVAL;
      return;
    }
}

// TODO
void
opcode_dup2 (struct stack_frame *)
{
} // try to reuse

// TODO
void
opcode_dup2_x1 (struct stack_frame *)
{
}

// TODO
void
opcode_dup2_x2 (struct stack_frame *)
{
}

void
opcode_f2d (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in F2D");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JFLOAT))
    {
      prerr ("Type mismatch in F2D: expected float");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = (jdouble)op1.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in F2D");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_f2i (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in F2I");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JFLOAT))
    {
      prerr ("Type mismatch in F2I: expected float");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);

  if (op1.value._float != op1.value._float)
    {
      result.value._int = 0;
    }
  else if (op1.value._float >= INT32_MAX)
    {
      result.value._int = INT32_MAX;
    }
  else if (op1.value._float <= INT32_MIN)
    {
      result.value._int = INT32_MIN;
    }
  else
    {
      result.value._int = (jint)op1.value._float;
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in F2I");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_f2l (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in F2L");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JFLOAT))
    {
      prerr ("Type mismatch in F2L: expected float");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);

  if (op1.value._float != op1.value._float)
    {
      result.value._long = 0;
    }
  else if (op1.value._float >= INT64_MAX)
    {
      result.value._long = INT64_MAX;
    }
  else if (op1.value._float <= INT64_MIN)
    {
      result.value._long = INT64_MIN;
    }
  else
    {
      result.value._long = (jlong)op1.value._float;
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in F2L");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_fadd (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= check_var_type (&op1, JFLOAT);
  err |= check_var_type (&op2, JFLOAT);
  if (err != 0)
    {
      prerr ("Take incorrect data from opstack in fadd");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JFLOAT);
  result.value._float = op1.value._float + op2.value._float;
  opstack_push (frame->operand_stack, result);
}

// TODO
void
opcode_faload (struct stack_frame *)
{
}

// TODO
void
opcode_fastore (struct stack_frame *)
{
}

// TODO
void
opcode_fcmpg (struct stack_frame *)
{
}

// TODO
void
opcode_fcmpl (struct stack_frame *)
{
}

void
_common_fconst (struct stack_frame *frame, jfloat value)
{
  jvariable var = create_variable (JFLOAT);
  var.value._float = value;
  opstack_push (frame->operand_stack, var);
}

void
opcode_fconst_0 (struct stack_frame *frame)
{
  _common_fconst (frame, 0.0f);
}

void
opcode_fconst_1 (struct stack_frame *frame)
{
  _common_fconst (frame, 1.0f);
}

void
opcode_fconst_2 (struct stack_frame *frame)
{
  _common_fconst (frame, 2.0f);
}

// TODO
void
opcode_fdiv (struct stack_frame *)
{
}

void
opcode_fload (struct stack_frame *frame)
{
  uint8_t index;
  jvariable value;
  int err;

  ++frame->pc;
  if (frame->pc >= frame->code_length)
    {
      prerr ("Truncated bytecode in fload: missing index operand");
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }
  index = frame->code[frame->pc].raw_byte;

  err = get_local_var (frame->local_vars, &value, index);
  if (err)
    {
      prerr ("Failed to get local variable %d in fload", index);
      frame->error = err;
      return;
    }

  if (value.type != JFLOAT)
    {
      prerr ("Type mismatch in fload: expected float at index %d", index);
      frame->error = EINVAL; // Invalid argument
      return;
    }

  // 5. Помещаем значение в стек операндов
  err = opstack_push (frame->operand_stack, value);
  if (err)
    {
      prerr ("Stack overflow in fload");
      frame->error = ENOMEM; // Not enough space
      return;
    }

  ++frame->pc;
}

void
opcode_fload_0 (struct stack_frame *frame)
{
  _common_load (frame, JFLOAT, 0);
}

void
opcode_fload_1 (struct stack_frame *frame)
{
  _common_load (frame, JFLOAT, 1);
}

void
opcode_fload_2 (struct stack_frame *frame)
{
  _common_load (frame, JFLOAT, 2);
}

void
opcode_fload_3 (struct stack_frame *frame)
{
  _common_load (frame, JFLOAT, 3);
}

void
opcode_fmul (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in FMUL");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JFLOAT) || check_var_type (&op2, JFLOAT))
    {
      prerr ("Type mismatch in FMUL: expected float");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = op1.value._float * op2.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in FMUL");
      frame->error = EINVAL;
      return;
    }
}
// TODO
void
opcode_fneg (struct stack_frame *)
{
}
// {
//     jvariable val;
//     int err = 0;

//     err |= opstack_pop(frame->operand_stack, &val);
//     err |= check_var_type(&val, JFLOAT);

//     if (err) {
//         prerr("FNEG operation failed");
//         return;
//     }

//     jvariable result = create_variable(JFLOAT);

//     if (isnan(val.value._float)) {
//         result.value._float = -val.value._float;
//     } else {
//         result.value._float = -val.value._float;
//     }

//     if (opstack_push(frame->operand_stack, result)) {
//         prerr("Stack overflow in FNEG");
//     }
// }

void
opcode_frem (struct stack_frame *frame)
{
  jvariable value1, value2;

  if (opstack_pop (frame->operand_stack, &value2)
      || opstack_pop (frame->operand_stack, &value1))
    {
      prerr ("Stack underflow in FREM");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&value1, JFLOAT) || check_var_type (&value2, JFLOAT))
    {
      prerr ("Type mismatch in FREM: expected float");
      frame->error = EINVAL;
      return;
    }

  if (value2.value._int == 0)
    {
      prerr ("ArithmeticException: division by zero in FREM"); // EXCEPTION
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float
      = value1.value._float
        - (value1.value._float / value2.value._float) * value2.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in FREM");
      frame->error = EINVAL;
      return;
    }
};
// TODO
void
opcode_freturn (struct stack_frame *)
{
}

// TODO
void
opcode_fstore (struct stack_frame *)
{
}

void
opcode_fstore_0 (struct stack_frame *frame)
{
  _common_store (frame, JFLOAT, 0);
}

void
opcode_fstore_1 (struct stack_frame *frame)
{
  _common_store (frame, JFLOAT, 1);
}

void
opcode_fstore_2 (struct stack_frame *frame)
{
  _common_store (frame, JFLOAT, 2);
}

void
opcode_fstore_3 (struct stack_frame *frame)
{
  _common_store (frame, JFLOAT, 3);
}

void
opcode_fsub (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in FSUB");
      frame->error = EINVAL;
      return;
    }

  // Type checking
  if (check_var_type (&op1, JFLOAT) || check_var_type (&op2, JFLOAT))
    {
      prerr ("Type mismatch in FSUB: expected float");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = op1.value._float - op2.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in FSUB");
      frame->error = EINVAL;
      return;
    }
}

// TODO
void
opcode_getfield (struct stack_frame *)
{
}
// TODO
void
opcode_getstatic (struct stack_frame *)
{
}

static void
_common_load_2branchbytes_and_jump (struct stack_frame *frame)
{
  if (frame->pc + 2 >= frame->code_length)
    {
      prerr ("Truncated bytecode: missing two byte operand");
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }

  int16_t branchoffset = (frame->code[frame->pc + 1].raw_byte << 8)
                         | frame->code[frame->pc + 2].raw_byte;
  frame->pc += branchoffset;
  if (frame->pc >= frame->code_length)
    {
      prerr ("Illegal jump: out of range");
      frame->error = JVM_ILLEGAL_BRANCH_JUMP;
    }
}

void
opcode_goto (struct stack_frame *frame)
{
  _common_load_2branchbytes_and_jump (frame);
}
// TODO
void
opcode_goto_w (struct stack_frame *)
{
}

void
opcode_i2b (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in I2B");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in I2B: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JBYTE);
  result.value._byte = (jbyte)op1.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in I2B");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_i2c (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in I2C");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in I2C: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JCHAR);
  result.value._char = (jchar)op1.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in I2C");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_i2d (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in I2D");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in I2D: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = (jdouble)op1.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in I2D");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_i2f (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in I2F");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in I2F: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = (jfloat)op1.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in I2F");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_i2l (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in I2L");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in I2L: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = (jlong)op1.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in I2L");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_i2s (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in I2S");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in I2S: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JSHORT);
  result.value._short = (jshort)op1.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in I2S");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_iadd (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= check_var_type (&op1, JINT);
  err |= check_var_type (&op2, JINT);
  if (err != 0)
    {
      prerr ("Take incorrect data from opstack in iadd");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int + op2.value._int;
  opstack_push (frame->operand_stack, result);
}
// TODO
void
opcode_iaload (struct stack_frame *)
{
}

void
opcode_iand (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;

  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);

  err |= check_var_type (&op1, JINT);
  err |= check_var_type (&op2, JINT);

  if (err != 0)
    {
      prerr ("Invalid operand types for IAND");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int & op2.value._int;

  opstack_push (frame->operand_stack, result);
}

// TODO
void
opcode_iastore (struct stack_frame *)
{
}

void
_common_iconst (struct stack_frame *frame, jint value)
{
  int err;
  jvariable var = create_variable (JINT);
  var.value._int = value;
  err = opstack_push (frame->operand_stack, var);
  if (err)
    {
      prerr ("iconst_m1: can not run opstack_push");
      frame->error = ENOMEM;
      return;
    }
}

void
opcode_iconst_m1 (struct stack_frame *frame)
{
  _common_iconst (frame, -1);
}

void
opcode_iconst_0 (struct stack_frame *frame)
{
  _common_iconst (frame, 0);
}

void
opcode_iconst_1 (struct stack_frame *frame)
{
  _common_iconst (frame, 1);
}
void
opcode_iconst_2 (struct stack_frame *frame)
{
  _common_iconst (frame, 2);
}
void
opcode_iconst_3 (struct stack_frame *frame)
{
  _common_iconst (frame, 3);
}

void
opcode_iconst_4 (struct stack_frame *frame)
{
  _common_iconst (frame, 4);
}

void
opcode_iconst_5 (struct stack_frame *frame)
{
  _common_iconst (frame, 5);
}

void
opcode_idiv (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;

  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= check_var_type (&op1, JINT);
  err |= check_var_type (&op2, JINT);

  if (err != 0)
    {
      prerr ("Incorrect data from opstack");
      frame->error = EINVAL;
      return;
    }

  if (op2.value._int == 0)
    {
      prerr ("Division by zero");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  if (op1.value._int == INT32_MIN && op2.value._int == -1)
    {
      result.value._int = INT32_MIN;
      opstack_push (frame->operand_stack, result);
      return;
    }
  result.value._int = op1.value._int / op2.value._int;
  opstack_push (frame->operand_stack, result);
}

void
opcode_if_acmpeq (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ACMPEQ");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JOBJECT) || check_var_type (&op2, JOBJECT))
    {
      prerr ("Type mismatch in ACMPEQ: expected reference");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._object == op2.value._object)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_acmpne (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ACMPNE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JOBJECT) || check_var_type (&op2, JOBJECT))
    {
      prerr ("Type mismatch in ACMPNE: expected reference");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._object != op2.value._object)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_icmpeq (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ICMPEQ");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in ICMPEQ: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int == op2.value._int)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_icmpne (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ICMPNE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in ICMPNE: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int != op2.value._int)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_icmplt (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ICMPLT");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in ICMPLT: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int < op2.value._int)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_icmpge (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ICMPGE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in ICMPGE: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int >= op2.value._int)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_icmpgt (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ICMPGT");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in ICMPGT: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int > op2.value._int)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_if_icmple (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in ICMPLE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in ICMPLE: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int <= op2.value._int)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifeq (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFEQ");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in IFEQ: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int == 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifne (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFNE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in IFNE: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int != 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_iflt (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFLT");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in IFLT: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int < 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifge (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFGE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in IFGE: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int >= 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifgt (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFGT");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in IFGT: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int > 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifle (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFLE");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT))
    {
      prerr ("Type mismatch in IFLE: expected int");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._int <= 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifnonnull (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFNONNULL");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JOBJECT))
    {
      prerr ("Type mismatch in IFNONNULL: expected reference");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._object != 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}

void
opcode_ifnull (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IFNULL");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JOBJECT))
    {
      prerr ("Type mismatch in IFNULL: expected reference");
      frame->error = EINVAL;
      return;
    }

  if (op1.value._object == 0)
    {
      _common_load_2branchbytes_and_jump (frame);
    }
  else
    {
      frame->pc = frame->pc + 3;
    }
}
// TODO
void
opcode_iinc (struct stack_frame *)
{
}

// TODO
void
opcode_iload (struct stack_frame *)
{
}

void
opcode_iload_0 (struct stack_frame *frame)
{
  _common_load (frame, JINT, 0);
}

void
opcode_iload_1 (struct stack_frame *frame)
{
  _common_load (frame, JINT, 1);
}

void
opcode_iload_2 (struct stack_frame *frame)
{
  _common_load (frame, JINT, 2);
}

void
opcode_iload_3 (struct stack_frame *frame)
{
  _common_load (frame, JINT, 3);
}

void
opcode_imul (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in IMUL");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in IMUL: expected int");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int * op2.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in IMUL");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_ineg (struct stack_frame *frame)
{
  jvariable val;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &val);
  err |= check_var_type (&val, JINT);

  if (err)
    {
      prerr ("INEG operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  if (val.value._int == INT32_MIN)
    {
      result.value._int = INT32_MIN;
    }
  else
    {
      result.value._int = -val.value._int;
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in INEG");
      frame->error = EINVAL;
      return;
    }
}
// TODO
void
opcode_instanceof (struct stack_frame *)
{
}
// TODO
void
opcode_invokedynamic (struct stack_frame *)
{
}
// TODO
void
opcode_invokevirtual (struct stack_frame *)
{
}
// TODO
/**
 * Invoke instance method with special handling
 * Format: invokespecial
 * Operand: indexbyte1, indexbyte2 (2-byte methodref index)
 * Stack: ..., objectref, [arg1, arg2, ...] -> ...
 */
void
opcode_invokespecial (struct stack_frame *)
{
  /*
  // 1. Проверка доступности операндов
  if (frame->pc + 2 >= frame->code_length) {
      prerr("Truncated bytecode in invokespecial");
      frame->error = EINVAL;
      return;
  }

  // 2. Чтение индекса метода
  uint16_t methodref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                         | frame->code[frame->pc + 2].raw_byte;

  // 3. Получение Methodref из пула констант
  struct cp_methodref *methodref;
  if (get_methodref(frame->class->runtime_cp, methodref_idx, &methodref)) {
      prerr("Invalid methodref index %d", methodref_idx);
      frame->error = EINVAL;
      return;
  }

  // 4. Загрузка класса-владельца метода
  struct jclass *target_class;
  if (frame->jvm->classloader->load_class(frame->jvm->classloader,
                                        methodref->class_name,
                                        &target_class)) {
      prerr("Class %s not found", methodref->class_name);
      frame->error = ENOENT;
      return;
  }

  // 5. Поиск метода в классе
  struct rt_method *method;
  int is_constructor = (strcmp(methodref->method_name, "<init>") == 0);

  if (find_method_special(target_class, methodref->method_name,
                        methodref->method_descriptor,
                        frame->class, &method)) {
      prerr("Method %s.%s%s not found",
            methodref->class_name,
            methodref->method_name,
            methodref->method_descriptor);
      frame->error = ENOENT;
      return;
  }

  // 6. Проверка доступности метода
  if (!check_method_access(frame->class, target_class, method)) {
      prerr("Illegal access to method %s", methodref->method_name);
      frame->error = EACCES;
      return;
  }

  // 7. Получение objectref из стека
  jvariable objectref;
  if (opstack_peek_nth(frame->operand_stack,
                     count_arguments(methodref->method_descriptor),
                     &objectref)) {
      prerr("Stack underflow in invokespecial");
      frame->error = EINVAL;
      return;
  }

  if (objectref.type != JOBJECT || !objectref.value._object) {
      prerr("Null object reference in invokespecial");
      frame->error = EFAULT;
      return;
  }

  // 8. Создание нового фрейма
  struct stack_frame *new_frame = create_frame(target_class, method);
  if (!new_frame) {
      prerr("Failed to create frame");
      frame->error = ENOMEM;
      return;
  }

  // 9. Копирование аргументов (включая objectref)
  if (copy_arguments(frame, new_frame, methodref->method_descriptor)) {
      free_frame(new_frame);
      frame->error = EINVAL;
      return;
  }

  // 10. Специальная обработка конструктора
  if (is_constructor) {
      init_object(objectref.value._object, target_class);
      new_frame->local_vars->vars[0] = objectref;
  }

  // 11. Установка связей между фреймами
  new_frame->caller = frame;
  new_frame->jvm = frame->jvm;

  // 12. Помещение фрейма в стек вызовов
  if (call_stack_push(frame->jvm->call_stack, new_frame)) {
      free_frame(new_frame);
      frame->error = ENOMEM;
      return;
  }

  // 13. Обновление PC
  frame->pc += 2;
  */
}

void
opcode_invokestatic (struct stack_frame *frame)
{
  int err;
  if (frame->pc + 2 >= frame->code_length)
    {
      prerr ("invokestatic: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  // Reading the method index from the constant pool
  uint16_t methodref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                           | frame->code[frame->pc + 2].raw_byte;
  if (methodref_idx >= frame->class->runtime_cp_count)
    {
      prerr ("invokestatic: Illegal index to cp");
      frame->error = EINVAL;
      return;
    }

  // Get MethodRef from constant pool
  struct rt_methodref *method_ref;
  if (frame->class->runtime_cp[methodref_idx - 1].tag != METHOD_REF)
    {
      prerr ("invokeStatic: CP_Entry by index %hu is not METHOD_REF",
             methodref_idx);
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }
  method_ref = &frame->class->runtime_cp[methodref_idx - 1].methodref;

  // Load the class containing the method
  struct jclass *target_class;
  err = classloader_load_class (frame->jvm_runtime->classloader,
                                method_ref->ref.class_name, &target_class);
  if (err)
    {
      prerr ("invokeStatic: Can not load class %s",
             method_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Find the method in the target class
  struct rt_method *target_method = NULL;
  err = find_method_in_current_class (target_class, &target_method,
                                      method_ref->ref.nat.name,
                                      method_ref->ref.nat.descriptor);
  if (err)
    {
      prerr ("invokeStatic: Can not find method %s:%s in class %s",
             method_ref->ref.nat.name, method_ref->ref.nat.descriptor,
             target_class->this_class);
      frame->error = ENOENT;
      return;
    }

  // Check that the method is static
  if (!(target_method->access_flags & ACC_STATIC))
    {
      prerr ("Method %s is not static", target_method->name);
      frame->error = EACCES;
      return;
    }

  if (ensure_class_initialized (frame->jvm_runtime, target_class))
    {
      prerr ("invokestatic: failed to initialize class %s",
             target_class->this_class);
      frame->error = EINVAL;
      return;
    }

  struct stack_frame *new_frame
      = init_stack_frame (target_class, target_method, frame->jvm_runtime);
  if (new_frame == NULL)
    {
      prerr ("invokeStatic: failed to create frame");
      frame->error = ENOMEM;
      return;
    }

  // Args copy from opstack to locals
  if (copy_arguments (frame, new_frame, target_method->descriptor))
    {
      prerr ("Argument copy failed in invokestatic");
      frame->error = EINVAL;
      return;
    }

  new_frame->caller = frame;
  if (call_stack_push (frame->jvm_runtime->call_stack, new_frame))
    {
      prerr ("Call stack overflow in invokestatic");
      frame->error = ENOMEM;
      return;
    }

  frame->pc += 3;
}
// TODO
/**
 * Invoke interface method
 * Format: invokeinterface
 * Operand: indexbyte1, indexbyte2, count, 0
 * Stack: ..., objectref, [arg1, arg2, ...] -> ...
 */
void
opcode_invokeinterface (struct stack_frame *)
{
  /*
  // 1. Проверка доступности операндов
  if (frame->pc + 4 >= frame->code_length) {
      prerr("Truncated bytecode in invokeinterface");
      frame->error = EINVAL;
      return;
  }

  // 2. Чтение операндов
  uint16_t methodref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                         | frame->code[frame->pc + 2].raw_byte;
  uint8_t args_count = frame->code[frame->pc + 3].raw_byte;
  uint8_t padding = frame->code[frame->pc + 4].raw_byte;

  // 3. Проверка формата (последний байт должен быть 0)
  if (padding != 0) {
      prerr("Invalid invokeinterface padding byte: %d", padding);
      frame->error = EINVAL;
      return;
  }

  // 4. Получение Methodref из пула констант
  struct cp_interfacemethodref *imethodref;
  if (get_interfacemethodref(frame->class->runtime_cp, methodref_idx,
  &imethodref)) { prerr("Invalid interface methodref index %d",
  methodref_idx); frame->error = EINVAL; return;
  }

  // 5. Загрузка интерфейса
  struct jclass *interface_class;
  if (frame->jvm->classloader->load_class(frame->jvm->classloader,
                                        imethodref->class_name,
                                        &interface_class)) {
      prerr("Interface %s not found", imethodref->class_name);
      frame->error = ENOENT;
      return;
  }

  // 6. Получение objectref и проверка null
  jvariable objectref;
  if (opstack_peek_nth(frame->operand_stack, args_count, &objectref)) {
      prerr("Stack underflow in invokeinterface");
      frame->error = EINVAL;
      return;
  }

  if (objectref.type != JOBJECT || !objectref.value._object) {
      prerr("Null objectref in invokeinterface");
      frame->error = EFAULT;
      return;
  }

  // 7. Получение реального класса объекта
  struct jclass *target_class = objectref.value._object->class;

  // 8. Проверка реализации интерфейса
  if (!implements_interface(target_class, interface_class)) {
      prerr("Class %s does not implement interface %s",
            target_class->this_class, interface_class->this_class);
      frame->error = EINVAL;
      return;
  }

  // 9. Поиск реализации метода
  struct rt_method *method;
  if (find_interface_method(target_class, interface_class,
                          imethodref->method_name,
                          imethodref->method_descriptor,
                          &method)) {
      prerr("No implementation for %s%s found in %s",
            imethodref->method_name, imethodref->method_descriptor,
            target_class->this_class);
      frame->error = ENOENT;
      return;
  }

  // 10. Проверка доступности метода
  if (!check_interface_access(frame->class, target_class, method)) {
      prerr("Illegal access to interface method %s",
  imethodref->method_name); frame->error = EACCES; return;
  }

  // 11. Создание нового фрейма
  struct stack_frame *new_frame = create_frame(target_class, method);
  if (!new_frame) {
      prerr("Failed to create frame");
      frame->error = ENOMEM;
      return;
  }

  // 12. Копирование аргументов (objectref + args)
  if (copy_arguments(frame, new_frame, imethodref->method_descriptor)) {
      free_frame(new_frame);
      frame->error = EINVAL;
      return;
  }

  // 13. Настройка связей между фреймами
  new_frame->caller = frame;
  new_frame->jvm = frame->jvm;

  // 14. Помещение фрейма в стек вызовов
  if (call_stack_push(frame->jvm->call_stack, new_frame)) {
      free_frame(new_frame);
      frame->error = ENOMEM;
      return;
  }

  // 15. Обновление PC (4 байта операнда)
  frame->pc += 4;
  */
}

void
opcode_ior (struct stack_frame *frame)
{
  jvariable op1, op2;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);

  err |= check_var_type (&op1, JINT);
  err |= check_var_type (&op2, JINT);

  if (err)
    {
      prerr ("IOR operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int | op2.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in IOR");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_irem (struct stack_frame *frame)
{
  jvariable value1, value2;

  if (opstack_pop (frame->operand_stack, &value2)
      || opstack_pop (frame->operand_stack, &value1))
    {
      prerr ("Stack underflow in IREM");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&value1, JINT) || check_var_type (&value2, JINT))
    {
      prerr ("Type mismatch in IREM: expected int");
      frame->error = EINVAL;
      return;
    }

  if (value2.value._int == 0)
    {
      prerr ("ArithmeticException: division by zero in IREM"); // EXCEPTION
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int
      = value1.value._int
        - (value1.value._int / value2.value._int) * value2.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in IREM");
      frame->error = EINVAL;
      return;
    }
}
// TODO
void
opcode_ireturn (struct stack_frame *)
{
}
// TODO
void
opcode_ishl (struct stack_frame *)
{
}
// TODO
void
opcode_ishr (struct stack_frame *)
{
}

// TODO
void
opcode_istore (struct stack_frame *)
{
}

void
opcode_istore_0 (struct stack_frame *frame)
{
  _common_store (frame, JINT, 0);
}

void
opcode_istore_1 (struct stack_frame *frame)
{
  _common_store (frame, JINT, 1);
}

void
opcode_istore_2 (struct stack_frame *frame)
{
  _common_store (frame, JINT, 2);
}

void
opcode_istore_3 (struct stack_frame *frame)
{
  _common_store (frame, JINT, 3);
}

void
opcode_isub (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= check_var_type (&op2, JINT);
  err |= check_var_type (&op1, JINT);
  if (err != 0)
    {
      prerr ("Take incorrect data drom opstack");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int - op2.value._int;
  opstack_push (frame->operand_stack, result);
}

void
opcode_iushr (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= check_var_type (&op2, JINT);
  err |= check_var_type (&op1, JINT);
  if (err != 0)
    {
      prerr ("Take incorrect data from opstack");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JINT);
  // from spec
  jint s = (op2.value._int & 0x1F);

  if (op1.value._int > 0)
    {
      result.value._int = op1.value._int >> s;
    }
  else
    {
      result.value._int = (op1.value._int >> s) + (2 << ~s);
    }

  opstack_push (frame->operand_stack, result);
}

void
opcode_ixor (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= check_var_type (&op1, JINT);
  err |= check_var_type (&op2, JINT);
  if (err != 0)
    {
      prerr ("Take incorrect data from opstack");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JINT);
  // Bitwise exclusive OR
  result.value._int = op1.value._int ^ op2.value._int;
  opstack_push (frame->operand_stack, result);
}
// TODO
void
opcode_jsr (struct stack_frame *)
{
}
// TODO
void
opcode_jsr_w (struct stack_frame *)
{
}

void
opcode_l2d (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in L2D");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JLONG))
    {
      prerr ("Type mismatch in L2D: expected long");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = (jdouble)op1.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in L2D");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_l2f (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in L2F");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JLONG))
    {
      prerr ("Type mismatch in L2F: expected long");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = (jfloat)op1.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in L2F");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_l2i (struct stack_frame *frame)
{
  jvariable op1;

  if (opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in L2I");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JLONG))
    {
      prerr ("Type mismatch in L2I: expected long");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = (jint)op1.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in L2I");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_ladd (struct stack_frame *frame)
{
  int err = 0;
  jvariable op1, op2;
  err |= opstack_pop (frame->operand_stack, &op1);
  err |= opstack_pop (frame->operand_stack, &op2);
  err |= check_var_type (&op1, JLONG);
  err |= check_var_type (&op2, JLONG);
  if (err != 0)
    {
      prerr ("Take incorrect data from opstack in ladd");
      frame->error = EINVAL;
      return;
    }
  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long + op2.value._long;
  opstack_push (frame->operand_stack, result);
}

// TODO
void
opcode_laload (struct stack_frame *)
{
}
void
opcode_land (struct stack_frame *frame)
{
  jvariable op1, op2;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);

  err |= check_var_type (&op1, JLONG);
  err |= check_var_type (&op2, JLONG);

  if (err)
    {
      prerr ("LAND operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long & op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LAND");
      frame->error = EINVAL;
      return;
    }
}
// TODO
void
opcode_lastore (struct stack_frame *)
{
}

void
opcode_lcmp (struct stack_frame *frame)
{
  jvariable value1, value2;

  if (opstack_pop (frame->operand_stack, &value2)
      || opstack_pop (frame->operand_stack, &value1))
    {
      prerr ("Stack underflow in LCMP");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&value1, JLONG) || check_var_type (&value2, JLONG))
    {
      prerr ("Type mismatch in LCMP: expected long");
      frame->error = EINVAL;
      return;
    }

  if (value1.value._long > value2.value._long)
    {
      _common_iconst (frame, 1);
      return;
    }
  else if (value1.value._long == value2.value._long)
    {
      _common_iconst (frame, 0);
      return;
    }
  _common_iconst (frame, -1);
};

void
_common_lconst (struct stack_frame *frame, jlong value)
{
  jvariable var = create_variable (JLONG);
  var.value._long = value;
  opstack_push (frame->operand_stack, var);
}

void
opcode_lconst_0 (struct stack_frame *frame)
{
  _common_lconst (frame, 0L);
};
void
opcode_lconst_1 (struct stack_frame *frame)
{
  _common_lconst (frame, 1L);
};

// TODO
/**
 * Push constant from constant pool onto the stack
 * Format: ldc
 * Operand: index (1 byte)
 * Stack: ... -> ..., value
 */
void
opcode_ldc (struct stack_frame *)
{
  /*
  // 1. Проверка доступности операнда
  if (frame->pc + 1 >= frame->code_length) {
      prerr("Truncated bytecode in ldc");
      frame->error = EINVAL;
      return;
  }

  // 2. Чтение индекса из пула констант
  uint8_t index = frame->code[frame->pc + 1].raw_byte;

  // 3. Получение записи из пула констант
  struct cp_entry entry;
  if (get_constant_pool_entry(frame->class->runtime_cp, index, &entry)) {
      prerr("Invalid constant pool index %d in ldc", index);
      frame->error = EINVAL;
      return;
  }

  jvariable constant;
  memset(&constant, 0, sizeof(jvariable));

  // 4. Обработка в зависимости от типа записи
  switch (entry.tag) {
      case CONSTANT_Integer: {
          constant.type = JINT;
          constant.value._int = entry.info.integer;
          break;
      }

      case CONSTANT_Float: {
          constant.type = JFLOAT;
          constant.value._float = entry.info.fbytes;
          break;
      }

      case CONSTANT_String: {
          // Создание строкового объекта
          jobject str_obj = create_string_object(
              frame->jvm->heap,
              entry.info.string.bytes,
              entry.info.string.length
          );
          if (!str_obj) {
              prerr("Failed to create string object");
              frame->error = ENOMEM;
              return;
          }
          constant.type = JOBJECT;
          constant.value._object = str_obj;
          break;
      }

      case CONSTANT_Class: {
          // Получение Class объекта
          struct jclass *cls;
          if (frame->jvm->classloader->load_class(
                  frame->jvm->classloader,
                  entry.info.classref.name,
                  &cls)) {
              prerr("Class %s not found", entry.info.classref.name);
              frame->error = ENOENT;
              return;
          }
          constant.type = JOBJECT;
          constant.value._object = cls->class_object;
          break;
      }

      default: {
          prerr("Unsupported constant type %d in ldc", entry.tag);
          frame->error = EINVAL;
          return;
      }
  }

  // 5. Помещение значения в стек
  if (opstack_push(frame->operand_stack, constant)) {
      prerr("Stack overflow in ldc");
      if (constant.type == JOBJECT) {
          heap_free(frame->jvm->heap, constant.value._object);
      }
      frame->error = ENOMEM;
      return;
  }

  // 6. Обновление счетчика команд
  frame->pc += 1;
  */
}
// TODO
void
opcode_ldc_w (struct stack_frame *)
{
}
// TODO
void
opcode_ldc2_w (struct stack_frame *)
{
}

// TODO
void
opcode_ldiv (struct stack_frame *)
{
}
// TODO
void
opcode_lload (struct stack_frame *)
{
}
void
opcode_lload_0 (struct stack_frame *frame)
{
  _common_load (frame, JLONG, 0);
}

void
opcode_lload_1 (struct stack_frame *frame)
{
  _common_load (frame, JLONG, 1);
}

void
opcode_lload_2 (struct stack_frame *frame)
{
  _common_load (frame, JLONG, 2);
}

void
opcode_lload_3 (struct stack_frame *frame)
{
  _common_load (frame, JLONG, 3);
}

void
opcode_lmul (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in LMUL");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JLONG) || check_var_type (&op2, JLONG))
    {
      prerr ("Type mismatch in LMUL: expected long");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long * op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LMUL");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_lneg (struct stack_frame *frame)
{
  jvariable val;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &val);
  err |= check_var_type (&val, JLONG);

  if (err)
    {
      prerr ("LNEG operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  if (val.value._long == INT64_MIN)
    {
      result.value._long = INT64_MIN;
    }
  else
    {
      result.value._long = -val.value._long;
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LNEG");
      frame->error = EINVAL;
    }
}

// TODO
void
opcode_lookupswitch (struct stack_frame *)
{
}

void
opcode_lor (struct stack_frame *frame)
{
  jvariable op1, op2;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);

  err |= check_var_type (&op1, JLONG);
  err |= check_var_type (&op2, JLONG);

  if (err)
    {
      prerr ("LOR operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long | op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LOR");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_lrem (struct stack_frame *frame)
{
  jvariable value1, value2;

  if (opstack_pop (frame->operand_stack, &value2)
      || opstack_pop (frame->operand_stack, &value1))
    {
      prerr ("Stack underflow in LREM");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&value1, JLONG) || check_var_type (&value2, JLONG))
    {
      prerr ("Type mismatch in LREM: expected long");
      frame->error = EINVAL;
      return;
    }

  if (value2.value._long == 0)
    {
      prerr ("ArithmeticException: division by zero in LREM"); // EXCEPTION
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long
      = value1.value._long
        - (value1.value._long / value2.value._long) * value2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LREM");
      frame->error = EINVAL;
      return;
    }
}

// TODO
void
opcode_lreturn (struct stack_frame *)
{
}

void
opcode_lshl (struct stack_frame *frame)
{
  jvariable val, shift;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &shift);
  err |= opstack_pop (frame->operand_stack, &val);

  err |= check_var_type (&val, JLONG);
  err |= check_var_type (&shift, JINT);

  if (err)
    {
      prerr ("LSHL operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  uint8_t shift_count = shift.value._int & 0x3F;
  result.value._long = val.value._long << shift_count;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LSHL");
      frame->error = EINVAL;
      return;
    }
}
void
opcode_lshr (struct stack_frame *frame)
{
  jvariable val, shift;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &shift);
  err |= opstack_pop (frame->operand_stack, &val);

  err |= check_var_type (&val, JLONG);
  err |= check_var_type (&shift, JINT);

  if (err)
    {
      prerr ("LSHR operation failed");
      frame->error = EINVAL;
      return;
    }

  uint8_t shift_count = shift.value._int & 0x3F;
  jvariable result = create_variable (JLONG);

  result.value._long = val.value._long >> shift_count;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LSHR");
      frame->error = EINVAL;
    }
}

void
opcode_lstore (struct stack_frame *)
{
}

void
opcode_lstore_0 (struct stack_frame *frame)
{
  _common_store (frame, JLONG, 0);
}

void
opcode_lstore_1 (struct stack_frame *frame)
{
  _common_store (frame, JLONG, 1);
}

void
opcode_lstore_2 (struct stack_frame *frame)
{
  _common_store (frame, JLONG, 2);
}

void
opcode_lstore_3 (struct stack_frame *frame)
{
  _common_store (frame, JLONG, 3);
}

void
opcode_lsub (struct stack_frame *frame)
{
  jvariable op1, op2;

  if (opstack_pop (frame->operand_stack, &op2)
      || opstack_pop (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in JLONG");
      frame->error = EINVAL;
      return;
    }

  if (check_var_type (&op1, JLONG) || check_var_type (&op2, JLONG))
    {
      prerr ("Type mismatch in JLONG: expected float");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long - op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in JLONG");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_lushr (struct stack_frame *frame)
{
  jvariable val, shift;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &shift);
  err |= opstack_pop (frame->operand_stack, &val);

  err |= check_var_type (&val, JLONG);
  err |= check_var_type (&shift, JINT);

  if (err)
    {
      prerr ("LUSHR operation failed");
      frame->error = EINVAL;
      return;
    }

  uint8_t shift_count = shift.value._int & 0x3F;
  jvariable result = create_variable (JLONG);

  if (val.value._long >= 0)
    {
      result.value._long = (val.value._long) >> shift_count;
    }
  else
    {
      result.value._long
          = ((val.value._long) >> shift_count) + (2 << ~shift_count);
    }

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LUSHR");
      frame->error = EINVAL;
      return;
    }
}

void
opcode_lxor (struct stack_frame *frame)
{
  jvariable op1, op2;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &op2);
  err |= opstack_pop (frame->operand_stack, &op1);

  err |= check_var_type (&op1, JLONG);
  err |= check_var_type (&op2, JLONG);

  if (err)
    {
      prerr ("LXOR operation failed");
      frame->error = EINVAL;
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long ^ op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LXOR");
      frame->error = EINVAL;
      return;
    }
}
// TODO
void
opcode_monitorenter (struct stack_frame *)
{
}
// TODO
void
opcode_monitorexit (struct stack_frame *)
{
}
// TODO
void
opcode_multianewarray (struct stack_frame *)
{
}
// TODO

void
opcode_new (struct stack_frame *)
{
  /*
  // 1. Проверка наличия достаточного количества байтов
  if (frame->pc + 2 >= frame->code_length) {
      prerr("Truncated bytecode in new");
      frame->error = EINVAL;
      return;
  }

  // 2. Чтение индекса класса из пула констант
  uint16_t class_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                     | frame->code[frame->pc + 2].raw_byte;

  // 3. Получение ссылки на класс из пула констант
  struct cp_class *class_ref;
  if (get_classref(frame->class->runtime_cp, class_idx, &class_ref)) {
      prerr("Invalid class index %d in new", class_idx);
      frame->error = EINVAL;
      return;
  }

  // 4. Загрузка класса (если не загружен)
  struct jclass *target_class;
  if (frame->jvm->classloader->load_class(frame->jvm->classloader,
                                        class_ref->name,
                                        &target_class)) {
      prerr("Class %s not found", class_ref->name);
      frame->error = ENOENT;
      return;
  }

  // 5. Проверка, что класс может быть инстанцирован
  if (target_class->access_flags & (ACC_ABSTRACT | ACC_INTERFACE)) {
      prerr("Cannot instantiate abstract class/interface %s",
  class_ref->name); frame->error = EACCES; return;
  }

  // 6. Выделение памяти для объекта
  jobject obj = heap_alloc(frame->jvm->heap, target_class);
  if (!obj) {
      prerr("Failed to allocate object of type %s", class_ref->name);
      frame->error = ENOMEM;
      return;
  }

  // 7. Инициализация полей объекта
  init_object_fields(obj, target_class);

  // 8. Помещение ссылки в стек операндов
  jvariable ref;
  ref.type = JOBJECT;
  ref.value._object = obj;

  if (opstack_push(frame->operand_stack, ref)) {
      prerr("Stack overflow in new");
      heap_free(frame->jvm->heap, obj);
      frame->error = ENOMEM;
      return;
  }

  // 9. Обновление счетчика команд
  frame->pc += 2;
  */
}
// TODO
void
opcode_newarray (struct stack_frame *)
{
}

void
opcode_nop (struct stack_frame *)
{
  // do nothing
}

void
opcode_pop (struct stack_frame *frame)
{
  jvariable var;
  int err;
  err = opstack_pop (frame->operand_stack, &var);
  if (err)
    {
      prerr ("POP: can not run opstack pop");
      frame->error = ENOMEM;
      return;
    }
}

void
opcode_pop2 (struct stack_frame *frame)
{
  jvariable var1, var2;

  if (opstack_pop (frame->operand_stack, &var1))
    {
      prerr ("Stack underflow in POP2");
      frame->error = EINVAL;
      return;
    }

  if (var_computation_type (&var1) == 2)
    {
      return;
    }

  if (opstack_pop (frame->operand_stack, &var2))
    {
      prerr ("Stack underflow in POP2");
      frame->error = EINVAL;
      return;
    }

  if (var_computation_type (&var2) != 1)
    {
      prerr ("Arg 2 is not category 1 computational type in POP2");
      frame->error = EINVAL;
      return;
    }
}
// TODO
void
opcode_putfield (struct stack_frame *)
{
}
// TODO
void
opcode_putstatic (struct stack_frame *)
{
}
// TODO
void
opcode_ret (struct stack_frame *)
{
}
// TODO
void
opcode_return (struct stack_frame *)
{
}
// TODO
void
opcode_saload (struct stack_frame *)
{
}
// TODO
void
opcode_sastore (struct stack_frame *)
{
}
// TODO
void
opcode_sipush (struct stack_frame *)
{
}
// TODO
void
opcode_swap (struct stack_frame *)
{
}
// TODO
void
opcode_tableswitch (struct stack_frame *)
{
}
// TODO
void
opcode_wide (struct stack_frame *)
{
}

void
opcode_error (struct stack_frame *)
{
  PANIC ("ILLEGAL OPCODE");
}