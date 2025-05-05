#include "bytecodes.h"

void
_common_store (struct stack_frame *frame, java_value_type type, uint32_t index)
{
  jvariable var;

  if (opstack_pop (frame->operand_stack, &var))
    {
      prerr ("Failed to pop from stack");
      return;
    }

  if (check_var_type (&var, type))
    {
      prerr ("Type mismatch in store: expected %d", type);
      return;
    }

  store_local_var (frame->local_vars, var, index);
}

void
_common_load (struct stack_frame *frame, java_value_type type, uint32_t index)
{
  jvariable var;
  get_local_var (frame->local_vars, &var, index);

  if (var.type != type)
    {
      prerr ("Type mismatch in load: expected %d", type);
      return;
    }

  if (opstack_push (frame->operand_stack, var))
    {
      prerr ("Failed to push variable to stack");
    }
}

void opcode_aaload (struct stack_frame *frame);

void opcode_aastore (struct stack_frame *frame);

void
opcode_aconst_null (struct stack_frame *frame)
{
  jvariable result = create_variable (JOBJECT);
  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in ACONST_NULL");
    }
};

void opcode_aload (struct stack_frame *frame, uint32_t index);

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

void opcode_anewarray (struct stack_frame *frame);

void opcode_areturn (struct stack_frame *frame);

void opcode_arraylength (struct stack_frame *frame);

void
_common_astore (struct stack_frame *frame, uint32_t index)
{
  jvariable var;
  opstack_pop (frame->operand_stack, &var);

  store_local_var (frame->local_vars, var, index);
}

void opcode_astore (struct stack_frame *frame);

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

void opcode_athrow (struct stack_frame *frame);

void opcode_baload (struct stack_frame *frame);

void opcode_bastore (struct stack_frame *frame);

void opcode_bipush (struct stack_frame *frame);

void opcode_caload (struct stack_frame *frame);

void opcode_castore (struct stack_frame *frame);

void opcode_checkcast (struct stack_frame *frame);

void opcode_d2f (struct stack_frame *frame);

void opcode_d2i (struct stack_frame *frame);

void opcode_d2l (struct stack_frame *frame);

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
      return;
    }
  jvariable result = create_variable (JDOUBLE);
  result.value._double = op1.value._double + op2.value._double;
  opstack_push (frame->operand_stack, result);
}

void opcode_daload (struct stack_frame *frame);

void opcode_dastore (struct stack_frame *frame);

void opcode_dcmpg (struct stack_frame *frame);

void opcode_dcmpl (struct stack_frame *frame);

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

void opcode_ddiv (struct stack_frame *frame);

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
      return;
    }

  if (check_var_type (&op1, JDOUBLE) || check_var_type (&op2, JDOUBLE))
    {
      prerr ("Type mismatch in DMUL: expected double");
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = op1.value._double * op2.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DMUL");
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
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double = -val.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DNEG");
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
      return;
    }

  if (check_var_type (&value1, JDOUBLE) || check_var_type (&value2, JDOUBLE))
    {
      prerr ("Type mismatch in DREM: expected double");
      return;
    }

  if (value2.value._double == 0)
    {
      prerr ("ArithmeticException: division by zero in DREM"); // EXCEPTION
      return;
    }

  jvariable result = create_variable (JDOUBLE);
  result.value._double
      = value1.value._double
        - (value1.value._double / value2.value._double) * value2.value._double;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DREM");
    }
};

void opcode_dreturn (struct stack_frame *frame);

void opcode_dstore (struct stack_frame *frame);

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
      return;
    }

  // Type checking
  if (check_var_type (&op1, JDOUBLE) || check_var_type (&op2, JDOUBLE))
    {
      prerr ("Type mismatch in DSUB: expected double");
      return;
    }

  // Perform subtraction
  jvariable result = create_variable (JDOUBLE);
  result.value._double = op1.value._double - op2.value._double;

  // Push result
  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in DSUB");
    }
}

