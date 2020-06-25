/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_stores.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:38:14 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/19 13:12:32 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_st(t_data *data, t_process *process, t_cache *c)
{
	int		tostore;
	int		pc;

	(void)data;
	tostore = process->reg[c->args[0].octet_data];
	if (c->args[1].type == T_REG)
		todo_change_reg(process, c->args[1].octet_data, tostore);
	else if (c->args[1].type == T_IND)
	{
		pc = (process->pc + (c->args[1].short_data) % IDX_MOD) % MEM_SIZE;
		todo_write_mars(process, pc, tostore);
	}
	verbose_operations(data, process);
	show_reg_elsif_number(data, &c->args[0], tostore);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[1], (int)c->args[1].short_data);
	verbose_opertation_end(data, process);
	return (0);
}

int		op_sti(t_data *data, t_process *process, t_cache *c)
{
	int		what;
	int		first;
	int		second;
	int		where;

	(void)data;
	what = process->reg[c->args[0].octet_data];
	first = get_int_from_indirect_arg(data, process, &c->args[1], 1);
	second = get_int_from_indirect_arg(data, process, &c->args[2], 1);
	where = (process->pc + ((first + second) % IDX_MOD)) % MEM_SIZE;
	todo_write_mars(process, where, what);
	v_sti(data, process, c);
	return (0);
}
