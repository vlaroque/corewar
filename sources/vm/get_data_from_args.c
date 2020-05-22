#include "op.h"
#include "corewar.h"

//deprecated
int		get_int_from_arg(t_data *d, t_process *p, t_cache *c, int arg_id)
{
	int		res;

	if (c->args[arg_id].type == T_REG)
		res = p->reg[c->args[arg_id].octet_data];
	else if (c->args[arg_id].type == T_IND)
		res = read_int_mars(d, (p->pc + c->args[arg_id].short_data)
				% MEM_SIZE);
	else if (c->args[arg_id].type == T_DIR)
		res = c->args[arg_id].int_data;
	return(res);
}

int		get_int_from_direct_arg(t_data *d, t_process *p, t_args *arg,
		int idx_lim)
{
	int		res;

	if (arg->type == T_REG)
		res = p->reg[arg->octet_data];
	else if (arg->type == T_IND && idx_lim)
		res = read_int_mars(d, ((p->pc + arg->short_data) % IDX_MOD) % MEM_SIZE);
	else if (arg->type == T_IND)
		res = read_int_mars(d, (p->pc + arg->short_data) % MEM_SIZE);
	else if (arg->type == T_DIR)
		res = arg->int_data;
	return(res);
}


int		get_int_from_indirect_arg(t_data *d, t_process *p, t_args *arg,
		int idx_lim)
{
	int		res;

	if (arg->type == T_REG)
		res = p->reg[arg->octet_data];
	else if (arg->type == T_IND && idx_lim)
		res = read_int_mars(d, ((p->pc + arg->short_data) % IDX_MOD) % MEM_SIZE);
	else if (arg->type == T_IND)
		res = read_int_mars(d, (p->pc + arg->short_data) % MEM_SIZE);
	else if (arg->type == T_DIR)
		res = arg->short_data;
	return(res);
}


