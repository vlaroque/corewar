/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_mars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:44:23 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/16 21:41:33 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

void		char_hexa_str(t_octet c, char *str)
{
	static char		base[] = "0123456789abcdef";

	str[0] = base[c / 16];
	str[1] = base[c % 16];
	str[2] = '\0';
}

int			write_in_buffer(char *buff, char *str, int i)
{
	int		a;

	a = 0;
	while (str[a])
	{
		buff[i + a] = str[a];
		a++;
	}
	return (i + a);
}

static int	write_octet_in_buffer(t_data *data, char *buff, int buff_i, int i)
{
	char	tmp[3];

	char_hexa_str(data->mars[i], tmp);
	buff_i = write_in_buffer(buff, tmp, buff_i);
	return (buff_i);
}

int			write_in_buff_formated_octet(t_data *data,
		char *buff, int buff_i, int i)
{
	if (i % 64 != 0)
		buff[buff_i++] = ' ';
	buff_i = color_octet(data, buff, buff_i, i);
	if (is_pointed(data, i))
		buff_i = write_in_buffer(buff, "\e[7m", buff_i);
	buff_i = write_octet_in_buffer(data, buff, buff_i, i);
	if (is_pointed(data, i))
	{
		buff_i = write_in_buffer(buff, "\e[0m", buff_i);
		buff_i = what_color(data, buff, buff_i, i);
	}
	if (i % 64 == 63)
		buff[buff_i++] = '\n';
	return (buff_i);
}

int			buff_mars(t_data *data)
{
	int		i;
	int		buff_i;
	char	buff[MEM_SIZE * 10];

	i = 0;
	buff_i = 0;
	if (!data->dump_option)
		write(1, "\e[H", 3);
	while (i < MEM_SIZE)
	{
		buff_i = write_in_buff_formated_octet(data, buff, buff_i, i);
		i++;
	}
	buff[buff_i] = '\0';
	write(1, buff, ft_strlen(buff));
	return (0);
}
