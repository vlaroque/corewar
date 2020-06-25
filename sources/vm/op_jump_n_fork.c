/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jump_n_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:40:46 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/19 12:13:16 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_zjmp(t_data *data, t_process *process, t_cache *c)
{
	(void)data;
	if (process->carry)
		todo_change_pc(process, c->args[0].short_data);
	if (data->verbosity & 4)
	{
		verbose_operations(data, process);
		ft_putnbr((int)c->args[0].short_data);
		if (process->carry)
			ft_putstr(" OK");
		else
			ft_putstr(" FAILED");
		verbose_opertation_end(data, process);
	}
	return (0);
}

int		op_fork(t_data *data, t_process *process, t_cache *c)
{
	int		pc;

	(void)data;
	pc = process->pc;
	pc += (c->args[0].short_data % IDX_MOD) % MEM_SIZE;
	pc = pc_fix(pc);
	todo_fork(process, pc);
	if (data->verbosity & 4)
	{
		verbose_operations(data, process);
		ft_putnbr((int)c->args[0].short_data);
		ft_putstr(" (");
		ft_putnbr(pc);
		ft_putstr(")");
		verbose_opertation_end(data, process);
	}
	return (0);
}

int		op_lfork(t_data *data, t_process *process, t_cache *c)
{
	int		pc;
	int		v_pc;

	(void)data;
	pc = process->pc;
	v_pc = pc + c->args[0].short_data;
	pc += c->args[0].short_data;
	pc = pc_fix(pc);
	todo_fork(process, pc);
	if (data->verbosity & 4)
	{
		verbose_operations(data, process);
		ft_putnbr((int)c->args[0].short_data);
		ft_putstr(" (");
		ft_putnbr(v_pc);
		ft_putstr(")");
		verbose_opertation_end(data, process);
	}
	return (0);
}
