#include "runtime_constpool.h"

int
get_UTF8 (struct cp_info *cp_info, struct UTF8_info *utf8,
          uint16_t constant_pool_count, uint16_t index)
{
  if (!cp_info)
    {
      prerr ("Invalid arguments in get_const");
      return EINVAL;
    }

  if (index == 0 || index >= constant_pool_count)
    {
      prerr ("Can't take constant by that adress in runtime_cp");
      return EINVAL;
    }
  struct cp_info *local = &(cp_info[index - 1]);
  if (local->tag != UTF8)
    {
      prerr ("CP by index %hu is - %d, but expected UTF", index, local->tag);
      return EINVAL;
    }

  utf8 = &local->utf8_info;
  return 0;
}

int
utf8_to_string (struct UTF8_info *utf8, string *dest)
{
  uint16_t length = utf8->lenght;
  string local = my_alloc_array (char, length + 1);
  if (local == NULL)
    {
      prerr ("Can not allocate memory for string");
      return ENOMEM;
    }
  memcpy (*dest, utf8->bytes, length + 1);
  (*dest)[length] = 0;
  return 0;
}

int
new_array_runtime_constpool (struct runtime_cp **runtime_cp,
                             struct cp_info *cp_info,
                             uint16_t constant_pool_count)
{
  uint16_t iter;
  if (cp_info == NULL)
    {
      prerr ("cp_info is null while making new_array_runtime_constpool");
      return EINVAL;
    }

  struct runtime_cp *new
      = my_alloc_array (struct runtime_cp, constant_pool_count);

  if (new == NULL)
    {
      prerr ("Can not allocate memory for runtime constant pool");
      return ENOMEM;
    }

  for (iter = 0; iter < constant_pool_count; ++iter)
    {
      struct cp_info local = cp_info[iter];
      new[iter].tag = local.tag;
      switch (local.tag)
        {

        case UTF8:
          uint16_t length = local.utf8_info.lenght;
          new[iter].utf8 = my_alloc_array (char, length + 1);

          if (new[iter].utf8 == NULL)
            {
              prerr ("Can not allocate memory for utf8 in runtime cp");
              return ENOMEM;
            }
          memcpy ((void *)new[iter].utf8, (void *)local.utf8_info.bytes,
                  length);
          new[iter].utf8[length] = 0;
          break;

        case INTEGER:
          memcpy (&new[iter].integer_info, &local.integer_info.info.bytes,
                  sizeof (jint));
          break;

        case FLOAT:
          memcpy (&new[iter].float_info, &local.float_info.info.bytes,
                  sizeof (jfloat));
          break;

        case LONG:
          uint64_t unsigned_val
              = ((uint64_t)local.long_info.info.high_bytes << 32)
                | local.long_info.info.low_bytes;
          memcpy (&new[iter].long_info, &unsigned_val, sizeof (jlong));
          break;

        case DOUBLE:
          uint64_t unsigned_val
              = ((uint64_t)local.double_info.info.high_bytes << 32)
                | local.double_info.info.low_bytes;
          memcpy (&new[iter].double_info, &unsigned_val, sizeof (jdouble));
          break;

        case CLASS:
          int err = 0;

          uint16_t index = local.class_info.name_index;
          struct UTF8_info utf8;
          err = get_UTF8 (cp_info, &utf8, constant_pool_count, index);
          if (err)
            {
              prerr ("can not take utf while parsing class");
              return -1;
            }

          new[iter].class_name = my_alloc_array (char, utf8.lenght + 1);

          break;

        case STRING:
          break;

        case FIELD_REF:
          break;

        case METHOD_REF:
          break;

        case INTERF_METHOD_REF:
          break;

        case NAME_AND_TYPE:
          break;

        case METHOD_HANDLE:
          break;

        case METHOD_TYPE:
          break;

        case DYNAMIC:
          break;

        case INVOKE_METHOD:
          break;

        case MODULE:
          break;

        case PACKAGE:
          break;

        default:
          break;
        }
    }

  *runtime_cp = new;
  return -1;
}