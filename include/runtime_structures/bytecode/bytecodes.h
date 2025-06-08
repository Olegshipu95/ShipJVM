#ifndef SHIP_JVM_BYTECODES_H
#define SHIP_JVM_BYTECODES_H
#include "stdint.h"

struct classloader;
struct stack_frame;



/**
 * Operation: Load reference from array
 * Operand stack: arrayref, index → value
 */
void opcode_aaload (struct stack_frame *frame); // 50 (0x32)

/**
 * Operation: Store into reference array
 * Operand stack: arrayref, index, value →
 */
void opcode_aastore (struct stack_frame *frame); // 83 (0x53)

/**
 * Operation: Push null reference
 * Operand stack: → null
 */
void opcode_aconst_null (struct stack_frame *frame); // 1 (0x01)

// aload section

/**
 * Operation: Load reference from local variable
 * Operand stack: → objectref
 */
void opcode_aload (struct stack_frame *frame); // 25 (0x19)

/**
 * Operation: Load reference from local variable 0
 * Operand stack: → objectref
 */
void opcode_aload_0 (struct stack_frame *frame); // 42 (0x2a)

/**
 * Operation: Load reference from local variable 1
 * Operand stack: → objectref
 */
void opcode_aload_1 (struct stack_frame *frame); // 43 (0x2b)

/**
 * Operation: Load reference from local variable 2
 * Operand stack: → objectref
 */
void opcode_aload_2 (struct stack_frame *frame); // 44 (0x2c)

/**
 * Operation: Load reference from local variable 3
 * Operand stack: → objectref
 */
void opcode_aload_3 (struct stack_frame *frame); // 45 (0x2d)

/**
 * Operation: Create new array of references
 * Operand stack: count → arrayref
 */
void opcode_anewarray (struct stack_frame *frame); // 189 (0xbd)

/**
 * Operation: Return reference from method
 * Operand stack: objectref → [empty]
 */
void opcode_areturn (struct stack_frame *frame); // 176 (0xb0)

/**
 * Operation: Get length of array
 * Operand stack: arrayref → length
 */
void opcode_arraylength (struct stack_frame *frame); // 190 (0xbe)

// astore

/**
 * Operation: Store reference into local variable
 * Operand stack: objectref →
 */
void opcode_astore (struct stack_frame *frame); // 58 (0x3a)

/**
 * Operation: Store reference into local variable 0
 * Operand stack: objectref →
 */
void opcode_astore_0 (struct stack_frame *frame); // 75 (0x4b)

/**
 * Operation: Store reference into local variable 1
 * Operand stack: objectref →
 */
void opcode_astore_1 (struct stack_frame *frame); // 76 (0x4c)

/**
 * Operation: Store reference into local variable 2
 * Operand stack: objectref →
 */
void opcode_astore_2 (struct stack_frame *frame); // 77 (0x4d)

/**
 * Operation: Store reference into local variable 3
 * Operand stack: objectref →
 */
void opcode_astore_3 (struct stack_frame *frame); // 78 (0x4e)

/**
 * Operation: Throw exception or error
 * Operand stack: objectref → [empty], objectref
 */
void opcode_athrow (struct stack_frame *frame); // 191 (0xbf)

/**
 * Operation: Load byte or boolean from array
 * Operand stack: arrayref, index → value
 */
void opcode_baload (struct stack_frame *frame); // 51 (0x33)

/**
 * Operation: Store into byte or boolean array
 * Operand stack: arrayref, index, value →
 */
void opcode_bastore (struct stack_frame *frame); // 84 (0x54)

/**
 * Operation: Push byte as integer
 * Operand stack: → value
 */
void opcode_bipush (struct stack_frame *frame); // 16 (0x10)

/**
 * Operation: Load char from array
 * Operand stack: arrayref, index → value
 */
void opcode_caload (struct stack_frame *frame); // 52 (0x34)

/**
 * Operation: Store into char array
 * Operand stack: arrayref, index, value →
 */
void opcode_castore (struct stack_frame *frame); // 85 (0x55)

/**
 * Operation: Check whether object is of given type
 * Operand stack: objectref → objectref
 */
void opcode_checkcast (struct stack_frame *frame); // 192 (0xc0)

/**
 * Operation: Convert double to float
 * Operand stack: value → result
 */
