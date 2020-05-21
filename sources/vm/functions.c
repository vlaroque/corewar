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
	char		c;
	p->todo.cmd_change_register = 1;
	p->todo.reg = reg_id;
	p->todo.reg_content = content;
//	printf("change reg id [%d] | cnt %d\n", p->todo.reg, 
//	p->todo.reg_content);
//	c = getchar();

}


void	todo_write_mars(t_process *p, int where, int what)
{
	p->todo.cmd_write_on_mars = 1;
	p->todo.pc = where;
	p->todo.mars_content = what;
}

void	todo_fork(t_process *p, int where)
{
	p->todo.cmd_fork = 1;
	p->todo.fork_pc = where;
}

void	todo_carry(t_process *p, int carry)
{
	p->todo.cmd_change_carry = 1;
	p->todo.carry_content = carry;
}

void	todo_change_pc(t_process *p, int pc)
{
	int		res;

	res = p->pc;
	res += pc;
	res = res % MEM_SIZE;
	if (res < 0)
		res += MEM_SIZE;
	p->todo.pc_add = res;
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
	int		pc;

	if (c->args[0].type == T_DIR)
		toload = c->args[0].int_data;
	else if (c->args[0].type == T_IND)
	{
		pc = (process->pc + (c->args[0].short_data % IDX_MOD)) % MEM_SIZE;
		toload = read_int_mars(data, pc);
	}
	todo_change_reg(process, c->args[1].octet_data, toload);
	return (0);
}

int		op_st(t_data *data, t_process *process, t_cache *c)
{
	int		tostore;
	int		pc;

	tostore = process->reg[c->args[0].octet_data];
	if (c->args[1].type == T_REG)
		todo_change_reg(process, c->args[1].octet_data, tostore);
	else if (c->args[1].type == T_IND)
	{
		pc = (process->pc + (c->args[1].short_data) % IDX_MOD) % MEM_SIZE;
		todo_write_mars(process, pc, tostore);
	}
	return (0);
}

int		op_add(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = process->reg[c->args[0].octet_data];
	second = process->reg[c->args[1].octet_data];
	res = first + second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if (res == 0)
		todo_carry(process, 1);
	else
		todo_carry(process, 0);
	return (0);
}

int		op_sub(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = process->reg[c->args[0].octet_data];
	second = process->reg[c->args[1].octet_data];
	res = first - second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if (res == 0)
		todo_carry(process, 1);
	else
		todo_carry(process, 0);
	return (0);
}

int		op_and(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = get_int_from_arg(data, process, c, 0);
	second = get_int_from_arg(data, process, c, 1);
	res = first & second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if (res == 0)
		todo_carry(process, 1);
	else
		todo_carry(process, 0);
	return (0);
}

int		op_or(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = get_int_from_arg(data, process, c, 0);
	second = get_int_from_arg(data, process, c, 1);
	res = first | second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if (res == 0)
		todo_carry(process, 1);
	else
		todo_carry(process, 0);
	return (0);
}

int		op_xor(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = get_int_from_arg(data, process, c, 0);
	second = get_int_from_arg(data, process, c, 1);
	res = first ^ second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if (res == 0)
		todo_carry(process, 1);
	else
		todo_carry(process, 0);
	return (0);
}

int		op_zjmp(t_data *data, t_process *process, t_cache *c)
{
	if (process->carry)
		todo_change_pc(process, c->args[0].short_data);
	return (0);
}

int		op_ldi(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		where;
	int		res;

	first = get_int_from_indirect_arg(data, process, &c->args[0], 1);
	second = get_int_from_indirect_arg(data, process, &c->args[1], 1);
	where = (process->pc + ((first + second) % IDX_MOD)) % MEM_SIZE;
	res = read_int_mars(data, where);
	todo_change_reg(process, c->args[2].octet_data, res);
	return (0);
}

int		op_sti(t_data *data, t_process *process, t_cache *c)
{
	int		what;
	int		first;
	int		second;
	int		where;

	what = process->reg[c->args[0].octet_data];
	first = get_int_from_indirect_arg(data, process, &c->args[1], 1);
	second = get_int_from_indirect_arg(data, process, &c->args[2], 1);
	where = (process->pc + ((first + second) % IDX_MOD)) % MEM_SIZE;
	todo_write_mars(process, where, what);
	return (0);
}

int		op_fork(t_data *data, t_process *process, t_cache *c)
{
	todo_fork(process, (c->args[0].short_data % IDX_MOD) % MEM_SIZE);
	return (0);
}

int		op_lld(t_data *data, t_process *process, t_cache *c)
{
	int		toload;
	int		pc;

	if (c->args[0].type == T_DIR)
		toload = c->args[0].int_data;
	else if (c->args[0].type == T_IND)
	{
		pc = (process->pc + c->args[0].short_data) % MEM_SIZE;
		toload = read_int_mars(data, pc);
	}
	todo_change_reg(process, c->args[1].octet_data, toload);
	return (0);
}

int		op_lldi(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		where;
	int		res;

	first = get_int_from_indirect_arg(data, process, &c->args[0], 1);
	second = get_int_from_indirect_arg(data, process, &c->args[1], 1);
	where = (process->pc + first + second) % MEM_SIZE;
	res = read_int_mars(data, where);
	todo_change_reg(process, c->args[2].octet_data, res);
	return (0);

	return (0);
}

int		op_lfork(t_data *data, t_process *process, t_cache *c)
{
	todo_fork(process, c->args[0].short_data % MEM_SIZE);
	return (0);
}

int		op_aff(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}
