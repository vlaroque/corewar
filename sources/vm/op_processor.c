#include <unistd.h>
#include "op.h"
#include "corewar.h"
//#include "../common/op.c"

int		(*op_fun[18])(t_data *, t_process *) = {
	op_just_next,
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff,
};

int		op_just_next(t_data *data, t_process *process)
{
	process->todo.something_to_do = 1;
	process->todo.pc_add = 1;
	return(1);
}

