/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:19:42 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/11 22:36:52 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"
#include <unistd.h>

static int		read_op_code(t_data *data, t_process *process)
{
	int		op_code;

	op_code = data->mars[process->pc];
	if (op_code < 0 || op_code > 16)
		op_code = 0;
	if (op_code > 0)
		process->cooldown = op_tab[op_code - 1].cycle;
	process->color = data->colors[process->pc];
	process->op = op_code;
	if (op_code == 0)
		op_just_next(data, process, NULL);
	return (0);
}

static int		new_turn(t_data *data)
{
	t_process	*process;

	process = data->processes;
	while (process)
	{
		if (process->cooldown > 0)
			process->cooldown--;
		if (process->cooldown <= 0 && data->turn != 0)
		{
			read_operation(data, process);
			execute_operation(data, process);
		}
		process = process->next;
	}
	process = data->processes;
	while (process)
	{
		if (process->cooldown <= 0)
			read_op_code(data, process);
		process = process->next;
	}
	return (0);
}

int				manage_checks(t_data *data, int turn)
{
	if (turn == 0)
	{
		data->cycles_to_die = data->max_cycles;
		return (0);
	}
	data->cycles_to_die--;
	if (data->cycles_to_die <= 0)
		if (checks(data))
			return (1);
	return (0);
}

int				battle(t_data *data)
{
	data->turn = 0;
	if (data->visual_option && !data->dump_option)
		write(1, "\e[2J", 4);
	while (1)
	{
		show_turn(data, data->turn);
		if (data->debug_option && data->turn > 5390)
			exit(0);
		new_turn(data);
		if (manage_checks(data, data->turn))
			return (1);
		if (data->visual_option && !data->dump_option)
			buff_mars(data);
		if (data->visual_option && data->dump_option
				&& data->turn == data->cycles_before_dump)
			return (buff_mars(data));
		if (data->dump_option && data->turn == data->cycles_before_dump)
			return (dump_option_mars(data));
//		printf("battle 4 lives_count = %d\n", data->processes->lives_count);
		data->turn++;
	}
	return (0);
}
