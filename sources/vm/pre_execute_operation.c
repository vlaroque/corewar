#include <unistd.h>
#include "op.h"
#include "corewar.h"
#include "operation_reading.h"

int		(*op_fun[18])(t_data *, t_process *, t_cache *) = {
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
	op_aff
};

int		pre_execute_op(t_data *data, t_process *proc, t_cache *c)
{
	if (c->op > 0)
	{
		proc->cooldown = op_tab[c->op - 1].cycle;
		proc->todo.something_to_do = 1;
		proc->todo.pc_add = c->pc_delta;
	}
	op_fun[c->op](data, proc, c);



	return (0);
}