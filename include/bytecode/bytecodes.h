#ifndef SHIP_JVM_BYTECODES_H
#define SHIP_JVM_BYTECODES_H

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

/**
 * Operation: Load reference from array
 * Operand stack: arrayref, index → value
 */
void opcode_aaload (); // 50 (0x32)

/**
 * Operation: Store into reference array
 * Operand stack: arrayref, index, value →
 */
void opcode_aastore (); // 83 (0x53)

/**
 * Operation: Push null reference
 * Operand stack: → null
 */
void opcode_aconst_null (); // 1 (0x01)

// aload section

/**
 * Operation: Load reference from local variable
 * Operand stack: → objectref
 */
void opcode_aload (); // 25 (0x19)

/**
 * Operation: Load reference from local variable 0
 * Operand stack: → objectref
 */
void opcode_aload_0 (); // 42 (0x2a)

/**
 * Operation: Load reference from local variable 1
 * Operand stack: → objectref
 */
void opcode_aload_1 (); // 43 (0x2b)

/**
 * Operation: Load reference from local variable 2
 * Operand stack: → objectref
 */
void opcode_aload_2 (); // 44 (0x2c)

/**
 * Operation: Load reference from local variable 3
 * Operand stack: → objectref
 */
void opcode_aload_3 (); // 45 (0x2d)

/**
 * Operation: Create new array of references
 * Operand stack: count → arrayref
 */
void opcode_anewarray (); // 189 (0xbd)

/**
 * Operation: Return reference from method
 * Operand stack: objectref → [empty]
 */
void opcode_areturn (); // 176 (0xb0)

/**
 * Operation: Get length of array
 * Operand stack: arrayref → length
 */
void opcode_arraylength (); // 190 (0xbe)

// astore

/**
 * Operation: Store reference into local variable
 * Operand stack: objectref →
 */
void opcode_astore (); // 58 (0x3a)

/**
 * Operation: Store reference into local variable 0
 * Operand stack: objectref →
 */
void opcode_astore_0 (); // 75 (0x4b)

/**
 * Operation: Store reference into local variable 1
 * Operand stack: objectref →
 */
void opcode_astore_1 (); // 76 (0x4c)

/**
 * Operation: Store reference into local variable 2
 * Operand stack: objectref →
 */
void opcode_astore_2 (); // 77 (0x4d)

/**
 * Operation: Store reference into local variable 3
 * Operand stack: objectref →
 */
void opcode_astore_3 (); // 78 (0x4e)

/**
 * Operation: Throw exception or error
 * Operand stack: objectref → [empty], objectref
 */
void opcode_athrow (); // 191 (0xbf)

/**
 * Operation: Load byte or boolean from array
 * Operand stack: arrayref, index → value
 */
void opcode_baload (); // 51 (0x33)

/**
 * Operation: Store into byte or boolean array
 * Operand stack: arrayref, index, value →
 */
void opcode_bastore (); // 84 (0x54)

/**
 * Operation: Push byte as integer
 * Operand stack: → value
 */
void opcode_bipush (); // 16 (0x10)

/**
 * Operation: Load char from array
 * Operand stack: arrayref, index → value
 */
void opcode_caload (); // 52 (0x34)

/**
 * Operation: Store into char array
 * Operand stack: arrayref, index, value →
 */
void opcode_castore (); // 85 (0x55)

/**
 * Operation: Check whether object is of given type
 * Operand stack: objectref → objectref
 */
void opcode_checkcast (); // 192 (0xc0)

/**
 * Operation: Convert double to float
 * Operand stack: value → result
 */
void opcode_d2f (); // 144 (0x90)

/**
 * Operation: Convert double to int
 * Operand stack: value → result
 */
void opcode_d2i (); // 142 (0x8e)

/**
 * Operation: Convert double to long
 * Operand stack: value → result
 */
void opcode_d2l (); // 143 (0x8f)

/**
 * Operation: Add two double values
 * Operand stack: value1, value2 → result
 */
void opcode_dadd (); // 99 (0x63)

/**
 * Operation: Load double from array
 * Operand stack: arrayref, index → value
 */
void opcode_daload (); // 49 (0x31)

/**
 * Operation: Store into double array
 * Operand stack: arrayref, index, value →
 */
void opcode_dastore (); // 82 (0x52)

/**
 * Operation: Compare double (returns 1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_dcmpg (); // 152 (0x98)

/**
 * Operation: Compare double (returns -1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_dcmpl (); // 151 (0x97)

// dconst section

/**
 * Operation: Push double constant 0.0
 * Operand stack: → 0.0
 */
void opcode_dconst_0 (); // 14 (0x0e)

/**
 * Operation: Push double constant 1.0
 * Operand stack: → 1.0
 */
