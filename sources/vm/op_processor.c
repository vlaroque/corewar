#include <unistd.h>
#include "op.h"
#include "corewar.h"
//#include "../common/op.c"

int		op_just_next(t_data *data, t_process *process, t_cache *c)
{
	process->todo.something_to_do = 1;
	process->todo.pc_add = 1;
	return(1);
}