void opcode_d2f (struct stack_frame *frame); // 144 (0x90)

/**
 * Operation: Convert double to int
 * Operand stack: value → result
 */
void opcode_d2i (struct stack_frame *frame); // 142 (0x8e)

/**
 * Operation: Convert double to long
 * Operand stack: value → result
 */
void opcode_d2l (struct stack_frame *frame); // 143 (0x8f)

/**
 * Operation: Add two double values
 * Operand stack: value1, value2 → result
 */
void opcode_dadd (struct stack_frame *frame); // 99 (0x63)

/**
 * Operation: Load double from array
 * Operand stack: arrayref, index → value
 */
void opcode_daload (struct stack_frame *frame); // 49 (0x31)

/**
 * Operation: Store into double array
 * Operand stack: arrayref, index, value →
 */
void opcode_dastore (struct stack_frame *frame); // 82 (0x52)

/**
 * Operation: Compare double (returns 1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_dcmpg (struct stack_frame *frame); // 152 (0x98)

/**
 * Operation: Compare double (returns -1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_dcmpl (struct stack_frame *frame); // 151 (0x97)

// dconst section

/**
 * Operation: Push double constant 0.0
 * Operand stack: → 0.0
 */
void opcode_dconst_0 (struct stack_frame *frame); // 14 (0x0e)

/**
 * Operation: Push double constant 1.0
 * Operand stack: → 1.0
 */
void opcode_dconst_1 (struct stack_frame *frame); // 15 (0x0f)

/**
 * Operation: Divide two double values
 * Operand stack: value1, value2 → result
 */
void opcode_ddiv (struct stack_frame *frame); // 111 (0x6f)

// dload

void opcode_dload (struct stack_frame *frame);

/**
 * Operation: Load double from local variable 0
 * Operand stack: → value
 */
void opcode_dload_0 (struct stack_frame *frame); // 38 (0x26)

/**
 * Operation: Load double from local variable 1
 * Operand stack: → value
 */
void opcode_dload_1 (struct stack_frame *frame); // 39 (0x27)

/**
 * Operation: Load double from local variable 2
 * Operand stack: → value
 */
void opcode_dload_2 (struct stack_frame *frame); // 40 (0x28)

/**
 * Operation: Load double from local variable 3
 * Operand stack: → value
 */
void opcode_dload_3 (struct stack_frame *frame); // 41 (0x29)

/**
 * Operation: Multiply two double values
 * Operand stack: value1, value2 → result
 */
void opcode_dmul (struct stack_frame *frame); // 107 (0x6b)

/**
 * Operation: Negate double value
 * Operand stack: value → result
 */
void opcode_dneg (struct stack_frame *frame); // 119 (0x77)

/**
 * Operation: Get remainder from division of two doubles
 * Operand stack: value1, value2 → result
 */
void opcode_drem (struct stack_frame *frame); // 115 (0x73)

/**
 * Operation: Return double from method
 * Operand stack: value → [empty]
 */
void opcode_dreturn (struct stack_frame *frame); // 175 (0xaf)

// dstore section

/**
 * Operation: Store double into local variable (index)
 * Operand stack: value →
 */
void opcode_dstore (struct stack_frame *frame); // 57 (0x39)

void opcode_dstore_0 (struct stack_frame *frame);

/**
 * Operation: Store double into local variable 1
 * Operand stack: value →
 */
void opcode_dstore_1 (struct stack_frame *frame); // 72 (0x48)

/**
 * Operation: Store double into local variable 2
 * Operand stack: value →
 */
void opcode_dstore_2 (struct stack_frame *frame); // 73 (0x49)

/**
 * Operation: Store double into local variable 3
 * Operand stack: value →
 */
void opcode_dstore_3 (struct stack_frame *frame); // 74 (0x4a)

/**
 * Operation: Subtract two double values
 * Operand stack: value1, value2 → result
 */
void opcode_dsub (struct stack_frame *frame); // 103 (0x67)

// dup section

/**
 * Operation: Duplicate top stack value
 * Operand stack: value → value, value
 */
void opcode_dup (struct stack_frame *frame); // 89 (0x59)

/**
 * Operation: Duplicate top stack value and insert two values down
 * Operand stack: value2, value1 → value1, value2, value1
 */
void opcode_dup_x1 (struct stack_frame *frame); // 90 (0x5a)

