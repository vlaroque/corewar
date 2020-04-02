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

static int		(*func[17])(t_data *, t_process *) =
{op_live, op_ld, op_st, op_add, op_sub, op_and, op_or, op_xor, op_zjmp,
	op_ldi, op_sti, op_fork, op_lld, op_lldi, op_lfork, op_aff, NULL};

int		execute_operation(t_data *data, t_process *process)
{
	func[process->instruction.op_id](data, process);
	process->cooldown--;
	usleep(100000);
	return (0);
}

int		new_turn(t_data *data)
{
	t_process	*process;

	process = data->processes;
	while (process)
	{
		if (process->cooldown > 1)
			process->cooldown--;
		else if (process->cooldown == 1)
			execute_operation(data, process);
		else if (read_operation(data, process))
			;
		else
		{
		//	usleep(100000);
			process->pc = (process->pc + 1) % MEM_SIZE;
		}
		process = process->next;
	}
	return (0);
}

int		death_reaper(t_data *data)
{
	t_process	*process;
	t_process	**previous_ptr;

	process = data->processes;
	previous_ptr = &(data->processes);
	while (process)
	{
		if (process->life == 0)
		{
			*previous_ptr = process->next;
			free(process);
		}
		else
			process->life = 0;
		previous_ptr = &process->next;
		process = process->next;
	}
	if (!data->processes)
		return (-1);
	return (0);
}

int		debug_global(t_data *data, int turn)
{
		ft_putstr("Turn = "); ft_putnbr(turn); ft_putstr("  ");
		ft_putstr("max = "); ft_putnbr(data->max_cycles); ft_putstr("  ");
		ft_putstr("lives = "); ft_putnbr(data->lives_count); ft_putstr("  ");
		if (data->processes)
			ft_putnbr(data->processes->cooldown);
		ft_putstr("           \n");
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
		buff_mars(data);
		new_turn(data);
		debug_global(data, turn);
		data->cycles_to_die--;
		if (data->cycles_to_die == 0)
			if (death_reaper(data))
				return (-1);
		turn++;
	}
	return (0);
}
