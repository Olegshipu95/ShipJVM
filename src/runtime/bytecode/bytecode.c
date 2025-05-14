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

//todo
void
opcode_getfield(struct stack_frame *)
{
  /*
  int err;

  // Проверка длины байткода
  if (frame->pc + 2 >= frame->code_length)
    {
      prerr("getfield: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  // Чтение индекса fieldref из bytecode
  uint16_t fieldref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                           | frame->code[frame->pc + 2].raw_byte;

  // Проверка границ индекса
  if (fieldref_idx >= frame->class->runtime_cp_count)
    {
      prerr("getfield: Illegal constant pool index");
      frame->error = EINVAL;
      return;
    }

  // Получаем FieldRef из constant pool
  struct rt_fieldref *field_ref;
  if (frame->class->runtime_cp[fieldref_idx - 1].tag != FIELD_REF)
    {
      prerr("getfield: Entry at index %hu is not a FIELD_REF", fieldref_idx);
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }

  field_ref = &frame->class->runtime_cp[fieldref_idx - 1].fieldref;

  // Загружаем класс, содержащий поле
  struct jclass *target_class;
  err = classloader_load_class(frame->jvm_runtime->classloader,
                                field_ref->ref.class_name, &target_class);
  if (err)
    {
      prerr("getfield: Failed to load class %s", field_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Ищем поле по имени и дескриптору
  struct rt_field *field = NULL;
  err = find_field_in_current_class(target_class, &field,
                                    field_ref->ref.nat.name,
                                    field_ref->ref.nat.descriptor);
  if (err)
    {
      prerr("getfield: Field %s:%s not found in class %s",
            field_ref->ref.nat.name,
            field_ref->ref.nat.descriptor,
            field_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Проверка, что поле не static
  if (field->access_flags & ACC_STATIC)
    {
      prerr("getfield: Field %s is static, expected instance field",
            field->name);
      frame->error = EACCES;
      return;
    }

  // Снимаем объект с операндного стека
  jvariable objectref;
  if (opstack_pop(frame->operand_stack, &objectref))
    {
      prerr("getfield: Operand stack underflow");
      frame->error = EINVAL;
      return;
    }

  // Проверка, что это объект
  if (objectref.type != JOBJECT || objectref.data.obj == NULL)
    {
      prerr("getfield: Expected object reference, got invalid value");
      frame->error = JVM_NULL_POINTER;
      return;
    }

  // Получение значения поля из объекта
  struct jobject *obj = objectref.data.obj;
  jvariable value;

  // Ищем поле внутри объекта
  int found = 0;
  for (int i = 0; i < obj->field_count; i++)
    {
      struct rt_field *inst_field = obj->fields[i];
      if (strcmp(inst_field->name, field->name) == 0 &&
          strcmp(inst_field->descriptor, field->descriptor) == 0)
        {
          value = inst_field->data;
          found = 1;
          break;
        }
    }

  if (!found)
    {
      prerr("getfield: Field %s not found in object instance", field->name);
      frame->error = ENOENT;
      return;
    }

  // Кладем значение поля обратно в стек
  if (opstack_push(frame->operand_stack, value))
    {
      prerr("getfield: Failed to push value onto operand stack");
      frame->error = EINVAL;
      return;
    }

  // Переход к следующей инструкции
  frame->pc += 2;
  */
}


