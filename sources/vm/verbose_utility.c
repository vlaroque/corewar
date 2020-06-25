/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 23:32:53 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/25 23:36:54 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "operation_reading.h"

int		nbr_len(int nbr)
{
	int		len;

	len = 1;
	while (nbr / 10)
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
