/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:14:39 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/16 12:15:01 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

short	big_to_short(short *nbr)
{
	short		dest;
	t_octet		*dest_ptr;
	t_octet		*nbr_ptr;

	dest_ptr = (t_octet *)&dest;
	nbr_ptr = (t_octet *)nbr;
	dest_ptr[0] = nbr_ptr[1];
	dest_ptr[1] = nbr_ptr[0];
	return (dest);
}

void	if_null_carry_up(t_process *p, int value)
{
	if (value == 0)
		todo_carry(p, 1);
	else
		todo_carry(p, 0);
}
