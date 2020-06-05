/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:14:39 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/05 20:53:51 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	if_null_carry_up(t_process *p, int value)
{
	if (value == 0)
		todo_carry(p, 1);
	else
		todo_carry(p, 0);
}

int		op_live(t_data *data, t_process *process, t_cache *c)
{
	process->todo.cmd_life = 1;
	process->todo.champ_id_life = c->args[0].int_data;
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
	if_null_carry_up(process, toload);
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
	if_null_carry_up(process, tostore);
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
	if_null_carry_up(process, res);
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
	if_null_carry_up(process, res);
	return (0);
}

int		op_and(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = get_int_from_direct_arg(data, process, &c->args[0], 1);
	second = get_int_from_direct_arg(data, process, &c->args[1], 1);
	res = first & second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if_null_carry_up(process, res);
	return (0);
}

int		op_or(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = get_int_from_direct_arg(data, process, &c->args[0], 1);
	second = get_int_from_direct_arg(data, process, &c->args[1], 1);
	res = first | second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if_null_carry_up(process, res);
	return (0);
}

int		op_xor(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	first = get_int_from_direct_arg(data, process, &c->args[0], 1);
	res = first ^ second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if_null_carry_up(process, res);
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
	if_null_carry_up(process, res);
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
	int		pc;

	pc = process->pc;
	pc += (c->args[0].short_data % IDX_MOD) % MEM_SIZE;
	pc = pc_fix(pc);
	todo_fork(process, pc);
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
	if_null_carry_up(process, toload);
	todo_change_reg(process, c->args[1].octet_data, toload);
	return (0);
}

int		op_lldi(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		where;
	int		res;

	first = get_int_from_indirect_arg(data, process, &c->args[0], 0);
	second = get_int_from_indirect_arg(data, process, &c->args[1], 0);
	where = (process->pc + first + second) % MEM_SIZE;
	res = read_int_mars(data, where);
	todo_change_reg(process, c->args[2].octet_data, res);
	if_null_carry_up(process, res);
	return (0);
}

int		op_lfork(t_data *data, t_process *process, t_cache *c)
{
	int		pc;

	pc = process->pc;
	pc += c->args[0].short_data % MEM_SIZE;
	pc = pc_fix(pc);
	todo_fork(process, pc);
	return (0);
}

int		op_aff(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_bad_encoding_byte(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

