/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:34:34 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/16 12:11:01 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_add(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	(void)data;
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

	(void)data;
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

	(void)data;
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

	(void)data;
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

	(void)data;
	first = get_int_from_direct_arg(data, process, &c->args[0], 1);
	res = first ^ second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if_null_carry_up(process, res);
	return (0);
}