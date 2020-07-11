/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:26:23 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/11 23:38:39 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

int			new_process(t_data *data, int loc, int champ_id)
{
	t_process		*process;
	static int		id = 1;

	if (!(process = (t_process *)malloc(sizeof(t_process))))
		print_error(data, -1);
	op_bzero(process, sizeof(t_process));
	process->id = id;
	id++;
	process->pc = loc;
	process->reg[1] = champ_id;
	if (data->processes)
		process->next = data->processes;
	data->processes = process;
	return (0);
}