/**
 * Operation: Duplicate top stack value and insert three values down
 * Operand stack: value3, value2, value1 → value1, value3, value2, value1
 */
void opcode_dup_x2 (struct stack_frame *frame); // 91 (0x5b)

/**
 * Operation: Duplicate top two stack values
 * Operand stack: value2, value1 → value2, value1, value2, value1
 */
void opcode_dup2 (struct stack_frame *frame); // 92 (0x5c)

/**
 * Operation: Duplicate top two values and insert three values down
 * Operand stack: value3, value2, value1 → value2, value1, value3, value2,
 * value1
 */
void opcode_dup2_x1 (struct stack_frame *frame); // 93 (0x5d)

/**
 * Operation: Duplicate top two values and insert four values down
 * Operand stack: value4, value3, value2, value1 → value2, value1, value4,
 * value3, value2, value1
 */
void opcode_dup2_x2 (struct stack_frame *frame); // 94 (0x5e)

// float to section

/**
 * Operation: Convert float to double
 * Operand stack: value → result
 */
void opcode_f2d (struct stack_frame *frame); // 141 (0x8d)

/**
 * Operation: Convert float to int
 * Operand stack: value → result
 */
void opcode_f2i (struct stack_frame *frame); // 139 (0x8b)

/**
 * Operation: Convert float to long
 * Operand stack: value → result
 */
void opcode_f2l (struct stack_frame *frame); // 140 (0x8c)

// float operations

/**
 * Operation: Add two float values
 * Operand stack: value1, value2 → result
 */
void opcode_fadd (struct stack_frame *frame); // 98 (0x62)

/**
 * Operation: Load float from array
 * Operand stack: arrayref, index → value
 */
void opcode_faload (struct stack_frame *frame); // 48 (0x30)

/**
 * Operation: Store into float array
 * Operand stack: arrayref, index, value →
 */
void opcode_fastore (struct stack_frame *frame); // 81 (0x51)

/**
 * Operation: Compare float (returns 1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_fcmpg (struct stack_frame *frame); // 150 (0x96)

/**
 * Operation: Compare float (returns -1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_fcmpl (struct stack_frame *frame); // 149 (0x95)

// float const section

/**
 * Operation: Push float constant 0.0f
 * Operand stack: → 0.0f
 */
void opcode_fconst_0 (struct stack_frame *frame); // 11 (0x0b)

/**
 * Operation: Push float constant 1.0f
 * Operand stack: → 1.0f
 */
void opcode_fconst_1 (struct stack_frame *frame); // 12 (0x0c)

/**
 * Operation: Push float constant 2.0f
 * Operand stack: → 2.0f
 */
void opcode_fconst_2 (struct stack_frame *frame); // 13 (0x0d)

/**
 * Operation: Divide two float values
 * Operand stack: value1, value2 → result
 */
void opcode_fdiv (struct stack_frame *frame); // 110 (0x6e)

// float load section

/**
 * Operation: Load float from local variable (index)
 * Operand stack: → value
 */
void opcode_fload (struct stack_frame *frame); // 23 (0x17)

/**
 * Operation: Load float from local variable 0
 * Operand stack: → value
 */
void opcode_fload_0 (struct stack_frame *frame); // 34 (0x22)

/**
 * Operation: Load float from local variable 1
 * Operand stack: → value
 */
void opcode_fload_1 (struct stack_frame *frame); // 35 (0x23)

/**
 * Operation: Load float from local variable 2
 * Operand stack: → value
 */
void opcode_fload_2 (struct stack_frame *frame); // 36 (0x24)

/**
 * Operation: Load float from local variable 3
 * Operand stack: → value
 */
void opcode_fload_3 (struct stack_frame *frame); // 37 (0x25)

/**
 * Operation: Multiply two float values
 * Operand stack: value1, value2 → result
 */
void opcode_fmul (struct stack_frame *frame); // 106 (0x6a)

/**
 * Operation: Negate float value
 * Operand stack: value → result
 */
void opcode_fneg (struct stack_frame *frame); // 118 (0x76)

/**
 * Operation: Get remainder from division of two floats
 * Operand stack: value1, value2 → result
 */
void opcode_frem (struct stack_frame *frame); // 114 (0x72)

/**
 * Operation: Return float from method
 * Operand stack: value → [empty]
 */
