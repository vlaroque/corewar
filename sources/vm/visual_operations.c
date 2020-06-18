/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:38:37 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/18 21:42:38 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "operation_reading.h"

int		nbr_len(int nbr)
{
	int		len;

	len = 1;
	while(nbr / 10)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

int		print_x_spaces(int x)
{
	if (x < 0)
	{
		ft_putstr("error x spaces\n");
		return (-1);
	}
	while (x)
	{
		ft_putstr(" ");
		x--;
	}
	return (0);
}

int		verbose_operations(t_data *data, t_process *p, t_cache *c)
{
	(void)c;
	if (!(data->verbosity & 4))
		return (0);
	if (p->op < 1 || p->op > 16)
		return (0);
	ft_putstr("P");
	print_x_spaces(5 - nbr_len(p->id));
	ft_putnbr(p->id);
	ft_putstr(" | ");
	ft_putstr(g_op_tab[p->op - 1].name);
	ft_putstr(" ");
	return (0);
}
