/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:56:00 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/16 23:13:16 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

int			is_pointed(t_data *data, int pc)
{
	t_process	*process;

	process = data->processes;
	while (process)
	{
		if (process->pc == pc)
			return (1);
		process = process->next;
	}
	return (0);
}

void		fill_address(char *adress)
{
	static int		adress_nbr = 0;
	static char		base[] = "0123456789abcdef";

	adress[0] = '0';
	adress[1] = 'x';
	adress[2] = base[(adress_nbr / 4096) % 16];
	adress[3] = base[(adress_nbr / 256) % 16];
	adress[4] = base[(adress_nbr / 16) % 16];
	adress[5] = base[adress_nbr % 16];
	adress[6] = ' ';
	adress[7] = ':';
	adress[8] = ' ';
	adress[9] = '\0';
	adress_nbr += 64;
}

int			dump_option_mars(t_data *data)
{
	int		i;
	int		buff_i;
	char	tmp[3];
	char	adress[10];
	char	buff[MEM_SIZE * 10];

	i = 0;
	buff_i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			fill_address(adress);
			buff_i = write_in_buffer(buff, adress, buff_i);
		}
		char_hexa_str(data->mars[i], tmp);
		buff_i = write_in_buffer(buff, tmp, buff_i);
		buff[buff_i++] = ' ';
		if (i % 64 == 63)
			buff[buff_i++] = '\n';
		i++;
	}
	buff[buff_i] = '\0';
	write(1, buff, ft_strlen(buff));
	return (0);
}
