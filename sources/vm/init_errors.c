/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:44:33 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/16 15:00:49 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

static int	print_error_more(int error)
{
	if (error == -1)
		ft_putstr("Malloc failed, program exit\n");
	else if (error == -2)
		ft_putstr("Cannot open file\n");
	return (0);
}

int			print_error(t_data *data, int error)
{
	ft_putstr("Error: ");
	print_error_more(error);
	if (error == 1)
		ft_putstr("-dump nbr_cycles, nbr_cycles is not a number\n");
	else if (error == 2)
		ft_putstr("-dump nbr_cycles, nbr_cycles cannot be negative\n");
	else if (error == 3)
		ft_putstr("-dump nbr_cycles, nbr_cycles is missing\n");
	else if (error == 10)
		ft_putstr("-n number, number is missing\n");
	else if (error == 11)
		ft_putstr("-n number, number is not a number\n");
	else if (error == 20)
		ft_putstr("Too short file\n");
	else if (error == 21)
		ft_putstr("Wrong magic number\n");
	else if (error == 22)
		ft_putstr("Champion is too big\n");
	else if (error == 30)
		ft_putstr("Too much champions\n");
	else if (error == 40)
		ft_putstr("Cannot assign twice the same champion id\n");
	free_data(data);
	exit(0);
}

int			ft_isnbr(char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		str++;
	if (*str >= '0' && *str <= '9')
		return (1);
	else
		return (0);
}

int			print_usage(t_data *data)
{
	ft_putstr("Usage: ./corewar [-dump nbr_cycles] [[-n number] ");
	ft_putstr("champion1.cor] ...\n");
	ft_putstr("\t-dump nbr_cycles   : Dumps memory after nbr_cycles cycles ");
	ft_putstr("then exits\n");
	ft_putstr("\t-n number          : Set the number of the next champion\n");
	free_data(data);
	exit(0);
	return (0);
}
