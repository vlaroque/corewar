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

int		death_reaper(t_data *data)
{
	return (0);
}

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
		{
			buff_mars(data);
			printf("t %d nouvelle op\n", turn);
			execute_operation(data, process);
			read_operation(data, process);
			getchar();
		}
//		usleep(10000);
		process = process->next;
	}
	turn++;
	return (0);
}

int		battle(t_data *data)
{
	int		turn;

	turn = 0;
	write(1, "\e[2J", 4);
	while (1)
	{
		if (turn > 100000)
			return (1 + err("end turn"));
//		buff_mars(data);
		new_turn(data);
		//		debug_global(data, turn);
		data->cycles_to_die--;
		if (data->cycles_to_die == 0)
			if (death_reaper(data))
				return (-1);
		turn++;
	}
	return (0);
}
