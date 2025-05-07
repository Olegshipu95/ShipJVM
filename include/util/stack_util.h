// Stack section
#include <stdint.h>
#include <stdlib.h>

#define OutOfBoundariesStack 50
#define value 100000
#define constOfSub 32

#define stack_push(list, x)                                                   \
  _Generic ((*(list)),                                                        \
      struct stack_int: stack_int_push (list, x),                             \
      struct stack_char: stack_char_push (list, x))
#define stack_pop(list)                                                       \
  _Generic ((*(list)),                                                        \
      struct stack_int: stack_int_pop (list),                                 \
      struct stack_char: stack_char_pop (list))
#define stack_peek(list)                                                      \
  _Generic ((*(list)),                                                        \
      struct stack_int: stack_int_peek (list),                                \
      struct stack_char: stack_char_peek (list))
#define DEFINE_STACK(type)                                                    \
  struct stack_##type                                                         \
  {                                                                           \
    type data[value];                                                         \
    size_t size;                                                              \
  };

// DEFINE_STACK (int)
// DEFINE_STACK (char)