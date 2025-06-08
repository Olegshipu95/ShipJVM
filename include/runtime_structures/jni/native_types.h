#ifndef SHIP_JVM_NATIVE_TYPES_H
#define SHIP_JVM_NATIVE_TYPES_H

struct stack_frame; // forward declaration

typedef int (*native_func_t) (struct stack_frame *frame);

#endif
