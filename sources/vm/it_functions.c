/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   it_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:10:37 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/05 20:45:39 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

int			it_live(t_data *data, t_process *process, int champ_id)
{
	t_champ		*champ;

	data->lives_count++;
	process->lives_count++;
	champ = data->champs;
	while (champ)
	{
		if (champ->id == champ_id)
			data->last_alive = champ_id;
		champ = champ->next;
	}
	return (champ_id);
}

static void	process_copy(t_process *src, t_process *dst)
{
	int		i;

	dst->carry = src->carry;
	i = 0;
	while (i < REG_NUMBER + 1)
	{
		dst->reg[i] = src->reg[i];
		i++;
	}
}

int			it_fork(t_data *data, t_process *process, int pc)
{
	new_process(data, pc, 0);
	process_copy(process, data->processes);
	op_bzero(&data->processes->todo, sizeof(t_todo));
	data->processes->pc = pc;
	return (0);
}

int			it_aff(t_data *data, t_process *process, char pc)
{
	write(0, &pc, 1);
	return (0);
}