void opcode_freturn (struct stack_frame *frame); // 174 (0xae)

// FSTORE SECTION

/**
 * Operation: Store float into local variable (index)
 * Operand stack: value →
 */
void opcode_fstore (struct stack_frame *frame); // 56 (0x38)

/**
 * Operation: Store float into local variable 0
 * Operand stack: value →
 */
void opcode_fstore_0 (struct stack_frame *frame); // 67 (0x43)

/**
 * Operation: Store float into local variable 1
 * Operand stack: value →
 */
void opcode_fstore_1 (struct stack_frame *frame); // 68 (0x44)

/**
 * Operation: Store float into local variable 2
 * Operand stack: value →
 */
void opcode_fstore_2 (struct stack_frame *frame); // 69 (0x45)

/**
 * Operation: Store float into local variable 3
 * Operand stack: value →
 */
void opcode_fstore_3 (struct stack_frame *frame); // 70 (0x46)

/**
 * Operation: Subtract two float values
 * Operand stack: value1, value2 → result
 */
void opcode_fsub (struct stack_frame *frame); // 102 (0x66)

/**
 * Operation: Fetch field from object
 * Operand stack: objectref → value
 */
void opcode_getfield (struct stack_frame *frame); // 180 (0xb4)

/**
 * Operation: Get static field from class
 * Operand stack: → value
 */
void opcode_getstatic (struct stack_frame *frame); // 178 (0xb2)

// GOTO SECTION

/**
 * Operation: Branch always (short)
 * Operand stack: No change
 */
void opcode_goto (struct stack_frame *frame); // 167 (0xa7)

/**
 * Operation: Branch always (wide)
 * Operand stack: No change
 */
void opcode_goto_w (struct stack_frame *frame); // 200 (0xc8)

// INTEGER TO SECTION

/**
 * Operation: Convert int to byte
 * Operand stack: value → result
 */
void opcode_i2b (struct stack_frame *frame); // 145 (0x91)

/**
 * Operation: Convert int to char
 * Operand stack: value → result
 */
void opcode_i2c (struct stack_frame *frame); // 146 (0x92)

/**
 * Operation: Convert int to double
 * Operand stack: value → result
 */
void opcode_i2d (struct stack_frame *frame); // 135 (0x87)

/**
 * Operation: Convert int to float
 * Operand stack: value → result
 */
void opcode_i2f (struct stack_frame *frame); // 134 (0x86)

/**
 * Operation: Convert int to long
 * Operand stack: value → result
 */
void opcode_i2l (struct stack_frame *frame); // 133 (0x85)

/**
 * Operation: Convert int to short
 * Operand stack: value → result
 */
void opcode_i2s (struct stack_frame *frame); // 147 (0x93)

// INTEGER OPERATIONS

/**
 * Operation: Add two int values
 * Operand stack: value1, value2 → result
 */
void opcode_iadd (struct stack_frame *frame); // 96 (0x60)

/**
 * Operation: Load int from array
 * Operand stack: arrayref, index → value
 */
void opcode_iaload (struct stack_frame *frame); // 46 (0x2e)

/**
 * Operation: Bitwise AND of two ints
 * Operand stack: value1, value2 → result
 */
void opcode_iand (struct stack_frame *frame); // 126 (0x7e)

/**
 * Operation: Store into int array
 * Operand stack: arrayref, index, value →
 */
void opcode_iastore (struct stack_frame *frame); // 79 (0x4f)

// INTEGER CONST SECTION

/**
 * Operation: Push int constant -1
 * Operand stack: → -1
 */
void opcode_iconst_m1 (struct stack_frame *frame); // 2 (0x02)

/**
 * Operation: Push int constant 0
 * Operand stack: → 0
 */
void opcode_iconst_0 (struct stack_frame *frame); // 3 (0x03)

/**
 * Operation: Push int constant 1
 * Operand stack: → 1
 */
void opcode_iconst_1 (struct stack_frame *frame); // 4 (0x04)

/**
 * Operation: Push int constant 2
 * Operand stack: → 2
 */
void opcode_iconst_2 (struct stack_frame *frame); // 5 (0x05)

/**
 * Operation: Push int constant 3
 * Operand stack: → 3
 */
void opcode_iconst_3 (struct stack_frame *frame); // 6 (0x06)

