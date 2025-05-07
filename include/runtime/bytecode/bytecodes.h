#ifndef SHIP_JVM_BYTECODES_H
#define SHIP_JVM_BYTECODES_H

#include "java_types.h"
#include "stack_frames.h"

#define OPC_NOP 0
#define OPC_ACONST_NULL 1
#define OPC_ICONST_M1 2
#define OPC_ICONST_0 3
#define OPC_ICONST_1 4
#define OPC_ICONST_2 5
#define OPC_ICONST_3 6
#define OPC_ICONST_4 7
#define OPC_ICONST_5 8
#define OPC_LCONST_0 9
#define OPC_LCONST_1 10
#define OPC_FCONST_0 11
#define OPC_FCONST_1 12
#define OPC_FCONST_2 13
#define OPC_DCONST_0 14
#define OPC_DCONST_1 15
#define OPC_BIPUSH 16
#define OPC_SIPUSH 17
#define OPC_LDC 18
#define OPC_LDC_W 19
#define OPC_LDC2_W 20
#define OPC_ILOAD 21
#define OPC_LLOAD 22
#define OPC_FLOAD 23
#define OPC_DLOAD 24
#define OPC_ALOAD 25
#define OPC_ILOAD_0 26
#define OPC_ILOAD_1 27
#define OPC_ILOAD_2 28
#define OPC_ILOAD_3 29
#define OPC_LLOAD_0 30
#define OPC_LLOAD_1 31
#define OPC_LLOAD_2 32
#define OPC_LLOAD_3 33
#define OPC_FLOAD_0 34
#define OPC_FLOAD_1 35
#define OPC_FLOAD_2 36
#define OPC_FLOAD_3 37
#define OPC_DLOAD_0 38
#define OPC_DLOAD_1 39
#define OPC_DLOAD_2 40
#define OPC_DLOAD_3 41
#define OPC_ALOAD_0 42
#define OPC_ALOAD_1 43
#define OPC_ALOAD_2 44
#define OPC_ALOAD_3 45
#define OPC_IALOAD 46
#define OPC_LALOAD 47
#define OPC_FALOAD 48
#define OPC_DALOAD 49
#define OPC_AALOAD 50
#define OPC_BALOAD 51
#define OPC_CALOAD 52
#define OPC_SALOAD 53
#define OPC_ISTORE 54
#define OPC_LSTORE 55
#define OPC_FSTORE 56
#define OPC_DSTORE 57
#define OPC_ASTORE 58
#define OPC_ISTORE_0 59
#define OPC_ISTORE_1 60
#define OPC_ISTORE_2 61
#define OPC_ISTORE_3 62
#define OPC_LSTORE_0 63
#define OPC_LSTORE_1 64
#define OPC_LSTORE_2 65
#define OPC_LSTORE_3 66
#define OPC_FSTORE_0 67
#define OPC_FSTORE_1 68
#define OPC_FSTORE_2 69
#define OPC_FSTORE_3 70
#define OPC_DSTORE_0 71
#define OPC_DSTORE_1 72
#define OPC_DSTORE_2 73
#define OPC_DSTORE_3 74
#define OPC_ASTORE_0 75
#define OPC_ASTORE_1 76
#define OPC_ASTORE_2 77
#define OPC_ASTORE_3 78
#define OPC_IASTORE 79
#define OPC_LASTORE 80
#define OPC_FASTORE 81
#define OPC_DASTORE 82
#define OPC_AASTORE 83
#define OPC_BASTORE 84
#define OPC_CASTORE 85
#define OPC_SASTORE 86
#define OPC_POP 87
#define OPC_POP2 88
#define OPC_DUP 89
#define OPC_DUP_X1 90
#define OPC_DUP_X2 91
#define OPC_DUP2 92
#define OPC_DUP2_X1 93
#define OPC_DUP2_X2 94
#define OPC_SWAP 95
#define OPC_IADD 96
#define OPC_LADD 97
#define OPC_FADD 98
#define OPC_DADD 99
#define OPC_ISUB 100
#define OPC_LSUB 101
#define OPC_FSUB 102
#define OPC_DSUB 103
#define OPC_IMUL 104
#define OPC_LMUL 105
#define OPC_FMUL 106
#define OPC_DMUL 107
#define OPC_IDIV 108
#define OPC_LDIV 109
#define OPC_FDIV 110
#define OPC_DDIV 111
#define OPC_IREM 112
#define OPC_LREM 113
#define OPC_FREM 114
#define OPC_DREM 115
#define OPC_INEG 116
#define OPC_LNEG 117
#define OPC_FNEG 118
#define OPC_DNEG 119
#define OPC_ISHL 120
#define OPC_LSHL 121
#define OPC_ISHR 122
#define OPC_LSHR 123
#define OPC_IUSHR 124
#define OPC_LUSHR 125
#define OPC_IAND 126
#define OPC_LAND 127
#define OPC_IOR 128
#define OPC_LOR 129
#define OPC_IXOR 130
#define OPC_LXOR 131
#define OPC_IINC 132
#define OPC_I2L 133
#define OPC_I2F 134
#define OPC_I2D 135
#define OPC_L2I 136
#define OPC_L2F 137
#define OPC_L2D 138
#define OPC_F2I 139
#define OPC_F2L 140
#define OPC_F2D 141
#define OPC_D2I 142
#define OPC_D2L 143
#define OPC_D2F 144
#define OPC_I2B 145
#define OPC_I2C 146
#define OPC_I2S 147
#define OPC_LCMP 148
#define OPC_FCMPL 149
#define OPC_FCMPG 150
#define OPC_DCMPL 151
#define OPC_DCMPG 152
#define OPC_IFEQ 153
#define OPC_IFNE 154
#define OPC_IFLT 155
#define OPC_IFGE 156
#define OPC_IFGT 157
#define OPC_IFLE 158
#define OPC_IF_ICMPEQ 159
#define OPC_IF_ICMPNE 160
#define OPC_IF_ICMPLT 161
#define OPC_IF_ICMPGE 162
#define OPC_IF_ICMPGT 163
#define OPC_IF_ICMPLE 164
#define OPC_IF_ACMPEQ 165
#define OPC_IF_ACMPNE 166
#define OPC_GOTO 167
#define OPC_JSR 168
#define OPC_RET 169
#define OPC_TABLESWITCH 170
#define OPC_LOOKUPSWITCH 171
#define OPC_IRETURN 172
#define OPC_LRETURN 173
#define OPC_FRETURN 174
#define OPC_DRETURN 175
#define OPC_ARETURN 176
#define OPC_RETURN 177
#define OPC_GETSTATIC 178
#define OPC_PUTSTATIC 179
#define OPC_GETFIELD 180
#define OPC_PUTFIELD 181
#define OPC_INVOKEVIRTUAL 182
#define OPC_INVOKESPECIAL 183
#define OPC_INVOKESTATIC 184
#define OPC_INVOKEINTERFACE 185
#define OPC_INVOKEDYNAMIC 186
#define OPC_NEW 187
#define OPC_NEWARRAY 188
#define OPC_ANEWARRAY 189
#define OPC_ARRAYLENGTH 190
#define OPC_ATHROW 191
#define OPC_CHECKCAST 192
#define OPC_INSTANCEOF 193
#define OPC_MONITORENTER 194
#define OPC_MONITOREXIT 195
#define OPC_WIDE 196
#define OPC_MULTIANEWARRAY 197
#define OPC_IFNULL 198
#define OPC_IFNONNULL 199
#define OPC_GOTO_W 200
#define OPC_JSR_W 201
#define OPC_BREAKPOINT 202
#define OPC_IMPDEP1 254
#define OPC_IMPDEP2 255
#define OPC_NUM_OPCODES 256

