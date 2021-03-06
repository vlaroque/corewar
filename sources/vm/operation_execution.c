/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:08:28 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/25 23:25:30 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		color_mars(t_data *data, int color, int pc)
{
	pc = pc_fix(pc);
	data->colors[pc % MEM_SIZE] = color;
	data->colors[(pc + 1) % MEM_SIZE] = color;
	data->colors[(pc + 2) % MEM_SIZE] = color;
	data->colors[(pc + 3) % MEM_SIZE] = color;
}

int			v_process_mvt(t_data *data, t_process *process, int to_add)
{
	int		new_pc;

	if (!(data->verbosity & 16))
		return (0);
	ft_putstr("process ");
	ft_putnbr(process->id);
	ft_putstr(" was ");
	ft_putnbr(process->pc);
	new_pc = pc_fix(process->pc + to_add);
	ft_putstr(" now ");
	ft_putnbr(new_pc);
	ft_putstr("\n");
	return (0);
}

int			execute_operation(t_data *data, t_process *process)
{
	if (!process->todo.something_to_do)
		return (0);
	if (process->todo.pc_add)
	{
		v_process_mvt(data, process, process->todo.pc_add);
		process->pc = pc_fix((process->todo.pc_add + process->pc) % MEM_SIZE);
	}
	if (process->todo.cmd_life)
		it_live(data, process, process->todo.champ_id_life);
	if (process->todo.cmd_write_on_mars)
	{
		write_int_mars(data, process->todo.mars_content, process->todo.pc);
		color_mars(data, process->color, process->todo.pc);
	}
	if (process->todo.cmd_change_register)
		process->reg[process->todo.reg] = process->todo.reg_content;
	if (process->todo.cmd_change_carry)
		process->carry = process->todo.carry_content;
	if (process->todo.cmd_fork)
		it_fork(data, process, process->todo.fork_pc);
	if (process->todo.cmd_aff)
		it_aff(data, process, process->todo.char_to_aff);
	op_bzero(&process->todo, sizeof(t_todo));
	return (1);
}