void
opcode_dup (struct stack_frame *frame)
{
  jvariable op1;
  if (opstack_peek (frame->operand_stack, &op1))
    {
      prerr ("Stack underflow in DUP");
      return;
    }

  if (opstack_push (frame->operand_stack, op1))
    {
      prerr ("Stack overflow in DUP");
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
      return;
    }

  if (var_computation_type (&op1) == 1 || var_computation_type (&op2) == 1)
    {
      prerr ("Args are not category 1 computational type in DUP_X1");
      return;
    }

  if (opstack_push (frame->operand_stack, op1)
      || opstack_push (frame->operand_stack, op2)
      || opstack_push (frame->operand_stack, op1))
    {
      prerr ("Stack overflow in DUP_X1");
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
      return;
    }

  if (var_computation_type (&op1) != 1)
    {
      prerr ("Value1 must be 1 computational type in DUP_X2");
      return;
    }

  computation_type = var_computation_type (&op2);

  if (computation_type == 1)
    {
      if (opstack_pop (frame->operand_stack, &op3))
        {
          prerr ("Stack underflow in DUP_X2");
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
            }
        }
      else
        {
          prerr ("Value3 must be 1 computational type in DUP_X2");
        }
    }
  else if (computation_type == 2)
    {
      if (opstack_push (frame->operand_stack, op1)
          || opstack_push (frame->operand_stack, op2)
          || opstack_push (frame->operand_stack, op1))
        {
          prerr ("Stack overflow in DUP_X2");
        }
    }
  else
    {
      prerr ("Value2 undefined computational type in DUP_X2");
    }
}

void opcode_dup2 (struct stack_frame *frame); // try to reuse

void opcode_dup2_x1 (struct stack_frame *frame);

void opcode_dup2_x2 (struct stack_frame *frame);

void opcode_f2d (struct stack_frame *frame);

void opcode_f2i (struct stack_frame *frame);

void opcode_f2l (struct stack_frame *frame);

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
      return;
    }
  jvariable result = create_variable (JFLOAT);
  result.value._float = op1.value._float + op2.value._float;
  opstack_push (frame->operand_stack, result);
}

void opcode_faload (struct stack_frame *frame);

void opcode_fastore (struct stack_frame *frame);

void opcode_fcmpg (struct stack_frame *frame);

void opcode_fcmpl (struct stack_frame *frame);

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

void opcode_fdiv (struct stack_frame *frame);

void opcode_fload (struct stack_frame *frame);

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
      return;
    }

  if (check_var_type (&op1, JFLOAT) || check_var_type (&op2, JFLOAT))
    {
      prerr ("Type mismatch in FMUL: expected float");
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = op1.value._float * op2.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in FMUL");
    }
}

// void opcode_fneg(struct stack_frame *frame)
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
      return;
    }

  if (check_var_type (&value1, JFLOAT) || check_var_type (&value2, JFLOAT))
    {
      prerr ("Type mismatch in FREM: expected float");
      return;
    }

  if (value2.value._int == 0)
    {
      prerr ("ArithmeticException: division by zero in FREM"); // EXCEPTION
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float
      = value1.value._float
        - (value1.value._float / value2.value._float) * value2.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in FREM");
    }
};
void opcode_freturn (struct stack_frame *frame);

void opcode_fstore (struct stack_frame *frame);

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
      return;
    }

  // Type checking
  if (check_var_type (&op1, JFLOAT) || check_var_type (&op2, JFLOAT))
    {
      prerr ("Type mismatch in FSUB: expected float");
      return;
    }

  jvariable result = create_variable (JFLOAT);
  result.value._float = op1.value._float - op2.value._float;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in FSUB");
    }
}

void opcode_getfield (struct stack_frame *frame);
void opcode_getstatic (struct stack_frame *frame);

void opcode_goto (struct stack_frame *frame);
void opcode_goto_w (struct stack_frame *frame);