/**
 * Operation: Push int constant 4
 * Operand stack: → 4
 */
void opcode_iconst_4 (struct stack_frame *frame); // 7 (0x07)

/**
 * Operation: Push int constant 5
 * Operand stack: → 5
 */
void opcode_iconst_5 (struct stack_frame *frame); // 8 (0x08)

/**
 * Operation: Divide two int values
 * Operand stack: value1, value2 → result
 */
void opcode_idiv (struct stack_frame *frame);

// INTEGER COMPARE SECTION

/**
 * Operation: Branch if object references are equal
 * Operand stack: value1, value2 →
 */
void opcode_if_acmpeq (struct stack_frame *frame); // 165 (0xa5)

/**
 * Operation: Branch if object references are not equal
 * Operand stack: value1, value2 →
 */
void opcode_if_acmpne (struct stack_frame *frame); // 166 (0xa6)

/**
 * Operation: Branch if ints are equal
 * Operand stack: value1, value2 →
 */
void opcode_if_icmpeq (struct stack_frame *frame); // 159 (0x9f)

/**
 * Operation: Branch if ints are not equal
 * Operand stack: value1, value2 →
 */
void opcode_if_icmpne (struct stack_frame *frame); // 160 (0xa0)

/**
 * Operation: Branch if int1 < int2
 * Operand stack: value1, value2 →
 */
void opcode_if_icmplt (struct stack_frame *frame); // 161 (0xa1)

/**
 * Operation: Branch if int1 >= int2
 * Operand stack: value1, value2 →
 */
void opcode_if_icmpge (struct stack_frame *frame); // 162 (0xa2)

/**
 * Operation: Branch if int1 > int2
 * Operand stack: value1, value2 →
 */
void opcode_if_icmpgt (struct stack_frame *frame); // 163 (0xa3)

/**
 * Operation: Branch if int1 <= int2
 * Operand stack: value1, value2 →
 */
void opcode_if_icmple (struct stack_frame *frame); // 164 (0xa4)

// IF SECTION

/**
 * Operation: Branch if int equals zero
 * Operand stack: value →
 */
void opcode_ifeq (struct stack_frame *frame); // 153 (0x99)

/**
 * Operation: Branch if int not zero
 * Operand stack: value →
 */
void opcode_ifne (struct stack_frame *frame); // 154 (0x9a)

/**
 * Operation: Branch if int less than zero
 * Operand stack: value →
 */
void opcode_iflt (struct stack_frame *frame); // 155 (0x9b)

/**
 * Operation: Branch if int greater than or equal to zero
 * Operand stack: value →
 */
void opcode_ifge (struct stack_frame *frame); // 156 (0x9c)

/**
 * Operation: Branch if int greater than zero
 * Operand stack: value →
 */
void opcode_ifgt (struct stack_frame *frame); // 157 (0x9d)

/**
 * Operation: Branch if int less than or equal to zero
 * Operand stack: value →
 */
void opcode_ifle (struct stack_frame *frame); // 158 (0x9e)

/**
 * Operation: Branch if reference not null
 * Operand stack: value →
 */
void opcode_ifnonnull (struct stack_frame *frame); // 199 (0xc7)

/**
 * Operation: Branch if reference is null
 * Operand stack: value →
 */
void opcode_ifnull (struct stack_frame *frame); // 198 (0xc6)

/**
 * Operation: Increment local variable by constant
 * Operand stack: No change
 */
void opcode_iinc (struct stack_frame *frame); // 132 (0x84)

// Integer load section

/**
 * Operation: Load int from local variable (index)
 * Operand stack: → value
 */
void opcode_iload (struct stack_frame *frame); // 21 (0x15)

void opcode_iload_0 (struct stack_frame *frame);

/**
 * Operation: Load int from local variable 1
 * Operand stack: → value
 */
void opcode_iload_1 (struct stack_frame *frame); // 27 (0x1b)

/**
 * Operation: Load int from local variable 2
 * Operand stack: → value
 */
void opcode_iload_2 (struct stack_frame *frame); // 28 (0x1c)

/**
 * Operation: Load int from local variable 3
 * Operand stack: → value
 */
void opcode_iload_3 (struct stack_frame *frame); // 29 (0x1d)

/**
 * Operation: Multiply two int values
 * Operand stack: value1, value2 → result
 */