void opcode_dconst_1 (); // 15 (0x0f)

/**
 * Operation: Divide two double values
 * Operand stack: value1, value2 → result
 */
void opcode_ddiv (); // 111 (0x6f)

// dload

/**
 * Operation: Load double from local variable 0
 * Operand stack: → value
 */
void opcode_dload_0 (); // 38 (0x26)

/**
 * Operation: Load double from local variable 1
 * Operand stack: → value
 */
void opcode_dload_1 (); // 39 (0x27)

/**
 * Operation: Load double from local variable 2
 * Operand stack: → value
 */
void opcode_dload_2 (); // 40 (0x28)

/**
 * Operation: Load double from local variable 3
 * Operand stack: → value
 */
void opcode_dload_3 (); // 41 (0x29)

/**
 * Operation: Multiply two double values
 * Operand stack: value1, value2 → result
 */
void opcode_dmul (); // 107 (0x6b)

/**
 * Operation: Negate double value
 * Operand stack: value → result
 */
void opcode_dneg (); // 119 (0x77)

/**
 * Operation: Get remainder from division of two doubles
 * Operand stack: value1, value2 → result
 */
void opcode_drem (); // 115 (0x73)

/**
 * Operation: Return double from method
 * Operand stack: value → [empty]
 */
void opcode_dreturn (); // 175 (0xaf)

// dstore section

/**
 * Operation: Store double into local variable (index)
 * Operand stack: value →
 */
void opcode_dstore (); // 57 (0x39)

/**
 * Operation: Store double into local variable 1
 * Operand stack: value →
 */
void opcode_dstore_1 (); // 72 (0x48)

/**
 * Operation: Store double into local variable 2
 * Operand stack: value →
 */
void opcode_dstore_2 (); // 73 (0x49)

/**
 * Operation: Store double into local variable 3
 * Operand stack: value →
 */
void opcode_dstore_3 (); // 74 (0x4a)

/**
 * Operation: Subtract two double values
 * Operand stack: value1, value2 → result
 */
void opcode_dsub (); // 103 (0x67)

// dup section

/**
 * Operation: Duplicate top stack value
 * Operand stack: value → value, value
 */
void opcode_dup (); // 89 (0x59)

/**
 * Operation: Duplicate top stack value and insert two values down
 * Operand stack: value2, value1 → value1, value2, value1
 */
void opcode_dup_x1 (); // 90 (0x5a)

/**
 * Operation: Duplicate top stack value and insert three values down
 * Operand stack: value3, value2, value1 → value1, value3, value2, value1
 */
void opcode_dup_x2 (); // 91 (0x5b)

/**
 * Operation: Duplicate top two stack values
 * Operand stack: value2, value1 → value2, value1, value2, value1
 */
void opcode_dup2 (); // 92 (0x5c)

/**
 * Operation: Duplicate top two values and insert three values down
 * Operand stack: value3, value2, value1 → value2, value1, value3, value2,
 * value1
 */
void opcode_dup2_x1 (); // 93 (0x5d)

/**
 * Operation: Duplicate top two values and insert four values down
 * Operand stack: value4, value3, value2, value1 → value2, value1, value4,
 * value3, value2, value1
 */
void opcode_dup2_x2 (); // 94 (0x5e)

// float to section

/**
 * Operation: Convert float to double
 * Operand stack: value → result
 */
void opcode_f2d (); // 141 (0x8d)

/**
 * Operation: Convert float to int
 * Operand stack: value → result
 */
void opcode_f2i (); // 139 (0x8b)

/**
 * Operation: Convert float to long
 * Operand stack: value → result
 */
void opcode_f2l (); // 140 (0x8c)

// float operations

/**
 * Operation: Add two float values
 * Operand stack: value1, value2 → result
 */
void opcode_fadd (); // 98 (0x62)

/**
 * Operation: Load float from array
 * Operand stack: arrayref, index → value
 */
void opcode_faload (); // 48 (0x30)

/**
 * Operation: Store into float array
 * Operand stack: arrayref, index, value →
 */
void opcode_fastore (); // 81 (0x51)

/**
 * Operation: Compare float (returns 1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_fcmpg (); // 150 (0x96)

/**
 * Operation: Compare float (returns -1 if NaN)
 * Operand stack: value1, value2 → result
 */
void opcode_fcmpl (); // 149 (0x95)

// float const section

/**
 * Operation: Push float constant 0.0f
 * Operand stack: → 0.0f
 */
void opcode_fconst_0 (); // 11 (0x0b)

/**
 * Operation: Push float constant 1.0f
 * Operand stack: → 1.0f
 */
void opcode_fconst_1 (); // 12 (0x0c)

/**
 * Operation: Push float constant 2.0f
 * Operand stack: → 2.0f
 */
void opcode_fconst_2 (); // 13 (0x0d)

