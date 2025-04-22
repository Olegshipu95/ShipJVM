#include "runtime_constpool.h"

int get_runtime_constant(struct runtime_cp* runtime_cp, uint16_t index, struct cp_info **cp_info){
  if (!runtime_cp){
    prerr("runtime_cp in null");
    return EINVAL;
  }
  if (index == 0 || index >= runtime_cp->cp_count)
    {
      prerr ("Can't take constant by that adress");
      return EINVAL;
    }
  *cp_info = &(runtime_cp->cp[index - 1]);
  return 0;
}