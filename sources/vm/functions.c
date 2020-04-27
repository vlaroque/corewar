/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:14:39 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/10 20:28:16 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

int		big_to_int(int *nbr)
{
	int			dest;
	t_octet		*dest_ptr;
	t_octet		*nbr_ptr;

	dest_ptr = (t_octet *)&dest;
	nbr_ptr = (t_octet *)nbr;
	dest_ptr[0] = nbr_ptr[3];
	dest_ptr[1] = nbr_ptr[2];
	dest_ptr[2] = nbr_ptr[1];
	dest_ptr[3] = nbr_ptr[0];
	return (dest);
}

short		big_to_short(short *nbr)
{
	short			dest;
	t_octet		*dest_ptr;
	t_octet		*nbr_ptr;

	dest_ptr = (t_octet *)&dest;
	nbr_ptr = (t_octet *)nbr;
	dest_ptr[0] = nbr_ptr[1];
	dest_ptr[1] = nbr_ptr[0];
	return (dest);
}


int		op_live(t_data *data, t_process *process, t_cache *c)
{
	process->life = 1;
	data->lives_count++;
	if (data->lives_count == NBR_LIVE)
	{
		data->lives_count = 0;
		if (data->max_cycles - CYCLE_DELTA >= 0)
			data->max_cycles -= CYCLE_DELTA;
		else
			data->max_cycles = 0;
	}
	return (0);
}

int		op_ld(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_st(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_add(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_sub(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_and(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_or(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_xor(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_zjmp(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_ldi(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_sti(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_fork(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_lld(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_lldi(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_lfork(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}

int		op_aff(t_data *data, t_process *process, t_cache *c)
{
	return (0);
}
