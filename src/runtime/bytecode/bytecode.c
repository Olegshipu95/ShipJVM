#include "bytecodes.h"

void opcode_aaload (struct stack_frame *frame);

void opcode_aastore (struct stack_frame *frame);

void opcode_aconst_null (struct stack_frame *frame);

void opcode_aload (struct stack_frame *frame);

void opcode_aload_0 (struct stack_frame *frame);

void opcode_aload_1 (struct stack_frame *frame);

void opcode_aload_2 (struct stack_frame *frame);

void opcode_aload_3 (struct stack_frame *frame);

void opcode_anewarray (struct stack_frame *frame);

void opcode_areturn (struct stack_frame *frame);

void opcode_arraylength (struct stack_frame *frame);

void opcode_astore (struct stack_frame *frame);

void opcode_astore_0 (struct stack_frame *frame);

void opcode_astore_1 (struct stack_frame *frame);

void opcode_astore_2 (struct stack_frame *frame);

void opcode_astore_3 (struct stack_frame *frame);

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

void opcode_dadd (struct stack_frame *frame);

void opcode_daload (struct stack_frame *frame);

void opcode_dastore (struct stack_frame *frame);

void opcode_dcmpg (struct stack_frame *frame);

void opcode_dcmpl (struct stack_frame *frame);

void opcode_dconst_0 (struct stack_frame *frame);

void opcode_dconst_1 (struct stack_frame *frame);

void opcode_ddiv (struct stack_frame *frame);

void opcode_dload_0 (struct stack_frame *frame);

void opcode_dload_1 (struct stack_frame *frame);

void opcode_dload_2 (struct stack_frame *frame);

void opcode_dload_3 (struct stack_frame *frame);

void opcode_dmul (struct stack_frame *frame);

void opcode_dneg (struct stack_frame *frame);

void opcode_drem (struct stack_frame *frame);

void opcode_dreturn (struct stack_frame *frame);

void opcode_dstore (struct stack_frame *frame);

void opcode_dstore_1 (struct stack_frame *frame);

void opcode_dstore_2 (struct stack_frame *frame);

void opcode_dstore_3 (struct stack_frame *frame);

void opcode_dsub (struct stack_frame *frame);

void opcode_dup (struct stack_frame *frame);

void opcode_dup_x1 (struct stack_frame *frame);

void opcode_dup_x2 (struct stack_frame *frame);

void opcode_dup2 (struct stack_frame *frame);

void opcode_dup2_x1 (struct stack_frame *frame);

void opcode_dup2_x2 (struct stack_frame *frame);

void opcode_f2d (struct stack_frame *frame);

void opcode_f2i (struct stack_frame *frame);

void opcode_f2l (struct stack_frame *frame);

void opcode_fadd (struct stack_frame *frame);

void opcode_faload (struct stack_frame *frame);

void opcode_fastore (struct stack_frame *frame);

void opcode_fcmpg (struct stack_frame *frame);

void opcode_fcmpl (struct stack_frame *frame);

void opcode_fconst_0 (struct stack_frame *frame);

void opcode_fconst_1 (struct stack_frame *frame);

void opcode_fconst_2 (struct stack_frame *frame);

void opcode_fdiv (struct stack_frame *frame);

void opcode_fload (struct stack_frame *frame);

void opcode_fload_0 (struct stack_frame *frame);

void opcode_fload_1 (struct stack_frame *frame);

void opcode_fload_2 (struct stack_frame *frame);

void opcode_fload_3 (struct stack_frame *frame);

void opcode_fmul (struct stack_frame *frame);
void opcode_fneg (struct stack_frame *frame);
void opcode_frem (struct stack_frame *frame);
void opcode_freturn (struct stack_frame *frame);

void opcode_fstore (struct stack_frame *frame);
void opcode_fstore_0 (struct stack_frame *frame);
void opcode_fstore_1 (struct stack_frame *frame);
void opcode_fstore_2 (struct stack_frame *frame);
void opcode_fstore_3 (struct stack_frame *frame);

void opcode_fsub (struct stack_frame *frame);
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

void opcode_iadd (struct stack_frame *frame);
void opcode_iaload (struct stack_frame *frame);
void opcode_iand (struct stack_frame *frame);
void opcode_iastore (struct stack_frame *frame);

void
opcode_common_iconst (struct stack_frame *frame, jint value)
{
  jvariable var =  create_variable(JINT);
  var.value._int = value;
  opstack_push(frame->operand_stack, var);
}

