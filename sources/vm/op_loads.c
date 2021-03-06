/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_loads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:27:55 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/19 12:49:54 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_ld(t_data *data, t_process *process, t_cache *c)
{
	int		toload;
	int		pc;

	toload = 0;
	if (c->args[0].type == T_DIR)
		toload = c->args[0].int_data;
	else if (c->args[0].type == T_IND)
	{
		pc = (process->pc + (c->args[0].short_data % IDX_MOD)) % MEM_SIZE;
		toload = read_int_mars(data, pc);
	}
	if_null_carry_up(process, toload);
	todo_change_reg(process, c->args[1].octet_data, toload);
	verbose_operations(data, process);
	verbose_putnbr(data, toload);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[1], -1);
	verbose_opertation_end(data, process);
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
	v_ldi(data, process, c);
	return (0);
}

int		op_lld(t_data *data, t_process *process, t_cache *c)
{
	int		toload;
	int		pc;

	toload = 0;
	if (c->args[0].type == T_DIR)
		toload = c->args[0].int_data;
	else if (c->args[0].type == T_IND)
	{
		pc = (process->pc + c->args[0].short_data) % MEM_SIZE;
		toload = read_int_mars(data, pc);
	}
	if_null_carry_up(process, toload);
	todo_change_reg(process, c->args[1].octet_data, toload);
	verbose_operations(data, process);
	verbose_putnbr(data, toload);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[1], -1);
	verbose_opertation_end(data, process);
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
	v_lldi(data, process, c);
	return (0);
}
