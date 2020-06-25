/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:38:37 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/19 12:25:07 by vlaroque         ###   ########.fr       */
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
		return (0);
	while (x)
	{
		ft_putstr(" ");
		x--;
	}
	return (0);
}

int		verbose_operations(t_data *data, t_process *p)
{
	if (!(data->verbosity & 4))
		return (0);
	if (p->op < 1 || p->op > 16)
		return (0);
	ft_putstr("P ");
	print_x_spaces(4 - nbr_len(p->id));
	ft_putnbr(p->id);
	ft_putstr(" | ");
	ft_putstr(g_op_tab[p->op - 1].name);
	ft_putstr(" ");
	return (0);
}

int		verbose_opertation_end(t_data *data, t_process *p)
{
	if (!(data->verbosity & 4))
		return (0);
	if (p->op < 1 || p->op > 16)
		return (0);
	ft_putstr("\n");
	return (0);
}

int		show_reg_elsif_number(t_data *data, t_args *arg, int nbr)
{
	if (!(data->verbosity & 4))
		return (0);
	if (arg->type == T_REG)
	{
		ft_putstr("r");
		ft_putnbr((int)arg->octet_data);
	}
	else
		ft_putnbr(nbr);
	return (0);
}

int		verbose_space(t_data *data)
{
	if (!(data->verbosity & 4))
		return (0);
	ft_putstr(" ");
	return (0);
}

int		verbose_putnbr(t_data *data, int nbr)
{
	if (!(data->verbosity & 4))
		return (0);
	ft_putnbr(nbr);
	return (0);
}