/**
 * Operation: Divide two float values
 * Operand stack: value1, value2 → result
 */
void opcode_fdiv (); // 110 (0x6e)

// float load section

/**
 * Operation: Load float from local variable (index)
 * Operand stack: → value
 */
void opcode_fload (); // 23 (0x17)

/**
 * Operation: Load float from local variable 0
 * Operand stack: → value
 */
void opcode_fload_0 (); // 34 (0x22)

/**
 * Operation: Load float from local variable 1
 * Operand stack: → value
 */
void opcode_fload_1 (); // 35 (0x23)

/**
 * Operation: Load float from local variable 2
 * Operand stack: → value
 */
void opcode_fload_2 (); // 36 (0x24)

/**
 * Operation: Load float from local variable 3
 * Operand stack: → value
 */
void opcode_fload_3 (); // 37 (0x25)

void opcode_fmul ();
void opcode_fneg ();
void opcode_frem ();
void opcode_freturn ();

void opcode_fstore ();
void opcode_fstore_0 ();
void opcode_fstore_1 ();
void opcode_fstore_2 ();
void opcode_fstore_3 ();

void opcode_fsub ();
void opcode_getfield ();
void opcode_getstatic ();

void opcode_goto ();
void opcode_goto_w ();

void opcode_i2b ();
void opcode_i2c ();
void opcode_i2d ();
void opcode_i2f ();
void opcode_i2l ();
void opcode_i2s ();

void opcode_iadd ();
void opcode_iaload ();
void opcode_iand ();
void opcode_iastore ();
void opcode_iconst_m1 ();

void opcode_iconst_0 ();
void opcode_iconst_1 ();
void opcode_iconst_2 ();
void opcode_iconst_3 ();
void opcode_iconst_4 ();
void opcode_iconst_5 ();

void opcode_idiv ();

void opcode_if_acmpeq ();
void opcode_if_acmpne ();
void opcode_if_icmpeq ();
void opcode_if_icmpne ();
void opcode_if_icmplt ();
void opcode_if_icmpge ();
void opcode_if_icmpgt ();
void opcode_if_icmple ();

void opcode_ifeq ();
void opcode_ifne ();
void opcode_iflt ();
void opcode_ifge ();
void opcode_ifgt ();
void opcode_ifle ();

void opcode_ifnonnull ();
void opcode_ifnull ();
void opcode_iinc ();

void opcode_iload ();
void opcode_iload_1 ();
void opcode_iload_2 ();
void opcode_iload_3 ();

void opcode_imull ();
void opcode_ineg ();
void opcode_instanceof ();

void opcode_invokedynamic ();
void opcode_invokeinterface ();
void opcode_invokespecial ();
void opcode_invokestatic ();
void opcode_invokevirtual ();

void opcode_ior ();
void opcode_irem ();
void opcode_ireturn ();
void opcode_ishl ();
void opcode_ishr ();

void opcode_istore ();
void opcode_istore_0 ();
void opcode_istore_1 ();
void opcode_istore_2 ();
void opcode_istore_3 ();

void opcode_isub ();
void opcode_iushr ();
void opcode_ixor ();

void opcode_jsr ();
void opcode_jsr_w ();

void opcode_l2d ();
void opcode_l2f ();
void opcode_l2i ();

void opcode_ladd ();
void opcode_laload ();
void opcode_land ();
void opcode_lastore ();
void opcode_lcmp ();

void opcode_lconst_0 ();
void opcode_lconst_1 ();

void opcode_ldc ();
void opcode_ldc_w ();
void opcode_ldc2_w ();

void opcode_ldiv ();

void opcode_lload ();
void opcode_lload_0 ();
void opcode_lload_1 ();
void opcode_lload_2 ();
void opcode_lload_3 ();

void opcode_lmul ();
void opcode_lneg ();
void opcode_lookupswitch ();
void opcode_lor ();
void opcode_lrem ();
void opcode_lreturn ();
void opcode_lshl ();
void opcode_lshr ();

void opcode_lstore ();
void opcode_lstore_0 ();
void opcode_lstore_1 ();
void opcode_lstore_2 ();
void opcode_lstore_3 ();

void opcode_lsub ();
void opcode_lushr ();
void opcode_lxor ();
void opcode_monitorenter ();
void opcode_monitorexit ();
void opcode_multianewarray ();
void opcode_new ();
void opcode_newarray ();
void opcode_nop ();
void opcode_pop ();
void opcode_pop2 ();
void opcode_putfield ();
void opcode_putstatic ();
void opcode_ret ();
void opcode_return ();
void opcode_saload ();
void opcode_sastore ();
void opcode_sipush ();
void opcode_swap ();
void opcode_tableswitch ();
void opcode_wide ();

#endif