void opcode_imul (struct stack_frame *frame); // 104 (0x68)

/**
 * Operation: Negate int value
 * Operand stack: value → result
 */
void opcode_ineg (struct stack_frame *frame); // 116 (0x74)

/**
 * Operation: Check if object is of given type
 * Operand stack: objectref → result
 */
void opcode_instanceof (struct stack_frame *frame); // 193 (0xc1)

// INVOKE SECTION

/**
 * Operation: Invoke dynamic method
 * Operand stack: [arg1, arg2, ...] → result
 */
void opcode_invokedynamic (struct stack_frame *frame); // 186 (0xba)

/**
 * Operation: Invoke interface method
 * Operand stack: objectref, [arg1, arg2, ...] → result
 */
void opcode_invokeinterface (struct stack_frame *frame); // 185 (0xb9)

/**
 * Operation: Invoke instance method (special handling)
 * Operand stack: objectref, [arg1, arg2, ...] → result
 */
void opcode_invokespecial (struct stack_frame *frame); // 183 (0xb7)

/**
 * Operation: Invoke static method
 * Operand stack: [arg1, arg2, ...] → result
 */
void opcode_invokestatic (struct stack_frame *frame); // 184 (0xb8)

/**
 * Operation: Invoke virtual method
 * Operand stack: objectref, [arg1, arg2, ...] → result
 */
void opcode_invokevirtual (struct stack_frame *frame); // 182 (0xb6)

/**
 * Operation: Bitwise OR of two ints
 * Operand stack: value1, value2 → result
 */
void opcode_ior (struct stack_frame *frame); // 128 (0x80)

/**
 * Operation: Remainder of int division
 * Operand stack: value1, value2 → result
 */
void opcode_irem (struct stack_frame *frame); // 112 (0x70)

/**
 * Operation: Return int from method
 * Operand stack: value → [empty]
 */
void opcode_ireturn (struct stack_frame *frame); // 172 (0xac)

/**
 * Operation: Shift left int
 * Operand stack: value1, value2 → result
 */
void opcode_ishl (struct stack_frame *frame); // 120 (0x78)

/**
 * Operation: Arithmetic shift right int
 * Operand stack: value1, value2 → result
 */
void opcode_ishr (struct stack_frame *frame); // 122 (0x7a)

// INTEGER STORE SECTION

/**
 * Operation: Store int into local variable (index)
 * Operand stack: value →
 */
void opcode_istore (struct stack_frame *frame); // 54 (0x36)

/**
 * Operation: Store int into local variable 0
 * Operand stack: value →
 */
void opcode_istore_0 (struct stack_frame *frame); // 59 (0x3b)

/**
 * Operation: Store int into local variable 1
 * Operand stack: value →
 */
void opcode_istore_1 (struct stack_frame *frame); // 60 (0x3c)

/**
 * Operation: Store int into local variable 2
 * Operand stack: value →
 */
void opcode_istore_2 (struct stack_frame *frame); // 61 (0x3d)

/**
 * Operation: Store int into local variable 3
 * Operand stack: value →
 */
void opcode_istore_3 (struct stack_frame *frame); // 62 (0x3e)

/**
 * Operation: Subtract two int values
 * Operand stack: value1, value2 → result
 */
void opcode_isub (struct stack_frame *frame); // 100 (0x64)

/**
 * Operation: Logical shift right int
 * Operand stack: value1, value2 → result
 */
void opcode_iushr (struct stack_frame *frame); // 124 (0x7c)

/**
 * Operation: Bitwise XOR of two ints
 * Operand stack: value1, value2 → result
 */
void opcode_ixor (struct stack_frame *frame); // 130 (0x82)

/**
 * Operation: Jump subroutine (short)
 * Operand stack: → address
 */
void opcode_jsr (struct stack_frame *frame); // 168 (0xa8)

/**
 * Operation: Jump subroutine (wide)
 * Operand stack: → address
 */
void opcode_jsr_w (struct stack_frame *frame); // 201 (0xc9)

/**
 * Operation: Convert long to double
 * Operand stack: value → result
 */
void opcode_l2d (struct stack_frame *frame); // 138 (0x8a)

/**
 * Operation: Convert long to float
 * Operand stack: value → result
 */
void opcode_l2f (struct stack_frame *frame); // 137 (0x89)