void opcode_i2b (struct stack_frame *frame);
void opcode_i2c (struct stack_frame *frame);
void opcode_i2d (struct stack_frame *frame);
void opcode_i2f (struct stack_frame *frame);
void opcode_i2l (struct stack_frame *frame);
void opcode_i2s (struct stack_frame *frame);

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
      return;
    }
  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int + op2.value._int;
  opstack_push (frame->operand_stack, result);
}

void opcode_iaload (struct stack_frame *frame);

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
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int & op2.value._int;

  opstack_push (frame->operand_stack, result);
}

void opcode_iastore (struct stack_frame *frame);

void
_common_iconst (struct stack_frame *frame, jint value)
{
  jvariable var = create_variable (JINT);
  var.value._int = value;
  opstack_push (frame->operand_stack, var);
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
      return;
    }

  if (op2.value._int == 0)
    {
      prerr ("Division by zero");
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

void opcode_if_acmpeq (struct stack_frame *frame);
void opcode_if_acmpne (struct stack_frame *frame);
void opcode_if_icmpeq (struct stack_frame *frame);
void opcode_if_icmpne (struct stack_frame *frame);
void opcode_if_icmplt (struct stack_frame *frame);
void opcode_if_icmpge (struct stack_frame *frame);
void opcode_if_icmpgt (struct stack_frame *frame);
void opcode_if_icmple (struct stack_frame *frame);

void opcode_ifeq (struct stack_frame *frame);
void opcode_ifne (struct stack_frame *frame);
void opcode_iflt (struct stack_frame *frame);
void opcode_ifge (struct stack_frame *frame);
void opcode_ifgt (struct stack_frame *frame);
void opcode_ifle (struct stack_frame *frame);

void opcode_ifnonnull (struct stack_frame *frame);
void opcode_ifnull (struct stack_frame *frame);
void opcode_iinc (struct stack_frame *frame);

void opcode_iload (struct stack_frame *frame);

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
      return;
    }

  if (check_var_type (&op1, JINT) || check_var_type (&op2, JINT))
    {
      prerr ("Type mismatch in IMUL: expected int");
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int * op2.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in IMUL");
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
    }
}

void opcode_instanceof (struct stack_frame *frame);

void opcode_invokedynamic (struct stack_frame *frame);
void opcode_invokeinterface (struct stack_frame *frame);
void opcode_invokespecial (struct stack_frame *frame);
void opcode_invokestatic (struct stack_frame *frame);
void opcode_invokevirtual (struct stack_frame *frame);

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
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int = op1.value._int | op2.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in IOR");
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
      return;
    }

  if (check_var_type (&value1, JINT) || check_var_type (&value2, JINT))
    {
      prerr ("Type mismatch in IREM: expected int");
      return;
    }

  if (value2.value._int == 0)
    {
      prerr ("ArithmeticException: division by zero in IREM"); // EXCEPTION
      return;
    }

  jvariable result = create_variable (JINT);
  result.value._int
      = value1.value._int
        - (value1.value._int / value2.value._int) * value2.value._int;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in IREM");
    }
}

void opcode_ireturn (struct stack_frame *frame);
void opcode_ishl (struct stack_frame *frame);
void opcode_ishr (struct stack_frame *frame);

void opcode_istore (struct stack_frame *frame);

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
      return;
    }
  jvariable result = create_variable (JINT);
  // Bitwise exclusive OR
  result.value._int = op1.value._int ^ op2.value._int;
  opstack_push (frame->operand_stack, result);
}

void opcode_jsr (struct stack_frame *frame);

void opcode_jsr_w (struct stack_frame *frame);

void opcode_l2d (struct stack_frame *frame);
void opcode_l2f (struct stack_frame *frame);
void opcode_l2i (struct stack_frame *frame);

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
      return;
    }
  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long + op2.value._long;
  opstack_push (frame->operand_stack, result);
}

void opcode_laload (struct stack_frame *frame);
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
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long & op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LAND");
    }
}

void opcode_lastore (struct stack_frame *frame);
void opcode_lcmp (struct stack_frame *frame);

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

