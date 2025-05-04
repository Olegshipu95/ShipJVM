#include "java_types.h"

jvariable
create_variable (java_value_type type)
{
  jvariable var;
  var.type = type;
  // reset all bits
  var.value._double = 0;
  return var;
}