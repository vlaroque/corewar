/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:34:34 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/19 12:25:54 by vlaroque         ###   ########.fr       */
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
	verbose_operations(data, process);
	show_reg_elsif_number(data, &c->args[0], -1);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[1], -1);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
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
	verbose_operations(data, process);
	show_reg_elsif_number(data, &c->args[0], -1);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[1], -1);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
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
	verbose_operations(data, process);
	verbose_putnbr(data, first);
	verbose_space(data);
	verbose_putnbr(data, second);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
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
	verbose_operations(data, process);
	verbose_putnbr(data, first);
	verbose_space(data);
	verbose_putnbr(data, second);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
	return (0);
}

int		op_xor(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		res;

	(void)data;
	first = get_int_from_direct_arg(data, process, &c->args[0], 1);
	second = get_int_from_direct_arg(data, process, &c->args[1], 1);
	res = first ^ second;
	todo_change_reg(process, c->args[2].octet_data, res);
	if_null_carry_up(process, res);
	verbose_operations(data, process);
	verbose_putnbr(data, first);
	verbose_space(data);
	verbose_putnbr(data, second);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
	return (0);
}