void opcode_ldc (struct stack_frame *frame);
void opcode_ldc_w (struct stack_frame *frame);
void opcode_ldc2_w (struct stack_frame *frame);

void opcode_ldiv (struct stack_frame *frame);

void opcode_lload (struct stack_frame *frame);
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
      return;
    }

  if (check_var_type (&op1, JLONG) || check_var_type (&op2, JLONG))
    {
      prerr ("Type mismatch in LMUL: expected long");
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long * op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LMUL");
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
    }
}

void opcode_lookupswitch (struct stack_frame *frame);

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
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long | op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LOR");
    }
}

void
opcode_lrem (struct stack_frame *frame)
{
  jvariable dividend, divisor;
  int err = 0;

  err |= opstack_pop (frame->operand_stack, &divisor);
  err |= opstack_pop (frame->operand_stack, &dividend);

  // Type checking
  err |= check_var_type (&dividend, JLONG);
  err |= check_var_type (&divisor, JLONG);

  if (err)
    {
      prerr ("LREM operation failed");
      return;
    }

  if (divisor.value._long == 0LL)
    {
      prerr ("Division by zero in LREM");
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = dividend.value._long % divisor.value._long;

  if (result.value._long != 0LL
      && ((dividend.value._long < 0LL) != (divisor.value._long < 0LL)))
    {
      result.value._long += divisor.value._long;
    }

  jvariable value1, value2;

  if (opstack_pop (frame->operand_stack, &value2)
      || opstack_pop (frame->operand_stack, &value1))
    {
      prerr ("Stack underflow in LREM");
      return;
    }

  if (check_var_type (&value1, JLONG) || check_var_type (&value2, JLONG))
    {
      prerr ("Type mismatch in LREM: expected long");
      return;
    }

  if (value2.value._long == 0)
    {
      prerr ("ArithmeticException: division by zero in LREM"); // EXCEPTION
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long
      = value1.value._long
        - (value1.value._long / value2.value._long) * value2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LREM");
    }
}

void opcode_lreturn (struct stack_frame *frame);

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
      return;
    }

  jvariable result = create_variable (JLONG);
  uint8_t shift_count = shift.value._int & 0x3F;
  result.value._long = val.value._long << shift_count;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LSHL");
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
      return;
    }

  uint8_t shift_count = shift.value._int & 0x3F;
  jvariable result = create_variable (JLONG);

  result.value._long = val.value._long >> shift_count;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LSHR");
    }
}

void opcode_lstore (struct stack_frame *frame);

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
      return;
    }

  if (check_var_type (&op1, JLONG) || check_var_type (&op2, JLONG))
    {
      prerr ("Type mismatch in JLONG: expected float");
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long - op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in JLONG");
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
      return;
    }

  jvariable result = create_variable (JLONG);
  result.value._long = op1.value._long ^ op2.value._long;

  if (opstack_push (frame->operand_stack, result))
    {
      prerr ("Stack overflow in LXOR");
    }
}

void opcode_monitorenter (struct stack_frame *frame);
void opcode_monitorexit (struct stack_frame *frame);
void opcode_multianewarray (struct stack_frame *frame);
void opcode_new (struct stack_frame *frame);
void opcode_newarray (struct stack_frame *frame);

void
opcode_nop (struct stack_frame *)
{
  // do nothing
}

void
opcode_pop (struct stack_frame *frame)
{
  jvariable var;
  opstack_pop (frame->operand_stack, &var);
}

void opcode_pop2 (struct stack_frame *frame);
void opcode_putfield (struct stack_frame *frame);
void opcode_putstatic (struct stack_frame *frame);
void opcode_ret (struct stack_frame *frame);
void opcode_return (struct stack_frame *frame);
void opcode_saload (struct stack_frame *frame);
void opcode_sastore (struct stack_frame *frame);
void opcode_sipush (struct stack_frame *frame);
void opcode_swap (struct stack_frame *frame);
void opcode_tableswitch (struct stack_frame *frame);
void opcode_wide (struct stack_frame *frame);