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

  *utf8 = local->utf8_info;
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
  memcpy (local, utf8->bytes, length + 1);
  local[length] = 0;
  *dest = local;
  return 0;
}

int
index_to_string (string *dest, struct cp_info *cp_info,
                 uint16_t constant_pool_count, uint16_t index)
{
  int err;
  struct UTF8_info utf8;

  err = get_UTF8 (cp_info, &utf8, constant_pool_count, index);
  if (err)
    {
      prerr ("can not convert index to string");
      return -1;
    }

  utf8_to_string (&utf8, dest);
  return 0;
}

reference_types
uint8_to_reference_type (uint8_t value)
{

  if (value >= REF_getField && value <= REF_invokeInterface)
    {
      return (reference_types)value;
    }

  prerr ("Invalid reference_type value: %hhu\n", value);
  return REF_INVALID;
}

int
new_array_runtime_constpool (struct runtime_cp **runtime_cp,
                             struct cp_info *cp_info,
                             uint16_t constant_pool_count)
{
  uint16_t iter;
  int err;
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

  memset (new, 0, sizeof (struct runtime_cp) * constant_pool_count);

  for (iter = 0; iter < constant_pool_count; ++iter)
    {
      if (new[iter].tag == 0)
        {
          continue;
        }

      struct cp_info local = cp_info[iter];
      new[iter].tag = local.tag;
      switch (local.tag)
        {
        case UTF8:
          {
            if (utf8_to_string (&local.utf8_info, &new[iter].utf8))
              {
                prerr ("Can not convert utf8 in runtime cp");
                return -1;
              }
          }
          break;

        case INTEGER:
          {
            memcpy (&new[iter].integer_info, &local.integer_info.info.bytes,
                    sizeof (jint));
          }
          break;

        case FLOAT:
          {
            memcpy (&new[iter].float_info, &local.float_info.info.bytes,
                    sizeof (jfloat));
          }
          break;

        case LONG:
          {
            uint64_t unsigned_val
                = ((uint64_t)local.long_info.info.high_bytes << 32)
                  | local.long_info.info.low_bytes;
            memcpy (&new[iter].long_info, &unsigned_val, sizeof (jlong));
          }
          break;

        case DOUBLE:
          {
            uint64_t unsigned_val
                = ((uint64_t)local.double_info.info.high_bytes << 32)
                  | local.double_info.info.low_bytes;
            memcpy (&new[iter].double_info, &unsigned_val, sizeof (jdouble));
          }
          break;

        case CLASS:
          {
            err = index_to_string (&new[iter].class_name, cp_info,
                                   constant_pool_count,
                                   local.class_info.name_index);

            if (err)
              {
                prerr ("can not take utf while parsing class");
                return -1;
              }
          }
          break;

        case STRING:
          {
            err = index_to_string (&new[iter].string_info, cp_info,
                                   constant_pool_count,
                                   local.string_info.string_index);

            if (err)
              {
                prerr ("Can not take utf while parsing string");
                return -1;
              }
          }
          break;

        case FIELD_REF:

          /*
          FIELD REF contains two refs -> class and NameTypeInfo
          First we need to check that these fields are already in runtime_cp
          */
          {
            // first parse class name
            uint16_t index;
            index = local.fieldref_info.info.class_index;
            if (index >= constant_pool_count)
              {
                prerr ("Incorrect index in field ref");
                return -1;
              }
            if (new[index].tag == 0)
              {
                new[index].tag = cp_info[index].tag;

                if (cp_info[index].tag != CLASS)
                  {
                    prerr ("index in field_ref is not class index");
                    return -1;
                  }

                err = index_to_string (&new[index].class_name, cp_info,
                                       constant_pool_count,
                                       cp_info[index].class_info.name_index);

                if (err)
                  {
                    prerr ("Can not parse class tag in FIELD_RED");
                    return -1;
                  }
              }

            new[iter].fieldref.ref.class_name = new[index].class_name;

            // after name parse name and type
            index = local.fieldref_info.info.name_and_type_index;

            if (index >= constant_pool_count)
              {
                prerr ("Incorrect index in field ref");
                return -1;
              }

            if (new[index].tag == 0)
              {
                new[index].tag = cp_info[index].tag;

                if (cp_info[index].tag != NAME_AND_TYPE)
                  {
                    prerr ("index in field_ref is not NAME_AND_TYPE index");
                    return -1;
                  }

                err = index_to_string (
                    &new[index].name_and_type.name, cp_info,
                    constant_pool_count,
                    cp_info[index].name_and_type_info.name_index);

                err |= index_to_string (
                    &new[index].name_and_type.descriptor, cp_info,
                    constant_pool_count,
                    cp_info[index].name_and_type_info.descripror_index);

                if (err)
                  {
                    prerr ("Can not convert name_and_type in runtime cp");
                    return -1;
                  }

                if (err)
                  {
                    prerr ("Can not parse class tag in FIELD_RED");
                    return -1;
                  }
              }

            new[iter].fieldref.ref.nat.name = new[index].name_and_type.name;
            new[iter].fieldref.ref.nat.descriptor
                = new[index].name_and_type.descriptor;
          }

          break;

        case METHOD_REF:

          /*
          METHOD_REF contains two refs -> class and NameTypeInfo
          First we need to check that these fields are already in runtime_cp
          */
          {
            // first parse class name
            uint16_t index;
            index = local.methodref_info.info.class_index;
            if (index >= constant_pool_count)
              {
                prerr ("Incorrect index in METHOD_REF");
                return -1;
              }
            if (new[index].tag == 0)
              {
                new[index].tag = cp_info[index].tag;

                if (cp_info[index].tag != CLASS)
                  {
                    prerr ("index in METHOD_REF is not class index");
                    return -1;
                  }

                err = index_to_string (&new[index].class_name, cp_info,
                                       constant_pool_count,
                                       cp_info[index].class_info.name_index);

                if (err)
                  {
                    prerr ("Can not parse class tag in METHOD_REF");
                    return -1;
                  }
              }

            new[iter].methodref.ref.class_name = new[index].class_name;

            // after name parse name and type
            index = local.methodref_info.info.name_and_type_index;

            if (index >= constant_pool_count)
              {
                prerr ("Incorrect index in METHOD_REF");
                return -1;
              }

            if (new[index].tag == 0)
              {
                new[index].tag = cp_info[index].tag;

                if (cp_info[index].tag != NAME_AND_TYPE)
                  {
                    prerr ("index in METHOD_REF is not NAME_AND_TYPE index");
                    return -1;
                  }

                err = index_to_string (
                    &new[index].name_and_type.name, cp_info,
                    constant_pool_count,
                    cp_info[index].name_and_type_info.name_index);

                err |= index_to_string (
                    &new[index].name_and_type.descriptor, cp_info,
                    constant_pool_count,
                    cp_info[index].name_and_type_info.descripror_index);

                if (err)
                  {
                    prerr ("Can not convert name_and_type in METHOD_REF");
                    return -1;
                  }

                if (err)
                  {
                    prerr ("Can not parse class tag in METHOD_REF");
                    return -1;
                  }
              }

            new[iter].methodref.ref.nat.name = new[index].name_and_type.name;
            new[iter].methodref.ref.nat.descriptor
                = new[index].name_and_type.descriptor;
          }
          break;

        case INTERF_METHOD_REF:

          /*
          INTERF_METHOD_REF contains two refs -> class and NameTypeInfo
          First we need to check that these fields are already in runtime_cp
          */
          {
            // first parse class name
            uint16_t index;
            index = local.interface_meth_ref_info.info.class_index;
            if (index >= constant_pool_count)
              {
                prerr ("Incorrect index in INTERF_METHOD_REF");
                return -1;
              }
            if (new[index].tag == 0)
              {
                new[index].tag = cp_info[index].tag;

                if (cp_info[index].tag != CLASS)
                  {
                    prerr ("index in INTERF_METHOD_REF is not class index");
                    return -1;
                  }

                err = index_to_string (&new[index].class_name, cp_info,
                                       constant_pool_count,
                                       cp_info[index].class_info.name_index);

                if (err)
                  {
                    prerr ("Can not parse class tag in INTERF_METHOD_REF");
                    return -1;
                  }
              }

            new[iter].methodref.ref.class_name = new[index].class_name;

            // after name parse name and type
            index = local.methodref_info.info.name_and_type_index;

            if (index >= constant_pool_count)
              {
                prerr ("Incorrect index in INTERF_METHOD_REF");
                return -1;
              }

            if (new[index].tag == 0)
              {
                new[index].tag = cp_info[index].tag;

                if (cp_info[index].tag != NAME_AND_TYPE)
                  {
                    prerr ("index in INTERF_METHOD_REF is not NAME_AND_TYPE "
                           "index");
                    return -1;
                  }

                err = index_to_string (
                    &new[index].name_and_type.name, cp_info,
                    constant_pool_count,
                    cp_info[index].name_and_type_info.name_index);

                err |= index_to_string (
                    &new[index].name_and_type.descriptor, cp_info,
                    constant_pool_count,
                    cp_info[index].name_and_type_info.descripror_index);

                if (err)
                  {
                    prerr (
                        "Can not convert name_and_type in INTERF_METHOD_REF");
                    return -1;
                  }

                if (err)
                  {
                    prerr ("Can not parse class tag in INTERF_METHOD_REF");
                    return -1;
                  }
              }

            new[iter].interf_meth.ref.nat.name = new[index].name_and_type.name;
            new[iter].interf_meth.ref.nat.descriptor
                = new[index].name_and_type.descriptor;
          }
          break;

        case NAME_AND_TYPE:
          {
            err = index_to_string (&new[iter].name_and_type.name, cp_info,
                                   constant_pool_count,
                                   local.name_and_type_info.name_index);
            err |= index_to_string (&new[iter].name_and_type.descriptor,
                                    cp_info, constant_pool_count,
                                    local.name_and_type_info.descripror_index);
            if (err)
              {
                prerr ("Can not convert name_and_type in runtime cp");
                return -1;
              }
          }
          break;

        case METHOD_HANDLE:
          {
            new[iter].method_handle.kind = uint8_to_reference_type (
                local.method_handle_info.reference_kind);
            if (local.method_handle_info.reference_index
                >= constant_pool_count)
              {
                prerr ("Invalid index in METHOD_HANDLE");
                return -1;
              }
          }
          break;

        case METHOD_TYPE:
          {
            err = index_to_string (&new[iter].method_type, cp_info,
                                   constant_pool_count,
                                   local.method_type_info.descriptor_index);
            if (err)
              {
                prerr ("Can not convert method type in rt cp");
                return -1;
              }
          }
          break;

        case DYNAMIC:
          {
            prerr ("Can not parse DYNAMIC");
            return -1;
          }
          break;

        case INVOKE_METHOD:
          {
          }
          break;

        case MODULE:
          {
            err = 0;

            uint16_t index = local.module_info.name_index;
            struct UTF8_info utf8;
            err = get_UTF8 (cp_info, &utf8, constant_pool_count, index);
            if (err)
              {
                prerr ("can not take utf while parsing module const");
                return -1;
              }
            utf8_to_string (&utf8, &(new[iter].module));
          }
          break;

        case PACKAGE:
          {
            err = 0;

            uint16_t index = local.package_info.name_index;
            struct UTF8_info utf8;
            err = get_UTF8 (cp_info, &utf8, constant_pool_count, index);
            if (err)
              {
                prerr ("can not take utf while parsing package const");
                return -1;
              }
            utf8_to_string (&utf8, &(new[iter].package));
          }
          break;

        default:
          break;
        }
    }

  *runtime_cp = new;
  return -1;
}