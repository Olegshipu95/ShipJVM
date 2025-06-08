#include "java_types.h"
#include "errno.h"
#include "stdio.h"
#include "util.h"
jvariable
create_variable (java_value_type type)
{
  jvariable var;
  var.type = type;

  switch (type)
    {
    case JBOOLEAN:
      var.value._bool = 0;
      break;
    case JBYTE:
      var.value._byte = 0;
      break;
    case JCHAR:
      var.value._char = 0;
      break;
    case JSHORT:
      var.value._short = 0;
      break;
    case JINT:
      var.value._int = 0;
      break;
    case JLONG:
      var.value._long = 0;
      break;
    case JFLOAT:
      var.value._float = 0.0f;
      break;
    case JDOUBLE:
      var.value._double = 0.0;
      break;
    case JOBJECT:
      var.value._object = NULL;
      break;
    default:
      PANIC ("Can not create var for %d type", type);
    }

  return var;
}

int
var_computation_type (jvariable *var)
{
  switch (var->type)
    {
    case JBOOLEAN:
    case JBYTE:
    case JCHAR:
    case JSHORT:
    case JINT:
    case JFLOAT:
    case JOBJECT:
      return 1;
      break;

    case JLONG:
    case JDOUBLE:
      return 2;
      break;

    default:
      prerr ("Unknown type in var_computation_type");
      return -1;
      break;
    }
}

int
check_var_type (jvariable *var, java_value_type type)
{
  if (var->type != type)
    {
      prerr ("check var type failed. Var - %d, expected - %d",
             (int)(var->type), (int)(type));
      return -1;
    }
  return 0;
}