typedef void (*opcode_handler) (struct stack_frame *);

struct runtime_opcode
{
  const char *name;
  opcode_handler handler;
};

#define OPCODES_NUMBER 257

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

static const struct runtime_opcode OPCODE_TABLE[OPCODES_NUMBER] = {
  [OPC_NOP] = { "nop", opcode_nop },
  [OPC_ACONST_NULL] = { "aconst_null", opcode_aconst_null },
  [OPC_ICONST_M1] = { "iconst_m1", opcode_iconst_m1 },
  [OPC_ICONST_0] = { "iconst_0", opcode_iconst_0 },
  [OPC_ICONST_1] = { "iconst_1", opcode_iconst_1 },
  [OPC_ICONST_2] = { "iconst_2", opcode_iconst_2 },
  [OPC_ICONST_3] = { "iconst_3", opcode_iconst_3 },
  [OPC_ICONST_4] = { "iconst_4", opcode_iconst_4 },
  [OPC_ICONST_5] = { "iconst_5", opcode_iconst_5 },
  [OPC_LCONST_0] = { "lconst_0", opcode_lconst_0 },
  [OPC_LCONST_1] = { "lconst_1", opcode_lconst_1 },
  [OPC_FCONST_0] = { "fconst_0", opcode_fconst_0 },
  [OPC_FCONST_1] = { "fconst_1", opcode_fconst_1 },
  [OPC_FCONST_2] = { "fconst_2", opcode_fconst_2 },
  [OPC_DCONST_0] = { "dconst_0", opcode_dconst_0 },
  [OPC_DCONST_1] = { "dconst_1", opcode_dconst_1 },
  [OPC_BIPUSH] = { "bipush", opcode_bipush },
  [OPC_SIPUSH] = { "sipush", opcode_sipush },
  [OPC_LDC] = { "ldc", opcode_ldc },
  [OPC_LDC_W] = { "ldc_w", opcode_ldc_w },
  [OPC_LDC2_W] = { "ldc2_w", opcode_ldc2_w },
  [OPC_ILOAD] = { "iload", opcode_iload },
  [OPC_LLOAD] = { "lload", opcode_lload },
  [OPC_FLOAD] = { "fload", opcode_fload },
  [OPC_DLOAD] = { "dload", opcode_dload },
  [OPC_ALOAD] = { "aload", opcode_aload },
  [OPC_ILOAD_0] = { "iload_0", opcode_iload_0 },
  [OPC_ILOAD_1] = { "iload_1", opcode_iload_1 },
  [OPC_ILOAD_2] = { "iload_2", opcode_iload_2 },
  [OPC_ILOAD_3] = { "iload_3", opcode_iload_3 },
  [OPC_LLOAD_0] = { "lload_0", opcode_lload_0 },
  [OPC_LLOAD_1] = { "lload_1", opcode_lload_1 },
  [OPC_LLOAD_2] = { "lload_2", opcode_lload_2 },
  [OPC_LLOAD_3] = { "lload_3", opcode_lload_3 },
  [OPC_FLOAD_0] = { "fload_0", opcode_fload_0 },
  [OPC_FLOAD_1] = { "fload_1", opcode_fload_1 },
  [OPC_FLOAD_2] = { "fload_2", opcode_fload_2 },
  [OPC_FLOAD_3] = { "fload_3", opcode_fload_3 },
  [OPC_DLOAD_0] = { "dload_0", opcode_dload_0 },
  [OPC_DLOAD_1] = { "dload_1", opcode_dload_1 },
  [OPC_DLOAD_2] = { "dload_2", opcode_dload_2 },
  [OPC_DLOAD_3] = { "dload_3", opcode_dload_3 },
  [OPC_ALOAD_0] = { "aload_0", opcode_aload_0 },
  [OPC_ALOAD_1] = { "aload_1", opcode_aload_1 },
  [OPC_ALOAD_2] = { "aload_2", opcode_aload_2 },
  [OPC_ALOAD_3] = { "aload_3", opcode_aload_3 },
  [OPC_IALOAD] = { "iaload", opcode_iaload },
  [OPC_LALOAD] = { "laload", opcode_laload },
  [OPC_FALOAD] = { "faload", opcode_faload },
  [OPC_DALOAD] = { "daload", opcode_daload },
  [OPC_AALOAD] = { "aaload", opcode_aaload },
  [OPC_BALOAD] = { "baload", opcode_baload },
  [OPC_CALOAD] = { "caload", opcode_caload },
  [OPC_SALOAD] = { "saload", opcode_saload },
  [OPC_ISTORE] = { "istore", opcode_istore },
  [OPC_LSTORE] = { "lstore", opcode_lstore },
  [OPC_FSTORE] = { "fstore", opcode_fstore },
  [OPC_DSTORE] = { "dstore", opcode_dstore },
  [OPC_ASTORE] = { "astore", opcode_astore },
  [OPC_ISTORE_0] = { "istore_0", opcode_istore_0 },
  [OPC_ISTORE_1] = { "istore_1", opcode_istore_1 },
  [OPC_ISTORE_2] = { "istore_2", opcode_istore_2 },
  [OPC_ISTORE_3] = { "istore_3", opcode_istore_3 },
  [OPC_LSTORE_0] = { "lstore_0", opcode_lstore_0 },
  [OPC_LSTORE_1] = { "lstore_1", opcode_lstore_1 },
  [OPC_LSTORE_2] = { "lstore_2", opcode_lstore_2 },
  [OPC_LSTORE_3] = { "lstore_3", opcode_lstore_3 },
  [OPC_FSTORE_0] = { "fstore_0", opcode_fstore_0 },
  [OPC_FSTORE_1] = { "fstore_1", opcode_fstore_1 },
  [OPC_FSTORE_2] = { "fstore_2", opcode_fstore_2 },
  [OPC_FSTORE_3] = { "fstore_3", opcode_fstore_3 },
  [OPC_DSTORE_0] = { "dstore_0", opcode_dstore_0 },
  [OPC_DSTORE_1] = { "dstore_1", opcode_dstore_1 },
  [OPC_DSTORE_2] = { "dstore_2", opcode_dstore_2 },
  [OPC_DSTORE_3] = { "dstore_3", opcode_dstore_3 },
  [OPC_ASTORE_0] = { "astore_0", opcode_astore_0 },
  [OPC_ASTORE_1] = { "astore_1", opcode_astore_1 },
  [OPC_ASTORE_2] = { "astore_2", opcode_astore_2 },
  [OPC_ASTORE_3] = { "astore_3", opcode_astore_3 },
  [OPC_IASTORE] = { "iastore", opcode_iastore },
  [OPC_LASTORE] = { "lastore", opcode_lastore },
  [OPC_FASTORE] = { "fastore", opcode_fastore },
  [OPC_DASTORE] = { "dastore", opcode_dastore },
  [OPC_AASTORE] = { "aastore", opcode_aastore },
  [OPC_BASTORE] = { "bastore", opcode_bastore },
  [OPC_CASTORE] = { "castore", opcode_castore },
  [OPC_SASTORE] = { "sastore", opcode_sastore },
  [OPC_POP] = { "pop", opcode_pop },
  [OPC_POP2] = { "pop2", opcode_pop2 },
  [OPC_DUP] = { "dup", opcode_dup },
  [OPC_DUP_X1] = { "dup_x1", opcode_dup_x1 },
  [OPC_DUP_X2] = { "dup_x2", opcode_dup_x2 },
  [OPC_DUP2] = { "dup2", opcode_dup2 },
  [OPC_DUP2_X1] = { "dup2_x1", opcode_dup2_x1 },
  [OPC_DUP2_X2] = { "dup2_x2", opcode_dup2_x2 },
  [OPC_SWAP] = { "swap", opcode_swap },
  [OPC_IADD] = { "iadd", opcode_iadd },
  [OPC_LADD] = { "ladd", opcode_ladd },
  [OPC_FADD] = { "fadd", opcode_fadd },
  [OPC_DADD] = { "dadd", opcode_dadd },
  [OPC_ISUB] = { "isub", opcode_isub },
  [OPC_LSUB] = { "lsub", opcode_lsub },
  [OPC_FSUB] = { "fsub", opcode_fsub },
  [OPC_DSUB] = { "dsub", opcode_dsub },
  [OPC_IMUL] = { "imul", opcode_imul },
  [OPC_LMUL] = { "lmul", opcode_lmul },
  [OPC_FMUL] = { "fmul", opcode_fmul },
  [OPC_DMUL] = { "dmul", opcode_dmul },
  [OPC_IDIV] = { "idiv", opcode_idiv },
  [OPC_LDIV] = { "ldiv", opcode_ldiv },
  [OPC_FDIV] = { "fdiv", opcode_fdiv },
  [OPC_DDIV] = { "ddiv", opcode_ddiv },
  [OPC_IREM] = { "irem", opcode_irem },
  [OPC_LREM] = { "lrem", opcode_lrem },
  [OPC_FREM] = { "frem", opcode_frem },
  [OPC_DREM] = { "drem", opcode_drem },
  [OPC_INEG] = { "ineg", opcode_ineg },
  [OPC_LNEG] = { "lneg", opcode_lneg },
  [OPC_FNEG] = { "fneg", opcode_fneg },
  [OPC_DNEG] = { "dneg", opcode_dneg },
  [OPC_ISHL] = { "ishl", opcode_ishl },
  [OPC_LSHL] = { "lshl", opcode_lshl },
  [OPC_ISHR] = { "ishr", opcode_ishr },
  [OPC_LSHR] = { "lshr", opcode_lshr },
  [OPC_IUSHR] = { "iushr", opcode_iushr },
  [OPC_LUSHR] = { "lushr", opcode_lushr },
  [OPC_IAND] = { "iand", opcode_iand },
  [OPC_LAND] = { "land", opcode_land },
  [OPC_IOR] = { "ior", opcode_ior },
  [OPC_LOR] = { "lor", opcode_lor },
  [OPC_IXOR] = { "ixor", opcode_ixor },
  [OPC_LXOR] = { "lxor", opcode_lxor },
  [OPC_IINC] = { "iinc", opcode_iinc },
  [OPC_I2L] = { "i2l", opcode_i2l },
  [OPC_I2F] = { "i2f", opcode_i2f },
  [OPC_I2D] = { "i2d", opcode_i2d },
  [OPC_L2I] = { "l2i", opcode_l2i },
  [OPC_L2F] = { "l2f", opcode_l2f },
  [OPC_L2D] = { "l2d", opcode_l2d },
  [OPC_F2I] = { "f2i", opcode_f2i },
  [OPC_F2L] = { "f2l", opcode_f2l },
  [OPC_F2D] = { "f2d", opcode_f2d },
  [OPC_D2I] = { "d2i", opcode_d2i },
  [OPC_D2L] = { "d2l", opcode_d2l },
  [OPC_D2F] = { "d2f", opcode_d2f },
  [OPC_I2B] = { "i2b", opcode_i2b },
  [OPC_I2C] = { "i2c", opcode_i2c },
  [OPC_I2S] = { "i2s", opcode_i2s },
  [OPC_LCMP] = { "lcmp", opcode_lcmp },
  [OPC_FCMPL] = { "fcmpl", opcode_fcmpl },
  [OPC_FCMPG] = { "fcmpg", opcode_fcmpg },
  [OPC_DCMPL] = { "dcmpl", opcode_dcmpl },
  [OPC_DCMPG] = { "dcmpg", opcode_dcmpg },
  [OPC_IFEQ] = { "ifeq", opcode_ifeq },
  [OPC_IFNE] = { "ifne", opcode_ifne },
  [OPC_IFLT] = { "iflt", opcode_iflt },
  [OPC_IFGE] = { "ifge", opcode_ifge },
  [OPC_IFGT] = { "ifgt", opcode_ifgt },
  [OPC_IFLE] = { "ifle", opcode_ifle },
  [OPC_IF_ICMPEQ] = { "if_icmpeq", opcode_if_icmpeq },
  [OPC_IF_ICMPNE] = { "if_icmpne", opcode_if_icmpne },
  [OPC_IF_ICMPLT] = { "if_icmplt", opcode_if_icmplt },
  [OPC_IF_ICMPGE] = { "if_icmpge", opcode_if_icmpge },
  [OPC_IF_ICMPGT] = { "if_icmpgt", opcode_if_icmpgt },
  [OPC_IF_ICMPLE] = { "if_icmple", opcode_if_icmple },
  [OPC_IF_ACMPEQ] = { "if_acmpeq", opcode_if_acmpeq },
  [OPC_IF_ACMPNE] = { "if_acmpne", opcode_if_acmpne },
  [OPC_GOTO] = { "goto", opcode_goto },
  [OPC_JSR] = { "jsr", opcode_jsr },
  [OPC_RET] = { "ret", opcode_ret },
  [OPC_TABLESWITCH] = { "tableswitch", opcode_tableswitch },
  [OPC_LOOKUPSWITCH] = { "lookupswitch", opcode_lookupswitch },
  [OPC_IRETURN] = { "ireturn", opcode_ireturn },
  [OPC_LRETURN] = { "lreturn", opcode_lreturn },
  [OPC_FRETURN] = { "freturn", opcode_freturn },
  [OPC_DRETURN] = { "dreturn", opcode_dreturn },
  [OPC_ARETURN] = { "areturn", opcode_areturn },
  [OPC_RETURN] = { "return", opcode_return },
  [OPC_GETSTATIC] = { "getstatic", opcode_getstatic },
  [OPC_PUTSTATIC] = { "putstatic", opcode_putstatic },
  [OPC_GETFIELD] = { "getfield", opcode_getfield },
  [OPC_PUTFIELD] = { "putfield", opcode_putfield },
  [OPC_INVOKEVIRTUAL] = { "invokevirtual", opcode_invokevirtual },
  [OPC_INVOKESPECIAL] = { "invokespecial", opcode_invokespecial },
  [OPC_INVOKESTATIC] = { "invokestatic", opcode_invokestatic },
  [OPC_INVOKEINTERFACE] = { "invokeinterface", opcode_invokeinterface },
  [OPC_INVOKEDYNAMIC] = { "invokedynamic", opcode_invokedynamic },
  [OPC_NEW] = { "new", opcode_new },
  [OPC_NEWARRAY] = { "newarray", opcode_newarray },
  [OPC_ANEWARRAY] = { "anewarray", opcode_anewarray },
  [OPC_ARRAYLENGTH] = { "arraylength", opcode_arraylength },
  [OPC_ATHROW] = { "athrow", opcode_athrow },
  [OPC_CHECKCAST] = { "checkcast", opcode_checkcast },
  [OPC_INSTANCEOF] = { "instanceof", opcode_instanceof },
  [OPC_MONITORENTER] = { "monitorenter", opcode_monitorenter },
  [OPC_MONITOREXIT] = { "monitorexit", opcode_monitorexit },
  [OPC_WIDE] = { "wide", opcode_wide },
  [OPC_MULTIANEWARRAY] = { "multianewarray", opcode_multianewarray },
  [OPC_IFNULL] = { "ifnull", opcode_ifnull },
  [OPC_IFNONNULL] = { "ifnonnull", opcode_ifnonnull },
  [OPC_GOTO_W] = { "goto_w", opcode_goto_w },
  [OPC_JSR_W] = { "jsr_w", opcode_jsr_w },
  // [OPC_BREAKPOINT] = {"opc_breakpoint", opcode_breakpoint},
  // [OPC_IMPDEP1] = {"opc_impdep1", opcode_impdep1},
  // [OPC_IMPDEP2] = {"opc_impdep2", opcode_impdep2},
  // [OPC_NUM_OPCODES] = {"opc_num_opcodes", opcode_num_opcodes},
};

#endif