/**
 * Operation: Convert long to int
 * Operand stack: value → result
 */
void opcode_l2i (struct stack_frame *frame); // 136 (0x88)

/**
 * Operation: Add two long values
 * Operand stack: value1, value2 → result
 */
void opcode_ladd (struct stack_frame *frame); // 97 (0x61)

/**
 * Operation: Load long from array
 * Operand stack: arrayref, index → value
 */
void opcode_laload (struct stack_frame *frame); // 47 (0x2f)

/**
 * Operation: Bitwise AND of two longs
 * Operand stack: value1, value2 → result
 */
void opcode_land (struct stack_frame *frame); // 127 (0x7f)

/**
 * Operation: Store into long array
 * Operand stack: arrayref, index, value →
 */
void opcode_lastore (struct stack_frame *frame); // 80 (0x50)

/**
 * Operation: Compare two longs
 * Operand stack: value1, value2 → result
 */
void opcode_lcmp (struct stack_frame *frame); // 148 (0x94)

// LONG CONST

/**
 * Operation: Push long constant 0
 * Operand stack: → 0L
 */
void opcode_lconst_0 (struct stack_frame *frame); // 9 (0x09)

/**
 * Operation: Push long constant 1
 * Operand stack: → 1L
 */
void opcode_lconst_1 (struct stack_frame *frame); // 10 (0x0a)

/**
 * Operation: Push item from constant pool (index)
 * Operand stack: → value
 */
void opcode_ldc (struct stack_frame *frame); // 18 (0x12)

/**
 * Operation: Push item from constant pool (wide index)
 * Operand stack: → value
 */
void opcode_ldc_w (struct stack_frame *frame); // 19 (0x13)

/**
 * Operation: Push long or double from constant pool
 * Operand stack: → value
 */
void opcode_ldc2_w (struct stack_frame *frame); // 20 (0x14)

/**
 * Operation: Divide two long values
 * Operand stack: value1, value2 → result
 */
void opcode_ldiv (struct stack_frame *frame); // 109 (0x6d)

// LONG LOAD SECTION

/**
 * Operation: Load long from local variable (index)
 * Operand stack: → value
 */
void opcode_lload (struct stack_frame *frame); // 22 (0x16)

/**
 * Operation: Load long from local variable 0
 * Operand stack: → value
 */
void opcode_lload_0 (struct stack_frame *frame); // 30 (0x1e)

/**
 * Operation: Load long from local variable 1
 * Operand stack: → value
 */
void opcode_lload_1 (struct stack_frame *frame); // 31 (0x1f)

/**
 * Operation: Load long from local variable 2
 * Operand stack: → value
 */
void opcode_lload_2 (struct stack_frame *frame); // 32 (0x20)

/**
 * Operation: Load long from local variable 3
 * Operand stack: → value
 */
void opcode_lload_3 (struct stack_frame *frame); // 33 (0x21)

/**
 * Operation: Multiply two long values
 * Operand stack: value1, value2 → result
 */
void opcode_lmul (struct stack_frame *frame); // 105 (0x69)

/**
 * Operation: Negate long value
 * Operand stack: value → result
 */
void opcode_lneg (struct stack_frame *frame); // 117 (0x75)

/**
 * Operation: Jump by key match in table
 * Operand stack: key →
 */
void opcode_lookupswitch (struct stack_frame *frame); // 171 (0xab)

/**
 * Operation: Bitwise OR of two longs
 * Operand stack: value1, value2 → result
 */
void opcode_lor (struct stack_frame *frame); // 129 (0x81)

/**
 * Operation: Remainder of long division
 * Operand stack: value1, value2 → result
 */
void opcode_lrem (struct stack_frame *frame); // 113 (0x71)

/**
 * Operation: Return long from method
 * Operand stack: value → [empty]
 */
void opcode_lreturn (struct stack_frame *frame); // 173 (0xad)

/**
 * Operation: Shift left long
 * Operand stack: value1, value2 → result
 */
void opcode_lshl (struct stack_frame *frame); // 121 (0x79)

/**
 * Operation: Arithmetic shift right long
 * Operand stack: value1, value2 → result
 */
void opcode_lshr (struct stack_frame *frame); // 123 (0x7b)

// LONG STORE SECTION

/**
 * Operation: Store long into local variable (index)
 * Operand stack: value →
 */
