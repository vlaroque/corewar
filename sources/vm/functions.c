/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:14:39 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/10 20:28:16 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

int		big_to_int(int *nbr)
{
	int			dest;
	t_octet		*dest_ptr;
	t_octet		*nbr_ptr;

	dest_ptr = (t_octet *)&dest;
	nbr_ptr = (t_octet *)nbr;
	dest_ptr[0] = nbr_ptr[3];
	dest_ptr[1] = nbr_ptr[2];
	dest_ptr[2] = nbr_ptr[1];
	dest_ptr[3] = nbr_ptr[0];
	return (dest);
}

short		big_to_short(short *nbr)
{
	short			dest;
	t_octet		*dest_ptr;
	t_octet		*nbr_ptr;

	dest_ptr = (t_octet *)&dest;
	nbr_ptr = (t_octet *)nbr;
	dest_ptr[0] = nbr_ptr[1];
	dest_ptr[1] = nbr_ptr[0];
	return (dest);
}

void		todo_change_reg(t_process *p, int reg_id, int content)
{
	p->todo.cmd_change_register = 1;
	process->todo.reg = reg_id;
	process->todo.reg_content = content;
}

int		op_live(t_data *data, t_process *process, t_cache *c)
{
	process->life = 1;
	data->lives_count++;
	if (data->lives_count == NBR_LIVE)
	{
		data->lives_count = 0;
		if (data->max_cycles - CYCLE_DELTA >= 0)
			data->max_cycles -= CYCLE_DELTA;
		else
			data->max_cycles = 0;
	}
	return (0);
}

int		op_ld(t_data *data, t_process *process, t_cache *c)
{
	int		toload;

	if (c->args[0].type == T_DIR)
		toload = c->args[0].int_data;
	else if (c->args[0].type == T_IND)
		toload = read_int_mars(data, (process->pc + (c->args[0].short_data % IDX_MOD)) % MEM_SIZE);
	todo_change_reg(process, c->args[1].octet_data, toload);
	process->todo.cmd_change_register = 1;
	process->todo.reg = c->args[1].octet_data;
	process->todo.reg_content = toload;
	return (0);
}

int		op_st(t_data *data, t_process *process, t_cache *c)
{
	int		tostore;

	tostore = process->reg[c->args[0].octet_data];
	if (c->args[1].type == T_REG)'
	{

	}
	return (0);
}

int		op_add(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_sub(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_and(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_or(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_xor(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_zjmp(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_ldi(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_sti(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_fork(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_lld(t_data *data, t_process *process, t_cache *c)
{
	int		toload;

	if (c->args[0].type == T_DIR)
		toload = c->args[0].int_data;
	else if (c->args[0].type == T_IND)
		toload = read_int_mars(data, (process->pc + c->args[0].short_data) % MEM_SIZE);
	process->todo.cmd_change_register = 1;
	process->todo.reg = c->args[1].octet_data;
	process->todo.reg_content = toload;
	return (0);

	return (0);
}

int		op_lldi(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_lfork(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_aff(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}
