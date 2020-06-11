/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:44:21 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/11 22:39:43 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		death_reaper(t_data *data)
{
	t_process		*p;
	t_process		**previous;

	p = data->processes;
	previous = &(data->processes);
	while (p)
	{
		if (p->lives_count <= 0)
		{
			*previous = p->next;
			show_process_death(data, p);
			free(p);
			p = *previous;
		}
		else
		{
			p->lives_count = 0;
			previous = &p->next;
			p = p->next;
		}
	}
	return (0);
}

int		checks(t_data *data)
{
	death_reaper(data);
	if (data->processes == NULL)
		return (1);
	if (data->lives_count >= NBR_LIVE)
	{
		data->max_cycles -= CYCLE_DELTA;
		show_cycle_to_die(data, data->max_cycles);
		data->checks_count = 0;
	}
	else if (data->checks_count >= MAX_CHECKS - 1)
	{
		data->max_cycles -= CYCLE_DELTA;
		show_cycle_to_die(data, data->max_cycles);
		data->checks_count = 0;
	}
	else
		data->checks_count += 1;
	data->lives_count = 0;
	data->cycles_to_die = data->max_cycles;
	return (0);
}
