/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:19:42 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/10 17:39:52 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"
#include <unistd.h>

int		new_turn(t_data *data)
{
	t_process	*process;
	static int		turn;

	process = data->processes;
	while(process)
	{
		if (process->cooldown > 0)
			process->cooldown--;
		if (process->cooldown <= 0)
			execute_operation(data, process);
		process = process->next;
	}
	process = data->processes;
	while(process)
	{
		if (process->cooldown <= 0)
			read_operation(data, process);
		process = process->next;
	}

	turn++;
	return (0);
}

int		battle(t_data *data)
{
	int		turn;

	turn = 0;
//	write(1, "\e[2J", 4);
	while (1)
	{
//		if (turn > 100000)
			//return (1 + err("end turn"));
		new_turn(data);
//		printf("turn %d\n", turn);
		//		debug_global(data, turn);
		data->cycles_to_die--;
		if (data->cycles_to_die == 0)
			if (checks(data))
				return (-1);
		if (data->visual_option && !data->dump_option)
			buff_mars(data);
		if (data->visual_option && data->dump_option && turn == data->cycles_before_dump)
			return (buff_mars(data));
		if (data->dump_option && turn == data->cycles_before_dump)
			return (dump_option_mars(data));
		turn++;
	}
	return (0);
}