void
opcode_getstatic(struct stack_frame *frame)
{
  int err;

  if (frame->pc + 2 >= frame->code_length)
    {
      prerr("getstatic: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  uint16_t fieldref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                          | frame->code[frame->pc + 2].raw_byte;

  if (fieldref_idx == 0 || fieldref_idx > frame->class->runtime_cp_count)
    {
      prerr("getstatic: Illegal index to cp");
      frame->error = EINVAL;
      return;
    }

  if (frame->class->runtime_cp[fieldref_idx - 1].tag != FIELD_REF)
    {
      prerr("getstatic: CP_Entry by index %hu is not FIELD_REF", fieldref_idx);
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }

  struct rt_fieldref *field_ref = &frame->class->runtime_cp[fieldref_idx - 1].fieldref;

  struct jclass *target_class;
  err = classloader_load_class(frame->jvm_runtime->classloader,
                               field_ref->ref.class_name, &target_class);
  if (err)
    {
      prerr("getstatic: Can not load class %s", field_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Ensure class initialized (call <clinit> if needed)
  err = ensure_class_initialized(frame->jvm_runtime, target_class);
  if (err)
    {
      prerr("getstatic: Failed to initialize class %s", target_class->this_class);
      frame->error = err;
      return;
    }

  struct rt_field *target_field = NULL;
  err = find_field_in_current_class(target_class, &target_field,
                                    field_ref->ref.nat.name,
                                    field_ref->ref.nat.descriptor);
  if (err)
    {
      prerr("getstatic: Can not find field %s:%s in class %s",
            field_ref->ref.nat.name, field_ref->ref.nat.descriptor,
            target_class->this_class);
      frame->error = ENOENT;
      return;
    }

  if (!(target_field->access_flags & ACC_STATIC))
    {
      prerr("Field %s is not static", target_field->name);
      frame->error = EACCES;
      return;
    }

  jvariable field_value = target_field->data;

  if (opstack_push(frame->operand_stack, field_value))
    {
      prerr("getstatic: Failed to push field value onto operand stack");
      frame->error = EINVAL;
      return;
    }

  frame->pc += 3; // 1 opcode + 2 bytes operand
}



void
opcode_goto (struct stack_frame *)
{
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
// TODO
void
opcode_if_acmpeq (struct stack_frame *)
{
}
// TODO
void
opcode_if_acmpne (struct stack_frame *)
{
}
// TODO
void
opcode_if_icmpeq (struct stack_frame *)
{
}
// TODO
void
opcode_if_icmpne (struct stack_frame *)
{
}
// TODO
void
opcode_if_icmplt (struct stack_frame *)
{
}
// TODO
void
opcode_if_icmpge (struct stack_frame *)
{
}
// TODO
void
opcode_if_icmpgt (struct stack_frame *)
{
}
// TODO
void
opcode_if_icmple (struct stack_frame *)
{
}

// TODO
void
opcode_ifeq (struct stack_frame *)
{
}
// TODO
void
opcode_ifne (struct stack_frame *)
{
}
// TODO
void
opcode_iflt (struct stack_frame *)
{
}
// TODO
void
opcode_ifge (struct stack_frame *)
{
}
// TODO
void
opcode_ifgt (struct stack_frame *)
{
}
// TODO
void
opcode_ifle (struct stack_frame *)
{
}

// TODO
void
opcode_ifnonnull (struct stack_frame *)
{
}
// TODO
void
opcode_ifnull (struct stack_frame *)
{
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
void
opcode_invokevirtual(struct stack_frame *frame)
{
  int err;

  if (frame->pc + 2 >= frame->code_length)
    {
      prerr("invokevirtual: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  // Чтение индекса methodref из constant pool
  uint16_t methodref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                         | frame->code[frame->pc + 2].raw_byte;

  if (methodref_idx == 0 || methodref_idx >= frame->class->runtime_cp_count)
    {
      prerr("invokevirtual: Invalid constant pool index");
      frame->error = EINVAL;
      return;
    }

  struct runtime_cp *entry = &frame->class->runtime_cp[methodref_idx - 1];

  if (entry->tag != METHOD_REF)
    {
      prerr("invokevirtual: Constant pool entry is not a methodref");
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }

  struct rt_methodref *method_ref = &entry->methodref;

  // Предварительно загружаем класс из methodref (но метод может быть в подклассе)
  struct jclass *decl_class;
  err = classloader_load_class(frame->jvm_runtime->classloader,
                               method_ref->ref.class_name,
                               &decl_class);
  if (err)
    {
      prerr("invokevirtual: Failed to load declared class %s",
            method_ref->ref.class_name);
      frame->error = err;
      return;
    }

  // Получаем количество аргументов, включая `this`
  int num_args = count_arguments_in_descriptor(method_ref->ref.nat.descriptor);
  if (num_args < 1)
    {
      prerr("invokevirtual: Invalid descriptor (no 'this')");
      frame->error = EINVAL;
      return;
    }

  // Получаем `this` из operand stack (не удаляя его)
  jvariable this_ref;
  if (opstack_peek_nth(frame->operand_stack, num_args - 1, &this_ref))
    {
      prerr("invokevirtual: Failed to peek 'this'");
      frame->error = EINVAL;
      return;
    }

  if (this_ref.type != JOBJECT || this_ref.value._object == NULL)
    {
      prerr("invokevirtual: 'this' is null");
      frame->error = JVM_NULL_POINTER;
      return;
    }

  struct jclass *actual_class = (struct jclass*) this_ref.value._object;
  if (!actual_class)
    {
      prerr("invokevirtual: Null class in object");
      frame->error = EINVAL;
      return;
    }

  // Убедимся, что класс инициализирован
  if ((err = ensure_class_initialized(frame->jvm_runtime, actual_class)))
    {
      prerr("invokevirtual: Failed to initialize target class");
      frame->error = err;
      return;
    }

  // Ищем переопределённый метод в иерархии
  struct rt_method *target_method = NULL;
  err = find_method_in_hierarchy(frame->jvm_runtime ,actual_class,
                                 &target_method,
                                 method_ref->ref.nat.name,
                                 method_ref->ref.nat.descriptor);
  if (err || !target_method)
    {
      prerr("invokevirtual: Method %s:%s not found in class hierarchy of %s",
            method_ref->ref.nat.name,
            method_ref->ref.nat.descriptor,
            actual_class->this_class);
      frame->error = ENOENT;
      return;
    }

  // Метод не должен быть static
  if (target_method->access_flags & ACC_STATIC)
    {
      prerr("invokevirtual: Attempt to call static method as virtual");
      frame->error = EACCES;
      return;
    }

  // Создаем стек-фрейм
  struct stack_frame *new_frame = init_stack_frame(actual_class,
                                                   target_method,
                                                   frame->jvm_runtime);
  if (!new_frame)
    {
      prerr("invokevirtual: Failed to create new frame");
      frame->error = ENOMEM;
      return;
    }

  // Копируем аргументы (включая `this`)
  err = copy_arguments(frame, new_frame,
                       method_ref->ref.nat.descriptor,
                       /* has_this = */ 1);
  if (err)
    {
      prerr("invokevirtual: Failed to copy arguments");
      frame->error = err;
      return;
    }

  new_frame->caller = frame;
  if ((err = call_stack_push(frame->jvm_runtime->call_stack, new_frame)))
    {
      prerr("invokevirtual: Call stack overflow");
      frame->error = err;
      return;
    }

  // Продвигаем PC на 2 байта
  frame->pc += 2;
}


/**
 * Invoke instance method with special handling
 * Format: invokespecial
 * Operand: indexbyte1, indexbyte2 (2-byte methodref index)
 * Stack: ..., objectref, [arg1, arg2, ...] -> ...
 */
void
opcode_invokespecial(struct stack_frame *frame)
{
  int err;

  if (frame->pc + 2 >= frame->code_length)
    {
      prerr("invokespecial: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  // Считываем индекс в constant pool
  uint16_t methodref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                          | frame->code[frame->pc + 2].raw_byte;

  if (methodref_idx == 0 || methodref_idx >= frame->class->runtime_cp_count)
    {
      prerr("invokespecial: Invalid constant pool index");
      frame->error = EINVAL;
      return;
    }

  struct runtime_cp *entry = &frame->class->runtime_cp[methodref_idx - 1];

  if (entry->tag != METHOD_REF)
    {
      prerr("invokespecial: Constant pool entry is not a methodref");
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }

  struct rt_methodref *method_ref = &entry->methodref;

  // Загружаем целевой класс
  struct jclass *target_class;
  err = classloader_load_class(frame->jvm_runtime->classloader,
                               method_ref->ref.class_name,
                               &target_class);
  if (err)
    {
      prerr("invokespecial: Failed to load class %s",
            method_ref->ref.class_name);
      frame->error = err;
      return;
    }

  // Проверка инициализации класса (на всякий случай)
  if ((err = ensure_class_initialized(frame->jvm_runtime, target_class)))
    {
      prerr("invokespecial: Class initialization failed");
      frame->error = err;
      return;
    }

  // Ищем метод
  struct rt_method *target_method = NULL;
  err = find_method_in_current_class(target_class,
                                     &target_method,
                                     method_ref->ref.nat.name,
                                     method_ref->ref.nat.descriptor);
  if (err)
    {
      prerr("invokespecial: Method %s:%s not found in class %s",
            method_ref->ref.nat.name,
            method_ref->ref.nat.descriptor,
            method_ref->ref.class_name);
      frame->error = err;
      return;
    }

  // Проверка: метод не должен быть static
  if ((target_method->access_flags & ACC_STATIC) != 0)
    {
      prerr("invokespecial: Attempt to call static method as special");
      frame->error = EACCES;
      return;
    }

  // Создаем стек-фрейм
  struct stack_frame *new_frame = init_stack_frame(target_class,
                                                   target_method,
                                                   frame->jvm_runtime);
  if (!new_frame)
    {
      prerr("invokespecial: Failed to create new frame");
      frame->error = ENOMEM;
      return;
    }

  // Копируем аргументы (включая `this`)
  err = copy_arguments(frame, new_frame,
                       method_ref->ref.nat.descriptor,
                       /* has_this = */ 1);
  if (err)
    {
      prerr("invokespecial: Failed to copy arguments");
      frame->error = err;
      return;
    }

  // Устанавливаем caller и помещаем фрейм на стек
  new_frame->caller = frame;
  err = call_stack_push(frame->jvm_runtime->call_stack, new_frame);
  if (err)
    {
      prerr("invokespecial: Call stack overflow");
      frame->error = err;
      return;
    }

  // Смещаем PC на 2 байта (индекс в constant pool)
  frame->pc += 2;
}


void
opcode_invokestatic(struct stack_frame *frame)
{
  int err;

  // Проверка на достаточную длину байткода (1 байт op + 2 байта index)
  if (frame->pc + 2 >= frame->code_length)
    {
      prerr("invokestatic: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  // Чтение индекса methodref (big-endian)
  uint16_t methodref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                           | frame->code[frame->pc + 2].raw_byte;

  // Проверка диапазона индекса
  if (methodref_idx == 0 || methodref_idx > frame->class->runtime_cp_count)
    {
      prerr("invokestatic: Illegal constant pool index %u", methodref_idx);
      frame->error = EINVAL;
      return;
    }

  // Получение метода из constant pool
  struct runtime_cp *cp_entry = &frame->class->runtime_cp[methodref_idx - 1];
  if (cp_entry->tag != METHOD_REF)
    {
      prerr("invokestatic: CP entry at index %u is not a MethodRef", methodref_idx);
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }

  struct rt_methodref *method_ref = &cp_entry->methodref;

  // Загрузка класса, в котором находится вызываемый метод
  struct jclass *target_class = NULL;
  err = classloader_load_class(frame->jvm_runtime->classloader,
                               method_ref->ref.class_name,
                               &target_class);
  if (err)
    {
      prerr("invokestatic: Cannot load class %s", method_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Инициализация класса, если необходимо
  if (ensure_class_initialized(frame->jvm_runtime, target_class))
    {
      prerr("invokestatic: Failed to initialize class %s", target_class->this_class);
      frame->error = EINVAL;
      return;
    }

  // Поиск метода
  struct rt_method *target_method = NULL;
  err = find_method_in_current_class(target_class, &target_method,
                                     method_ref->ref.nat.name,
                                     method_ref->ref.nat.descriptor);
  if (err)
    {
      prerr("invokestatic: Method %s:%s not found in class %s",
            method_ref->ref.nat.name, method_ref->ref.nat.descriptor,
            target_class->this_class);
      frame->error = ENOENT;
      return;
    }

  // Проверка флага ACC_STATIC
  if (!(target_method->access_flags & ACC_STATIC))
    {
      prerr("invokestatic: Method %s is not static", target_method->name);
      frame->error = EACCES;
      return;
    }

  // Создание нового стека фрейма
  struct stack_frame *new_frame = init_stack_frame(target_class, target_method, frame->jvm_runtime);
  if (!new_frame)
    {
      prerr("invokestatic: Failed to create new frame");
      frame->error = ENOMEM;
      return;
    }

  // Копирование аргументов из текущего стека операндов в локальные переменные нового фрейма
  if (copy_arguments(frame, new_frame, target_method->descriptor, 0))
    {
      prerr("invokestatic: Argument copy failed");
      frame->error = EINVAL;
      return;
    }

  // Установка caller
  new_frame->caller = frame;

  // Помещаем фрейм в стек вызовов
  if (call_stack_push(frame->jvm_runtime->call_stack, new_frame))
    {
      prerr("invokestatic: Call stack overflow");
      frame->error = ENOMEM;
      return;
    }

  // Продвигаем PC (1 байт опкод + 2 байта индекса)
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
  &imethodref)) { prerr("Invalid interface methodref index %d", methodref_idx);
      frame->error = EINVAL;
      return;
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
      prerr("Illegal access to interface method %s", imethodref->method_name);
      frame->error = EACCES;
      return;
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
void
opcode_ireturn(struct stack_frame *frame)
{
  jvariable ret_val;

  // 1. Снять значение со стека операндов текущего фрейма
  if (opstack_pop(frame->operand_stack, &ret_val)) {
    prerr("ireturn: Stack underflow");
    frame->error = EINVAL;
    return;
  }

  // 2. Проверка типа
  if (ret_val.type != JINT) {
    prerr("ireturn: Invalid return type (expected JINT)");
    frame->error = EINVAL;
    return;
  }

  // 3. Снять текущий фрейм с call stack
  if (call_stack_pop(frame->jvm_runtime->call_stack) == NULL ) {
    prerr("ireturn: Failed to pop current frame");
    frame->error = EINVAL;
    return;
  }

  // 4. Передать значение вызывающему фрейму
  struct stack_frame *caller = call_stack_peek(frame->jvm_runtime->call_stack);
  if (!caller) {
    prerr("ireturn: No caller frame to return to");
    frame->error = EINVAL;
    return;
  }

  // 5. Поместить значение на стек операндов вызывающего метода
  if (opstack_push(caller->operand_stack, ret_val)) {
    prerr("ireturn: Failed to push return value to caller's operand stack");
    caller->error = ENOMEM;
    return;
  }
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
      prerr("Cannot instantiate abstract class/interface %s", class_ref->name);
      frame->error = EACCES;
      return;
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

void
opcode_putstatic(struct stack_frame *frame)
{
  int err;

  // Проверка длины bytecode
  if (frame->pc + 2 >= frame->code_length)
    {
      prerr("putstatic: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  // Чтение индекса поля (2 байта)
  uint16_t fieldref_idx = (frame->code[frame->pc + 1].raw_byte << 8)
                         | frame->code[frame->pc + 2].raw_byte;

  // Проверка границ
  if (fieldref_idx >= frame->class->runtime_cp_count)
    {
      prerr("putstatic: Illegal CP index");
      frame->error = EINVAL;
      return;
    }

  // Получение fieldref
  struct rt_fieldref *field_ref;
  if (frame->class->runtime_cp[fieldref_idx - 1].tag != FIELD_REF)
    {
      prerr("putstatic: Constant pool entry %hu is not a FIELD_REF", fieldref_idx);
      frame->error = JVM_INVALID_BYTECODE;
      return;
    }
  field_ref = &frame->class->runtime_cp[fieldref_idx - 1].fieldref;

  // Загрузка целевого класса
  struct jclass *target_class;
  err = classloader_load_class(frame->jvm_runtime->classloader,
                               field_ref->ref.class_name, &target_class);
  if (err)
    {
      prerr("putstatic: Failed to load class %s", field_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Поиск статического поля
  struct rt_field *target_field = NULL;
  err = find_field_in_current_class(target_class, &target_field,
                                    field_ref->ref.nat.name,
                                    field_ref->ref.nat.descriptor);
  if (err)
    {
      prerr("putstatic: Field %s:%s not found in class %s",
            field_ref->ref.nat.name,
            field_ref->ref.nat.descriptor,
            field_ref->ref.class_name);
      frame->error = ENOENT;
      return;
    }

  // Проверка, что поле действительно static
  if (!(target_field->access_flags & ACC_STATIC))
    {
      prerr("putstatic: Field %s is not static", target_field->name);
      frame->error = EACCES;
      return;
    }

  // Снятие значения с операндного стека
  jvariable value;
  if (opstack_pop(frame->operand_stack, &value))
    {
      prerr("putstatic: Stack underflow");
      frame->error = EINVAL;
      return;
    }

  // Запись значения в поле
  target_field->data = value;

  // Переход к следующей инструкции
  frame->pc += 2;
}


void
opcode_ret(struct stack_frame *frame)
{
  if (frame->pc + 1 >= frame->code_length)
    {
      prerr("ret: Truncated bytecode");
      frame->error = EINVAL;
      return;
    }

  uint8_t index = frame->code[frame->pc + 1].raw_byte;

  jvariable ret_addr;
  if (get_local_var(frame->local_vars, &ret_addr, index))
    {
      prerr("ret: Failed to load return address from local variable index %u", index);
      frame->error = EINVAL;
      return;
    }

  if (ret_addr.type != JINT)
    {
      prerr("ret: Invalid type for return address (expected JINT), got %d", ret_addr.type);
      frame->error = EINVAL;
      return;
    }

  frame->pc = (uint32_t)ret_addr.value._int;
}


void
opcode_return (struct stack_frame *frame)
{
  if (call_stack_pop(frame->jvm_runtime->call_stack) == NULL) {
    prerr("opcode_return: Failed to pop call stack");
    frame->error = EINVAL;
    return;
  }
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