void opcode_iconst_m1 (struct stack_frame *frame){
  opcode_common_iconst(frame, -1);
}
void opcode_iconst_0 (struct stack_frame *frame){
  opcode_common_iconst(frame, 0);
}
void opcode_iconst_1 (struct stack_frame *frame){
  opcode_common_iconst(frame, 1);
}
void opcode_iconst_2 (struct stack_frame *frame){
  opcode_common_iconst(frame, 2);
}
void opcode_iconst_3 (struct stack_frame *frame){
  opcode_common_iconst(frame, 3);
}
void opcode_iconst_4 (struct stack_frame *frame){
  opcode_common_iconst(frame, 4);
}
void opcode_iconst_5 (struct stack_frame *frame){
  opcode_common_iconst(frame, 5);
}

void opcode_idiv (struct stack_frame *frame);

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
void opcode_iload_1 (struct stack_frame *frame);
void opcode_iload_2 (struct stack_frame *frame);
void opcode_iload_3 (struct stack_frame *frame);

void opcode_imull (struct stack_frame *frame);
void opcode_ineg (struct stack_frame *frame);
void opcode_instanceof (struct stack_frame *frame);

void opcode_invokedynamic (struct stack_frame *frame);
void opcode_invokeinterface (struct stack_frame *frame);
void opcode_invokespecial (struct stack_frame *frame);
void opcode_invokestatic (struct stack_frame *frame);
void opcode_invokevirtual (struct stack_frame *frame);

void opcode_ior (struct stack_frame *frame);
void opcode_irem (struct stack_frame *frame);
void opcode_ireturn (struct stack_frame *frame);
void opcode_ishl (struct stack_frame *frame);
void opcode_ishr (struct stack_frame *frame);

void opcode_istore (struct stack_frame *frame);
void opcode_istore_0 (struct stack_frame *frame);
void opcode_istore_1 (struct stack_frame *frame);
void opcode_istore_2 (struct stack_frame *frame);
void opcode_istore_3 (struct stack_frame *frame);

void opcode_isub (struct stack_frame *frame);
void opcode_iushr (struct stack_frame *frame);
void opcode_ixor (struct stack_frame *frame);

void opcode_jsr (struct stack_frame *frame);
void opcode_jsr_w (struct stack_frame *frame);

void opcode_l2d (struct stack_frame *frame);
void opcode_l2f (struct stack_frame *frame);
void opcode_l2i (struct stack_frame *frame);

void opcode_ladd (struct stack_frame *frame);
void opcode_laload (struct stack_frame *frame);
void opcode_land (struct stack_frame *frame);
void opcode_lastore (struct stack_frame *frame);
void opcode_lcmp (struct stack_frame *frame);

void opcode_lconst_0 (struct stack_frame *frame);
void opcode_lconst_1 (struct stack_frame *frame);

void opcode_ldc (struct stack_frame *frame);
void opcode_ldc_w (struct stack_frame *frame);
void opcode_ldc2_w (struct stack_frame *frame);

void opcode_ldiv (struct stack_frame *frame);

void opcode_lload (struct stack_frame *frame);
void opcode_lload_0 (struct stack_frame *frame);
void opcode_lload_1 (struct stack_frame *frame);
void opcode_lload_2 (struct stack_frame *frame);
void opcode_lload_3 (struct stack_frame *frame);

void opcode_lmul (struct stack_frame *frame);
void opcode_lneg (struct stack_frame *frame);
void opcode_lookupswitch (struct stack_frame *frame);
void opcode_lor (struct stack_frame *frame);
void opcode_lrem (struct stack_frame *frame);
void opcode_lreturn (struct stack_frame *frame);
void opcode_lshl (struct stack_frame *frame);
void opcode_lshr (struct stack_frame *frame);

void opcode_lstore (struct stack_frame *frame);
void opcode_lstore_0 (struct stack_frame *frame);
void opcode_lstore_1 (struct stack_frame *frame);
void opcode_lstore_2 (struct stack_frame *frame);
void opcode_lstore_3 (struct stack_frame *frame);

void opcode_lsub (struct stack_frame *frame);
void opcode_lushr (struct stack_frame *frame);
void opcode_lxor (struct stack_frame *frame);
void opcode_monitorenter (struct stack_frame *frame);
void opcode_monitorexit (struct stack_frame *frame);
void opcode_multianewarray (struct stack_frame *frame);
void opcode_new (struct stack_frame *frame);
void opcode_newarray (struct stack_frame *frame);
void opcode_nop (struct stack_frame *frame);
void opcode_pop (struct stack_frame *frame);
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