void opcode_lstore (struct stack_frame *frame); // 55 (0x37)

/**
 * Operation: Store long into local variable 0
 * Operand stack: value →
 */
void opcode_lstore_0 (struct stack_frame *frame); // 63 (0x3f)

/**
 * Operation: Store long into local variable 1
 * Operand stack: value →
 */
void opcode_lstore_1 (struct stack_frame *frame); // 64 (0x40)

/**
 * Operation: Store long into local variable 2
 * Operand stack: value →
 */
void opcode_lstore_2 (struct stack_frame *frame); // 65 (0x41)

/**
 * Operation: Store long into local variable 3
 * Operand stack: value →
 */
void opcode_lstore_3 (struct stack_frame *frame); // 66 (0x42)

/**
 * Operation: Subtract two long values
 * Operand stack: value1, value2 → result
 */
void opcode_lsub (struct stack_frame *frame); // 101 (0x65)

/**
 * Operation: Logical shift right long
 * Operand stack: value1, value2 → result
 */
void opcode_lushr (struct stack_frame *frame); // 125 (0x7d)

/**
 * Operation: Bitwise XOR of two longs
 * Operand stack: value1, value2 → result
 */
void opcode_lxor (struct stack_frame *frame); // 131 (0x83)

// MONITOR SECTION

/**
 * Operation: Enter monitor for object
 * Operand stack: objectref →
 */
void opcode_monitorenter (struct stack_frame *frame); // 194 (0xc2)

/**
 * Operation: Exit monitor for object
 * Operand stack: objectref →
 */
void opcode_monitorexit (struct stack_frame *frame); // 195 (0xc3)

/**
 * Operation: Create new multidimensional array
 * Operand stack: count1, [count2, ...] → arrayref
 */
void opcode_multianewarray (struct stack_frame *frame); // 197 (0xc5)

// MEW SECTION

/**
 * Operation: Create new object
 * Operand stack: → objectref
 */
void opcode_new (struct stack_frame *frame); // 187 (0xbb)

/**
 * Operation: Create new primitive array
 * Operand stack: count → arrayref
 */
void opcode_newarray (struct stack_frame *frame); // 188 (0xbc)

/**
 * Operation: Do nothing
 * Operand stack: No change
 */
void opcode_nop (struct stack_frame *frame); // 0 (0x00)

// POP SECTION

/**
 * Operation: Pop top stack word
 * Operand stack: value →
 */
void opcode_pop (struct stack_frame *frame); // 87 (0x57)

/**
 * Operation: Pop top two stack words
 * Operand stack: value2, value1 →
 */
void opcode_pop2 (struct stack_frame *frame); // 88 (0x58)

/**
 * Operation: Set field in object
 * Operand stack: objectref, value →
 */
void opcode_putfield (struct stack_frame *frame); // 181 (0xb5)

/**
 * Operation: Set static field in class
 * Operand stack: value →
 */
void opcode_putstatic (struct stack_frame *frame); // 179 (0xb3)

// RETURN SECTION

/**
 * Operation: Return from subroutine
 * Operand stack: No change
 */
void opcode_ret (struct stack_frame *frame); // 169 (0xa9)

/**
 * Operation: Return void from method
 * Operand stack: → [empty]
 */
void opcode_return (struct stack_frame *frame); // 177 (0xb1)

/**
 * Operation: Load short from array
 * Operand stack: arrayref, index → value
 */
void opcode_saload (struct stack_frame *frame); // 53 (0x35)

/**
 * Operation: Store into short array
 * Operand stack: arrayref, index, value →
 */
void opcode_sastore (struct stack_frame *frame); // 86 (0x56)

/**
 * Operation: Push short constant
 * Operand stack: → value
 */
void opcode_sipush (struct stack_frame *frame); // 17 (0x11)

/**
 * Operation: Swap top two stack words
 * Operand stack: value2, value1 → value1, value2
 */
void opcode_swap (struct stack_frame *frame); // 95 (0x5f)

/**
 * Operation: Jump via index table
 * Operand stack: key →
 */
void opcode_tableswitch (struct stack_frame *frame); // 170 (0xaa)

/**
 * Operation: Extended wide instruction
 * Operand stack: [varies]
 */
void opcode_wide (struct stack_frame *frame); // 196 (0xc4)

void opcode_error (struct stack_frame *);

#endif
