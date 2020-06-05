/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:19:42 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/05 22:38:25 by vlaroque         ###   ########.fr       */
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
	static int	turn = 0;

	process = data->processes;
	while (process)
	{
		if (process->cooldown > 0)
			process->cooldown--;
		if (process->cooldown <= 0 && turn != 0)
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
	turn++;
	return (0);
}

int				battle(t_data *data)
{
	int		turn;

	turn = 0;
	if (data->visual_option && !data->dump_option)
		write(1, "\e[2J", 4);
	while (1)
	{
		if (data->debug_option)
			printf("turn %d\n", turn);
		if (data->debug_option && turn > 5390)
			exit(0);
		new_turn(data);
		data->cycles_to_die--;
		if (data->cycles_to_die <= 0)
			if (checks(data))
				return (1);
		if (data->visual_option && !data->dump_option)
			buff_mars(data);
		if (data->visual_option && data->dump_option
				&& turn == data->cycles_before_dump)
			return (buff_mars(data));
		if (data->dump_option && turn == data->cycles_before_dump)
			return (dump_option_mars(data));
		turn++;
	}
	return (0);
}
